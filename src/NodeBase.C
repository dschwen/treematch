#include "DecisionTreeNode.h"
#include "NodeBase.h"

#include <algorithm>

NodeBase::NodeBase() : _wildcard_mask(0), _dying(false) {}

NodeBase::NodeBase(std::initializer_list<NodeBase *> children)
    : _children(children), _wildcard_mask(0), _dying(false) {
  for (auto &c : _children)
    c->_parent = this;
}

NodeBase::NodeBase(const NodeBase *rhs) {
  _wildcard_mask = rhs->_wildcard_mask;
  _dying = rhs->_dying;
  for (auto &c : _children)
    _children.push_back(c->clone());
}

NodeBase::~NodeBase() {
  // going into teardown state
  _dying = true;

  // delete all children
  for (auto &c : _children)
    delete c;

  // if the parent is not in teardown mode remove self from list of children,
  // otherwise it is both unnecessary and will invalidate teh iterator in the
  // loop directly above.
  if (_parent && !_parent->_dying)
    _parent->unlinkChild(this);
}

void NodeBase::print(std::string indent) const {
  std::cout << indent;
  printLocal();
  std::cout << '\n';

  for (auto &c : _children)
    c->print(indent + "  ");
}

void NodeBase::updateHash(
    std::set<std::size_t> *hash_set,
    std::unordered_multimap<std::size_t, NodeBase *> *hash_map) {
  // hash the node specific data
  updateLocalHash();
  _wildcard_mask = 0;

  for (auto &c : _children) {
    // roll hash right (this avoids discarding information)
    std::size_t low_bit = _hash << (sizeof(std::size_t) * 8 - 1);
    _hash = (_hash >> 1) | low_bit;

    // update child hash
    c->updateHash(hash_set, hash_map);

    // XOR child hash onto node hash
    _hash ^= c->_hash;
    _wildcard_mask |= c->_wildcard_mask;
  }

  // add to hash set
  if (hash_set)
    hash_set->insert(_hash);

  // add to hash map
  if (hash_map)
    hash_map->insert(std::make_pair(_hash, this));
}

// compare subtrees without wild card matches
bool NodeBase::isSameTree(NodeBase *rhs) {
  // same hashes?
  if (_hash != rhs->hash())
    return false;

  // locally same?
  if (*this != *rhs)
    return false;

  // same number of children?
  const auto c_size = _children.size();
  if (c_size != rhs->children().size())
    return false;

  // all children are the same
  for (std::size_t i = 0; i < c_size; ++i)
    if (!_children[i]->isSameTree(rhs->children()[i]))
      return false;

  return true;
}

// compare with wildcard application
bool NodeBase::match(NodeBase *rhs, DecisionTreeNode *root) {
  // perform matching (no wildcard)
  if (_wildcard_mask == 0)
    return isSameTree(rhs);

  // is a permutation required
  // for all permutations
  // {
  //   auto * branch = new DecisionTreeNode
  //   root->append(branch)
  //   recurse into all children
  // }

  return false;
}

void NodeBase::unlinkChild(NodeBase *child) {
  auto it = std::find(_children.begin(), _children.end(), child);
  if (it != _children.end())
    _children.erase(it);
}

void NodeBase::linkChild(NodeBase *child) { _children.push_back(child); }

void NodeBase::addClonesToLeaves(NodeBase *child) {
  if (_children.empty())
    linkChild(child->clone());
  else {
    for (auto &c : _children)
      c->addClonesToLeaves(child);
  }
}

void NodeBase::prune() {
  if (_parent && _parent->children().size() == 1)
    _parent->prune();
  else
    delete this;
}

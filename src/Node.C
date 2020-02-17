#include "Node.h"

Node::Node() : NodeBase<Node>() {}

Node::Node(std::initializer_list<Node *> children) : NodeBase(children) {}

void Node::updateHash(
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
bool Node::isSameTree(Node *rhs) {
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
bool Node::match(Node *rhs, DecisionTreeNode *root) {
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

const std::size_t Node::_class_hash = typeid(Node).hash_code();

#include "DecisionTreeNode.h"
#include "WildcardNode.h"

#include <array>
#include <stdexcept>

WildcardNode::WildcardNode(WildcardID id) : Node(), _id(id) {
  if (id >= Node::MAX_ID)
    throw std::out_of_range("invalid wildcard ID");
}

void WildcardNode::printLocal() const { std::cout << "*[" << _id << ']'; }

void WildcardNode::updateLocalHash() {
  // hash the node specific data
  _hash = _class_hash ^ std::hash<unsigned char>{}(_id);
}

bool WildcardNode::operator==(const Node &rhs) const {
  // comparing two wild card nodes
  const auto ptr = dynamic_cast<const WildcardNode *>(&rhs);
  if (ptr)
    return (_id == ptr->_id);

  // attempting a match to an arbitrary node
  if (!restriction(rhs))
    return false;

  // go through decision tree
  return false;
}

bool WildcardNode::match(Node *rhs, DecisionTreeNode *root) {
  // look up if a mapping already exits
  DecisionTreeNode *i = root;
  while (i) {
    if (i->map()[_id]) {
      if (i->map()[_id]->isSameTree(rhs))
        return true;
      return false;
    }
    i = i->parent();
  }

  // no mapping exists. add it
  std::make_pair(_id, rhs);

  // this wildcard matches every node
  return true;
}

const std::size_t WildcardNode::_class_hash = typeid(WildcardNode).hash_code();

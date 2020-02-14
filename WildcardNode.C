#include "WildcardNode.h"
#include <stdexcept>

WildcardNode::WildcardNode(unsigned int id) : NodeBase(), _id(id) {
  if (id >= NodeBase::MAX_ID)
    throw std::out_of_range("invalid wildcard ID");
}

void WildcardNode::print(std::string indent) {
  std::cout << indent << "*[" << _id << "]\t[" << _hash << "]\n";
  for (auto &c : _children)
    c->print(indent + "  ");
}

void WildcardNode::updateLocalHash() {
  // hash the node specific data
  _hash = _class_hash ^ std::hash<unsigned char>{}(_id);
}

bool WildcardNode::operator==(const NodeBase &rhs) const {
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

const std::size_t WildcardNode::_class_hash = typeid(WildcardNode).hash_code();

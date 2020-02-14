#include "WildcardNode.h"

void WildcardNode::print(std::string indent) {
  std::cout << indent << "*[" << _id << "]\t[" << _hash << "]\n";
  for (auto &c : _children)
    c->print(indent + "  ");
}

void WildcardNode::updateLocalHash() {
  // hash the node specific data
  _hash = _class_hash ^ std::hash<unsigned char>{}(_id);
}

const std::size_t WildcardNode::_class_hash = typeid(WildcardNode).hash_code();

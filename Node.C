#include "Node.h"

Node::Node(std::string label, std::initializer_list<NodeBase *> children)
    : NodeBase(children), _label(label) {}

void Node::print(std::string indent) {
  std::cout << indent << '\'' << _label << "'\t[" << _hash << "]\n";
  for (auto &c : _children)
    c->print(indent + "  ");
}

void Node::updateLocalHash() {
  // hash the node specific data
  _hash = _class_hash ^ std::hash<std::string>{}(_label);
}

const std::size_t Node::_class_hash = typeid(Node).hash_code();

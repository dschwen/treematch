#include "Node.h"

Node::Node(std::string label) : NodeBase(), _label(label) {}

Node::Node(std::string label, std::initializer_list<NodeBase *> children)
    : NodeBase(children), _label(label) {}

void Node::printLocal() const {
  std::cout << '"' << _label << "\t[" << _hash << ']';
}

void Node::updateLocalHash() {
  // hash the node specific data
  _hash = _class_hash ^ std::hash<std::string>{}(_label);
}

bool Node::operator==(const NodeBase &rhs) const {
  const auto ptr = dynamic_cast<const Node *>(&rhs);
  return ptr && (_label == ptr->_label);
}

const std::size_t Node::_class_hash = typeid(Node).hash_code();

#include "SymNode.h"

SymNode::SymNode(std::string label) : Node(), _label(label) {}

SymNode::SymNode(std::string label, std::initializer_list<Node *> children)
    : Node(children), _label(label) {}

void SymNode::printLocal() const {
  std::cout << '"' << _label << "\t[" << _hash << ']';
}

void SymNode::updateLocalHash() {
  // hash the node specific data
  _hash = _class_hash ^ std::hash<std::string>{}(_label);
}

bool SymNode::operator==(const Node &rhs) const {
  const auto ptr = dynamic_cast<const SymNode *>(&rhs);
  return ptr && (_label == ptr->_label);
}

const std::size_t SymNode::_class_hash = typeid(SymNode).hash_code();

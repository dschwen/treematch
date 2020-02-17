#include "Node.h"

#pragma once

class SymNode : public Node {
public:
  SymNode(std::string label);
  SymNode(std::string label, std::initializer_list<Node *> children);

  // deep copy constructor
  SymNode(const SymNode *rhs) : Node(rhs), _label(rhs->_label) {}
  SymNode *clone() const override { return new SymNode(this); }

  const std::string &label() const { return _label; }

  void printLocal() const override;
  virtual void updateLocalHash();

  bool operator==(const Node &rhs) const override;

protected:
  std::string _label;

private:
  static const std::size_t _class_hash;
};

#include "NodeBase.h"

#pragma once

class Node : public NodeBase {
public:
  Node(std::string label);
  Node(std::string label, std::initializer_list<NodeBase *> children);

  // deep copy constructor
  Node(const Node *rhs) : NodeBase(rhs), _label(rhs->_label) {}
  Node *clone() const override { return new Node(this); }

  const std::string &label() const { return _label; }

  void printLocal() const override;
  void updateLocalHash() override;

  bool operator==(const NodeBase &rhs) const override;

protected:
  std::string _label;

private:
  static const std::size_t _class_hash;
};

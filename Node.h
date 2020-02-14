#include "NodeBase.h"

#pragma once

class Node : public NodeBase {
public:
  Node(std::string label) : NodeBase(), _label(label) {}
  Node(std::string label, std::initializer_list<NodeBase *> children);

  const std::string &label() const { return _label; }

  void print(std::string indent = "") override;

  void updateLocalHash() override;

protected:
  std::string _label;

private:
  static const std::size_t _class_hash;
};

#include "Node.h"
#include "NodeBase.h"

#pragma once

class DecisionTreeNode;

class DecisionTreeNode : public NodeBase<DecisionTreeNode> {
public:
  using WildcardMap = std::array<Node *, Node::MAX_ID>;

  // deep copy constructor
  DecisionTreeNode(const DecisionTreeNode *rhs)
      : NodeBase<DecisionTreeNode>(rhs), _map(rhs->_map) {}
  DecisionTreeNode *clone() const override {
    return new DecisionTreeNode(this);
  }

  void printLocal() const override {}

  const WildcardMap &map() const { return _map; }

  bool operator==(const DecisionTreeNode &rhs) const override { return false; }

protected:
  WildcardMap _map;
};

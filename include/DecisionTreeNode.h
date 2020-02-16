#include "NodeBase.h"

#pragma once

class DecisionTreeNode : public NodeBase {
public:
  using WildcardMap = std::array<NodeBase *, NodeBase::MAX_ID>;

  // deep copy constructor
  DecisionTreeNode(const DecisionTreeNode *rhs)
      : NodeBase(rhs), _map(rhs->_map) {}
  DecisionTreeNode *clone() const override {
    return new DecisionTreeNode(this);
  }

  void printLocal() const override {}
  void updateLocalHash() override {}

  const WildcardMap &map() const { return _map; }

  bool operator==(const NodeBase &rhs) const override { return false; }

protected:
  WildcardMap _map;
};

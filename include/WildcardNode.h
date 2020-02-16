#include "NodeBase.h"

#pragma once

class DecisionTreeNode;

class WildcardNode : public NodeBase {
public:
  // we'll make this private and add BackTrackMatch as a friend
  WildcardNode(WildcardID id);

  // deep copy constructor
  WildcardNode(const WildcardNode *rhs) : NodeBase(rhs), _id(rhs->_id) {}
  WildcardNode *clone() const override { return new WildcardNode(this); }

  void printLocal() const override;
  void updateLocalHash() override;

  bool operator==(const NodeBase &rhs) const override;

  bool match(NodeBase *rhs, DecisionTreeNode *root) override;

protected:
  /// this allows the implementation of derived restricted wildcards (e.g.
  /// integer, positive results etc.)
  virtual bool restriction(const NodeBase &rhs) const { return true; }

  WildcardID _id;

private:
  static const std::size_t _class_hash;
};

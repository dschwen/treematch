#include "NodeBase.h"

#pragma once

class WildcardNode : public NodeBase {
public:
  // we'll make this private and add BackTrackMatch as a friend
  WildcardNode(unsigned int id);

  void print(std::string indent = "") override;
  void updateLocalHash() override;

  bool operator==(const NodeBase &rhs) const override;

protected:
  /// this allows the implementation of derived restricted wildcards (e.g.
  /// integer, positive results etc.)
  virtual bool restriction(const NodeBase &rhs) const { return true; }

  unsigned int _id;

private:
  static const std::size_t _class_hash;
};

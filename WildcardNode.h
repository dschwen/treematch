#include "NodeBase.h"

#pragma once

class WildcardNode : public NodeBase {
public:
  WildcardNode(unsigned char id) : NodeBase(), _id(id) {}

  void print(std::string indent = "") override;

  void updateLocalHash() override;

protected:
  unsigned char _id;

private:
  static const std::size_t _class_hash;
};

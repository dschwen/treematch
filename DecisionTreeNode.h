#include "NodeBase.h"

#pragma once

class DecisionTreeNode : public NodeBase
{
protected:
  std::vector<std::pair<WildCardID, NodeBase *>> _map;
};

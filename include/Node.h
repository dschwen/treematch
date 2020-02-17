#include "NodeBase.h"
#include <unordered_map>

#pragma once

// Wildcard ID number type
using WildcardID = int;
/// fast bitmask type for wildcard occurence in subtrees
using WildcardMask = uint32_t;

class Node;
class DecisionTreeNode;

class Node : public NodeBase<Node> {
public:
  Node();
  Node(std::initializer_list<Node *> children);

  // deep copy constructor
  Node(const Node *rhs) : NodeBase<Node>(rhs), _wildcard_mask(0) {}

  const std::size_t &hash() const { return _hash; }

  /// update hash and wildcard mask in subtree
  void updateHash(
      std::set<std::size_t> *hash_set = nullptr,
      std::unordered_multimap<std::size_t, NodeBase *> *hash_map = nullptr);
  virtual void updateLocalHash() = 0;

  // compare subtrees without wild card matches
  bool isSameTree(Node *rhs);

  // compare with wildcard application
  virtual bool match(Node *rhs, DecisionTreeNode *dtree);

  // permit at most 32 different wildcards
  static constexpr unsigned char MAX_ID = 32;

protected:
  std::size_t _hash;
  WildcardMask _wildcard_mask;

private:
  static const std::size_t _class_hash;
};

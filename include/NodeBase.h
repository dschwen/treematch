#include <bitset>
#include <cstdint>
#include <functional>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

#pragma once

// Wildcard ID number type
using WildcardID = unsigned int;
/// fast bitmask type for wildcard occurence in subtrees
using WildcardMask = uint32_t;

class NodeBase;
class NodeBase {
public:
  NodeBase();
  NodeBase(std::initializer_list<NodeBase *> children);
  virtual ~NodeBase();

  const std::vector<NodeBase *> &children() const { return _children; }
  const std::size_t &hash() const { return _hash; }

  void print(std::string indent = "") const;
  virtual void printLocal() const = 0;
  virtual void updateLocalHash() = 0;

  void updateHash();
  void updateHash(std::set<std::size_t> &hash_set);
  void updateHash(std::unordered_multimap<std::size_t, NodeBase *> &hash_map);

  virtual bool operator==(const NodeBase &rhs) const = 0;
  bool operator!=(const NodeBase &rhs) const { return !(*this == rhs); };

  // compare subtrees without wild card matches
  bool isSameTree(NodeBase * rhs);

  // compare with wildcard application
  bool match(NodeBase * rhs/* , DecisionTreeNode * dtree */);

protected:
  std::vector<NodeBase *> _children;
  NodeBase *_parent;
  std::size_t _hash;

  WildcardMask _wildcard_mask;

  // permit at most 32 different wildcards
  static constexpr unsigned char MAX_ID = 32;
};

#include "NodeBase.h"

NodeBase::NodeBase(std::initializer_list<NodeBase *> children)
    : _children(children) {
  for (auto &c : _children)
    c->_parent = this;
}

NodeBase::~NodeBase() {
  for (auto &c : _children)
    delete c;
}

void NodeBase::updateHash() {
  // hash the node specific data
  updateLocalHash();

  for (auto &c : _children) {
    // roll hash right (this avoids discarding information)
    std::size_t low_bit = _hash << (sizeof(std::size_t) * 8 - 1);
    _hash = (_hash >> 1) | low_bit;

    // update child hash
    c->updateHash();

    // XOR child hash onto node hash
    _hash ^= c->_hash;
  }
}

void NodeBase::updateHash(std::set<std::size_t> &hash_set) {
  // hash the node specific data
  updateLocalHash();

  for (auto &c : _children) {
    // roll hash right (this avoids discarding information)
    std::size_t low_bit = _hash << (sizeof(std::size_t) * 8 - 1);
    _hash = (_hash >> 1) | low_bit;

    // update child hash
    c->updateHash(hash_set);

    // XOR child hash onto node hash
    _hash ^= c->_hash;
  }

  // add to hash set
  hash_set.insert(_hash);
}

void NodeBase::updateHash(
    std::unordered_multimap<std::size_t, NodeBase *> &hash_map) {
  // hash the node specific data
  updateLocalHash();

  for (auto &c : _children) {
    // roll hash right (this avoids discarding information)
    std::size_t low_bit = _hash << (sizeof(std::size_t) * 8 - 1);
    _hash = (_hash >> 1) | low_bit;

    // update child hash
    c->updateHash(hash_map);

    // XOR child hash onto node hash
    _hash ^= c->_hash;
  }

  // add to hash set
  hash_map.insert(std::make_pair(_hash, this));
}

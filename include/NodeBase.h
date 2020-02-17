#include <algorithm>
#include <bitset>
#include <cstdint>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

#pragma once

// Curiously Recurring Template Pattern (CRTP)
template <class T> class NodeBase {
public:
  NodeBase();
  NodeBase(std::initializer_list<T *> children);

  // deep copy constructor
  NodeBase(const T *rhs);

  virtual ~NodeBase();

  virtual T *clone() const = 0;

  const std::vector<T *> &children() const { return _children; }

  T *parent() { return _parent; }
  const T *parent() const { return _parent; }

  void print(std::string indent = "") const;
  virtual void printLocal() const = 0;

  virtual bool operator==(const T &rhs) const = 0;
  bool operator!=(const T &rhs) const { return !(*this == rhs); };

  /// remove given node from the list of child nodes
  void unlinkChild(T *child);

  /// add a child
  void linkChild(T *child);

  /// append clones leaves
  void addClonesToLeaves(T *child);

  /// remove branch (including all parents this branch is the only child of)
  void prune();

protected:
  std::vector<T *> _children;
  T *_parent;
  bool _dying;
};

template <typename T> NodeBase<T>::NodeBase() : _dying(false) {}

template <typename T>
NodeBase<T>::NodeBase(std::initializer_list<T *> children)
    : _children(children), _dying(false) {
  for (auto &c : _children)
    c->_parent = static_cast<T *>(this);
}

template <typename T> NodeBase<T>::NodeBase(const T *rhs) {
  _dying = rhs->_dying;
  for (auto &c : _children) {
    auto n = c->clone();
    n->_parent = static_cast<T *>(this);
    _children.push_back(n);
  }
}

template <typename T> NodeBase<T>::~NodeBase() {
  // going into teardown state
  _dying = true;

  // delete all children
  for (auto &c : _children)
    delete c;

  // if the parent is not in teardown mode remove self from list of children,
  // otherwise it is both unnecessary and will invalidate teh iterator in the
  // loop directly above.
  if (_parent && !_parent->_dying)
    _parent->unlinkChild(static_cast<T *>(this));
}

template <typename T> void NodeBase<T>::print(std::string indent) const {
  std::cout << indent;
  printLocal();
  std::cout << '\n';

  for (auto &c : _children)
    c->print(indent + "  ");
}

template <typename T> void NodeBase<T>::unlinkChild(T *child) {
  auto it = std::find(_children.begin(), _children.end(), child);
  if (it != _children.end())
    _children.erase(it);
}

template <typename T> void NodeBase<T>::linkChild(T *child) {
  _children.push_back(child);
}

template <typename T> void NodeBase<T>::addClonesToLeaves(T *child) {
  if (_children.empty())
    linkChild(child->clone());
  else {
    for (auto &c : _children)
      c->addClonesToLeaves(child);
  }
}

template <typename T> void NodeBase<T>::prune() {
  if (_parent && _parent->children().size() == 1)
    _parent->prune();
  else
    delete this;
}

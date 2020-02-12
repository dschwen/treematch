#include <initializer_list>
#include <iostream>
#include <vector>

class Node;
class Node {
public:
  Node(std::string label) : _label(label) {}
  Node(std::string label, std::initializer_list<Node *> children)
      : _children(children), _label(label) {}
  ~Node() {
    for (auto &c : _children)
      delete c;
  }
  const std::vector<Node *> &children() const { return _children; }
  const std::string &label() const { return _label; }

  void print(std::string indent = "") {
    std::cout << indent << _label << '\n';
    for (auto &c : _children)
      c->print(indent + "  ");
  }

protected:
  std::vector<Node *> _children;
  std::string _label;
};

// compare two sub trees
bool same(Node *a, Node *b) {
  // same label?
  if (a->label() != b->label())
    return false;

  // same number of children?
  const auto a_size = a->children().size();
  if (a_size != b->children().size())
    return false;

  // all children are the same
  for (std::size_t i = 0; i < a_size; ++i)
    if (!same(a->children()[i], b->children()[i]))
      return false;

  return true;
}

// backtrack chain link
class BackTrackLink;
class BackTrackLink {
public:
  using DataType = std::pair<std::string, Node *>;

  BackTrackLink(BackTrackLink *parent, DataType data)
      : _parent(parent), _data(data) {}

  DataType _data;
  BackTrackLink *_parent;
};

// does the chain contain the given pointer (i.e. is a node already consumed as
// a match?)
bool containsNode(BackTrackLink *chain, Node *node) {
  if (!chain)
    return false;

  if (chain->_data.second == node)
    return true;

  return containsNode(chain->_parent, node);
}

// delete chain starting at tip
void deleteChain(BackTrackLink *chain) {
  if (!chain)
    return;

  deleteChain(chain->_parent);
  delete chain;
}

struct TreeNode {
  const Node *_self;
  const Node *_parent;
  std::size_t _size;
};

// preprocessed tree wrapper for a raw node structure
class Tree {
public:
  Tree(Node *root);

  void print();

protected:
  std::size_t traverse(const Node *self, const Node *parent);

  std::vector<TreeNode> _serialized;
  const Node *_root;
};

Tree::Tree(Node *root) : _root(root) { traverse(_root, nullptr); }

void Tree::print() {
  for (auto item : _serialized)
    std::cout << item._self->label() << '\t'
              << (item._parent ? item._parent->label() : "[NULL]") << '\t'
              << item._size << '\n';
}

std::size_t Tree::traverse(const Node *self, const Node *parent) {
  // get the current index
  auto idx = _serialized.size();

  // add self and parent
  TreeNode me;
  me._self = self;
  me._parent = parent;

  // push into the serialized vector (at position idx)
  _serialized.push_back(me);

  // recurse into children
  std::size_t size = 1;
  for (auto c : self->children())
    size += traverse(c, self);

  // update size
  _serialized[idx]._size = size;

  return size;
}

// backtracking tree match
class BackTrackMatch {
public:
  BackTrackMatch(const Tree &pattern, const Tree &target)
      : _pattern(pattern), _target(target) {}
  bool run();

protected:
  BackTrackLink *decide(BackTrackLink *);
  const Tree &_pattern;
  const Tree &_target;

  std::size_t _p_idx;
  std::size_t _t_idx;
};

// user facing API to match a patetrn to a target
bool BackTrackMatch::run() {
  // set pattern and target pointers target and
  return true;
}

// backtracking algorithm (recursive function)
BackTrackLink *BackTrackMatch::decide(BackTrackLink *chain) {
  // if we are at a wild card in the pattern tree try all possible matches

  // for all potential matches
  {
    auto match =
        new BackTrackLink(chain, BackTrackLink::DataType("label", nullptr));
    auto result = decide(match);

    // backtrack propagates the tip of the link chain if a successful match
    // was made
    if (result)
      // successful match was found all the way through
      return result;

    // otherwise we discard the attempted match and try the next possible
    // match
    delete match;
  }

  return nullptr;
}

// entry point
int main() {
  // raw tree
  auto root =
      new Node("+", {new Node("^2", {new Node("sin", {new Node("a")})}),
                     new Node("^2", {new Node("cos", {new Node("a")})})});
  root->print();
  std::cout << '\n';

  // processed tree
  Tree tree(root);
  tree.print();

  return 0;
}

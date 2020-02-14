
#include "Node.h"
#include "WildcardNode.h"

// compare two sub trees without wildcards!
bool same(Node *a, Node *b) {
  // same hashes?
  if (a->hash() != b->hash())
    return false;

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

// backtracking tree match
class BackTrackMatch {
public:
  BackTrackMatch(const Node *pattern, const Node *target)
      : _pattern(pattern), _target(target) {}
  bool run();

protected:
  BackTrackLink *decide(BackTrackLink *);
  const Node *const _pattern;
  const Node *const _target;

  const Node *_p_it;
  const Node *_t_it;
};

// user facing API to match a patetrn to a target
bool BackTrackMatch::run() {
  // set pattern and target pointers target and
  _p_it = _pattern;
  _t_it = _target;

  auto result = decide(nullptr);

  return result != nullptr;
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
  auto pattern =
      new Node("+", {new WildcardNode("[*A]"), new WildcardNode("[*A]")});

  auto replace = new Node("*", {new Node("2"), new WildcardNode("[*A]")});

  auto target = new Node("+", {new Node("sin", {new Node("x")}),
                               new Node("sin", {new Node("x")})});

  pattern->updateHash();
  pattern->print();
  std::cout << '\n';

  replace->updateHash();
  replace->print();
  std::cout << '\n';

  target->updateHash();
  target->print();
  std::cout << '\n';

  return 0;
}

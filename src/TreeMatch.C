#include "SymNode.h"
#include "WildcardNode.h"

// entry point
int main() {
  // raw tree
  auto pattern = new SymNode("+", {new WildcardNode(0), new WildcardNode(0)});

  auto replace = new SymNode("*", {new SymNode("2"), new WildcardNode(0)});

  auto target = new SymNode("+", {new SymNode("sin", {new SymNode("x")}),
                                  new SymNode("sin", {new SymNode("x")})});

  auto leaf = new SymNode("x");
  auto test =
      new SymNode("+", {new SymNode("sin", {new SymNode("x")}),
                        new SymNode("sin", {new SymNode("log", {leaf})})});
  test->updateHash();
  test->print();
  std::cout << '\n';

  leaf->prune();

  // test->updateHash();
  test->print();
  std::cout << '\n';

  // pattern->updateHash();
  // pattern->print();
  // std::cout << '\n';
  //
  // replace->updateHash();
  // replace->print();
  // std::cout << '\n';
  //
  // target->updateHash();
  // target->print();
  // std::cout << '\n';

  return 0;
}

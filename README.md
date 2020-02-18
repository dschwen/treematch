# treematch [![Build Status](https://travis-ci.org/dschwen/treematch.svg?branch=master)](https://travis-ci.org/dschwen/treematch)

## Goal

Matching a pattern in the form of a small tree containing (named) wildcard and
catch-all nodes to a position inside a bigger target tree.

This problem can be simplified to matching a sub-tree root to a specific node in
the target tree.

Named wildcards may appear multiple times in the pattern and must match to
identical sub-trees. E.g. `(+ (*[1], *[1] )) -> (* (2, *[1]))` would match the
sum of two identical terms (represented by arbitrarily large sub-trees). The `->`
syntax indicates a substitution to be performed on the sub-tree.

This task would be trivial for for trees with a fixed child order. However in
sub-trees representing mathematical expressions the commutative property of the
`+` and `*` operators requires multiple matching attempts against permutations
of the child node vector. Each permutation represents a fork in the decision
tree in which matches are assigned to wildcard elements.

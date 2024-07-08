//oriyai0701@gmail.com

# TreesIterators

## Overview

This project implements a tree data structure (`Tree`) in C++ with various iterators (`pre_order`, `post_order`, `in_order`, `bfs_scan`, `dfs_scan`, `heap`) and demonstrates their usage through unit tests using the `doctest` framework.

## Classes

### Tree Class

The `Tree` class is a templated implementation of a k-ary tree, where:
- `T` is the type of data stored in each node.
- `D` is the degree of the tree (default is 2).

#### Methods

- **add_root**: Adds a root node to the tree.
- **add_sub_node**: Adds a child node under a given parent node.
- **begin_pre_order, end_pre_order**: Returns iterators for pre-order traversal.
- **begin_post_order, end_post_order**: Returns iterators for post-order traversal.
- **begin_in_order, end_in_order**: Returns iterators for in-order traversal.
- **begin_bfs_scan, end_bfs_scan**: Returns iterators for breadth-first search (BFS) traversal.
- **begin_dfs_scan, end_dfs_scan**: Returns iterators for depth-first search (DFS) traversal.
- **begin_heap, end_heap**: Returns iterators for heap traversal.

### Other Classes (if applicable)

- **Complex**: (Brief description if applicable)

## Usage

To use the `Tree` class and iterators:
1. Include `"Tree.hpp"` in your source files.
2. Instantiate `Tree` with the desired data type and optionally the degree `D`.
3. Use the provided methods to manipulate the tree structure and iterate through nodes.

## Unit Tests

Unit tests are implemented using the `doctest` framework to validate the functionality of `Tree` and its iterators. Each test case checks specific functionalities such as adding nodes, iterating through the tree in different orders, and validating heap properties.

### Running Tests

To run the tests:
1. Compile your project with `doctest` included.
2. Execute the compiled executable to run the tests.
3. Check the console output for test results.

## Dependencies

- **SFML**: Required for GUI functionalities if applicable.

## Example

```cpp
#include "Tree.hpp"
#include <iostream>

int main() {
    // Example usage of Tree class
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);

    // Example iteration
    std::cout << "Pre-order traversal:";
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        std::cout << " " << (*it)->key;
    }
    std::cout << std::endl;

    return 0;
}

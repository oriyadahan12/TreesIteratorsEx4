//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//oriyai0701@gmail.com

#include "doctest.h"
#include <iostream>
#include <vector>
#include <algorithm> // For std::is_sorted
//#include "Tree.hpp"
#include "GUI.hpp"

TEST_CASE("Test add_root") {
    Tree<int, 2> tree;
    tree.add_root(1);

    CHECK(tree.get_root()->key == 1);

    // Test that adding another root throws an error
    CHECK_THROWS_AS(tree.add_root(2), std::invalid_argument);
}

TEST_CASE("Test add_sub_node") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    tree.add_sub_node(2, 4);
    tree.add_sub_node(2, 5);

    CHECK(tree.get_root()->children.size() == 2);
    CHECK(tree.get_root()->children[0]->key == 2);
    CHECK(tree.get_root()->children[1]->key == 3);
    CHECK(tree.get_root()->children[0]->children[0]->key == 4);
    CHECK(tree.get_root()->children[0]->children[1]->key == 5);

    // Test adding sub-node to non-existent parent throws an error
    CHECK_THROWS_AS(tree.add_sub_node(6, 7), std::logic_error);
}

TEST_CASE("Test pre_order_iterator") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    tree.add_sub_node(2, 4);
    tree.add_sub_node(2, 5);

    std::vector<int> keys;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        keys.push_back((*it)->key);
        std::cout << (*it)->key << "  ";
    }

    std::vector<int> expected = {1, 2, 4, 5, 3};
    CHECK(keys == expected);
}

TEST_CASE("Test post_order_iterator") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    tree.add_sub_node(2, 4);
    tree.add_sub_node(2, 5);

    std::vector<int> keys;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        keys.push_back((*it)->key);
    }

    std::vector<int> expected = {4, 5, 2, 3, 1};
    CHECK(keys == expected);
}

TEST_CASE("Test in_order_iterator") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);

    std::vector<int> keys;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        keys.push_back((*it)->key);
    }

    std::vector<int> expected = {2, 1, 3};
    CHECK(keys == expected);
}

TEST_CASE("Test bfs_iterator") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    tree.add_sub_node(2, 4);
    tree.add_sub_node(2, 5);

    std::vector<int> keys;
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        keys.push_back((*it)->key);
    }

    std::vector<int> expected = {1, 2, 3, 4, 5};
    CHECK(keys == expected);
}

TEST_CASE("Test dfs_iterator") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    tree.add_sub_node(2, 4);
    tree.add_sub_node(2, 5);

    std::vector<int> keys;
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
        keys.push_back((*it)->key);
    }

    std::vector<int> expected = {1, 2, 4, 5, 3};
    CHECK(keys == expected);
}

TEST_CASE("Test heap") {
    Tree<int, 2> tree;
    tree.add_root(5);
    tree.add_sub_node(5, 3);
    tree.add_sub_node(5, 4);
    tree.add_sub_node(3, 2);
    tree.add_sub_node(3, 1);

    std::vector<int> keys;
    for (auto it = tree.begin_heap(); it != tree.end_heap(); ++it) {
        keys.push_back((*it)->key);
    }

    std::vector<int> expected = {1, 2, 4 ,5, 3};
    for(auto &each: keys){
        std::cout << each << "/n key  ";
    }
    GUI<int> gui(tree);
    gui.run();
    CHECK(keys == expected);
}

TEST_CASE("Adding_root_to_empty_tree_sets_root_correctly") {
    Tree<int, 2> tree;
    tree.add_root(10);
    CHECK(tree.get_root()->key == 10);
}

TEST_CASE("Adding_root_to_non_empty_tree_updates_root") {
    Tree<int, 2> tree;
    tree.add_root(1);
    CHECK_THROWS(tree.add_root(2) );
    CHECK(tree.get_root()->key == 1);

}

TEST_CASE("Adding_sub_node_increases_children_count") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    CHECK(tree.get_root()->children.size() == 1);
}

TEST_CASE("Adding_sub_node_to_non_existent_parent_throws_error") {
    Tree<int, 2> tree;
    tree.add_root(1);
    CHECK_THROWS_AS(tree.add_sub_node(3, 2), std::logic_error);
}

TEST_CASE("Pre_order_iterator_traverses_in_pre_order") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    std::vector<int> traversal;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        traversal.push_back((*it)->key);
    }
    std::vector<int> expected = {1, 2, 3};
    CHECK(traversal == expected);
}

TEST_CASE("Post_order_iterator_traverses_in_post_order") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    std::vector<int> traversal;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        traversal.push_back((*it)->key);
    }
    std::vector<int> expected = {2, 3, 1};
    CHECK(traversal == expected);
}

TEST_CASE("In_order_iterator_traverses_in_in_order_for_binary_tree") {
    Tree<int, 2> tree;
    tree.add_root(2);
    tree.add_sub_node(2, 1);
    tree.add_sub_node(2, 3);
    std::vector<int> traversal;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        traversal.push_back((*it)->key);
    }
    std::vector<int> expected = {1, 2, 3};
    CHECK(traversal == expected);
}

TEST_CASE("BFS_iterator_traverses_in_level_order") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(1, 3);
    std::vector<int> traversal;
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        traversal.push_back((*it)->key);
    }
    std::vector<int> expected = {1, 2, 3};
    CHECK(traversal == expected);
}

TEST_CASE("DFS_iterator_traverses_in_depth_first_order") {
    Tree<int, 2> tree;
    tree.add_root(1);
    tree.add_sub_node(1, 2);
    tree.add_sub_node(2, 3);
    std::vector<int> traversal;
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
        traversal.push_back((*it)->key);
    }
    std::vector<int> expected = {1, 2, 3};
    CHECK(traversal == expected);
}

TEST_CASE("Heap_iterator_traverses_in_heap_order") {
    Tree<int, 2> tree;
    tree.add_root(5);
    tree.add_sub_node(5, 3);
    tree.add_sub_node(5, 4);
    std::vector<int> traversal;
    for (auto it = tree.begin_heap(); it != tree.end_heap(); ++it) {
        traversal.push_back((*it)->key);
    }
    std::vector<int> expected = {3, 5, 4}; // Assuming min-heap for demonstration
    CHECK(traversal == expected);
}

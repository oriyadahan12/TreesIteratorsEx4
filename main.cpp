//oriyati0701@gmail.com

#include <SFML/Graphics.hpp>
#include <iostream>
#include "GUI.hpp"



int main() {


    Tree<Complex> tree;

    // Add root and some nodes to the tree
    tree.add_root(Complex(5, 5));
    tree.add_sub_node(Complex(5, 5), Complex(3, 3));
    tree.add_sub_node(Complex(5, 5), Complex(8, 8));
    tree.add_sub_node(Complex(3, 3), Complex(2, 2));
    tree.add_sub_node(Complex(3, 3), Complex(4, 4));
    tree.add_sub_node(Complex(8, 8), Complex(7, 7));
    tree.add_sub_node(Complex(8, 8), Complex(9, 9));

    // Pre-Order Traversal
    std::cout << "Pre-Order Traversal: ";
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        std::cout << (*it)->key << " ";
    }
    std::cout << std::endl;

    // Post-Order Traversal
    std::cout << "Post-Order Traversal: ";
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        std::cout << (*it)->key << " ";
    }
    std::cout << std::endl;

    // In-Order Traversal
    std::cout << "In-Order Traversal: ";
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        std::cout << (*it)->key << " ";
    }
    std::cout << std::endl;

    // BFS Traversal
    std::cout << "BFS Traversal: ";
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        std::cout << (*it)->key << " ";
    }
    std::cout << std::endl;

    // DFS Traversal
    std::cout << "DFS Traversal: ";
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
        std::cout << (*it)->key << " ";
    }
    std::cout << std::endl;

    // Convert the tree to a min-heap and traverse it
    std::cout << "Heap Traversal: ";
//    tree.myHeap();
    for (auto it = tree.begin_heap(); it != tree.end_heap(); ++it) {
        std::cout << (*it)->key << " ";
    }
    std::cout << std::endl;

    GUI<Complex> gui(tree);
    gui.run();

    tree.myHeap();
    GUI<Complex> gui1(tree);
    gui1.run();

    Tree<std::string,3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root("a");
    three_ary_tree.add_sub_node("a", "b");
    three_ary_tree.add_sub_node("a", "c");
    three_ary_tree.add_sub_node("a", "d");
    three_ary_tree.add_sub_node("b", "e");
    three_ary_tree.add_sub_node("c", "f");

    GUI<std::string, 3> gui2(three_ary_tree);
//    gui2.run();


    return 0;
}

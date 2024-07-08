//oriyati0701@gmail.com

#include <vector>
#include <memory>
#include <queue>
#include <functional> // For std::greater
#include <algorithm> // For std::make_heap, std::sort_heap
#include <stdexcept>
#include <stack> // Include stack header

/**
 * @brief A templated tree class with D-ary tree structure and various traversal iterators.
 *
 * @tparam T The type of the elements stored in the tree.
 * @tparam D The degree of the tree, default is 2 (binary tree).
 */
template<typename T, unsigned int D = 2>
class Tree {
public:
    /**
     * @brief A struct representing a node in the tree.
     */
    struct Node {
        T key;  ///< The key or value stored in the node.
        std::vector<std::shared_ptr<Node>> children;  ///< The children nodes of this node.

        /**
         * @brief Construct a new Node object.
         *
         * @param key The value to be stored in the node.
         */
        Node(T key) : key(key) {}
    };

/**
 * @brief Helper function to convert the tree into a min-heap.
 */
void myHeap() {
    std::vector<T> values;
    for (auto it = begin_bfs_scan(); it != end_bfs_scan(); ++it) {
        values.push_back((*it)->key);
    }
    std::make_heap(values.begin(), values.end(), std::greater<T>());
    root = nullptr;
    add_root(values.front());

    for (unsigned int i = 1; i < values.size(); i++) {
        add_sub_node(values[(i-1)/2], values[i]);
    }
}

private:
    std::shared_ptr<Node> root;  ///< The root node of the tree.

public:
    /**
     * @brief Get the root node.
     *
     * @return Node* Pointer to the root node.
     */
    Node* get_root() {
        return root.get();
    }

    /**
     * @brief Add a root node to the tree.
     *
     * @param key The value to be stored in the root node.
     * @throws std::invalid_argument If the root already exists.
     */
    void add_root(T key) {
        if (root) {
            throw std::invalid_argument("Root already exists.");
        }
        root = std::make_shared<Node>(key);
    }

    /**
     * @brief Add a sub node to a parent node identified by its value.
     *
     * @param parent The value of the parent node.
     * @param key The value to be stored in the new sub node.
     * @throws std::logic_error If the parent node is not found.
     */
    void add_sub_node(T parent, T key) {
        for (auto it = begin_bfs_scan(); it != end_bfs_scan(); ++it) {
            if ((*it)->key == parent) {
                (*it)->children.push_back(std::make_shared<Node>(key));
                return;
            }
        }
        throw std::logic_error("Parent not found.");
    }

    /**
     * @brief Base class for different types of tree iterators.
     */
    class Iterator {
    protected:
        std::vector<std::shared_ptr<Node>> nodes;  ///< Vector of nodes to iterate over.

    public:
        /**
         * @brief Advance the iterator to the next element.
         *
         * @return Iterator& Reference to the current iterator.
         */
        virtual Iterator &operator++() {
            if (!nodes.empty()) {
                nodes.erase(nodes.begin());
            }
            return *this;
        }

        /**
         * @brief Check if two iterators are not equal.
         *
         * @param other Another iterator to compare with.
         * @return true If the iterators are not equal.
         * @return false If the iterators are equal.
         */
        virtual bool operator!=(const Iterator &other) const {
            return !nodes.empty() || !other.nodes.empty();
        }

        /**
         * @brief Dereference the iterator to get the current node.
         *
         * @return std::shared_ptr<Node> The current node.
         */
        std::shared_ptr<Node> operator*() const {
            return nodes.front();
        }
    };

    /**
     * @brief Iterator for pre-order traversal.
     */
    class PreOrderIterator : public Iterator {
    public:
        /**
         * @brief Construct a new PreOrderIterator object.
         *
         * @param root The root node to start the traversal from.
         */
        PreOrderIterator(std::shared_ptr<Node> root) {
            if (root)
                preorder(root);
        }

    private:
        /**
         * @brief Helper function to perform pre-order traversal.
         *
         * @param node The current node in the traversal.
         */
        void preorder(std::shared_ptr<Node> node) {
            this->nodes.push_back(node);
            for (auto child : node->children) {
                preorder(child);
            }
        }
    };

    /**
     * @brief Get an iterator to the beginning of the pre-order traversal.
     *
     * @return PreOrderIterator The beginning iterator.
     */
    PreOrderIterator begin_pre_order() const {
        return PreOrderIterator(root);
    }

    /**
     * @brief Get an iterator to the end of the pre-order traversal.
     *
     * @return PreOrderIterator The end iterator.
     */
    PreOrderIterator end_pre_order() const {
        return PreOrderIterator(nullptr);
    }

    /**
     * @brief Iterator for post-order traversal.
     */
    class PostOrderIterator : public Iterator {
    public:
        /**
         * @brief Construct a new PostOrderIterator object.
         *
         * @param root The root node to start the traversal from.
         */
        PostOrderIterator(std::shared_ptr<Node> root) {
            if (root)
                postorder(root);
        }

    private:
        /**
         * @brief Helper function to perform post-order traversal.
         *
         * @param node The current node in the traversal.
         */
        void postorder(std::shared_ptr<Node> node) {
            for (auto child : node->children) {
                postorder(child);
            }
            this->nodes.push_back(node);
        }
    };

    /**
     * @brief Get an iterator to the beginning of the post-order traversal.
     *
     * @return PostOrderIterator The beginning iterator.
     */
    PostOrderIterator begin_post_order() const {
        return PostOrderIterator(root);
    }

    /**
     * @brief Get an iterator to the end of the post-order traversal.
     *
     * @return PostOrderIterator The end iterator.
     */
    PostOrderIterator end_post_order() const {
        return PostOrderIterator(nullptr);
    }

    /**
     * @brief Iterator for in-order traversal.
     */
    class InOrderIterator : public Iterator {
    public:
        /**
         * @brief Construct a new InOrderIterator object.
         *
         * @param root The root node to start the traversal from.
         */
        InOrderIterator(std::shared_ptr<Node> root) {
            if (root)
                inorder(root);
        }

    private:
        /**
         * @brief Helper function to perform in-order traversal.
         *
         * @param node The current node in the traversal.
         */
        void inorder(std::shared_ptr<Node> node) {
            if (D == 2) {
                inorder_binary(node);
            } else {
                dfs(node);
            }
        }

        /**
         * @brief Helper function to perform in-order traversal for binary trees.
         *
         * @param node The current node in the traversal.
         */
        void inorder_binary(std::shared_ptr<Node> node) {
            if (node->children.size() > 0) {
                inorder_binary(node->children[0]); // left child
            }
            this->nodes.push_back(node); // current node
            if (node->children.size() > 1) {
                inorder_binary(node->children[1]); // right child
            }
        }

        /**
         * @brief Helper function to perform depth-first traversal for non-binary trees.
         *
         * @param node The current node in the traversal.
         */
        void dfs(std::shared_ptr<Node> node) {
            this->nodes.push_back(node);
            for (auto child : node->children) {
                dfs(child);
            }
        }
    };

    /**
     * @brief Get an iterator to the beginning of the in-order traversal.
     *
     * @return InOrderIterator The beginning iterator.
     */
    InOrderIterator begin_in_order() const {
        return InOrderIterator(root);
    }

    /**
     * @brief Get an iterator to the end of the in-order traversal.
     *
     * @return InOrderIterator The end iterator.
     */
    InOrderIterator end_in_order() const {
        return InOrderIterator(nullptr);
    }

    /**
     * @brief Iterator for breadth-first traversal.
     */
    class BFSIterator : public Iterator {
    public:
        /**
         * @brief Construct a new BFSIterator object.
         *
         * @param root The root node to start the traversal from.
         */
        BFSIterator(std::shared_ptr<Node> root) {
            if (root)
                bfs(root);
        }

    private:
        /**
         * @brief Helper function to perform breadth-first traversal.
         *
         * @param root The current node in the traversal.
         */
        void bfs(std::shared_ptr<Node> root) {
            std::queue<std::shared_ptr<Node>> queue;
            queue.push(root);
            while (!queue.empty()) {
                auto node = queue.front();
                queue.pop();
                this->nodes.push_back(node);
                for (auto &child : node->children) {
                    queue.push(child);
                }
            }
        }
    };

    /**
     * @brief Get an iterator to the beginning of the breadth-first traversal.
     *
     * @return BFSIterator The beginning iterator.
     */
    BFSIterator begin_bfs_scan() const {
        return BFSIterator(root);
    }

    /**
     * @brief Get an iterator to the end of the breadth-first traversal.
     *
     * @return BFSIterator The end iterator.
     */
    BFSIterator end_bfs_scan() const {
        return BFSIterator(nullptr);
    }

    /**
     * @brief Iterator for depth-first traversal.
     */
    class DFSIterator : public Iterator {
    public:
        /**
         * @brief Construct a new DFSIterator object.
         *
         * @param root The root node to start the traversal from.
         */
        DFSIterator(std::shared_ptr<Node> root) {
            if (root)
                dfs(root);
        }

    private:
        /**
         * @brief Helper function to perform depth-first traversal.
         *
         * @param root The current node in the traversal.
         */
        void dfs(std::shared_ptr<Node> root) {
            std::stack<std::shared_ptr<Node>> stack;
            stack.push(root);
            while (!stack.empty()) {
                auto node = stack.top();
                stack.pop();
                this->nodes.push_back(node);
                // Push children in reverse order to maintain the correct order
                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                    stack.push(*it);
                }
            }
        }
    };

    /**
     * @brief Get an iterator to the beginning of the depth-first traversal.
     *
     * @return DFSIterator The beginning iterator.
     */
    DFSIterator begin_dfs_scan() const {
        return DFSIterator(root);
    }

    /**
     * @brief Get an iterator to the end of the depth-first traversal.
     *
     * @return DFSIterator The end iterator.
     */
    DFSIterator end_dfs_scan() const {
        return DFSIterator(nullptr);
    }

    /**
     * @brief Iterator for heap traversal.
     */
    class HeapIterator : public Iterator {
    public:
        /**
         * @brief Construct a new HeapIterator object.
         *
         * @param root The root node to start the traversal from.
         */
        HeapIterator(std::shared_ptr<Node> root) {
            if (root)
                bfs(root);
        }

    private:
        /**
         * @brief Helper function to perform breadth-first traversal for heap conversion.
         *
         * @param root The current node in the traversal.
         */
        void bfs(std::shared_ptr<Node> root) {
            std::queue<std::shared_ptr<Node>> queue;
            queue.push(root);
            while (!queue.empty()) {
                auto node = queue.front();
                queue.pop();
                this->nodes.push_back(node);
                for (auto &child : node->children) {
                    queue.push(child);
                }
            }
        }
    };

    /**
     * @brief Get an iterator to the beginning of the heap traversal.
     *
     * @return HeapIterator The beginning iterator.
     */
    HeapIterator begin_heap() {
        myHeap();
        return HeapIterator(root);
    }

    /**
     * @brief Get an iterator to the end of the heap traversal.
     *
     * @return HeapIterator The end iterator.
     */
    HeapIterator end_heap() {
        return HeapIterator(nullptr);
    }

};

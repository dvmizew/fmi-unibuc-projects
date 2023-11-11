#include <iostream>

// Using binary search trees, implement the intersection of two multisets.
// Each multiset is a binary search tree, and the result is a new binary search tree
// containing the elements from the intersection. O(n log n) 4a 2b 7c ∩ 2a 4b 3c = 2a 2b 3c -> take the minimum.

struct Node {
    int data;
    Node *left, *right;
};

struct BinaryTree {
    Node *root;

    BinaryTree() {
        root = nullptr;
    }

    void insertElement(int x) {
        Node *newNode = new Node;
        newNode->data = x;
        newNode->left = nullptr;
        newNode->right = nullptr;
        if (root == nullptr) {
            root = newNode;
            return;
        }
        Node *prevPointer = nullptr;
        Node *pointer = root;
        int direction = 0;
        while (pointer != nullptr) {
            prevPointer = pointer;
            if (x <= pointer->data) {
                pointer = pointer->left;
                direction = -1;
            } else {
                pointer = pointer->right;
                direction = 1;
            }
        }

        if (direction < 0)
            prevPointer->left = newNode;
        else
            prevPointer->right = newNode;
    }

    void deleteElement(int x) {
        Node *prevPointer = nullptr;
        Node *pointer = root;
        int direction = 0;
        while (pointer != nullptr && pointer->data != x) {
            prevPointer = pointer;
            if (x <= pointer->data) {
                pointer = pointer->left;
                direction = -1;
            } else {
                pointer = pointer->right;
                direction = 1;
            }
        }
        if (pointer == nullptr) {
            std::cout << "Does not exist " << x << std::endl;
            return;
        }
        if (pointer->left == nullptr && pointer->right == nullptr) {
            std::cout << "Doesn't have children " << x << std::endl;
            if (pointer == root) {
                std::cout << "It's the root" << x << std::endl;
                root = nullptr;
                delete pointer;
                return;
            }
            if (direction < 0)
                prevPointer->left = nullptr;
            else
                prevPointer->right = nullptr;
            delete pointer;
            return;
        }
        // If it has only a left child
        if (pointer->left != nullptr && pointer->right == nullptr) {
            std::cout << "It has only a left child " << x << std::endl;
            if (pointer == root) {
                std::cout << "It's the root " << x << std::endl;
                root = pointer->left;
                delete pointer;
                return;
            }
            if (direction < 0)
                prevPointer->left = pointer->left;
            else
                prevPointer->right = pointer->left;
            delete pointer;
            return;
        }
        // If it has only a right child
        if (pointer->left == nullptr && pointer->right != nullptr) {
            std::cout << "It has only a right child " << x << std::endl;
            if (pointer == root) {
                std::cout << "It's the root " << x << std::endl;
                root = pointer->right;
                delete pointer;
                return;
            }
            if (direction < 0)
                prevPointer->left = pointer->right;
            else
                prevPointer->right = pointer->right;
            delete pointer;
            return;
        }
        // If it has both children
        std::cout << "It has both children " << x << std::endl;
        Node *pointer2 = pointer->left;
        while (pointer2->right != nullptr)
            pointer2 = pointer2->right;

        int value = pointer2->data;
        std::cout << "The node " << value << " can replace " << x << std::endl;
        deleteElement(value);
        pointer->data = value;
    }

    // Print functions

    void inOrderTraversal() {
        std::cout << "In-order traversal: ";
        inOrderTraversal(root);
        std::cout << std::endl;
    }

    void inOrderTraversal(Node *pointer) {
        if (pointer != nullptr) {
            inOrderTraversal(pointer->left);
            std::cout << pointer->data << " ";
            inOrderTraversal(pointer->right);
        }
    }

    void preOrderTraversal() {
        std::cout << "Pre-order traversal: ";
        preOrderTraversal(root);
        std::cout << std::endl;
    }

    void preOrderTraversal(Node *pointer) {
        if (pointer != nullptr) {
            std::cout << pointer->data << " ";
            preOrderTraversal(pointer->left);
            preOrderTraversal(pointer->right);
        }
    }

    // THE ANSWER
    BinaryTree intersect(const BinaryTree &otherTree) const {
        BinaryTree result;

        recursiveIntersection(root, otherTree.root, result);

        return result;
    }

    void recursiveIntersection(Node *node1, Node *node2, BinaryTree &result) const {
        if (node1 == nullptr || node2 == nullptr)
            return;

        if (node2Contains(node2, node1->data))
            result.insertElement(node1->data);

        recursiveIntersection(node1->left, node2, result);
        recursiveIntersection(node1->right, node2, result);
    }

    bool node2Contains(Node *node, int x) const {
        while (node != nullptr) {
            if (x == node->data)
                return true;
            else if (x < node->data)
                node = node->left;
            else
                node = node->right;
        }
        return false;
    }
};

int main() {
    BinaryTree tree1;
    tree1.insertElement(4);
    tree1.insertElement(2);
    tree1.insertElement(7);
    tree1.insertElement(3);
    tree1.insertElement(5);
    tree1.insertElement(10);

    std::cout << "First binary tree: ";
    tree1.inOrderTraversal();

    BinaryTree tree2;
    tree2.insertElement(2);
    tree2.insertElement(4);
    tree2.insertElement(3);
    tree2.insertElement(7);
    tree2.insertElement(19);
    tree2.insertElement(25);
    tree2.insertElement(10);

    std::cout << "Second binary tree: ";
    tree2.inOrderTraversal();
    std::cout << "Intersection:\n";

    BinaryTree result = tree1.intersect(tree2);

    result.inOrderTraversal();
    result.preOrderTraversal();
    return 0;
}

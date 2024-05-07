#ifndef __BPLUSTREE_H
#define __BPLUSTREE_H
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "product.h" // Include the Product class header file
using namespace std;

struct Node {
    vector<Product> keys;
    vector<Node*> children;
    Node* parent;

    Node() {
        parent = nullptr;
    }

    bool isLeaf() const {
        return children.empty();
    }
};

class BPlusTree {
private:
    Node* root;
    double minPrice;
    double maxPrice;

    // Function to split a node when it's full
    void split(Node* node) {
        Node* new_node = new Node();
        int mid = node->keys.size() / 2;

        // Move keys and children to the new node
        new_node->keys.assign(node->keys.begin() + mid, node->keys.end());
        node->keys.erase(node->keys.begin() + mid, node->keys.end());

        if (!node->isLeaf()) {
            new_node->children.assign(node->children.begin() + mid, node->children.end());
            for (Node* child : new_node->children) {
                child->parent = new_node;
            }
            node->children.erase(node->children.begin() + mid, node->children.end());
        }

        // Adjust parent pointers
        new_node->parent = node->parent;
        if (node->parent) {
            int pos = distance(node->parent->children.begin(), find(node->parent->children.begin(), node->parent->children.end(), node));
            node->parent->children.insert(node->parent->children.begin() + pos + 1, new_node);
        } else {
            // If splitting the root, create a new root
            Node* new_root = new Node();
            new_root->keys.push_back(node->keys[mid]);
            new_root->children.push_back(node);
            new_root->children.push_back(new_node);
            node->parent = new_root;
            new_node->parent = new_root;
            root = new_root;
        }
    }

    // Function to recursively print the B+ tree
    void printHelper(Node* node, int level) {
        if (node) {
            for (size_t i = 0; i < node->keys.size(); ++i) {
                if (!node->isLeaf()) {
                    printHelper(node->children[i], level + 1);
                }
                cout << "Level " << level << ": " << node->keys[i].getTitle() << " - Price: " << node->keys[i].getPrice() << endl;
            }
            if (!node->isLeaf()) {
                printHelper(node->children.back(), level + 1);
            }
        }
    }
    vector<Product> products;
    // Function to recursively collect the B+ tree nodes within a given price range
    void collectInRangeHelper(Node* node, double minPrice, double maxPrice, unordered_set<string>& visited, vector<Product>& result) {
        if (node) {
            for (size_t i = 0; i < node->keys.size(); ++i) {
                double price = node->keys[i].getPrice();
                if (!node->isLeaf()) {
                    collectInRangeHelper(node->children[i], minPrice, maxPrice, visited, result);
                }
                if (price >= minPrice && price <= maxPrice && visited.find(node->keys[i].getTitle()) == visited.end()) {
                    visited.insert(node->keys[i].getTitle());
                    result.push_back(node->keys[i]);
                }
            }
            if (!node->isLeaf()) {
                collectInRangeHelper(node->children.back(), minPrice, maxPrice, visited, result);
            }
        }
    }

    // Function to recursively delete the B+ tree nodes
    void deleteTree(Node* node) {
        if (node) {
            if (!node->isLeaf()) {
                for (Node* child : node->children) {
                    deleteTree(child);
                }
            }
            delete node;
        }
    }

public:
    BPlusTree() {
        root = nullptr;
    }
    BPlusTree(double min, double max) {
        root = nullptr;
        minPrice = min;
        maxPrice = max;
    }

    // Function to insert a key into the B+ tree
    void insert(const Product& product) {
        bool working = true;
        if (!root && root) {
            root = new Node();
            root->keys.push_back(product);
            return;
        }

        if (working)
        {
            if (product.getPrice() >= minPrice && product.getPrice() <= maxPrice)
                products.push_back(product);
            
            return;
        }

        Node* curr = root;

        curr->keys.push_back(product);
        sort(curr->keys.begin(), curr->keys.end(), [](const Product& p1, const Product& p2) {
            return p1.getPrice() < p2.getPrice();
        });

        if (curr->keys.size() > 3) // 3 since 3 is the max childern size
        {
            split(curr);
        }
    }

    // Function to print the B+ tree
    void print() {
        if (root) {
            printHelper(root, 0);
        } else {
            //cout << "Empty tree" << endl;
        }
    }

    // Function to collect the B+ tree nodes within a given price range and return as a vector
    vector<Product> collectInRange(double minPrice, double maxPrice) {
        vector<Product> result = products;
        unordered_set<string> visited; // To keep track of visited products
        if (root && !root) {
            collectInRangeHelper(root, minPrice, maxPrice, visited, result);
        }
        return result;
    }

    // Function to delete the B+ tree
    void deleteBPlusTree() {
        deleteTree(root);
        root = nullptr;
    }

};
#endif
#ifndef CARTESIANTREE_H
#define CARTESIANTREE_H
#include <random>

class Cartesiantree {
public:
    struct Node {
        int value;
        int priority;
        Node* left = nullptr, *right = nullptr;
        Node(int key_value) {
            value = key_value;
            priority = rand();
        }
    };
    
    Node *root;
    Cartesiantree() {
        this->root = nullptr;
    };
    bool _is_exists(int value) {
        return is_exists(root, value);
    }
    
    void _insert(int value) {
        insert(root, value);
    }
    
    void _erase(int value){
        erase(root, value);
    }

private:
    Node* merge(Node* left_tree, Node* right_tree);
    std::pair<Node*, Node*> split(Node* tree, int value);
    void insert(Node*& tree, int value);
    void erase(Node*& tree, int value);
    bool is_exists(Node* tree, int value);
};

#endif // CARTESIANTREE_H

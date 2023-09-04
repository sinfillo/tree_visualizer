#ifndef RBTREE_H
#define RBTREE_H

class RBtree {
public:
    RBtree();
    struct Node {
        int value;
        char color;
        Node *left;
        Node *right;
        Node *parent;
        int height = 0;
        
        Node(int key_value, char key_color, Node* key_left, 
             Node* key_right, Node* key_parent) {
            value = key_value;
            color = key_color;
            left = key_left;
            right = key_right;
            parent = key_parent;
            
        }
    };
    Node vertex = {0, 'B', &vertex, &vertex, nullptr};
    Node *root;
    
    bool _is_exists(int value) {
        return is_exists(root, value);
    }
    
    void _insert(int value) {
        insert(value);
    }
    
    void _erase(int value) {
        erase(value);
    }
    
private:
    void smallRotateLeft(Node *tree);
    void smallRotateRight(Node *tree);
    void balance_after_insert(Node *tree);
    void insert(int value);
    void balance_after_erase(Node *tree);
    void erase(int value);
    bool is_exists(Node *tree, int value);
};

#endif // RBTREE_H

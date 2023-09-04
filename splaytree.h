#ifndef SPLAYTREE_H
#define SPLAYTREE_H


class Splaytree {

public:
    Splaytree();
    struct Node{
        int value;
            Node *left = nullptr, *right = nullptr;
            Node *parent = nullptr;

            Node (int key_value) {
                value = key_value;
            }
    };

    Node *root;

    bool _is_exists(int value) {
        return is_exists(root, value);
    }

    void _insert(int value) {
        return insert(value);
    }

    void _erase(int value) {
        return erase(value);
    }

private:
    void smallRotateRight(Node* tree);
    void smallRotateLeft(Node* tree);
    void splay(Node*& tree);
    void insert(int value);
    bool is_exists(Node *tree, int value);
    void erase(int value);
};

#endif // SPLAYTREE_H

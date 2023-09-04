#ifndef AVLTREE_H
#define AVLTREE_H
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QString>

class AVLtree {
public:
    struct Node {
        int value, height = 1;
        Node *left = nullptr, *right = nullptr;

        Node(int key_value) {value = key_value;}
    };

    Node *root;
    AVLtree() {
        this->root = nullptr;
    };

    bool _is_exists(int value) {
        return is_exists(root, value);
    }

    void _insert(int value) {
        root = insert(root, value);
    }

    void _erase(int value) {
        root = erase(root, value);
    }

private:
    int get_height(Node *tree);
    int difference(Node *tree);
    void upd_height(Node *tree);
    Node *smallRotateLeft(Node *tree);
    Node *smallRotateRight(Node *tree);
    Node *bigRotateLeft(Node *tree);
    Node *bigRotateRight(Node *tree);
    void balance (Node *&tree);
    Node *insert(Node *tree, int value);
    Node *min_in_right(Node *tree);
    Node *erase_min(Node *tree);
    Node *erase(Node *tree, int min);
    bool is_exists(Node *tree, int value);
};
#endif // AVLTREE_H

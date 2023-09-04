#include "splaytree.h"

Splaytree::Splaytree() {
    root = nullptr;
}

void Splaytree::smallRotateRight(Splaytree::Node* tree) {
    Splaytree::Node *par = tree->parent;
    Splaytree::Node *left = tree->left;
    if (par != nullptr) {
        if (tree == par->left) {
            par->left = left;
        } else {
            par->right = left;
        }
    }

    Splaytree::Node *tmp = left->right;
    left->right = tree;
    tree->left = tmp;
    tree->parent = left;
    left->parent = par;
    if (tree->left != nullptr) {
        tree->left->parent = tree;
    }

    return;
}

void Splaytree::smallRotateLeft(Splaytree::Node* tree) {
    Splaytree::Node *par = tree->parent;
    Splaytree::Node *right = tree->right;
    if (par != nullptr) {
        if (tree == par->left) {
            par->left = right;
        } else {
            par->right = right;
        }
    }

    Splaytree::Node *tmp = right->left;
    right->left = tree;
    tree->right = tmp;
    tree->parent = right;
    right->parent = par;
    if (tree->right != nullptr) {
        tree->right->parent = tree;
    }

    return;
}

void Splaytree::splay(Splaytree::Node*& tree) {
    while (tree->parent != nullptr) {
        //Node *g = tree->parent->parent;
        if (tree == tree->parent->left) {
            if (tree->parent->parent == nullptr) {
                smallRotateRight(tree->parent);
            } else if (tree->parent == tree->parent->parent->left) {
                smallRotateRight(tree->parent->parent);
                smallRotateRight(tree->parent);
            } else {
                smallRotateRight(tree->parent);
                smallRotateLeft(tree->parent);
            }
        } else {
            if (tree->parent->parent == nullptr) {
                smallRotateLeft(tree->parent);
            } else if (tree->parent == tree->parent->parent->right) {
                smallRotateLeft(tree->parent->parent);
                smallRotateLeft(tree->parent);
            } else {
                smallRotateLeft(tree->parent);
                smallRotateRight(tree->parent);
            }
        }
    }

    root = tree;

    return;
}

void Splaytree::insert(int value) {
    Splaytree::Node *cur = root;
    Splaytree::Node *parent = nullptr;
    while (cur != nullptr) {
        if (value == cur->value) {
            return;
        }
        parent = cur;
        if (value < cur->value) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }

    Splaytree::Node *tree = new Node(value);
    tree->parent = parent;
    if (parent != nullptr) {
        if (value < parent->value) {
            parent->left = tree;
        } else {
            parent->right = tree;
        }
    } else {
        root = tree;
    }

    splay(tree);

    return;
}

bool Splaytree::is_exists(Splaytree::Node* tree, int value) {
    if (!tree) {
        return false;
    }
    if (tree->value == value) {
        return true;
    }
    bool ans_left = false, ans_right = false;
    if (tree->value > value) {
        ans_left = is_exists(tree->left, value);
    }
    else {
        ans_right = is_exists(tree->right, value);
    }

    return ans_left || ans_right;
}

void Splaytree::erase(int value) {
    Splaytree::Node *cur = root;
    Splaytree::Node *parent = nullptr;
    while (cur->value != value) {
        parent = cur;
        if (value < cur->value) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }

    splay(cur);
    Splaytree::Node *left_tree = root->left, *right_tree = root->right;
    if (root->left) {
        root->left->parent = nullptr;
    }
    if (root->right) {
        root->right->parent = nullptr;
    }
    if (!left_tree) {
        root = right_tree;
        return;
    }
    Splaytree::Node *max_in_left = left_tree;
    while (max_in_left->right != nullptr) {
        max_in_left = max_in_left->right;
    }
    splay(max_in_left);
    root->right = right_tree;
    if (right_tree) {
        right_tree->parent = root;
    }
    return;
}


#include "cartesiantree.h"

Cartesiantree::Node* Cartesiantree::merge(Cartesiantree::Node* left_tree, Cartesiantree::Node* right_tree) {
    if (left_tree == nullptr) {
        return right_tree;
    }
    if (right_tree == nullptr) {
        return left_tree;
    }
    if (left_tree->priority > right_tree->priority) {
        left_tree->right = merge(left_tree->right, right_tree);
        return left_tree;
    } else {
        right_tree->left = merge(left_tree, right_tree->left);
        return right_tree;
    }
}

std::pair<Cartesiantree::Node*, Cartesiantree::Node*> Cartesiantree::split(Cartesiantree::Node *tree, int value) {
    if (tree == nullptr) {
        return { nullptr, nullptr };
    }

    if (tree->value <= value) {
        std::pair<Cartesiantree::Node*, Cartesiantree::Node*> cur = split(tree->right, value);
        tree->right = cur.first;

        return { tree, cur.second };
    } else {
        std::pair<Cartesiantree::Node*, Cartesiantree::Node*> cur = split(tree->left, value);
        tree->left = cur.second;

        return { cur.first, tree };
    }
}

void Cartesiantree::insert(Cartesiantree::Node*& tree, int value) {
    std::pair<Cartesiantree::Node*, Cartesiantree::Node*> cur = split(tree, value);
    Cartesiantree::Node* it = new Cartesiantree::Node(value);
    tree = merge(cur.first, merge(it, cur.second));

    return;
}

void Cartesiantree::erase(Cartesiantree::Node*& tree, int value) {
    std::pair<Cartesiantree::Node*, Cartesiantree::Node*> cur = split(tree, value);
    std::pair<Cartesiantree::Node*, Cartesiantree::Node*> cur_left = split(cur.first, value - 1);
    tree = merge(cur_left.first, cur.second);

    return;
}

bool Cartesiantree::is_exists(Cartesiantree::Node* tree, int value) {
    bool ans = false;
    std::pair<Cartesiantree::Node*, Cartesiantree::Node*> cur = split(tree, value);
    std::pair<Cartesiantree::Node*, Cartesiantree::Node*> cur_left = split(cur.first, value - 1);
    if (cur_left.second == nullptr) {
        ans = false;
    } else {
        ans = true;
    }

    tree = merge(merge(cur_left.first, cur_left.second), cur.second);

    return ans;
}

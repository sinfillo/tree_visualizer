#include "avltree.h"
#include <algorithm>
#include <vector>
#include "QGraphicsScene"
#include <QDebug>

int AVLtree::get_height(AVLtree::Node* tree) {
    if (!tree) {
      return 0;
    } else {
      return tree->height;
    }
}

int AVLtree::difference(AVLtree::Node* tree) {
    return get_height(tree->right) - get_height(tree->left);
}

void AVLtree::upd_height(AVLtree::Node* tree) {
    int left_height = get_height(tree->left);
    int right_height = get_height(tree->right);
    tree->height = std::max(left_height, right_height) + 1;

    return;
}

AVLtree::Node* AVLtree::smallRotateLeft(AVLtree::Node* tree) {
    AVLtree::Node* cur = tree->right;
    tree->right = cur->left;
    cur->left = tree;

    upd_height(tree), upd_height(cur);

    return cur;
}

AVLtree::Node* AVLtree::smallRotateRight(AVLtree::Node* tree){
    AVLtree::Node* cur = tree->left;
    tree->left = cur->right;
    cur->right = tree;

    upd_height(tree), upd_height(cur);

    return cur;
}

AVLtree::Node* AVLtree::bigRotateLeft(AVLtree::Node* tree) {
    tree->right = smallRotateRight(tree->right);
    tree = smallRotateLeft(tree);

    return tree;
}

AVLtree::Node* AVLtree::bigRotateRight(AVLtree::Node* tree) {
    tree->left = smallRotateLeft(tree->left);
    tree = smallRotateRight(tree);

    return tree;
}

void AVLtree::balance(AVLtree::Node*& tree) {
    upd_height(tree);
    if (difference(tree) == 2) {
        if (difference(tree->right) < 0) {
            tree = bigRotateLeft(tree);
        } else {
            tree = smallRotateLeft(tree);
        }

        return;
    }
    if (difference(tree) == -2) {
        if (difference(tree->left) > 0) {
            tree = bigRotateRight(tree);
        } else {
            tree = smallRotateRight(tree);
        }

        return;
    }

    return;
}

AVLtree::Node* AVLtree::insert(AVLtree::Node* tree, int value) {
    if (!tree) {
        return new AVLtree::Node(value);
    }
    if (tree->value > value) {
        tree->left = insert(tree->left, value);
    } else {
        tree->right = insert(tree->right, value);
    }

    balance(tree);

    return tree;
}

AVLtree::Node* AVLtree::min_in_right(AVLtree::Node* tree) {
    if (!tree->left) {
        return tree;
    } else {
        return min_in_right(tree->left);
    }
}

AVLtree::Node* AVLtree::erase_min(AVLtree::Node* tree) {
    if (!tree->left) {
        return tree->right;
    }
    tree->left = erase_min(tree->left);

    balance(tree);

    return tree;
}

AVLtree::Node* AVLtree::erase(AVLtree::Node* tree, int value) {
    if (!tree) {
        return nullptr;
    }
    if (tree->value > value) {
        tree->left = erase(tree->left, value);
    } else if (tree->value < value) {
        tree->right = erase(tree->right, value);
    } else {
        AVLtree::Node* left_tree = tree->left;
        AVLtree::Node* right_tree = tree->right;
        delete tree;
        if (!right_tree) {
            return left_tree;
        }
        AVLtree::Node* min = min_in_right(right_tree);
        min->right = erase_min(right_tree);
        min->left = left_tree;

        balance(min);

        return min;
    }

    balance(tree);

    return tree;

}

bool AVLtree::is_exists(AVLtree::Node* tree, int value) {
    if (!tree) {
        return false;
    }
    if (tree->value == value) {
        return true;
    }
    bool ans_left = false, ans_right = false;
    if (tree->value > value) {
        ans_left = is_exists(tree->left, value);
    } else {
        ans_right = is_exists(tree->right, value);
    }

    return ans_left || ans_right;
}

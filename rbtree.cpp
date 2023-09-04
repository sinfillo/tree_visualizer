#include "rbtree.h"

//RBtree::Node vertex = {0, 'B', &vertex, &vertex, nullptr};

RBtree::RBtree() {
    vertex = {0, 'B', &vertex, &vertex, nullptr};
    root = &vertex;
}

void RBtree::smallRotateLeft(RBtree::Node* tree) {
	RBtree::Node* cur = tree->right;
	tree->right = cur->left;
	if (cur->left != &vertex) {
		cur->left->parent = tree;
	}
	if (cur != &vertex) {
		cur->parent = tree->parent;
	}
	if (tree->parent != nullptr) {
		if (tree == tree->parent->left) {
			tree->parent->left = cur;
		} else {
			tree->parent->right = cur;
		}
	} else {
		root = cur;
	}
	cur->left = tree;
	if (tree != &vertex) {
		tree->parent = cur;
	}

	return;
}

void RBtree::smallRotateRight(RBtree::Node* tree) {
	RBtree::Node* cur = tree->left;
	tree->left = cur->right;
	if (cur->right != &vertex) {
		cur->right->parent = tree;
	}
	if (cur != &vertex) {
		cur->parent = tree->parent;
	}
	if (tree->parent != nullptr) {
		if (tree == tree->parent->right) {
			tree->parent->right = cur;
		} else {
			tree->parent->left = cur;
		}
	} else {
		root = cur;
	}
	cur->right = tree;
	if (tree != &vertex) {
		tree->parent = cur;
	}

	return;
}

void RBtree::balance_after_insert(RBtree::Node* tree) {
	while (tree != root && tree->parent->color == 'R') {
		if (tree->parent == tree->parent->parent->left) {
			RBtree::Node* uncle = tree->parent->parent->right;
			if (uncle->color == 'R') {
				tree->parent->color = 'B';
				uncle->color = 'B';
				tree->parent->parent->color = 'R';
				tree = tree->parent->parent;
			} else {
				if (tree == tree->parent->right) {
					tree = tree->parent;
					smallRotateLeft(tree);
				}

				tree->parent->color = 'B';
				tree->parent->parent->color = 'R';
				smallRotateRight(tree->parent->parent);
			}
		} else {
			RBtree::Node* uncle = tree->parent->parent->left;
			if (uncle->color == 'R') {
				tree->parent->color = 'B';
				uncle->color = 'B';
				tree->parent->parent->color = 'R';
				tree = tree->parent->parent;
			} else {
				if (tree == tree->parent->left) {
					tree = tree->parent;
					smallRotateRight(tree);
				}

				tree->parent->color = 'B';
				tree->parent->parent->color = 'R';
				smallRotateLeft(tree->parent->parent);
			}
		}
	}

	root->color = 'B';

	return;
}

void RBtree::insert(int value) {
	RBtree::Node* cur = root;
	RBtree::Node* parent = nullptr;
	while (cur != &vertex) {
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
	RBtree::Node* tree = new RBtree::Node(value, 'R', &vertex, &vertex, parent);
	if (parent != nullptr) {
		if (value < parent->value) {
			parent->left = tree;
		} else {
			parent->right = tree;
		}
	} else {
		root = tree;
	}

	balance_after_insert(tree);

	return;
}

void RBtree::balance_after_erase(RBtree::Node* tree) {
	while (tree != root && tree->color == 'B') {
		if (tree == tree->parent->left) {
			RBtree::Node* brother = tree->parent->right;
			if (brother->color == 'R') {
				brother->color = 'B';
				tree->parent->color = 'R';
				smallRotateLeft(tree->parent);
				brother = tree->parent->right;
			}
			if (brother->left->color == 'B' && brother->right->color == 'B') {
				brother->color = 'R';
				tree = tree->parent;
			} else {
				if (brother->right->color == 'B') {
					brother->left->color = 'B';
					brother->color = 'R';
					smallRotateRight(brother);
					brother = tree->parent->right;
				}
				brother->color = tree->parent->color;
				tree->parent->color = 'B';
				brother->right->color = 'B';
				smallRotateLeft(tree->parent);
				tree = root;
			}
		} else {
			RBtree::Node* brother = tree->parent->left;
			if (brother->color == 'R') {
				brother->color = 'B';
				tree->parent->color = 'R';
				smallRotateRight(tree->parent);
				brother = tree->parent->left;
			}
			if (brother->left->color == 'B' && brother->right->color == 'B') {
				brother->color = 'R';
				tree = tree->parent;
			} else {
				if (brother->left->color == 'B') {
					brother->right->color = 'B';
					brother->color = 'R';
					smallRotateLeft(brother);
					brother = tree->parent->left;
				}
				brother->color = tree->parent->color;
				tree->parent->color = 'B';
				brother->left->color = 'B';
				smallRotateRight(tree->parent);
				tree = root;
			}
		}
	}
	tree->color = 'B';
}

void RBtree::erase(int value) {
	RBtree::Node* tree = root;
	while (tree->value != value) {
		if (value < tree->value) {
			tree = tree->left;
		} else {
			tree = tree->right;
		}
	}
	if (!tree || tree == &vertex) {
		return;
	}
	RBtree::Node* list = nullptr;
	if (tree->left == &vertex || tree->right == &vertex) {
		list = tree;
	} else {
		list = tree->right;
		while (list->left != &vertex) {
			list = list->left;
		}
	}

	RBtree::Node* cur = nullptr;
	if (list->left != &vertex) {
		cur = list->left;
	} else {
		cur = list->right;
	}
	cur->parent = list->parent;
	if (list->parent != nullptr) {
		if (list == list->parent->left) {
			list->parent->left = cur;
		} else {
			list->parent->right = cur;
		}
	} else {
		root = cur;
	}
	if (list != tree) {
		tree->value = list->value;
	}

	if (list->color == 'B') {
		balance_after_erase(cur);
	}

	delete(list);
    
	return;
}

bool RBtree::is_exists(RBtree::Node* tree, int value) {
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

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>

template <typename Comparable>
class AvlTree {
public:


private:
	struct AvlNode {
		Comparable element;
		AvlNode* left;
		AvlNode* right;
		int height;

		AvlNode(const Comparable& ele, AvlNode* lt, AvlNode* rt, int h = 0)
			: element { ele }, left { lt }, right { rt }, height { h } {}

		AvlNode(Comparable&& ele, AvlNode* lt, AvlNode* rt, int h = 0)
			: element{ std::move(ele) }, left{ lt }, right{ rt }, height{ h } {}
	};

	AvlNode* root;

	int height(AvlNode* t) const {
		return (t == nullptr) ? -1 : t->height;
	}

	void insert(const Comparable& ele, AvlNode*& t) {
		if (t == nullptr) {
			t = new AvlNode{ ele, nullptr, nullptr }；
		} else if (ele < t->element) {
			insert(ele, t->left);
		} else if (ele > t->element) {
			insert(ele, t->right);
		} else
			;
		balance(t);
	}

	static const int ALLOWED_IMBALANCE = 1;

	void balance(AvlNode*& t) {
		if (t == nullptr)
			return;

		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
			if (height(t->left->left) >= height(t->left->right))
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		}
		else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
			if (height(t->right->right) >= height(t->right->left))
				rotateWithRightChild(t);
			else
				doubleWithRightChild(t);
		}
		t->height = std::max(height(t->left), height(t->right)) + 1;
	}

	void rotateWithLeftChild(AvlNode*& k2) {
		AvlNode* k1 = k2->left;
		//这里两部不能颠倒顺序，若是 k1->right = k2 先执行，那么k1原先的右节点就找不到了。
		k2->left = k1->right;
		k1->right = k2;
		k2->height = std::max(height(k2->left), height(k2->right)) + 1;
		k1->height = std::max(height(k1->left), k2->height) + 1;
		//设置新根
		k2 = k1
	}
	//对称
	void rotateWithRightChild(AvlNode*& k1) {
		AvlNode* k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = std::max(height(k1->left), height(k1->right)) + 1;
		k2->height = std::max(height(k2->right), k1->height) + 1;
		k1 = k2;
	}

	void doubleWithLeftChild(AvlNode*& k3) {
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}

	void doubleWithRightChild(AvlNode*& k1) {
		rotateWithLeftChild(k1->right);
		rotateWithRightChild(k1);
	}

	void remove(const Comparable& x, AvlNode*& t) {
		if (t == nullptr)
			return;
		if (x < t->element) {
			remove(x, t->left);
		}
		else if (x > t->element) {
			remove(x, t->right);
		}
		else if (t->left != nullptr && t->right != nullptr) {
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			BinaryNode* oldNode = t;
			t = (t->left == nullptr) ? t->right : t->left;
			delete oldNode;
		}
		balance(t);
	}

};

#endif

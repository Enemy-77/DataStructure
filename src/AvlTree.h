#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include "dsexceptions.h"

template <typename Comparable>
class AvlTree {
public:
	AvlTree() : root{nullptr} {}
	AvlTree(const AvlTree& rhs) : root{ nullptr }
	{
		root = clone(rhs.root);
	}
	AvlTree(AvlTree&& rhs) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}
	~AvlTree()
	{
		makeEmpty();
	}
	AvlTree& operator=(const AvlTree& rhs)
	{
		AvlTree copy = rhs;
		std::swap(*this, copy);
		return *this;
	}
	AvlTree& operator=(AvlTree&& rhs)
	{
		std::swap(root, rhs.root);
		return *this;
	}
	
	void makeEmpty()
	{
		makeEmpty(root);
	}
	const Comparable& findMin() const
	{
		if (isEmpty())
			throw UnderflowException{ };
		return findMin(root)->element;
	}
	const Comparable& findMax() const
	{
		if (isEmpty())
			throw UnderflowException{ };
		return findMax(root)->element;
	}
	bool contains(const Comparable& x) const
	{
		return contains(x, root);
	}
	bool isEmpty() const
	{
		return root == nullptr;
	}
	void printTree() const
	{
		if (isEmpty())
			std::cout << "Empty tree" << std::endl;
		else
			printTree(root);
	}
	void insert(const Comparable& x)
	{
		insert(x, root);
	}
	void insert(Comparable&& x)
	{
		insert(std::move(x), root);
	}
	void remove(const Comparable& x)
	{
		remove(x, root);
	}

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
			t = new AvlNode{ ele, nullptr, nullptr };
		} else if (ele < t->element) {
			insert(ele, t->left);
		} else if (ele > t->element) {
			insert(ele, t->right);
		} else
			;
		balance(t);
	}

	void insert(const Comparable&& ele, AvlNode*& t) {
		if (t == nullptr) {
			t = new AvlNode{ std::move(ele), nullptr, nullptr }；
		}
		else if (ele < t->element) {
			insert(std::move(ele), t->left);
		}
		else if (ele > t->element) {
			insert(std::move(ele), t->right);
		}
		else
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
		k2 = k1;
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
			AvlNode* oldNode = t;
			t = (t->left == nullptr) ? t->right : t->left;
			delete oldNode;
		}
		balance(t);
	}

	AvlNode* findMin(AvlNode* t) const {
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr)
			return t;
		return findMin(t->left);
	}

	AvlNode* findMax(AvlNode* t) const {
		if (t == nullptr)
			return nullptr;
		if (t->right == nullptr)
			return t;
		return findMax(t->right);
	}

	bool contains(const Comparable& x, AvlNode* t) const {
		if (t == nullptr)
			return false;
		if (x > t->element)
			return contains(x, t->right);
		else if (x < t->element)
			return contains(x, t->left);
		else
			return true;
	}

	void makeEmpty(AvlNode*& t) {
		if (t != nullptr) {
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}

	void printTree(AvlNode* t) const {
		if (t != nullptr)
		{
			printTree(t->left);
			std::cout << t->element << std::endl;
			printTree(t->right);
		}
	}

	AvlNode* clone(AvlNode* t) const {
		if (t == nullptr)
			return nullptr;
		return new AvlNode(t->element, clone(t->left), clone(t->right), t->height);
	}


};

#endif

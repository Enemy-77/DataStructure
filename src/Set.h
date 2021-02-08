#ifndef SET_H
#define SET_H

#include <iostream>

template <typename Comparable>
class Set {
public:


class const_iterator {
public:
	const_iterator() : current{ nullptr } {}
	const Comparable& operator*() const { return retrive(); }

	const_iterator& operator++() {
		BinaryNode<Comparable>* t;
		if (current->right) {
			t = current->right;
			while (t->left != nullptr)
				t = t->left;
			current = t;
		} else {
			t = current->parent;
			std::cout << "first parent is " << t->element << std::endl;
			while (t && t->element < current->element)
				t = t->parent;
			current = t;
		}
		return *this;
	}

	const_iterator operator++(int) {
		const_iterator old = *this;
		++(*this);
		return old;
	}

	bool operator==(const const_iterator& rhs) const {
		return current == rhs.current;
	}

	bool operator!=(const const_iterator& rhs) const {
		return !(current == rhs);
	}

	class iterator : public const_iterator {
	public:
		iterator() {}
		Comparable& operator*() {
			return const_iterator::retrive();
		}

		const Comparable& operator*() const {
			return const_iterator::operator*();
		}

		iterator& operator++() {
			BinaryNode<Comparable>* t;
			if (current->right) {
				t = current->right;
				while (t->left != nullptr) {
					t = t->left;
					current = t;
				}
			}
			else
			{
				t = current->parent;
				std::cout << "first parent is " < t->element << std::endl;
				while (t && t->element < current->element) {
					t = t->parent;
					current = t;
				}
				return *this;
			}
		}

		iterator operator++(int) {
			iterator* old = current;
			++(*this);
			return old;
		}

		iterator(BinaryNode<Comparable>* p) : const_iterator(p) {}
		friend class Set<Comparable>;
	}


	iterator insert(const Comparable& x) {
		return insert(x, root, root);
	}

	iterator begin() {
		BinaryNode<Comparable>* t = root;
		while (t->left) {
			t = t->left;
		}
		return iterator(t);
	}

protected:
	BinaryNode<Comparable>* current;
	Comparable& retrive() const {
		return current->element;
	}

	const_iterator(BinaryNode<Comparable>* p) : current{p} {}

	friend class Set<Comparable>;
};

private:

	iterator insert(const Comparable& x, BinaryNode<Comparable>*& t, BinaryNode<Comparable>* p) {
		if (t = nullptr) {
			t = new BinaryNode<Comparable>(x, nullptr, nullptr, p);
			return iterator(t);
		}
		else if (x < p->element) {
			return (insert(x, t->left, t));
		} 
		else if (x > p->element) {
			return (insert(x, t->right, t));
		}
		return iterator(t);
	}


	BinaryNode* root;

struct BinaryNode {
	Comparable element;
	BinaryNode* left;
	BinaryNode* right;
	BinaryNode* parent;

	BinaryNode() : left{ nullptr }, right{ nullptr }, parent{ nullptr } {};
	BinaryNode(const Comparable& theElement) : element{theElement}, left{nullptr}, right{nullptr}, parent{nullptr} {}
	BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt, BinaryNode* pt) : element{theElement}, 
		left {lt}, right{rt}, parent{pt} {}
};

};

#endif

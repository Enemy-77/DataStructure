#ifndef LIST_H
#define LIST_H

#include <algorithm>

template <typename Object>
class List {
private:
	struct Node {
		Object data;
		Node* prev;
		Node* next;

		Node(const Object& d = Object(), Node* p = nullptr, Node* n = nullptr) :
			data(d), prev(p), next(n) {}
	};

public:
	class const_iterator {
	public:
		const_iterator() : current{nullptr} {}
		const Object& operator*() const { return retrive(); }
		// ++it
		const_iterator& operator++() {
			current = current->next;
			return *this;
		}
		// it++, int never be used, just to distinguish
		const_iterator operator++(int) {
			const_iterator old = *this;
			++(*this);
			return old;
		}
		const_iterator& operator--() {
			current = current->prev;
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator old = *this;
			--(*this);
			return old;
		}
		bool operator==(const const_iterator&& rhs) {
			return current == rhs.current;
		}
		bool operator!=(const const_iterator&& rhs) {
			return !(*this == rhs);
		}

		bool operator==(const const_iterator& rhs) const {
			return current == rhs.current;
		}

		bool operator!=(const const_iterator& rhs) const {
			return !(*this == rhs);
		}
	protected:
		Node* current;
		Object& retrive() const {
			return current->data;
		}
		const_iterator(Node* p) : current {p} {}

		friend class List<Object>;
	};

	class iterator : public const_iterator {
	public:
		iterator() {}
		Object& operator*() { return const_iterator::retrive(); }
		const Object& operator*() const { return const_iterator::operator*(); }

		iterator& operator++() {
			this->current = this->current->next;
			return *this;
		}
		iterator operator++(int) {
			iterator old = *this;
			++(*this);
			return old;
		}
		iterator& operator--() {
			this->current = this->current->prev;
			return *this;
		}
		iterator operator--(int) {
			iterator old = *this;
			--(*this);
			return old;
		}


	protected:
		iterator(Node* p) : const_iterator{p} {}

		friend class List<Object>;
	};

public:
	List() { Init(); }

	List(const List& rhs) {
		Init();
		for (auto& x : rhs) {
			push_back(x);
		}
	}

	~List() {
		clear();
		delete head;
		delete tail;
	}

	List& operator=(const List& rhs) {
		List copy = this;
		std::swap(*this, copy);
		return *this;
	}

	List(List&& rhs) : theSize{ rhs.theSize }, head{ rhs.head }, tail{rhs.tail} {
		rhs.theSize = 0;
		rhs.head = nullptr;
		rhs.tail = nullptr;
	}

	List& operator=(List && rhs) {
		std::swap(theSize, rhs.theSize);
		std::swap(head, rhs.head);
		std::swap(tail, rhs.tail);
		return *this;
	}

	iterator begin() {
		return iterator(head->next);
	}

	const_iterator begin() const {
		return const_iterator(head->next);
	}

	iterator end() {
		return iterator(tail);
	}

	const_iterator end() const {
		return const_iterator(tail);
	}

	int size() const {
		return theSize;
	}

	bool empty() const {
		return theSize == 0;
	}

	void clear() {
		while (!empty())
			pop_front();
	}

	Object& front() {
		return *begin();
	}

	const Object& front() const {
		return *begin();
	}

	Object& back() {
		return *--end();
	}

	const Object& back() const {
		return *--end();
	}

	void push_front(const Object& x) {
		insert(begin(), x);
	}

	void push_front(Object&& x) {
		insert(begin(), std::move(x));
	}

	void push_back(const Object& x) {
		insert(end(), x);
	}

	void push_back(Object&& x) {
		insert(end(), std::move(x));
	}

	void pop_front() {
		erase(begin());
	}

	void pop_back() {
		iterator it = end();
		erase(--it);
	}

	iterator insert(iterator itr, const Object& x) {
		theSize++;
		Node* node = itr.current;
		Node* new_node = new Node(x, node->prev, node);
		node->prev->next = new_node;
		node->prev = new_node;
		return iterator(new_node);
	}

	iterator insert(iterator itr, Object&& x) {
		theSize++;
		Node* node = itr.current;
		Node* new_node = new Node(std::move(x), node->prev, node);
		node->prev->next = new_node;
		node->prev = new_node;
		return iterator(new_node);
	}

	iterator erase(iterator itr) {
		theSize--;
		Node* node = itr.current;
		Node* next = node->next;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete node;
		return iterator(next);
	}

	iterator erase(iterator from, iterator to) {
		for (iterator it = from; it != to; ) {
			it = erase(it);
		}
		return to;
	}

private:
	void Init() {
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}
	int theSize;
	Node* head;
	Node* tail;
};

#endif // !LIST_H

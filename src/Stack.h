#ifndef STACK_H
#define STACK_H

#include "List.h"

template <typename Object>
class Stack {
public:
	bool isEmpty() const {
		return theList.empty();
	}
	const Object& top() const {
		return theList.front();
	}
	void push(const Object& object) {
		theList.push_front(object);
	}
	void pop(Object& x) {
		x = theList.front();
		theList.pop_front();
	}
private:
	List<Object> theList;
};


template <typename Object>
class Queue {
public:
	bool isEmpty() const {
		return theList.empty();
	}
	const Object& getFront() const {
		return theList.front();
	}
	void enqueue(const Object& x) {
		theList.push_back(x);
	}
	void dequeue(Object& x) {
		x = theList.front();
		theList.pop_front();
	}

private:
	List<Object> theList;
};

#endif

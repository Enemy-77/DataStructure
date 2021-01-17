#pragma once
#ifndef VECOTR_H
#define VECOTR_H
#define DllExport __declspec(dllexport)

#include <algorithm>

template <typename Object>
class Vector {
public:
	explicit Vector(int initSize = 0) : theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY} {
		objects = new Object[theCapacity];
	}

	Vector(const Vector& rhs) : theCapacity(rhs.theCapacity), theSize(rhs.theSize) {
		objects = new Object[theCapacity];
		for (int i = 0; i < theSize; ++i) {
			objects[i] = rhs.objects[i];
		}
	}

	Vector& operator=(const Vector& rhs) {
		Vector copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	~Vector() {
		delete[] objects;
	}

	//TODO: 数组可以这么弄吗(大括号初始化)？
	Vector(Vector&& rhs) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{rhs.objects} {
		rhs.theCapacity = 0;
		rhs.theSize = 0;
		rhs.objects = nullptr;
	}

	Vector& operator=(Vector&& rhs) {
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(theSize, rhs.theSize);
		std::swap(objects, rhs.objects);
		return *this;
	}

	void resize(int newSize) {
		theSize = newSize;
		if (newSize > theCapacity) {
			reserve(newSize * 2);
		}
	}

	void reserve(int newCapacity) {
		if (newCapacity > theCapacity) {
			Object* tmp = new Object[newCapacity];
			for (int i = 0; i < theSize; ++i) {
				tmp[i] = tmp[i];
			}
			delete[] objects;
			objects = tmp;
		}
	}

	Object& operator[](int index) {
		if (index > theSize) {
			...
		}
		return objects[index];
	}

	const Object& operator[](int index) const {
		if (index > theSize) {
			...
		}
		return objects[index];
	}

	bool empty() const {
		return theSize == 0;
	}

	int size() const {
		return theSize;
	}

	int capacity() const {
		return theCapacity;
	}

	void push_back(const Object& x) {
		if (theSize == theCapacity) {
			reserve(2 * theCapacity + 1);
		}
		objects[theSize++] = x;
	}

	void push_back(Object&& x) {
		if (theSize == theCapacity) {
			reserve(2 * theCapacity + 1);
		}
		objects[theSize++] = std::move(x);
	}

	void pop_back() {
		theSize--;
	}

	const Object& back() const {
		return objects[theSize - 1];
	}

	
	typedef Object* iterator;
	typedef const Object* const_iterator;

	iterator begin() {
		return objects;
	}

	const_iterator begin() const {
		return objects;
	}

	iterator end() {
		return &objects[theSize];
	}

	const_iterator end() const {
		return &objects[theSize];
	}

	static const int SPARE_CAPACITY = 16;

private:
	int theCapacity;
	int theSize;
	Object* objects;
};

#endif // !VECOTR_H

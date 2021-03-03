#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "Vector.h"

template <typename Comparable>
class BinaryHeap
{
public:
	explicit BinaryHeap(int capacity = 100) : array(capacity + 1), currentSize(0) {}
	
	explicit BinaryHeap(const Vector<Comparable>& items) : array(items.size() + 10), currentSize{ items.size() }
	{
		for (int i = 0; i < items.size(); ++i)
			array[i + 1] = items[i];
		buildHeap();
	}

	bool isEmpty() const
	{
		return currentSize == 0;
	}

	const Comparable& findMin() const
	{
		if (isEmpty())
			throw UnderflowException{};
		return array[1];
	}

	void insert(const Comparable& x)
	{
		if (currentSize == array.size() - 1)
			array.resize(array.size() * 2);

		int hole = ++currentSize;
		Comparable copy = x;

		array[0] = std::move(copy);
		for (; x < array[hole / 2]; hole /= 2)    //父亲在 i/2 的位置上
			array[hole] = std::move(array[hole / 2]);
		array[hole] = std::move(array[0]);
		//避免了过多的赋值
	}

	void insert(Comparable&& x)
	{
		if (currentSize == array.size() - 1)
			array.resize(array.size() * 2);

		int hole = ++currentSize;
		for (; hole > 1 && x < array[hole / 2]; hole /= 2) 
			array[hole] = std::move(array[hole / 2]);
		array[hole] = std::move(x);
	}

	void deleteMin()
	{
		if (isEmpty())
			throw UnderflowException{};

		array[1] = std::move(array[currentSize--]);
		percolateDown(1);
	}

	void deleteMin(Comparable& minItem)
	{
		if (isEmpty())
			throw UnderflowException{};

		minItem = std::move(array[1]);
		array[1] = std:::move(array[currentSize--]);
		percolateDown(1);
	}
	void makeEmpty()
	{
		currentSize = 0;
	}

private:
	int currentSize;
	Vector<Comparable> array;

	void buildHeap()
	{
		for (int i = currentSize / 2; i > 0; --i)
			percolateDown(i);
	}

	void percolateDown(int hole)
	{
		int child;
		Comparable tmp = std::move(array[hole]);

		for (; hole * 2 <= currentSize; hole = child) {
			child = hole * 2;
			if (child != currentSize && array[child + 1] < array[child])  //比较右儿子和左儿子的大小
				++child;

			if (array[child] < tmp)
				array[hole] = std::move(array[child]);
			else
				break;
		}
		array[hole] = std::move(tmp);
	}
};

#endif
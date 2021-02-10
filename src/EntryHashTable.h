#ifndef ENTRY_HASH_TABLE_H
#define ENTRY_HASH_TABLE_H

#include "Vector.h"

bool isPrime(int n)
{
	if (n == 2 || n == 3)
		return true;

	if (n == 1 || n % 2 == 0)
		return false;

	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;

	return true;
}

int nextPrime(int n)
{
	if (n % 2 == 0)
		++n;

	for (; !isPrime(n); n += 2)
		;

	return n;
}


template <typename HashedObj>
class EntryHashTable {
public:
	explicit EntryHashTable(int size = 101) : array(nextPrime(size)) {
		makeEmpty();
	}

	bool contains(const HashedObj& x) const
	{
		return isActive(findPos(x));
	}

	void makeEmpty()
	{
		currentSize = 0;
		for (auto & entry : array)
		{
			entry.info = EMPTY;
		}
	}
	bool insert(const HashObj& x)
	{
		int currentPos = findPos(x);
		if (isActive(currentPos))
			return false;

		array[currentPos].element = x;
		array[currentPos].info = ACTIVE;

		if (++currentSize > array.size() / 2)
			rehash();

		return true;
	}
	bool insert(HashedObj&& x)
	{
		int currentPos = findPos(x);
		if (isActive(currentPos))
			return false;

		array[currentPos].element = std::move(x);
		array[currentPos].info = ACTIVE;

		if (++currentSize > array.size() / 2)
			rehash();

		return true;
	}
	bool remove(const HashedObj& x)
	{
		int currentPos = findPos(x);
		if (!isActive(currentPos))
			return false;

		array[currentPos].info = DELETED;
		return true;
	}

	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
			: element{e}, info{i} {}

		HashEntry(HashedObj&& e, EntryType i = EMPTY)
			: element{ std::move(e) }, info{ i } {}
	};


	Vector<HashEntry> array;
	int currentSize;

	bool isActive(int currentPos) const
	{
		return array[currentPos].info == ACTIVE;
	}

	int findPos(const HashedObj& x) const
	{
		int offset = 1;
		int currentPos = myhash(x);

		while (array[currentPos].info != EMPTY && array[currentPos].element != x)
		{
			currentPos + = offset;
			offset += 2;
			if (currentPos >= array.size())
				currentPos -= array.size();
		}
		return currentPos;
	}
	void rehash()
	{
		Vector<HashEntry> oldArray = array;

		array.resize(nextPrime(2 * oldArray.size()));
		for (auto& entry : array)
			entry.info = EMPTY;

		currentSize = 0;
		for (auto& entry : oldArray) {
			if (entry.info == ACTIVE)
				insert(std::move(entry.element));
		}
	}
	size_t myhash(const HashedObj& x) const;
};



#endif

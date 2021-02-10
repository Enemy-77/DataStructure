#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "Vector.h"
#include "List.h"

template <typename Iterator, typename Object>
Iterator find(Iterator start, Iterator end, const Object& x) {
	Iterator itr = start;
	while (itr != end && *itr != x) {
		itr++;
	}
	return itr;
}

template <typename HashedObj>
class HashTable
{
public:
	explicit HashTable(int size = 101);

	bool contains(const HashedObj& x) {
		auto& whichList = theLists[myhash(x)];
		return find(begin(whichList), end(whichList), x) != end(whichList);
	}

	void makeEmpty() {
		for (auto& theList : theLists)
			theList.clear();
	}
	bool insert(const HashedObj& x) {
		auto& whichList = theLists[myhash(x)];
		auto itr = find(begin(whichList), end(whichList), x);
		if (itr == end(whichList))
			return false;
		whichList.push_back(itr, x);

		// 再散列
		if (++currentSize > theLists.size())
			rehash();

		return true;
	}
	bool insert(const HashedObj&& x) {
		auto& whichList = theLists[myhash(x)];
		auto itr = find(begin(whichList), end(whichList), x);
		if (itr == end(whichList))
			return false;
		whichList.push_back(itr, std::move(x));

		// 再散列
		if (++currentSize > theLists.size())
			rehash();

		return true;
	}
	bool remove(const HashedObj& x) {
		auto& whichList = theLists[myhash(x)];
		auto itr = find(begin(whichList), end(whichList), x);
		if (itr == end(whichList))
			return false;

		whichList.erase(itr);
		--currentSize;
		return true;
	}

private:
	Vector<List<HashedObj>> theLists;
	int currentSize;

	void rehash()
	{
		Vector<List<HashedObj>> oldLists = theLists;
		theLists.resize(nextPrime(2 * theLists.size()));
		for (auto& thisList : theLists)
			thisList.clear();
		
		currentSize = 0;
		for (auto & thisList : oldLists) {
			for (auto & x : thisList) {
				insert(std::move(x));
			}
		}
	}
	size_t myhash(const HashedObj& x) const;
};

#endif

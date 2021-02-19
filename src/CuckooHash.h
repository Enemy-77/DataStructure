#ifndef CUCKOO_HASH
#define CUCKOO_HASH

#include "Vector.h"
#include "UniformRandom.h"

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

template <typename AnyType>
class CuckooHashFamily
{
public:
	size_t hash(const AnyType& x, int which) const;
	int getNumberOfFunctions();
	void generateNewFunction();
};

template <int count>
class StringHashFamily
{
public:
	StringHashFamily() : MULTIPLIERS(count)
	{
		generateNewFunctions();
	}

	int getNumberOfFunctions() const
	{
		return count;
	}

	void generateNewFunctions()
	{
		for (auto& mult : MULTIPLIERS)
			mult = r.nextInt();
	}

	size_t hash(const string& x, int which) const
	{
		const int multiplier = MULTIPLIERS[which];
		size_t hashVal = 0;

		for (auto ch : x)
			hashVal = multiplier * hashVal + ch;

		return hashVal;
	}

private:
	Vector<int> MULTIPLIERS;
	UniformRandom r;
};


template <typename AnyType, typename HashFamily>
class CuckooHashTable
{
public:
	explicit CuckooHashTable(int size = 101) : array(nextPrime(size))
	{
		numHashFunctions = hashFunctions.getNumberOfFunctions();
		rehashes = 0;
		makeEmpty();
	}

	void makeEmpty()
	{
		currentSize = 0;
		for (auto& entry : array)
			entry.isActive = false;
	}

	bool contains(const AnyType& x) const
	{
		return findPos(x) != -1;
	}

	int size() const
	{
		return currentSize;
	}

	int capacity() const
	{
		return array.size();
	}

	bool remove(const AnyType& x)
	{
		int currentPos = findPos(x);
		if (!isActive(currentPos))
			return false;

		array[currentPos].isActive = false;
		--currentSize;
		return true;
	}
	bool insert(const AnyType& x)
	{
		if (contains(x))
			return false;

		if (currentSize >= array.size() * MAX_LOAD)
			expand();

		return insertHelper(x);
	}
	bool insert(AnyType&& x)
	{
		if (contains(x))
			return false;

		if (currentSize >= array.size() * MAX_LOAD)
			expand();

		return insertHelper(std::move(x));
	}


private:
	struct HashEntry
	{
		AnyType element;
		bool isActive;

		HashEntry(const AnyType& e = AnyType(), bool a = false)
			: element {e}, isActive{a} {}
		HashEntry(AnyType&& e, bool a = false)
			: element { std::move(e) }, isActive { a } {}
	};

	bool insertHelper(const AnyType& xx)
	{
		const int COUNT_LIMIT = 100;
		AnyType x = xx;
		while (true)
		{
			int lastPos = -1;
			int pos;

			for (int count = 0; count < COUNT_LIMIT; ++count)
			{
				for (int i = 0; i < numHashFunctions; ++i)
				{
					pos = myhash(x, i);

					if (!isActive(pos))
					{
						array[pos] = std::move(HashEntry{ std::move(x), true });
						++currentSize;
						return true;
					}
				}
				int i = 0;
				do 
				{
					pos = myhash(x, r.nextInt(numHashFunctions));
				} while ( pos == lastPos && i++ < 5 );

				lastPos = pos;
				std::swap(x, array[pos].element);
			}

			if (++rehashes > ALLOWED_REHASHES)
			{
				expand();
				rehashes = 0;
			}
			else
				rehash();
		}
	}

	bool insertHelper(AnyType&& x)
	{
		const int COUNT_LIMIT = 100;
		while (true)
		{
			int lastPos = -1;
			int pos;

			for (int count = 0; count < COUNT_LIMIT; ++count)
			{
				for (int i = 0; i < numHashFunctions; ++i)
				{
					pos = myhash(x, i);

					if (!isActive(pos))
					{
						array[pos] = std::move(HashEntry{ std::move(x), true });
						++currentSize;
						return true;
					}
				}
				int i = 0;
				do
				{
					pos = myhash(x, r.nextInt(numHashFunctions));
				} while (pos == lastPos && i++ < 5);

				lastPos = pos;
				std::swap(x, array[pos].element);
			}

			if (++rehashes > ALLOWED_REHASHES)
			{
				expand();
				rehashes = 0;
			}
			else
				rehash();
		}
	}

	bool isActive(int currentPos) const
	{
		return currentPos != -1 && array[currentPos].isActive;
	}

	size_t myhash(const AnyType& x, int which) const
	{
		return hashFunctions.hash(x, which) % array.size();
	}

	int findPos(const AnyType& x) const
	{
		for (int i = 0; i < numHashFunctions; ++i)
		{
			int pos = myhash(x, i);

			if (isActive(pos) && array[pos].element == x)
				return pos;
		}
		return -1;
	}

	void expand()
	{
		rehash(static_cast<int>(array.size() / MAX_LOAD));
	}

	void rehash()
	{
		hashFunctions.generateNewFunction();
		rehash(array.size());
	}

	void rehash(int newSize)
	{
		Vector<HashEntry> oldArray = array;

		array.resize(nextPrime(newSize));
		for (auto& entry : array)
			entry.isActive = false;

		currentSize = 0;
		for (auto& entry : oldArray)
			if (entry.isActive)
				insert(std::move(entry.element));
	}

	static const double MAX_LOAD = 0.40;
	static const int ALLOWED_REHASHES = 5;

	Vector<HashEntry> array;
	int currentSize;
	int numHashFunctions;
	int rehashes;
	UniformRandom r;
	HashFamily hashFunctions;
};

#endif

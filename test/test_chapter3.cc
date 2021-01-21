
#include "Chapter3.h"
#include <gtest/gtest.h>

template <typename Object>
void PrintList(const List<Object>& list) {
	if (list.empty())
		return;

	typedef List<Object>::const_iterator iterator;
	iterator it = list.begin();
	while (it != list.end())
	{
		std::cout << *it << "\n";
		it++;
	}
}


TEST(DSTest, TestThreeOne) {
	List<int> list_1;
	for (int i = 0; i < 10; ++i) {
		list_1.push_back(i);
	}
	List<int> list_2;
	list_2.push_back(3);
	list_2.push_back(7);
	//printLots(list_1, list_2);
}

TEST(DSTest, TestFind) {
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	typedef List<int>::iterator iterator;
	iterator start = list.begin();
	iterator end = list.end();
	iterator pos = find(start, end, 2);
	iterator real = ++list.begin();
	ASSERT_TRUE(pos == real);
}

TEST(CPTest, TestIntersection) {
	List<int> list1;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	list1.push_back(4);
	list1.push_back(5);
	
	List<int> list2;
	list2.push_back(3);
	list2.push_back(4);
	list2.push_back(5);
	list2.push_back(6);
	list2.push_back(7);
	list2.push_back(8);

	List<int> list = intersection(list1, list2);
	PrintList(list);
}

TEST(CPTest, TestUnion) {
	List<int> list1;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	list1.push_back(4);
	list1.push_back(5);

	List<int> list2;
	list2.push_back(3);
	list2.push_back(4);
	list2.push_back(5);
	list2.push_back(6);
	list2.push_back(7);

	List<int> list = listUnion(list1, list2);
	PrintList(list);
}
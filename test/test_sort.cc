#include <gtest/gtest.h>
#include "SortAlgo.h"

TEST(TestSort, TestInsert) {
	std::vector<int> vec = { 3,0,1,13,9,6,5, 20, 2, 4 };
	insertSort(vec);
}

TEST(TestSort, TestShell) {
	std::vector<int> vec = { 81, 94, 11, 96, 12, 35, 17, 95, 28, 58,41,75,15 };
	shellsort(vec);
}

#include <gtest/gtest.h>
#include "Vector.h"

TEST(TestDS, TestVector) {
	Vector<int> v;
	v.push_back(1);
	ASSERT_TRUE(v.size() == 1);

}
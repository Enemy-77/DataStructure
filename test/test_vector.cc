#include <gtest/gtest.h>
#include "Vector.h"

TEST(TestDS, TestVector) {
	Vector<int> v;
	ASSERT_TRUE(v.empty());
	v.reserve(48);
	ASSERT_TRUE(v.capacity() == 48);
	ASSERT_TRUE(v.size() == 0);
	v.push_back(1);
	ASSERT_TRUE(v.size() == 1);
	v.push_back(2);
	v.push_back(3);
	ASSERT_TRUE(v.size() == 3);
	ASSERT_TRUE(v[0] == 1);
	ASSERT_TRUE(v[1] == 2);
	ASSERT_TRUE(v[2] == 3);
	ASSERT_TRUE(v.back() == 3);
	v.pop_back();
	ASSERT_TRUE(v.size() == 2);
	Vector<int> v_1(v);
	Vector<int> v_2 = std::move(v);
	ASSERT_TRUE(v.empty());
	v_1 = std::move(v_2);
}
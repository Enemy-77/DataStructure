
#include <gtest/gtest.h>
#include "BinarySearchTree.h"

TEST(BTreeTest, TestTree) {
	BinarySearchTree<int> tree;
	ASSERT_TRUE(tree.isEmpty());
	for (int i = 0; i < 10; ++i) {
		tree.insert(i);
	}
	int min = tree.findMin();
	ASSERT_TRUE(min == 0);
	int max = tree.findMax();
	ASSERT_TRUE(max == 9);
	ASSERT_FALSE(tree.contains(10));
	ASSERT_TRUE(tree.contains(9));
}

TEST(BinaryTreeTest, TestW) {
	BinarySearchTree<int> t;
	int NUMS = 400000;
	const int GAP = 3711;
	int i;

	std::cout << "Checking... (no more output means success)" << std::endl;

	for (i = GAP; i != 0; i = (i + GAP) % NUMS)
		t.insert(i);

	for (i = 1; i < NUMS; i += 2)
		t.remove(i);

	if (NUMS < 40)
		t.printTree();
	if (t.findMin() != 2 || t.findMax() != NUMS - 2)
		std::cout << "FindMin or FindMax error!" << std::endl;

	for (i = 2; i < NUMS; i += 2)
		if (!t.contains(i))
			std::cout << "Find error1!" << std::endl;

	for (i = 1; i < NUMS; i += 2)
	{
		if (t.contains(i))
			std::cout << "Find error2!" << std::endl;
	}

	BinarySearchTree<int> t2;
	t2 = t;

	for (i = 2; i < NUMS; i += 2)
		if (!t2.contains(i))
			std::cout << "Find error1!" << std::endl;

	for (i = 1; i < NUMS; i += 2)
	{
		if (t2.contains(i))
			std::cout << "Find error2!" << std::endl;
	}

	std::cout << "Finished testing" << std::endl;
}
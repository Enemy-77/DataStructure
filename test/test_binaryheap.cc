#include <gtest/gtest.h>
#include "BinaryHeap.h"

TEST(DSTest, TestBinaryHeap) {
	BinaryHeap<int> heap(10);
	heap.insert(10);
	heap.insert(5);
	heap.insert(1);
	heap.insert(4);
	heap.insert(9);
	heap.insert(0);
	ASSERT_TRUE(heap.findMin() == 0);
	heap.deleteMin();
	ASSERT_TRUE(heap.findMin() == 1);

}

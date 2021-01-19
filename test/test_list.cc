#include <gtest/gtest.h>
#include "List.h"
#include "Stack.h"

TEST(TestDS, TestList) {
	List<int> list;
	ASSERT_TRUE(list.empty());
	ASSERT_TRUE(list.size() == 0);
	list.push_back(1);

	List<int>::iterator it = list.begin();
	ASSERT_TRUE(*it == 1);
	list.push_front(2);
	it = list.begin();
	ASSERT_TRUE(*it == 2);
	ASSERT_TRUE(list.size() == 2);
	ASSERT_TRUE(*(--list.end()) == 1);
 
 	ASSERT_TRUE(list.front() == 2);
 	ASSERT_TRUE(list.back() == 1);
 	list.pop_front();
 	ASSERT_TRUE(list.size() == 1);
 	ASSERT_TRUE(*list.begin() == 1);
	list.push_back(3);
	ASSERT_TRUE(*--list.end() == 3);
	list.pop_back();
	ASSERT_TRUE(*--list.end() == 1);
}

TEST(DSTest, TestStack) {
	Stack<int> stack;
	ASSERT_TRUE(stack.isEmpty());
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	ASSERT_TRUE(stack.top() == 4);
	int x;
	stack.pop(x);
	ASSERT_TRUE(x == 4);
	stack.pop(x);
	ASSERT_TRUE(x == 3);
	stack.pop(x);
	ASSERT_TRUE(x == 2);
	stack.pop(x);
	ASSERT_TRUE(x == 1);
}

TEST(DSTest, TestQueue) {
	Queue<int> queue;
	ASSERT_TRUE(queue.isEmpty());
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);
	queue.enqueue(4);
	ASSERT_TRUE(queue.getFront() == 1);
	int x;
	queue.dequeue(x);
	ASSERT_TRUE(x == 1);
	ASSERT_TRUE(queue.getFront() == 2);
}

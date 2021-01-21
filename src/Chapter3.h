#ifndef CHAPTER__3_H
#define CHAPTER__3_H

#include <iostream>
#include "List.h"

// 3.1
template <typename Object>
void printLots(List<Object> L, List<int> P) {

	typename List<int>::const_iterator pIter;
	typename List<Object>::const_iterator lIter;

	int start = 0;
	lIter = L.begin();
	for (pIter = P.begin(); pIter != P.end() && lIter != L.end(); pIter++) {
		while (start < *pIter && lIter != L.end()) {
			start++;
			lIter++;
		}
		if (lIter != L.end()) {
			std::cout << *lIter << std::endl;
		}
	}
}

//3.3
template <typename Iterator, typename Object>
Iterator find(Iterator start, Iterator end, const Object& x) {
	Iterator itr = start;
	while (itr != end && *itr != x) {
		itr++;
	}
	return itr;
}

//3.4
template <typename Object>
List<Object> intersection(const List<Object>& L1, const List<Object>& L2) {
// 	List<Object> list;
// 	typedef List<Object>::const_iterator iterator;
// 	for (iterator it1 = L1.begin(); it1 != L1.end(); ++it1) {
// 		for (iterator it2 = L2.begin(); it2 != L2.end(); ++it2)
// 		{
// 			if (*it1 == *it2)
// 			{
// 				list.push_back(*it1);
// 			}
// 		}
// 	}
// 	return list;

 	//better version(already sorted)
 	List<Object> result;
	typename List<Object>::const_iterator iter1 = L1.begin();
	typename List<Object>::const_iterator iter2 = L2.begin();
	while (iter1 != L1.end() && iter2 != L2.end()) {
		if (*iter1 == *iter2) {
			result.push_back(*iter1);
			iter1++;
			iter2++;
		}
		else if (*iter1 > *iter2) {
			iter2++;
		}
		else {
			iter1++;
		}
	}

	return result;
}
//3.5
template <typename Object>
List<Object> listUnion(const List<Object>& L1, const List<Object>& L2) {
	List<Object> result;
	typedef List<Object>::const_iterator iterator;
	typename iterator iter1 = L1.begin();
	typename iterator iter2 = L2.begin();
	while (iter1 != L1.end() && iter2 != L2.end()) {
		if (*iter1 == *iter2) {
			result.push_back(*iter1);
			iter1++;
			iter2++;
		}
		else if (*iter1 > * iter2) {
			result.push_back(*iter2);
			iter2++;
		}
		else {
			result.push_back(*iter1);
			iter1++;
		}
	}
	if (iter1 == L1.end()) {
		while (iter2 != L2.end()) {
			result.push_back(*iter2);
			iter2++;
		}
	}
	if (iter2 == L2.end()) {
		while (iter1 != L1.end()) {
			result.push_back(*iter1);
			iter1++;
		}
	}
	return result;
}


#endif //

#ifndef SORT_ALGO_H
#define SORT_ALGO_H

#include <vector>

template <typename Comparable>
void insertSort(std::vector<Comparable>& a) {
// 	for (int i = 1; i < a.size(); ++i) {
// 		Comparable tmp = a[i];
// 		for (int j = i; j > 0; --j) {
// 			if (tmp < a[j - 1]) {
// 				a[j] = a[j - 1];
// 				a[j - 1] = tmp;
// 			}
// 			
// 		}
// 	}

	for (int i = 1; i < a.size(); ++i)
	{
	    Comparable tmp = a[i];
		int j;
		for (j = i; j > 0 && tmp < a[j - 1]; --j)
		{
			a[j] = a[j - 1];
		}
		a[j] = tmp;
	}
}

template <typename Iterator>
void insertionSort(const Iterator& begin, const Iterator& end) {
	insertionSort(begin, end, less<decltype(*begin)>{})
}

template <typename Iterator, typename Comparator>
void insertionSort(const Iterator& begin, const Iterator& end, Comparator lessThan) {
	if (begin == end)
		return;

	Iterator j;
	for (Iterator p = begin + 1; p != end; ++p) {
		auto tmp = std::move(*p);
		for (j = p; j!= begin && lessThan(tmp, *(j - 1)); --j) {
			*j = std::move(*(j - 1));
		}
		*j = std::move(tmp);
	}
}

template <typename Comparable>
void shellsort(std::vector<Comparable>& a) {
	for (int gap = a.size() / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < a.size(); ++i) {
			Comparable tmp = a[i];
			int j = i;
			for (; j >= gap && tmp < a[j - gap]; j -= gap)
				a[j] = a[j - gap];
			a[j] = tmp;
		}
	}
}

#endif

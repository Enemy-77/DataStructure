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


template <typename Comparable>
void mergeSort(std::vector<Comparable>& a)
{
	std::vector<Comparable> tmpArray(a.size());

    mergeSort(a, tmpArray, 0, a.size() - 1);
}

template <typename Comparable>
void mergeSort(std::vector<Comparable>& a, std::vector<Comparable>& tmpArray, int left, int right)
{
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(a, tmpArray, left, mid);
        mergeSort(a, tmpArray, mid + 1, right);
        merge(a, tmpArray, left, mid + 1, right);
    }
}

template <typename Comparable>
void merge(std::vector<Comparable>& a, std::vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd)
{
    int leftEnd = rightPos - 1;
    int tempPos = leftPos;
	int numElem = rightEnd - leftPos + 1;
    while (leftPos <= leftEnd && rightPos <= rightEnd)
    {
        tmpArray[tempPos++] = a[leftPos] < a[rightPos] ? a[leftPos++] : a[rightPos++];
    }
    if (leftPos <= leftEnd)
    {
        for (int i = leftPos; i <= leftEnd; ++i)
        {
            tmpArray[tempPos++] = a[i];
        }
    }
    if (rightPos <= rightEnd)
    {
        for (int i = rightPos; i <= rightEnd; ++i)
        {
            tmpArray[tempPos++] = a[i];
        }
    }

	for (int i = 0; i < numElem; ++i, --rightEnd)
	{
		a[rightEnd] = tmpArray[rightEnd];
	}

}


#endif

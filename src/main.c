#include <iostream>
#include <algorithm>

#include <ctime>
#include <cstdlib>

#include "list.h"
#include "Stack.h"

// 遍历所有的子序列
// int MaxSub(const int A[], int N) {
//     int thisSum, maxSum, i, j;
//     maxSum = 0;
//     for (i = 0; i < N; ++i) {
//         thisSum = 0;
//         for (j = 0; j < N; ++j) {
//             thisSum += A[j];
//             if (thisSum > maxSum) {
//                 maxSum = thisSum;
//             }
//         }
//     }
//     return maxSum;
// }

//最大子序列和算法(分治策略)
int Max3(int a, int b, int c) {
    int m1 = std::max(a, b);
    int m2 = std::max(b, c);
    int max = std::max(m1, m2);
    return max;
}

int MaxSubSum(const int A[], int left, int right) {

	if(left == right) {
		if(A[left] > 0 ) {
			return A[left];
		} else {
			return 0;
		} 
	}
	int MaxLeftSum, MaxRightSum;
	int MaxLeftBorderSum, MaxRightBorderSum;
	int LeftBorderSum, RightBorderSum;
	
	int center, i;
	center = (left + right) / 2;
	MaxLeftSum = MaxSubSum(A, left, center);
	MaxRightSum = MaxSubSum(A, center + 1, right);

	MaxLeftBorderSum = 0, LeftBorderSum = 0;
	for (i = center; i >= left;i--){
		LeftBorderSum += A[i];
		if(LeftBorderSum > MaxLeftBorderSum){
			MaxLeftBorderSum = LeftBorderSum;
		}
	}

	MaxRightBorderSum = 0, RightBorderSum = 0;
	for (i = center + 1; i <= right; ++i) {
		RightBorderSum += A[i];
		if(RightBorderSum > MaxRightBorderSum){
			MaxRightBorderSum = RightBorderSum;
		}
	}
	return Max3(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);
}

int MaxSubSubSequenceSum(const int A[], int N) {
	return MaxSubSum(A, 0, N - 1); 
}


//对分查找
int BinarySerach(const int A[], int X, int N) {
    int low, mid, high;
    low = 0;
    high = N - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (X == A[mid]) {
            return mid;
        }
        else if (X < A[mid]) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return -1;
}



int RandInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

//O(n^2log n)
void fun1(int A[], const int n) {
    int tmp;
    for (int i = 0; i < n; ++i) {
        tmp = RandInt(1, n);
        for (int j = 0; j < i; ++j) {
            if (A[j] == tmp) {
                tmp = RandInt(1, n);
                j = -1;
            }
        }
        A[i] = tmp;
    }
}

//O(nlon(n))
int used[10000];
void fun2(int A[], const int n) {
    int tmp;
    memset(used, 0, sizeof(int) * 10000);
    for (int i = 0; i < n; ++i) {
        tmp = RandInt(1, n);
        while (used[tmp] !=0) {
            tmp = RandInt(1, n);
        }
        A[i] = tmp;
        used[tmp] = 1;
    }
}

//O(n)
void fun3(int A[], const int n) {
    for (int i = 0; i < n; ++i) {
        A[i] = i + 1;
    }
    for (int i = 1; i < n; ++i) {
        std::swap(A[i], A[RandInt(0, i)]);
    }
}

void PrintList(const List L)
{
    Position P = Header(L);
    if (IsEmpty(L))
        printf("empty list\n");
    else
    {
        do
        {
            P = Advance(P);
            printf("%d ", Retrieve(P));
        } while (!IsLast(P, L));
        printf("\n");
    }
}


int main() {
	int A[] = {0, 1, -2, 3, 4};
	//int max = MaxSubSubSequenceSum_0(A, 5);

    int B[] = { 0,1,2,3,4,5,6,7,8,9 };
    int index = BinarySerach(B, 5, 10);

    const int n = 100;
    int C[n];
    fun3(C, n);

    // test list
    List L;
    L = MakeEmpty(NULL);

    Position P = Header(L);
    for (int i = 0; i < 10; ++i) {
        Insert(i, L, P);
        PrintList(L);
        P = Advance(P);
    }
    int i;
    for (i = 0; i < 10; i += 2)
        Delete(i, L);

    for (i = 0; i < 10; i++)
        if ((i % 2 == 0) == (Find(i, L) != NULL))
            printf("Find fails\n");
    printf("Finished deletions\n");
    PrintList(L);
    DeleteList(L);
    PrintList(L);

    Stack S;
    CreateStack(S);





}
	 
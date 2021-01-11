#include "Stack.h"
#include "fatal.h"
#include <stdlib.h>

struct Node
{
    ElementType X;
    PtrToNode Next;
};

int Empty(Stack S)
{
    return S->Next == NULL;
}

Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct Node));
    if (S == NULL) {
        ERROR("out of memory");
        return S;
    }
    S->X = 0;
    S->Next = NULL;
    return S;
}

void DisposeStack(Stack S)
{
    while (!Empty(S))
    {
        Pop(S);
    }
}

void MakeEmpty(Stack S)
{
    if (S == NULL)
    {
        ERROR("call create stack first");
    } else {
        while (!Empty(S))
        {
            Pop(S);
        }
    }
}

void Push(ElementType X, Stack S)
{
    PtrToNode N;
    N = (PtrToNode)malloc(sizeof(struct Node));
    if (N == NULL) {
        ERROR("not enough storage");
    }
    N->X = X;
    N->Next = S->Next;
    S->Next = N;
}

ElementType Top(Stack S)
{
    if (Empty(S))
        return 0;
    return S->Next->X;
}

void Pop(Stack S)
{
    if (Empty(S))
    {
        return;
    }
    PtrToNode N = S->Next;
    S->Next = N->Next;
    free(N);
}


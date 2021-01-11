#include "ArrayStack.h"
#include "fatal.h"
#include <stdlib.h>

#define EmptyTOS -1
#define MinStackSize 5

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};

int IsEmpty(ArrayStack S)
{
    return S->TopOfStack == EmptyTOS;
}

int IsFull(ArrayStack S)
{
    return S->TopOfStack == S->Capacity - 1;
}

ArrayStack CreateStack(int MaxElements)
{
    //TODO error
    if (MaxElements < MinStackSize) {


    }

    ArrayStack S;
    S =(ArrayStack)malloc(sizeof(struct StackRecord));
    if (S == NULL) {
        //Todo : error
    }
    S->Capacity = MaxElements;
    S->TopOfStack = -1;
    S->Array = (int*)malloc(MaxElements * sizeof(int));
    if (S->Array == NULL) {
        //Todo : error
    }
    return S;
}

void DisposeStack(ArrayStack S)
{
    if (!IsEmpty(S)) {
        free(S->Array);
        free(S);
    }
}

void MakeEmpty(ArrayStack S)
{
    S->TopOfStack = EmptyTOS;
}

void Push(ElementType X, ArrayStack S)
{
    if (IsFull(S))
    {
        ERROR("full stack");
    }
    (S->TopOfStack)++;
    S->Array[S->TopOfStack] = X;
}

ElementType Top(ArrayStack S)
{
    if (IsEmpty(S))
    {
        //TODO error
        return 0;
    }
    return S->Array[S->TopOfStack];
}

void Pop(ArrayStack S)
{
    if (IsEmpty(S)) {
        //TODO error
        return;
    }
    S->TopOfStack--;
}

ElementType TopAndPop(ArrayStack S)
{
    if (IsEmpty(S)) {
        //TODO error
        return 0;
    }

    // S->Array[S->TopOfStack--]; and S->Array[(S->TopOfStack)--]

    ElementType element = Top(S);
    Pop(S);
    return element;
}


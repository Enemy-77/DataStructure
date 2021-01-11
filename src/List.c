#include "List.h"
#include "fatal.h"
#include <stdlib.h>

struct Node {
    ElementType Element;
    Position Next;
};

List MakeEmpty(List L)
{
    if (L != NULL)
    {
        DeleteList(L);
    }
    L = (List)malloc(sizeof(struct Node));
    if (L == NULL)
    {
        FatalError("Out Of Memory!");
    }
    L->Element = 0;
    L->Next = NULL;
    return L;
}

ElementType IsEmpty(List L)
{
    return L->Next == NULL;
}

ElementType IsLast(Position P, List L)
{
    return P->Next == NULL;
}

Position Find(ElementType X, List L)
{
    Position P;
    P = L->Next;
    while (P != NULL && P->Element != X)
    {
        P = P->Next;
    }
    return P;
}

void Delete(ElementType X, List L)
{
    Position P;
    P = FindPrevious(X, L);
    if (P == NULL)
        return;
    P->Next = P->Next->Next;
}

Position FindPrevious(ElementType X, List L)
{
    Position P;
    P = L;
    while (P->Next != NULL && P->Next->Element != X)
    {
        P = P->Next;
    }
    return P;
}

void Insert(ElementType X, List L, Position P)
{
    Position TmpCell;
    TmpCell = (Position)malloc(sizeof(struct Node));

    if (TmpCell == NULL)
        FatalError("out of space!");
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

void DeleteList(List L)
{
    Position P, Tmp;
    P = L->Next;
    L->Next = NULL;
    while (P != NULL)
    {
        Tmp = P->Next;
        free(P);
        P = Tmp;
    }
}

Position Header(List L)
{
    return L;
}

Position First(List L)
{
    return L->Next;
}

Position Advance(Position P)
{
    return P->Next;
}

ElementType Retrieve(Position P)
{
    return P->Element;
}


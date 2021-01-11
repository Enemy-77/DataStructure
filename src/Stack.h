
#ifndef STACK_H
#define STACK_H

typedef int ElementType;


struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int Empty(Stack S);
Stack CreateStack();
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType x, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);


#endif
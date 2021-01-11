#pragma once

#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

typedef int ElementType;

struct StackRecord;
typedef struct StackRecord* ArrayStack;

int IsEmpty(ArrayStack S);
int IsFull(ArrayStack S);
ArrayStack CreateStack(int MaxElements);
void DisposeStack(ArrayStack S);
void MakeEmpty(ArrayStack S);
void Push(ElementType X, ArrayStack S);
ElementType Top(ArrayStack S);
void Pop(ArrayStack S);
ElementType TopAndPop(ArrayStack S);

#endif
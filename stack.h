/******************************************************************************
 *
 * File Name: stack.h
 * Authors:    Group 29 AED 2017/2018 2S
 * Last modified: 2018-03-30
 * 
 * COMMENTS
 *		Function prototype to implement a stack array implementation
 *
 *****************************************************************************/



#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>

typedef struct _stack Stack;

Stack* initStack(int);
int testFull(Stack*); 
int testEmpty(Stack*); 
void PushStack(Stack*, int); 
int PopStack(Stack*);
int GetSize(Stack*);
int FindStack (Stack*, Stack*, int, int);
int ReadEntry(Stack*, int);
void FreeStack(Stack*);

#endif 

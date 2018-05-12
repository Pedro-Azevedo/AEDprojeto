/******************************************************************************
 *
 * File Name: write.c
 * Authors:    Group 29 AED 2017/2018 2S
 * Last modified: 2018-03-30
 *
 * COMMENTS
 *		Implements functions defined in stack.h
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

struct _stack{
	int top; 
	int size;
	int* coords; 
};


/******************************************************************************
 * initStack()
 *
 * Arguments: size -> capacity of stack
 * 
 * Returns: the stack created
 * 
 * Side-Effects: none
 *
 * Description: allocates memory and initializes a stack
 *
 *****************************************************************************/


Stack* initStack(int size)
{
	Stack* paths=NULL; 
	paths=(Stack*)calloc(1, sizeof(Stack)); 
	paths->size=size; 
	paths->top=-1;
	paths->coords=(int*)calloc(size, sizeof(int)); 
	return paths; 
}


/******************************************************************************
 * testFull()
 *
 * Arguments: paths -> stack
 * 
 * Returns: TRUE -> stack is full; FALSE -> stack is not full;
 * 
 * Side-Effects: none
 *
 * Description: tests if stack is full
 *
 *****************************************************************************/

 
int testFull (Stack* paths)
{
	return ((paths->top)==(paths->size)-1);  
}


/******************************************************************************
 * testEmpty()
 *
 * Arguments: paths -> stack
 * 
 * Returns: TRUE -> stack is empty; FALSE -> stack is not empty;
 * 
 * Side-Effects: none
 *
 * Description: tests if stack is empty
 *
 *****************************************************************************/

int testEmpty (Stack* paths)
{
	return (paths->top==-1);
}


/******************************************************************************
 * PushStack()
 *
 * Arguments: paths -> stack
 * 			  item -> integer to push
 * 
 * Returns: void
 * 
 * Side-Effects: none
 *
 * Description: puts an item in Stack
 *
 *****************************************************************************/

void PushStack (Stack* paths, int item)
{
	if(testFull(paths))
		return; 
	paths->coords[++(paths->top)]=item; 
	return;
} 


/******************************************************************************
 * PopStack()
 *
 * Arguments: paths -> stack
 * 
 * Returns: item to remove from the stack;
 * 
 * Side-Effects: none
 *
 * Description: removes an item from the stack
 *
 *****************************************************************************/

int PopStack(Stack* paths)
{
	if(testEmpty(paths))
		return INT_MIN; 
	return (paths->coords[(paths->top)--]); 
}


int GetSize(Stack* paths)
{
	return paths->size;
}


int FindStack (Stack* lpaths, Stack*cpaths, int _l, int _c)
{
	int i=0, j=0; 
	for(i=0, j=0; i<=(lpaths->top) && j<=(cpaths->top); i++, j++)
	{
		if(((lpaths->coords[i])==_l) && ((cpaths->coords[j])==_c))
			return 1;
	}
	return 0;
}


int ReadEntry(Stack* paths, int i)
{
	return paths->coords[i];
}

void FreeStack(Stack* paths)
{
	free(paths->coords);
	free(paths);
}

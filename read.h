
/******************************************************************************
 *
 * File Name: read.h
 * Authors:    Group 29 AED 2017/2018 2S
 * Last modified: 2018-03-28
 * 
 * COMMENTS
 *		Function prototype for reading file and produce solution
 *
 *****************************************************************************/



#ifndef READ_H_INCLUDED
#define READ_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_WORD 10000
#define Item void*


typedef struct _tableinfo tableinfo;

void path(char*);
void solve (FILE*); 
int* filltable(char*); 
void memory_allocation_error(void);

#endif 

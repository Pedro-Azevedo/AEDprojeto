
/******************************************************************************
 *
 * File Name: read.h
 * Authors:    Group 29 AED 2017/2018 2S
 * Last modified: 2018-03-28
 * 
 * COMMENTS
 *		Function prototype for reading file and fill information
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

void solve (FILE*); 
tableinfo fill_info_table(char*);
int* fill_table_line(char*, int); 
void memory_allocation_error(char*);

#endif 

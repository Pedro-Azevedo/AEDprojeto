
/******************************************************************************
 *
 * File Name: read.h
 * Authors:    Group 29 AED 2017/2018 2S
 * Last modified: 2018-03-30
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


typedef struct _tableinfo tableinfo;

void solve (FILE*, FILE*); 
tableinfo fill_info_table(FILE*);
int getL (tableinfo *info);
int getC (tableinfo *info); 
int lget (tableinfo *info); 
int cget (tableinfo *info);
int kget (tableinfo *info);
int l2get (tableinfo *info);
int c2get (tableinfo *info); 


#endif 

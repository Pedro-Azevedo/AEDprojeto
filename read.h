
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

/*Macros to access the vector with the information to solve the problem*/
#define L 0
#define C 1
#define l 2
#define c 3
#define k 4
#define l2 5
#define c2 6

/*Macros to access the vector with the dimensions of the table to use*/
#define down 0
#define right 1
#define up 2
#define left 3
#define height 4
#define width 5


void solve (FILE*, FILE*); 
int fill_info(FILE*, int*);
int well_defined_problem(int*);
int well_bound_test(int, int, int, int);
int maxint (int, int); 
int minint (int, int); 
void boundaries(int*, int*);
void alloc_table(int***, int*);
void fill_table(int**, int*, int*, FILE*); 
void free_table(int**, int*); 
void no_solution(FILE*, FILE*, int*); 


#endif 

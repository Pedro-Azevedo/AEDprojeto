
/******************************************************************************
 *
 * File Name: write.h
 * Authors:    Group 29 AED 2017/2018 2S
 * Last modified: 2018-03-30
 * 
 * COMMENTS
 *		Function prototype for solving the problem tasks
 *
 *****************************************************************************/



#ifndef WRITE_H_INCLUDED
#define WRITE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "read.h"


void decision (int*, int*, int**, FILE*);
int sum(int*, int*, int**);
int max(int*, int*, int**); 
int upleft(int, int); 
int downright(int, int, int);
void walk (int*, int*, int**, FILE*);
void write_solution_info(FILE*, int*, int);


#endif 



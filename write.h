
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


void decision (tableinfo, int**, FILE*);
int sum(tableinfo, int**);
int max(tableinfo, int**); 
int upleft(int, int); 
int downright(int, int, int);
void walk (tableinfo, int**, FILE*);
int well_defined_problem(tableinfo);
int well_bound_test(int, int, int, int);
void write_solution_info(FILE*, tableinfo, int);
int uppertrianglesum(int**, tableinfo, int, int);
int lowertrianglesum(int**, tableinfo, int, int); 
void uppertrianglemax(int**, tableinfo, int, int, int*);
void lowertrianglemax(int**, tableinfo, int, int, int*); 


#endif 



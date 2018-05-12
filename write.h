
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
#include "stack.h"

extern int output_energy;
extern int LOL;

void decision (int*, int*, int**, FILE*);
int solvepath(int, int, int, int, int, int*, int**, Stack*, Stack*);
void maximumenergy(int, int, int, int, int*, int**, Stack*, Stack*);
int allowed(int*, int*, Stack*, Stack*, int*, int*, int*, int*, int, int);
void checkdir(int*, int*, int*, int*, int, int, int, int, int, int, int*, int*, int*, int**);
int sum(int, int, int, int*, int**, Stack*, Stack*);
int upleft(int, int); 
int downright(int, int, int);
void walk (Stack*, Stack*, int, int, int**, FILE*);
void write_solution_info(FILE*, int*, int);
int checkpath(int, int, int, int, int, int*, Stack*, Stack*);

#endif 




/******************************************************************************
 *
 * File Name: read.c
 * Authors:    Group 29 AED 2017/2018 2S
 * Last modified: 2018-03-30
 *
 * COMMENTS
 *		Implements fucntions defined in paths.h
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read.h"
#include "write.h"

struct _tableinfo{
	int L; 
	int C;
	int l;
	int c;
	int k;
	int l2;
	int c2;
};


void decision (tableinfo info, int** table, FILE* output)
{
	int goal=0; 
	if(info.k>0)
	{
		goal = sum(info, table);
		write_solution_info(output, info, goal); 
	}
	else if(info.k<0)
	{
	    goal = max(info, table); 
	    write_solution_info(output, info, goal);
	}
	else
		walk(info, table, output); 
	return;
}


int sum (tableinfo info, int** table)
{
	int sum=0;
	int up=0, down=0, left=0, right=0;
	int radius=0; 
	radius=info.k;
	
	boundaries (&left, &right, &up, &down, radius, info); 
	sum+=uppertrianglesum(left, right, up, table, info, radius);
	sum+=lowertrianglesum(left, right, down, table, info, radius);
		
	return sum; 
}


int uppertrianglesum (int left, int right, int up, int**table, tableinfo info, int radius)
{ 
	int i=0, j=0;
	int sum=0;
	
	for(i=info.l-1; i>=up; i--)
	{
		for(j=left; j<=right; j++)
		{
			if(i==info.l-1 && j==info.c-1)
				continue;
			if(table[i][j]>0)
				sum+=table[i][j];	
		}
		radius--;	
		left= upleft(info.c-1, radius);
		right=downright(info.c-1, radius, info.C-1);
	}
	
	return sum;
}



int lowertrianglesum (int left, int right, int down, int**table, tableinfo info, int radius)
{ 
	int i=0, j=0;
	int sum=0;
	
	for(i=info.l-1+1; i<=down; i++)
	{
		radius--; 
		left= upleft(info.c-1, radius);
		right=downright(info.c-1, radius, info.C-1);
		for(j=left; j<=right; j++)
		{
			if(table[i][j]>0)
				sum+=table[i][j];	
		}
	}
	
	return sum;
}



int upleft (int pos, int r)
{
	int boundary=0; 
	if(pos-r<0)
		boundary=0; 
	else
		boundary=pos-r;
	
	return boundary;
}


int downright (int pos, int r, int lim)
{
	int boundary=0; 
	if(pos+r>lim)
		boundary=lim; 
	else
		boundary=pos+r; 
	
	return boundary;
}


int max (tableinfo info, int** table)
{
	int max=0; 
	int up=0, down=0, left=0, right=0;
	int radius=0; 
	radius= - info.k;
	
	boundaries (&left, &right, &up, &down, radius, info); 

	uppertrianglemax(left, right, up, table, info, radius, &max);
	lowertrianglemax(left, right, down, table, info, radius, &max);
	
	return max;
}


void uppertrianglemax (int left, int right, int up, int**table, tableinfo info, int radius, int* max)
{
	int i=0, j=0;
	
	for(i=info.l-1; i>=up; i--)
	{
		for(j=left; j<=right; j++)
		{
			if(i==info.l-1 && j==info.c-1)
				continue;
			if(table[i][j]>(*max))
				(*max)=table[i][j];	
		}
		radius--;	
		left= upleft(info.c-1, radius);
		right=downright(info.c-1, radius, info.C-1);
	}
}



void lowertrianglemax (int left, int right, int down, int**table, tableinfo info, int radius, int* max)
{ 
	int i=0, j=0;
	
	for(i=info.l-1+1; i<=down; i++)
	{
		radius--; 
		left= upleft(info.c-1, radius);
		right=downright(info.c-1, radius, info.C-1);
		for(j=left; j<=right; j++)
		{
			if(table[i][j]>(*max))
				(*max)=table[i][j];	
		}
	}
}




void boundaries (int* left, int* right, int* up, int*down, int radius, tableinfo info)
{
	*left=upleft(info.c-1, radius);  
	*right=downright(info.c-1, radius, info.C-1);
	*up=upleft(info.l-1, radius);
	*down=downright(info.l-1, radius, info.L-1);
}


void walk(tableinfo info, int** table, FILE*output)
{
	int i=0, j=0; 
	
	write_solution_info(output, info, 0); 
	
	i=info.l-1;
	j=info.c-1;
	
	while(i!=info.l2-1)
    {
		if(i<info.l2-1)
			i++;
		else
			i--;
			
		fprintf(output, "%d %d %d\n", i+1, j+1, table[i][j]); 
	}
	
	
	while(j!=info.c2-1)
	{
		if(j<info.c2-1)
			j++;
		else
			j--; 
		fprintf(output, "%d %d %d\n", i+1, j+1, table[i][j]); 
	}
	
		
}


int well_defined_problem(tableinfo info)
{
	int ret=0; 
	
	ret=well_bound_test(info.l-1, info.c-1, info.L-1, info.C-1); 
	
	if(ret==-1)
		return ret;
	
	if(info.k==0) 
		ret=well_bound_test(info.l2-1, info.c2-1, info.L-1, info.C-1); 
	
	return ret;
	
}


int well_bound_test(int l, int c, int L, int C)
{
	int ret=0; 
	
	if(l<0 || l>L || c<0 || c>C)
		ret=-1;
	
	return ret;
	
}



void write_solution_info(FILE* output, tableinfo info, int res)
{
	if(info.k==0)
		fprintf(output, "%d %d %d %d %d %d %d\n", info.L, info.C, info.l, info.c, info.k, info.l2, info.c2); 
	
	else
	{	
		if(res==-1)
			fprintf(output, "%d %d %d %d %d\n", info.L, info.C, info.l, info.c, info.k); 
		else
			fprintf(output, "%d %d %d %d %d %d\n", info.L, info.C, info.l, info.c, info.k, res); 
	}
	return;
}

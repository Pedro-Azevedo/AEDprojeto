/******************************************************************************
 *
 * File Name: write.c
 * Authors:    Group 29 AED 2017/2018 2S
 * Last modified: 2018-03-30
 *
 * COMMENTS
 *		Implements fucntions defined in write.h
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read.h"
#include "write.h"


/******************************************************************************
 * decision()
 *
 * Arguments: info - array with the information to solve the problem
 *            dimensions - array with the size of table
 * 			  table - table with the values. 
 * 			  output - output file to write the solution
 * 
 * Returns: (void)
 * 
 * Side-Effects: according to the value of info[k], redirects the problem to to ther functions
 *
 * Description: function to solve the problem
 *
 *****************************************************************************/


void decision (int* info, int* dimensions, int** table, FILE* output)
{
	int goal=0; /* integer to store the solution if info[k]!=0 */
	
	/*info[k] positive -> sum problem */
	if(info[k]>0)
	{
		goal = sum(info, dimensions, table);
		write_solution_info(output, info, goal); 
	}
	
	/*info[k] negative -> max problem */
	else if(info[k]<0)
	{
	    goal = max(info, dimensions, table); 
	    write_solution_info(output, info, goal);
	}
	
	/*info[k] zero -> path problem */
	else
		walk(info, dimensions, table, output); 
	return;
}


/******************************************************************************
 * sum()
 *
 * Arguments: info - array with the information to solve the problem
 *            dimensions - array with the size of table
 * 			  table - table with the values. 
 * 
 * Returns: the value sum
 * 
 * Side-Effects: none
 *
 * Description: function to calculate the sum of the element that are at a certain
 *              distance from a pivot 
 *
 *****************************************************************************/

int sum (int* info, int* dimensions, int** table)
{
	int sum=0, i=0, j=0, transfl=0, transfc=0; 
	
	/*Transformation of coordinates of the pivot (l, c) on the original map to the
	 * considered table*/
	transfl=info[l]-1-dimensions[up];
	transfc=info[c]-1-dimensions[left];
	
	/*Go through the table*/
	for(i=0; i<dimensions[height]; i++)
	{
		for(j=0; j<dimensions[width]; j++)
		{
			/*Skip the pivot*/
			if(i==transfl && j==transfc)
				continue;
				
			/*We sum the element if its distance from the pivot is less or equal info[k]*/
			if(abs(transfl-i)+abs(transfc-j)<=info[k]) 
			{
				/*We sum teh element if it is positive*/
				if(table[i][j]>0)
					sum+=table[i][j];
			} 
		}
	}
	
	return sum; 
}


/******************************************************************************
 * upleft()
 *
 * Arguments: pos - pivot in the table
 * 			  r - maximum distance to the pivot
 * 
 * Returns: the maximum limit either above or on the left of the pivot
 * 
 * Side-Effects: none
 *
 * Description: function that calculates the maximum value to consider either
 *              above or on the left of the pivot. It serves to truncate the
 *              value pos+r if it is outside the table. 
 *
 *****************************************************************************/


int upleft (int pos, int r)
{
	int boundary=0;
	
	/*if the value pos-r is less than zero (it is either above or on the left
	 * of the table) we assign it to zero */
	if(pos-r<0)
		boundary=0; 
	
	/*else we consider that value*/
	else
		boundary=pos-r;
	
	return boundary;
}


/******************************************************************************
 * downright()
 *
 * Arguments: pos - pivot in the table
 * 			  r - maximum distance to the pivot
 *            lim - limit of the table (L or C)
 * 
 * Returns: the maximum limit either under or on the right of the pivot
 * 
 * Side-Effects: none
 *
 * Description: function that calculates the maximum value to consider either
 *              under or on the right of the pivot. It serves to truncate the
 *              value pos+r if it is outside the table. 
 *
 *****************************************************************************/

int downright (int pos, int r, int lim)
{
	int boundary=0; 
	
	/*if the value pos+r is more than lim (it is either under or on the right
	 * of the table) we assign it to this limit (colums-1) */
	if(pos+r>lim)
		boundary=lim; 
		
	/*else we consider that value*/
	else
		boundary=pos+r; 
	
	return boundary;
}



/******************************************************************************
 * max()
 *
 * Arguments: info - array with the information to solve the problem
 *            dimensions - array with the size of table
 * 			  table - table with the values. 
 * 
 * Returns: the value max
 * 
 * Side-Effects: none
 *
 * Description: function to calculate the max element that is at a certain
 *              distance from a pivot 
 *
 *****************************************************************************/

int max (int* info, int*dimensions, int** table)
{
	int max=0, i=0, j=0, transfl=0, transfc=0; 
		
	/*Transformation of coordinates of the pivot (l, c) on the original map to the
	 * considered table*/
	 
	transfl=info[l]-1-dimensions[up];
	transfc=info[c]-1-dimensions[left];

	/*Go through the table*/
	for(i=0; i<dimensions[height]; i++)
	{ 
		for(j=0; j<dimensions[width]; j++)
		{
			/*Skip the pivot*/
			if(i==transfl && j==transfc)
				continue;
				
			/*We consider the element if its distance from the pivot is less or equal info[k]*/
			if(abs(transfl-i)+abs(transfc-j)<=abs(info[k])) 
			{
				/*If the element is great than "max" it is the new max*/
				if(table[i][j]>max)
					max=table[i][j];
			} 
		}
	}
	return max; 
}

/******************************************************************************
 * walk()
 *
 * Arguments: info - array with the information to solve the problem
 *            dimensions - array with the size of table
 * 			  table - table with the values. 
 *            output - output file to write the solution
 * 
 * Returns: void
 * 
 * Side-Effects: writing the steps of the path on the output file
 *
 * Description: function to solve the problem of going from a point of the table
 *              to other
 *
 *****************************************************************************/

void walk(int* info, int* dimensions, int** table, FILE*output)
{
	int i=0, j=0; 
	
	/* We start by writing the first line of the problem*/
	write_solution_info(output, info, 0); 
	
	/*We set the iteration variables to the initial point*/
	/*We apply a Transformation of Coordinates*/
	i=info[l]-1-dimensions[up];
	j=info[c]-1-dimensions[left];
	
	/*We start to go through the lines until we reach info.l2-1*/
	while(i!=info[l2]-1-dimensions[up])
    {
		/*if the point (l,c) is above (l2, c2) we need to go down*/
		if(i<info[l2]-1-dimensions[up])
			i++;
			
		/*else, we go up*/
		else
			i--;
			
	    /*for each iteration we print on the output file the coordinates we
	     * are before the next iteration. We also print the value of [i][j]
	     * on the table. Note that we reverse the transformation of coordinates*/		
		fprintf(output, "%d %d %d\n", i+1+dimensions[up], j+1+dimensions[left], table[i][j]); 
	}
	
	/*Now we go through the columns until we reach info.c2-1*/
	while(j!=info[c2]-1-dimensions[left])
	{
		/*if the point (l,c) is on the left of (l2, c2) we need to go to the right*/
		if(j<info[c2]-1-dimensions[left])
			j++;
		
		/*else, we go to the left*/
		else
			j--; 
		
        /*Same case as listed above*/
		fprintf(output, "%d %d %d\n", i+1+dimensions[up], j+1+dimensions[left], table[i][j]); 
	}
	
	return;
		
}


/******************************************************************************
 * write_solution_info()
 *
 * Arguments: output - file to write the solution
 * 			  info - array with the information to solve the problem
 * 			  res - parameter the solution value or -1 (problem without solution)
 *  
 * 
 * Returns: void
 * 
 * Side-Effects: none
 *
 * Description: writes the information of the problem on the output file and the
 *  			result in the case of valid parameters and info[k]!=0
 *
 *****************************************************************************/


void write_solution_info(FILE* output, int* info, int res)
{
	/*if info[k] is zero we repeat the first line of the problem either if it has solution or not*/

	if(info[k]==0) 
		fprintf(output, "%d %d %d %d %d %d %d\n", info[L], info[C], info[l], info[c], info[k], info[l2], info[c2]);
	
	/* else if info[k]!=0 and the problem doesn't have a solution we only print the info*/
	else if(res==-1)
		fprintf(output, "%d %d %d %d %d\n", info[L], info[C], info[l], info[c], info[k]);
	
	/*if info[k]=0 and it has solution we print the info and the result*/
	else
		fprintf(output, "%d %d %d %d %d %d\n", info[L], info[C], info[l], info[c], info[k], res);

	return;
}

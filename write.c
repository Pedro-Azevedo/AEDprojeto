
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



/******************************************************************************
 * decision()
 *
 * Arguments: info - structure with the information to solve the problem
 * 			  table - table with the values. 
 * 			  output - output file to write the solution
 * 
 * Returns: (void)
 * 
 * Side-Effects: according to the value of info.k, redirects the problem to to ther functions
 *
 * Description: function to solve the problem
 *
 *****************************************************************************/


void decision (tableinfo info, int** table, FILE* output)
{
	int goal=0; /* integer to store the solution if info.k!=0 */
	
	/*info.k positive -> sum problem */
	if(info.k>0)
	{
		goal = sum(info, table);
		write_solution_info(output, info, goal); 
	}
	
	/*info.k negative -> max problem */
	else if(info.k<0)
	{
	    goal = max(info, table); 
	    write_solution_info(output, info, goal);
	}
	
	/*info.k zero -> path problem */
	else
		walk(info, table, output); 
	return;
}


/******************************************************************************
 * sum()
 *
 * Arguments: info - structure with the information to solve the problem
 * 			  table - table with the values. 
 * 
 * Returns: the value sum
 * 
 * Side-Effects: calculates the maximum and minimum lines to consider in the
 *               sum
 *
 * Description: function to calculate the sum of the element that are at a certain
 *              distance (radius) from a pivot 
 *
 *****************************************************************************/

int sum (tableinfo info, int** table)
{
	int sum=0, up=0, down=0, radius=0; 
	
	/*Assign to radius the distance from the pivot to consider*/
	radius=info.k;
	
	/*Determine the upper and lower lines to consider in the sum*/
	/*we use info.l-1 because the vector is numbered from 0 to L-1 
	 * but on the info we refer the points using [1,L]*/
	up=upleft(info.l-1, radius); 
	down=downright(info.l-1, radius, info.L-1);
	
	/*Strategy: we will split the problem into 2 separate problem: 
	 * first: we'll determine the sum in the lines above the line with
	 *        the pivot (including the line with the pivot)
	 * second: we'll determine the sum in the lines below the line with
	 *         the pivot
	*/
	sum+=uppertrianglesum(table, info, up, radius);
	sum+=lowertrianglesum(table, info, down, radius);
		
	/*Note that if we only find negative values, sum will be zero*/
	return sum; 
}


/******************************************************************************
 * upleft()
 *
 * Arguments: pos - pivot in the table
 * 			  radius - maximum distance to the pivot
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
 * 			  radius - maximum distance to the pivot
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
 * uppertrianglesum()
 *
 * Arguments: table - table with the values. 
 *            info - structure with the information to solve the problem
 *            up - minimum line on the table to consider
 *            radius - distance from the pivot to consider calculating the sum
 * 
 * Returns: the value sum
 * 
 * Side-Effects: none
 *
 * Description: function to calculate the sum of the element that are at a certain
 *              distance (radius) from a pivot on the lines above it
 *
 *****************************************************************************/

int uppertrianglesum (int**table, tableinfo info, int up, int radius)
{ 
	int i=0, j=0, left=0, right=0, sum=0;
	
	/*we'll iterate from the line of the pivot [info.l - 1 (-1 because of the
	 * numbering of the lines and columns being [0, L-1] and [0, C-1], but we
	 * access them using [1, L] and [1,C])*/
	  
	for(i=info.l-1; i>=up; i--)
	{
		left= upleft(info.c-1, radius); /*determine the minimum column to consider*/
		right=downright(info.c-1, radius, info.C-1); /*determine the maximum column to consider*/
		
		for(j=left; j<=right; j++)
		{
			/*Skip the pivot*/
			if(i==info.l-1 && j==info.c-1)
				continue;
			
			/*If the value [i,j] on the table is positive, we add it to the sum*/
			if(table[i][j]>0)
				sum+=table[i][j];	
		}
		
		/*Now we decrement the variable radius because as we walk to lines farther from the
		 * pivot, the distance to go for the left or for the right shrinks (we need to 
		 * respect the number of steps we can walk -> input value i.e. initial value of radius)
		 * */
		radius--;	
	}
	
	return sum;
}


/******************************************************************************
 * lowertrianglesum()
 *
 * Arguments: table - table with the values. 
 *            info - structure with the information to solve the problem
 *            down - maximum line on the table to consider
 *            radius - distance from the pivot to consider calculating the sum
 * 
 * Returns: the value sum
 * 
 * Side-Effects: none
 *
 * Description: function to calculate the sum of the element that are at a certain
 *              distance (radius) from a pivot on the lines below it
 *
 *****************************************************************************/


int lowertrianglesum (int**table, tableinfo info, int down, int radius)
{ 
	int i=0, j=0, left=0, right=0, sum=0;
	
	/*we'll iterate from the line below the pivot [info.l - 1 +1 (-1 because of the
	 * numbering of the lines and columns being [0, L-1] and [0, C-1], but we
	 * access them using [1, L] and [1,C]; +1 to go below)*/
	 
	for(i=info.l-1+1; i<=down; i++)
	{
		/*Now we decrement the variable radius because as we walk to lines farther from the
		 * pivot, the distance to go for the left or for the right shrinks (we need to 
		 * respect the number of steps we can walk -> input value i.e. initial value of radius)
		 * */
		radius--; 
		left= upleft(info.c-1, radius); /*determine the minimum column to consider*/
		right=downright(info.c-1, radius, info.C-1); /*determine the maximum column to consider*/
		for(j=left; j<=right; j++)
		{
			/*If the value [i,j] on the table is positive, we add it to the sum*/
			if(table[i][j]>0)
				sum+=table[i][j];	
		}
	}
	
	return sum;
}


/******************************************************************************
 * max()
 *
 * Arguments: info - structure with the information to solve the problem
 * 			  table - table with the values. 
 * 
 * Returns: the value max
 * 
 * Side-Effects: calculates the maximum and minimum lines to consider in the
 *               claclulation of the max value
 *
 * Description: function to calculate the max element that is at a certain
 *              distance (radius) from a pivot 
 *
 *****************************************************************************/

int max (tableinfo info, int** table)
{
	int max=0, up=0, down=0, radius=0; 
	
	/*Assign to radius the distance from the pivot to consider
	 * minus sign because info.k is negative */
	radius= - info.k;
	
	/*Determine the upper and lower lines to consider in the sum*/
	/*we use info.l-1 because the vector is numbered from 0 to L-1 
	 * but on the info we refer the points using [1,L]*/
	up=upleft(info.l-1, radius); 
	down=downright(info.l-1, radius, info.L-1);
	

    /*Strategy: we will split the problem into 2 separate problem: 
	 * first: we'll check the lines above the line with the pivot 
	 *       (including the line with the pivot)
	 * second: we'll check lines below the line with the pivot
	*/
	uppertrianglemax(table, info, up, radius, &max);
	lowertrianglemax(table, info, down, radius, &max);
	
	/*Note that if we only find negative values, max will be zero*/
	
	return max;
}


/******************************************************************************
 * uppertrianglemax()
 *
 * Arguments: table - table with the values. 
 *            info - structure with the information to solve the problem
 *            up - minimum line on the table to consider
 *            radius - distance from the pivot to consider calculating the max
 *            max - max value (passed by reference)
 * 
 * Returns: void
 * 
 * Side-Effects: none
 *
 * Description: function to look for the max element that is at a certain
 *              distance (radius) from a pivot on the lines above it
 *
 *****************************************************************************/

void uppertrianglemax (int**table, tableinfo info, int up, int radius, int* max)
{
	int i=0, j=0, left=0, right=0;
	
	/*we'll iterate from the line of the pivot [info.l - 1 (-1 because of the
	 * numbering of the lines and columns being [0, L-1] and [0, C-1], but we
	 * access them using [1, L] and [1,C])*/ 
	for(i=info.l-1; i>=up; i--)
	{
		left= upleft(info.c-1, radius); /*determine the minimum column to consider*/
		right=downright(info.c-1, radius, info.C-1); /*determine the maximum column to consider*/
		
		for(j=left; j<=right; j++)
		{
			/*Skip the pivot*/
			if(i==info.l-1 && j==info.c-1)
				continue;
			/*If the value [i,j] on the table is greater than max, we have a new max value*/
			if(table[i][j]>(*max))
				(*max)=table[i][j];	
		}
		
		/*Now we decrement the variable radius because as we walk to lines farther from the
		 * pivot, the distance to go for the left or for the right shrinks (we need to 
		 * respect the number of steps we can walk -> input value i.e. initial value of radius)
		 * */
		radius--;	
	}
}


/******************************************************************************
 * lowertrianglemax()
 *
 * Arguments: table - table with the values. 
 *            info - structure with the information to solve the problem
 *            down - maximum line on the table to consider
 *            radius - distance from the pivot to consider calculating the max
 *            max - max value (passed by reference)
 * 
 * Returns: void
 * 
 * Side-Effects: none
 *
 * Description: function to look for the max element that is at a certain
 *              distance (radius) from a pivot on the lines below it
 *
 *****************************************************************************/

void lowertrianglemax (int**table, tableinfo info, int down, int radius, int* max)
{ 
	int i=0, j=0, left=0, right=0;
	
	/*we'll iterate from the line below the pivot [info.l - 1 +1 (-1 because of the
	 * numbering of the lines and columns being [0, L-1] and [0, C-1], but we
	 * access them using [1, L] and [1,C]; +1 to go below)*/
	for(i=info.l-1+1; i<=down; i++)
	{
		/*Now we decrement the variable radius because as we walk to lines farther from the
		 * pivot, the distance to go for the left or for the right shrinks (we need to 
		 * respect the number of steps we can walk -> input value i.e. initial value of radius)
		 * */
		radius--; 
		left= upleft(info.c-1, radius); /*determine the minimum column to consider*/
		right=downright(info.c-1, radius, info.C-1); /*determine the maximum column to consider*/
		for(j=left; j<=right; j++)
		{
			if(table[i][j]>(*max))
				(*max)=table[i][j];	
		}
	}
}

	

/******************************************************************************
 * walk()
 *
 * Arguments: info - structure with the information to solve the problem
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

void walk(tableinfo info, int** table, FILE*output)
{
	int i=0, j=0; 
	
	/* We start by writing the first line of the problem*/
	write_solution_info(output, info, 0); 
	
	/*We set the iteration variables to the initial point*/
	/* Note that we use (info.l- 1, info.c-1) because the
	 * numbering of the lines and columns is [0, L-1] and 
	 * [0, C-1],but we access the table using [1, L] and [1,C]*/
	i=info.l-1;
	j=info.c-1;
	
	/*We start to go through the lines until we reach info.l2-1*/
	while(i!=info.l2-1)
    {
		/*if the point (l,c) is above (l2, c2) we need to go down*/
		if(i<info.l2-1)
			i++;
			
		/*else, we go up*/
		else
			i--;
			
	    /*for each iteration we print on the output file the coordinates we
	     * are before the next iteration. We also print the value of [i][j]
	     * on the table. Note that this time we use i+1 and j+1 for the same 
	     * reason mentioned above about the real limits of the table and the 
	     * limits we use to mention it*/		
		fprintf(output, "%d %d %d\n", i+1, j+1, table[i][j]); 
	}
	
	/*Now we go through the columns until we reach info.c2-1*/
	while(j!=info.c2-1)
	{
		/*if the point (l,c) is on the left of (l2, c2) we need to go to the right*/
		if(j<info.c2-1)
			j++;
		
		/*else, we go to the left*/
		else
			j--; 
		
        /*Same case as listed above*/
		fprintf(output, "%d %d %d\n", i+1, j+1, table[i][j]); 
	}
	
		
}


/******************************************************************************
 * well_defined_problem()
 *
 * Arguments: info - structure with the problem info
 * 			  
 * Returns: 0 -> SUCCESS (valid info); -1 -> UNSUCCESS
 * 
 * Side-Effects: uses other function to test if the point (l,c) is in the table.
 *               does the same with (l2, c2), if applicable
 *
 * Description: tests the informations of the problem
 *
 *****************************************************************************/


int well_defined_problem(tableinfo info)
{
	int ret=0; /*test variable*/
	
	/* Note that we use (info.l- 1, info.c-1) because the
	 * numbering of the lines and columns is [0, L-1] and 
	 * [0, C-1],but we access the table using [1, L] and [1,C]*/
	
	/*test if (l,c) is on the table*/
	ret=well_bound_test(info.l-1, info.c-1, info.L-1, info.C-1); 
	
	/*if it's not, we immediately return*/
	
	if(ret==-1)
		return ret;
		
	/*if it passed the previous test and info.k is 0, then we have 
	 * other pair (l2, c2) to test*/
	
	if(info.k==0) 
		ret=well_bound_test(info.l2-1, info.c2-1, info.L-1, info.C-1); 
	
	return ret;
	
}


/******************************************************************************
 * well_bound_test()
 *
 * Arguments: l and c - coordinates of the point to test 
 * 			  L - number of lines[1 to L] of the table
 * 			  C - number of columns[1 to C] of the table
 *  
 * 
 * Returns: 0 -> SUCCESS (valid info); -1 -> UNSUCCESS
 * 
 * Side-Effects: none
 *
 * Description: tests if the coordinates (l,c) of a point are within a table
 *
 *****************************************************************************/

int well_bound_test(int l, int c, int L, int C)
{
	int ret=0; 
	 
	if(l<0 || l>L || c<0 || c>C)
		ret=-1;
	
	return ret;
	
}


/******************************************************************************
 * write_solution_info()
 *
 * Arguments: output - file to write the solution
 * 			  info - structure with the information to solve the problem
 * 			  res - parameter the solution value or -1 (problem without solution)
 *  
 * 
 * Returns: void
 * 
 * Side-Effects: none
 *
 * Description: writes the information of the problem on the output file and the
 *  			result in the case of valid parameters and info.k!=0
 *
 *****************************************************************************/


void write_solution_info(FILE* output, tableinfo info, int res)
{
	/*if info.k is zero we repeat the first line of the problem either if it has solution or not*/
	if(info.k==0)
		fprintf(output, "%d %d %d %d %d %d %d\n", info.L, info.C, info.l, info.c, info.k, info.l2, info.c2); 
	
	else
	{
		/*invalid parameters -> problem without solution -> just print the information*/	
		if(res==-1)
			fprintf(output, "%d %d %d %d %d\n", info.L, info.C, info.l, info.c, info.k); 
		
		/*valid parameters -> problem with solution -> print the information plus the solution*/
		else
			fprintf(output, "%d %d %d %d %d %d\n", info.L, info.C, info.l, info.c, info.k, res); 
	}
	return;
}

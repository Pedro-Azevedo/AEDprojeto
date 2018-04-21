/******************************************************************************
 *
 * File Name: read.c
 * Authors:    Group 29 AED 2017/2018 2S
 * Last modified: 2018-03-30
 *
 * COMMENTS
 *		Implements fucntions defined in read.h
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read.h"
#include "write.h"

 

/******************************************************************************
 * solve()
 *
 * Arguments: input - input file to read to solve 
 * 			  output - output file to write the solution
 * Returns: (void)
 * Side-Effects: reads from the file, save the problem information on a 
 * 				 array, store memory for the table and fill it with 
 * 				 the info from the file. 
 * 				 It also works the information: tests the validity and calls 
 * 				 other functions to either solve the problem or to write on the 
 * 				 output file
 *
 * Description: solve the problem(s)
 *
 *****************************************************************************/

void solve (FILE* input, FILE* output)
{
	int info[7]={0}; /*array to store information to solve the problem*/
	int** table=NULL; /* map to store*/
	int def=0;
	int dimensions[7]={0}; /*array with dimensions for the map*/
	
	/*Read the file until there is no more problems to solve*/
	/*That is tested with the return value of fill_info_table */ 
	
	while (fill_info(input, info)==1)
	{ 	
		def=well_defined_problem(info); /*Test if the parameters are valid*/
		
		/*Problem with non valid parameters*/
		if(def==-1)
		{
			no_solution(input, output, info); 
			continue; /*Next problem*/
		}
		
		/*Valid problem: we proceed to solve it*/ 
		/*We don't need to allocate memory for all the map of the file just a region*/
		/*We need to determine the boundaries of the problem */ 
		boundaries(info, dimensions); 
		
		/*Allocate memory for the table and verify*/
		alloc_table(&table, dimensions);
		
		/*Fill the table with the information of the input file*/
		fill_table(table, dimensions, info, input);  
		
		/*Now that the table is filled, we analyse our info to solve the problem*/
		decision(info, dimensions, table, output);
		
		/*The problem was solved. Print an empty line to separate the next problem*/
		fprintf(output, "\n");
		
		/*Free the memory of the table for this problem*/
		free_table(table, dimensions); 
		/*Continue to the next problem*/
	}
	
	return; 
}



/******************************************************************************
 * fill_info_table()
 *
 * Arguments: input -> pointer to the file used to read the information of the problem. 
 *            info -> integer array to store the information of the problem
 * Returns: 1-> If the reading was successful; 0-> if it failed
 * Side-Effects: none
 *
 * Description: store in am array the information of the problem to solve
 *
 *****************************************************************************/
 
int fill_info (FILE* input, int* info)
 {
	int i=L;
			
	/*scan the information to the array*/
	while(i<=k)
	{
		if(fscanf(input, "%d", &info[i++])!=1)
			return 0; 	
	}
	/* if k is zero there are 2 more parameteres to store */
	if(info[k]==0)
	{
		while(i<=c2)
		{
			if(fscanf(input, "%d", &info[i++])!=1)
				return 0;
		}
	}
	return 1;
 }
 


/******************************************************************************
 * well_defined_problem()
 *
 * Arguments: info - pointer to structure with the problem info
 * 			  
 * Returns: 0 -> SUCCESS (valid info); -1 -> UNSUCCESS
 * 
 * Side-Effects: uses other function to test if the point (l,c) is in the table.
 *               does the same with (l2, c2), if applicable
 *
 * Description: tests the informations of the problem
 *
 *****************************************************************************/


int well_defined_problem(int* info)
{
	int ret=0; /*test variable*/
	
	/*test if (l,c) is on the table*/
	ret=well_bound_test(info[l], info[c], info[L], info[C]); 
	
	/*if it's not, we immediately return*/
	
	if(ret==-1)
		return ret;
		
	/*if it passed the previous test and info[k] is 0, then we have 
	 * other pair (l2, c2) to test*/
	
	if(info[k]==0) 
		ret=well_bound_test(info[l2], info[c2], info[L], info[C]); 
	
	return ret;
	
}


/******************************************************************************
 * well_bound_test()
 *
 * Arguments: _l and _c - coordinates of the point to test 
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

int well_bound_test(int _l, int _c, int _L, int _C)
{
	int ret=0; /*test variable*/
	
	/*We check if _l is in [1; L], if _c is in [1; C] and if 
	 * L and C are equal or great than 1*/
	 
	if(_l<1 || _l>_L || _c<1 || _c>_C || _L<1 || _C<1)
		ret=-1;
	
	return ret;
}


/******************************************************************************
 * maxint()
 *
 * Arguments: num1 and num2 - integers to compare 
 *  
 * 
 * Returns: num1 (if num1>num2) or num2 (else)
 * 
 * Side-Effects: none
 *
 * Description: compares two numbers and returns the greatest one
 *
 *****************************************************************************/


int maxint(int num1, int num2)
{
	if(num1>num2)
		return num1;
	return num2;
}


/******************************************************************************
 * mimint()
 *
 * Arguments: num1 and num2 - integers to compare 
 *  
 * 
 * Returns: num1 (if num1<num2) or num2 (else)
 * 
 * Side-Effects: none
 *
 * Description: compares two numbers and returns the smallest one
 *
 *****************************************************************************/

int minint(int num1, int num2)
{
	if(num1<num2)
		return num1;
	return num2;
}


/******************************************************************************
 * boundaries()
 *
 * Arguments: info - array with the info of the problem
 *            dimensions - array to store the dimensions of the table to use
 *  
 * 
 * Returns: void
 * 
 * Side-Effects: none
 *
 * Description: determines the size of the table to allocate in memory and 
 *              the respective boundaries in the original map (described in the file)
 *
 *****************************************************************************/

void boundaries(int* info, int* dimensions)
{
	/*If we are in a problem with info[k] is zero 
	 * our boundaries are determined by the points (l,c)
	 * and (l2, c2)
	 
	 * Note that we use (info.l- 1, info.c-1) because the
	 * numbering of the lines and columns is [0, L-1] and 
	 * [0, C-1],but we access the table using [1, L] and [1,C] */
	 
	if(info[k]==0)
	{
		dimensions[down]=maxint(info[l2]-1, info[l]-1); 
		dimensions[right]= maxint(info[c2]-1, info[c]-1); 
		dimensions[up]=minint(info[l2]-1, info[l]-1); 
		dimensions[left]=minint(info[c2]-1, info[c]-1);	
	}
	
	/*If we are in a problem with info[k] non zero then it will be
	 * info[k] that will determine the dimension of the table
	 * We are however limited by the corners of the original table 
	 * so we have to determine this values*/
		
	else
	{
		dimensions[down]=downright(info[l]-1, abs(info[k]), info[L]-1);  
		dimensions[right]=downright(info[c]-1, abs(info[k]), info[C]-1); 
		dimensions[up]=upleft(info[l]-1, abs(info[k]));
		dimensions[left]=upleft(info[c]-1, abs(info[k])); 
	}
	
	/*Calculate height and width of the table*/
	dimensions[height]= dimensions[down]-dimensions[up]+1; 
	dimensions[width]=dimensions[right]-dimensions[left]+1;
	
	return;
}


/******************************************************************************
 * alloc_table()
 *
 * Arguments: table - pointer to the matrix we are allocating memory for
 *            dimensions - array with the dimensions of the matrix
 *  
 * 
 * Returns: void
 * 
 * Side-Effects: none
 *
 * Description: allocates memory to the matrix to solve the problem
 * 
 *
 *****************************************************************************/


void alloc_table(int*** table, int*dimensions)
{
	int i=0;
	
	/*Allocate memory to the table and test it*/
	(*table)=(int**) calloc(dimensions[height], sizeof(int*));
	if((*table)==NULL)
		exit(0);
			
			
	/*Allocate memory for the lines of the table and test it*/
	for(i=0; i<dimensions[height]; i++)
	{
		(*table)[i]=(int*)calloc(dimensions[width], sizeof(int));
		if((*table)[i]==NULL)
			exit(0);
	}
	
	return;
}



/******************************************************************************
 * fill_table()
 *
 * Arguments: table - matrix to store the map on the file
 *            dimensions - array with the dimensions of the matrix
 * 			  info - array with the info of the problem
 * 			  input - input file to read
 * 
 * Returns: void
 * 
 * Side-Effects: none
 *
 * Description: fills the table with the map read form the input file
 * 
 *
 *****************************************************************************/


void fill_table(int** table, int* dimensions, int* info, FILE* input)
{
	int lines=0, cols=0, i=0, j=0, def=0;
	
	/*We need to read info[L]*info[C] integers*/
	
	for(i=0; i<info[L]; i++)
	{
		for(j=0; j<info[C]; j++)
		{	
			/*If we are not in the (sub-)table of the map that interests us, we skip the number*/
			if(i<dimensions[up] || i>dimensions[down] || j<dimensions[left] || j>dimensions[right]) 
			{
				if(fscanf(input, "%d", &def)!=1) 
					exit(0); 
			}
			
			/*Else: we scan it to the table*/	
			else
			{
				if(fscanf(input, "%d", &table[lines][cols++])!=1)
					exit(0);
				/*Test if we finished a line of the table and need to go to the next*/
				if(cols==dimensions[width]) 
				{
					lines++; /*increment lines*/
					cols=0; /*reset columns*/
				}
			}
		}
	}
	return;
}

/******************************************************************************
 * free_table()
 *
 * Arguments: table - matrix to free memory from 
 *            dimensions - array with the dimensions of the matrix
 * 
 * Returns: void
 * 
 * Side-Effects: none
 *
 * Description: frees the memory of the matrix 
 * 
 *
 *****************************************************************************/


void free_table(int** table, int* dimensions)
{
	int i=0; 
	/*Free the lines*/
	for(i=0; i<dimensions[height]; i++)
		free(table[i]);
	/*Free the matrix*/
	free (table);
	return;
}


/******************************************************************************
 * no_solution()
 *
 * Arguments: input - input file to read 
 *            output - output file to write to
 * 			  info - array with the info of the problem
 * 			  
 * 
 * Returns: void
 * 
 * Side-Effects: none
 *
 * Description: function to use when a problem doesn't have a solution
 * 
 *
 *****************************************************************************/

void no_solution(FILE* input, FILE* output, int* info)
{
	int def=-1, i=0; 
	
	write_solution_info(output, info, def); /*repeat the first line of the problem*/
	fprintf(output, "\n"); /*put an empty line, to separate from the next problem*/
	
	/*Skip the table */
	for(i=0; i<info[L]*info[C]; i++)
	{
		if(fscanf(input, "%d", &def)!=1)
			exit(0);
	}
	
	return;
}

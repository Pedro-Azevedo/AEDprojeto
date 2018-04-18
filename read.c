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


/*Structure to store the information of the problem*/
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
 * getL ()
 *
 * Arguments: info - pointer to structure with the problem information
 * Returns: parameter L of the structure
 * Side-Effects: exits the program
 *
 * Description: function to access the parameter L of the structure
 *
 *****************************************************************************/


int getL (tableinfo *info)
{
	return info->L;
}


/******************************************************************************
 * getC ()
 *
 * Arguments: info - pointer to structure with the problem information
 * Returns: parameter C of the structure
 * Side-Effects: exits the program
 *
 * Description: function to access the parameter C of the structure
 *
 *****************************************************************************/

int getC (tableinfo *info)
{
	return info->C;
}



/******************************************************************************
 * lget ()
 *
 * Arguments: info - pointer to structure with the problem information
 * Returns: parameter l of the structure
 * Side-Effects: exits the program
 *
 * Description: function to access the parameter l of the structure
 *
 *****************************************************************************/
 
int lget (tableinfo *info)
{
	return info->l;
}


/******************************************************************************
 * cget ()
 *
 * Arguments: info - pointer to structure with the problem information
 * Returns: parameter c of the structure
 * Side-Effects: exits the program
 *
 * Description: function to access the parameter c of the structure
 *
 *****************************************************************************/

int cget (tableinfo *info)
{
	return info->c;
}


/******************************************************************************
 * kget ()
 *
 * Arguments: info - pointer to structure with the problem information
 * Returns: parameter k of the structure
 * Side-Effects: exits the program
 *
 * Description: function to access the parameter k of the structure
 *
 *****************************************************************************/

int kget (tableinfo *info)
{
	return info->k;
}


/******************************************************************************
 * l2get ()
 *
 * Arguments: info - pointer to structure with the problem information
 * Returns: parameter l2 of the structure
 * Side-Effects: exits the program
 *
 * Description: function to access the parameter l2 of the structure
 *
 *****************************************************************************/

int l2get (tableinfo *info)
{
	return info->l2;
}


/******************************************************************************
 * c2get ()
 *
 * Arguments: info - pointer to structure with the problem information
 * Returns: parameter c2 of the structure
 * Side-Effects: exits the program
 *
 * Description: function to access the parameter c2 of the structure
 *
 *****************************************************************************/

int c2get (tableinfo *info)
{
	return info->c2;
}


/******************************************************************************
 * fill_info_table()
 *
 * Arguments: information - a string with the info to store in the structure
 * Returns: info -> a structure with the info of the problem to solve
 * Side-Effects: none
 *
 * Description: store in a structure the information of the problem to solve
 *
 *****************************************************************************/
 
tableinfo fill_info_table (FILE* input)
 {
	tableinfo info;
	int def;
		
	/*scan the information to the structure*/
	def=fscanf(input, "%d", &info.L);
	def=fscanf(input, "%d", &info.C);
	def=fscanf(input, "%d", &info.l);
	def=fscanf(input, "%d", &info.c); 
	def=fscanf(input, "%d", &info.k);
	
	/* if info.k is zero there are 2 more parameteres to store */
	if(info.k==0)
	{
		/*scan the information to the structure again*/
		def=fscanf(input, "%d", &info.l2);
		def=fscanf(input, "%d", &info.c2);
	}

    if(def<0)
	  exit(0);

	return info;
 }
 
 

/******************************************************************************
 * solve()
 *
 * Arguments: input - input file to read to solve 
 * 			  output - output file to write the solution
 * Returns: (void)
 * Side-Effects: reads from the file, save the problem information on a 
 * 				 structure, store memory for the table and fill it with 
 * 				 the info from the file (line by line, using other function). 
 * 				 It also works the information: tests the validity and calls 
 * 				 other functions to either solve the problem or to write on the 
 * 				 output file
 *
 * Description: solve the problem(s)
 *
 *****************************************************************************/

void solve (FILE* input, FILE* output)
{
	tableinfo info; /*structure to store information to solve the problem*/
	int** table=NULL;
	int i=0, j=0, def=0, test=0;
	
	/*Read the file until the end*/
	while (!feof(input))
	{ 	
		info=fill_info_table(input); /*Fill a structure with the info to solve the problem */
		def=well_defined_problem(&info); /*Test if the parameters are valid*/
		
		/*Problem with non valid parameters*/
		if(def==-1)
		{
			write_solution_info(output, &info, def); /*repeat the first line of the problem*/
			fprintf(output, "\n"); /*put an empty line, to separate from the next problem*/
			/*Skip the lines with the table */
			for(i=0; i<getL(&info)*getC(&info); i++)
			{
				def=fscanf(input, "%d", &test);
			}
			continue; 
		}
		
		/*Problem with valid parameters*/
		
		/*Allocate memory for the table and verify*/
		table=(int**) calloc(getL(&info), sizeof(int*));
		if(table==NULL)
			exit(0);
			
		/*Work on the lines of the table: read the line from the file and fill it in  
		 * the table using other function */
		for(i=0; i<getL(&info); i++)
		{
			table[i]=(int*)calloc(getC(&info), sizeof(int));
			if(table[i]==NULL)
				exit(0);
				
			for(j=0; j<getC(&info); j++)
				 def=fscanf(input, "%d", &table[i][j]);
		}
		
		
		/*Now that the table is filled, we analyse our info to solve the problem
		 * that will be done with other function*/
		decision(&info, table, output);
		
		/*The problem was solved. Print an empty line to separate the next problem*/
		fprintf(output, "\n");
		
		/*Free the memory of the table for this problem*/
		for(i=0; i<getL(&info); i++)
			free(table[i]);
		free (table);
		/*Continue to the next problem*/
	}
	
	return; 
}


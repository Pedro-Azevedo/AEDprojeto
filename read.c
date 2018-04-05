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
 * memory_allocation_error ()
 *
 * Arguments: information - string to print with the memory error
 * Returns: (void)
 * Side-Effects: exits the program
 *
 * Description: message function when memory is not correctly allocated
 *
 *****************************************************************************/

void memory_allocation_error(char* information) {

  printf("%s\n", information);
  exit(1);
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
 
tableinfo fill_info_table (char* information)
 {
	tableinfo info;
		
	/*scan the information to the structure*/
	sscanf(information, "%d %d %d %d %d", &info.L, &info.C, &info.l, &info.c, &info.k);
	/* if info.k is zero there are 2 more parameteres to store */
	if(info.k==0)
		/*scan the information to the structure again*/
		sscanf(information, "%d %d %d %d %d %d %d", &info.L, &info.C, &info.l, &info.c, &info.k, &info.l2, &info.c2);
	return info;
 }
 
 
 /******************************************************************************
 * fill_table_line()
 *
 * Arguments: line - string with the numbers to store in the line of the table 
 * 		      cols - number of columns on the table. 
 * Returns: the line of the table filled with the numbers
 * Side-Effects: none
 *
 * Description: read a line of the file with numbers to store in a line 
 *              of the table
 *
 *****************************************************************************/
 
 int* fill_table_line (char* line, int cols)
 {
	 char* token=NULL;
	 int* tableline=NULL;
	 int j=0;
	 
	 /*Allocate memory to the line of the table*/
	 tableline=(int*)calloc(cols, sizeof(int));
	 if(tableline==NULL)
		memory_allocation_error("Error: Could not allocate memory for tableline");
	 
	 /* Save the numbers (separated by a space) in the positions of the table line*/
	 token=strtok(line, " ");
	 for(j=0; j<cols; j++)
	 {
		 sscanf(token, "%d", &tableline[j]);
		 token=strtok(NULL, " ");  
	 }
	 
	 return tableline;
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
	char line[MAX_WORD] = {'\0'}; /*buffer line to read lines from the file*/
	tableinfo info; /*structure to store information to solve the problem*/
	int** table=NULL;
	int i=0, def=0; 
	
	/*Read the file until the end*/
	while (fgets(line, sizeof(line), input)!=NULL)
	{
		/*Skip an empty line*/
		if(strcmp(line, "\n")==0)
			continue;
			
		info=fill_info_table(line); /*Fill a structure with the info to solve the problem */
		def=well_defined_problem(info); /*Test if the parameters are valid*/
		
		/*Problem with non valid parameters*/
		if(def==-1)
		{
			write_solution_info(output, info, def); /*repeat the first line of the problem*/
			fprintf(output, "\n"); /*put an empty line, to separate from the next problem*/
			/*Skip the lines with the table */
			for(i=0; i<info.L; i++)
				fgets(line, sizeof(line), input);  
			continue; 
		}
		
		/*Problem with valid parameters*/
		
		/*Allocate memory for the table and verify*/
		table=(int**) calloc(info.L, sizeof(int*));
		if(table==NULL)
			memory_allocation_error("Error: Could not allocate memory for table");
			
		/*Work on the lines of the table: read the line from the file and fill it in  
		 * the table using other function */
		for(i=0; i<info.L; i++)
		{
			fgets(line, sizeof(line), input); 
			table[i]=fill_table_line(line, info.C); 
		}
		
		/*Now that the table is filled, we analyse our info to solve the problem
		 * that will be done with other function*/
		decision(info, table, output);
		
		/*The problem was solved. Print an empty line to separate the next problem*/
		fprintf(output, "\n");
		
		/*Free the memory of the table for this problem*/
		for(i=0; i<info.L; i++)
			free(table[i]);
		free (table);
		
		/*Continue to the next problem*/
	}
	
	return; 
}



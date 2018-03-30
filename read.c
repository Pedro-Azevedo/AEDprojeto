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
 * Returns: info -> a strucutre with the info of the problem to solve
 * Side-Effects: none
 *
 * Description: store in a structure the information of the problem to solve
 *
 *****************************************************************************/
 
tableinfo fill_info_table (char* information)
 {
	tableinfo info;
	char* token=NULL;
	
	/*scan the information to the structure*/
	sscanf(information, "%d %d %d %d %d", &info.L, &info.C, &info.l, &info.c, &info.k);
	/* if info.k is zero there are 2 more parameteres to store */
	if(info.k==0)
	{
		/* save the information after info.k*/
		token=strtok(information, "0");
		token=strtok(NULL, "0");
		/*scan the information*/
		sscanf(token, "%d %d", &info.l2, &info.c2);
	}
	return info;
 }
 
 
 /******************************************************************************
 * fill_table_line()
 *
 * Arguments: line - string with the numbers to store in the line of the table 
 * 		      cols - number os columns in the table. 
 * Returns: the line of the table filled with the numbers
 * Side-Effects: none
 *
 * Description: read a line of the file with numbers to store in a line of the table
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
 * Returns: (void)
 * Side-Effects: reads from the file, save the problem information on a structure, store memory for the table 
 * 			     and fill it with the info from the file (line by line, using other function). 
 *
 * Description: solve the problem(s)
 *
 *****************************************************************************/

void solve (FILE* input, FILE* output)
{
	char line[MAX_WORD] = {'\0'};
	tableinfo info;
	int** table=NULL;
	int i=0; 
	int def=0; 
	
	/*Read the file until the end*/
	while (fgets(line, sizeof(line), input)!=NULL)
	{
		/*Skip an empty line*/
		if(strcmp(line, "\n")==0)
			continue;
		info=fill_info_table(line); /*Fill a structure with the info to solve the problem */
		def=well_defined_problem(info); 
		
		if(def==-1)
		{
			
			for(i=0; i<info.L; i++)
				fgets(line, sizeof(line), input);  
			continue; 
		}
		/*Allocate memory to the table*/
		table=(int**) calloc(info.L, sizeof(int*));
		if(table==NULL)
			memory_allocation_error("Error: Could not allocate memory for table");
		/*Work on the lines of the table: real the line from the file and fill it in other function */
		for(i=0; i<info.L; i++)
		{
			fgets(line, sizeof(line), input); 
			table[i]=fill_table_line(line, info.C); 
		}
		
		decision(info, table, output);
		
		/*Free the table memory for this problem*/
		for(i=0; i<info.L; i++)
			free(table[i]);
		free (table);
		/*Continue to the next problem*/
	}
	
	return; 
}



/******************************************************************************
 *
 * File Name: main.c
 * Authors:    Group 29 AED 2017/2018 2S
 * Last modified: 2018-03-28
 *
 * COMMENTS
 *		Main program
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read.h"



/******************************************************************************
 * main ()
 *
 * Arguments: argc - number of command-line arguments
 *            argv - table of pointers for string arguments
 * Returns: int
 * Side-Effects: none
 *
 * Description: main Program
 *
 *****************************************************************************/


int main(int argc, char *argv[]) {
	
	FILE* input=NULL;
	char* name_input_file=NULL; 
	char delim[2]="."; 
	char* token = NULL;
	
	/* Number of arguments of different than 2 */
	if(argc!=2)
		exit(0); 
	
	name_input_file=(char*) calloc(strlen(argv[1]), sizeof(char*)); 
	
	if(name_input_file==NULL)
		memory_allocation_error();
		
	strcpy(name_input_file, argv[1]);
	
	token = strtok(argv[1], delim); 
	token = strtok(NULL, delim); 
	
	if(token==NULL || strcmp(token, "1maps")!=0)
	{
		free(name_input_file);
		exit(0); 
	}
	
	input = fopen(name_input_file, "r");
	
	if(input==NULL)
	{
		free(name_input_file);
		exit(0);
	} 
		
	solve (input);
	
	free(name_input_file);

	fclose (input);
	return 0; 
}

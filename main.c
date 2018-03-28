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
	
	name_input_file=argv[1]; 
	
	token = strtok(name_input_file, delim); 
	token = strtok(NULL, delim); 
	
	if(token==NULL) 
		exit(0); 
		
	if(strcmp(token, ".1maps")!=0)
		exit(0); 
		
	input = fopen(name_input_file, "r");
	
	if(input==NULL)
		exit(0); 
		
	/*solve (input);*/ 

	fclose (input);
	return 0; 
	
}

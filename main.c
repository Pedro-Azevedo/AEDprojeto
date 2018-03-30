/******************************************************************************
 *
 * File Name: main.c
 * Authors:    Group 29 AED 2017/2018 2S
 * Last modified: 2018-03-30
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
	
	FILE* input=NULL, *output=NULL;
	char* name_input_file=NULL, *name_output_file=NULL; 
	char* token = NULL;
	
	/* Number of arguments of different than 2 */
	if(argc!=2)
		exit(0); 
		
	name_input_file = argv[1];
	
	/*Separate the extension from the name of the file*/
	token = strtok(name_input_file, "."); 
	token = strtok(NULL, "."); 
	
	/* Verify if the extension either doesn't exist or is different than 1maps)*/
	if(token==NULL || strcmp(token, "1maps")!=0)
		exit(0); 
	
	/*Put the extension again on the file name*/
	strcat(name_input_file, ".1maps");
	/*Open the file and verify*/
	input = fopen(name_input_file, "r");
	
	if(input==NULL)
		exit(0);
	
	/*Separate the extension from the name of the file*/
	token = strtok(name_input_file, "."); 
	
	name_output_file=(char*) calloc(strlen(token)+strlen(".query")+1, sizeof(char)); 
	
	if(name_output_file==NULL)
		memory_allocation_error("Error: Memory not correctly allocated for name_output_file\n"); 
		
	strcpy(name_output_file, token); 
	strcat(name_output_file, ".query"); 
	
	output=fopen(name_output_file, "w"); 
	
	if(output==NULL)
		exit(0); 
	
	/*read the input file */ 
	solve (input, output);
	
	/*close files*/ 
	fclose (output);
	fclose (input);
	return 0; 
}

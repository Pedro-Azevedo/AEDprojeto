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


/******************************************************************************
 * memory_allocation_error ()
 *
 * Arguments: none
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: message function when memory is not correctly allocated
 *
 *****************************************************************************/

void memory_allocation_error(void) {

  printf("Error: Memory not correctly allocated\n");
  exit(1);
}


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
	
	name_input_file=(char*) calloc (strlen(argv[1])+1, sizeof(char)); 
	
	if(name_input_file==NULL)
		memory_allocation_error(); 
		
	strcpy(name_input_file, argv[1]); 
	token = strtok(name_input_file, delim); 
	token = strtok(NULL; delim); 
	
	if(strcmp(token, ".1maps")!=0)
		exit(0); 
		
	input = fopen(name_input_file, "r");
	
	if(fp==NULL)
		exit(0); 
		
	//solve (input); 
		
	free(name_input_file); 

	return 0; 
	
}

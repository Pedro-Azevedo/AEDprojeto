/******************************************************************************
 *
 * File Name: read.c
 * Authors:    Group 29 AED 2017/2018 2S
 * Last modified: 2018-03-28
 *
 * COMMENTS
 *		Implements fucntions defined in read.h
 *
 *****************************************************************************/

#include "read.h"


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
 * path()
 *
 * Arguments: 
 * Returns: (void)
 * Side-Effects: passes by reference the informations
 *
 * Description: o explore the line of the input file that tells us what to do
 *
 *****************************************************************************/
 
 void path (char* information)
 {
	 /*
	char aux[5]={'\0'};
	sscanf(information, "%d %d %d %d %d %s", L, C, l, c, k, aux);
	if(k==0)
		sscanf(aux, "%d %d", l2, c2); */
	return;
 }
 
 
 /******************************************************************************
 * filltable()
 *
 * Arguments: 
 * Returns: (void)
 * Side-Effects: passes by reference the informations
 *
 * Description: o explore the line of the input file that tells us what to do
 *
 *****************************************************************************/
 
 int* filltable (char* line)
 {
	 int* cena=NULL;
	 return cena;
 }
 
 
 

/******************************************************************************
 * solve()
 *
 * Arguments: input - input file to read to solve 
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: solve the problem
 *
 *****************************************************************************/

void solve (FILE* input)
{
	char line[MAX_WORD] = {'\0'};
	int** table=NULL;
	 
	while (fgets(line, sizeof(line), input)!=NULL)
	{
		printf("%s\n", line);
		path(line);
		/*
		table=(int**) calloc(L, sizeof(int*)); 
		if(table==NULL)
			memory_allocation_error(); 
		for(i=0; i<L; i++)
			table[i]=(int*) calloc(C, sizeof(int));
		for(i=0; i<L; i++)
		{
			t=fscanf(input, "%s", line);
			if(t==1)
			{
				;
			}
			
		}
		
		 
		for(i=0; i<L; i++)
			free(table[i]); 
		free(table);*/
	}
	
	return; 
}


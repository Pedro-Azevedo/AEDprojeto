/******************************************************************************
 *
 * File Name: write.c
 * Authors:    Group 29 AED 2017/2018 2S
 * Last modified: 2018-03-30
 *
 * COMMENTS
 *		Implements fucntions defined in write.h
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read.h"
#include "write.h"
#include "stack.h"


int output_energy=0;
int LOL=0;


/******************************************************************************
 * decision()
 *
 * Arguments: info - array with the information to solve the problem
 *            dimensions - array with the size of table
 * 			  table - table with the values. 
 * 			  output - output file to write the solution
 * 
 * Returns: (void)
 * 
 * Side-Effects: according to the value of info[k], redirects the problem to to ther functions
 *
 * Description: function to solve the problem
 *
 *****************************************************************************/


void decision (int* info, int* dimensions, int** table, FILE* output)
{	
	Stack* lpaths=NULL, *cpaths=NULL;
	int transfl=0, transfc=0, goal=0;
	
	/*Create 2 stacks to store steps we take to the solution*/
	lpaths=initStack(info[k]+1); 
	cpaths=initStack(info[k]+1);
	
	/*Transformation of coordinates original map -> our matrix*/
	transfl=info[l]-1-dimensions[up];
	transfc=info[c]-1-dimensions[left];
	
	output_energy=0;
	
	if(info[k]==0)
	{
		if(info[E]>=info[o])
			goal=info[E];
		else
			goal=-1;
	}
	
	/*Problem of type 2*/
	/*Find the path which maximizes the energy*/
	else if(info[o]==-2)
	{
		maximumenergy(transfl, transfc, info[E], info[k], dimensions, table, lpaths, cpaths);
		/*printf("OUTPUT ENERGY: %d", output_energy);*/
		goal=solvepath(transfl, transfc, info[E], output_energy, info[k], dimensions, table, lpaths, cpaths);
	}
	
	/*Problem of type 1*/
	/*Find a correct path to reach our goal*/
	else
		goal=solvepath(transfl, transfc, info[E], info[o], info[k], dimensions, table, lpaths, cpaths);
	
	
	/*Write the solution: info + final energy(problem with solution)/ -1 (problem without solution*/
	write_solution_info(output, info, goal);
	/*If the problem has a solution, we write the steps*/
	if(goal!=-1)
		walk(lpaths, cpaths, dimensions[up], dimensions[left], table, output);
		
	/*Free the memory of the stacks*/
	FreeStack(lpaths);
	FreeStack(cpaths);		
	
	return;
}


/******************************************************************************
 * solvepath()
 *
 * Arguments: _l -> line of the cell to analyse
 * 			  _c -> column of the cell to analyse
 * 			  _Ei -> input energy 
 * 			  _Eo -> miminum output energy
 * 			  _k -> number of steps allowed
 *            dimensions - array with the size of table
 * 			  table - table with the values. 
 * 			  lpaths -> stack to store the lines of the steps we take
 * 			  cpaths -> stack to store the columns of the steps we take
 * 
 * Returns: an integer with (a) the final energy (b) -1[no solution]
 * 
 * Side-Effects: recursive call function: it calls the different steps 
 *
 * Description: function to solve the problem of type 1
 *
 *****************************************************************************/

int solvepath (int coorl, int coorc, int energy, int objet, int coork, int* dimensions, int** table, Stack* lpaths, Stack* cpaths)
{
	int doors[4]={0}; /*array to help us know where to navigate in our matrix*/
	int nextl=-1, nextc=-1, nextEi=0, nextk=0, nextdir=-1; 
	int testsum=0, dirdown=0, dirright=0, dirup=0, dirleft=0, toreturn=0;
	char ch;
	int compE=0, compFS=0;
	
	/*Push the current step to the stack*/
	PushStack(lpaths, coorl); 
	PushStack(cpaths, coorc);
	
	/*Set the number of steps for the next step*/
	nextk=coork-1;	
	
	/*We will test this cell until all the possible directions are blocked*/	
	
	while(1)
	{
		/*We check the availability of each of the directions allowed (down, right, up, left)*/		
		/*We also check if all the directions are already unavailable*/
		
		/*In that case this cell is a dead end
			Since we didn't reach k movements going to this cell is wrong
			We pop the values from the stack and return*/
			
		printf("\nl %d c %d E %d\n", coorl+1+dimensions[up], coorc+1+dimensions[left], energy);
		if(!allowed(dimensions, doors, lpaths, cpaths, &dirdown, &dirup, &dirright, &dirleft, coorl, coorc)) 
			break;

        printf("DOWN %d RIGHT %d UP %d LEFT %d\n", dirdown, dirright, dirup, dirleft);
		
		/*We'll apply branch and bound to help us decide where to go
		 * To do that we determine the sum of the current energy with the gain/penalty of the
		 * cell we're trying to enter (nextEi). Then we add the sum of the positives at a distance nextk from
		 * from that cell (fullsum). If fullsum is greater than our minimum output energy and nextEi is positive, we're good 
		 * with that direction and don't need to test the others
		 * Else: Block that direction*/
			
		compE=0; 
		compFS=0;
		nextdir=-1;
		
		if(dirdown)
		{
			printf("Down:\t");
			testsum=sum(coorl+1, coorc, nextk, dimensions, table, lpaths, cpaths);
			checkdir(&nextdir, &nextEi, &nextl, &nextc, energy, coorl+1, coorc, testsum, down, objet, &compE, &compFS, doors, table); 
			printf("Comparison: %d\t", compE);
			printf("Nextdir: %d\t", nextdir);
			printf("\n");
		}
		
		if(dirup)
		{
			printf("Up:\t");
			testsum=sum(coorl-1, coorc, nextk, dimensions, table, lpaths, cpaths);
			checkdir(&nextdir, &nextEi, &nextl, &nextc, energy, coorl-1, coorc, testsum, up, objet, &compE, &compFS, doors, table);
			printf("Comparison: %d\t", compE);
			printf("Nextdir: %d\t", nextdir); 
			printf("\n");
		}
		
		if(dirright)
		{
			printf("Right:\t");
			testsum=sum(coorl, coorc+1, nextk, dimensions, table, lpaths, cpaths);
			checkdir(&nextdir, &nextEi, &nextl, &nextc, energy, coorl, coorc+1, testsum, right, objet, &compE, &compFS, doors, table); 	
			printf("Comparison: %d\t", compE);
			printf("Nextdir: %d\t", nextdir);
			printf("\n");
		}
		
		if(dirleft)
		{
			printf("Left:\t");
			testsum=sum(coorl, coorc-1, nextk, dimensions, table, lpaths, cpaths);
			checkdir(&nextdir, &nextEi, &nextl, &nextc, energy, coorl, coorc-1, testsum, left, objet, &compE, &compFS, doors, table); 
			printf("Comparison: %d\t", compE);
			printf("Nextdir: %d\t", nextdir);
			printf("\n");
		}
		

		/*We then check if any direction was picked*/
		/*In that case we reached a dead end and need to backtrack*/
		/*We pop the current cell and return*/
		if(nextdir==-1)
			break;
		
		/*Now if nextk is positive we still need to walk*/
		/*We make a recursive call to the next cell*/
		
		printf("Nextl: %d Nextc: %d\n", nextl+1+dimensions[up], nextc+1+dimensions[left]);
		printf("NEXTK: %d\n", nextk);
		
		/*
		LOL++;
		if(LOL>10)
		{
		do{
			ch=fgetc(stdin);
		}while(ch!=EOF && ch!='\n');
	}*/
		
		if(nextk>0)
			toreturn=solvepath(nextl, nextc, nextEi, objet, nextk, dimensions, table, lpaths, cpaths);

		/*Else, we reached a end with the steps taken*/
		else
		{
			/*Check if we beated our minimum final energy*/
			/*In that case, add the next cell to the stack and return our final energy*/
			if(nextEi>=objet)	
			{
				PushStack(lpaths, nextl); 
				PushStack(cpaths, nextc);
				return nextEi; 
			}
			/*Else, we find no solution and need to backtrack*/
			else
				break;
		}
		
		/*If we reach this point, is because we're backtracking*/
		/*Now if the return value received is different than -1
		 * that's because a correct solution was found and in that case 
		 * we simply return. By breaking the cycle we'' continue
		 * to return the final energy we received*/
	
		if(toreturn!=-1)
			return toreturn; 
		
		/*Else we0re still finding a solution.
		 * In that case we set nextdir to -1 again and block 
		 * the direction that we just tried to avoid repeating it and go back to the 
		 * beginning of the cycle*/
		else
		{
			doors[nextdir]=1;
			nextdir=-1;
		}
		
	} 
	
	nextl=PopStack(lpaths);
	nextc=PopStack(cpaths);
	return -1;
}

/******************************************************************************
 * maximumenergy()
 *
 * Arguments: _l -> line of the cell to analyse
 * 			  _c -> column of the cell to analyse
 * 			  _Ei -> input energy 
 * 			  _Eo -> miminum output energy
 * 			  _k -> number of steps allowed
 *            dimensions - array with the size of table
 * 			  table - table with the values. 
 * 			  lpaths -> stack to store the lines of the steps we take
 * 			  cpaths -> stack to store the columns of the steps we take
 * 
 * Returns: an integer with (a) the final energy (b) -1[no solution]
 * 
 * Side-Effects: recursive call function: it calls the different steps 
 *
 * Description: function to solve the problem of type 2
 *
 *****************************************************************************/

void maximumenergy (int coorl, int coorc, int energy, int coork, int* dimensions, int** table, Stack* lpaths, Stack* cpaths)
{
	int doors[4]={0}; /*array to help us know where to navigate in our matrix*/
	int nextl=-1, nextc=-1, nextEi=0, nextk=0, nextdir=-1; 
	int testsum=0, dirdown=0, dirright=0, dirup=0, dirleft=0;
	int compE=0, compFS=0; 
	char ch;
	
	/*Push the current step to the stack*/
	PushStack(lpaths, coorl); 
	PushStack(cpaths, coorc);
	
	/*Set the number of steps for the next step*/
	nextk=coork-1;	
	
	/*Well test this cell until all the possible directions are blocked*/
	while(1)
	{
		/*We check the availability of each of the directions allowed (down, right, up, left)
		 * A cell is not available if
		 * (a) is out of the matrix
		 * (b) we already tried to go to that direction from this cell
		 * (c) in our global path we already passed that cell (we can't go to the same cell twice)
		*/
		
		/*Don't forget to reverse the reverse transformation of coordinates*/
		
		/*printf("\nl %d c %d E %d\n", coorl+1+dimensions[up], coorc+1+dimensions[left], energy);*/
		
		/*Check if all the directions are already unavailable*/
		/*In that case this cell is a dead end
			Since we didn't reach k movements going to this cell is wrong
			We pop the values from the stack and return*/
		if(!allowed(dimensions, doors, lpaths, cpaths, &dirdown, &dirup, &dirright, &dirleft, coorl, coorc)) 
			break;
			
		
		/*printf("DOWN %d RIGHT %d UP %d LEFT %d\n", dirdown, dirright, dirup, dirleft);*/
		
		/*We'll apply branch and bound to help us decide where to go
		 * To do that we determine the sum of the current energy, the gain/penalty of the
		 * cell we're trying to enter and the sum of the positives at a distance nextk from
		 * from that cell. If that value is greater than our minimum output energy, we're good 
		 * with that direction and don't need to test the others
		 * Else: Block that direction*/
		
		compE=0;
		compFS=0; 
		nextdir=-1;
		
		if(dirdown)
		{
			/*printf("Down:\t");*/
			testsum=sum(coorl+1, coorc, nextk, dimensions, table, lpaths, cpaths);
			checkdir(&nextdir, &nextEi, &nextl, &nextc, energy, coorl+1, coorc, testsum, down, output_energy, &compE, &compFS, doors, table); 
			/*printf("Comparison: %d\t", comparison);
			printf("Nextdir: %d\t", nextdir);
			printf("\n");*/
		}
		
		if(dirup)
		{
			/*printf("Up:\t");*/
			testsum=sum(coorl-1, coorc, nextk, dimensions, table, lpaths, cpaths);
			checkdir(&nextdir, &nextEi, &nextl, &nextc, energy, coorl-1, coorc, testsum, up, output_energy, &compE, &compFS, doors, table); 
			/*printf("Comparison: %d\t", comparison);
			printf("Nextdir: %d\t", nextdir);
			printf("\n");*/
		}
		
		if(dirright)
		{
			/*printf("Right:\t");*/
			testsum=sum(coorl, coorc+1, nextk, dimensions, table, lpaths, cpaths);
			checkdir(&nextdir, &nextEi, &nextl, &nextc, energy, coorl, coorc+1, testsum, right, output_energy, &compE, &compFS, doors, table); 
			/*printf("Comparison: %d\t", comparison);
			printf("Nextdir: %d\t", nextdir);
			printf("\n");*/
		}
		
		if(dirleft)
		{
			/*printf("Left:\t");*/
			testsum=sum(coorl, coorc-1, nextk, dimensions, table, lpaths, cpaths);
			checkdir(&nextdir, &nextEi, &nextl, &nextc, energy, coorl, coorc-1, testsum, left, output_energy, &compE, &compFS, doors, table); 
			/*printf("Comparison: %d\t", comparison);
			printf("Nextdir: %d\t", nextdir);
			printf("\n");*/
		}
		
		/*
		printf("Nextl: %d Nextc: %d\n", nextl+1+dimensions[up], nextc+1+dimensions[left]);
		printf("NEXTK: %d\n", nextk); */
		
		/*If nextl or nextc are different from -1, one of the direction above were picked*/
		/*We calculate the new energy */
		
		 
		/*We than check if that energy reached zero or if nextl or nextc are -1*/
		/*In that case we reached a dead end and need to backtrack*/
		/*We pop the current cell and return*/
		if(nextdir==-1)
			break;
		
		/*Now if nextk is positive we still need to walk*/
		/*We make a recursive call to the next cell*/
		
		
		if(nextk>0)
			maximumenergy(nextl, nextc, nextEi, nextk, dimensions, table, lpaths, cpaths);

		/*Else, we reached a end with the steps taken*/
		else
		{
			/*Check if we beated our minimum final energy*/
			/*In that case, add the next cell to the stack and return our final energy*/
			if(nextEi>=output_energy)	
				output_energy=nextEi;
			/*Else, we find no solution and need to backtrack*/
			doors[nextdir]=1;
			nextdir=-1;
			continue;
		}
		
		/*If we reach this point, is because we're backtracking*/	
		/*Else we0re still finding a solution.
		 * In that case we set nextl and nextc to -1 again and block 
		 * the direction that we just tried to avoid and go back to the 
		 * beginning of the cycle*/
		doors[nextdir]=1;
		nextdir=-1;
	} 
	
	nextl=PopStack(lpaths);
	nextc=PopStack(cpaths);
	return;
}



int allowed(int* dimensions, int* doors, Stack* lpaths, Stack* cpaths, int* dirdown, int* dirup, int* dirright, int*dirleft, int coorl, int coorc)
{
	/* A cell is not available if
		 * (a) is out of the matrix
		 * (b) we already tried to go to that direction from this cell
		 * (c) in our global path we already passed that cell (we can't go to the same cell twice)
	*/
		
	/*Don't forget to reverse the reverse transformation of coordinates*/
	
	*dirdown=(coorl+1+1+dimensions[up])<=(dimensions[down]+1) && doors[down]==0 && !FindStack(lpaths, cpaths, coorl+1, coorc);
	*dirright=(coorc+1+1+dimensions[left])<=(dimensions[right]+1) && doors[right]==0 && !FindStack(lpaths, cpaths, coorl, coorc+1);
	*dirup= (coorl-1+1+dimensions[up])>=(dimensions[up]+1) && doors[up]==0 && !FindStack(lpaths, cpaths, coorl-1, coorc);
	*dirleft= (coorc-1+1+dimensions[left])>=(dimensions[left]+1) && doors[left]==0 && !FindStack(lpaths, cpaths, coorl, coorc-1);	
	
	if((*dirdown)==0 && (*dirright)==0 && (*dirup)==0 && (*dirleft)==0)
		return 0;
	
	return 1;
}

void checkdir(int* nextdir, int* nextEi, int* nextl, int* nextc, int energy, int testl, int testc, int testsum, int testdir, int objet, int* compE, int* compFS, int* doors, int**table)
{
	int fullsum=0, tempenergy; 
	
	printf("Testsum: %d\t", testsum);
	tempenergy=energy+table[testl][testc]; 
	printf("Tempenergy: %d\t", tempenergy);
	fullsum=tempenergy+testsum; 
	printf("Fullsum: %d\t", fullsum);
	printf("Objet: %d\t", objet);
	if(tempenergy>0 && fullsum>=objet)
	{
		if(tempenergy>=(*compE))
		{	
			if((tempenergy==compE) && (fullsum>(*compFS)))
			{
				(*compE)=tempenergy;
				(*compFS)=fullsum;
				(*nextEi)=tempenergy;
				(*nextl)=testl;
				(*nextc)=testc;
				(*nextdir)=testdir; 
			}
		}
		
	}
		
	else
		doors[testdir]=1;
}

/******************************************************************************
 * sum()
 *
 * Arguments: _l - line of the cell to test
 * 			  _c - column of the cell to test
 * 			  _k - distance from the pivot
 *            dimensions - array with the size of table
 * 			  table - table with the values. 
 * 			  lpaths - stack with the values of the lines of our path
 * 			  cpaths - stack with the values of the columns of our path
 * 
 * Returns: the value sum
 * 
 * Side-Effects: none
 *
 * Description: function to calculate the sum of the elements that are at a certain
 *              distance from a pivot, under certain constraints
 *
 *****************************************************************************/

int sum (int _l, int _c, int _k, int* dimensions, int** table, Stack*lpaths, Stack*cpaths)
{
	int _sum=0, i=0, j=0;
	
	/*Go through the table*/
	for(i=0; i<dimensions[height]; i++)
	{
		for(j=0; j<dimensions[width]; j++)
		{
			/*Skip the pivot*/
			if(i==_l && j==_c)
				continue;
				
			/*Skip an element in the stack */
			if(FindStack(lpaths, cpaths, i, j))
				continue;
				
			/*We sum the element if its distance from the pivot is less or equal info[k]*/
			if(abs(_l-i)+abs(_c-j)<=_k) 
			{
				/*We sum the element if it is positive*/
				if(table[i][j]>0)
					_sum+=table[i][j];
			} 
		}
	}
	
	return _sum; 
}


/******************************************************************************
 * upleft()
 *
 * Arguments: pos - pivot in the table
 * 			  r - maximum distance to the pivot
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
 * 			  r - maximum distance to the pivot
 *            lim - limit of the table (L or C)
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
 * walk()
 *
 * Arguments: lpaths - stack with the values of the lines of our path
 * 			  cpaths - stack with the values of the columns of our path
 * 			  _up - variable to apply a transformation of coordinates
 *            _left - variable to apply a transformation of coordinates
 * 			  table - table with the values. 
 *            output - output file to write the solution
 * 
 * Returns: void
 * 
 * Side-Effects: calculates the size of our stacks
 *
 * Description: writing the steps of the path on the output file
 *
 *****************************************************************************/

void walk(Stack* lpaths, Stack* cpaths, int _up, int _left, int** table, FILE*output)
{
	int maxl=GetSize(lpaths), maxc=GetSize(cpaths), i=0, j=0; /*Get the size of the stacks*/
	int transfl=0, transfc=0;

	/*We ignore the line and column of the bottom of the stack because it's the initial cell*/
	for(i=1, j=1; i<maxl && j<maxc; i++, j++) 
	{
		/*Read the entries and apply the reverse transformation of coordinates*/
		transfl=ReadEntry(lpaths, i)+1+_up;
		transfc=ReadEntry(cpaths, j)+1+_left;
		/*Write on the output file*/
		fprintf(output, "%d %d %d\n", transfl, transfc, table[transfl-1-_up][transfc-1-_left]);
	}
	
	return;
		
}


/******************************************************************************
 * write_solution_info()
 *
 * Arguments: output - file to write the solution
 * 			  info - array with the information to solve the problem
 * 			  res - parameter the solution value or -1 (problem without solution)
 *  
 * 
 * Returns: void
 * 
 * Side-Effects: none
 *
 * Description: writes the information of the problem on the output file and the
 *  			result in the case of valid parameters and info[k]!=0
 *
 *****************************************************************************/


void write_solution_info(FILE* output, int* info, int res)
{
	/*Write the line with the info and the final energy or -1 to the output file*/
	if(res!=-2)
		fprintf(output, "%d %d %d %d %d %d %d %d\n", info[L], info[C], info[o], info[l], info[c], info[k], info[E], res);
	else
		fprintf(output, "%d %d %d %d %d %d %d\n", info[L], info[C], info[o], info[l], info[c], info[k], info[E]);
	return;
}

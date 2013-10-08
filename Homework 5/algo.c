/* Filename: algo.c
 * Author:   
 * Created by: Tanya L. Crenshaw
 * Date created: 4/7/2013
 * Date modified:  4/7/2013
 * Modified by: Dan Nelson
 * 
 * Description:  This file contains stub definitions for the
 *               following functions:
 * 
 *               1. shuffle(): Create a random shuffling of an array
 *               of strings.
 *
 *               2. createNextPermutation(): Create a permutation of a
 *               string.
 * 
 *               3. usage(): Affirm that the main() function has been
 *               invoked with the correct parameters.
 *
 *   To complete programming assignment 5, CS303 students must
 *   complete or extend all of these functions.
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "algo.h"

/* shuffle() 
 *
 * Given an array, a, of strings (i.e., character pointers), and,
 * length, the number of items in the array, shuffle the array of
 * strings in place.
 * 
 * NOTE: CS303 Students must implement this function.
 *
 */
void shuffle(char * a[], int length){
	//Seed the random number generator with the system clock
	srand((unsigned int) time(NULL));
	//Initalize the iterators
	int i = 0;
	int k = 0;
	//Get the amount of chars in each string
	int lengthChars = (strlen(a[0]));
	//For loop to iterate through the array positions
	for (i = 0; i < length - 1; i++) {
		//Generate a random position
		int j = rand()%(i +1);
		//For loop to iterate through the chars in each string
		for(k = 0; k<(lengthChars);k++){
			//If they are the same, do not switch them
			if(a[i][k] != a[j][k]){
				//Bitwise switch each letter in the strings
				a[i][k]^=a[j][k];
				a[j][k]^=a[i][k];
				a[i][k]^=a[j][k];
			}
		}
	}
}

/* createNextPermutation() 
 *
 * Given a string a, get the next permutation of the string
 * by replacing a with the next permutation.  For example
 * if the string "ABC" is supplied, it will be updated to
 * "ACB".
 * 
 * If there is no next permutation, augment a to the 
 * empty string.
 * 
 * NOTE: CS303 Students must implement this function.
 *
 */
void createNextPermutation(char * a){
	//Initalize each iterator
	int i = 0;
	int l = 0;
	int k = 0;
	int j = 0;
	//Find the position that has the greatest value such that a[k] < a[k+1]
	for(i = 0; i < strlen(a); i++){
		if(a[i] < a[i+1]){
			k = i;
		}
	}
	//Find the position after the greatest value such that a[k]<a[l]
	for(i = 0; i < strlen(a); i++){
		if(a[k] < a[i]){
			l = i;
		}
	}
	//If the letters are the same then do not switch them
	if(a[k]!=a[l]){
		//Bitwise switch letter
		a[k]^=a[l];
		a[l]^=a[k];
		a[k]^=a[l];
		i=0;
		//Get the length of the string-1
		j = strlen(a)-1;
		//Iterate through all of the chars backwards
		for(i = k+1; i<j; i++){
			//Bitwise switch the chars
			a[i] ^= a[j];
			a[j]^=a[i];
			a[i]^=a[j];
			j--;
		}
	}
}

/* Function: usage()
 * Parameters: 1. argc: the number of parameters entered at the command 
 *                      line.
 *             2. argv: an array of pointers, each pointing to each string 
 *                      entered at the command line.
 * 
 * Description: If the program is called with the correct argc, it
 *              does nothing; otherwise it informs the user of the
 *              usage and exits the program.
 */
void usage(int argc, char * argv[])
{
	if (argc != REQUIRED_ARGS)
	{
		printf(USAGE, argv[0]);
		exit(EXIT_FAILURE);
	}
	//If the string contains more than 10 chars print an error then exit the program
	if(strlen(argv[1]) > 10){
		printf("This string is longer than 10 characters!");
		exit(EXIT_FAILURE);
	}
}

/*
 * Filename: main.c
 * Author: Danny Nelson
 * Section: B
 * Description: 
 * This program examines a file filled with words. It capitalizes the first letter in the file. All other letters
 * Are changed to lowercase. If a word appears after a period, the first letter of that word is capitalize.
 * All other letters are changed to lowercase. Extra credit for the homework was done allowing the program to 
 * Correctly capitalize words of arbitrary lengths.
 */
 
//Includes
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "donotedit.h"


//Constants
#define REQUIRED_ARGS 2
#define USAGE "usage: %s <input file>. \n"

//Function prototypes
void usage(int argc, char * argv[]);
FILE* fileOpener(char * argv[]);
int* calculateSizes(FILE * inputFile,char * argv[]);
void fileReader(FILE * inputFile, char ** rolodex,char * scannedWords, char * wordPtr);
void autocaps(char * rolodex[]);

int main(int argc, char * argv[])
{
	//Temporary pointer
	char * wordPtr = NULL;
	//Infile for method opener
	FILE * inFiles = NULL;
	//Array of sizes 
	int * arraySizes = NULL;
	//Iterator
	int iterator = 0;
	
	//Check that the number of command line parameters is correct.
	usage(argc, argv);
	//Save open file to file ptr
	inFiles = fileOpener(argv);
	//Save the file parameters to an aray
	arraySizes = calculateSizes(inFiles,argv); 
	printf("The number of words in the file: %d \n", arraySizes[0]);
	printf("The number of chars in longest word: %d \n",arraySizes[1]);
	//Allocate memory for words
	char ** rolodex = NULL;
	rolodex = malloc((int)sizeof(char*)*((arraySizes[0] + 1)));
	//Initialize each entry of rolodex to NULL
	memset( rolodex, 0, (int)sizeof(rolodex) ); 
	char * scannedWords = malloc(sizeof(char)*arraySizes[1] + 1);  
	//Rewind file to beginging so fileread can read
	rewind(inFiles);
	//Read file and save to word array
	fileReader(inFiles,rolodex,scannedWords,wordPtr);
	//Print unmodified string
	printWords(rolodex);
	//Auto caps file
	autocaps(rolodex);
	//Print newly editied file
	printWords(rolodex);
	//Free memory
	for(iterator = 0; rolodex[iterator]; iterator++){
		free(rolodex[iterator]);
	}
	free(arraySizes);
	free(scannedWords);
	free(wordPtr);
	//close file
	fclose(inFiles);

	return EXIT_SUCCESS;
}

/*
 *Function:usage(int, char *)
 *Descrition:Checks the command line parameters
 *Inputs:
 *	Parameters:
 *		int 	 argc	Number of command line parameters
 *		char[] 	 argv	Command line parameters
 *Outputs:
 *		void
 */
void usage(int argc, char * argv[])
{
	/* ***************************************** 
	 * CS303 students do not need to  alter 
	 * this function 
	 * ***************************************** */
	if (argc != REQUIRED_ARGS)
	{
		printf("%s: Incorrect number of parameters. \n", argv[0]);
		printf(USAGE, argv[0]);
		//Force an exit of the program.
		exit(EXIT_FAILURE);
	}
	return;
}

/*
 *Function:fileOpener(char **)
 *Description: Makes sure file can be opened and opens it
 *Inputs:
 *	Parameters:
 *		char[] 	 argv	Command line parameters
 *Outputs:
 *		FILE * 	 file Pointer to open file
 */
FILE * fileOpener(char * argv[]){
	//Open file
	FILE * inFile = NULL;
	//Check to make sure file could be opened
	if((inFile = fopen(argv[1],"r")) == NULL){
		printf("Could not find file! \n");
		exit(EXIT_FAILURE);
	}
	//Return file
	return inFile;
}

/*
 *Function:fileOpener(FILE *, char**)
 *Descrition: Calculates the number of words in the file
 *			  Calculates the number of chars in longest word
 *Inputs:
 *	Parameters:
 *		FILE * 	 inputFile	Open file to read
 *		char *	 argv[] 	Command line parameters
 *Outputs:
 *		int * 	 a[0] = Num words in file
 *				 a[1] = Num chars in longest word
 */
int * calculateSizes(FILE * inputFile,char * argv[]){
	//Instance variables
	int numWordsInFile = 0;
	int longestWordInFile = 0;
	int longest = 0;
	int c = 0;
	int doubleSpace = 0;
	//Create array for return
	int * returnArr = malloc(sizeof(int)*2);
	//Scan through file
	while((c = fgetc(inputFile)) != EOF){
		//If space
	  if(c == 32 || c == '\n') {
			//If two spaces in a row
			if(doubleSpace == 0){
				//Increment number of words in file
				numWordsInFile++;
				//Increment double space to prevent two spaces in a row
				doubleSpace++;
				//If the new longest word is longer than the prior one save that length
				//To the longest word
				if(longest > longestWordInFile){
					longestWordInFile = longest+1;
				}
				//Reset longest word to 0 and start checking for a new longer one
				longest = 0;
			}
		}
		//iIf not a space
		else{
			//Unset space
			doubleSpace = 0;
			//Start counting for longest again
			longest++;
		}
	}
	//Save the number of words in the file to a[0]
	returnArr[0] = numWordsInFile;
	//Save number of chars of longest word to a[1]
	returnArr[1] = longestWordInFile;
	//Exit if no words in file
	if((returnArr[0]) == 0){
		printf("There were no words in the file! \n");
		exit(EXIT_FAILURE);
	}
	else if((returnArr[0]) > 25){
		printf("%s contains over 25 words, but will continue! \n",argv[0]);
	}
	else if((returnArr[0] == 0) && (returnArr[1]!=0)){
		returnArr[0] = 1;
	}
	return returnArr;
}

/*
 *Function:fileReader(FILE *,char **, char *, char *)
 *Description: read file and place result into char **
 *
 *Inputs:
 *	Parameters:
 *		FILE * 	  inputFile		Open file to read
 *		char **   rolodex 		Place to save read words to
 *		char *	  scannedWords	Temp array to put the scanned words in 
 *		wordPtr * wordPtr		Array to save word into before saving to rolodex
 *
 *Outputs:
 *		void
 */
void fileReader(FILE * inputFile,char ** rolodex,char * scannedWords,char * wordPtr){
	int j = 0;
	//Read the file and save to scanned words
	while((fscanf(inputFile, "%s",scannedWords)==1)){
		//Allocate enough memory to hold the scanned word
		wordPtr = malloc((int)strlen(scannedWords)+1);
		//Copy scanned word to wordptr
		strncpy(wordPtr,scannedWords,(int)strlen(scannedWords)+1);	
		//Copy word ptr to rolodex
		rolodex[j] = wordPtr;
		j++;
	}
	return;
}

/*
 *Function:autocaps(char *)
 *Description: auto capitalize first characters
 *Inputs:
 *	Parameters:
 *		char * rolodex[]	Array of words to capitalize
 *Outputs:
 *	Return:
 *		void
 */
void autocaps(char * rolodex[])
{
	//Instance variables
	int capsLock = 0;
	int i = 0;
	int iterator = 0;
	char * wordPtr = NULL;
	//Loop to scan through file
	while(rolodex[i] != NULL) {
		//Copy each word to temp ptr
		wordPtr = malloc((int)strlen(rolodex[i])+1);
		strncpy(wordPtr,rolodex[i],(int)strlen(rolodex[i])+1);	
		//Scan through all chars in each word
		for(iterator = 0; iterator < ((int)strlen(wordPtr)); iterator++) {
			//Capitalize first letter of file
			if((i == 0)  && (iterator == 0)){
				wordPtr[0] = toupper(wordPtr[0]);
			}
			//Set the next letter after space to be capitalized
			else if(((wordPtr[iterator]==(unsigned char)('.')) || (wordPtr[iterator]==(unsigned char)('?'))  || (wordPtr[iterator]==(unsigned char)('!'))) && (capsLock == 0)){
				capsLock = 1;
			}
			//Capitalize next letter
			else if((capsLock == 1) && (wordPtr[iterator]!=(unsigned char)(' '))){
				capsLock = 0;
				wordPtr[iterator] = toupper(wordPtr[iterator]);
			}
			//Lowercase all other letters
			else{
				wordPtr[iterator] = tolower(wordPtr[iterator]);
			}
		}
		//Save correctly capitalized words back to ptr	
		rolodex[i] = wordPtr;
		i++;
	}
	return;
}

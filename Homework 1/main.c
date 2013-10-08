/*
 * Filename: main.c
 * Author: Danny Nelson
 * Section: B
 * Description: 
 * This program accepts between 2 and 5 command line parameters in pounds and converts to BDF.
 * It prints the number of command line parameters, prints the pounds, and prints the converted BDF.
 * This program also notifies the user when an invalid number of command line paramters is entered.
 */

//Header files to include
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

//Define constants
#define NUMBER_PARAM_LOW 2
#define NUMBER_PARAM_HIGH 5
#define BDF_WEIGHT 30

//Function prototype
double BDFConverter(int );

/*
 *Function:main(argc,argv[])
 *Description: Main entry point of program
 *Inputs:
 *	Paramaters
 *		int argc	Number of command line parameters
 *		char argv[]	Array of chars for each command line parameter
 */
int main(int argc, char * argv[]){
	
	//Initiate variables
	int i = 0;
	int input = 0;

	//Case for incorrect number of parameters
	if((argc<NUMBER_PARAM_LOW) || (argc>NUMBER_PARAM_HIGH)){
		printf("Incorrect number of parameters\n");
		//exit program with failure
		return EXIT_FAILURE;
	}
	
	//Print out number of parameters entered
	printf("%d parameters.\n",argc);

	//Print out pounds to BDF conversions
	for(i=1; i<argc; i++){
		//print pounds and conveted and format it to two decimal places
		printf("%d lbs = %.2f BDF\n",atoi(argv[i]),BDFConverter(atoi(argv[i])));
	}
	
	//Exit program with success
	return EXIT_SUCCESS;
}

/*
 *Function:BDFConverter(lbs)
 *Descrition:Convert pounds to BDf
 *Inputs:
 *	Parameters:
 *		int lbs		Number of pounds to convert to BDF's
 *Outputs:
 *	Return:
 *		double		Number of BDF's
 */
double BDFConverter(int  lbs){
	//Initialize variable to return
	double BDFLbs = 0.0;
	//Perfrom BDF conversion
	BDFLbs = ((double)lbs/BDF_WEIGHT);
	return BDFLbs;
}

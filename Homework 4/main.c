/* Filename: main.c
 * Author:
 * Created by: Tanya L. Crenshaw
 * Date created: 2/08/2012
 * Date updated: 3/14/2012
 *
 * CS303 students do not need to edit this file, except to place their
 * name after "Author" above.  If students are working on a team,
 * please place both names.
 */

// Includes
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "usage.h"
#include "sort.h"
#include "list.h"
#include "readLine.h"

// Constants
#define PARSE_SUCCESS -1

// A small MACRO to simplify some of the informative error and success
// statements in the main function.
#define mainlog(x) printf("%s: " x ", %s.\n",argv[0], argv[fileIndex])

// Function prototypes
int usage(int argc, char * argv[]);
int parseFile(FILE * fp, listNode ** list);

int main(int argc, char * argv[])
{

  FILE * fp = NULL;

  listNode * companyListPtr = NULL;
  int n;

  int fileIndex = 1;
  int mode = usage(argc, argv);

  // If this program was invoked with a flag, then the name of the
  // input file may be found in argv[2];
  if (mode > 0)
    fileIndex = 2;

  // Attempt to open the file.
  if((fp = fopen(argv[fileIndex],"r")) == NULL)
    {
      mainlog("File not found");
      return EXIT_FAILURE;
    }

  // Attempt to parse the file and store the results in the linked
  // list companyListPtr.
  if((n = parseFile(fp, &companyListPtr)) != PARSE_SUCCESS)
    {
      printf("Parse error on line no. %d. \n", n);
      mainlog("Error parsing file");
      fclose(fp);
      return EXIT_FAILURE;
    }
  
  mainlog("Successfully parsed file");

  // Print the unsorted linked list that resulted from parsing the
  // file.
  printList(companyListPtr, mode);
  printf("There are %d nodes in the list.\n\n", count(companyListPtr));
  
  if(mode == INSERTIONSORT_MODE)
    {
      // First, sort alphabetically and print the result.
      insertionSort(&companyListPtr, alphabetCompare);
      printf("\n****Sorted alphabetically****\n");
      printList(companyListPtr, mode);
    
      // Second, sort by zipcode and print the result.
      insertionSort(&companyListPtr, zipCompare);
      printf("\n****Sorted by zip****\n");
      printList(companyListPtr, mode);
  
      // Third, sort by distance from the UP Bell Tower and print the
      // result.
      insertionSort(&companyListPtr, distanceCompare);
      printf("\n****Sorted by distance from UP Bell tower****\n");
      printList(companyListPtr, mode);      

    }
     
  else if (mode == MERGESORT_MODE)
    {
      // First, sort alphabetically and print the result.
      mergeSort(&companyListPtr, alphabetCompare);
      printf("\n****Sorted alphabetically****\n");
      printList(companyListPtr, mode);
    
      // Second, sort by zipcode and print the result.
      mergeSort(&companyListPtr, zipCompare);
      printf("\n****Sorted by zip****\n");
      printList(companyListPtr, mode);
  
      // Third, sort by distance from the UP Bell Tower and print the
      // result.
      mergeSort(&companyListPtr, distanceCompare);
      printf("\n****Sorted by distance from UP Bell Tower****\n");
      printList(companyListPtr, mode);      

    }

  // All done with the linked list.  Free memory back into the wild so
  // that it may frolic in the wilderness.  Hopefully the memory has
  // not been weakened by its servitude.
  // http://www.youtube.com/watch?v=63YruDd2nJY
  freeList(&companyListPtr);

  fclose(fp);

  return EXIT_SUCCESS;
}

/* Function: parseFile()
 * Parameters:
 *
 * Description: Given a file pointer and a listNode pointer
 * this function reads a company entry from the file, allocates a
 * node for it, and inserts it into the linked list pointed to
 * by p.
 *
 */
int parseFile(FILE * fp, listNode ** list)
{
  char c;
  int i = 0;
  int lineCount = 0;
  
  listNode * newNode = NULL;
  
  // If the input file is well-formed, the first character
  // of each company entry is preceeded by a '*'.  At the 
  // top of each loop iteration, affirm that the * is there.
  // if not, the file is not well-formed, it has not followed
  // the expected format, and we should return with an error code.
  while((c = fgetc(fp)) == '*')
    {
      // Create a newNode to be inserted into the list.
      newNode = makeEmptyNode();
      
      // Eat the space after the asterix
      fgetc(fp);

#ifdef DEBUG
      printf("Debug print at line no. %d\n", __LINE__);
#endif
      
      // Read a line from the file and store it in a field
      // of the newNode.  
      newNode->companyName = readLine(fp);
      newNode->companyDescription = readLine(fp);
      newNode->website = readLine(fp);
      newNode->streetAddr = readLine(fp);
      newNode->suiteNumber = readLine(fp);
      newNode->city = readLine(fp);
      newNode->state = readLine(fp);
      newNode->zip = atoi(readLine(fp));
      newNode->latitude = atof(readLine(fp));
      newNode->longitude = atof(readLine(fp));

      char ** p = &(newNode->companyName);

      // Loop through the character pointer fields of newNode and make
      // sure that no pointer is NULL.  If any pointer is NULL, then 
      // readLine() failed and the function should be exited.

      // Reset i to check the latest entry read from the file.
      i = 0;

      
      while(i < COMPANY_STRING_FIELDS)
	{
	  if(*p == NULL)
	    {
	      freeNodeContents(newNode);
	      free(newNode);
	      freeList(list);

	      return lineCount + i;
	    }

	  p++;
	  i++;
	}

#ifdef DEBUG
      printf("Debug print at line no. %d\n", __LINE__);
#endif

      lineCount = lineCount + COMPANY_ENTRY_FIELDS;

      // 
      // Use the insert() function to insert it into
      // a linked list.
      insert(newNode, list);

#ifdef DEBUG
      printf("Inserted %s \n", newNode->companyName);
#endif

      // Eat the blank line between the company entries. 
      // If the line is not blank, the file is not well-formed
      // and we should return with an error code.
      char * eatLine = readLine(fp);
      lineCount++;
      
      // Maybe we are at the end of the file.
      if(eatLine == NULL)
	{
	  c = EOF;
	  break;
	}

      // Maybe we didn't just eat an empty line.
      if(!strncmp(" ", eatLine, 1))
	{
	  // Break out of this loop because a parse error
	  // was found.  The blank line that was
	  // expected is not there.
	  free(eatLine);
	  break;
	}

      // We don't need to keep the line that was read
      // to pass over the blank line between entries.
      free(eatLine);

    }

#ifdef DEBUG
      printf("Last value of c: %c\n", c);
      printf("Debug print at line no. %d\n", __LINE__);
#endif

  // At this moment, the loop is done executing.  Is it because
  // the END OF FILE was reached, or because the file is badly-formed?
  // If the file was successfully parsed, return success code,
  // otherwise return the line number at which the file was badly
  // formed.

  if(c == EOF)
    {
      return PARSE_SUCCESS;
    }
  else
    {
      freeList(list);

      return lineCount;
    }

  return PARSE_SUCCESS;

}



/* Function: usage()
 * Parameters: 1. argc: the number of parameters entered at the command 
 *                      line.
 *             2. argv: an array of pointers, each pointing to each string 
 *                      entered at the command line.
 * 
 * Description: If the program is called with the correct argc, it
 *              returns a code for the flag used at program invocation; 
 *              otherwise it informs the user of the usage and exits 
 *              the program.
 */
int usage(int argc, char * argv[])
{

  // Affirm that the program is invoked with MIN_ARGS to MAX_ARGS
  // arguments.  If not, exit the program.
  if (argc < MIN_ARGS || argc > MAX_ARGS )
    {
      printf(USAGE, argv[0]);
      exit(EXIT_FAILURE);
    }

  if(argc == MIN_ARGS)
    return NO_MODE;


  // Check for flags and return the appropriate mode 
  // value.
  else if(argc == MAX_ARGS)
    {
      if(!strncmp(argv[1], VERBOSE_FLAG, FLAG_SIZE))
	return VERBOSE_MODE;

      if(!strncmp(argv[1], IS_FLAG, FLAG_SIZE))
	return INSERTIONSORT_MODE;

      if(!strncmp(argv[1], MS_FLAG, FLAG_SIZE))
	return MERGESORT_MODE;

      else
	{
	  printf(USAGE, argv[0]);
	  exit(EXIT_FAILURE);
	}

    }

}


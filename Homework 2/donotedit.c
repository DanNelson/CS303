// Includes
#include <stdio.h>
#include <stdlib.h>

/* Function: printWords()
 *
 * Description: Given a pointer to an array of character pointers,
 * this function traverses the array, printing each string of 
 * characters.  This function makes no assumptions about number of
 * words allowed, and simply continues printing until it finds
 * a NULL pointer.  Thus, it is not impervious to segmentation
 * fault.
 *
 */
void printWords(char * a[])
{
  int i = 0;

  // Some nefarious or uninformed user may hand this function
  // a NULL pointer.  Handle it.
  if (a == NULL)
    {
      printf("empty array.\n");
      return;
    }
  

  // Otherwise, assume for the best and print each character
  // pointer as a string using the built-in printf() function.
  while(a[i] != NULL)
    {
      printf("%s ", a[i]);
      i++;
    }

  printf("\n");

  return;
}

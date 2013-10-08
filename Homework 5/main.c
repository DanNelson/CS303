/* Filename: main.c
 * Author:   
 * Created by: Tanya L. Crenshaw
 * Date created: 4/5/2013
 * Date modified: 2/16/2013
 *
 * Description: This is a small program provided to CS303 students
 *              to get them started on their programming 5 assignment. 
 *
 * For an input string of characters in alphabetical order, (e.g. abc,
 * abdn, drtx), this program produces all permutations of the input
 * string, shuffles them, and creates a binary search tree of 
 * the permutations.
 * 
 
   **************************************************** 
    NOTE: CS303 students should NOT edit main.c.        
    Instead, students should implement the following    
    following functions used in main.c                  

      1. createNextPermutation() in algo.c              
      2. shuffle() in algo.c
      3. insert() in tree.c
      4. printTree() in tree.c
      5. height() in tree.c
      6. count() in tree.c
      7. freeTree() in tree.c
      8. Extend usage() in algo.c

   **************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "tree.h"
#include "algo.h"

/* Function prototypes
 */
int factorial(int n);
int optimumHeight(double x);
void freePermutations(char ** perms, int nop);


int main(int argc, char * argv[])
{

  int i = 0; // Counter for for-loop.

  /* Check that the number of command line parameters is correct
   */
  usage(argc, argv);
  
  /* Get the length of the parameter and calculate the maximum number
   * of permutation slots that will need to be created.
   */
  int length = strlen(argv[INPUT_STRING]);
 
  /* Note to self: 10!  is 3,628,800.  Small enough to store in an
   * int.
   */
  int numberOfPermutations = factorial(length);  
  

  /* Allocate space for all of the permutations.  The variable, perms,
   * is an array of character pointers, where each character pointer
   * shall point to a particular permutation of the original string.
   */
  char ** perms = malloc(sizeof(char *) * numberOfPermutations);

  printf("************************************************************\n");
  printf(" Welcome to the tree builder! \n");
 
  /* Begin to print the list of permutations */
  printf("\nAll permutations of '%s': ", argv[INPUT_STRING]);
  printf("\n   ");


  /* Allocate space for each string, while creating each permutation
   * and storing it into the array, perms.  As you go, print each
   * resulting permutation.
   */
  for(i = 0; i < numberOfPermutations && *argv[INPUT_STRING] != '\0' ; i++)
    {
      /* Allocate, copy, print. */
      perms[i] = malloc(sizeof(char) * (length + 1));
      strncpy(perms[i], argv[INPUT_STRING], length + 1);
      printf("%s", argv[INPUT_STRING]);
      
      /* Pretty-print separating commas, with 10 perms per line. */
      if(i < numberOfPermutations - 1)
	printf(", ");
      
      if((i + 1) % 10 == 0)
	printf("\n   ");

      if(i == (numberOfPermutations - 1))
	printf(". \n");

      /* The first permutation stored is the original string.
       * Create the next permutation for the next iteration
       * of the loop.
       */
      createNextPermutation(argv[INPUT_STRING]);	     
    }


  printf("\n");

  /* Shuffle the permutations.  Right now, due to the nature of
   * createNextPermutation(), they are in alphabetical order.
   * Randomize them using shuffle() so that the resulting
   * bst is more balanced.
   */
  shuffle(perms, numberOfPermutations);

  /* Print the resulting shuffle */
  printf("Shuffled permutations: \n   ");
  
  for(i = 0; i < numberOfPermutations; i++)
    {
      printf("%s", perms[i]);
      
      /* Pretty-print separating commas, with 10 perms per line. */
      if(i < numberOfPermutations - 1)
	printf(", ");
      
      if((i + 1) % 10 == 0)
	printf("\n   ");

      if(i == (numberOfPermutations - 1))
	printf(". \n");
    }

  /* 
   * Create a binary search tree of the shuffled permutations. 
   */
  
  /* Initialize the tree to NULL to indicate it is empty 
   */
  TreeNode * bst = NULL;


  /* Insert all the permutations into the tree, one by one
   */
  for(i = 0; i < numberOfPermutations; i++)
    {
      insert(perms[i], &bst);
    }
  
  /* Calculate the height of the resulting tree */
  int h = height(bst);

  /* Print the tree */
  printf("\nThe tree contains %d nodes: \n", count(bst));
  printTree(bst);  

  /* Print the result */
  printf("\nThe worst-case height of the tree: %d\n", numberOfPermutations);

  /* Bug fix on 4/14/2013.  Use numberOfPermutations to calculate optimum
   * height where a single-noded tree has height of 1
   */
  printf("The best-case height of the tree: %d\n", optimumHeight((double)numberOfPermutations));

  printf("The height of the actual tree: %d\n\n", h);
    printf("************************************************************\n");

  /* All done.  Clean up */
  freeTree(&bst);
  freePermutations(perms, numberOfPermutations);

  return EXIT_SUCCESS;

}

/* optimumHeight()
 *
 * Given a value, x, return the optimum height for a tree with x
 * nodes where a tree with 1 node has height 1.
 */
int optimumHeight(double x)
{
  /* C's log function is base e.  Convert to base 2 */
  double changeBase = log(x) / log(2);

  return ((int)changeBase + 1);
}


/* factorial()
 * 
 * Given an integer, n, return (n * (n -1) * (n-2) * ... 1).
 *
 * Warning: This implementation is not intended for big
 * integers, and cannot compute values larger than 12!
 *
 */
int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}


/* freePermutations()
 *
 * Free the permutations allocated by the main function.  The
 * permutations are stored in an array of character pointers, where
 * each pointer points to a dynamically allocated string.
 */
void freePermutations(char ** perms, int nop)
{
  int i = 0;

  // Free each string.
  for(i; i < nop; i++)
    {
      free(perms[i]);
    }

  // Free the array.
  free(perms);

  return;
}

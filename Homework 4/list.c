#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "usage.h"

/* 
 * list.c
 * 
 * Description: Contains a linked list implementation for the company
 * entry listNode.
 *
 * CS303 students do not need to edit this file.
 */

/* Function: count()
 *
 * Description: Given a linked list, return the number of nodes
 * in the list.
 */
int count(listNode * listPtr)
{
  if (listPtr != NULL)
    {
      return 1 + count(listPtr->next);
    }

  return 0;

}

/* 
 * Function: insert()
 *
 * Description: Given a listNode initialized with company information,
 * insert it into the linked list.
 *
 */
int insert(listNode * newNode, listNode ** listPtr)
{


#ifdef DEBUG  
  printf("\nInserting: %s\n\n", newNode->companyName);
#endif


  // Writing secure code is mostly a matter of being paranoid about
  // your inputs. If either parameter is NULL, no work can be done.
  if(listPtr == NULL)
    {
      return INSERT_ERROR;
    }

  if(newNode == NULL)
    {
      return INSERT_ERROR;
    }

  // Insert the new node into the front of the list.
  newNode->next = *listPtr;
  *listPtr = newNode;

  return 0;
}


/*
 * Function: printList()
 *
 * Description: Print a linked list. If mode is VERBOSE, print every
 * field of every node.  Otherwise, print its name, zip, and lat,lon.
 *
 */
void printList(listNode * listPtr, int mode)
{

  if(listPtr != NULL)
    {

      if (mode == VERBOSE_MODE)
	{
	  printf("* %s\n  %s\n  %s\n", listPtr->companyName, listPtr->companyDescription, listPtr->website);
	  printf("  %s, %s\n", listPtr->streetAddr, listPtr->suiteNumber);
	  printf("  %s, %s %d\n", listPtr->city, listPtr->state, listPtr->zip);
	  printf("  (%f, %f)\n", listPtr->latitude, listPtr->longitude); 
	  printList(listPtr->next, mode);
	}

      else
	{
	  printf("* %s: %d.  ", listPtr->companyName, listPtr->zip);
	  printf("(%f, %f)\n", listPtr->latitude, listPtr->longitude); 
	  printList(listPtr->next, mode);
	}
    }

  return;

}

/*
 * Function: freeList()
 *
 * Description: Free memory allocated to a linked list.
 *
 */
void freeList(listNode ** listPtr)
{
  if(listPtr == NULL)
    return;

  listNode * current = *listPtr;
  listNode * next = NULL;

  while(current != NULL)
    {
      next = current->next;
      freeNodeContents(current);
      free(current);	
      current = next;
    }

  // Avoid future dangling pointer dereferencing by initializing the
  // contents of listPtr to NULL.
  *listPtr=NULL;

}


/*
 * Function: freeNodeContents()
 *
 * Description: Free memory allocated to the fields of a linked list
 * node.
 *
 */
void freeNodeContents(listNode * listPtr)
{

  if(!listPtr->companyName)
    free(listPtr->companyName);
  
  if(!listPtr->companyDescription)
    free(listPtr->companyDescription);
  
  if(!listPtr->website)
    free(listPtr->website);
  
  if(!listPtr->streetAddr)
    free(listPtr->streetAddr);
  
  if(!listPtr->suiteNumber)
    free(listPtr->suiteNumber);
  
  if(!listPtr->city)
    free(listPtr->city);

  if(!listPtr->state)
    free(listPtr->state);

  return;

}

/*
 * Function: makeEmptyNode()
 *
 * Description: Create an empty linked list node, initializing all fields
 * to their appropriate NULL or zero values.
 */
listNode * makeEmptyNode(void)
{
  listNode * newNode = malloc(sizeof(listNode));

  // Initialize all the character pointer type fields to NULL.
  newNode->companyName = NULL;
  newNode->companyDescription = NULL;
  newNode->website = NULL;
  newNode->streetAddr = NULL;
  newNode->suiteNumber = NULL;
  newNode->city = NULL;
  newNode->state = NULL;

  // Initialize the zip to 0. USPS reports that 00000 is
  // not a valid zip code.  
  newNode->zip = 0;

  // Inititalize the lat/lon to 0,0.  While this is an actual 
  // lat/lon, it's located in the middle of the Gulf of Guinea near
  // the African continent.  Hard to say that there's a tech company
  // located in deep seawater.  Though, maybe the Cobra Commander
  // relocated his underwater fortress there and he's hiring
  // generic white labcoats to run away from explosions in the
  // next movie.
  newNode->latitude = 0;
  newNode->latitude = 0;

  newNode->next = NULL;

#ifdef DEBUG
  printf("Making empty node: %s %s %d\n", newNode->companyName, newNode->state, newNode->zip);
#endif

  return newNode;
}

#ifndef __LIST_H__
#define __LIST_H__

/*
 * list.h
 *
 * Description: 
 *
 * 1. Define the fields in a node of a linked list
 * using the type struct listNodeTag, or listNode.
 *
 * 2. Define the function prototypes for the linked
 * list implementation found in list.c.
 *
 * Written by: Tanya L. Crenshaw
 * Date created: 02/09/2012
 * Date updated: 03/14/2012
 *
 * CS303 students do not need to edit this file.
 *
 */

#define COMPANY_ENTRY_FIELDS 10
#define COMPANY_STRING_FIELDS 7
#define INSERT_ERROR 1

/* Define a companyEntry in a linked list of
 * company entries.
 */
typedef struct listNodeTag{
  char * companyName;
  char * companyDescription;
  char * website;
  char * streetAddr;
  char * suiteNumber;
  char * city;
  char * state;
  int zip;
  double latitude;
  double longitude;
  struct listNodeTag * next;
} listNode;

// Function prototypes for functions already implemented.
int insert(listNode * newNode, listNode ** listPtr);
void printList(listNode * listPtr, int mode);
void freeList(listNode ** listPtr);
void freeNodeContents(listNode * listPtr);
listNode * makeEmptyNode(void);
int count(listNode * listPtr);

#endif


/* Filename: sort.c
 * Date modified: 4/6/2013
 * Modified by: Danny Nelson and Logan Adams 
 *
 * Description: Contains sorting functions that operate on the linked
 * list implementation for the company entry listNode found in
 * list.[c,h].
 * 
 *
 */
 
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "sort.h"
#define pi M_PI

#define swapYes 1
#define swapNo 0


// Function prototypes for helper functions used only
// within this file.
static listNode * mergeSortHelper(listNode * head, listNodeCompareFcn compare);
static listNode * merge(listNode * l1, listNode * l2, listNodeCompareFcn compare);
// Fuction Prototypes for student added and written helper methods for insertion sort
static listNode * findPrevious(listNode *headPtr, listNode *ptr);
void nodeSwap(listNode **headPtr, listNode *previous, listNode *current);

/* insertionSort()
 *
 * CS303 students must implement this function for HW4.
 */

void insertionSort(listNode ** listPtr, listNodeCompareFcn compare) {
	// The node that will point to the end of what is sorted in the linked list
	listNode *endSortedList = *listPtr;
	// The node that we are operating on
	listNode *changeNode;
	// Boolean to determine if the nodes were swapped last time to know the ordering
	int swap;
	// If the list is NULL, we don't want to deal with it at all
	while(endSortedList != NULL) {
		// Need to start working on the node at the end of our sorted list
		// Also need to get the previous item to compare it to
		changeNode = endSortedList->next;
		listNode *prev = findPrevious(*listPtr, changeNode);
		// Swap = 0 means that a swap is not happening
		swap = 0;
	
		// As long as we are not that the end of the list, and we are smaller than the previous node
		while(changeNode != NULL && prev != NULL && changeNode != *listPtr && compare(changeNode, prev)) {
			// If this is true, the nodes need to be switched and checked again
			nodeSwap(listPtr, prev, changeNode);
			// Update the nodes so we can check them again
			prev = findPrevious(*listPtr,changeNode);
			// Since a swap occured, we need to set our boolean
			swap = 1;
		}
		
		// Now, we want to iterate to the next node, but only if we didn't have a swap
		// If we had a swap, we can leave the endSortedList where it is and let is sort again
		if(!swap) { endSortedList = endSortedList->next; }
	}

}

/*
 * findPrevious(listNode **headPtr, listNode *nodeToAnalyze)
 *
 * This function is added to aid in Insertion Sort so we can find the previous node for swapping
 * This takes as parameters a double pointer to the front of the linked list
 * and the pointer to the node that we are looking for the node previous to
 * 
 */
static listNode *findPrevious(listNode *headPtr, listNode *ptr) {
	// Creates a node that will iterate through the linked list
	listNode *currentNode = headPtr;
	// If we have been passed anything that is NULL, return
	if(headPtr == NULL || ptr == NULL) { return NULL; }
	// If we are at the front of the list already, then we cannot return a previous node
	if(ptr == headPtr) { return NULL; }
	// Look through the list to find the node that we are looking for
	while(currentNode->next != ptr) { currentNode = currentNode->next; }
	// Assuming we have found the current node, return it, becuase our list should have found it or returned NULL
	return currentNode;
}



/*
 * nodeSwap(listNode **headPtr, listNode *previousSwap, listNode *currentSwap)
 *
 * This function aids in the Insertion sort becuase it allows us to take two nodes
 * that are next to each other and switch their order in the linked list
 * 
 */
void nodeSwap(listNode **headPtr, listNode *previous, listNode *current) {
	// Need to ensure that both of these are going to use a graceful exit code for the program

	if(*headPtr == NULL || previous == NULL || current == NULL) { return; }
	if(previous->next != current) { return; }
	if(*headPtr == previous) { 
		previous->next = current->next;
		*headPtr = current;
		current->next = previous;
	}
	else {
		listNode *doublePrev = findPrevious(*headPtr, previous);
		doublePrev->next = current;
		previous->next = current->next;
		current->next = previous;
	}
	return;
	
}

/* 
 * There are multiple ways to implement mergeSort, and these multiple
 * ways are often reflected in the function prototype for mergeSort().
 * The starter code has set up the functions for one kind of
 * implementation, though others are welcome.  If desired, students
 * may edit the function prototypes and parameters for mergeSort,
 * merge, or mergeSortHelper.
 */

/* mergeSort()
 *
 * CS303 students may alter the implementation of this function for
 * HW4.
 *
 */
void mergeSort(listNode ** listPtr, listNodeCompareFcn compare){
	*listPtr = mergeSortHelper(*listPtr, compare);
}


/* mergeSortHelper()
 *
 * CS303 students must implement this function for HW4.
 */
static listNode * mergeSortHelper(listNode * head, listNodeCompareFcn compare){
	//If there is no list items or if there is only one
	//List item, then return the list that was given seeing
	//This does not need sorthing beacuse it is only one item
	if(head == NULL || head->next == NULL){
		return head;
	}
	//Keep track of where the last node is before the middle node head
	listNode * previous = head;
	//Find where the middle node is
	listNode * middleHead = head ->next;
	//How many nodes does this contain?
	int numNodes = count(head);
	//Half way through the number of nodes this contains
	int half = (numNodes / 2);
	//Iterator
	int i = 0;
	//Go through the nodes until the middle node is found
	while(middleHead != NULL && i<half -1 ){
		middleHead = middleHead -> next;
		previous = previous -> next;
		i++;
	}
	//Unlink the first and second sections
	previous -> next = NULL;

	//Call recursively
	return 	merge(mergeSortHelper(head,compare),mergeSortHelper(middleHead,compare),compare);


}


/* merge()
 * Parameters: 1. l1: the first linked list to be merged.
 *             2. l2: the second linked list to be merged.
 *
 * Description: Merge two linked lists and return the merged
 *              list.
 *
 * CS303 students must implement this function for HW4.
 *
 */
static listNode * merge(listNode * l1, listNode * l2, listNodeCompareFcn compare){
	//Create new listNode to save results to
	listNode * l3 = NULL;
	//If l1 is empty, return list 2
	if(l1 == NULL){
		return l2;
	}
	//If l2 is empty, return list 1
	if(l2 == NULL){
		return l1;
	}
	//Compare the two lists
	int compareResult = compare(l1,l2);
	//If l1 is bigger
	if(compareResult == 1){
		l3 = l1;
		l3 -> next = merge(l1->next,l2,compare);
	}
	//If l2 is bigger
	else{
		l3 = l2;
		l3 -> next = merge(l1,l2->next,compare);
	}
	//Return results
	return l3;
}


/* alphabetCompare()
 *
 * Given two pointers to listNode, return 1 if the first one's
 * companyName is lexicographically less than the second one.
 * Otherwise, return 0.
 * 
 * For example, if l1->companyName is 'aaaa' and l2->companyName is
 * 'aaab' then l1->companyName is less than l2->companyName.
 * 
 * CS303 students must implement this function for HW4.
 * 
 */
int alphabetCompare(listNode * l1, listNode * l2)
{

	// Make sure that no one passes me anything that is NULL
	// Get the length of each of the strings so we can compare them
	int lengthL1 = strlen(l1->companyName);
	int lengthL2 = strlen(l2->companyName);
	if(lengthL1 < lengthL2) { lengthL1 = lengthL2; }
	// Now compare the strings
	if((strncmp(l1->companyName,l2->companyName, lengthL1) < 0)) { return swapYes; }
	else { return swapNo; }
}

/* zipCompare()
 *
 * Given two pointers to listNode, return 1 if the first one's
 * zip is smaller than the second one.  Otherwise, return 0.

 * CS303 students must implement this function for HW4.
 */
int zipCompare(listNode * l1, listNode * l2)
{
	// Compare the Zipcode Values for the two nodes
	if((l1->zip) < (l2->zip)) { return swapYes; }
	else { return swapNo; }
}

/* distanceCompare()
 *
 * Given two pointers to listNode, return 1 if the first one's
 * latitude + longitude place it closer to the University of Portland
 * Bell Tower than the second one.  Otherwise, return 0.
 *
 * CS303 students must implement this function for HW4.
 *
 */
int distanceCompare(listNode * l1, listNode * l2)
{
	double r = 6378.1;
	double distanceL1, distanceL2;
	// UP Calculations
	double longBell = -122.726029;
	double latBell = 45.571262;
	double upLong = longBell / (180 / pi);
	double upLat = latBell / (180 / pi);
	double upx, upy, upz;
	upx = cos(upLat) * cos(upLong);
	upy = cos(upLat) * sin(upLong);
	upz = sin(upLat);

	// Company L1 calculations
	double L1CompLong, L1CompLat, L1x, L1y, L1z;
	L1CompLong = l1->longitude / (180 / pi);
	L1CompLat = l1->latitude / (180 / pi);
	L1x = cos(L1CompLat) * cos(L1CompLong);
	L1y = cos(L1CompLat) * sin(L1CompLong);
	L1z = sin(L1CompLat);

	// Company L2 calculations
	double L2CompLong, L2CompLat, L2x, L2y, L2z;
	L2CompLong = l2->longitude / (180 / pi);
	L2CompLat = l2->latitude / (180 / pi);
	L2x = cos(L2CompLat) * cos(L2CompLong);
	L2y = cos(L2CompLat) * sin(L2CompLong);
	L2z = sin(L2CompLat);

	// Calculate BellTower L1 Distance
	distanceL1 = acos(upx*L1x + upy*L1y + upz*L1z) * r;
	distanceL2 = acos(upx*L2x + upy*L2y + upz*L2z) * r;
	if(distanceL1 < distanceL2) { return swapYes; }
	else { return swapNo; }

}



#ifndef __SORT_H__
#define __SORT_H__

#include "list.h"


/* sort.h
 *
 * Description: header file for the sort functionality for CS303 HW
 * #4.
 *
 * Written by: Tanya L. Crenshaw
 * Date created: 03/14/2012
 *
 * CS303 students do not need to edit this file.
 */

/*
 * So that we may have parameterized sort, define 'listNodeCompareFcn' as a
 * type that is a (pointer to) function that takes two int parameters
 * and returns an int
 */
typedef int listNodeCompareFcn(listNode * a, listNode * b);

// Function prototypes for the functions in sort.c.
void insertionSort(listNode ** listPtr, listNodeCompareFcn compare);
void mergeSort(listNode ** listPtr, listNodeCompareFcn compare);


int alphabetCompare(listNode * l1, listNode * l2);
int distanceCompare(listNode * l1, listNode * l2);
int zipCompare(listNode * l1, listNode * l2);

#endif

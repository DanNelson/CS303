/* Filename: tree.c
 * Author:   
 * Created by: Tanya L. Crenshaw
 * Date created: 2/25/2011
 * Date modified:  4/4/2013
 *
 * Description:  This file contains a partial implementation of a binary search
 *               tree data structure.  The functions implemented are:
 * 
 *               1. makeNode():  Create a new node for the tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/* makeNode()
 *  Parameter: newPermutation: A newly permuted string to be inserted into the tree.
 *
 *  Description:
 * 
 *    This helper function creates a new node for a tree.  The new
 *    node is initialized with a NULL left and right child and it is
 *    labeled with the given "newPermutation".  The function returns a
 *    pointer of type TreeNode * which is a pointer to the new node.
 */
TreeNode * makeNode(char * newPermutation)
{
	TreeNode * newNode = (TreeNode *)malloc(sizeof(TreeNode));
	newNode->left = NULL;
	newNode->right = NULL;
	//Extra credit count int
	newNode->count = 0;
	newNode->permutation = (char *)malloc(strlen(newPermutation) + 1);
	strncpy(newNode->permutation, newPermutation, strlen(newPermutation) + 1);
	return newNode;
}

/* printTree()
 * Parameter: root: The pointer to a tree
 *
 * Description:
 * 
 *  This function prints a tree in infix order; that is, it prints the
 *  left subtree first, the root second, and then completes the print
 *  operation by printing the right subtree.
 */
void printTree(TreeNode * root){
	//If there is a tree
	if(root!=NULL){
		//Recurse and print the left side
		printTree(root->left);
		//Print the permutation. Print the extra credit count.
		printf("%s(%d), ",root->permutation,root->count);
		//Recurse and print the right side
		printTree(root->right);
	}

}

/* This function should be commented and implemented by CS303 students
 * using the above function comment headers as a model.
 */
void insert(char * newPermutation, TreeNode ** rootPtr){
	//Get the length of the permutation
	int length = strlen(newPermutation);
	//If there is a root
	if((*rootPtr) == NULL){
		//Make a new node and add the permutation
		*rootPtr = makeNode(newPermutation);
		//Increment the count
		(*rootPtr)->count = (*rootPtr)->count +1;
		return;
	}
	//Increment the count
	(*rootPtr)->count = (*rootPtr)->count +1;
	//Insert to the left
	if(strncmp(newPermutation,((*rootPtr)->permutation),length)<0){
		insert(newPermutation,&((*rootPtr)->left));
		return;
	}
	//Insert to the right
	else{
		insert(newPermutation,&((*rootPtr)->right));
		return;
	}
}

/* This function should be commented and implemented by CS303 students
 * using the above function comment headers as a model.
 */
void freeTree(TreeNode ** rootPtr){
	//If the tree is empty do not free
	if((*rootPtr) == NULL){
		return;
	}
	else{
		//Recursively free tree
		freeTree(&((*rootPtr)->left));
		freeTree(&((*rootPtr)->right));
		//Free memory
		free(*rootPtr);
	}


}

/* This function should be commented and implemented by CS303 students
 * using the above function comment headers as a model.
 */

//2
int height(TreeNode * root){
	//If there is no tree
	if(root ==NULL){
		return 0;
	}
	else{
		//Recursively get the height of the left and right
		int left = height(root->left);
		int right = height(root->right);
		//If left is greater than right then return the left+1
		if(left > right){
			return left +1;
		}
		//If the right is taller than the left return the right+1
		return right +1;
	}

}

/* This function should be commented and implemented by CS303 students
 * using the above function comment headers as a model.
 */
int count(TreeNode * root){
	//If the tree is empty
	if(root == NULL){
		return 0;
	}
	//Count the left and right nodes and add 1
	else{
		return 1 + count(root->left) + count(root->right);
	}
}

/* Filename: aclist.c
 * Created by: Tanya L. Crenshaw
 * Date created: 1/24/2011
 * Date modified: 3/1/2013
 * Modified by: Danny Nelson
 *
 * Description:  This file contains a partial implementation of an access control
 *               list data structure.  The functions implemented are:
 * 
 *               1. initializeACL(): create the access control list node that
 *                  contains the file name and the pointer to the linked list
 *                  of entries.
 *
 *               2. addEntry(): insert a new entry into an access control list.
 *               3. printList(): print the contents of an access control list.
 *               4. ownerToFront(): moves the owner/s of the file to the front of the list
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aclist.h"


/* Function:    initializeACL()
 * Parameters:  1. filename: The name of the file for this access control list.
 *              2. aclPtr: The address of a NULL pointer to an access control list.
 * Description: Allocate memory for an access control list.  Initialize the 
 *              access control list with the filename.
 */
int initializeACL(char * filename, AccessControlList ** aclPtr)
{

	/* Check if aclPtr is NULL.  If so, then this function cannot
	 * proceed.
	 */
	if (aclPtr == NULL)
	{
		return INITIALIZE_FAILURE;
	}

	/* Check if the access control list pointer is NULL.  If it's not
	 * NULL, this access control list may have already been initialized.
	 */
	if (*aclPtr != NULL)
	{
		return INITIALIZE_FAILURE;
	}

	/* Allocate enough memory to hold an access control list.
	 */
	(*aclPtr) = malloc(sizeof(AccessControlList));

	/* Copy the filename into the new access control list.
	 */
	strncpy((*aclPtr) -> filename, filename, MAX_LENGTH);

	/* Set the pointer to the list of access control entries to NULL
	 * as there are no entries at this time.
	 */
	(*aclPtr) -> aces = NULL;
	return INITIALIZE_SUCCESS;
}

/* Function:    addEntry()
 * Parameters:  1. newUser, the new user to be inserted into the access control list.
 *              2. rights, the rights applied to the new user.
 *              3. acl, a pointer to the list.
 * Description: This function inserts a user and set of rights into an 
 *              access control list.  
 */
int addEntry(char * newUser, int rights, AccessControlList * acl)
{

	/* Create a temporary pointer which initially points to the same location
	 * as the start of the list of entries.
	 */
	AccessControlEntry * currentNode;

	/* Create a pointer which will point to the new element to be
	 * added to the list of entries.
	 */
	AccessControlEntry * newNode;

	/* Check if the access control list pointer is empty.  If so,
	 * then this list is not well-formed.  One cannot add a new user
	 * to an empty access control list.
	 */
	if (acl == NULL)
	{
		return ADD_ENTRY_FAILURE;
	}

	/* Allocate enough memory to hold an access control entry.
	 */
	newNode = malloc(sizeof(AccessControlEntry));

	/* Initialize the new node with the username.
	 */
	strncpy(newNode -> user, newUser, MAX_LENGTH);

	/* No null character is added by strncpy, so add one deliberately
	 */
	newNode -> user[MAX_LENGTH -1] = '\0';

	/* Initialize the new node with the user's rights.
	 */
	newNode -> rights = rights;


	/* Set the next pointer to NULL
	 */
	newNode -> next = NULL;

	/* Check if the list has 0 users.  If so, simply point at the
	 * new user and exit the function.
	 */
	if (acl -> aces == NULL)
	{
#ifdef DEBUG_MODE_2
		printf("Filename: %s, Line no: %d \n", __FILE__, __LINE__);
#endif 
		acl -> aces = newNode;
		return ADD_ENTRY_SUCCESS;
	}

	/* Otherwise, there is at least one entry in the linked list of
	 * access control entries.
	 */
	currentNode = acl -> aces;


	/* Insert the new entry at the front of the list.
	 */
	newNode -> next = acl -> aces;
	acl-> aces = newNode;

#ifdef DEBUG_MODE_2
	printf("Filename: %s, Line no: %d \n", __FILE__, __LINE__);
#endif 

	return METHOD_SUCCESS;
}

/*
 *Function:ownerToFront(*acl)
 *Description: Moves the owner of the file to the front of the list
 *Inputs:
 *	Parameters
 *		AccessControlList *acl	access list to edit
 *	Outputs:
 *	Return:
 *		int				  results of the move
 */
int ownerToFront(AccessControlList * acl){
	//If the ACL is null return
	if (acl == NULL){
		return NULL_ACL;
	}
	//If there is no ACL
	else if(acl -> aces == NULL){
		return METHOD_SUCCESS;
	}
	//If ACL exists and is filled with data
	else{
		//Temp holder
		AccessControlEntry * tempNode;
		//Keeps track of current entry
		AccessControlEntry * currentNode;
		currentNode = acl -> aces;
		//Traverses through list
		while(currentNode -> next != NULL){
			if(currentNode->next->rights & R_OWN){
				//1 sets the temp node equal to the node after current
				tempNode = currentNode -> next;
				//2 set the next node in the current position to the one after the one moving to front
				currentNode -> next = tempNode -> next;
				//3 sets the node moving's next to the current front's address
				tempNode -> next = acl -> aces;
				//4 sets the front to the node moving
				acl -> aces = tempNode;
				return OWNER_MOVED;
			}
			//Incramets the traversal
			currentNode = currentNode->next;
		}
	}
	return METHOD_SUCCESS;
}


/* Function:    printACL()
 * Parameters:  head, a pointer to a list node
 * Description: This function prints the contents of a list of
 *              AccessControlEntries (ACE) in an AccessControlList:
 *
 *              printList: ( filename:  ACE1, ACE2, ..., ACEN)
 *
 *              If the AccessControlList is empty, it prints:
 * 
 *              printList: ( empty access control list)
 */
void printACL(AccessControlList * acl)
{

	/* Create a temporary pointer will point to the current node
	 * being printed in the access control list.
	 */
	AccessControlEntry * currentNode;

	/* Print an initial "("
	 */
	printf("printList: (");


	/* Check if the access control list is empty.
	 */
	if (acl == NULL)
	{
		printf(" empty access control list )\n");
		return;
	}

	/* Print the filename.
	 */
	printf("File: %s. ", acl -> filename);

	/* Check if there are any users who have rights to this file
	 */
	if (acl-> aces != NULL)
	{
		/* Point to the beginning of the list and print the
		 * first element in the list.
		 */
		currentNode = acl -> aces;

		/* Traverse the list to the last element of the list.  As long
		 * as the next pointer of the node is not NULL, then there is
		 * still another element in the list.
		 */
		while(currentNode != NULL)
		{
			//Single & is bitwise AND
			printf(", %s (", currentNode->user);
			//If owner
			if(currentNode ->rights & R_OWN){
				printf("o");
			}
			//If can read
			if(currentNode ->rights & R_READ){
				printf("r");
			}
			//If can write
			if(currentNode ->rights & R_WRITE){
				printf("w");
			}
			//If can execute
			if(currentNode ->rights & R_EXECUTE){
				printf("x");
			}
			printf(")");

			// Point to the next entry
			currentNode = currentNode->next;
		}
	}
	//If no entries in list
	else{
		printf("  No entries.");
	}

	/* Print the final parenthesis
	 */
	printf(") \n");

	return;
}


/*
 *Function:deleteRight(right,*username,*acl)
 *Description: removes right from specified user if they have it
 *Inputs:
 *	Parameters:
 *		int 			  right  	right to remove
 *		char			  *username the user to remove the right from
 *		AccessControlList *acl	 	access list to edit
 *	Outputs:
 *	Return:
 *		int				  results of the delete
 */
int deleteRight(int right, char * username, AccessControlList * acl){
	//Keeps track if user is found
	int found = 1;
	//If ACL is null
	if (acl == NULL){
		return NULL_ACL;
	}
	//If there is no ACL
	else if(acl -> aces == NULL){
		return METHOD_SUCCESS;
	}
	//If the right specified is not a valid right
	if(!((right & R_OWN)||(right & R_WRITE)||(right & R_READ)||(right & R_EXECUTE))){
		return INCORRECT_PERMISSION;
	}

	else{
		//Keeps track of current node
		AccessControlEntry * currentNode;
		currentNode = acl -> aces;
		/* Traverse the list to the last element of the list.  As long
		 * as the next pointer of the node is not NULL, then there is
		 * still another element in the list.
		 */
		while(currentNode != NULL){
			//If the  username matches
			if(strncmp(currentNode->user,username,MAX_LENGTH)==0){
				found = 0;
				//If have right, remove it
				if((currentNode ->rights & right)){
					currentNode ->rights -= right;
				}
			}
			//Incraments current node
			currentNode = currentNode->next;
		}
		//If user is not found
		if(found){
			return NO_USERNAME;
		}
		return METHOD_SUCCESS;
	}
}

/*
 *Function:addRight(right,*username,*acl)
 *Description: adds right from specified user if they have it
 *Inputs:
 *	Parameters:
 *		int 			  right  	right to add
 *		char			  *username the user to remove the right from
 *		AccessControlList *acl	 	access list to edit
 *	Outputs:
 *	Return:
 *		int				  results of the add
 */
int addRight(int right, char * username, AccessControlList * acl){
	int found = 1;
	//If ACL is null
	if (acl == NULL){
		return NULL_ACL;
	}
	//If there is no ACL
	else if(acl -> aces == NULL){
		return METHOD_SUCCESS;
	}
	//If right provided is not valid
	if(!((right & R_OWN)||(right & R_WRITE)||(right & R_READ)||(right & R_EXECUTE))){
		return INCORRECT_PERMISSION;
	}
	else{
		//Keeps track of current entry
		AccessControlEntry * currentNode;
		currentNode = acl -> aces;
		/* Traverse the list to the last element of the list.  As long
		 * as the next pointer of the node is not NULL, then there is
		 * still another element in the list.
		 */
		while(currentNode != NULL){
			//If the username matches
			if(strncmp(currentNode->user,username,MAX_LENGTH)==0){
				found = 0;
				//If they do not already have the right add it
				if(!(currentNode ->rights & right)){
					currentNode ->rights += right;
				}
			}
			//Incraments the current position of the list
			currentNode = currentNode->next;
		}
		//If the username was not found
		if(found){
			return NO_USERNAME;
		}
		return METHOD_SUCCESS;
	}
}

/*
 *Function:deleteEntry(*username,*acl)
 *Description: removes user from list
 *Inputs:
 *	Parameters:
 *		char			  *username the user to remove the right from
 *		AccessControlList *acl	 	access list to edit
 *	Outputs:
 *	Return:
 *		int				  results of the user remove
 */
int deleteEntry(char * username, AccessControlList * acl){
	//If ACL is null
	if (acl == NULL){
		return NULL_ACL;
	}
	//If ACL does not exists
	else if (acl->aces == NULL){
		return NULL_ACE;
	}

	int userFind = 1;
	//Keeps track of current position in list
	AccessControlEntry * newNode;
	AccessControlEntry * currentNode;
	currentNode = acl -> aces;

	//If the user is position 0
	if(strncmp(acl->aces->user,username,MAX_LENGTH)==0){
		userFind = 0;
		//Save to temp node
		newNode = acl -> aces;
		//Points the next of the current node to the node to be deleted's next
		acl -> aces = acl -> aces -> next;
		free(newNode);
		return REMOVE_ENTRY_SUCCESS;
	}
	//If the user is not position 0 of the list
	else{
		//Traverse list
		while(currentNode->next != NULL){
			//If user is found
			if(strncmp(currentNode->next->user,username,MAX_LENGTH)==0){
				userFind = 0;
				//Save to temp node
				newNode = currentNode -> next;
				//Points the next of the current node to the node to be deleted's next
				currentNode -> next = currentNode -> next -> next;
				free(newNode);
				return REMOVE_ENTRY_SUCCESS;
			}
			//Incrament the position in the list
			currentNode = currentNode ->next;
		}
	}
	//User not found
	if(userFind){
		return NO_USERNAME;
	}

	return METHOD_SUCCESS;
}

/*
 *Function:freeACL(*acl)
 *Description: frees all the memory once the program is done executing
 *Inputs:
 *	Parameters:
 *		AccessControlList *acl	 	access list to free
 *	Outputs:
 *	Return:
 *		int				  results of the free
 */
int freeACL(AccessControlList * acl){
	// Check for NULL pointer
	if(acl == NULL){
		return EXIT_FAILURE;
	}

	// Handle the case when there are not users.
	if(acl->aces == NULL){
		free(acl);
		return EXIT_SUCCESS;
	}

	// Handle the case when there is 1 user.
	AccessControlEntry * current;
	current = acl->aces;
	if(current->next == NULL){
		free(current);
		free(acl);
		return EXIT_SUCCESS;
	}

	//Other
	AccessControlEntry * n = current->next;
	while(n != NULL){
		free(current);
		current = n;
		n = current -> next;
	}
	free (acl);

	return EXIT_SUCCESS;
}

/* Filename: aclist.h
 * Author:   
 * Created by: Tanya L. Crenshaw
 * Date created: 1/24/2011
 * Date modified: 3/1/2013
 * Modified by: Danny Nelson
 *
 */

#ifndef __ACLIST_H__
#define __ACLIST_H__

#define INITIALIZE_FAILURE (-1)
#define INITIALIZE_SUCCESS 0

#define ADD_ENTRY_FAILURE (-1)
#define ADD_ENTRY_SUCCESS 0

#define REMOVE_ENTRY_FAILURE (-1)
#define REMOVE_ENTRY_SUCCESS 0

#define NULL_ACL (-1)

#define NULL_ACE (-1)

#define INCORRECT_PERMISSION (-1)

#define	NO_USERNAME (-1)

#define	NO_OWNER (-1)
#define	OWNER_MOVED 0

#define METHOD_SUCCESS 0

/* Define the rights for files.
 */
#define R_OWN 8     // Binary = 0b1000 
#define R_READ 4    // Binary = 0b0100
#define R_WRITE 2   // Binary = 0b0010
#define R_EXECUTE 1 // Binary = 0b0001

/* Define the maximum length username and filename.
 */
#define MAX_LENGTH 128

/* Define structures.
 */

/* An Access Control Entry consists of a user's name, the rights that
 * a user may invoke on a file, and a pointer to the next Access
 * Control Entry in the linked list of entries.
 */
typedef struct AccessControlEntryTag {
	char user[MAX_LENGTH];
	unsigned int rights : 4;
	struct AccessControlEntryTag * next;
} AccessControlEntry;

/* An Access Control List consists of a filename and a pointer to the
 * linked list of Access Control Entries that describe the users who
 * have access to that file and the rights they may invoke on that
 * file.
 */
typedef struct AccessControlListTag{
	char filename[MAX_LENGTH];
	AccessControlEntry * aces;
} AccessControlList;


/* Function prototypes for functions that are provided with this
 *   assignment. 
 */
int initializeACL(char * filename, AccessControlList ** aclPtr);
int addEntry(char * newUser, int rights, AccessControlList * acl);
void printACL(AccessControlList * acl);

/* Function prototypes for functions that have been implemented
 * by the student.
 */
int deleteRight(int right, char * username, AccessControlList * acl);
int addRight(int right, char * username, AccessControlList * acl);
int deleteEntry(char * username, AccessControlList * acl);
int freeACL(AccessControlList * acl);
//ADDED prototype to move the person who owns the file to the front
int ownerToFront(AccessControlList * acl);

/* NOTE: Students may add more functions than these, especially any
 * functions that improve the modularity of the program.
 */

#endif

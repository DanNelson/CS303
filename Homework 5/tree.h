/* Filename: tree.h
 * Author:   
 * Created by: Tanya L. Crenshaw
 * Date created: 2/25/2011
 * Date modified: 4/8/2013
 *
 * Description: Type definitions and function prototypes supporting
 * the BST implementation in tree.c
 */

/* Type definition for a tree node.
 */
typedef struct treeNodeTag{
  char * permutation;            // The permutation labeling this node.
  int count;				    // Extra credit count variable
  struct treeNodeTag * left;   // Pointer to the left child.
  struct treeNodeTag * right; // Pointer to the right child.
} TreeNode; 

/* Function prototypes
 */
TreeNode * makeNode(char * newPermutation);
void printTree(TreeNode * root);
void insert(char * newPermutation, TreeNode ** rootPtr);
void freeTree(TreeNode ** rootPtr);
int height(TreeNode * root);
int count(TreeNode * root);

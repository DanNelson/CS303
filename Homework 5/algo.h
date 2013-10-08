/* Filename: algo.h
 * Author:   
 * Created by: Tanya L. Crenshaw
 * Date created: 4/7/2013
 * Date modified: 4/7/2013
 *
 * Description: Constant definitions and function prototypes
 * supporting the usage(), shuffle(), and createNextPermutation()
 * functions in algo.c.
 * 
 */

/* Constant definitions
 */
#define REQUIRED_ARGS 2
#define INPUT_STRING 1
#define USAGE "usage: %s <permuting string> . \n"

/* Function prototypes
 */
void usage(int argc, char * argv[]);
void createNextPermutation(char * p);
void shuffle(char * p[], int length);

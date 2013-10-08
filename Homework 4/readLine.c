#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "readLine.h"


/* 
 * readLine.c
 * 
 * Description: Implements a function that reads an arbitrary-length
 * line of text from a file:
 *
 * readLine()
 * CS303 students do not need to edit this file.
 *
 */

// The size of the chunk to handle at each recursion level
#define CHUNKSIZE 100

// macro to turn macro-value into a string
#define stringify(x) helpStringify(x)
#define helpStringify(x) #x

// function prototype
static char *helpReadLine(FILE *fp, int count);

/*
 * Function readLine() - reads a line from a file
 *
 * Parameters:
 * - fp: the FILE pointer denoting the file from which to read
 *
 * Result:
 * - returns a malloc-allocated string containg the characters read,
 *   or NULL if no charcters were read because end-of-file is reached.
 *   The returned string does NOT contain the newline character that
 *   terminated the line.
 */
char *readLine(FILE *fp) {
  // call our helper-function with values initialized from position 0
  // (i.e., all values initialized)
  return helpReadLine(fp, 0);
}

/*
 * Function helpReadLine() - helper function for readLine
 *
 * Parameters:
 * - fp: the FILE pointer denoting the file from which to read
 * - count: the number of chararcters previously read on this line
 *
 * Result:
 * - returns a malloc-allocated string containg the characters read, from
 *   position 'count' on. The calling function is responsible for
 *   setting the character values up through position 'count'-1.
 *   NULL is returned if EOF is reached and count is zero. The returned
 *   string does NOT contain the newline character that terminated the line.
 */
static char *helpReadLine(FILE *fp, int count) {

  // the buffer to read the current "chunk" of characters
  char buffer[CHUNKSIZE];

  // read the next chunk of the line
  int first, last; // first and last positions that contribute to the string
  int code = fscanf(fp, "%n%" stringify(CHUNKSIZE) "[^\n]%n",
		    &first, buffer, &last);
  int len = last-first; // length of the string written to the buffer

  // if EOF, set the length to 0, as 'last' may not have been written
  if (code <= 0) len = 0;

  // if room, store the null byte explicitly
  if (len < CHUNKSIZE) buffer[len] = '\0';

  // if hit EOF, and no characters were read at a higher recursive level,
  // return NULL, indicating EOF
  if (code == EOF && count == 0) {
    // hit EOF, and no characters have been read: return NULL;
    return NULL;
  }

  // if we filled the entire buffer with non-null characters, then
  // we'll let the recursive call do theh rest of the work; we'll just
  // pass it a pointer to our data so that
  if (len == CHUNKSIZE && buffer[CHUNKSIZE-1] != '\0') {

    // we only read part of the line: recurse to allocate the string and
    // initialize the characters beginning as position 'count'+CHUNKSIZE
    char *str = helpReadLine(fp, count+CHUNKSIZE);

    // copy the characters from position 'count' through 'count'+CHUNKSIZE-1;
    // then return
    strncpy(str+count, buffer, CHUNKSIZE);
    return str;
  }

  // we have gotten to the end of our line, so malloc the memory for
  // the string to return. Its size is the sum of
  // - count: the number of characters read in higher recursive levels
  // - len: the number of characters read at this recursive level
  // - 1: to make room for the null byte
  char *rtnVal = malloc(count+len+1);

  // copy the bytes from our buffer
  strncpy(rtnVal+count, buffer, len+1);
  
  // skip over the newline character in the file
  fscanf(fp, "%1[\n]", buffer);

  // return the malloc'd string
  return rtnVal;
}

#if 0    // for testing
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Need exactly one argument\n");
    return EXIT_FAILURE;
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("Could not open file %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  // read and print each line
  for (;;) {
    char *str = readLine(fp);
    if (str == NULL) break;
    printf("LINE: %s\n", str);
    free(str);
  }

  // close file and return
  fclose(fp);
  return EXIT_SUCCESS;
}
#endif

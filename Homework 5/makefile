# Filename: Makefile (for prog5)
# Author: 
# Created by: Tanya L. Crenshaw
# Date created: 1/25/2009
# Date modified: 4/6/2013
#
CC = gcc
SRCS = main.c tree.c algo.c
OBJS = main.o tree.o algo.o

# Compile the prog5 executable from a list 
# of object files.  If none of the object files 
# has changed, make will report 'prog5 is up to date.'
prog3:	main.o algo.o tree.o
	$(CC) -o prog5 main.o algo.o tree.o

# State the dependencies of the object files.
main.o:	main.c tree.h algo.h
	$(CC) -c main.c

tree.o:	tree.c tree.h
	$(CC) -c tree.c	

algo.o:	algo.c algo.h
	$(CC) -c algo.c

# Define the 'make clean' rule.
clean: 
	-rm $(OBJS) prog5

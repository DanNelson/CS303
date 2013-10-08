# Filename: Makefile (for prog3)
# Author: 
# Created by: Tanya L. Crenshaw
# Date created: 1/25/2009
# Date modified: 2/16/2013
#
CC = gcc
SRCS = main.c aclist.c
OBJS = main.o aclist.o

# Compile the prog3 executable from a list 
# of object files.  If none of the object files 
# has changed, make will report 'prog3 is up to date.'
prog3:	main.o aclist.o
	$(CC) -o prog3 main.o aclist.o

# State the dependencies of the main object file.
# If any changes are made in main.c or aclist.h
# main.o will be recreated.
main.o:	main.c aclist.h 
	$(CC) -c main.c

# State the dependencies of the list object file.
# If any changes are made in aclist.c or aclist.h
# aclist.o will be recreated.
aclist.o:	aclist.c aclist.h
	$(CC) -c aclist.c	

clean: 
	-rm $(OBJS) prog3

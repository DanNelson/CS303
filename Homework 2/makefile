# Filename: Makefile 
# Created by: Tanya L. Crenshaw
# Date created: 01/11/2012
#
# Use this file to compile the programming 
# assignment #2 for CS303.  It may be invoked
# from the command line using the make tool
# by simply typing:
#
# % make
#
# Students do not need to edit this file.
#
CC = gcc
SRCS = mainAlt.c donotedit.c
OBJS = mainAlr.o donotedit.o

prog2:	mainAlt.o donotedit.o
	$(CC) -o prog2 mainAlt.o donotedit.o

main.o:	main.c 
	$(CC) -c mainAlt.c

donotedit.o:	donotedit.c donotedit.h
	$(CC) -c donotedit.c
clean: 
	-rm $(OBJS) 
	-rm prog2

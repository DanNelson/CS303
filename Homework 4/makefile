# Filename: Makefile 
# Created by: Tanya L. Crenshaw
# Date created: 02/10/2012
# Date updated: 03/14/2012
#
# Use this file to compile the programming 
# assignment #4 for CS303.  It may be invoked
# from the command line using the make tool
# by simply typing:
#
# % make
#
# Students do not need to edit this file.
#
CC = gcc
SRCS = main.c list.c readLine.c sort.c
OBJS = main.o list.o readLine.o sort.o

prog4:	main.o list.o list.h sort.o sort.h readLine.o readLine.h usage.h
	$(CC) -o prog4 main.o list.o sort.o readLine.o

main.o:	main.c list.h sort.h readLine.h usage.h
	$(CC) -c main.c

readLine.o:	readLine.c readLine.h
	$(CC) -c readLine.c

list.o:	list.c list.h usage.h
	$(CC) -c list.c

sort.o:	sort.c sort.h list.h
	$(CC) -c sort.c
clean: 
	-rm $(OBJS) 
	-rm prog4
all: homework5

homework5: iofunctions.o
	        gcc -o homework5 iofunctions.o

iofunctions.o: iofunctions.c
	        gcc -ansi -pedantic-errors -Wall -c iofunctions.c


CC=gcc
CFLAGS=-g -Wall -ansi -pedantic

amazeme: main.o read.o
	$(CC) $(CFLAGS) -o amazeme main.o read.o

main.o: main.c read.h
	$(CC) -c $(CFLAGS) main.c

read.o: read.c read.h
	$(CC) -c $(CFLAGS) read.c

clean::
	rm -f *.o core a.out amazeme *~

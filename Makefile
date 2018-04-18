CC=gcc
CFLAGS=-Wall -ansi -O3

amazeme: main.o read.o write.o
	$(CC) $(CFLAGS) -o amazeme main.o read.o write.o

write.o: write.c read.h write.h
	$(CC) -c $(CFLAGS) write.c

read.o: read.c read.h write.h
	$(CC) -c $(CFLAGS) read.c

main.o: main.c read.h
	$(CC) -c $(CFLAGS) main.c

clean::
	rm -f *.o core a.out amazeme *~

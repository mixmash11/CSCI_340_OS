CC=gcc
CFLAGS=-c -O -Wall -g -std=gnu90

all: hw7

hw7: mem.o main.o
	$(CC) mem.c main.o -o hw7

mem.o: mem.c
	$(CC) $(CFLAGS) mem.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	/bin/rm -f hw7 *.o *.gz

run:
	./hw7

tarball:
	 tar -cvzf hunt.tar.gz main.c mem.c

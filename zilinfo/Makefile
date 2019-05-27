CC=gcc
CFLAGS=-c -g -Wall -pedantic

.PHONY: all clean

all: zilinfo

zilinfo: zilinfo.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^


clean:
	rm -f *.o zilinfo

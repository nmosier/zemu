CFLAGS=-g -c -Wall -pedantic

%.8xp: %.z80
	spasm -E $^ $@

zmap: zmap.o
	gcc -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f *.8xp *.8xv zmap *.o

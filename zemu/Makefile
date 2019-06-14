CFLAGS=-g -c -Wall -pedantic
ZSOURCES=zemu.z80 zerr.z80 zutil.z80 zmem.z80 zaddr.z80 zmap.z80 zcode.z80 zvar.z80
ZMAIN=zemu.z80
ZTARGET=$(ZMAIN:.z80=.8xp)

$(ZTARGET): $(ZSOURCES)
	spasm -E -L $(ZMAIN) $@

%.8xp: %.z80
	spasm -E -L $^ $@

zmap: zmap.o
	gcc -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f *.8xp *.8xv zmap *.o

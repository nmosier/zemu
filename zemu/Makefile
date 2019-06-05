CFLAGS=-g -c -Wall -pedantic
ZSOURCES=zemu.z80 zerr.z80 zutil.z80 zmem.z80
ZMAIN=zemu.z80
ZTARGET=$(ZMAIN:.z80=.8xp)

$(ZTARGET): $(ZSOURCES)
	spasm -E -L $(ZMAIN) $@ && sed -i "" 's/=/.equ/g' $(ZTARGET:.8xp=.lab)

%.8xp: %.z80
	spasm -E -L $^ $@ && sed -i "" 's/=/.equ/g' $*.lab

zmap: zmap.o
	gcc -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f *.8xp *.8xv zmap *.o

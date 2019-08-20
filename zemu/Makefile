CFLAGS=-g -c -Wall -pedantic
ZSOURCES=$(wildcard z*.z80)
ZMAIN=zemu.z80
ZTARGET=$(ZMAIN:.z80=.8xp)
ZTARGET_LOG=$(ZMAIN:.z80=log.8xp)

$(ZTARGET): $(ZSOURCES)
	spasm -E -L $(ZMAIN) $@

$(ZTARGET_LOG): $(ZSOURCES)
	spasm -E -L -DZDBG_LOG $(ZMAIN) $@

.PHONY: log
log: $(ZTARGET_LOG)

%.8xp: %.z80
	spasm -E -L $^ $@

zmap: zmap.o
	gcc -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f *.8xp *.8xv zmap *.o *.lab


.PHONY: size
.SILENT: size
size:
	wc -l z*.{z80,inc} | tail -n 1 | tr -s " " | cut -d " " -f 2

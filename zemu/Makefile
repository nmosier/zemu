CFLAGS=-g -c -Wall -pedantic
ZSOURCES=$(wildcard z*.z80 z*.inc)
ZMAIN=zemu.z80
ZTARGET=$(ZMAIN:.z80=.8xp)
ZTARGET_LOG=$(ZMAIN:.z80=log.8xp)
ZTARGET_DBG=$(ZMAIN:.z80=dbg.8xp)

# Feature Flags
ZCURSOR=1

# Feature Defines (for SPASM)
FEATURES=-DZCURSOR=$(ZCURSOR)

# Compilation Flags
DDBG=-DZDBG
DLOG=$(DDBG) -DZDBG_LOG

$(ZTARGET): $(ZSOURCES)
	spasm -E -L $(FEATURES) $(ZMAIN) $@

$(ZTARGET_DBG): $(ZSOURCES)
	spasm -E -L $(FEATURES) $(DDBG) $(ZMAIN) $@

$(ZTARGET_LOG): $(ZSOURCES)
	spasm -E -L $(FEATURES) $(DLOG) $(ZMAIN) $@

.PHONY: log
log: $(ZTARGET_LOG)

.PHONY: dbg
dbg: $(ZTARGET_DBG)

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

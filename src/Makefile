Z80_DIR=z80
INC_DIR=inc
CFLAGS=-g -c -Wall -pedantic
ZSOURCES=$(wildcard $(Z80_DIR)/z*.z80 $(INC_DIR)z*.inc)
ZMAIN=$(Z80_DIR)/zemu.z80
ZTARGET=$(ZMAIN:.z80=.8xp)
ZTARGET_LOG=$(ZMAIN:.z80=log.8xp)
ZTARGET_DBG=$(ZMAIN:.z80=dbg.8xp)

# Platform Flag
PLATFORM=TI84PCE

# Feature Flags
ZCURSOR=1
ZSELECT_GAME=0

# Defines (for SPASM)
FEATURES=-DZCURSOR=$(ZCURSOR) -DZSELECT_GAME=$(ZSELECT_GAME) -DZOFFSET=1
DPLATFORM=-D$(PLATFORM)=1

# Compilation Flags
DDBG=-DZDBG
DLOG=$(DDBG) -DZDBG_LOG

.PHONY: all
all: $(ZTARGET) $(ZTARGET_DBG) $(ZTARGET_LOG)

$(ZTARGET): $(ZSOURCES)
	spasm -E -L $(FEATURES) $(DPLATFORM) -I $(INC_DIR) -I $(Z80_DIR) $(ZMAIN) $@

$(ZTARGET_DBG): $(ZSOURCES)
	spasm -E -L $(FEATURES) $(DDBG) $(DPLATFORM) -I $(INC_DIR) -I $(Z80_DIR) $(ZMAIN) $@

$(ZTARGET_LOG): $(ZSOURCES)
	spasm -E -L $(FEATURES) $(DLOG) $(DPLATFORM) -I $(INC_DIR) -I $(Z80_DIR) $(ZMAIN) $@

.PHONY: log
log: $(ZTARGET_LOG)

.PHONY: dbg
dbg: $(ZTARGET_DBG)

%.8xp: %.z80
	spasm -E -L $(DPLATFORM) $^ $@

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

# Build Directories
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
Z80_DIR = $(SRC_DIR)/z80
INC_DIR = $(SRC_DIR)/inc

# Executable Targets
TARGETS = zmap zgen.sh zpages.sh zemu.8xp zemudbg.8xp zemulog.8xp
BINS = $(addprefix $(BIN_DIR)/, $(TARGETS))

# Compilation Flags
CFLAGS = -g -c -Wall -pedantic

# TI-8x Platform Flag
PLATFORM = TI84PCE

# ZEMU Source Files
ZMAIN = zemu

ZSRC_MAIN = $(Z80_DIR)/$(ZMAIN).z80
ZSRC_Z80 := $(find $(Z80_DIR) -iname "*.z80")
ZSRC_INC := $(find $(INC_DIR) -iname "*.inc")
ZSRCS = $(ZSRC_Z80) $(ZSRC_INC)

ZTARGET=$(BIN_DIR)/$(ZMAIN).8xp
ZTARGET_LOG=$(ZTARGET:.8xp=log.8xp)
ZTARGET_DBG=$(ZTARGET:.8xp=dbg.8xp)

# ZMAP Files
# ZMAP = zmap
# ZMAP_SRC = $(SRC_DIR)/$(ZMAP).c
# ZMAP_OBJ = $(OBJ_DIR)/$(ZMAP).o
# ZMAP_BIN = $(BIN_DIR)/$(ZMAP)

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
all: $(BINS)

$(ZTARGET): $(ZSRCS)
	spasm -E -L $(FEATURES) $(DPLATFORM) -I $(INC_DIR) -I $(Z80_DIR) $(ZSRC_MAIN) $@

$(ZTARGET_DBG): $(ZSRCS)
	spasm -E -L $(FEATURES) $(DDBG) $(DPLATFORM) -I $(INC_DIR) -I $(Z80_DIR) $(ZSRC_MAIN) $@

$(ZTARGET_LOG): $(ZSRCS)
	spasm -E -L $(FEATURES) $(DLOG) $(DPLATFORM) -I $(INC_DIR) -I $(Z80_DIR) $(ZSRC_MAIN) $@

.PHONY: log
log: $(ZTARGET_LOG)

.PHONY: dbg
dbg: $(ZTARGET_DBG)

%.8xp: %.z80
	spasm -E -L $(DPLATFORM) $^ $@

zmap: zmap.o
	gcc -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(CFLAGS) -o $@ $^



.PHONY: clean
clean:
	rm -f *.8xp *.8xv zmap *.o *.lab


.PHONY: size
.SILENT: size
size:
	wc -l z*.{z80,inc} | tail -n 1 | tr -s " " | cut -d " " -f 2

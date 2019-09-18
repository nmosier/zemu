# Build Directories
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
Z80_DIR = z80
INC_DIR = inc
CPP_DIR = cpp

OBJ_SUBDIRS = $(Z80_DIR) $(INC_DIR)
# OBJ_DIRS = $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(OBJ_SUBDIRS))

SRC_DIRS = $(shell find $(SRC_DIR) -type d)
OBJ_DIRS = $(SRC_DIRS:$(SRC_DIR)%=$(OBJ_DIR)%)

BUILD_DIRS = $(OBJ_DIRS) $(BIN_DIR)

# Executable Targets
TARGETS = zmap zgen.sh zpages.sh zemu.8xp # zemudbg.8xp zemulog.8xp
BINS = $(addprefix $(BIN_DIR)/, $(TARGETS))

# Compilation Flags
CFLAGS = -g -c -Wall -pedantic

# TI-8x Platform Flag
PLATFORM = TI84PCE

# ZEMU Source Files
ZMAIN = zemu

ZSRC_MAIN = $(SRC_DIR)/$(Z80_DIR)/$(ZMAIN).z80
# ZSRC_Z80 := $(find $(SRC_DIR)/$(Z80_DIR) -iname "*.z80")
# ZSRC_INC := $(find $(SRC_DIR)/$(INC_DIR) -iname "*.inc")
# ZSRC_Z80 = $(wildcard $(SRC_DIR)/$(Z80_DIR)/*.z80)
# ZSRC_INC = $(wildcard $(SRC_DIR)/$(INC_DIR)/*.inc)
ZSRC_Z80 = $(shell find $(SRC_DIR)/$(Z80_DIR) -iname "*.z80")
ZSRC_INC = $(shell find $(SRC_DIR)/$(INC_DIR) -iname "*.inc")
ZSRCS = $(ZSRC_Z80) $(ZSRC_INC)

ZOBJ_MAIN = $(ZSRC_MAIN:$(SRC_DIR)%=$(OBJ_DIR)%)
ZOBJ_Z80 = $(ZSRC_Z80:$(SRC_DIR)%=$(OBJ_DIR)%)
ZOBJ_INC = $(ZSRC_INC:$(SRC_DIR)%=$(OBJ_DIR)%)
ZOBJS = $(ZOBJ_Z80) $(ZOBJ_INC)

ZTARGET=$(BIN_DIR)/$(ZMAIN).8xp
ZTARGET_LOG=$(ZTARGET:.8xp=log.8xp)
ZTARGET_DBG=$(ZTARGET:.8xp=dbg.8xp)

ZCPP = $(SRC_DIR)/$(CPP_DIR)/zcpp.h

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

$(ZTARGET): $(ZOBJS)
	spasm -E -L $(FEATURES) $(DPLATFORM) -I $(OBJ_DIR)/$(INC_DIR) -I $(OBJ_DIR)/$(Z80_DIR) $(ZOBJ_MAIN) $@
#	spasm -E -L $(FEATURES) $(DPLATFORM) -I $(SRC_DIR)/$(INC_DIR) -I $(SRC_DIR)/$(Z80_DIR) $(ZSRC_MAIN) $@

$(ZTARGET_DBG): $(ZSRCS)
	spasm -E -L $(FEATURES) $(DDBG) $(DPLATFORM) -I $(SRC_DIR)/$(INC_DIR) -I $(SRC_DIR)/$(Z80_DIR) $(ZSRC_MAIN) $@

$(ZTARGET_LOG): $(ZSRCS)
	spasm -E -L $(FEATURES) $(DLOG) $(DPLATFORM) -I $(SRC_DIR)/$(INC_DIR) -I $(SRC_DIR)/$(Z80_DIR) $(ZSRC_MAIN) $@

.PHONY: log
log: $(ZTARGET_LOG)

.PHONY: dbg
dbg: $(ZTARGET_DBG)

%.8xp: %.z80
	spasm -E -L $(DPLATFORM) $^ $@

$(BIN_DIR)/%: $(OBJ_DIR)/%.o
	gcc -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc -c $(CFLAGS) -o $@ $<


$(BIN_DIR)/%.sh: $(SRC_DIR)/%.sh
	cp $< $@

$(ZOBJS): $(OBJ_DIR)/%: $(SRC_DIR)/%
	sed -E 's/^[[:space:]]*#/;%;/g' < $< | cpp -D$(PLATFORM)=1 -xassembler-with-cpp -P -imacros$(ZCPP) | sed -E "s/^;%;/#/g" > $@
# $(OBJ_DIR)/$(Z80_DIR)/%.z80: $(SRC_DIR)/$(Z80_DIR)/%.z80 $(OBJ_DIR)/$(Z80_DIR)

# $(OBJ_DIR)/$(INC_DIR)/%.inc: $(SRC_DIR)/$(INC_DIR)/%.inc $(OBJ_DIR)/$(INC_DIR)
#	sed -E 's/^[[:space:]]*#/%/g' < $< | cpp -D$(PLATFORM)=1 -xassembler-with-cpp -imacros$(ZCPP) | grep -v "^#" | sed -E "s/^%/#/g" > $@

.PHONY: clean
clean:
	rm -f *.8xp *.8xv zmap *.o *.lab

.PHONY: dirs
dirs: $(BUILD_DIRS)

$(BUILD_DIRS):
	mkdir -p $@

.PHONY: size
.SILENT: size
size:
	wc -l z*.{z80,inc} | tail -n 1 | tr -s " " | cut -d " " -f 2


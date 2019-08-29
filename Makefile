
BINS=src/zmap src/zgen.sh src/zpages.sh src/zemu.8xp


.PHONY: bin
bin: all
	[ -d bin ] || mkdir bin
	cp $(BINS) bin

.PHONY: all
all:
	cd src && make all

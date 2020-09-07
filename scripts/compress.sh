#!/bin/bash

usage() {
    cat <<EOF
usage: $0 [-hv]
EOF
}

VERBOSE=0

while getopts "hv" OPTION; do
    case "$OPTION" in
        h)
            usage
            exit 0
            ;;
        v)
            VERBOSE=1
            ;;
        "?")
            usage >&2
            exit 1
            ;;
    esac
done

shift $((OPTIND-1))

DIRS=(../src/zemu ../src/zemu/ti83plus)

# Create dummy dirs.
DUMMY_DIR=$(mktemp -d)
trap "rm $DUMMY_DIR" EXIT

dummy_dir() {
    [[ -d "${DUMMY_DIR}/$1" ]] || mkdir -p "${DUMMY_DIR}/$1"
    find "../src/zemu/$1" -name "*.z80" -depth 1 | while read Z80; do
        DUMMY="${DUMMY_DIR}/$1/$(basename "$Z80")"
        echo " " > "$DUMMY"
    done
}

dummy_dir . && dummy_dir ti83plus

# For each Z80 file, compile binary.
BIN_DIR=$(mktemp -d)
trap "rm -rf $BIN_DIR" EXIT
LOG=$(mktemp)
LOG2=$(mktemp)
trap "rm -f $LOG $LOG2" EXIT

assemble_dir() {
    [[ -d "${BIN_DIR}/$1" ]] || mkdir -p "${BIN_DIR}/$1" # make binary directory
    find "../src/zemu/$1" -name "*.z80" -depth 1 | while read Z80; do
        BIN="${BIN_DIR}/$1/$(basename "$Z80" z80)bin"
        spasm -N -DTI83PLUS=1 -I ../include/zemu -I ${DUMMY_DIR} "$Z80" "$BIN" > $LOG 2> $LOG2
        if ! [[ -f "$BIN" ]]; then
            echo "failed on $BIN"
            cat $LOG $LOG2
            exit 1
        fi

        # BEFORE=$(wc -c "$BIN" | awk '{ print $1 }')
        ZIP="$(dirname "$BIN")/$(basename "$BIN" bin)zip"
        PCT=$(zip "$ZIP" "$BIN" | grep -E "(deflated|stored)" | awk '/[[:digit:]]%+/ { print $NF }' | grep -Eo "[[:digit:]]+%")
        # AFTER=$(wc -c "$ZIP" | awk '{ print $1 }')

        echo "$1/$(basename "$BIN")" $PCT
        
    done
}

(assemble_dir . && assemble_dir ti83plus) | sort -rn -k2 | column -t

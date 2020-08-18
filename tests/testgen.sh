#!/bin/bash
# ZEMU test generator

usage() {
    cat <<EOF
usage: $0 [option...] [string...]
Options:
 -h            help
 -r <rom>      path to CE rom
 -t <target>   name of target
 -v <var_dir>  directory containing story variables
 -x <8xp>      path to *.8xp TI executable
 -o <output>   output CEmu JSON autotester file
 -k <str2key>  path to str2key binary
 -w <ms>       delay after each keypress, in ms
 -s <start>,<size>[,<lab>]
               specify start address and size for checksum. If <lab> is provided,
               it translates symbols <start> and <size> to values
 -R <readlab>  path to readlab binary
EOF
}

error() {
    echo "$1" >&2
    exit 1
}

join() {
    local IFS="$1"
    shift
    echo "$*"
}

# convert symbol to value using lab file
sym2val() {
    if ! [[ "$1" =~ [^[:digit:]] ]]; then
        echo $1
        return 0
    fi
        
    # otherwise lookup in LAB file
    DECIMAL=$("$READLAB" -e "$2" "$1") || exit 1
    printf '0x%x\n' "$DECIMAL"
}

ROM=
TARGET=
VARDIR=
EXEC=
OUT=/dev/fd/1
STR2KEY=
KEYDELAY=50 # default: 50 ms
LOCINFO=()
READLAB=

while getopts "hr:t:v:x:o:k:w:s:R:" OPTION; do
    case $OPTION in
        h)
            usage
            exit 0
            ;;
        r)
            ROM="$OPTARG"
            ;;
        t)
            TARGET="$OPTARG"
            ;;
        v)
            VARDIR="$OPTARG"
            ;;
        x)
            EXEC="$OPTARG"
            ;;
        o)
            OUT="$OPTARG"
            ;;
        k)
            STR2KEY="$OPTARG"
            ;;
        w)
            KEYDELAY="$OPTARG"
            ;;
        s)
            IFS=',' read -ra LOCINFO <<< "$OPTARG"
            ;;
        R)
            READLAB="$OPTARG"
            ;;
        "?")
            usage >&2
            exit 1
            ;;
    esac
done

shift $((OPTIND-1))

[ -z "$ROM" ]     && error "$0: specify ROM with '-r'"
[ -z "$TARGET" ]  && error "$0: specify target with '-t'"
[ -z "$VARDIR" ]  && error "$0: specify variable directory with '-v'"
[ -z "$EXEC" ]    && error "$0: specify *.8xp executable with '-x'"
[ -z "$STR2KEY" ] && error "$0: specify str2key binary with '-k'"

case ${#LOCINFO[@]} in
    0)
        ;;
    1)
        error "$0: '-s': missing location size"
        ;;
    *)
        [ -z "$READLAB" ] && error "$0: specify readlab binary with '-r'"
        ;;
esac

# truncate file
: > "$OUT"

cat >> "$OUT" <<EOF
{
   "rom": "$ROM",
   "transfer_files": [ 
EOF

# get list of files
for VAR in $(find "$VARDIR" -name "*.8xv"); do
    [ -z "$VARS" ] || VARS+=","
    cat >> "$OUT" <<EOF
       "$VAR",
EOF
done

cat >> "$OUT" <<EOF
       "$EXEC"
    ],
    "target": {
       "name": "$TARGET",
       "isASM": true
    },
    "delay_after_key": $KEYDELAY,
    "sequence": [
       "action|launch",
       "delay|2000",
EOF

# get string of keypresses
CMDS=()
STEP=0
CRCS=()
while [ $# -gt 0 ]; do
    # get string
    STRING="$1"
    shift
    
    # add keypress commands
    KEYS="$("$STR2KEY" "$STRING")" || exit 1
    read -ra KEYARR <<< "$KEYS"
    for KEY in "${KEYARR[@]}"; do
        CMDS+=("key|$KEY")
    done

    # get crc
    CRC="$1"
    shift
    CRCS+=("$CRC")
    
    # add enter keypress
    CMDS+=("hashWait|$STEP")

    ((++STEP))
done

# emit key seqs
NCMDS=${#CMDS[@]}
for ((I = 0; I < NCMDS; ++I)); do
    CMD="${CMDS[$I]}"
    if [[ $I -eq $(($NCMDS - 1)) ]]; then
        SEP=
    else
        SEP=","
    fi
    
    cat >> "$OUT" <<EOF
        "$CMD"$SEP
EOF
done

# emit hashes
cat >> "$OUT" <<EOF
    ],
    "hashes": {
EOF

# get start, size
START="vram_start"
SIZE="vram_16_size"

NLOCINFO=${#LOCINFO[@]}
if [[ $NLOCINFO -gt 0 ]]; then
    START="${LOCINFO[0]}"
    SIZE="${LOCINFO[1]}"
    if [[ $NLOCINFO -eq 3 ]]; then
        LAB="${LOCINFO[2]}"
        START=$(sym2val "$START" "$LAB") || exit 1 
        SIZE=$(sym2val "$SIZE" "$LAB") || exit 1
    fi
fi

NCRCS=${#CRCS[@]}
for ((I = 0; I < NCRCS; ++I)); do
    CRC="${CRCS[$I]}"
    if [[ $I -eq $(($NCRCS - 1)) ]]; then
        SEP=
    else
        SEP=","
    fi

    cat >> "$OUT" <<EOF
       "$I": {
          "description": "$I",
          "start": "$START",
          "size": "$SIZE",
          "expected_CRCs": ["$CRC"],
          "timeout": 5000
       }$SEP
EOF
done

cat >> "$OUT" <<EOF
    }
}
EOF

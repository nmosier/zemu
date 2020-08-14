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
 -c <crc32>    expected CRC code
 -m <desc>     description of test
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

ROM=
TARGET=
VARDIR=
EXEC=
OUT=
CRC=
DESC=

while getopts "hr:t:v:x:o:c:m:" OPTION; do
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
        c)
            CRC="$OPTARG"
            ;;
        m)
            DESC="$OPTARG"
            ;;
        "?")
            usage >&2
            exit 1
            ;;
    esac
done

shift $((OPTIND-1))

[ -z "$ROM" ]    && error "$0: specify ROM with '-r'"
[ -z "$TARGET" ] && error "$0: specify target with '-t'"
[ -z "$VARDIR" ] && error "$0: specify variable directory with '-v'"
[ -z "$EXEC" ]   && error "$0: specify *.8xp executable with '-x'"
[ -z "$OUT" ]    && OUT=/dev/fd/1  # output to stdout
[ -z "$CRC" ]    && error "$0: specify expected CRC32 code with '-c'"
[ -z "$DESC" ]   && DESC="$TARGET $VARDIR"

# get list of files
VARS="$(find "$VARDIR" -name "*.8xv")"

VARS=
for VAR in $(find "$VARDIR" -name "*.8xv"); do
    [ -z "$VARS" ] || VARS+=","
    VARS+="\"$VAR\""
done

cat > "$OUT" <<EOF
{
    "rom": "$ROM",
    "transfer_files": [ "$EXEC", $VARS ],
    "target": {
        "name": "$TARGET",
        "isASM": true
    },
    "sequence": [
        "action|launch",
        "delay|1000",
        "hash|1"
    ],
    "hashes": {
        "1": {
            "description": "$DESC",
            "start": "vram_start",
            "size": "vram_16_size",
            "expected_CRCs": ["$CRC"]
        }
    }
}
EOF

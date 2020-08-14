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
 -k <str2key>  path to str2key binary
 -w <ms>       delay after each keypress, in ms
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
OUT=/dev/fd/1
CRC=
DESC=
STR2KEY=
KEYDELAY=100 # default: 100 ms

while getopts "hr:t:v:x:o:c:m:k:w:" OPTION; do
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
        k)
            STR2KEY="$OPTARG"
            ;;
        w)
            KEYDELAY="$OPTARG"
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
[ -z "$CRC" ]     && error "$0: specify expected CRC32 code with '-c'"
[ -z "$DESC" ]    && DESC="$TARGET $VARDIR"
[ -z "$STR2KEY" ] && error "$0: specify str2key binary with '-k'"

# get list of files
VARS="$(find "$VARDIR" -name "*.8xv")"

VARS=
for VAR in $(find "$VARDIR" -name "*.8xv"); do
    [ -z "$VARS" ] || VARS+=","
    VARS+="\"$VAR\""
done

# get string of keypresses
KEYCMDS=
for STRING in "$@"; do
    # add keypress commands
    KEYS="$("$STR2KEY" "$STRING")"
    read -ra KEYARR <<< "$KEYS"
    for KEY in "${KEYARR[@]}"; do
        KEYCMDS+="\"key|$KEY\","
    done

    # add enter keypress
    KEYCMDS+="\"key|enter\","
    KEYCMDS+="\"delay|1000\","
done

cat > "$OUT" <<EOF
{
    "rom": "$ROM",
    "transfer_files": [ "$EXEC", $VARS ],
    "target": {
        "name": "$TARGET",
        "isASM": true
    },
    "delay_after_key": $KEYDELAY,
    "sequence": [
        "action|launch",
        "delay|1000",
        $KEYCMDS
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

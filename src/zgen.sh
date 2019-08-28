#!/bin/sh

USAGE="usage: $0 [-n zpage_size] [-v] story_file [outdir]"
ZMAP_BIN="./zmap"
ZPAGES_SH="./zpages.sh"
VERBOSE=""

while getopts "n:hv" optchar
do
    case "${optchar}" in
        n)
            ZPAGE_SIZE="${OPTARG}"
            ;;
        h)
            echo $USAGE
            exit 0
            ;;
        v)
            VERBOSE="-v"
            ;;
        *)
            echo $USAGE
            exit 1
            ;;
    esac
done
shift $((OPTIND-1))

if [ $# -lt 1 ]
then
    echo $USAGE
    exit 1
fi

if ! [ -n "${ZPAGE_SIZE}" ] || [ "${ZPAGE_SIZE}" -le 0 ]
then
    echo "$0: ZPAGE_SIZE must be defined as an environment variable or using the \`-n\' parameter"
    exit 1
fi

STORY_FILE="$1"
OUTDIR="."

# get filename
STORY_FILENAME=$(basename "${STORY_FILE}")
STORY_NAME="${STORY_FILENAME%.*}"

echo $STORY_NAME

if [ -n "$2" ]
then
    OUTDIR="$2"
fi

# create zpages
"${ZPAGES_SH}" -n "${ZPAGE_SIZE}" "${STORY_FILE}" "${OUTDIR}"

# create zmap
"${ZMAP_BIN}" -n "${ZPAGE_SIZE}" ${VERBOSE} "${STORY_FILE}" "${OUTDIR}/${STORY_NAME}R"[a-z][a-z]".8xv" | tipack -n "${STORY_NAME}" -t 8xv -o "${OUTDIR}/${STORY_NAME}.8xv"

exit 0

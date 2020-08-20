#!/bin/bash
# split story files into TI appvars

USAGE="usage: $0 [-n blk_size] story_file [outdir]"

while getopts "n:h" optchar
do
    case "${optchar}" in
        n)
            ZPAGE_SIZE="${OPTARG}"
            ;;
        h)
            echo $USAGE
            exit 0
            ;;
        *)
            echo $USAGE
            exit 1
            ;;
    esac
done
shift $((OPTIND-1))

if ! [ -n "$1" ]
then
    echo $USAGE
    exit 1
fi

# verify that page size is power of 2
MAX_ZPAGE_SIZE=65535
i=0
acc=1
while [[ $acc -lt $MAX_ZPAGE_SIZE ]]; do
    if [ $ZPAGE_SIZE -eq $acc ]
    then
        break
    fi
    i=$((i+1))
    acc=$((acc*2))
done
if [[ $acc -ge $MAX_ZPAGE_SIZE ]]; then
    echo "$0: zpage size must be power of 2"
    exit 1
fi

STORY_PATH="$1"
OUTDIR="$2"

echo "story file = $STORY_PATH"
echo "block size = $ZPAGE_SIZE"

# get story filename
STORY_FILENAME="${STORY_PATH##*/}"
echo "story filename = $STORY_FILENAME"

# get story directory
STORY_DIR="${STORY_PATH:0:$((${#STORY_PATH} - ${#STORY_FILENAME}))}"
STORY_DIR="${STORY_DIR:-.}"

# set default output directory
OUTDIR="${OUTDIR:-$STORY_DIR}"

# get story file prefix
STORY_PAGE_PREFIX="R"
STORY_STEM="${STORY_FILENAME%.*}${STORY_PAGE_PREFIX}"

echo "story path = $STORY_PATH"
echo "story filename = $STORY_FILENAME"
echo "story dir = $STORY_DIR"
echo "story stem = $STORY_STEM"

# make sure directory exists
if ! [ -d "$OUTDIR" ]
then
    mkdir "$OUTDIR"
fi

split -b `printf %d $ZPAGE_SIZE` "$STORY_PATH" "$OUTDIR/$STORY_STEM"

# convert them into vars
pushd "$OUTDIR"
BINS=`ls $STORY_STEM[a-z][a-z]`
for BIN in $BINS
do
    tipack -t 8xv -o "$BIN.8xv" "$BIN"
    rm "$BIN"
done
popd

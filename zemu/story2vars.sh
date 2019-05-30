#!/bin/sh
# split story files into TI appvars

USAGE="usage: $0 [-n blk_size] story_file [outdir]"

ZBLK_SIZE=0x1000

while getopts "n:h" optchar
do
    case "${optchar}" in
        n)
            ZBLK_SIZE="${OPTARG}"
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

STORY_PATH="$1"
OUTDIR="$2"

echo "story file = $STORY_PATH"
echo "block size = $ZBLK_SIZE"

# get story filename
STORY_FILENAME="${STORY_PATH##*/}"
echo "story filename = $STORY_FILENAME"

# get story directory
STORY_DIR="${STORY_PATH:0:$((${#STORY_PATH} - ${#STORY_FILENAME}))}"
STORY_DIR="${STORY_DIR:-.}"

# set default output directory
OUTDIR="${OUTDIR:-$STORY_DIR}"

# get story file prefix
STORY_STEM="${STORY_FILENAME%.*}"

echo "story path = $STORY_PATH"
echo "story filename = $STORY_FILENAME"
echo "story dir = $STORY_DIR"
echo "story stem = $STORY_STEM"

split -b `printf %d $ZBLK_SIZE` "$STORY_PATH" "$OUTDIR/$STORY_STEM"

# convert them into vars
pushd "$OUTDIR"
BINS=`ls $STORY_STEM[a-z][a-z]`
for BIN in $BINS
do
    tipack -t 8xv -o "$BIN.8xv" "$BIN"
    rm "$BIN"
done
popd

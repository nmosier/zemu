;; zemu.inc

#ifndef ZEMU_INC
#define ZEMU_INC

#include "zti.inc"
#include "util.inc"
#include "zfile.inc"

ZWORD_BYTE .equ 1
ZWORD_SIZE .equ 2

STORYSIZE_SIZE .equ 3

ZMAP_HDR_BEGIN      .equ 0
ZMAP_HDR_PAGEMASK   .equ ZMAP_HDR_BEGIN                 ; B
ZMAP_HDR_PAGEBITS   .equ ZMAP_HDR_PAGEMASK + BYTE_SIZE  ; B
ZMAP_HDR_STORYSIZE  .equ ZMAP_HDR_PAGEBITS + BYTE_SIZE ; B[3]
ZMAP_HDR_NPAGES     .equ ZMAP_HDR_STORYSIZE + STORYSIZE_SIZE ; B
ZMAP_HDR_STATIC     .equ ZMAP_HDR_NPAGES + BYTE_SIZE  ; W
ZMAP_HDR_END        .equ ZMAP_HDR_STATIC + WORD_SIZE

ZMAP_HDRSIZE        .equ ZMAP_HDR_END - ZMAP_HDR_BEGIN

ZMAP_ENT.FILE  .equ 0
ZMAP_ENT.FLAGS .equ ZMAP_ENT.FILE + SIZEOF_FILE
SIZEOF_ZMAP_ENT .equ ZMAP_ENT.FLAGS + BYTE_SIZE

ZMAP_ENT.FLAGS.COPY .equ 0   ; whether page should be copied
ZMAP_ENT.FLAGS.SAVE .equ 1   ; whether page should be saved

ZPACK .equ 2 ; scaling factor

WIN_DBGIN_BUFSIZE .equ 32


;; NAMING CONVENTION ;;
ZNAME_CURMAP .equ 'M'

STORY_NAME_MAXLEN .equ 4

ZADDR_NULL .equ ULONG_MAX

;; MAIN WINDOWS
#if TI83PLUS
win_main.buflen .equ 256
#elif TI84PCE
win_main.buflen .equ 512
#endif


#endif

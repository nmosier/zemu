;; zemu.inc

#ifndef ZEMU_INC
#define ZEMU_INC

#include "zti.inc"
#include "util.inc"

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

ZMAP_ENT_VARNAME .equ 0                           ; char[]
ZMAP_ENT_FLAGS .equ ZMAP_ENT_VARNAME + VARNAMELEN ; B
ZMAP_ENT_PTR .equ ZMAP_ENT_FLAGS + BYTE_SIZE      ; L
ZMAP_TABENTLEN .equ ZMAP_ENT_PTR + LONG_SIZE

ZMAP_ENT_FLAGS_INRAM .equ 0
ZMAP_ENT_FLAGS_COPY .equ 1   ; whether page should be copied
ZMAP_ENT_FLAGS_SAVE .equ 2   ; whether page should be saved
ZMAP_ENT_FLAGS_UPDATE .equ 3 ; whether pointer needs to be updated

ZPACK .equ 2 ; scaling factor

WIN_DBGIN_BUFSIZE .equ 32


;; NAMING CONVENTION ;;
ZNAME_CURMAP .equ 'M'

STORY_NAME_MAXLEN .equ 4

ZADDR_NULL .equ ULONG_MAX

#define ZFRAME_SIZE zframe_end-zframe_begin

#endif

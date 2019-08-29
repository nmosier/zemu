;; zemu.inc

#ifndef __ZEMU_INC
#define __ZEMU_INC

#include "zutil.inc"

ZBYTE_SIZE .equ 1
ZWORD_SIZE .equ 2

ZMAP_TABENTLEN .equ (VARNAMELEN + 1 + 3) ; this should be manually updated

ZMAP_HDR_BEGIN      .equ 0
ZMAP_HDR_PAGEMASK   .equ ZMAP_HDR_BEGIN
ZMAP_HDR_PAGEBITS   .equ ZMAP_HDR_PAGEMASK + 1
ZMAP_HDR_STORYSIZE  .equ ZMAP_HDR_PAGEBITS + 1
ZMAP_HDR_NPAGES     .equ ZMAP_HDR_STORYSIZE + 3
ZMAP_HDR_STATIC     .equ ZMAP_HDR_NPAGES + 1
ZMAP_HDR_END        .equ ZMAP_HDR_STATIC + 2

ZMAP_HDRSIZE        .equ ZMAP_HDR_END - ZMAP_HDR_BEGIN

ZMAP_ENT_VARNAME .equ 0
ZMAP_ENT_FLAGS .equ ZMAP_ENT_VARNAME + VARNAMELEN
ZMAP_ENT_PTR .equ ZMAP_ENT_FLAGS + 1

ZMAP_ENT_FLAGS_INRAM .equ 0
ZMAP_ENT_FLAGS_COPY .equ 1   ; whether page should be copied
ZMAP_ENT_FLAGS_SAVE .equ 2   ; whether page should be saved
ZMAP_ENT_FLAGS_UPDATE .equ 3 ; whether pointer needs to be updated

ZPACK .equ 2 ; scaling factor

WIN_DBGIN_BUFSIZE .equ 32


;; NAMING CONVENTION ;;
ZNAME_CURMAP .equ 'M'

STORY_NAME_MAXLEN .equ 4



#define ZFRAME_SIZE zframe_end-zframe_begin

#endif

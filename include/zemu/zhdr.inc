;; zhdr.inc -- equates for story file headers

#ifndef __ZHDR_INC
#define __ZHDR_INC

#include "zemu.inc"
#include "zutil.inc"

;; Header Fields ;;
ZHDR_VERSION  .equ $00
ZHDR_FLAGS1   .equ $01
ZHDR_FLAGS1_NOSTAT .equ 4
ZHDR_FLAGS1_SCRNSPLIT .equ 5
ZHDR_FLAGS1_VARFONTDEF .equ 6
ZHDR_HIGHMEM  .equ $04
ZHDR_INITPC   .equ $06
ZHDR_DICT     .equ $08
ZHDR_OBJTAB   .equ $0a
ZHDR_GLOBALS  .equ $0c
ZHDR_STATIC   .equ $0e
ZHDR_FLAGS2   .equ $10
ZHDR_FLAGS2_TRANS .equ 0
ZHDR_FLAGS2_FIXEDPITCH .equ 1
ZHDR_ABBR     .equ $18
ZHDR_STORYLEN .equ $1a
ZHDR_CHKSUM   .equ $1a
ZHDR_STDREVNO .equ $32

;; ZEMU Defaults Table ;;
ZHDR_DEFENT.TYPE .equ 0
ZHDR_DEFENT.OFF .equ ZHDR_DEFENT.TYPE + BYTE_SIZE

ZHDR_DEFENT_SETBIT.BIT .equ ZHDR_DEFENT.OFF + BYTE_SIZE
ZHDR_DEFENT_SETBIT_SIZE .equ ZHDR_DEFENT_SETBIT.BIT + BYTE_SIZE

ZHDR_DEFENT_RESBIT.BIT .equ ZHDR_DEFENT.OFF + BYTE_SIZE
ZHDR_DEFENT_RESBIT_SIZE .equ ZHDR_DEFENT_RESBIT.BIT + BYTE_SIZE

ZHDR_DEFENT_BYTE.VAL .equ ZHDR_DEFENT.OFF + BYTE_SIZE
ZHDR_DEFENT_BYTE_SIZE .equ ZHDR_DEFENT_BYTE.VAL + BYTE_SIZE

ZHDR_DEFENT_WORD.VAL .equ ZHDR_DEFENT.OFF + BYTE_SIZE
ZHDR_DEFENT_WORD_SIZE .equ ZHDR_DEFENT_WORD.VAL + WORD_SIZE

;; Defaults Entry Types ;;
ZHDR_DEFENT_NULL   .equ 0
ZHDR_DEFENT_SETBIT .equ 1
ZHDR_DEFENT_RESBIT .equ 2
ZHDR_DEFENT_BYTE   .equ 3
ZHDR_DEFENT_WORD   .equ 4

;; Defaults Entry Construction Macros ;;
#define D_ZHDR_DEFENT_NULL() .db ZHDR_DEFENT_NULL

#define D_ZHDR_DEFENT_SETBIT(off, b) .db ZHDR_DEFENT_SETBIT, off, b

#define D_ZHDR_DEFENT_RESBIT(off, b) .db ZHDR_DEFENT_RESBIT, off, b

#define D_ZHDR_DEFENT_BYTE(off, val) .db ZHDR_DEFENT_BYTE, off, val

#macro D_ZHDR_DEFENT_WORD(off, val)
   .db ZHDR_DEFENT_WORD, off
   .dw val
#endmacro

#endif
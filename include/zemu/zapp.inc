#ifndef __ZAPP_INC
#define __ZAPP_INC

#include "zemu.inc"
#include "zutil.inc"
#include "zti.inc"

;; SYMBOL TABLE EQUATES ;;
SYMENT         .equ 0
SYMENT.T       .equ SYMENT                  ; W
SYMENT.T2      .equ SYMENT.T + WORD_SIZE    ; W
SYMENT.VER     .equ SYMENT.T2 + WORD_SIZE   ; W
SYMENT.ADDR    .equ SYMENT.VER + WORD_SIZE  ; L
SYMENT.NL      .equ SYMENT.ADDR + LONG_SIZE ; B
SYMENT.VARNAME .equ SYMENT.NL + BYTE_SIZE   ; char[]
SYMENT_MAXSIZE .equ SYMENT.VARNAME + VARNAMELEN

#endif
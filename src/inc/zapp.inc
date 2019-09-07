#ifndef __ZAPP_INC
#define __ZAPP_INC

#include "zemu.inc"
#include "zutil.inc"

;; SYMBOL TABLE EQUATES ;;
SYMENT.T       .equ 0   ; W
SYMENT.T2      .equ 2   ; W
SYMENT.VER     .equ 4   ; W
SYMENT.ADDR    .equ 6   ; L
SYMENT.NL      .equ 9   ; B
SYMENT.VARNAME .equ 10  ; char[]

SYMENT_MAXSIZE .equ SYMENT.VARNAME + VARNAMELEN

#endif
; zstr.inc -- routines for printing ZSCII codes

#ifndef __ZSTR_INC
#define __ZSTR_INC

#include "ti84pce.inc"

ZSTR_CODE_WIDTH .equ 5

ZSTR_A1 .equ 4
ZSTR_A2 .equ 5

ZSTR_ABBRMIN .equ 1
ZSTR_ABBRMAX .equ 3

ZSTR_AMIN .equ $6
ZSTR_AMAX .equ $1f

ZSTR_ALEN .equ ZSTR_AMAX - ZSTR_AMIN + 1

ZSTR_NEWLINE .equ '^'

ASCII_NEWLINE .equ $F2
ASCII_DEL .equ $F3
ASCII_CLEAR .equ $F4

ZSTR_NCODES .equ 32
ZSTR_CODEMASK .equ $1f

ZSTR_FLAGS_SHIFT .equ 0  ; shift enabled for next character?
ZSTR_FLAGS_AX    .equ 1  ; Z = A1, NZ = A2
ZSTR_FLAGS_ABBR  .equ 2  ; expecting abbreviation code?

STRLEN_LONG .equ 8

#macro A0(c)
       c-'a'+ZSTR_AMIN
#endmacro

#macro A1(c)
       c-'A'+ZSTR_AMIN
#endmacro

#macro A2(n)
       n+ZSTR_AMIN
#endmacro       

#macro STRW(a,b,c)
       (a << (ZSTR_CODE_WIDTH * 2)) + (b << ZSTR_CODE_WIDTH) + c
#endmacro

#macro STRWT(a,b,c)
       (STRW(a,b,c)) | $8000
#endmacro       

#macro JCLASS(low, hi, label)
       cp a,low
       jr c,_
       cp a,hi+1
       jr c,label
_      
#endmacro

#macro JCHAR(cmpval, newval, label)
       cp a,cmpval
       jr nz,_
       ld a,newval
       jr label
_
#endmacro

ZENCODE_MAXCHARLEN .equ 3

ZENCODE_BUFSIZE .equ zstr_encode.buf_end - zstr_encode.buf

ZENCODE_TABENT_CH1  .equ 0
ZENCODE_TABENT_CH2  .equ 1

ZENCODE_TABENTSIZE  .equ 2

ZSTR_EMPTYSTR .equ ($1 << (5*3)) | (ZSTR_A2 << (5*2)) | (ZSTR_A2 << (5*1)) | (ZSTR_A2 << (5*0))

;; Z-aliases for system routines
;sysputc      .equ _VPutMap
sysputs      .equ _VPutS
syscurrow    .equ penRow
syscurcol    .equ penCol

#endif

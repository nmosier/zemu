; zstr.inc -- routines for printing ZSCII codes

#ifndef __ZSTR_INC
#define __ZSTR_INC

ZSTR_CODE_WIDTH .equ 5

ZSTR_A1 .equ 4
ZSTR_A2 .equ 5

ZSTR_ABBRMIN .equ 1
ZSTR_ABBRMAX .equ 3

ZSTR_AMIN .equ $6
ZSTR_AMAX .equ $1f

ZSTR_ALEN .equ ZSTR_AMAX - ZSTR_AMIN + 1

ZSTR_NEWLINE .equ '^'

ZSTR_NCODES .equ 32
ZSTR_CODEMASK .equ $1f

ZSTR_FLAGS_SHIFT .equ 0  ; shift enabled for next character?
ZSTR_FLAGS_AX    .equ 1  ; Z = A1, NZ = A2
ZSTR_FLAGS_ABBR  .equ 2  ; expecting abbreviation code?

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

#endif
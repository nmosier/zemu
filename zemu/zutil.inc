#ifndef __ZUTIL_INC
#define __ZUTIL_INC

LONG_MIN .equ $800000
LONG_MAX .equ LONG_MIN - 1

LONG_SIZE .equ 3

ZFALSE .equ $000000
ZTRUE .equ  $000001

VARNAMELEN .equ 8

#macro RESB(n)
#if n > 0
    .db 0
    RESB(n-1)
#endif
#endmacro

#macro RESW(n)
#if n > 0
    .dw 0
    RESW(n-1)
#endif
#endmacro

#macro RESL(n)
#if n > 0
    .dl 0
    RESL(n-1)
#endif    
#endmacro

#endif

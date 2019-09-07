#ifndef __ZUTIL_INC
#define __ZUTIL_INC

#include "zti.inc"

ZFALSE .equ $000000
ZTRUE .equ  $000001

VARNAMELEN .equ 8


#macro RESB(n)
#if n > 0
    DB 0
    RESB(n-1)
#endif
#endmacro

#macro RESW(n)
#if n > 0
    DW 0
    RESW(n-1)
#endif
#endmacro

#macro RESL(n)
#if n > 0
    DL 0
    RESL(n-1)
#endif    
#endmacro


#macro MASK(n)
    1 << n
#endmacro

#macro LOW(i)
    i & $ff
#endmacro

#macro HIGH(i)
    LOW((i >> 8))
#endmacro


;; ADDRESS SIZE SCALING ;;
#macro MLTA_A_TO_HL()
   UCAST_A_TO_HL
   sla l
   rl h
   add a,l
   ld l,a
   jr nc,_
   inc h
_
#endmacro

#macro MLTA_A_TO_BC()
   UCAST_A_TO_BC
   sla c
   rl b
   add a,c
   ld c,a
   jr nc,_
   inc b
_
#endmacro

R_HL .equ 0
R_DE .equ 1
R_BC .equ 2
R_IX .equ 3
R_IY .equ 4

#macro LD_REG_IMM(reg, imm)
#if reg == R_HL
   ld hl,imm
#elif reg == R_DE
   ld de,imm
#elif reg == R_BC
   ld bc,imm
#elif reg == R_IX
   ld ix,imm
#elif reg == R_IY
   ld iy,imm
#endif
#endmacro

#macro ADD_HL_REG(reg)
#if reg == R_HL
   add hl,hl
#elif reg == R_DE
   add hl,de
#elif reg == R_BC
   add hl,bc
#endif
#endmacro

#macro ADD_IX_REG(reg)
#if reg == R_DE
   add ix,de
#elif reg == R_BC
   add ix,bc
#elif reg == R_IX
   add ix,ix
#endif
#endmacro


#endif



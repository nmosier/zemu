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

#define LD_BC_HL push hl \\ pop bc
#define LD_BC_DE push de \\ pop bc
#define LD_HL_BC push bc \\ pop hl
#define LD_DE_BC push bc \\ pop de
#define LD_IX_DE push de \\ pop ix
#define LD_IX_HL push hl \\ pop ix

#define EX_BC_HL push bc \\ ex (sp),hl \\ pop bc

#define EX_BC_DE EX_BC_HL \\ ex de,hl \\ EX_BC_HL

;; COMPATABILE UPPER-BYTE INITIALIZATION ;;

#define CLEAR_UPPER_HL ld hl,0
#define CLEAR_UPPER_DE ld de,0
#define CLEAR_UPPER_BC ld bc,0
#define CLEAR_UPPER_IX ld ix,0
#define CLEAR_UPPER_IY ld iy,0

;; 8-bit to 16-/24-bit CASTING ;;
#define UCAST_A_TO_HL   ld hl,0 \\ ld l,a
#define UCAST_A_TO_DE   ld de,0 \\ ld e,a
#define UCAST_A_TO_BC   ld bc,0 \\ ld c,a

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

#endif



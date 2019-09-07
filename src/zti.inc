#ifndef __ZTI_INC
#define __ZTI_INC


BYTE_SIZE .equ 1
WORD_SIZE .equ 2


#define DB .db
#define DW .dw

#ifdef TI84PCE
;;;;; TI 84 PLUS CE ;;;;;
#undef TI84PCE
#include "ti84pce.inc"
#define TI84PCE

LONG_SIZE .equ 3

PENCOL_SIZE .equ LONG_SIZE

#define DL .dl

#define CLEAR_UPPER_HL ld hl,0
#define CLEAR_UPPER_DE ld de,0
#define CLEAR_UPPER_BC ld bc,0
#define CLEAR_UPPER_IX ld ix,0
#define CLEAR_UPPER_IY ld iy,0

#define UCAST_A_TO_HL   ld hl,0 \\ ld l,a
#define UCAST_A_TO_DE   ld de,0 \\ ld e,a
#define UCAST_A_TO_BC   ld bc,0 \\ ld c,a

#define LD_BC_HL push hl \\ pop bc
#define LD_BC_DE push de \\ pop bc
#define LD_HL_BC push bc \\ pop hl
#define LD_DE_BC push bc \\ pop de
#define LD_IX_DE push de \\ pop ix
#define LD_IX_HL push hl \\ pop ix

#define LEA_IX_IX(off, reg) lea ix,ix+off

#define LD_HL_FROM_IX(off) ld hl,(ix+off)

#macro MLT_A(off, reg16)
#if reg16 == R_HL
   ld hl,off
   ld h,a
   mlt hl
#elif reg16 == R_DE
   ld de,off
   ld d,a
   mlt de
#elif reg16 == R_BC
   ld bc,off
   ld b,a
   mlt bc
#endif
#endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;
#endif

#ifdef TI83PLUS
;;;;; TI 83 PLUS ;;;;;
#undef TI83PLUS
#include "ti83plus.inc"
#define TI83PLUS

LONG_SIZE .equ WORD_SIZE

PENCOL_SIZE .equ BYTE_SIZE

#define DL DW

#define CLEAR_UPPER_HL
#define CLEAR_UPPER_DE
#define CLEAR_UPPER_BC
#define CLEAR_UPPER_IX
#define CLEAR_UPPER_IY

#define UCAST_A_TO_HL   ld h,0 \\ ld l,a
#define UCAST_A_TO_DE   ld d,0 \\ ld e,a
#define UCAST_A_TO_BC   ld b,0 \\ ld c,a

#define LD_BC_HL ld b,h \\ ld c,l
#define LD_BC_DE ld b,d \\ ld c,e
#define LD_HL_BC ld h,b \\ ld l,c
#define LD_DE_BC ld d,b \\ ld e,c
#define LD_IX_DE ld ixh,d \\ ld ixl,e
#define LD_IX_HL ld ixh,h \\ ld ixl,l


#macro LEA_IX_IX(off, reg)
   LD_REG_IMM(reg, off)
   ADD_IX_REG(reg)
#endmacro

#macro LD_HL_FROM_IX(off)
   ld l,(ix+off)
   ld h,(ix+off)
#endmacro

#macro MLT_A(off, reg16)
#if reg16 == R_HL
   ld hl,off
   push af
   call mul_hl_a
   pop af
#elif reg16 == R_DE
   ex de,hl
   ld hl,off
   push af
   call mul_hl_a
   pop af
   ex de,hl
#elif reg16 == R_BC
   push hl
   ld hl,off
   push af
   call mul_hl_a
   pop af
   LD_BC_HL
   pop hl
#endif
#endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;
#endif

LONG_BITS .equ LONG_SIZE * 8
LONG_MIN .equ 1 << (LONG_BITS - 1)
LONG_MAX .equ LONG_MIN - 1
ULONG_MIN .equ 0
ULONG_MAX .equ (1 << LONG_BITS) - 1

PENROW_SIZE .equ BYTE_SIZE


#endif
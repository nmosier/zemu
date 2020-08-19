#ifndef TI83PLUS_ZADDR_INC
#define TI83PLUS_ZADDR_INC

#include "util.inc"

#define DZA(zaddr) .db LOW_IMM(zaddr), HIGH_IMM(zaddr), UPPER_IMM(zaddr)

#macro LD_BHL_FROM_IX_ZA(off)
  ld l,(ix+off+0)
  ld h,(ix+off+1)
  ld b,(ix+off+2)
#endmacro
#macro LD_CDE_FROM_IX_ZA(off)
  ld e,(ix+off+0)
  ld d,(ix+off+1)
  ld c,(ix+off+2)
#endmacro

#macro LD_BHL_FROM_IX_ZAW(off)
  LD_HL_FROM_IX_W(off)
  ld b,0  
#endmacro
#macro LD_CDE_FROM_IX_ZAW(off)
  LD_DE_FROM_IX_W(off)
  ld c,0  
#endmacro

#macro LD_BHL_FROM_IY_ZA(off)
  ld l,(iy+off+0)
  ld h,(iy+off+1)
  ld b,(iy+off+2)
#endmacro
#macro LD_CDE_FROM_IY_ZA(off)
  ld e,(iy+off+0)
  ld d,(iy+off+1)
  ld c,(iy+off+2)
#endmacro

#macro LD_BHL_FROM_IY_ZAW(off)
  LD_HL_FROM_IY_W(off)
  ld b,0  
#endmacro
#macro LD_CDE_FROM_IY_ZAW(off)
  LD_DE_FROM_IY_W(off)
  ld c,0  
#endmacro

#macro LD_CDE_TO_IX_ZA(off)
  LD_DE_TO_IX_W(off)
  ld (ix+off+2),c
#endmacro

#macro LD_BHL_FROM_ABS_ZA(addr)
  ld l,a
  ld a,(addr+2)
  ld b,a
  ld a,l
  ld hl,(addr)
#endmacro
#macro LD_CDE_FROM_ABS_ZA(addr)
  ld e,a
  ld a,(addr+2)
  ld c,a
  ld a,e
  ld de,(addr)
#endmacro

#macro LD_BHL_TO_ABS_ZA(addr)
  ld (addr+1),bc
  ld (addr),hl
#endmacro
#macro LD_CDE_TO_ABS_ZA(addr)
  push af
  ld (addr),de
  ld a,c
  ld (addr+2),a
  pop af
#endmacro

#macro LD_BHL_IMM(imm)
  ld hl, imm & $ffff
  ld b, UPPER_IMM(imm)
#endmacro
#macro LD_CDE_IMM(imm)
  ld de, imm & $ffff
  ld c, UPPER_IMM(imm)
#endmacro

#define INC_BHL_ZA call zaddr_inc
#define DEC_BHL_ZA call zaddr_dec

#macro PUSH_BHL_ZA
  push bc
  inc sp
  push hl
#endmacro
#macro POP_BHL_ZA
  pop hl
  dec sp
  ex (sp),hl
  ld b,h
  pop hl
#endmacro

#macro PUSH_CDE_ZA
  EX_CDE_BHL_ZA
  PUSH_BHL_ZA  
  EX_CDE_BHL_ZA
#endmacro
#macro POP_CDE_ZA
  EX_CDE_BHL_ZA
  POP_BHL_ZA
  EX_CDE_BHL_ZA
#endmacro


#define UCAST_A_TO_BHL_ZA UCAST_A_TO_HL \\ ld b,0
#define UCAST_A_TO_CDE_ZA UCAST_A_TO_DE \\ ld c,0

#define UCAST_HL_TO_BHL_ZA ld b,0
#define UCAST_DE_TO_CDE_ZA ld c,0

#define ADD_BHL_CDE_ZA call zaddr_add
#macro ADD_BHL_DE_ZA
  add hl,de
  jr nc,_
  inc b
_
#endmacro

#define EX_CDE_BHL_ZA call zaddr_ex

#endif

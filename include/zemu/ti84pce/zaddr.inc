#ifndef TI84PCE_ZADDR_INC
#define TI84PCE_ZADDR_INC

#include "zti.inc"

#define DZA(zaddr) .dl zaddr

#define zaddr_cp cp_hl_de

#define LD_BHL_FROM_IX_ZA(off) LD_HL_FROM_IX(off)
#define LD_CDE_FROM_IX_ZA(off) LD_DE_FROM_IX(off)

#macro LD_BHL_FROM_IX_ZAW(off)
  ld hl,0
  ld l,(ix+off+0)
  ld h,(ix+off+1)
#endmacro
#macro LD_CDE_FROM_IX_ZAW(off)
  ld de,0
  ld e,(ix+off+0)
  ld d,(ix+off+1)
#endmacro

#define LD_BHL_FROM_IY_ZA(off) LD_HL_FROM_IY(off)
#define LD_CDE_FROM_IY_ZA(off) LD_DE_FROM_IY(off)

#macro LD_BHL_FROM_IY_ZAW(off)
  ld hl,0
  ld l,(iy+off+0)
  ld h,(iy+off+1)
#endmacro
#macro LD_CDE_FROM_IY_ZAW(off)
  ld de,0
  ld e,(iy+off+0)
  ld d,(iy+off+1)
#endmacro


#define LD_BHL_IMM(imm) ld hl,imm
#define LD_CDE_IMM(imm) ld de,imm

#define INC_BHL_ZA inc hl
#define DEC_BHL_ZA dec hl

#define PUSH_BHL_ZA push hl
#define PUSH_CDE_ZA push de
#define POP_BHL_ZA  pop hl
#define POP_CDE_ZA  pop de

#define UCAST_A_TO_BHL_ZA UCAST_A_TO_HL
#define UCAST_A_TO_CDE_ZA UCAST_A_TO_DE

#macro UCAST_HL_TO_BHL_ZA
#endmacro
#macro UCAST_DE_TO_CDE_ZA
#endmacro

#define ADD_BHL_CDE_ZA add hl,de
#define ADD_BHL_DE_ZA  add hl,de

#define LD_BHL_FROM_ABS_ZA(addr) ld hl,(addr)
#define LD_CDE_FROM_ABS_ZA(addr) ld de,(addr)
#define LD_BHL_TO_ABS_ZA(addr) ld (addr),hl
#define LD_CDE_TO_ABS_ZA(addr) ld (addr),de

#define EX_CDE_BHL_ZA ex de,hl

#endif

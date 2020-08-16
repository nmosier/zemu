#ifndef TI84PCE_ZADDR_INC
#define TI84PCE_ZADDR_INC

#include "zti.inc"

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

#define INC_BHL_ZA inc hl

#define PUSH_BHL_ZA push hl
#define POP_BHL_ZA  pop hl

#define UCAST_A_TO_BHL_ZA UCAST_A_TO_HL
#define UCAST_A_TO_CDE_ZA UCAST_A_TO_DE

#endif

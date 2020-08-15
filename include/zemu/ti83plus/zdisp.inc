#ifndef __TI83PLUS_ZDISP_INC
#define __TI83PLUS_ZDISP_INC

#include "zti.inc"

SFONT_HEIGHT .equ $07

SFONT_TAB_ENTLEN .equ $08

DISP_WIDTH .equ 96
DISP_HEIGHT .equ 64

DISP_VRAM .equ plotSScreen

#define MLT_A_DISP_WIDTH(reg) MLT_A(DISP_WIDTH, reg)

#define DCOL DB
COL_SIZE .equ 1

#define LD_COL_FROM_IX(off, reg) LD_REG8_FROM_IX(off, R_LOW(reg))

;; Macros for load/store columns
#macro LD_HL_FROM_IX_C(off)
  ld h,0
  ld l,(ix+off)
#endmacro
#macro LD_DE_FROM_IX_C(off)
  ld d,0
  ld e,(ix+off)
#endmacro
#macro LD_BC_FROM_IX_C(off)
  ld b,0
  ld c,(ix+off)
#endmacro

#define LD_HL_TO_IX_C(off) ld (ix+off),l
#define LD_DE_TO_IX_C(off) ld (ix+off),e
#define LD_BC_TO_IX_C(off) ld (ix+off),c


#macro LD_HL_FROM_IY_C(off)
  ld h,0
  ld l,(iy+off)
#endmacro
#macro LD_DE_FROM_IY_C(off)
  ld d,0
  ld e,(iy+off)
#endmacro
#macro LD_BC_FROM_IY_C(off)
  ld b,0
  ld c,(iy+off)
#endmacro

#define LD_HL_TO_IY_C(off) ld (iy+off),l
#define LD_DE_TO_IY_C(off) ld (iy+off),e
#define LD_BC_TO_IY_C(off) ld (iy+off),c


#endif
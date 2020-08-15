#ifndef __TI84PCE_ZDISP_INC
#define __TI84PCE_ZDISP_INC

#include "zti.inc"

SFONT_TAB_ENTLEN .equ $19

DISP_WIDTH .equ lcdWidth
DISP_HEIGHT .equ lcdHeight

DISP_VRAM .equ vRam

PIXEL_SIZE .equ 2

;; NOTE: accounts for 2 bytes per pixel.
#macro MLT_A_DISP_WIDTH(reg)
   MLT_A(DISP_WIDTH/2, reg)
   add hl,hl               
   add hl,hl
#endmacro

COL_SIZE .equ LONG_SIZE
#define DCOL DL

;; Macros for load/store columns
#define LD_HL_FROM_IX_C(off) LD_HL_FROM_IX(off)
#define LD_DE_FROM_IX_C(off) LD_DE_FROM_IX(off)
#define LD_BC_FROM_IX_C(off) LD_BC_FROM_IX(off)

#define LD_HL_TO_IX_C(off) LD_HL_TO_IX(off)
#define LD_DE_TO_IX_C(off) LD_DE_TO_IX(off)
#define LD_BC_TO_IX_C(off) LD_BC_TO_IX(off)

#define LD_HL_FROM_IY_C(off) LD_HL_FROM_IY(off)
#define LD_DE_FROM_IY_C(off) LD_DE_FROM_IY(off)
#define LD_BC_FROM_IY_C(off) LD_BC_FROM_IY(off)

#define LD_HL_TO_IY_C(off) LD_HL_TO_IY(off)
#define LD_DE_TO_IY_C(off) LD_DE_TO_IY(off)
#define LD_BC_TO_IY_C(off) LD_BC_TO_IY(off)

#endif
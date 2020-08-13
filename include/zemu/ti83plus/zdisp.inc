#ifndef __TI83PLUS_ZDISP_INC
#define __TI83PLUS_ZDISP_INC

#include "zti.inc"

SFONT_TAB_ENTLEN .equ $08

DISP_WIDTH .equ 96
DISP_HEIGHT .equ 64

DISP_VRAM .equ plotSScreen

#define MLT_A_DISP_WIDTH(reg) MLT_A(DISP_WIDTH, reg)

#define DCOL DB
COL_SIZE .equ 1

#define LD_COL_FROM_IX(off, reg) LD_REG8_FROM_IX(off, R_LOW(reg))

#endif
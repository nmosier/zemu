#ifndef __TI83PLUS_ZDISP_INC
#define __TI83PLUS_ZDISP_INC

#include "zti.inc"

SFONT_TAB_ENTLEN .equ $08

DISP_WIDTH .equ 128
DISP_HEIGHT .equ 96

DISP_VRAM .equ plotSScreen
PIXEL_SIZE .equ 1 ; 1 byte per pixel in VRAM

#define MLT_A_DISP_WIDTH(reg) MLT_A(DISP_WIDTH, reg)

#define DCOL DB

#define LD_COL_FROM_IX(off, reg) LD_REG8_FROM_IX(off, R_LOW(reg))

#endif
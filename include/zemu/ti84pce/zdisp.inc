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

#define DCOL DL

#endif
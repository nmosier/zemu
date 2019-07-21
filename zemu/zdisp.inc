;; zdisp.inc -- display routines & system entry points

#ifndef __ZDISP_INC
#define __ZDISP_INC

#include "ti84pce.inc"

SFONT_HEIGHT .equ $0e ; TODO: adjust this.

SFONT_TAB_ADDR .equ $092694
SFONT_TAB_ENTLEN .equ $19

DISP_WIDTH .equ lcdWidth
DISP_HEIGHT .equ lcdHeight

PIXEL_SIZE .equ 1 ; bytes per pixel

VRAM_WIDTH .equ DISP_WIDTH * PIXEL_SIZE


#endif

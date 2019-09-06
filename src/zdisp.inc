;; zdisp.inc -- display routines & system entry points

#ifndef __ZDISP_INC
#define __ZDISP_INC

#include "zti.inc"

SFONT_HEIGHT .equ $0e ; TODO: adjust this.

SFONT_TAB_ADDR .equ $092694
SFONT_TAB_ENTLEN .equ $19

DISP_WIDTH .equ lcdWidth
DISP_HEIGHT .equ lcdHeight

PIXEL_SIZE .equ 2

;; struct zrect
;; L orgcol
;; B orgrow
;; L width
;; B height
ZRECT.ORGCOL .equ 0
ZRECT.ORGROW .equ 3
ZRECT.WIDTH  .equ 4
ZRECT.HEIGHT .equ 7

ZRECT_SIZE .equ 8


#macro D_ZRECT(orgcol, orgrow, width, height)
       .dl orgcol
       .db orgrow
       .dl width
       .db height
#endmacro

#endif

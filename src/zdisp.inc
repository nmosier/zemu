;; zdisp.inc -- display routines & system entry points

#ifndef __ZDISP_INC
#define __ZDISP_INC

#include "zti.inc"

SFONT_HEIGHT .equ $0e ; TODO: adjust this?

SFONT_TAB_ADDR .equ $092694
SFONT_TAB_ENTLEN .equ $19

#ifdef TI84PCE
DISP_WIDTH .equ lcdWidth
DISP_HEIGHT .equ lcdHeight
#endif
#ifdef TI83PLUS
DISP_WIDTH .equ 128
DISP_HEIGHT .equ 96
#endif

;; TODO -- this is TI84PCE-dependent
PIXEL_SIZE .equ 2

;; struct zrect
;; L orgcol
;; B orgrow
;; L width
;; B height
ZRECT.ORGCOL .equ 0
ZRECT.ORGROW .equ ZRECT.ORGCOL + LONG_SIZE
ZRECT.WIDTH  .equ ZRECT.ORGROW + BYTE_SIZE
ZRECT.HEIGHT .equ ZRECT.WIDTH + LONG_SIZE

ZRECT_SIZE .equ ZRECT.HEIGHT + BYTE_SIZE

#ifdef TI84PCE
#define DCOL DL
#endif
#ifdef TI83PLUS
#define DCOL DB
#endif

#define DROW DB

#macro D_ZRECT(orgcol, orgrow, width, height)
       DCOL orgcol
       DROW orgrow
       DCOL width
       DROW height
#endmacro


#endif

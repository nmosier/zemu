;; zdisp.inc -- display routines & system entry points

#ifndef __ZDISP_INC
#define __ZDISP_INC

#include "zti.inc"

#if TI84PCE
#include "ti84pce/zdisp.inc"
#endif
#if TI83PLUS
#include "ti83plus/zdisp.inc"
#endif

SFONT_HEIGHT .equ $0e ; TODO: adjust this?

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

#define DROW DB

#macro D_ZRECT(orgcol, orgrow, width, height)
       DCOL orgcol
       DROW orgrow
       DCOL width
       DROW height
#endmacro

#endif

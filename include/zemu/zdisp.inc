;; zdisp.inc -- display routines & system entry points

#ifndef __ZDISP_INC
#define __ZDISP_INC

#include "zti.inc"

ROW_SIZE .equ 1
#define DROW DB

#if TI84PCE
#include "ti84pce/zdisp.inc"
#endif
#if TI83PLUS
#include "ti83plus/zdisp.inc"
#endif

SFONT_HEIGHT .equ $0e ; TODO: adjust this?

;; struct zrect
;; C orgcol
;; R orgrow
;; C width
;; R height
ZRECT.ORGCOL .equ 0
ZRECT.ORGROW .equ ZRECT.ORGCOL + COL_SIZE
ZRECT.WIDTH  .equ ZRECT.ORGROW + ROW_SIZE
ZRECT.HEIGHT .equ ZRECT.WIDTH + COL_SIZE
ZRECT_SIZE   .equ ZRECT.HEIGHT + ROW_SIZE

#macro D_ZRECT(orgcol, orgrow, width, height)
       DCOL orgcol
       DROW orgrow
       DCOL width
       DROW height
#endmacro

#endif

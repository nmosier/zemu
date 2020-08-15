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


;; Macros for load/store rows
#define LD_A_FROM_IX_R(off) ld a,(ix+off)
#define LD_B_FROM_IX_R(off) ld b,(ix+off)
#define LD_C_FROM_IX_R(off) ld c,(ix+off)
#define LD_D_FROM_IX_R(off) ld d,(ix+off)
#define LD_E_FROM_IX_R(off) ld e,(ix+off)
#define LD_H_FROM_IX_R(off) ld e,(ix+off)
#define LD_L_FROM_IX_R(off) ld e,(ix+off)

#define LD_A_TO_IX_R(off) ld (ix+off),a
#define LD_B_TO_IX_R(off) ld (ix+off),b
#define LD_C_TO_IX_R(off) ld (ix+off),c
#define LD_D_TO_IX_R(off) ld (ix+off),d
#define LD_E_TO_IX_R(off) ld (ix+off),e
#define LD_H_TO_IX_R(off) ld (ix+off),h
#define LD_L_TO_IX_R(off) ld (ix+off),l

#define LD_A_FROM_IY_R(off) ld a,(iy+off)
#define LD_B_FROM_IY_R(off) ld b,(iy+off)
#define LD_C_FROM_IY_R(off) ld c,(iy+off)
#define LD_D_FROM_IY_R(off) ld d,(iy+off)
#define LD_E_FROM_IY_R(off) ld e,(iy+off)
#define LD_H_FROM_IY_R(off) ld e,(iy+off)
#define LD_L_FROM_IY_R(off) ld e,(iy+off)

#define LD_A_TO_IY_R(off) ld (iy+off),a
#define LD_B_TO_IY_R(off) ld (iy+off),b
#define LD_C_TO_IY_R(off) ld (iy+off),c
#define LD_D_TO_IY_R(off) ld (iy+off),d
#define LD_E_TO_IY_R(off) ld (iy+off),e
#define LD_H_TO_IY_R(off) ld (iy+off),h
#define LD_L_TO_IY_R(off) ld (iy+off),l



#endif

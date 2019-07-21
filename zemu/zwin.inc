;; zwin.inc -- window management routines

#ifndef __ZWIN_INC
#define __ZWIN_INC

#include "zutil.inc"
#include "zdisp.inc"

; struct zwin
;  L curcol
;  B currow
;  L orgcol
;  B orgrow
;  L width
;  B height
;  B flags
;  L buflen
;  L bufptr
;  [buflen] B buf

ZWIN.CURCOL .equ 0      ; L 3
ZWIN.CURROW .equ 3      ; B 1
ZWIN.ORGCOL .equ 4      ; L 3
ZWIN.ORGROW .equ 7      ; B 1
ZWIN.WIDTH  .equ 8      ; L 3
ZWIN.HEIGHT .equ 11     ; B 1
ZWIN.FLAGS  .equ 12     ; B 1
ZWIN.BUFLEN .equ 13     ; L 3
ZWIN.BUFPTR .equ 16     ; L 3
ZWIN.BUF    .equ 19

ZWIN.FLAGS.BUFD .equ 0 ; whether buffered

ZWIN_NOBUF_SIZE .equ 13 ; without buffering
ZWIN_BUF_BASE_SIZE .equ 19 ; all fixed-sized fields, with buffering


ZWIN_CLEARCOLOR .equ $ff

#macro D_ZWIN(orgcol, orgrow, width, height, flags, buflen)
  .dl orgcol ; curcol
  .db orgrow ; currow
  .dl orgcol ; orgcol
  .db orgrow ; orgrow
  .dl width  ; width
  .db height ; height
  .db flags  ; flags
#if buflen > 0  
  .dl buflen ; buflen
  .dl _      ; bufptr
_ RESB(buflen) ; buf
#endif
#endmacro

#macro RES_ZWIN(buflen)
  RESB(ZWIN_BUF_BASE_SIZE + buflen)
#endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;; GLOBAL VARIABLES ;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;

ZWIN.MAIN.HEIGHT .equ DISP_HEIGHT - SFONT_HEIGHT
ZWIN.MAIN.WIDTH .equ DISP_WIDTH
ZWIN.MAIN.ORGCOL .equ 0
ZWIN.MAIN.ORGROW .equ 0

ZWIN.DEBUG.HEIGHT .equ DISP_HEIGHT - ZWIN.MAIN.HEIGHT
ZWIN.DEBUG.WIDTH .equ DISP_WIDTH
ZWIN.DEBUG.ORGCOL .equ 0
ZWIN.DEBUG.ORGROW .equ ZWIN.MAIN.ORGROW + ZWIN.MAIN.HEIGHT



#endif

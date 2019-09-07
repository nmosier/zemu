;; zwin.inc -- window management routines

#ifndef __ZWIN_INC
#define __ZWIN_INC

#include "zti.inc"
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

ZWIN.CURCOL .equ 0                           ; PENCOL_SIZE
ZWIN.CURROW .equ ZWIN.CURCOL + PENCOL_SIZE   ; PENROW_SIZE
ZWIN.RECT   .equ ZWIN.CURROW + PENROW_SIZE   ;
ZWIN.ORGCOL .equ ZWIN.RECT                   ; PENCOL_SIZE
ZWIN.ORGROW .equ ZWIN.ORGCOL + PENCOL_SIZE   ; PENROW_SIZE
ZWIN.WIDTH  .equ ZWIN.ORGROW + PENROW_SIZE   ; PENCOL_SIZE
ZWIN.HEIGHT .equ ZWIN.WIDTH + PENCOL_SIZE    ; PENROW_SIZE
ZWIN.FLAGS  .equ ZWIN.HEIGHT + PENROW_SIZE   ; BYTE_SIZE
ZWIN.BUFLEN .equ ZWIN.FLAGS + BYTE_SIZE      ; LONG_SIZE
ZWIN.BUFPTR .equ ZWIN.BUFLEN + LONG_SIZE     ; LONG_SIZE
ZWIN.BUFANC .equ ZWIN.BUFPTR + LONG_SIZE     ; LONG_SIZE
ZWIN.BUF    .equ ZWIN.BUFANC + LONG_SIZE     ;


ZWIN.FLAGS.BUFD .equ 0 ; whether buffered
ZWIN.FLAGS.PAGD .equ 1 ; whether paged (must be buffered)

ZWIN_NOBUF_SIZE .equ ZWIN.BUFLEN ; without buffering
ZWIN_BUF_BASE_SIZE .equ ZWIN.BUF ; all fixed-sized fields, with buffering

ZWIN_CLEARCOLOR .equ $ff

#macro D_ZWIN(orgcol, orgrow, width, height, flags, buflen)
  DCOL orgcol ; curcol
  DROW orgrow ; currow
  DCOL orgcol ; orgcol
  DROW orgrow ; orgrow
  DCOL width  ; width
  DROW height ; height
  DB flags  ; flags
#if buflen > 0
  DL buflen ; buflen
  DL _      ; bufptr
  DL 0      ; bufanc
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

ZWIN_CURSOR .equ '_'
;; SBAR?


#endif

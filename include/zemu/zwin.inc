;; zwin.inc -- window management routines

#ifndef __ZWIN_INC
#define __ZWIN_INC

#include "zti.inc"
#include "util.inc"
#include "zdisp.inc"
#include "zfile.inc"

; struct zwin
; C curcol
; R currow
; C orgcol
; R orgrow
; C width
; R height
; B flags
; L buflen
; L bufptr
; [buflen] B buf
; F file

ZWIN.CURCOL .equ 0                       ; PENCOL_SIZE
ZWIN.CURROW .equ ZWIN.CURCOL + COL_SIZE  ; PENROW_SIZE
ZWIN.ORGCOL .equ ZWIN.CURROW + ROW_SIZE  ;
ZWIN.ORGROW .equ ZWIN.ORGCOL + COL_SIZE  ; PENROW_SIZE
ZWIN.WIDTH  .equ ZWIN.ORGROW + ROW_SIZE  ; PENCOL_SIZE
ZWIN.HEIGHT .equ ZWIN.WIDTH + COL_SIZE   ; PENROW_SIZE
ZWIN.FLAGS  .equ ZWIN.HEIGHT + ROW_SIZE  ; BYTE_SIZE
ZWIN.BUFLEN .equ ZWIN.FLAGS + BYTE_SIZE  ; LONG_SIZE
ZWIN.BUFPTR .equ ZWIN.BUFLEN + LONG_SIZE ; LONG_SIZE
ZWIN.BUFANC .equ ZWIN.BUFPTR + LONG_SIZE ; LONG_SIZE
#if ZTEST
ZWIN.CKSUM  .equ ZWIN.BUFANC + LONG_SIZE
ZWIN.FILE   .equ ZWIN.CKSUM + LONG_SIZE
#else
ZWIN.FILE   .equ ZWIN.BUFANC + LONG_SIZE ; SIZEOF_FILE
#endif


ZWIN.RECT   .equ ZWIN.ORGCOL


ZWIN.FLAGS.BUFD .equ 0 ; whether buffered
ZWIN.FLAGS.PAGD .equ 1 ; whether paged (must be buffered)
ZWIN.FLAGS.WAIT .equ 2 ; whether to always wait on scroll

ZWIN_SIZE .equ ZWIN.FILE + SIZEOF_FILE

ZWIN_CLEARCOLOR .equ $ff

#macro D_ZWIN(orgcol, orgrow, width, height, flags, buflen, filename)
  DCOL orgcol ; curcol
  DROW orgrow ; currow
  DCOL orgcol ; orgcol
  DROW orgrow ; orgrow
  DCOL width  ; width 
  DROW height ; height
#if buflen > 0
  DB flags|(1<<ZWIN.FLAGS.BUFD)
#else
  DB flags  ; flags
#endif
  DL buflen ; buflen
  DL 0      ; bufptr
  DL buflen ; bufanc
#if ZTEST
  DL 5381   ; cksum
#endif
  D_FILE(filename, buflen) ; filesize 
#endmacro


#define RES_ZWIN RESB(ZWIN_SIZE)


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

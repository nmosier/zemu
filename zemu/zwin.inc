;; zwin.inc -- window management routines

#ifndef __ZWIN_INC
#define __ZWIN_INC

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

ZWIN.CURCOL .equ 0
ZWIN.CURROW .equ 3
ZWIN.ORGCOL .equ 4
ZWIN.ORGROW .equ 7
ZWIN.WIDTH  .equ 8
ZWIN.HEIGHT .equ 11
ZWIN.FLAGS  .equ 12
ZWIN.FLAGS.BUFD .equ 0
ZWIN.BUFLEN .equ 13
ZWIN.BUFPTR .equ 16
ZWIN.BUF    .equ 19
ZWIN_SIZE .equ 22

ZWIN_CLEARCOLOR .equ $ff

#endif
;; zwin.inc -- window management routines

; struct zwin
;  L penCol
;  B penRow
;  L orgCol
;  B orgRow
;  L width
;  B height

ZWIN.PENCOL .equ 0
ZWIN.PENROW .equ 3
ZWIN.ORGCOL .equ 4
ZWIN.ORGROW .equ 7
ZWIN.WIDTH  .equ 8
ZWIN.HEIGHT .equ 11
ZWIN_SIZE .equ 12
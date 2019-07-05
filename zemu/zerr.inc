;; zerr.inc -- errors

#ifndef __ZERR_INC
#define __ZERR_INC

ZERRCNT .equ 8

ZERR_NOVAR       .equ 0
ZERR_NOMEM       .equ 1
ZERR_BADADDR     .equ 2
ZERR_NOTAVAIL    .equ 3
ZERR_NOLOCL      .equ 4
ZERR_STACKEMPTY  .equ 5
ZERR_BADINSTR    .equ 6
ZERR_BADVARNO    .equ 7
ZERR_DIVZERO     .equ 8
ZERR_BADOBJ      .equ 9
ZERR_BADATTR     .equ 10
ZERR_NOPROP      .equ 11
ZERR_BADPROP     .equ 12
ZERR_BADCHAR     .equ 13

#endif
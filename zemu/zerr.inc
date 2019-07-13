;; zerr.inc -- errors

#ifndef __ZERR_INC
#define __ZERR_INC

ZERRCNT .equ 8

ZERR_SUCCESS     .equ 0
ZERR_NOVAR       .equ 1
ZERR_NOMEM       .equ 2
ZERR_BADADDR     .equ 3
ZERR_NOTAVAIL    .equ 4
ZERR_NOLOCL      .equ 5
ZERR_STACKEMPTY  .equ 6
ZERR_BADINSTR    .equ 7
ZERR_BADVARNO    .equ 8
ZERR_DIVZERO     .equ 9
ZERR_BADOBJ      .equ 10
ZERR_BADATTR     .equ 11
ZERR_NOPROP      .equ 12
ZERR_BADPROP     .equ 13
ZERR_BADCHAR     .equ 14
ZERR_ARGC        .equ 15
ZERR_INTR        .equ 16

#endif
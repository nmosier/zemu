#ifndef __ZTI_INC
#define __ZTI_INC

BYTE_SIZE .equ 1
WORD_SIZE .equ 2

PENROW_SIZE .equ BYTE_SIZE

#define DB .db
#define DW .dw

#ifdef TI84PCE
;;;;; TI 84 PLUS CE ;;;;;
#undef TI84PCE
#include "ti84pce.inc"
#define TI84PCE

LONG_SIZE .equ 3

LONG_MIN .equ $800000
LONG_MAX .equ LONG_MIN - 1
ULONG_MAX .equ $ffffff


PENCOL_SIZE .equ LONG_SIZE

#define DL .dl
;;;;;;;;;;;;;;;;;;;;;;;;;
#else

#ifdef TI83PLUS
;;;;; TI 83 PLUS ;;;;;
#undef TI83PLUS
#include "ti83plus.inc"
#define TI83PLUS

LONG_SIZE .equ WORD_SIZE

LONG_MIN .equ $8000
LONG_MAX .equ LONG_MIN - 1
ULONG_MAX .equ $ffff

PENCOL_SIZE .equ BYTE_SIZE

#define DL DW
;;;;;;;;;;;;;;;;;;;;;;;;;
#endif

#endif

#endif
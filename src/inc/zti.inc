#ifndef __ZTI_INC
#define __ZTI_INC


BYTE_SIZE .equ 1
WORD_SIZE .equ 2


#define DB .db
#define DW .dw

#ifdef TI84PCE
#include "ti84pce/zti84pce.inc"
#endif

#ifdef TI83PLUS
#include "ti83plus/zti83plus.inc"
#endif

LONG_BITS .equ LONG_SIZE * 8
LONG_MIN .equ 1 << (LONG_BITS - 1)
LONG_MAX .equ LONG_MIN - 1
ULONG_MIN .equ 0
ULONG_MAX .equ (1 << LONG_BITS) - 1

PENROW_SIZE .equ BYTE_SIZE


#endif
;; zcode.inc -- include file for zcode

#ifndef __ZCODE_INC
#define __ZCODE_INC

#include "zutil.inc"

ZOPCODE_TYPE_H .equ 7
ZOPCODE_TYPE_L .equ 6
ZOPCODE_EXTENDED .equ $be

Z_2OP .equ 2
Z_1OP .equ 1
Z_0OP .equ 0
Z_VAR .equ -1

ZOP_OMITTED .equ $03
ZOP_VARIABLE .equ $02
ZOP_SMALL .equ $01
ZOP_LARGE .equ $00

ZCODE_2OP_TABSIZE .equ (zcode.2OP_end - zcode.2OP) / LONG_SIZE
ZCODE_1OP_TABSIZE .equ (zcode.1OP_end - zcode.1OP) / LONG_SIZE
ZCODE_0OP_TABSIZE .equ (zcode.0OP_end - zcode.0OP) / LONG_SIZE
ZCODE_VAR_TABSIZE .equ (zcode.VAR_end - zcode.VAR) / LONG_SIZE

#endif
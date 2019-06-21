;; zcode.inc -- include file for zcode

#ifndef __ZCODE_INC
#define __ZCODE_INC

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

#endif
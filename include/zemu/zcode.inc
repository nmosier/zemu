;; zcode.inc -- include file for zcode

#ifndef __ZCODE_INC
#define __ZCODE_INC

#include "zutil.inc"
#include "util.inc"

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

; ZCODE_2OP_TABSIZE .equ (zcode.2OP_end - zcode.2OP) / LONG_SIZE
; ZCODE_1OP_TABSIZE .equ (zcode.1OP_end - zcode.1OP) / LONG_SIZE
; ZCODE_0OP_TABSIZE .equ (zcode.0OP_end - zcode.0OP) / LONG_SIZE
; ZCODE_VAR_TABSIZE .equ (zcode.VAR_end - zcode.VAR) / LONG_SIZE


; %xxxx.xxaa
; a -- parameter count

ZCODE_ENT.INFO .equ 0
ZCODE_ENT.HANDLER .equ ZCODE_ENT.INFO + BYTE_SIZE
SIZEOF_ZCODE_ENT .equ ZCODE_ENT.HANDLER + LONG_SIZE

ZCODE_ENT.INFO.NPARAMS    .equ %00000011
ZCODE_ENT.INFO.WRITES_VAR .equ 7
ZCODE_ENT.INFO.CJMP       .equ 6

#macro D_ZCODE_ENT(nparams, var, cjmp, handler)
  .db nparams | (var * MASK(ZCODE_ENT.INFO.WRITES_VAR)) | (cjmp * MASK(ZCODE_ENT.INFO.CJMP))
  DL handler
#endmacro



#endif

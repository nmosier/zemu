#ifndef __ZTI_INC
#define __ZTI_INC


BYTE_SIZE .equ 1
WORD_SIZE .equ 2


#define DB .db
#define DW .dw

#ifdef TI84PCE
#include "ti84pce/zti.inc"
#endif

#ifdef TI83PLUS
#include "ti83plus/zti.inc"
#endif

LONG_BITS .equ LONG_SIZE * 8
LONG_MIN .equ 1 << (LONG_BITS - 1)
LONG_MAX .equ LONG_MIN - 1
ULONG_MIN .equ 0
ULONG_MAX .equ (1 << LONG_BITS) - 1

#define LD_IX_DE push de \\ pop ix
#define LD_IX_HL push hl \\ pop ix
#define LD_HL_IX push ix \\ pop hl
#define LD_DE_IX push ix \\ pop de
#define LD_BC_IX push ix \\ pop bc

#macro LD_HL_SP
  ld hl,0
  add hl,sp
#endmacro

;; ALLOCA_HL_A -- allocate %a bytes on the stack, loading pointer into %hl
;; INPUTS:
;;  a = size in bytes
;; OUTPUTS:
;;  hl = pointer to char[a] on stack
;; DESTROYS: (none)
#macro ALLOCA_HL_A(size)
  ld hl,-1
  neg
  ld l,a
  add hl,sp
  ld sp,hl
  neg
#endmacro

#endif

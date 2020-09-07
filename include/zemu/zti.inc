#ifndef ZTI_INC
#define ZTI_INC

BYTE_SIZE .equ 1
WORD_SIZE .equ 2

#define DB .db
#define DW .dw

#if TI83PLUS
#include "ti83plus/zti.inc"
#elif TI84PCE
#include "ti84pce/zti.inc"
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

#macro LD_DE_SP
  ex de,hl
  LD_HL_SP
  ex de,hl
#endmacro

#macro CALL_IX
  call jp_ix
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

#macro LD_HL_TO_IX_W(off)
  ld (ix+off),l
  ld (ix+off+1),h
#endmacro

#macro LD_HL_TO_IY_W(off)
  ld (iy+off),l
  ld (iy+off+1),h
#endmacro

#macro LD_DE_TO_IX_W(off)
  ld (ix+off),e
  ld (ix+off+1),d
#endmacro

#macro LD_DE_TO_IY_W(off)
  ld (iy+off),e
  ld (iy+off+1),d
#endmacro

#define LD_IX_IY push iy \\ pop ix

#endif

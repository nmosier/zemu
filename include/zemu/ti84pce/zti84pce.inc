#ifndef __ZTI84PCE_INC
#define __ZTI84PCE_INC

#undef TI84PCE
#include "ti84pce/ti84pce.inc"
#define TI84PCE

LONG_SIZE .equ 3

PENCOL_SIZE .equ LONG_SIZE

#define DL .dl

#define CLEAR_UPPER_HL ld hl,0
#define CLEAR_UPPER_DE ld de,0
#define CLEAR_UPPER_BC ld bc,0
#define CLEAR_UPPER_IX ld ix,0
#define CLEAR_UPPER_IY ld iy,0

#define UCAST_A_TO_HL   ld hl,0 \\ ld l,a
#define UCAST_A_TO_DE   ld de,0 \\ ld e,a
#define UCAST_A_TO_BC   ld bc,0 \\ ld c,a

#define LD_BC_HL push hl \\ pop bc
#define LD_BC_DE push de \\ pop bc
#define LD_HL_BC push bc \\ pop hl
#define LD_DE_BC push bc \\ pop de

#define LEA_IX_IX(off, reg) lea ix,ix+off
#define LEA_HL_IX(off) lea hl,ix+off

#define LD_HLL_FROM_IX(off) ld hl,(ix+off)
#define LD_DEL_FROM_IX(off) ld de,(ix+off)
#define LD_BCL_FROM_IX(off) ld bc,(ix+off)

#macro MLT_A(off, reg16)
#if reg16 == R_HL       
   ld hl,off            
   ld h,a               
   mlt hl               
#elif reg16 == R_DE     
   ld de,off            
   ld d,a               
   mlt de               
#elif reg16 == R_BC     
   ld bc,off            
   ld b,a               
   mlt bc               
#endif
#endmacro

;; SYSCALLS ;;
#define SYSCALL(addr) call addr


#endif
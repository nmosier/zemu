#ifndef __ZTI84PCE_INC
#define __ZTI84PCE_INC

#undef TI84PCE
#include "ti84pce/ti84pce.inc"
#define TI84PCE

LONG_SIZE .equ 3

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
#define LEA_DE_IX(off) lea de,ix+off
#define LEA_BC_IX(off) lea bc,ix+off

#define LD_HL_FROM_IX(off) ld hl,(ix+off)
#define LD_DE_FROM_IX(off) ld de,(ix+off)
#define LD_BC_FROM_IX(off) ld bc,(ix+off)

#define LD_HL_TO_IX(off) ld (ix+off),hl
#define LD_DE_TO_IX(off) ld (ix+off),de
#define LD_BC_TO_IX(off) ld (ix+off),bc

#define LD_HL_FROM_IX_W(off) ld.s hl,(ix+off)
#define LD_DE_FROM_IX_W(off) ld.s de,(ix+off)
#define LD_BC_FROM_IX_W(off) ld.s bc,(ix+off)

#define LD_HL_TO_IX_W(off) ld.s (ix+off),hl
#define LD_DE_TO_IX_W(off) ld.s (ix+off),de
#define LD_BC_TO_IX_W(off) ld.s (ix+off),bc


#define LD_HL_FROM_IY(off) ld hl,(iy+off)
#define LD_DE_FROM_IY(off) ld de,(iy+off)
#define LD_BC_FROM_IY(off) ld bc,(iy+off)

#define LD_HL_TO_IY(off) ld (iy+off),hl
#define LD_DE_TO_IY(off) ld (iy+off),de
#define LD_BC_TO_IY(off) ld (iy+off),bc

#define LD_HL_FROM_IY_W(off) ld.s hl,(iy+off)
#define LD_DE_FROM_IY_W(off) ld.s de,(iy+off)
#define LD_BC_FROM_IY_W(off) ld.s bc,(iy+off)

#define LD_HL_TO_IY_W(off) ld.s (iy+off),hl
#define LD_DE_TO_IY_W(off) ld.s (iy+off),de
#define LD_BC_TO_IY_W(off) ld.s (iy+off),bc



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
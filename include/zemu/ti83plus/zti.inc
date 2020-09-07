#ifndef TI83PLUS_ZTI_INC
#define TI83PLUS_ZTI_INC

#include "util.inc"

#undef TI83PLUS
#include "ti83plus/ti83plus.inc"
#define TI83PLUS

LONG_SIZE .equ WORD_SIZE

#define DL DW

#macro CLEAR_UPPER_HL
#endmacro
#macro CLEAR_UPPER_DE
#endmacro
#macro CLEAR_UPPER_BC
#endmacro
#macro CLEAR_UPPER_IX
#endmacro
#macro CLEAR_UPPER_IY
#endmacro

#define UCAST_A_TO_HL   ld h,0 \\ ld l,a
#define UCAST_A_TO_DE   ld d,0 \\ ld e,a
#define UCAST_A_TO_BC   ld b,0 \\ ld c,a

#define UCAST_B_TO_HL   ld h,0 \\ ld l,b
#define UCAST_B_TO_DE   ld d,0 \\ ld e,b

#define UCAST_C_TO_DE   ld e,0 \\ ld d,c

#define UCAST_L_TO_DE   ld d,0 \\ ld e,l

#define UCAST_FROM_HL_TO_BC ld b,0 \\ ld c,(hl)
#define UCAST_FROM_IX_TO_BC ld b,0 \\ ld c,(ix+0)
#define UCAST_FROM_IX_TO_HL(off) ld h,0 \\ ld l,(ix+off)

#macro LTOWU_HL
#endmacro

#define LD_BC_HL ld b,h \\ ld c,l
#define LD_BC_DE ld b,d \\ ld c,e
#define LD_HL_BC ld h,b \\ ld l,c
#define LD_DE_BC ld d,b \\ ld e,c

#macro LEA_IX_IX_REG(off, reg) 
   LD_REG_IMM(reg, off)     
   ADD_IX_REG(reg)
#endmacro

#macro LEA_IX_IX(off)
#if off != 0
  push de
   ld de,off
   add ix,de
  pop de
#endif
#endmacro

;; LEA_HL_IX -- load effective address from ix into hl
;; DESTROYS: (none, including flags)
#macro LEA_HL_IX(off)
#if off == 0
   LD_HL_IX
#else
  push af
   ld a,off
   call _lea_hl_ix
  pop af
#endif
#endmacro

;; LEA_DE_IX -- load effective address from ix into de
;; DESTROYS: (none, including flags)
#macro LEA_DE_IX(off)
#if off == 0
  LD_DE_IX
#else
  push af
   ld a,off
   call _lea_de_ix
  pop af
#endif
#endmacro

#macro LD_HL_FROM_IX(off)
   ld l,(ix+off)         
   ld h,(ix+off+1)
#endmacro
#macro LD_DE_FROM_IX(off)
   ld e,(ix+off)
   ld d,(ix+off+1)
#endmacro
#macro LD_BC_FROM_IX(off)
   ld c,(ix+off)
   ld b,(ix+off+1)
#endmacro
#macro LD_IX_FROM_IX(off)
  push de
  ld de,off
  call _ld_ix_from_ix
  pop de
#endmacro

#macro LD_HL_TO_IX(off)
  ld (ix+off),l
  ld (ix+off+1),h
#endmacro
#macro LD_DE_TO_IX(off)
  ld (ix+off),e
  ld (ix+off+1),d
#endmacro
#macro LD_BC_TO_IX(off)
  ld (ix+off),c
  ld (ix+off+1),b
#endmacro

#define LD_DE_TO_IX_W(off) LD_DE_TO_IX(off)

#define LD_HL_FROM_IX_W(off) LD_HL_FROM_IX(off)
#define LD_DE_FROM_IX_W(off) LD_DE_FROM_IX(off)
#define LD_BC_FROM_IX_W(off) LD_BC_FROM_IX(off)

#define LD_ZX_W2L_HL_FROM_IX(off) LD_HL_FROM_IX_W(off)
#define LD_ZX_W2L_DE_FROM_IX(off) LD_DE_FROM_IX_W(off)
#define LD_ZX_W2L_BC_FROM_IX(off) LD_BC_FROM_IX_W(off)


#macro LD_HL_FROM_IY(off)
   ld l,(iy+off)         
   ld h,(iy+off+1)
#endmacro
#macro LD_DE_FROM_IY(off)
   ld e,(iy+off)
   ld d,(iy+off+1)
#endmacro
#macro LD_BC_FROM_IY(off)
   ld c,(iy+off)
   ld b,(iy+off+1)
#endmacro

#macro LD_HL_TO_IY(off)
  ld (iy+off),l
  ld (iy+off+1),h
#endmacro
#macro LD_DE_TO_IY(off)
  ld (iy+off),e
  ld (iy+off+1),d
#endmacro
#macro LD_BC_TO_IY(off)
  ld (iy+off),c
  ld (iy+off+1),b
#endmacro

#define LD_HL_FROM_IY_W(off) LD_HL_FROM_IY(off)
#define LD_DE_FROM_IY_W(off) LD_DE_FROM_IY(off)
#define LD_BC_FROM_IY_W(off) LD_BC_FROM_IY(off)

#macro MLT_A(off, reg16) 
#if reg16 == R_HL        
   ld hl,off             
   push af               
   call mul_hl_a         
   pop af                
#elif reg16 == R_DE      
   ex de,hl              
   ld hl,off             
   push af               
   call mul_hl_a         
   pop af                
   ex de,hl              
#elif reg16 == R_BC      
   push hl               
   ld hl,off             
   push af               
   call mul_hl_a         
   pop af                
   LD_BC_HL              
   pop hl                
#endif
#endmacro


#define LD_HL_FROM_HL call _ld_hl_from_hl

#define PUSH_HL_L dec sp \\ push hl
#define PUSH_DE_L dec sp \\ push de
#define PUSH_BC_L dec sp \\ push bc

#define POP_HL_L  pop hl \\ inc sp
#define POP_DE_L  pop de \\ inc sp
#define POP_BC_L  pop bc \\ inc sp

#define LD_HL_0   ld h,0 \\ ld l,0

#macro LD_ABS_TO_IX(off, abs)
  ld (ix+off),LOW_IMM(abs)
  ld (ix+off+1),HIGH_IMM(abs)
#endmacro

;; SYSTEM CALLS ;;
#define SYSCALL(addr) bcall(addr)
#define SYSERR_PUSH(addr) AppOnErr(addr)
#define SYSERR_POP(addr) AppOffErr


#endif
#ifndef __ZTI83PLUS_INC
#define __ZTI83PLUS_INC

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

#define LD_BC_HL ld b,h \\ ld c,l
#define LD_BC_DE ld b,d \\ ld c,e
#define LD_HL_BC ld h,b \\ ld l,c
#define LD_DE_BC ld d,b \\ ld e,c

#macro LEA_IX_IX(off, reg) 
   LD_REG_IMM(reg, off)     
   ADD_IX_REG(reg)
#endmacro

;; LEA_HL_IX -- load effective address from ix into hl
;; DESTROYS: (none, including flags)
#macro LEA_HL_IX(off)
   push af
   ld a,off
   call _lea_hl_ix
   pop af
#endmacro

;; LEA_DE_IX -- load effective address from ix into de
;; DESTROYS: (none, including flags)
#macro LEA_DE_IX(off)
  push af
  ld a,off
  call _lea_de_ix
  pop af
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

#define LD_HL_FROM_IX_W(off) LD_HL_FROM_IX(off)
#define LD_DE_FROM_IX_W(off) LD_DE_FROM_IX(off)
#define LD_BC_FROM_IX_W(off) LD_BC_FROM_IX(off)


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


;; SYSTEM CALLS ;;
#define SYSCALL(addr) bcall(addr)


#endif
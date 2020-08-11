#ifndef __ZTI83PLUS_INC
#define __ZTI83PLUS_INC

#undef TI83PLUS
#include "ti83plus/ti83plus.inc"
#define TI83PLUS

LONG_SIZE .equ WORD_SIZE

PENCOL_SIZE .equ BYTE_SIZE

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

#macro LEA_HL_IX(off)
   push af
   ld a,off
   call lea_hl_ix
   pop af
#endmacro

#macro LD_HLL_FROM_IX(off)
   ld l,(ix+off)         
   ld h,(ix+off+1)
#endmacro
#macro LD_DEL_FROM_IX(off)
   ld e,(ix+off)
   ld d,(ix+off+1)
#endmacro
#macro LD_BCL_FROM_IX(off)
   ld c,(ix+off)
   ld b,(ix+off+1)
#endmacro

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

;; SYSTEM CALLS ;;
#define SYSCALL(addr) bcall(addr)


#endif
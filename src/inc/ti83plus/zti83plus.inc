#ifndef __ZTI83PLUS_INC
#define __ZTI83PLUS_INC

#undef TI83PLUS
#include "ti83plus/ti83plus.inc"
#define TI83PLUS

LONG_SIZE .equ WORD_SIZE

PENCOL_SIZE .equ BYTE_SIZE

#define DL DW

#define CLEAR_UPPER_HL
#define CLEAR_UPPER_DE
#define CLEAR_UPPER_BC
#define CLEAR_UPPER_IX
#define CLEAR_UPPER_IY

#define UCAST_A_TO_HL   ld h,0 \\ ld l,a
#define UCAST_A_TO_DE   ld d,0 \\ ld e,a
#define UCAST_A_TO_BC   ld b,0 \\ ld c,a

#define LD_BC_HL ld b,h \\ ld c,l
#define LD_BC_DE ld b,d \\ ld c,e
#define LD_HL_BC ld h,b \\ ld l,c
#define LD_DE_BC ld d,b \\ ld e,c
#define LD_IX_DE ld ixh,d \\ ld ixl,e
#define LD_IX_HL ld ixh,h \\ ld ixl,l


#macro LEA_IX_IX(off, reg) 
   LD_REG_IMM(reg, off)     
   ADD_IX_REG(reg)
#endmacro

#macro LD_HL_FROM_IX(off)
   ld l,(ix+off)         
   ld h,(ix+off)
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
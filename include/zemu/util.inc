#ifndef UTIL_INC
#define UTIL_INC

#include "zti.inc"

VARNAMELEN .equ 8

;; Register Equates ;;
;; 24-/16-bit Registers
R_HL .equ 0
R_DE .equ 1
R_BC .equ 2
R_IX .equ 3
R_IY .equ 4

;; 8-bit Registers
R_LOW_OFF .equ 10
R_L   .equ R_LOW_OFF + R_HL
R_E   .equ R_LOW_OFF + R_DE
R_C   .equ R_LOW_OFF + R_BC
R_IXL .equ R_LOW_OFF + R_IX
R_IYL .equ R_LOW_OFF + R_IY

R_HIGH_OFF .equ 20
R_H   .equ R_HIGH_OFF + R_HL
R_D   .equ R_HIGH_OFF + R_DE
R_B   .equ R_HIGH_OFF + R_BC
R_IXH .equ R_HIGH_OFF + R_IX
R_IYH .equ R_HIGH_OFF + R_IY

;; Conversion
#define R_LOW(reg) reg+R_LOW_OFF
#define R_HIGH(reg) reg+R_HIGH_OFF

#macro RESB(n)     
#if n > 0           
    DB 0            
    RESB(n-1)       
#endif
#endmacro

#macro RESW(n)     
#if n > 0           
    DW 0            
    RESW(n-1)       
#endif
#endmacro

#macro RESL(n)     
#if n > 0           
    DL 0            
    RESL(n-1)       
#endif
#endmacro

#define MASK(n) 1 << n         

#define LOW_IMM(i) i & $ff

#define HIGH_IMM(i) LOW_IMM((i >> 8))

;; ADDRESS SIZE SCALING ;;
#macro MLTA_A_TO_HL()
   UCAST_A_TO_HL      
   sla l              
   rl h               
   add a,l            
   ld l,a                
   jr nc,_            
   inc h              
_
#endmacro

#macro MLTA_A_TO_BC()
   UCAST_A_TO_BC     
   sla c             
   rl b                
   add a,c           
   ld c,a              
   jr nc,_           
   inc b             
_
#endmacro

#macro LD_REG_IMM(reg, imm)  
#if reg == R_HL               
   ld hl,imm                  
#elif reg == R_DE               
   ld de,imm                  
#elif reg == R_BC             
   ld bc,imm                  
#elif reg == R_IX             
   ld ix,imm                  
#elif reg == R_IY             
   ld iy,imm                  
#endif
#endmacro
                              
#macro ADD_HL_REG(reg)       
#if reg == R_HL               
   add hl,hl                  
#elif reg == R_DE             
   add hl,de                  
#elif reg == R_BC             
   add hl,bc                  
#endif
#endmacro

#macro ADD_IX_REG(reg)    
#if reg == R_DE            
   add ix,de               
#elif reg == R_BC          
   add ix,bc               
#elif reg == R_IX          
   add ix,ix               
#endif
#endmacro


#macro LD_REG8_FROM_IX(off, reg8)
#if reg8 == R_H              
   ld h,(ix+off)             
#elif reg8 == R_L            
   ld l,(ix+off)             
#elif reg8 == R_D            
   ld d,(ix+off)             
#elif reg8 == R_E            
   ld e,(ix+off)             
#elif reg8 == R_B            
   ld b,(ix+off)             
#elif reg8 == R_C            
   ld c,(ix+off)             
#elif reg8 == R_IXH          
   ld ixh,(ix+off)           
#elif reg8 == R_IXL          
   ld ixl,(ix+off)           
#elif reg8 == R_IYH          
   ld iyh,(ix+off)           
#elif reg8 == R_IYL          
   ld ixl,(ix+off)           
#endif
#endmacro

#macro LD_REG8_IMM(imm, reg8)
#if reg8 == R_H               
   ld h,imm                   
#elif reg8 == R_L             
   ld l,imm                   
#elif reg8 == R_D             
   ld d,imm                   
#elif reg8 == R_E             
   ld e,imm                   
#elif reg8 == R_B             
   ld b,imm                   
#elif reg8 == R_C             
   ld c,imm                   
#elif reg8 == R_IXH           
   ld ixh,imm                 
#elif reg8 == R_IXL           
   ld ixl,imm                 
#elif reg8 == R_IYH           
   ld iyh,imm                 
#elif reg8 == R_IYL           
   ld ixl,imm                 
#endif
#endmacro

#if TI83PLUS
#include "ti83plus/util.inc"
#endif

#endif
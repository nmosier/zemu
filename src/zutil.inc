#ifndef __ZUTIL_INC
#define __ZUTIL_INC

LONG_MIN .equ $800000
LONG_MAX .equ LONG_MIN - 1

BYTE_SIZE .equ 1
WORD_SIZE .equ 2
LONG_SIZE .equ 3

ZFALSE .equ $000000
ZTRUE .equ  $000001

VARNAMELEN .equ 8

#macro RESB(n)
#if n > 0
    .db 0
    RESB(n-1)
#endif
#endmacro

#macro RESW(n)
#if n > 0
    .dw 0
    RESW(n-1)
#endif
#endmacro

#macro RESL(n)
#if n > 0
    .dl 0
    RESL(n-1)
#endif    
#endmacro

#macro MASK(n)
    1 << n
#endmacro

#macro LOW(i)
    i & $ff
#endmacro

#macro HIGH(i)
    LOW((i >> 8))
#endmacro

#macro UPPER(i)
   HIGH((i >> 8))
#endmacro

#define LD_BC_HL push hl \\ pop bc
#define LD_BC_DE push de \\ pop bc
#define LD_HL_BC push bc \\ pop hl
#define LD_DE_BC push bc \\ pop de
#define LD_IX_DE push de \\ pop ix
#define LD_IX_HL push hl \\ pop ix

#define EX_BC_HL push bc \\ ex (sp),hl \\ pop bc

#define EX_BC_DE EX_BC_HL \\ ex de,hl \\ EX_BC_HL

;; COMPATABILE UPPER-BYTE INITIALIZATION ;;

#define CLEAR_UPPER_HL ld hl,0
#define CLEAR_UPPER_DE ld de,0
#define CLEAR_UPPER_BC ld bc,0
#define CLEAR_UPPER_IX ld ix,0
#define CLEAR_UPPER_IY ld iy,0

;; 8-bit to 16-/24-bit CASTING ;;
#define UCAST_A_TO_HL   ld hl,0 \\ ld l,a
#define UCAST_A_TO_DE   ld de,0 \\ ld e,a
#define UCAST_A_TO_BC   ld bc,0 \\ ld c,a

;; ADDRESS SIZE SCALING ;;
;; #define MLTA_A_TO_HL    UCAST_A_TO_HL \\ sla l \\ rl h \\ add a,l \\ ld l,a \\ jr c,_ \\ 
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


;; FRAME SETTING ;;
#macro FRAME_SIZE(bytes, words, longs)
   bytes * BYTE_SIZE + words * WORD_SIZE + longs * LONG_SIZE
#endmacro


#macro FRAME_SET(bytes, words, longs)
   ld iy,-(bytes * BYTE_SIZE + words * WORD_SIZE + longs * LONG_SIZE)
   add iy,sp
   ld sp,iy
#endmacro

#macro FRAME_UNSET(bytes, words, longs)
   ld de,bytes * BYTE_SIZE + words * WORD_SIZE + longs * LONG_SIZE
   add iy,de
   ld sp,iy
#endmacro

#macro FRAME_OFFSET(bytes, words, longs)
       FRAME_SIZE(bytes, words, longs)
#endmacro

#macro FRAME_ADDR(n, bytes, words, longs)
   #if n < bytes
      iy + n * BYTE_SIZE
   #elif n < bytes + words
      iy + bytes * BYTE_SIZE + (n - bytes) * WORD_SIZE
   #elif n < bytes + words + longs
      iy + bytes * BYTE_SIZE + words * WORD_SIZE + (n - bytes - words) * LONG_SIZE
   #else
      ;; TODO -- should generate error
   #endif
#endmacro

#macro FRAME_VAL(n, bytes, words, longs)
   (FRAME_ADDR(n, bytes, words, longs))
#endmacro



#endif



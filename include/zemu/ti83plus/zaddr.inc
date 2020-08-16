#ifndef TI83PLUS_ZADDR_INC
#define TI83PLUS_ZADDR_INC

#macro LD_BHL_FROM_IX_ZA(off)
  ld l,(ix+off+0)
  ld h,(ix+off+1)
  ld b,(ix+off+2)
#endmacro
#macro LD_CDE_FROM_IX_ZA(off)
  ld e,(ix+off+0)
  ld d,(ix+off+1)
  ld c,(ix+off+2)
#endmacro

#macro LD_BHL_FROM_IX_ZAW(off)
  LD_HL_FROM_IX_W(off)
  ld b,0  
#endmacro
#macro LD_CDE_FROM_IX_ZAW(off)
  LD_DE_FROM_IX_W(off)
  ld c,0  
#endmacro

#define INC_BHL_ZA call zaddr_inc

#define PUSH_BHL_ZA push hl \\ push bc
#define POP_BHL_ZA pop bc \\ pop hl

#define UCAST_A_TO_BHL_ZA UCAST_A_TO_HL \\ ld b,0
#define UCAST_A_TO_CDE_ZA UCAST_A_TO_DE \\ ld c,0

#endif
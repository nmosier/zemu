#ifndef TI84PCE_UTIL_INC
#define TI84PCE_UTIL_INC

#define WTOLU_HL call wtolu
#define WTOLS_HL call wtols

#macro BTOLU
  or a,a
  sbc hl,hl
  ld l,a
#endmacro

#macro BTOLU_C
  ld hl,0
  ld l,a
#endmacro

#endif
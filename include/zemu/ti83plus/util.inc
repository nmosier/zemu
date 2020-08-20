#ifndef TI83PLUS_UTIL_INC
#define TI83PLUS_UTIL_INC

#macro INC_W_AT_IX(off)
  inc (ix+off)
  jr nc,_
  inc (ix+off+1)
_
#endif

#macro INC_L_AT_IX(off)
   INC_W_AT_IX(off)
#endif

#macro DEC_W_AT_IX(off)
  dec (ix+off)
  jr nc,_
  dec (ix+off+1)
_
#endmacro

#macro DEC_L_AT_IX(off)
  DEC_W_AT_IX(off)
#endmacro

#macro WTOLU_HL
#endmacro
#macro WTOLS_HL
#endmacro

#endif
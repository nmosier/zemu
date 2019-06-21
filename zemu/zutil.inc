#macro rotl8(cnt)
  #if cnt>4
    call rotr8_+8-cnt
  #else
    call rotl8_+cnt
  #endif
#endmacro

#macro rotr8(cnt)
  #if cnt>4
    call rotl8_+8-cnt
  #else
    call rotr8_+cnt
  #endif
#endmacro

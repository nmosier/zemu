#ifndef TI83PLUS_ZRAND_INC
#define TI83PLUS_ZRAND_INC

#define DRAND(seed) .db LOW_IMM(seed), HIGH_IMM(seed), UPPER_IMM(seed)

#macro LD_BHL_FROM_ABS_RAND(abs)
  ld hl,(abs)
  ld b,(abs+2)
#endmacro
#macro LD_BHL_TO_ABS_RAND(abs)
  ld (abs+1),bc
  ld (abs),hl
#endmacro

#macro SLA_BHL_RAND
  add hl,hl
  rl b
#endmacro

#macro RL_BHL_RAND
  adc hl,hl
  rl b
#endmacro

#macro PUSH_BHL_RAND
  push bc
  inc sp
  push hl
#endmacro

#macro POP_BLH_RAND
  pop hl
  dec sp
  ex (sp),hl
  ld b,h
  pop hl
#endmacro

#endif

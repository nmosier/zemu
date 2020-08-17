#ifndef TI84PCE_ZRAND_INC
#define TI84PCE_ZRAND_INC

#define DRAND(seed) .dl seed

#define LD_BHL_FROM_ABS_RAND(abs) ld hl,(abs)
#define LD_BHL_TO_ABS_RAND(abs)   ld (abs),hl

#define SLA_BHL_RAND add hl,hl
#define RL_BHL_RAND  adc hl,hl

#define PUSH_BHL_RAND push hl
#define POP_BHL_RAND  pop hl

#endif
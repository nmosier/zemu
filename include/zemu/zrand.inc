;; zrand.inc -- random number generator

#ifndef __ZRAND_INC
#define __ZRAND_INC

ZRAND_BITS .equ 23
ZRAND_XORBIT .equ 5

#if TI83PLUS
#include "ti83plus/zrand.inc"
#elif TI84PCE
#include "ti84pce/zrand.inc"
#endif

#endif

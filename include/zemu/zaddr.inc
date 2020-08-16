;; zaddr.inc

#ifndef __ZADDR_INC
#define __ZADDR_INC

#if TI83PLUS
#include "ti83plus/zaddr.inc"
#elif TI84PCE
#include "ti84pce/zaddr.inc"
#endif

ZADDR_READ  .equ 0
ZADDR_WRITE .equ 1

#endif

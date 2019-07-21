;; zinput.inc -- keyboard input routines

#ifndef __ZIN_INC
#define __ZIN_INC

ZIN_RBUFSIZE .equ $80



sysint .equ $038

SYS_IDT_SIZE .equ $100
syssaferam .equ saveSScreen
sys_idt .equ (syssaferam + SYS_IDT_SIZE) >> 8



#endif

;; zobj.inc -- include file for object table manipulation code

#ifndef __ZOBJ_INC
#define __ZOBJ_INC

#include "zemu.inc"

ZOBJTAB_PROPDEFAULTS_SIZE .equ 31 * 2

ZOBJ_O_ATTRS .equ 0
ZOBJ_O_FAMILY .equ 4
ZOBJ_O_PARENT .equ 4
ZOBJ_O_SIBLING .equ 5
ZOBJ_O_CHILD .equ 6
ZOBJ_O_PROPS .equ 7

ZOBJ_FAM_PARENT .equ 0
ZOBJ_FAM_SIBLING .equ 1
ZOBJ_FAM_CHILD .equ 2


ZOBJSIZE .equ 9

ZPROPTAB_HDR .equ 0
ZPROPTAB_TEXTLEN .equ 0
ZPROPTAB_TEXT .equ 1

ZPROP_SIZE .equ 0
ZPROP_DATA .equ 1

ZPROPMIN .equ 1
ZPROPMAX .equ 31

#endif

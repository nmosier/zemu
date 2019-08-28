;; zhdr.inc -- equates for story file headers

#ifndef __ZHDR_INC
#define __ZHDR_INC

;; NOTE: the values are in decimal so that they can be shared with C programs.

ZHDR_VERSION .equ 0
ZHDR_FLAGS1  .equ 1
ZHDR_HIGHMEM .equ 4
ZHDR_INITPC  .equ 6
ZHDR_DICT    .equ 8
ZHDR_OBJTAB  .equ 10
ZHDR_GLOBALS .equ 12
ZHDR_STATIC  .equ 14
ZHDR_FLAGS2  .equ 16

ZHDR_ABBR    .equ 24
;; TODO


#endif

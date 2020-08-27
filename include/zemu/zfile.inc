#ifndef ZFILE_INC
#define ZFILE_INC

#include "util.inc"

; struct FILE {
;  char name[VARNAMELEN];
;  uint16_t size;
; } 

FILE.NAME .equ 0
FILE.SIZE .equ FILE.NAME + VARNAMELEN

SIZEOF_FILE .equ FILE.SIZE + WORD_SIZE

#macro D_FILE(name, size)
   ; for label
_  .db name
   RESB(VARNAMELEN - $ + (-_)) ; pad name
   .dw size
#endmacro


#define RES_FILE RESB(SIZEOF_FILE)

#endif
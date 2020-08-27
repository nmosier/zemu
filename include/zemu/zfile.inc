#ifndef ZFILE_INC
#define ZFILE_INC

#include "util.inc"

; struct FILE {
;  char name[VARNAMELEN];
;  uint8_t flags;
;  uint16_t size;
; } 

FILE.NAME .equ 0
FILE.FLAGS .equ FILE.NAME + VARNAMELEN
FILE.SIZE .equ FILE.FLAGS + BYTE_SIZE

SIZEOF_FILE .equ FILE.SIZE + WORD_SIZE

FILE.FLAGS.SIZE .equ 0

#macro D_FILE(name, size)
   ; for label
_  .db name
   RESB(VARNAMELEN - $ + (-_)) ; pad name
   .db 0
   .dw size
#endmacro


#define RES_FILE RESB(SIZEOF_FILE)

#endif
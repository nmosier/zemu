#ifndef ZFILE_INC
#define ZFILE_INC

#include "util.inc"

; struct FILE {
;  char name[VARNAMELEN];
;  uint16_t size;
; }

FILE.NAME  .equ 0
FILE.SIZE  .equ FILE.NAME + VARNAMELEN
FILE.FD    .equ FILE.SIZE + WORD_SIZE
FILE.PTR   .equ FILE.FD   + 1

SIZEOF_FILE .equ FILE.PTR + 3

;; File Flags
;; TODO

#macro D_FILE(name, size)
   ; for label
_  .db name
   RESB(VARNAMELEN - $ + (-_)) ; pad name
   .dw size
   .db 0 ; file descriptor
   RESB(3) ; ptr
#endmacro


#define RES_FILE RESB(SIZEOF_FILE)

; struct FILETAB_ENT {
;  uint8_t flags;
; }
FILETAB_ENT.FLAGS .equ 0

SIZEOF_FILETAB_ENT .equ FILETAB_ENT.FLAGS + 1

FILETAB_ENT.FLAGS.USED  .equ 0 ; used bit  -- whether currently assigned to open file
FILETAB_ENT.FLAGS.DIRTY .equ 1 ; dirty bit -- whether generalized address is correct

MAX_FILES .equ 32

#endif
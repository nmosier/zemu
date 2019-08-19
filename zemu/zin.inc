#ifndef __ZIN_INC
#define __ZIN_INC

ZIN_TXTBUF_MAXCHARS .equ 0 ; byte 0
ZIN_TXTBUF_TEXT     .equ 1 ; main buffer

ZIN_TXTBUF_MINSIZE  .equ 3
ZIN_PRSBUF_MINSIZE  .equ 6

ZIN_TXTBUF_HDRSIZE  .equ 1

ZIN_MAXWORDLEN      .equ 127 ; maximum length (in ZSCII codes / bytes) of (textual) word

#endif
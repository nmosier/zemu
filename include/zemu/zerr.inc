;; zerr.inc -- errors

#ifndef __ZERR_INC
#define __ZERR_INC

ZERR_SUCCESS     .equ 0
ZERR_NOVAR       .equ 1
ZERR_NOMEM       .equ 2
ZERR_BADADDR     .equ 3
ZERR_NOTAVAIL    .equ 4
ZERR_NOLOCL      .equ 5
ZERR_STACKEMPTY  .equ 6
ZERR_BADINSTR    .equ 7
ZERR_BADVARNO    .equ 8
ZERR_DIVZERO     .equ 9
ZERR_BADOBJ      .equ 10
ZERR_BADATTR     .equ 11
ZERR_NOPROP      .equ 12
ZERR_BADPROP     .equ 13
ZERR_BADCHAR     .equ 14
ZERR_ARGC        .equ 15
ZERR_INTR        .equ 16
ZERR_ZCHAR       .equ 17
ZERR_TXTBUF      .equ 18
ZERR_PRSBUF      .equ 19
ZERR_TOOLONG     .equ 20
ZERR_BADNAME     .equ 21
ZERR_RDONLY      .equ 22
ZERR_STACKOVER   .equ 23
ZERR_INTERNAL    .equ 24
ZERR_READEOF     .equ 25
ZERR_BADFD       .equ 26
ZERR_TOOMANYF    .equ 27

ZERR_COUNT       .equ 28

ZERR_MAX_STRLEN  .equ 36

#define zerrstr_success     "success"
#define zerrstr_novar       "appvar not found"
#define zerrstr_nomem       "not enough free RAM"
#define zerrstr_badaddr     "bad address"
#define zerrstr_notavail    "opcode not supported"
#define zerrstr_nolocl      "invalid local variable"
#define zerrstr_stackempty  "cannot pop from empty stack"
#define zerrstr_badinstr    "illegal instruction"
#define zerrstr_badvarno    "invalid variable number"
#define zerrstr_divzero     "divide by 0"
#define zerrstr_badobj      "invalid object"
#define zerrstr_badattr     "attribute number out of range"
#define zerrstr_noprop      "object missing property"
#define zerrstr_badprop     "invalid property length"
#define zerrstr_badchar     "bad character"
#define zerrstr_argc        "too many arguments"
#define zerrstr_intr        "interrupt"
#define zerrstr_zchar       "not a ZSCII character"
#define zerrstr_txtbuf      "text buffer too small"
#define zerrstr_prsbuf      "parse buffer too small"
#define zerrstr_toolong     "name is too long"
#define zerrstr_badname     "name contains invalid character"
#define zerrstr_rdonly      "write attempt to read-only memory"
#define zerrstr_stackover   "stack overflow"
#define zerrstr_internal    "internal error"
#define zerrstr_readeof     "read past EOF"
#define zerrstr_badfd       "bad file descriptor"
#define zerrstr_toomanyf    "too many files open"

;; ZERR_EXTERN, ZERR_INTERN, ZERR_BASIC

#if ZERR_EXTERN
zerr_fallback .equ xtos
#endif

#endif

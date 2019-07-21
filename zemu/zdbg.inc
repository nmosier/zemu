;; zdbg.inc -- debugging routines

#ifndef __ZDBG_INC
#define __ZDBG_INC

ZDBG_OUTPUT_ROW .equ 7
ZDBG_OUTPUT_COL .equ 0

ZDBG_INPUT_ROW .equ 8
ZDBG_INPUT_COL .equ 0

ZDBG_FLAGS_BREAK .equ 0 ; whether to break
ZDBG_FLAGS_MODE .equ 1 ; res = run, set = step
ZDBG_FLAGS_INTR .equ 2 ; whether to test for interrupt
ZDBG_FLAGS_STAT .equ 3 ; whether to display status info

ZDBG_FLAGS_STEP .equ 7 ; used by debugger -- don't set directly

#endif

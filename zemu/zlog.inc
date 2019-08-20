;; zlog.inc -- logger for zemu

#ifndef __ZLOG_INC
#define __ZLOG_INC

LOG_PREFIX    .equ $ED
LOGSTR_OPCODE .equ $F0
LOGNUM_OPCODE .equ $F1

#macro LOGSTR(str)
   .db LOG_PREFIX, LOGSTR_OPCODE
   .db str,0
#endmacro

#macro LOGNUM(num)
   .db LOG_PREFIX, LOGNUM_OPCODE
   .dl num   
#endmacro


#macro LOGLN()
   LOGSTR($0A)
#endmacro

#endif
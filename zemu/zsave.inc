;; zsave.inc -- routines for saving & restoring games

#ifndef __ZSAVE_INC
#define __ZSAVE_INC

#include "zemu.inc" ;; TODO -- the equates needed in this header should
                    ;;         really be in zmap.inc

;; zsave:
;;   zsave_base BASE:
;;     zsave_hdr HDR:
;;       L MAP_OFF
;;       L MEM_OFF
;;     zframe FRAME
;;   VAR:
;;     zmap MAP
;;     zmem MEM

;; ZSAVE_HDR definition
ZSAVE_HDR.MAP_OFF .equ 0
ZSAVE_HDR.MEM_OFF   .equ 3
ZSAVE_HDR_SIZE    .equ 6


;; ZSAVE_BASE definition
ZSAVE_BASE.HDR    .equ 0
ZSAVE_BASE.FRAME  .equ ZSAVE_BASE.HDR + ZSAVE_HDR_SIZE
ZSAVE_BASE_SIZE   .equ ZSAVE_HDR_SIZE + ZFRAME_SIZE


;; ZSAVE definition
ZSAVE.BASE .equ 0
ZSAVE.VAR  .equ ZSAVE.BASE + ZSAVE_BASE_SIZE


#endif
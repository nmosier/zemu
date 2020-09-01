;; zsave.inc -- routines for saving & restoring games

#ifndef ZSAVE_INC
#define ZSAVE_INC

#include "zemu.inc" ;; TODO -- the equates needed in this header should
                    ;;         really be in zmap.inc


;; zsave:
;;  1. frame (fixed)
;;  2. map (variable)
;;  3. mem (variable)

; struct zsave {
;  struct zframe frame;
;  uint16_t zmap_size;
;  char zmap_data[zmap_size];
;  uint16_t zmem_size;
;  char zmem_data[
; }

#endif
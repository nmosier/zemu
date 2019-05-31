(setq ez80-mode-font-lock-keywords
      (let* (
             ;; define categories of keywords
             (z-opcodes '("adc" "add" "cp" "daa" "dec" "inc" "mlt"
                          "neg" "sbc" "sub"
                          "bit" "res" "set" "cpd" "cpdr" "cpi" "cpir"
                          "ldd" "lddr" "ldi" "ldir" "ex" "exx" "in"
                          "in0" "ind" "indr" "indrx" "ind2" "ind2r"
                          "indm" "indmr" "ini" "inir" "inirx" "ini2"
                          "ini2r" "inim" "inimr" "otdm" "otdmr" "otdrx"
                          "otim" "otimr" "otirx" "out" "out0" "outd"
                          "otdr" "outd2" "otd2r" "outi" "otir" "outi2"
                          "outi2r" "tstio" "ld" "lea" "pea" "pop"
                          "push" "and" "cpl" "or" "tst" "xor" "ccf"
                          "di" "ei" "halt" "im" "nop" "rsmix" "scf"
                          "slp" "stmix" "call" "djnz" "jp" "jr" "ret"
                          "reti" "retn" "rst" "rl" "rla" "rlc" "rlca"
                          "rld" "rr" "rra" "rrc" "rrca" "rrd" "sla"
                          "sra" "srl"))
             (z-conds '("c" "nc" "z" "nz"))
             (z-regs '("a" "b" "c" "d" "e" "f" "h" "l" "hlu" "deu" "bcu"
                       "af" "hl" "bc" "de" "ix" "iy" "sp"))
             (z-suffixes '("\.s" "\.l"))

             ;; regex
             (z-opcodes-regexp (regexp-opt z-opcodes 'words))
             (z-conds-regexp (regexp-opt z-conds 'words))
             (z-regs-regexp (regexp-opt z-regs 'words))
             (z-comments-regexp '";.*$")
             (z-label-regexp '"^[^;\n]*:")
             (z-ref-regexp '"[[:alpha:]_][[:alnum:]_\.]*")
             (z-suffixes-regexp (regexp-opt z-suffixes 'words))
             (z-string-regexp '"\"\([^\\\"]\|\\\"\)*\"")
             (z-directive-regexp '"^[\.#][[:alpha:]]+")
             (z-directive2-regexp '"[[:space:]][\.#][[:alpha:]]+")
             )
        
             ;; weird part
        `(
          (,z-comments-regexp . font-lock-comment-face)
          (,z-opcodes-regexp . font-lock-type-face)
          (,z-suffixes-regexp . font-lock-type-face)
          (,z-directive-regexp . font-lock-preprocessor-face)
          (,z-directive2-regexp . font-lock-preprocessor-face)
          (,z-conds-regexp . font-lock-constant-face)
          (,z-regs-regexp . font-lock-function-name-face)
          (,z-label-regexp . font-lock-variable-name-face)
          (,z-ref-regexp . font-lock-variable-name-face)
          (,z-string-regexp . font-lock-string-face)
          )))


(define-derived-mode ez80-mode fundamental-mode "ez80"
  "major mode for editing ez80 assembly."
  (setq font-lock-defaults '((ez80-mode-font-lock-keywords))))

(provide 'ez80-mode)
  

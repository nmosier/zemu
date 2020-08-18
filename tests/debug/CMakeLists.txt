set(EXEC zemudbg)
set(LOCATION VRAM)

add_zemu_test(zork-dbg-init
  COMMANDS "''" E906AD95
  )
add_zemu_test(zork-dbg-step
  COMMANDS "\\r" E074871C
  )
add_zemu_test(zork-dbg-run
  COMMANDS "\\n" 20D443C0
  )
add_zemu_test(zork-dbg-obj
  COMMANDS "+PO1\\n" 964039E
  )

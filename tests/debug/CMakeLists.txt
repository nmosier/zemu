get_target_property(EXEC zemudbg 8XP)

add_zemu_test(zork-dbg-init
  COMMANDS "''" EC5D4466
  )
add_zemu_test(zork-dbg-step
  COMMANDS "\\r" 656B5DAF
  )
add_zemu_test(zork-dbg-run
  COMMANDS "\\n" 258FAA33
  )
add_zemu_test(zork-dbg-obj
  COMMANDS "+PO1\\n" C3FEA6D
  )

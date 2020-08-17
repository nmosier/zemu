include(${CMAKE_SOURCE_DIR}/cmake/ZEMUTest.cmake)

set(TESTS zork-welcome)

set(TESTGEN ${CMAKE_CURRENT_SOURCE_DIR}/testgen.sh)

get_target_property(zemu_8xp zemu 8XP)

add_zemu_test(zork-welcome ${zemu_8xp}
  VARDIR "../vars/zork"
  COMMANDS "''" E3E88479
  )

add_zemu_test(zork-north ${zemu_8xp}
  VARDIR "../vars/zork"
  COMMANDS "n\\n" 830BA2CD
  )

add_zemu_test(zork-open-mailbox ${zemu_8xp}
  VARDIR "../vars/zork"
  COMMANDS "open mailbox\\n" 8F98BDAF
  )

add_zemu_test(zork-multiline-command ${zemu_8xp}
  VARDIR "../vars/zork"
  COMMANDS "this is a very long sentence which spans two" "5A6702D1" " lines" "8493A536"
  )

add_zemu_test(zork-forest ${zemu_8xp}
  VARDIR "../vars/zork"
  COMMANDS
  "north\\n"      5355D174
  "north\\n"      D9E56563
  "climb tree\\n" AF367190
  "\\d"           6C4AF6B6
  "\\d"           B5F66B0
  "\\d"           1B3E02BB
  "take egg\\n"   B3368F6A
  "inventory\\n"  F3875276
  )


get_target_property(zemu_dbg_8xp zemudbg 8XP)

add_zemu_test(zork-dbg-init ${zemu_dbg_8xp}
  VARDIR "../vars/zork"
  COMMANDS "''" EC5D4466
  )
add_zemu_test(zork-dbg-step ${zemu_dbg_8xp}
  VARDIR "../vars/zork"
  COMMANDS "\\r" 656B5DAF
  )
add_zemu_test(zork-dbg-run ${zemu_dbg_8xp}
  VARDIR "../vars/zork"
  COMMANDS "\\n" 258FAA33
  )
add_zemu_test(zork-dbg-obj ${zemu_dbg_8xp}
  VARDIR "../vars/zork"
  COMMANDS "+PO1\\n" C3FEA6D
  )

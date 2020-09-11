set(EXEC zemu84pce)

set(LOCATION WIN_MAIN)

add_zemu_test(zork-welcome
  COMMANDS
  "ZORK\\n" 75C7D4EE
  )

add_zemu_test(zork-north
  COMMANDS
  "ZORK\\n" 75C7D4EE
  "n\\n" 3FD77B1C
  )

add_zemu_test(zork-open-mailbox
  COMMANDS
  "ZORK\\n" 75C7D4EE
  "open mailbox\\n" 5FC0A09C
  )

add_zemu_test(zork-multiline-command
  COMMANDS
  "ZORK\\n" 75C7D4EE
  "this is a very long sentence which spans two" 7A1A91F4
  " lines" 305DE299
  )

add_zemu_test(zork-forest
  COMMANDS
  "ZORK\\n" 75C7D4EE
  "north\\n"      E732B934
  "north\\n"      A749FFF1
  "climb tree\\n" 26F5FF8D
  "\\d"           E50A7BDD
  "\\d"           4C377625
  "take egg\\n"   11532993
  "inventory\\n"  24AE30AC
  )

add_zemu_test(zork-leaflet
  COMMANDS
  "ZORK\\n" 75C7D4EE
  "open mailbox\\n" 5FC0A09C
  "take leaflet\\n" AC617D04
  "read leaflet\\n" 1D5A1C5F
  )  

add_zemu_test(zork-restore
  COMMANDS
  "ZORK\\n" 75C7D4EE
  "save\\n"         D6163777
  "north\\n"        CDA06A7D
  "restore\\n"      184594DD
  "open mailbox\\n" E4BB66FF
  )


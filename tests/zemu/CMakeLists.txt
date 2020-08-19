set(EXEC zemu84pce)

set(LOCATION WIN_MAIN)

add_zemu_test(zork-welcome
  COMMANDS "''" 1A7BB317
  )

add_zemu_test(zork-north
  COMMANDS "''" 1A7BB317 "n\\n" 3FD77B1C
  )

add_zemu_test(zork-open-mailbox
  COMMANDS "''" 1A7BB317 "open mailbox\\n" 5FC0A09C
  )

add_zemu_test(zork-multiline-command
  COMMANDS "''" 1A7BB317
  "this is a very long sentence which spans two" FCC9AACC
  " lines" 303A9207
  )

add_zemu_test(zork-forest
  COMMANDS
  "''"            1A7BB317
  "north\\n"      E732B934
  "north\\n"      A749FFF1
  "climb tree\\n" DCECCC81
  "\\d"           C10500AA
  "\\d"           E50A7BDD
  "\\d"           4C377625
  "take egg\\n"   11532993
  "inventory\\n"  24AE30AC
  )

add_zemu_test(zork-leaflet
  COMMANDS
  "''"              1A7BB317
  "open mailbox\\n" 5FC0A09C
  "take leaflet\\n" AC617D04
  "read leaflet\\n" 1D5A1C5F
  )  

set(EXEC zemu)

set(START win_main.buf)
set(SIZE win_main.buflen)

add_zemu_test(zork-welcome
  COMMANDS "''" AA57DDA7
  )

add_zemu_test(zork-north
  COMMANDS "n\\n" 830BA2CD
  )

add_zemu_test(zork-open-mailbox
  COMMANDS "open mailbox\\n" 8F98BDAF
  )

add_zemu_test(zork-multiline-command
  COMMANDS "this is a very long sentence which spans two" "5A6702D1" " lines" "8493A536"
  )

add_zemu_test(zork-forest
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

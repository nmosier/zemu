set(PLATFORM TI84PCE)

foreach(DRIVER lds cksum)
  add_8xp(${DRIVER} ${DRIVER}.z80)
endforeach()

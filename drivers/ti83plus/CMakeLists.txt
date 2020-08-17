set(PLATFORM TI83PLUS)

add_subdirectory(zwin)

foreach(DRIVER clearrect scrollrectupclear scrollrectup)
  add_8xp(${DRIVER} ${DRIVER}.z80)
endforeach()

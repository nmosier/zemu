set(PLATFORM TI83PLUS)

add_subdirectory(zwin)
add_subdirectory(zapp)

foreach(DRIVER clearrect scrollrectupclear scrollrectup big)
  add_8xp(${DRIVER} ${DRIVER}.z80)
endforeach()

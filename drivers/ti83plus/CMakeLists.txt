set(DRIVERS clearrect scrollrectupclear scrollrectup)

foreach(DRIVER ${DRIVERS})
  add_8xp(${DRIVER} ${DRIVER}.z80
    INCLUDE_DIRS ${8XP_INCLUDE_DIRS}
    PLATFORM TI83PLUS
    SPASM_FLAGS -L
    )
endforeach()

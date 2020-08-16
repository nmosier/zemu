set(DRIVERS lds)

foreach(DRIVER ${DRIVERS})
  add_8xp(${DRIVER} ${DRIVER}.z80
    INCLUDE_DIRS ${8XP_INCLUDE_DIRS}
    PLATFORM TI84PCE
    SPASM_FLAGS -L
    )
endforeach()

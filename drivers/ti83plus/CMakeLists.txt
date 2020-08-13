list(APPEND 8XP_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include/zemu ${CMAKE_SOURCE_DIR}/src/zemu)

set(DRIVERS clearrect scrollrect)

foreach(DRIVER ${DRIVERS})
  add_8xp(${DRIVER} ${DRIVER}.z80
    INCLUDE_DIRS ${8XP_INCLUDE_DIRS}
    PLATFORM TI83PLUS
    SPASM_FLAGS -L
    )
endforeach()

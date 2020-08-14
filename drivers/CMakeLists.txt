list(APPEND 8XP_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include/zemu ${CMAKE_SOURCE_DIR}/src/zemu)

add_subdirectory(ti83plus)
add_subdirectory(ti84pce)

set(DRIVERS sfont)

foreach(DRIVER ${DRIVERS})
  add_8xp(${DRIVER}83plus ${DRIVER}.z80
    INCLUDE_DIRS ${8XP_INCLUDE_DIRS}
    PLATFORM TI83PLUS
    SPASM_FLAGS -L
    )
  add_8xp(${DRIVER}84pce ${DRIVER}.z80
    INCLUDE_DIRS ${8XP_INCLUDE_DIRS}
    PLATFORM TI84PCE
    SPASM_FLAGS -L
    )
endforeach()


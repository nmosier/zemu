list(APPEND 8XP_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include/zemu ${CMAKE_SOURCE_DIR}/src/zemu)

add_8xp(clearrect clearrect.z80
  INCLUDE_DIRS ${8XP_INCLUDE_DIRS}
  PLATFORM TI83PLUS
  SPASM_FLAGS -L
  )

add_8xp(clearrectcolumn clearrectcolumn.z80
  INCLUDE_DIRS ${8XP_INCLUDE_DIRS}
  PLATFORM TI83PLUS
  SPASM_FLAGS -L
  )

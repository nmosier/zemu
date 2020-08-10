add_8xp(test
  SOURCES test.z80 test2.z80
  INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include/zemu
  DEFINITIONS TI84PCE=1
  )

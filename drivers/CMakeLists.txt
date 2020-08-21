
include_directories(${CMAKE_SOURCE_DIR}/include/zemu ${CMAKE_SOURCE_DIR}/src/zemu)
add_compile_options(-L)

add_subdirectory(ti83plus)
add_subdirectory(ti84pce)
add_subdirectory(file)


foreach(DRIVER flash)
  add_8xp(${DRIVER}83plus ${DRIVER}.z80
    NAME ${DRIVER}83plus
    PLATFORM TI83PLUS
    )
  add_8xp(${DRIVER}84pce ${DRIVER}.z80
    NAME ${DRIVER}84pce
    PLATFORM TI84PCE
    )
endforeach()


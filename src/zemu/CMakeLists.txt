include_directories(${CMAKE_SOURCE_DIR}/include/zemu)
add_compile_definitions(ZCURSOR=1 ZOFFSET=1)
add_compile_options(-L)

include(${CMAKE_SOURCE_DIR}/cmake/TI_BIN_Target.cmake)
add_8xv(zerrtab zerrtab.z80
  NAME ZEMUERR
  PLATFORM TI83PLUS # works for all platforms
  )

add_subdirectory(ti83plus)
add_subdirectory(ti84pce)

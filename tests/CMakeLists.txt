include(${CMAKE_SOURCE_DIR}/cmake/ZEMUTest.cmake)

set(TESTGEN ${CMAKE_CURRENT_SOURCE_DIR}/testgen.sh) # required for add_zemu_test
set(VARDIR ${CMAKE_SOURCE_DIR}/vars/zork)
set(ROM ${CMAKE_SOURCE_DIR}/misc/ce.rom)

add_subdirectory(zemu)  # zemu
add_subdirectory(debug) # zemu w/ debugger


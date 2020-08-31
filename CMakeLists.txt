cmake_minimum_required(VERSION 3.16)

project(zemu
  VERSION 1.0
  DESCRIPTION "A Z-machine emulator for the TI-84+ CE"
  )

enable_testing()

set(PLATFORM "TI84PCE" CACHE STRING "Available platforms: TI83PLUS, TI84PCE (default)")

find_program(SPASM spasm REQUIRED)

include(cmake/TITarget.cmake)

add_subdirectory(src)
add_subdirectory(drivers)
add_subdirectory(scripts)
add_subdirectory(vars)
add_subdirectory(tests)

cmake_minimum_required(VERSION 3.18)

project(zemu
  VERSION 1.0
  DESCRIPTION "A Z-machine emulator for the TI-84+ CE"
  )

set(PLATFORM "TI84PCE" CACHE STRING "Available platforms: TI83PLUS, TI84PCE (default)")

find_program(SPASM spasm REQUIRED)

include(cmake/TITarget.cmake)

add_subdirectory(src)

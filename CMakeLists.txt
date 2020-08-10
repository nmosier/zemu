cmake_minimum_required(VERSION 3.18)

project(zemu
  VERSION 1.0
  DESCRIPTION "A Z-machine emulator for the TI-84+ CE"
  )

find_program(SPASM spasm REQUIRED)

include(cmake/TITarget.cmake)

add_subdirectory(src)

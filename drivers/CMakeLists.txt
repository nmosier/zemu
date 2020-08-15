function(add_drivers)
  cmake_parse_arguments(AD
    ""
    "PLATFORM"
    "DRIVERS"
    ${ARGN}
    )

  if(DEFINED AD_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR "add_drivers: invalid arguments '${AD_UNPARSED_ARGUMENTS}'")
  endif()

  if(NOT DEFINED AD_PLATFORM)
    message(FATAL_ERROR "add_drivers: specify platform with 'PLATFORM'")
  endif()

  foreach(DRIVER ${AD_DRIVERS})
    add_8xp(${DRIVER} ${DRIVER}.z80
      INCLUDE_DIRS ${8XP_INCLUDE_DIRS}
      PLATFORM ${AD_PLATFORM}
      SPASM_FLAGS -L
      )
  endforeach()
    
endfunction()


list(APPEND 8XP_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include/zemu ${CMAKE_SOURCE_DIR}/src/zemu)


add_subdirectory(ti83plus)
add_subdirectory(ti84pce)

# set(DRIVERS sfont)
# 
# set(DRIVERS_TI83PLUS ${DRIVERS})
# list(TRANSFORM DRIVERS_TI83PLUS APPEND 83plus)
# add_drivers(${DRIVERS_TI83PLUS} PLATFORM TI83PLUS)
# 
# set(DRIVERS_TI84PCE ${DRIVERS})
# list(TRANSFORM DRIVERS_TI84PCE APPEND 84pce)
# add_drivers(${DRIVERS_TI84PCE} PLATFORM TI84PCE)

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


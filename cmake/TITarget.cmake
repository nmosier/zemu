function(add_8xp TARGET MAIN_SOURCE)
  cmake_parse_arguments(TI
    ""
    "PLATFORM"
    "INCLUDE_DIRS;DEFINITIONS;SPASM_FLAGS"
    ${ARGN}
    )

  if (DEFINED TI_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR "add_8xp: invalid argument")
  endif()

  set(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}.8xp)

  get_directory_property(INCLUDE_DIRS INCLUDE_DIRECTORIES)
  list(APPEND TI_INCLUDE_DIRS ${INCLUDE_DIRS})
  list(TRANSFORM TI_INCLUDE_DIRS PREPEND "-I")

  get_directory_property(DEFINITIONS COMPILE_DEFINITIONS)
  list(APPEND TI_DEFINITIONS ${DEFINITIONS})
  list(TRANSFORM TI_DEFINITIONS PREPEND "-D")

  get_directory_property(FLAGS COMPILE_OPTIONS)
  list(APPEND TI_SPASM_FLAGS ${FLAGS})
  list(APPEND TI_SPASM_FLAGS -N) # no color

  if(DEFINED TI_PLATFORM)
    set(PLATFORM ${TI_PLATFORM})
  endif()
  if(DEFINED PLATFORM)
    if(PLATFORM STREQUAL "TI83PLUS")
      list(APPEND TI_DEFINITIONS -DTI83PLUS=1)
    elseif(PLATFORM STREQUAL "TI84PCE")
      list(APPEND TI_DEFINITIONS -DTI84PCE=1)
      list(APPEND TI_SPASM_FLAGS -E)
    else()
      message(FATAL_ERROR "add_8xp: unrecognized platform '${PLATFORM}'")
    endif()
  endif()

  get_filename_component(MAIN_SOURCE ${MAIN_SOURCE} ABSOLUTE)

  add_custom_command(OUTPUT ${OUTPUT}
    COMMAND ${SPASM} ${TI_SPASM_FLAGS} ${TI_INCLUDE_DIRS} -I ${CMAKE_CURRENT_SOURCE_DIR} ${TI_DEFINITIONS} ${MAIN_SOURCE} ${OUTPUT}
    DEPENDS /dev/null # always remake
    )
  
  add_custom_target(${TARGET} ALL
    DEPENDS ${OUTPUT}
    )

  set_target_properties(${TARGET} PROPERTIES 8XP ${OUTPUT})

endfunction()

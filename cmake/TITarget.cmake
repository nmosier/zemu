function(add_8xp TARGET MAIN_SOURCE)
  cmake_parse_arguments(TI
    ""
    ""
    "INCLUDE_DIRS;DEFINITIONS;SOURCES;INCLUDES"
    ${ARGN}
    )

  set(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}.8xp)

  set(INCLUDE_DIRS)
  if (DEFINED TI_INCLUDE_DIRS)
    foreach(INCLUDE_DIR ${TI_INCLUDE_DIRS})
      list(APPEND INCLUDE_DIRS -I "${INCLUDE_DIR}")
    endforeach()
  endif()

  set(DEFINITIONS)
  if (DEFINED TI_DEFINITIONS)
    foreach(DEFINITION ${TI_DEFINITIONS})
      list(APPEND DEFINITIONS -D${DEFINITION})
    endforeach()
  endif()

  get_filename_component(MAIN_SOURCE ${MAIN_SOURCE} ABSOLUTE)

  add_custom_command(OUTPUT ${OUTPUT}
    COMMAND ${SPASM} -N -E ${INCLUDE_DIRS} -I ${CMAKE_CURRENT_SOURCE_DIR} ${DEFINITIONS} ${MAIN_SOURCE} ${OUTPUT}
    COMMAND_EXPAND_LISTS
    DEPENDS ${MAIN_SOURCE} ${SOURCES} ${INCLUDES}
    )
  
  add_custom_target(${TARGET} ALL
    DEPENDS ${OUTPUT}
    )
  
endfunction()

function(add_8xp TARGET)
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

  if (NOT DEFINED TI_SOURCES)
    message(FATAL_ERROR "missing SOURCES")
  endif()
  list(LENGTH TI_SOURCES NSOURCES)
  if (NSOURCES EQUAL 0)
    message(FATAL_ERROR "empty SOURCES list")
  endif()
  set(SOURCES)
  foreach(TI_SOURCE ${TI_SOURCES})
    get_filename_component(SOURCE ${TI_SOURCE} ABSOLUTE)
    list(APPEND SOURCES ${SOURCE})
  endforeach()

  set(COMBINED ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}-all.z80)
  add_custom_command(OUTPUT ${COMBINED}
    COMMAND cat ${SOURCES} > ${COMBINED}
    DEPENDS ${SOURCES}
    )

  add_custom_command(OUTPUT ${OUTPUT}
    COMMAND ${SPASM} -N -E ${INCLUDE_DIRS} -I ${CMAKE_CURRENT_SOURCE_DIR} ${DEFINITIONS} ${COMBINED} ${OUTPUT}
    COMMAND_EXPAND_LISTS
    DEPENDS ${COMBINED} ${INCLUDES}
    )
  
  add_custom_target(${TARGET} ALL
    DEPENDS ${OUTPUT}
    )

endfunction()

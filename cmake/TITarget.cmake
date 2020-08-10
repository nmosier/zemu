function(add_8xp TARGET)
  cmake_parse_arguments(TI
    ""
    ""
    "INCLUDE_DIRS;DEFINITIONS;SOURCES"
    ${ARGN}
    )

  set(OUTPUT ${TARGET}.8xp)

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

  set(COMBINED ${TARGET}-all.z80)
  add_custom_command(OUTPUT ${COMBINED}
    COMMAND cat ${TI_SOURCES} > ${COMBINED}
    DEPENDS ${TI_SOURCES}
    )

  add_custom_command(OUTPUT ${OUTPUT}
    COMMAND ${SPASM} -E ${INCLUDE_DIRS} ${DEFINITIONS} ${COMBINED} ${OUTPUT}
    COMMAND_EXPAND_LISTS
    DEPENDS ${COMBINED}
    )
  
  add_custom_target(${TARGET} ALL
    DEPENDS ${OUTPUT}
    )

endfunction()

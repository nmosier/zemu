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

  if (NOT DEFINED TI_SPASM_FLAGS)
    set(SPASM_FLAGS)
  else()
    set(SPASM_FLAGS ${TI_SPASM_FLAGS})
  endif()

  if(DEFINED TI_PLATFORM)
    if(TI_PLATFORM STREQUAL "TI83PLUS")
      list(APPEND DEFINITIONS -DTI83PLUS=1)
    elseif(TI_PLATFORM STREQUAL "TI84PCE")
      list(APPEND DEFINITIONS -DTI84PCE=1)
      list(APPEND SPASM_FLAGS -E)
    else()
      message(FATAL_ERROR "add_8xp: unrecognized platform '${TI_PLATFORM}'")
    endif()
  endif()

  get_filename_component(MAIN_SOURCE ${MAIN_SOURCE} ABSOLUTE)

  add_custom_command(OUTPUT ${OUTPUT}
    COMMAND ${SPASM} ${SPASM_FLAGS} ${INCLUDE_DIRS} -I ${CMAKE_CURRENT_SOURCE_DIR} ${DEFINITIONS} ${MAIN_SOURCE} ${OUTPUT}
    DEPENDS /dev/null # always remake
    )
  
  add_custom_target(${TARGET} ALL
    DEPENDS ${OUTPUT}
    )
  
endfunction()

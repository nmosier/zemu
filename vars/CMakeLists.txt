function(add_story STORY_NAME STORY_FILE)
    cmake_parse_arguments(STORY
      ""
      "PAGESIZE"
      ""
      ${ARGN}
      )

    if(NOT DEFINED STORY_PAGESIZE)
      set(STORY_PAGESIZE 2048)
    endif()

    # set output directory
    set(STORY_DIR ${CMAKE_CURRENT_BINARY_DIR}/${STORY_NAME})

    # set zgen script path
    set(ZGEN_SH ${CMAKE_SOURCE_DIR}/src/zmap/zgen.sh)
    
    add_custom_command(OUTPUT ${STORY_DIR}
      COMMAND rm -rf ${STORY_DIR}
      COMMAND ${ZGEN_SH} -n ${STORY_PAGESIZE} ${STORY_FILE} ${STORY_DIR}
      DEPENDS ${ZGEN_SH} zmap ${STORY_FILE} 
      )

    set(STORY_TARGET ${STORY_NAME}_tgt)
    
    add_custom_target(${STORY_TARGET} DEPENDS ${STORY_DIR})

endfunction()

add_story(zork ${CMAKE_SOURCE_DIR}/misc/ZORK.DAT
#  PAGESIZE 2048
  )
add_story(tristam ${CMAKE_SOURCE_DIR}/misc/tristam.z3)

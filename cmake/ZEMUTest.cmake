# Test Generator
function(add_zemu_test NAME EXEC)
  cmake_parse_arguments(ZT
    "JSON"
    "VARDIR;KEY_DELAY"
    "COMMANDS"
    ${ARGN}
    )

  if(NOT ${ZT_JSON})
    if(DEFINED ZT_UNPARSED_ARGUMENTS)
      message(FATAL_ERROR "add_zemu_test: invalid arguments: ${ZT_UNPARSED_ARGUMENTS}")
    endif()

    if(NOT DEFINED ZT_VARDIR)
      message(FATAL_ERROR "add_zemu_test: VARDIR parameter required")
    endif()

    if(DEFINED ZT_KEY_DELAY)
      set(ZT_KEY_DELAY -w ${ZT_KEY_DELAY})
    endif()

    # Quote Commands (???)
    set(COMMANDS)
    foreach(COMMAND ${ZT_COMMANDS})
      list(APPEND COMMANDS "'${COMMAND}'")
    endforeach()

    get_filename_component(TARGET_NAME_LOWER ${EXEC} NAME_WLE)
    string(TOUPPER ${TARGET_NAME_LOWER} TARGET_NAME)
    

    # Generate test command
    add_custom_command(OUTPUT ${NAME}.json
      COMMAND ${TESTGEN} -r ../misc/ce.rom -t ${TARGET_NAME} -v ${ZT_VARDIR} -x ${EXEC} -o ${NAME}.json -k $<TARGET_FILE:str2keys> ${COMMANDS}
      DEPENDS ${TESTGEN} str2keys
      )
    
    # Generate test target
    add_custom_target(${NAME}_tgt ALL
      DEPENDS ${NAME}.json
      )
    
  endif()
  
  # Add CTest
  add_test(NAME ${NAME}
    COMMAND cemu-autotester ./${NAME}.json
    )

endfunction()

# Test Generator
function(add_zemu_test NAME)
  cmake_parse_arguments(ZT
    "JSON"
    "VARDIR;KEY_DELAY;EXEC;ROM;LOCATION"
    "COMMANDS"
    ${ARGN}
    )

  if(NOT DEFINED TESTGEN)
    message(FATAL_ERROR "specify test generator with variable 'TESTGEN'")
  endif()

  if(NOT ${ZT_JSON})
    if(DEFINED ZT_UNPARSED_ARGUMENTS)
      message(FATAL_ERROR "add_zemu_test: invalid arguments: ${ZT_UNPARSED_ARGUMENTS}")
    endif()

    if(NOT DEFINED ZT_VARDIR)
      if(DEFINED VARDIR)
        set(ZT_VARDIR ${VARDIR})
      else()
        message(FATAL_ERROR "add_zemu_test: VARDIR parameter required, or VARDIR variable set")
      endif()
    endif()

    if(DEFINED ZT_KEY_DELAY)
      set(ZT_KEY_DELAY -w ${ZT_KEY_DELAY})
    endif()

    if(NOT DEFINED ZT_EXEC)
      if(DEFINED EXEC)
        set(ZT_EXEC ${EXEC})
      else()
        message(FATAL_ERROR "add_zemu_test: EXEC parameter required, or EXEC variable set")
      endif()
    endif()

    get_target_property(ZT_8XP ${ZT_EXEC} 8XP)
    get_target_property(ZT_LAB ${ZT_EXEC} LAB)

    if(NOT DEFINED ZT_ROM)
      if(DEFINED ROM)
        set(ZT_ROM ${ROM})
      else()
        message(FATAL_ERROR "add_zemu_test: must specify ROM parameter or ROM variable")
      endif()
    endif()

    if(NOT DEFINED ZT_LOCATION)
      if(DEFINED LOCATION)
        set(ZT_LOCATION ${LOCATION})
      else()
        message(FATAL_ERROR "add_zemu_test: must specify LOCATION paramter or LOCATION variable")
      endif()
    endif()
    if(ZT_LOCATION STREQUAL "VRAM")
      set(LOC -s vram_start,vram_16_size)
    elseif(ZT_LOCATION STREQUAL "WIN_MAIN")
      set(LOC -s "win_main.cksum,3,${ZT_LAB}")
    else()
      message(FATAL_ERROR "add_zemu_test: unrecognized LOCATION '${ZT_LOCATION}'")
    endif()
    
    # Quote Commands (???)
    set(COMMANDS)
    foreach(COMMAND ${ZT_COMMANDS})
      list(APPEND COMMANDS "'${COMMAND}'")
    endforeach()

    get_filename_component(TARGET_NAME_LOWER ${ZT_8XP} NAME_WLE)
    string(TOUPPER ${TARGET_NAME_LOWER} TARGET_NAME)
    

    # Generate test command
    add_custom_command(OUTPUT ${NAME}.json
      COMMAND ${TESTGEN} -r ${ZT_ROM} -t ${TARGET_NAME} -v ${ZT_VARDIR} -x ${ZT_8XP} -o ${NAME}.json -k $<TARGET_FILE:str2keys> -R $<TARGET_FILE:readlab> ${LOC} ${COMMANDS}
      DEPENDS ${TESTGEN} str2keys ${ZT_8XP} ${ZT_LAB} ${ZT_VARDIR}
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

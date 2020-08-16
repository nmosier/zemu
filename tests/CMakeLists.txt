set(TESTS zork-welcome)

set(TESTGEN ${CMAKE_CURRENT_SOURCE_DIR}/testgen.sh)

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

    # Generate test command
    add_custom_command(OUTPUT ${NAME}.json
      COMMAND ${TESTGEN} -r ../misc/ce.rom -t ZEMU -v ${ZT_VARDIR} -x ${EXEC} -o ${NAME}.json -k $<TARGET_FILE:str2keys> ${COMMANDS}
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

get_target_property(zemu_8xp zemu 8XP)

add_zemu_test(zork-welcome ${zemu_8xp}
  VARDIR "../vars/zork"
  COMMANDS "''" "E3E88479"
  )

add_zemu_test(zork-north ${zemu_8xp}
  VARDIR "../vars/zork"
  COMMANDS "n\\n" "830BA2CD"
  )

add_zemu_test(zork-open-mailbox ${zemu_8xp}
  VARDIR "../vars/zork"
  COMMANDS "open mailbox\\n" "8F98BDAF"
  )

add_zemu_test(zork-multiline-command ${zemu_8xp}
  VARDIR "../vars/zork"
  COMMANDS "this is a very long sentence which spans two" "5A6702D1" " lines" "8493A536"
  )

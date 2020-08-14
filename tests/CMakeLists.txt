set(TESTS zork-welcome)

set(TESTGEN ${CMAKE_CURRENT_SOURCE_DIR}/testgen.sh)

# Test Generator
function(add_zemu_test NAME EXEC)
  cmake_parse_arguments(ZT
    "JSON"
    "VARDIR;CRC;DESCRIPTION;KEY_DELAY"
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

    if(NOT DEFINED ZT_CRC)
      message(FATAL_ERROR "add_zemu_test: CRC parameter required")
    endif()

    if(DEFINED ZT_DESCRIPTION)
      set(DESC_FLAG -m ${ZT_DESCRIPTION})
    endif()

    if(DEFINED ZT_KEY_DELAY)
      set(ZT_KEY_DELAY -w ${ZT_KEY_DELAY})
    endif()

    # Generate test command
    add_custom_command(OUTPUT ${NAME}.json
      COMMAND ${TESTGEN} -r ../misc/ce.rom -t ZEMU -v ${ZT_VARDIR} -x ${EXEC} -c ${ZT_CRC} ${DESC_FLAG} -o ${NAME}.json -k $<TARGET_FILE:str2keys> ${ZT_COMMANDS}
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
  CRC "E3E88479"
  DESCRIPTION "ZORK welcome screen"
  )

add_zemu_test(zork-north ${zemu_8xp}
  VARDIR "../vars/zork"
  CRC "830BA2CD"
  DESCRIPTION "ZORK go north once"
  COMMANDS "n"
  )

add_zemu_test(zork-open-mailbox ${zemu_8xp}
  VARDIR "../vars/zork"
  CRC "8F98BDAF"
  DESCRIPTION "ZORK open mailbox"
  COMMANDS "open mailbox"
  )

add_zemu_test(zork-multiline-command ${zemu_8xp} JSON)


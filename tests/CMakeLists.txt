set(TESTS zork-welcome)

set(TESTGEN ${CMAKE_CURRENT_SOURCE_DIR}/testgen.sh)

# Test Generator
function(add_zemu_test NAME EXEC)
  cmake_parse_arguments(ZT
    ""
    "VARDIR;CRC;DESCRIPTION"
    ""
    ${ARGN}
    )

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

  # Generate test command
  add_custom_command(OUTPUT ${NAME}.json
    COMMAND ${TESTGEN} -r ../misc/ce.rom -t ZEMU -v ${ZT_VARDIR} -x ${EXEC} -c ${ZT_CRC} ${DESC_FLAG} -o ${NAME}.json
    DEPENDS ${TESTGEN}
    )

  # Generate test target
  add_custom_target(${NAME}_tgt ALL
    DEPENDS ${NAME}.json
    )

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

# foreach(TEST ${TESTS})
#   get_filename_component(${TEST}_json ${TEST}.json ABSOLUTE)
#   add_test(NAME ${TEST}
#     COMMAND cemu-autotester ${${TEST}_json}
#     )
# endforeach()


# ./testgen.sh -r ../misc/ce.rom -t ZEMU -v ../vars/zork -x ../src/zemu/zemu.8xp -c E3E88479 -m "ZORK welcome screen" -o zork-welcome.json 

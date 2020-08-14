set(TESTS zork-welcome)

foreach(TEST ${TESTS})
  get_filename_component(${TEST}_json ${TEST}.json ABSOLUTE)
  add_test(NAME ${TEST}
    COMMAND cemu-autotester ${${TEST}_json}
    )
endforeach()

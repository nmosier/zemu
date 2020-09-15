function(add_zscript NAME TXT)
  set(VAR ${NAME}.8xv)
  add_custom_command(OUTPUT ${VAR}
    COMMAND tr '\\n' '\\362' < ${TXT} | LD_LIBRARY_PATH=/usr/local/lib tipack -o ${VAR} -n ZSCRIPT
    DEPENDS ${TXT}
    )
  add_custom_target(${NAME} ALL
    DEPENDS ${NAME}.8xv
    )
endfunction()

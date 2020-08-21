foreach(DRIVER create rw read copy)
  add_8xp(${DRIVER}83plus ${DRIVER}.z80
    NAME ${DRIVER}83plus
    PLATFORM TI83PLUS
    )
  add_8xp(${DRIVER}84pce ${DRIVER}.z80
    NAME ${DRIVER}84pce
    PLATFORM TI84PCE
    )
endforeach()

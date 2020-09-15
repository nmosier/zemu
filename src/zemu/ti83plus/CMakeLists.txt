set(PLATFORM TI83PLUS)
add_compile_definitions(ZSELECT_GAME=1)
add_8xp(zemu83p ../zemu.z80
  NAME zemu
  DEFINITIONS ZERR_BASIC=1
  )

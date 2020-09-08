set(PLATFORM TI84PCE)
add_compile_definitions(ZTEST=1)
# add_compile_definitions(ZSTORYNAME=\\\"TRIS\\\")
add_compile_definitions(ZSELECT_GAME=1)
add_8xp(zemu84pce ../zemu.z80
  NAME zemu)
add_8xp(zemudbg ../zemu.z80
  DEFINITIONS ZDBG=1
  NAME zemudbg
  )

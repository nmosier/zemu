set(PLATFORM TI84PCE)
include_directories(${CMAKE_SOURCE_DIR}/include/zemu)
add_compile_definitions(ZCURSOR=1 ZSELECT_GAME=0 ZOFFSET=1)
add_compile_options(-L)

add_8xp(zemu zemu.z80)

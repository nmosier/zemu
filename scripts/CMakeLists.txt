# Utility Commands

# find unused labels in /src/zemu
set(ZEMU_SRC ${CMAKE_SOURCE_DIR}/src/zemu)
set(ZEMU_INC ${CMAKE_SOURCE_DIR}/include/zemu)
add_custom_target(unused-labels
  find ${ZEMU_SRC} ${ZEMU_INC} -name "*.z80" -or -name "*.inc" | xargs ./unused.awk
  )

# find unused labels for TI83PLUS target in /src/zemu
add_custom_target(unused-labels-ti83p
  find ${ZEMU_SRC} ${ZEMU_INC} ${ZEMU_SRC}/ti83plus ${ZEMU_INC}/ti83plus -depth 1 -name "*.z80" -or -name "*.inc" | xargs ./unused.awk
  )

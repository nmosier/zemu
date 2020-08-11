add_8xp(zemu zemu.z80
  SOURCES zaddr.z80 zapp.z80 zbranch.z80 zcall.z80 zcode.z80 zcpu.z80 zdbg.z80 zdict.z80 zdisp.z80 zerr.z80 zexec.z80 zhdr.z80 zhex.z80 zin.z80 zmap.z80 zmem.z80 zname.z80 zobj.z80 zop.z80 zrand.z80 zsave.z80 zstr.z80 zutil.z80 zvar.z80 zwin.z80
  INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include/zemu ${CMAKE_SOURCE_DIR}/zemu 
  DEFINITIONS ${PLATFORM}=1
  INCLUDES zaddr.inc zapp.inc zcall.inc zcode.inc zdbg.inc zdict.inc zdisp.inc zemu.inc zerr.inc zhdr.inc zhex.inc zin.inc zlog.inc zmem.inc zobj.inc zrand.inc zsave.inc zstr.inc zti.inc zutil.inc zvar.inc zwin.inc
  )

#ifndef __ZTI_INC
#define __ZTI_INC

#ifdef TI84PCE

#undef TI84PCE
#include "ti84pce.inc"
#define TI84PCE

#else

#ifdef TI83PLUS

#undef TI83PLUS
#include "ti83plus.inc"
#define TI83PLUS

#endif

#endif

#endif
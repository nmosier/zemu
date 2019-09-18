/* C Preprocessor macros for preprocessing ZEMU src *
 * (since SPASM-NG sucks at parameterized macros)   */

#if TI84PCE
#include "ti84pce/zcpp.h"
#elif TI83PLUS
#include "ti83plus/zcpp.h"
#endif

#define LD_R_R(r1, r2) ld r1,r2
#define LD_R_IX(r, i)  ld r,(ix+i)
#define LD_R_IY(r, i)  ld r,(iy+i)
#define LD_IX_R(r, i)  ld (ix+i),r
#define LD_IY_R(r, i)  ld (iy+i),r

#define HI "Hello, world!"

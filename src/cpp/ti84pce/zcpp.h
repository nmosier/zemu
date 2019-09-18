#define CLEAR_UPPER_RR(rr, rrh, rrl) ld rr,0
#define UCAST_A_TO_RR(rr, rrh, rrl)             \
   ld rr,0                                      \
   ld rl,a
#define LD_RR_RR(rr1, rr1h, rr1l, rr2, rr2h, rr2l) \
   push rr2                                        \
   pop rr1
#define LEA_RR_XY(rr, rrh, rrl, xy, xyh, xyl, off, ss, ssh, ssl)   lea  rr,xy+off
#define LD_RR_FROM_XY(rr, rrh, rrl, xy, xyh, xyl, off)  ld rr,(xy+off)

   
   

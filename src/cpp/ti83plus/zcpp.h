#define CLEAR_UPPER_RR(rr, rrh, rrl)
#define UCAST_A_TO_RR(rr, rrh, rrl)                \
   ld rrh,0                                        \
   ld rrl,a
#define LD_RR_RR(rr1, rr1h, rr1l, rr2, rr2h, rr2l) \
   ld rr1h,rr2h                                    \
   ld rr1l,rr2l
#define LEA_RR_XY(rr, rrh, rrl, xy, xyh, xyl, off, ss, ssh, ssl)   \
   ld ss,off                                                       \
   add xy,ss
#define LD_RR_FROM_XY(rr, rrh, rrl, xy, xyh, xyl, off)   \
   ld rrl,(xy+off)                                       \
   ld rrh,(xy+off+1)

   

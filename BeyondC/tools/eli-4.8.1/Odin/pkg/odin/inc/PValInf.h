#ifndef TPS_PValINF
#define TPS_PValINF

typedef struct _tps_PValInf {
   tp_LocPVal Father, Brother, Son;

   tp_LocHdr LocHdr;
   tp_LocPVal ValLocPVal;
   tp_LocHdr DataLocHdr;
   }				tps_PValInf;

#endif

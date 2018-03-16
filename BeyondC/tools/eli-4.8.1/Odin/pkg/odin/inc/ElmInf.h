#ifndef TPS_ELMINF
#define TPS_ELMINF


typedef struct _tps_ElmInf {
   tp_LocHdr LocHdr;
   tp_LocElm BackLink, Link;
   tp_LocPrm LocPrm;
   tp_LocHdr ListLocHdr;
   tp_LocElm Next;
   }				tps_ElmInf;

#endif

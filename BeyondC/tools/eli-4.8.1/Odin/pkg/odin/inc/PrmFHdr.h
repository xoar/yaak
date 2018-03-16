#ifndef TPS_PRMFHDR
#define TPS_PRMFHDR


typedef struct _tps_PrmFHdr {
   tp_FilHdr FilHdr;
   tp_FilPrm FilPrm;
   tp_PrmFHdr Next;
   boolean InUse;
   }				tps_PrmFHdr;

#endif

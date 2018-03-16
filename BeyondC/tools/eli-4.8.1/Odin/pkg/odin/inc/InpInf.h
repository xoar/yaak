#ifndef TPS_INPINF
#define TPS_INPINF


typedef struct _tps_InpInf {
   int IArg;
   tp_LocHdr LocHdr;
   tp_LocStr LocStr;
   tp_LocInp BackLink, Link;
   tp_InpKind InpKind;
   tp_LocHdr OutLocHdr;
   tp_LocInp Next;
   }				tps_InpInf;

#endif

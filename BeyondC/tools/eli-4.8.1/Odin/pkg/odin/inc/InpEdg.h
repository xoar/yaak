#ifndef TPS_SRCEDG
#define TPS_SRCEDG


typedef struct _tps_InpEdg {
   tp_InpSpc InpSpc;
   tp_InpKind InpKind;
   boolean IsUserArg;
   tp_InpEdg Next;
   }				tps_InpEdg;

#endif

#ifndef TPS_INPSPC
#define TPS_INPSPC

typedef struct _tps_InpSpc {
   tp_ISKind ISKind;
   tp_FilTyp FilTyp;
   tp_PrmTyp PrmTyp;
   tp_Str Str;
   boolean IsEnvVar;
   tp_InpSpc InpSpc;
   tp_InpSpc Next;
   int Index;
   tp_InpSpc Link;
   }				tps_InpSpc;

#endif

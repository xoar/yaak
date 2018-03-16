#ifndef TPS_PRMTYPLST
#define TPS_PRMTYPLST

typedef struct _tps_PrmTypLst {
   tp_PrmTyp PrmTyp;
   tp_PrmTypLst Next;
   tp_PrmTypLst Brother;
   tp_PrmTypLst Son;
   int Index;
   tp_PrmTypLst Link;
   }				tps_PrmTypLst;

#endif

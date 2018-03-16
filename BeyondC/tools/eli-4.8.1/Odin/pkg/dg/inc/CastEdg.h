#ifndef TPS_CASTEDG
#define TPS_CASTEDG

typedef struct _tps_CastEdg {
   tp_FilTyp FrmFilTyp;
   tp_FilTyp FilTyp;
   tp_CastEdg FrmNext;
   tp_CastEdg Next;
   int Index;
   tp_CastEdg Link;
   }				tps_CastEdg;

#endif

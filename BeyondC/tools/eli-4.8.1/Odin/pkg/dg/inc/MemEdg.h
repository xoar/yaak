#ifndef TPS_MEMEDG
#define TPS_MEMEDG

typedef struct _tps_MemEdg {
   tp_FilTyp FilTyp;
   tp_MemEdg Next;
   int Index;
   tp_MemEdg Link;
   }				tps_MemEdg;

#endif

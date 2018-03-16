#ifndef TPS_DRVEDG
#define TPS_DRVEDG

typedef struct _tps_DrvEdg {
   tp_FilTyp FrmFilTyp;
   tp_FilTyp FilTyp;
   tp_PrmTypLst PrmTypLst;
   tp_DrvEdg FrmNext;
   tp_DrvEdg Next;
   int Index;
   tp_DrvEdg Link;
   boolean Flag;
   }				tps_DrvEdg;

#endif

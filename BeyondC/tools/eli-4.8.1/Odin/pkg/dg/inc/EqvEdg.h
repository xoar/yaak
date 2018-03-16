#ifndef TPS_EQVEDG
#define TPS_EQVEDG

typedef struct _tps_EqvEdg {
   tp_FilTyp FrmFilTyp;
   tp_FilTyp FilTyp;
   tp_EqvEdg FrmNext;
   tp_EqvEdg Next;
   int Index;
   tp_EqvEdg Link;
   }				tps_EqvEdg;

#endif

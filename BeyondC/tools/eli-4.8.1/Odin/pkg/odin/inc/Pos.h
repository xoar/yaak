#ifndef TPS_POS
#define TPS_POS


typedef struct _tps_Pos {
   tp_PType PType;
   tp_FilTyp FilTyp;
   tp_DrvEdg DrvEdg;
   tp_Pos Base;
   tp_Pos Next;
   tp_Pos Last;
   }				tps_Pos;

#endif

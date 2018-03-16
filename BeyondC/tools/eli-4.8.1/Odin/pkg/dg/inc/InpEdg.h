#ifndef TPS_INPEDG
#define TPS_INPEDG

typedef struct _tps_InpEdg {
   tp_FilTyp FilTyp;
   tp_InpSpc InpSpc;
   tp_InpKind InpKind;
   boolean IsUserArg;
   tp_InpEdg Next;
   tp_Tool Tool;
   tp_InpEdg InpLink;
   boolean Done;
   int Index;
   tp_InpEdg Link;
   }				tps_InpEdg;

#endif

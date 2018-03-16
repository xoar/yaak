#ifndef TPS_DRVPTH
#define TPS_DRVPTH

typedef struct _tps_DrvPth {
   tp_DPType DPType;
   tp_FKind FKind;
   tp_FilTyp FilTyp;
   tp_DrvEdg DrvEdg;
   tp_DrvPth Next;
   boolean InUse;
   }				tps_DrvPth;

#endif

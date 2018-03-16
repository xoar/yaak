#ifndef TPS_SRCTYP
#define TPS_SRCTYP

typedef struct _tps_SrcTyp {
   tp_Pattern Pattern;
   boolean IsPrefix;
   tp_FilTyp FilTyp;
   tp_SrcTyp Link;
   }				tps_SrcTyp;

#endif

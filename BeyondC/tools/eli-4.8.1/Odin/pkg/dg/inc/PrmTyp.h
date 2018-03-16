#ifndef TPS_PRMTYP
#define TPS_PRMTYP

typedef struct _tps_PrmTyp {
   tp_PTName PTName;
   tp_Desc Desc;
   int HelpLevel;
   tp_FilTyp FilTyp;
   int Index;
   tp_PrmTyp Link;
   }				tps_PrmTyp;

#endif

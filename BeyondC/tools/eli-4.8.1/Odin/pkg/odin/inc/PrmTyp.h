#ifndef TPS_PRMTYP
#define TPS_PRMTYP

typedef struct _tps_PrmTyp {
   tp_PTName PTName;
   tp_Desc Desc;
   int HelpLevel;
   tp_FilTyp FilTyp;
   tp_LocPVal RootLocPVal;
   tp_LocHdr StrDirLocHdr;
   boolean Mark;
   int IPrmTyp;
   }				tps_PrmTyp;

#endif

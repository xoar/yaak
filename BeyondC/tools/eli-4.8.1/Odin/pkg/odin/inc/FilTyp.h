#ifndef TPS_FILTYP
#define TPS_FILTYP

typedef struct _tps_FilTyp {
   tp_FTClass FTClass;
   tp_FTName FTName;
   tp_Desc Desc;
   int HelpLevel;
   tp_FilTyp ArgFilTyp;
   tp_Tool Tool;
   tp_MemEdg MemEdg;
   tp_EqvEdg EqvEdg;
   tp_CastEdg CastEdg;
   tp_DrvEdg DrvEdg;
   tp_PrmTypLst MapPrmTypLst;
   boolean IsCopy, IsGrouping, IsGroupingInput;
   boolean Reach;
   boolean Mark;
   tp_Pos Pos;
   int IFilTyp;
   }				tps_FilTyp;

#endif

#ifndef TPS_FILHDR
#define TPS_FILHDR

#include "HdrInf.h"

typedef struct _tps_FilHdr {
   tp_LocHdr LocHdr;
   tp_Item NextHash;

   tps_HdrInf HdrInf;
   tp_FilTyp FilTyp;
   tp_FilPrm FilPrm;
   tp_Str Ident;

   int Cnt;
   tp_FilHdr PrevFree, NextFree;

   boolean Modified;
   tp_FilHdr NextMod;

   tp_Flag Flag;
   int AnyOKDepth;
   int ElmDepth;
   int ElmTag;
   tp_FilHdr SCC;
   tp_Status DepStatus;
   tp_Date DepModDate;
   boolean PndFlag, ElmNamePndFlag, ElmPndFlag;
   }				tps_FilHdr;

#endif

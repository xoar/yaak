#ifndef TPS_FILSRC
#define TPS_FILSRC

#include "InpInf.h"

typedef struct _tps_FilInp {
   tp_LocInp LocInp;
   tp_Item NextHash;

   tps_InpInf InpInf;

   int Cnt;
   tp_FilInp PrevFree, NextFree;

   boolean Modified;
   tp_FilInp NextMod;
   }				tps_FilInp;

#endif

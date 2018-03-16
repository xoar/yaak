#ifndef TPS_FILELM
#define TPS_FILELM

#include "ElmInf.h"

typedef struct _tps_FilElm {
   tp_LocElm LocElm;
   tp_Item NextHash;

   tps_ElmInf ElmInf;
   tp_FilPrm FilPrm;

   int Cnt;
   tp_FilElm PrevFree, NextFree;

   boolean Modified;
   tp_FilElm NextMod;
   }				tps_FilElm;

#endif

#ifndef TPS_FILPRM
#define TPS_FILPRM

#include "PrmInf.h"

typedef struct _tps_FilPrm {
   tp_LocPrm LocPrm;
   tp_Item NextHash;

   tp_FilPrm Father, Brother, Son;

   tps_PrmInf PrmInf;
   tp_PrmTyp PrmTyp;
   tp_FilPVal FilPVal;
   }				tps_FilPrm;

#endif

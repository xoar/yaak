#ifndef TPS_FILPVAL
#define TPS_FILPVAL

#include "PValInf.h"

typedef struct _tps_FilPVal {
   tp_LocPVal LocPVal;
   tp_Item NextHash;

   tp_FilPVal Father, Brother, Son;

   tps_PValInf PValInf;
   }				tps_FilPVal;

#endif

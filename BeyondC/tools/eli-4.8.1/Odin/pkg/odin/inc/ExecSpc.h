#ifndef TPS_EXECSPC
#define TPS_EXECSPC

#include "Inputs.h"
#include "Outputs.h"

typedef struct _tps_ExecSpc {
   tp_Job Job;
   tp_FilHdr FilHdr;
   tp_FilTyp FilTyp;
   int NumInps;
   tps_InpFilHdrs InpFilHdrs;
   int NumOuts;
   tps_OutFilHdrs OutFilHdrs;
   }				tps_ExecSpc;

#endif

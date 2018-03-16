#ifndef TPS_BUILD
#define TPS_BUILD

typedef struct _tps_Build {
   tp_Host Host;
   tp_BuildID BuildID;
   tp_JobID JobID;
   tp_Build Next;
   }				tps_Build;

#endif

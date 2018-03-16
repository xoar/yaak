#ifndef TPS_HOST
#define TPS_HOST

typedef struct _tps_Host {
   tp_HostName HostName;
   int FD;
   int RBS_Id;
   tp_Host Next;
   }				tps_Host;

#endif

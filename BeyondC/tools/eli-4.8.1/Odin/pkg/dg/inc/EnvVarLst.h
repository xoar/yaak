#ifndef TPS_ENVVARLST
#define TPS_ENVVARLST

typedef struct _tps_EnvVarLst {
   tp_EnvVar EnvVar;
   tp_EnvVarLst Next;
   tp_EnvVarLst Brother;
   tp_EnvVarLst Son;
   int Index;
   tp_EnvVarLst Link;
   }				tps_EnvVarLst;

#endif

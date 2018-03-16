#ifndef TPS_ENVVAR
#define TPS_ENVVAR

typedef struct _tps_EnvVar {
   tp_Str Name;
   tp_Desc Desc;
   int HelpLevel;
   tp_Str Default;
   boolean IsFile;
   }				tps_EnvVar;

#endif

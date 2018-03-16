#ifndef TPS_ENVVAR
#define TPS_ENVVAR

typedef struct _tps_EnvVar {
   tp_Str Name;
   tp_Desc Desc;
   int HelpLevel;
   tp_Str Default;
   boolean IsFile;
   int Index;
   tp_EnvVar Link;
   }				tps_EnvVar;

#endif

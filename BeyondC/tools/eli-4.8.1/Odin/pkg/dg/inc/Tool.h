#ifndef TPS_TOOL
#define TPS_TOOL

typedef struct _tps_Tool {
   tp_TClass TClass;
   tp_FilTyp FilTyp;
   tp_InpEdg InpEdg;
   tp_InpEdg HomInpEdg;
   tp_PrmTypLst BasePrmTypLst, PrmTypLst;
   tp_EnvVarLst EnvVarLst;
   tp_Package Package;
   boolean Flag;
   int Defer;
   int Index;
   tp_Tool Link;
   }				tps_Tool;

#endif

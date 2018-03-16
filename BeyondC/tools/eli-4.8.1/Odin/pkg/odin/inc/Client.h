#ifndef TPS_CLIENT
#define TPS_CLIENT

typedef struct _tps_Client {
   tp_ClientID ClientID;
   tp_FHLst CWDFilHdrS;
   boolean KeepGoing;
   int ErrLevel, WarnLevel, LogLevel, HelpLevel;
   tp_FilHdr FilHdr;
   boolean NeedsData;
   tp_FHLst ToDo, LastToDo;
   int NumJobs, MaxJobs;
   tp_Job Job;
   boolean Interrupted;
   tp_Client Next;
   boolean InUse;
   }				tps_Client;

#endif

#ifndef TPS_JOB
#define TPS_JOB

typedef struct _tps_Job {
   tp_JobID JobID;
   tp_FilHdr FilHdr;
   tp_FileName JobDirName;
   tp_FileName WarningFN;
   tp_FileName ErrorFN;
   boolean Canceled;
   tp_Job Next;
   boolean InUse;
   }				tps_Job;

#endif

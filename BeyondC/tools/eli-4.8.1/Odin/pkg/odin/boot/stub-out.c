#include "inc/GMC.h"
#include "inc/Str.h"
#include "inc/FileName.h"

extern boolean IPC_Do_Return;
extern int *IPC_IArg1, *IPC_IArg2, *IPC_IArg3;
extern tp_FileName IPC_SArg1;
extern tp_Str IPC_SArg2, IPC_SArg3;

#ifndef CLIENT_ONLY
void
Add_BuildArg(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   boolean IPC_Abort;

#ifndef SERVER_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Add_BuildArg(FileName);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 2);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, FileName);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef SERVER_ONLY
   };
#endif
   }
#endif

#ifndef CLIENT_ONLY
void
Do_Build(
   GMC_ARG(tp_JobID, JobID),
   GMC_ARG(tp_FileName, JobDirName),
   GMC_ARG(tp_FileName, LogFileName)
   )
   GMC_DCL(tp_JobID, JobID)
   GMC_DCL(tp_FileName, JobDirName)
   GMC_DCL(tp_FileName, LogFileName)
{
   boolean IPC_Abort;

#ifndef SERVER_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Do_Build(JobID, JobDirName, LogFileName);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 3);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, JobID);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, JobDirName);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, LogFileName);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef SERVER_ONLY
   };
#endif
   }
#endif

#ifndef CLIENT_ONLY
void
Abort_Build(
   GMC_ARG(tp_JobID, JobID)
   )
   GMC_DCL(tp_JobID, JobID)
{
   boolean IPC_Abort;

#ifndef SERVER_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Abort_Build(JobID);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 4);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, JobID);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef SERVER_ONLY
   };
#endif
   }
#endif

#ifndef CLIENT_ONLY
void
Do_MakeReadOnly(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   boolean IPC_Abort;

#ifndef SERVER_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Do_MakeReadOnly(FileName);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 5);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, FileName);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef SERVER_ONLY
   };
#endif
   }
#endif

#ifndef CLIENT_ONLY
void
ErrMessage(
   GMC_ARG(char*, Message)
   )
   GMC_DCL(char*, Message)
{
   boolean IPC_Abort;

#ifndef SERVER_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_ErrMessage(Message);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 6);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, Message);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef SERVER_ONLY
   };
#endif
   }
#endif

#ifndef CLIENT_ONLY
void
LogMessage(
   GMC_ARG(char*, Message)
   )
   GMC_DCL(char*, Message)
{
   boolean IPC_Abort;

#ifndef SERVER_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_LogMessage(Message);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 7);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, Message);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef SERVER_ONLY
   };
#endif
   }
#endif

#ifndef CLIENT_ONLY
void
FileErrMessage(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   boolean IPC_Abort;

#ifndef SERVER_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_FileErrMessage(FileName);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 8);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, FileName);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef SERVER_ONLY
   };
#endif
   }
#endif

#ifndef CLIENT_ONLY
void
Next_OdinFile(
   GMC_ARG(tp_Str, OdinExpr),
   GMC_ARG(int, ID)
   )
   GMC_DCL(tp_Str, OdinExpr)
   GMC_DCL(int, ID)
{
   boolean IPC_Abort;

#ifndef SERVER_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Next_OdinFile(OdinExpr, ID);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 9);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, OdinExpr);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, ID);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef SERVER_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Get_UseCount(
   GMC_ARG(int*, CountPtr)
   )
   GMC_DCL(int*, CountPtr)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Get_UseCount(CountPtr);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 10);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
   IPC_Read_Int(&IPC_Abort, CountPtr);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Get_CurSize(
   GMC_ARG(int*, SizePtr)
   )
   GMC_DCL(int*, SizePtr)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Get_CurSize(SizePtr);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 11);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
   IPC_Read_Int(&IPC_Abort, SizePtr);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
ShutDown(GMC_ARG_VOID)
{
   boolean IPC_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_ShutDown();
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 12);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Get_Banner(
   GMC_ARG(tp_Str, Str)
   )
   GMC_DCL(tp_Str, Str)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Get_Banner(Str);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 13);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
   IPC_Read_Str(&IPC_Abort, Str);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Do_Interrupt(
   GMC_ARG(boolean, InterruptFlag)
   )
   GMC_DCL(boolean, InterruptFlag)
{
   boolean IPC_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Do_Interrupt(InterruptFlag);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 14);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, InterruptFlag);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Do_Alias(
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(boolean, ForceFlag)
   )
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(boolean, ForceFlag)
{
   boolean IPC_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Do_Alias(FileName, ForceFlag);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 15);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, FileName);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, ForceFlag);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Get_Alias(
   GMC_ARG(tp_FileName, OutFileName),
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, OutFileName)
   GMC_DCL(tp_FileName, FileName)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;
   tps_Str buf;
   size_t sz;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Get_Alias(OutFileName, FileName);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 16);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, FileName);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
   IPC_Read_Str(&IPC_Abort, buf);
   if (IPC_Abort) IPC_Do_Abort();
   sz = snprintf(OutFileName, MAX_FileName, "%s", buf);
   if (sz >= MAX_FileName) {
      (void)fprintf(stderr, "File name too long (MAX_FileName=%d): %s\n",
                  MAX_FileName, buf);
      exit(1); }/*if*/;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Job_Done(
   GMC_ARG(tp_JobID, JobID),
   GMC_ARG(boolean, Abort)
   )
   GMC_DCL(tp_JobID, JobID)
   GMC_DCL(boolean, Abort)
{
   boolean IPC_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Job_Done(JobID, Abort);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 17);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, JobID);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, Abort);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Test(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Test(FileName);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 18);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, FileName);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Test_All(GMC_ARG_VOID)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Test_All();
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 19);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Get_OdinFile(
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(tp_Status*, StatusPtr),
   GMC_ARG(boolean*, ExecFlagPtr),
   GMC_ARG(tp_Str, OdinExpr),
   GMC_ARG(boolean, NeedsData)
   )
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(tp_Status*, StatusPtr)
   GMC_DCL(boolean*, ExecFlagPtr)
   GMC_DCL(tp_Str, OdinExpr)
   GMC_DCL(boolean, NeedsData)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;
   tps_Str buf;
   size_t sz;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      FORBIDDEN(IPC_Do_Return);
      FORBIDDEN(IPC_SArg1 != NIL);
      IPC_SArg1 = FileName;
      FORBIDDEN(IPC_IArg2 != NIL);
      IPC_IArg2 = StatusPtr;
      FORBIDDEN(IPC_IArg3 != NIL);
      IPC_IArg3 = ExecFlagPtr;
      Local_Get_OdinFile(OdinExpr, NeedsData);
      if (!IPC_Do_Return) {
         IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
         FORBIDDEN(IPC_Cmd_Abort);
         FORBIDDEN(!IPC_Do_Return); }/*if*/;
      IPC_Do_Return = FALSE;
      IPC_SArg1 = NIL;
      IPC_IArg2 = NIL;
      IPC_IArg3 = NIL;
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 20);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, OdinExpr);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, NeedsData);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
   IPC_Read_Str(&IPC_Abort, buf);
   if (IPC_Abort) IPC_Do_Abort();
   sz = snprintf(FileName, MAX_FileName, "%s", buf);
   if (sz >= MAX_FileName) {
      (void)fprintf(stderr, "File name too long (MAX_FileName=%d): %s\n",
                  MAX_FileName, buf);
      exit(1); }/*if*/;
   IPC_Read_Int(&IPC_Abort, StatusPtr);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Read_Int(&IPC_Abort, ExecFlagPtr);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Set_CWD(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Set_CWD(FileName);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 21);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, FileName);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Push_Context(
   GMC_ARG(tp_FileName, DirName),
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, DirName)
   GMC_DCL(tp_FileName, FileName)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;
   tps_Str buf;
   size_t sz;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Push_Context(DirName, FileName);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 22);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, FileName);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
   IPC_Read_Str(&IPC_Abort, buf);
   if (IPC_Abort) IPC_Do_Abort();
   sz = snprintf(DirName, MAX_FileName, "%s", buf);
   if (sz >= MAX_FileName) {
      (void)fprintf(stderr, "File name too long (MAX_FileName=%d): %s\n",
                  MAX_FileName, buf);
      exit(1); }/*if*/;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Pop_Context(
   GMC_ARG(tp_FileName, DirName)
   )
   GMC_DCL(tp_FileName, DirName)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;
   tps_Str buf;
   size_t sz;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Pop_Context(DirName);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 23);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
   IPC_Read_Str(&IPC_Abort, buf);
   if (IPC_Abort) IPC_Do_Abort();
   sz = snprintf(DirName, MAX_FileName, "%s", buf);
   if (sz >= MAX_FileName) {
      (void)fprintf(stderr, "File name too long (MAX_FileName=%d): %s\n",
                  MAX_FileName, buf);
      exit(1); }/*if*/;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Set_KeepGoing(
   GMC_ARG(int, Flag)
   )
   GMC_DCL(int, Flag)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Set_KeepGoing(Flag);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 24);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, Flag);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Set_ErrLevel(
   GMC_ARG(int, ErrLevel)
   )
   GMC_DCL(int, ErrLevel)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Set_ErrLevel(ErrLevel);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 25);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, ErrLevel);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Set_WarnLevel(
   GMC_ARG(int, WarnLevel)
   )
   GMC_DCL(int, WarnLevel)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Set_WarnLevel(WarnLevel);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 26);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, WarnLevel);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Set_LogLevel(
   GMC_ARG(tp_LogLevel, LogLevel)
   )
   GMC_DCL(tp_LogLevel, LogLevel)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Set_LogLevel(LogLevel);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 27);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, LogLevel);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Set_HelpLevel(
   GMC_ARG(int, HelpLevel)
   )
   GMC_DCL(int, HelpLevel)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Set_HelpLevel(HelpLevel);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 28);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, HelpLevel);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Set_Debug(
   GMC_ARG(tp_Str, DebugName)
   )
   GMC_DCL(tp_Str, DebugName)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Set_Debug(DebugName);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 29);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, DebugName);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Set_MaxJobs(
   GMC_ARG(int, MaxJobs)
   )
   GMC_DCL(int, MaxJobs)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Set_MaxJobs(MaxJobs);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 30);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, MaxJobs);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Redo(
   GMC_ARG(tp_Str, OdinExpr)
   )
   GMC_DCL(tp_Str, OdinExpr)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Redo(OdinExpr);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 31);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, OdinExpr);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
OdinExpr_ID(
   GMC_ARG(int*, IDPtr),
   GMC_ARG(tp_Str, OdinExpr)
   )
   GMC_DCL(int*, IDPtr)
   GMC_DCL(tp_Str, OdinExpr)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_OdinExpr_ID(IDPtr, OdinExpr);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 32);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, OdinExpr);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
   IPC_Read_Int(&IPC_Abort, IDPtr);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
ID_OdinExpr(
   GMC_ARG(tp_Str, OdinExpr),
   GMC_ARG(int, ID)
   )
   GMC_DCL(tp_Str, OdinExpr)
   GMC_DCL(int, ID)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_ID_OdinExpr(OdinExpr, ID);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 33);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, ID);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
   IPC_Read_Str(&IPC_Abort, OdinExpr);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
ID_LongOdinExpr(
   GMC_ARG(tp_Str, OdinExpr),
   GMC_ARG(int, ID)
   )
   GMC_DCL(tp_Str, OdinExpr)
   GMC_DCL(int, ID)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_ID_LongOdinExpr(OdinExpr, ID);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 34);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, ID);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
   IPC_Read_Str(&IPC_Abort, OdinExpr);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Get_Status(
   GMC_ARG(tp_Status*, StatusPtr),
   GMC_ARG(tp_Status*, ElmStatusPtr),
   GMC_ARG(int, ID)
   )
   GMC_DCL(tp_Status*, StatusPtr)
   GMC_DCL(tp_Status*, ElmStatusPtr)
   GMC_DCL(int, ID)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Get_Status(StatusPtr, ElmStatusPtr, ID);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 35);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, ID);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
   IPC_Read_Int(&IPC_Abort, StatusPtr);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Read_Int(&IPC_Abort, ElmStatusPtr);
   if (IPC_Abort) IPC_Do_Abort();
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Get_Elements(
   GMC_ARG(int, ID)
   )
   GMC_DCL(int, ID)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Get_Elements(ID);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 36);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, ID);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Get_ElementsOf(
   GMC_ARG(int, ID)
   )
   GMC_DCL(int, ID)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Get_ElementsOf(ID);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 37);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, ID);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Get_Inputs(
   GMC_ARG(int, ID)
   )
   GMC_DCL(int, ID)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Get_Inputs(ID);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 38);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, ID);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Get_Outputs(
   GMC_ARG(int, ID)
   )
   GMC_DCL(int, ID)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Get_Outputs(ID);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 39);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, ID);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#ifndef SERVER_ONLY
void
Get_DPath(
   GMC_ARG(tp_Str, OdinExpr)
   )
   GMC_DCL(tp_Str, OdinExpr)
{
   boolean IPC_Abort;

   boolean IPC_Cmd_Abort;

#ifndef CLIENT_ONLY
   if (IsServer && Is_LocalClient(CurrentClient)) {
      Local_Get_DPath(OdinExpr);
   }else{
#endif
   IPC_Write_Int(&IPC_Abort, 40);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, OdinExpr);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Get_Commands(&IPC_Cmd_Abort, (char *)NIL);
   FORBIDDEN(IPC_Cmd_Abort);
   FORBIDDEN(!IPC_Do_Return);
   IPC_Do_Return = FALSE;
#ifndef CLIENT_ONLY
   };
#endif
   }
#endif

#include "inc/GMC.h"
#include "inc/Str.h"

extern boolean IPC_Do_Return;
extern int *IPC_IArg1, *IPC_IArg2, *IPC_IArg3;
extern tp_Str IPC_SArg1, IPC_SArg2, IPC_SArg3;


#ifndef SERVER_ONLY
static void
Add_BuildArg_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str FileName;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, FileName);
   if (*IPC_AbortPtr) return;
   Local_Add_BuildArg(FileName);
}
#endif

#ifndef SERVER_ONLY
static void
Do_Build_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int JobID;
   tps_Str JobDirName;
   tps_Str LogFileName;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &JobID);
   if (*IPC_AbortPtr) return;
   IPC_Read_Str(IPC_AbortPtr, JobDirName);
   if (*IPC_AbortPtr) return;
   IPC_Read_Str(IPC_AbortPtr, LogFileName);
   if (*IPC_AbortPtr) return;
   Local_Do_Build(JobID, JobDirName, LogFileName);
}
#endif

#ifndef SERVER_ONLY
static void
Abort_Build_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int JobID;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &JobID);
   if (*IPC_AbortPtr) return;
   Local_Abort_Build(JobID);
}
#endif

#ifndef SERVER_ONLY
static void
Do_MakeReadOnly_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str FileName;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, FileName);
   if (*IPC_AbortPtr) return;
   Local_Do_MakeReadOnly(FileName);
}
#endif

#ifndef SERVER_ONLY
static void
ErrMessage_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str Message;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, Message);
   if (*IPC_AbortPtr) return;
   Local_ErrMessage(Message);
}
#endif

#ifndef SERVER_ONLY
static void
LogMessage_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str Message;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, Message);
   if (*IPC_AbortPtr) return;
   Local_LogMessage(Message);
}
#endif

#ifndef SERVER_ONLY
static void
FileErrMessage_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str FileName;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, FileName);
   if (*IPC_AbortPtr) return;
   Local_FileErrMessage(FileName);
}
#endif

#ifndef SERVER_ONLY
static void
Next_OdinFile_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str OdinExpr;
   int ID;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, OdinExpr);
   if (*IPC_AbortPtr) return;
   IPC_Read_Int(IPC_AbortPtr, &ID);
   if (*IPC_AbortPtr) return;
   Local_Next_OdinFile(OdinExpr, ID);
}
#endif

#ifndef CLIENT_ONLY
static void
Get_UseCount_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int CountPtr;

   *IPC_AbortPtr = FALSE;
   Local_Get_UseCount(&CountPtr);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
   IPC_Write_Int(IPC_AbortPtr, CountPtr);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Get_CurSize_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int SizePtr;

   *IPC_AbortPtr = FALSE;
   Local_Get_CurSize(&SizePtr);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
   IPC_Write_Int(IPC_AbortPtr, SizePtr);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
ShutDown_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{

   *IPC_AbortPtr = FALSE;
   Local_ShutDown();
}
#endif

#ifndef CLIENT_ONLY
static void
Get_Banner_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str Str;

   *IPC_AbortPtr = FALSE;
   Local_Get_Banner(Str);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
   IPC_Write_Str(IPC_AbortPtr, Str);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Do_Interrupt_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int InterruptFlag;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &InterruptFlag);
   if (*IPC_AbortPtr) return;
   Local_Do_Interrupt(InterruptFlag);
}
#endif

#ifndef CLIENT_ONLY
static void
Do_Alias_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str FileName;
   int ForceFlag;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, FileName);
   if (*IPC_AbortPtr) return;
   IPC_Read_Int(IPC_AbortPtr, &ForceFlag);
   if (*IPC_AbortPtr) return;
   Local_Do_Alias(FileName, ForceFlag);
}
#endif

#ifndef CLIENT_ONLY
static void
Get_Alias_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str OutFileName;
   tps_Str FileName;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, FileName);
   if (*IPC_AbortPtr) return;
   Local_Get_Alias(OutFileName, FileName);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
   IPC_Write_Str(IPC_AbortPtr, OutFileName);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Job_Done_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int JobID;
   int Abort;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &JobID);
   if (*IPC_AbortPtr) return;
   IPC_Read_Int(IPC_AbortPtr, &Abort);
   if (*IPC_AbortPtr) return;
   Local_Job_Done(JobID, Abort);
}
#endif

#ifndef CLIENT_ONLY
static void
Test_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str FileName;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, FileName);
   if (*IPC_AbortPtr) return;
   Local_Test(FileName);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Test_All_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{

   *IPC_AbortPtr = FALSE;
   Local_Test_All();
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Get_OdinFile_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str OdinExpr;
   int NeedsData;

   IPC_Read_Str(IPC_AbortPtr, OdinExpr);
   if (*IPC_AbortPtr) return;
   IPC_Read_Int(IPC_AbortPtr, &NeedsData);
   if (*IPC_AbortPtr) return;
   Local_Get_OdinFile(OdinExpr, NeedsData);
}

void
LocalEnd_Get_OdinFile(
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(tp_Status, StatusPtr),
   GMC_ARG(boolean, ExecFlagPtr)
   )
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(tp_Status, StatusPtr)
   GMC_DCL(boolean, ExecFlagPtr)
{
   boolean IPC_Abort;

   if (IsServer && Is_LocalClient(CurrentClient)) {
      (void)strcpy(IPC_SArg1, FileName);
      *IPC_IArg2 = StatusPtr;
      *IPC_IArg3 = ExecFlagPtr;
      FORBIDDEN(IPC_Do_Return);

      IPC_Do_Return = TRUE;

      return; };

   IPC_Write_Int(&IPC_Abort, 1);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Str(&IPC_Abort, FileName);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, StatusPtr);
   if (IPC_Abort) IPC_Do_Abort();
   IPC_Write_Int(&IPC_Abort, ExecFlagPtr);
   if (IPC_Abort) IPC_Do_Abort();
}
#endif

#ifndef CLIENT_ONLY
static void
Set_CWD_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str FileName;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, FileName);
   if (*IPC_AbortPtr) return;
   Local_Set_CWD(FileName);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Push_Context_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str DirName;
   tps_Str FileName;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, FileName);
   if (*IPC_AbortPtr) return;
   Local_Push_Context(DirName, FileName);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
   IPC_Write_Str(IPC_AbortPtr, DirName);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Pop_Context_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str DirName;

   *IPC_AbortPtr = FALSE;
   Local_Pop_Context(DirName);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
   IPC_Write_Str(IPC_AbortPtr, DirName);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Set_KeepGoing_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int Flag;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &Flag);
   if (*IPC_AbortPtr) return;
   Local_Set_KeepGoing(Flag);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Set_ErrLevel_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int ErrLevel;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &ErrLevel);
   if (*IPC_AbortPtr) return;
   Local_Set_ErrLevel(ErrLevel);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Set_WarnLevel_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int WarnLevel;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &WarnLevel);
   if (*IPC_AbortPtr) return;
   Local_Set_WarnLevel(WarnLevel);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Set_LogLevel_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int LogLevel;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &LogLevel);
   if (*IPC_AbortPtr) return;
   Local_Set_LogLevel(LogLevel);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Set_HelpLevel_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int HelpLevel;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &HelpLevel);
   if (*IPC_AbortPtr) return;
   Local_Set_HelpLevel(HelpLevel);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Set_Debug_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str DebugName;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, DebugName);
   if (*IPC_AbortPtr) return;
   Local_Set_Debug(DebugName);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Set_MaxJobs_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int MaxJobs;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &MaxJobs);
   if (*IPC_AbortPtr) return;
   Local_Set_MaxJobs(MaxJobs);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Redo_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str OdinExpr;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, OdinExpr);
   if (*IPC_AbortPtr) return;
   Local_Redo(OdinExpr);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
OdinExpr_ID_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int IDPtr;
   tps_Str OdinExpr;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, OdinExpr);
   if (*IPC_AbortPtr) return;
   Local_OdinExpr_ID(&IDPtr, OdinExpr);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
   IPC_Write_Int(IPC_AbortPtr, IDPtr);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
ID_OdinExpr_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str OdinExpr;
   int ID;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &ID);
   if (*IPC_AbortPtr) return;
   Local_ID_OdinExpr(OdinExpr, ID);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
   IPC_Write_Str(IPC_AbortPtr, OdinExpr);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
ID_LongOdinExpr_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str OdinExpr;
   int ID;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &ID);
   if (*IPC_AbortPtr) return;
   Local_ID_LongOdinExpr(OdinExpr, ID);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
   IPC_Write_Str(IPC_AbortPtr, OdinExpr);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Get_Status_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int StatusPtr;
   int ElmStatusPtr;
   int ID;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &ID);
   if (*IPC_AbortPtr) return;
   Local_Get_Status(&StatusPtr, &ElmStatusPtr, ID);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
   IPC_Write_Int(IPC_AbortPtr, StatusPtr);
   if (*IPC_AbortPtr) return;
   IPC_Write_Int(IPC_AbortPtr, ElmStatusPtr);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Get_Elements_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int ID;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &ID);
   if (*IPC_AbortPtr) return;
   Local_Get_Elements(ID);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Get_ElementsOf_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int ID;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &ID);
   if (*IPC_AbortPtr) return;
   Local_Get_ElementsOf(ID);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Get_Inputs_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int ID;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &ID);
   if (*IPC_AbortPtr) return;
   Local_Get_Inputs(ID);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Get_Outputs_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   int ID;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Int(IPC_AbortPtr, &ID);
   if (*IPC_AbortPtr) return;
   Local_Get_Outputs(ID);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif

#ifndef CLIENT_ONLY
static void
Get_DPath_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
{
   tps_Str OdinExpr;

   *IPC_AbortPtr = FALSE;
   IPC_Read_Str(IPC_AbortPtr, OdinExpr);
   if (*IPC_AbortPtr) return;
   Local_Get_DPath(OdinExpr);
   IPC_Write_Int(IPC_AbortPtr, 1);
   if (*IPC_AbortPtr) return;
}
#endif
void
IPC_Do_Msg(
   GMC_ARG(boolean*, IPC_AbortPtr),
   GMC_ARG(int, MsgType)
   )
   GMC_DCL(boolean*, IPC_AbortPtr)
   GMC_DCL(int, MsgType)
{
   switch (MsgType) {
      case 1: {
         IPC_Do_Return = TRUE;
         *IPC_AbortPtr = FALSE;
         break; }/*case*/;
      case 2: {
#ifndef SERVER_ONLY
         Add_BuildArg_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 3: {
#ifndef SERVER_ONLY
         Do_Build_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 4: {
#ifndef SERVER_ONLY
         Abort_Build_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 5: {
#ifndef SERVER_ONLY
         Do_MakeReadOnly_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 6: {
#ifndef SERVER_ONLY
         ErrMessage_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 7: {
#ifndef SERVER_ONLY
         LogMessage_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 8: {
#ifndef SERVER_ONLY
         FileErrMessage_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 9: {
#ifndef SERVER_ONLY
         Next_OdinFile_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 10: {
#ifndef CLIENT_ONLY
         Get_UseCount_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 11: {
#ifndef CLIENT_ONLY
         Get_CurSize_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 12: {
#ifndef CLIENT_ONLY
         ShutDown_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 13: {
#ifndef CLIENT_ONLY
         Get_Banner_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 14: {
#ifndef CLIENT_ONLY
         Do_Interrupt_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 15: {
#ifndef CLIENT_ONLY
         Do_Alias_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 16: {
#ifndef CLIENT_ONLY
         Get_Alias_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 17: {
#ifndef CLIENT_ONLY
         Job_Done_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 18: {
#ifndef CLIENT_ONLY
         Test_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 19: {
#ifndef CLIENT_ONLY
         Test_All_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 20: {
#ifndef CLIENT_ONLY
         Get_OdinFile_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 21: {
#ifndef CLIENT_ONLY
         Set_CWD_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 22: {
#ifndef CLIENT_ONLY
         Push_Context_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 23: {
#ifndef CLIENT_ONLY
         Pop_Context_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 24: {
#ifndef CLIENT_ONLY
         Set_KeepGoing_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 25: {
#ifndef CLIENT_ONLY
         Set_ErrLevel_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 26: {
#ifndef CLIENT_ONLY
         Set_WarnLevel_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 27: {
#ifndef CLIENT_ONLY
         Set_LogLevel_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 28: {
#ifndef CLIENT_ONLY
         Set_HelpLevel_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 29: {
#ifndef CLIENT_ONLY
         Set_Debug_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 30: {
#ifndef CLIENT_ONLY
         Set_MaxJobs_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 31: {
#ifndef CLIENT_ONLY
         Redo_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 32: {
#ifndef CLIENT_ONLY
         OdinExpr_ID_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 33: {
#ifndef CLIENT_ONLY
         ID_OdinExpr_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 34: {
#ifndef CLIENT_ONLY
         ID_LongOdinExpr_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 35: {
#ifndef CLIENT_ONLY
         Get_Status_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 36: {
#ifndef CLIENT_ONLY
         Get_Elements_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 37: {
#ifndef CLIENT_ONLY
         Get_ElementsOf_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 38: {
#ifndef CLIENT_ONLY
         Get_Inputs_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 39: {
#ifndef CLIENT_ONLY
         Get_Outputs_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      case 40: {
#ifndef CLIENT_ONLY
         Get_DPath_Msg(IPC_AbortPtr);
#else
         *IPC_AbortPtr = TRUE;
#endif
         break; }/*case*/;
      default: {
         FATALERROR("Unexpected message type"); };}/*switch*/;
   }/*IPC_Do_Msg*/

/*client*/ /*notice*/
Add_BuildArg(FileName)
   /*in*/ /*str*/ tp_FileName FileName;
{
   Local_Add_BuildArg(FileName);}


/*client*/ /*notice*/
Do_Build(JobID, JobDirName, LogFileName)
   /*in*/ /*int*/ tp_JobID JobID;
   /*in*/ /*str*/ tp_FileName JobDirName;
   /*in*/ /*str*/ tp_FileName LogFileName;
{
   Local_Do_Build(JobID, JobDirName, LogFileName);}


/*client*/ /*notice*/
Abort_Build(JobID)
   /*in*/ /*int*/ tp_JobID JobID;
{
   Local_Abort_Build(JobID);}


/*client*/ /*notice*/
Do_MakeReadOnly(FileName)
   /*in*/ /*str*/ tp_FileName FileName;
{
   Local_Do_MakeReadOnly(FileName);}


/*client*/ /*notice*/
ErrMessage(Message)
   /*in*/ /*str*/ char *Message;
{
   Local_ErrMessage(Message);}


/*client*/ /*notice*/
LogMessage(Message)
   /*in*/ /*str*/ char *Message;
{
   Local_LogMessage(Message);}


/*client*/ /*notice*/
FileErrMessage(FileName)
   /*in*/ /*str*/ tp_FileName FileName;
{
   Local_FileErrMessage(FileName);}


/*client*/ /*notice*/
Next_OdinFile(OdinExpr, ID)
   /*in*/ /*str*/ tp_Str OdinExpr;
   /*in*/ /*int*/ int ID;
{
   Local_Next_OdinFile(OdinExpr, ID);}


/*server*/ /*request*/
Get_UseCount(CountPtr)
   /*out*/ /*int*/ int *CountPtr;
{
   Local_Get_UseCount(CountPtr);}


/*server*/ /*request*/
Get_CurSize(SizePtr)
   /*out*/ /*int*/ int *SizePtr;
{
   Local_Get_CurSize(SizePtr);}


/*server*/ /*notice*/
ShutDown()
{
   Local_ShutDown();}


/*server*/ /*request*/
Get_Banner(Str)
   /*out*/ /*str*/ tp_Str Str;
{
   Local_Get_Banner(Str);}


/*server*/ /*notice*/
Do_Interrupt(InterruptFlag)
   /*in*/ /*int*/ boolean InterruptFlag;
{
   Local_Do_Interrupt(InterruptFlag);}


/*server*/ /*notice*/
Do_Alias(FileName, ForceFlag)
   /*in*/ /*str*/ tp_FileName FileName;
   /*in*/ /*int*/ boolean ForceFlag;
{
   Local_Do_Alias(FileName, ForceFlag);}


/*server*/ /*request*/
Get_Alias(OutFileName, FileName)
   /*out*/ /*str*/ tp_FileName OutFileName;
   /*in*/ /*str*/ tp_FileName FileName;
{
   Local_Get_Alias(OutFileName, FileName);}


/*server*/ /*notice*/
Job_Done(JobID, Abort)
   /*in*/ /*int*/ tp_JobID JobID;
   /*in*/ /*int*/ boolean Abort;
{
   Local_Job_Done(JobID, Abort);}


/*server*/ /*request*/
Test(FileName)
   /*in*/ /*str*/ tp_FileName FileName;
{
   Local_Test(FileName);}


/*server*/ /*request*/
Test_All()
{
   Local_Test_All();}


/*server*/ /*split-request*/
Get_OdinFile(FileName, StatusPtr, ExecFlagPtr, OdinExpr, NeedsData)
   /*out*/ /*str*/ tp_FileName FileName;
   /*out*/ /*int*/ tp_Status *StatusPtr;
   /*out*/ /*int*/ boolean *ExecFlagPtr;
   /*in*/ /*str*/ tp_Str OdinExpr;
   /*in*/ /*int*/ boolean NeedsData;
{
   Local_Get_OdinFile(FileName, StatusPtr, ExecFlagPtr, OdinExpr, NeedsData);}


/*server*/ /*request*/
Set_CWD(FileName)
   /*in*/ /*str*/ tp_FileName FileName;
{
   Local_Set_CWD(FileName);}


/*server*/ /*request*/
Push_Context(DirName, FileName)
   /*out*/ /*str*/ tp_FileName DirName;
   /*in*/ /*str*/ tp_FileName FileName;
{
   Local_Push_Context(DirName, FileName);}


/*server*/ /*request*/
Pop_Context(DirName)
   /*out*/ /*str*/ tp_FileName DirName;
{
   Local_Pop_Context(DirName);}


/*server*/ /*request*/
Set_KeepGoing(Flag)
   /*in*/ /*int*/ int Flag;
{
   Local_Set_KeepGoing(Flag);}


/*server*/ /*request*/
Set_ErrLevel(ErrLevel)
   /*in*/ /*int*/ int ErrLevel;
{
   Local_Set_ErrLevel(ErrLevel);}

/*server*/ /*request*/
Set_WarnLevel(WarnLevel)
   /*in*/ /*int*/ int WarnLevel;
{
   Local_Set_WarnLevel(WarnLevel);}

/*server*/ /*request*/
Set_LogLevel(LogLevel)
   /*in*/ /*int*/ tp_LogLevel LogLevel;
{
   Local_Set_LogLevel(LogLevel);}

/*server*/ /*request*/
Set_HelpLevel(HelpLevel)
   /*in*/ /*int*/ int HelpLevel;
{
   Local_Set_HelpLevel(HelpLevel);}


/*server*/ /*request*/
Set_Debug(DebugName)
   /*in*/ /*str*/ tp_Str DebugName;
{
   Local_Set_Debug(DebugName);}


/*server*/ /*request*/
Set_MaxJobs(MaxJobs)
   /*in*/ /*int*/ int MaxJobs;
{
   Local_Set_MaxJobs(MaxJobs);}


/*server*/ /*request*/
Redo(OdinExpr)
   /*in*/ /*str*/ tp_Str OdinExpr;
{
   Local_Redo(OdinExpr);}


/*server*/ /*request*/
OdinExpr_ID(IDPtr, OdinExpr)
   /*out*/ /*int*/ int *IDPtr;
   /*in*/ /*str*/ tp_Str OdinExpr;
{
   Local_OdinExpr_ID(IDPtr, OdinExpr);}


/*server*/ /*request*/
ID_OdinExpr(OdinExpr, ID)
   /*out*/ /*str*/ tp_Str OdinExpr;
   /*in*/ /*int*/ int ID;
{
   Local_ID_OdinExpr(OdinExpr, ID);}


/*server*/ /*request*/
ID_LongOdinExpr(OdinExpr, ID)
   /*out*/ /*str*/ tp_Str OdinExpr;
   /*in*/ /*int*/ int ID;
{
   Local_ID_LongOdinExpr(OdinExpr, ID);}


/*server*/ /*request*/
Get_Status(StatusPtr, ElmStatusPtr, ID)
   /*out*/ /*int*/ tp_Status *StatusPtr;
   /*out*/ /*int*/ tp_Status *ElmStatusPtr;
   /*in*/ /*int*/ int ID;
{
   Local_Get_Status(StatusPtr, ElmStatusPtr, ID);}


/*server*/ /*request*/
Get_Elements(ID)
   /*in*/ /*int*/ int ID;
{
   Local_Get_Elements(ID);}


/*server*/ /*request*/
Get_ElementsOf(ID)
   /*in*/ /*int*/ int ID;
{
   Local_Get_ElementsOf(ID);}


/*server*/ /*request*/
Get_Inputs(ID)
   /*in*/ /*int*/ int ID;
{
   Local_Get_Inputs(ID);}


/*server*/ /*request*/
Get_Outputs(ID)
   /*in*/ /*int*/ int ID;
{
   Local_Get_Outputs(ID);}


/*server*/ /*request*/
Get_DPath(OdinExpr)
   /*in*/ /*str*/ tp_Str OdinExpr;
{
   Local_Get_DPath(OdinExpr);}


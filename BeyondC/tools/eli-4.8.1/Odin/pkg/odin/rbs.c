/*	
Copyright (C) 1991 Geoffrey M. Clemm

This file is part of the Odin system.

The Odin system is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation (see the file COPYING).

The Odin system is distributed WITHOUT ANY WARRANTY, without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

geoff@boulder.colorado.edu
*/

#include "inc/GMC.h"
#include <fcntl.h>
#include "inc/sys_param.h"
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>

#include "inc/FileName.h"
#include "inc/Build.h"
#include "inc/Str.h"


extern char **environ;

tp_Str		Author = "odin-build-users@lists.sourceforge.net";

int SocketFD;

tp_Build FirstBuild = NIL;

#define		MAX_BUILDARGV 100
int		Num_BuildArgV = 0;
char		*BuildArgV[MAX_BUILDARGV];


void
Local_Add_BuildArg(
   GMC_ARG(tp_FileName, Arg)
   )
   GMC_DCL(tp_FileName, Arg)
{
   FORBIDDEN((Num_BuildArgV+2) > MAX_BUILDARGV);
   if (BuildArgV[Num_BuildArgV] != NIL) free(BuildArgV[Num_BuildArgV]);
   BuildArgV[Num_BuildArgV] = Malloc_Str(Arg);
   Num_BuildArgV += 1;
   }/*Local_Add_BuildArg*/


tp_Build
BuildID_Build(
   GMC_ARG(tp_BuildID, BuildID)
   )
   GMC_DCL(tp_BuildID, BuildID)
{
   tp_Build Build;

   for (Build=FirstBuild; Build!=NIL; Build=Build->Next) {
      if (BuildID == Build->BuildID) {
	 return Build; }/*if*/; }/*for*/;
   return NIL;
   }/*BuildID_Build*/


tp_Build
JobID_Build(
   GMC_ARG(tp_JobID, JobID)
   )
   GMC_DCL(tp_JobID, JobID)
{
   tp_Build Build;

   for (Build=FirstBuild; Build!=NIL; Build=Build->Next) {
      if (JobID == Build->JobID) {
	 return Build; }/*if*/; }/*for*/;
   return NIL;
   }/*JobID_Build*/


tp_Build
New_Build(GMC_ARG_VOID)
{
   tp_Build Build;

   Build = JobID_Build(0);
   if (Build == NIL) {
      Build = (tp_Build)malloc(sizeof(tps_Build));
      Build->JobID = 0;
      Build->BuildID = 0;
      Build->Next = FirstBuild;
      FirstBuild = Build; }/*if*/;
   return Build;
   }/*New_Build*/


static int
RBS_Read(
   GMC_ARG(int, fd),
   GMC_ARG(char*, buf),
   GMC_ARG(int, len)
   )
   GMC_DCL(int, fd)
   GMC_DCL(char*, buf)
   GMC_DCL(int, len)
{
   int n, i;

   for (i=0; i<len; i+=n) {
      n = read(fd, &buf[i], len-i);
      if (n <= 0) {
         return i; }/*if*/; }/*for*/;
   return i;
   }/*RBS_Read*/


static void
RBS_Write_Int(
   GMC_ARG(int, Int)
   )
   GMC_DCL(int, Int)
{
   int cc;

   cc = write(SocketFD, (char *)&Int, sizeof(Int));
   if (cc != sizeof(Int)) Exit(1);
   }/*RBS_Write_Int*/


static void
RBS_Read_Int(
   GMC_ARG(int*, IntPtr)
   )
   GMC_DCL(int*, IntPtr)
{
   int cc;

   cc = RBS_Read(SocketFD, (char *)IntPtr, sizeof(*IntPtr));
   if (cc != sizeof(*IntPtr)) Exit(1);
   }/*RBS_Read_Int*/


static void
RBS_Write_Str(
   GMC_ARG(const char*, Str)
   )
   GMC_DCL(char*, Str)
{
   int cc, len;

   len = strlen(Str);
   RBS_Write_Int(len);
   if (len > 0) {
      cc = write(SocketFD, Str, len);
      if (cc != len) Exit(1); }/*if*/;
   }/*RBS_Write_Str*/


static void
RBS_Read_Str(
   GMC_ARG(char*, Str)
   )
   GMC_DCL(char*, Str)
{
   int cc, len;

   RBS_Read_Int(&len);
   if (len > 0) {
      cc = RBS_Read(SocketFD, Str, len);
      if (cc != len) Exit(1); }/*if*/;
   Str[len] = 0;
   }/*RBS_Read_Str*/


void
RBS_Read_VarDef(GMC_ARG_VOID)
{
   tps_Str StrBuf;
   int status;

   RBS_Read_Str(StrBuf);
   status = putenv(Malloc_Str(StrBuf));
   FORBIDDEN(status != 0);
   }/*RBS_Read_VarDef*/


void
Set_ODINRBSHOST(GMC_ARG_VOID)
{
   int status;
   char LocalHostName[MAXHOSTNAMELEN];
   tps_Str EnvStr;

   status = gethostname(LocalHostName, MAXHOSTNAMELEN);
   FORBIDDEN(status != 0);
   (void)sprintf(EnvStr, "ODINRBSHOST=%s: ", LocalHostName);
   (void)putenv(strdup(EnvStr));
   }/*Set_ODINRBSHOST*/


int
main(
   GMC_ARG(int, argc),
   GMC_ARG(char**, argv)
   )
   GMC_DCL(int, argc)
   GMC_DCL(char**, argv)
{
#ifndef BSD_SIGNALS
   struct sigaction actbuf;
#endif
   tp_Str HostName, PortStr;
   struct sockaddr_in InSockAddr;
   struct sockaddr *SockAddrPtr = (struct sockaddr *)&InSockAddr;
   struct hostent *HostEnt;
   int i, status, MsgType, BuildID, JobID;
   boolean Abort;
   fd_set _readfds, *readfds = &_readfds;
   int fd, pid, nfds;
   struct timeval _Timeout, *Timeout;
   tps_FileName JobDirName, LogFileName, Arg;
   tp_Build Build;

   FORBIDDEN(argc != 3);
   Init_IO();
   Init_Err();
   Init_Sigs(FALSE);

   Unblock_Signals();
   HostName = argv[1];
   PortStr = argv[2];
#ifdef BSD_SIGNALS
   (void)signal(SIGPIPE, SIG_IGN);
#else
   actbuf.sa_handler = SIG_IGN;
   status = sigemptyset(&actbuf.sa_mask);
   FORBIDDEN(status != 0);
   actbuf.sa_flags = 0;
   status = sigaction(SIGPIPE, &actbuf, (struct sigaction *)NULL);
   FORBIDDEN(status != 0);
#endif
   SocketFD = socket(AF_INET, SOCK_STREAM, 0);
   FORBIDDEN(SocketFD < 0);
   for (i=0; i<sizeof(InSockAddr); i+=1) {
      ((char *)&InSockAddr)[i] = '\0'; }/*for*/;
   InSockAddr.sin_family = AF_INET;
   HostEnt = gethostbyname(HostName);
   for (i=0; i<HostEnt->h_length; i+=1) {
      ((char *)&InSockAddr.sin_addr)[i] = HostEnt->h_addr[i]; }/*for*/;
   InSockAddr.sin_port = atoi(PortStr);

   Lose_ControlTTY();
   fd = open("/dev/null", O_RDONLY);
   status = dup2(fd, 0);
   FORBIDDEN(status != 0);

   Set_ODINRBSHOST();

   status = connect(SocketFD, SockAddrPtr, sizeof(InSockAddr));
   FORBIDDEN(status != 0);
   while (TRUE) {
      FD_SET(SocketFD, readfds);
      nfds = Await_Event(readfds, FALSE);
      if (nfds < 0) FD_ZERO(readfds);
      if (SigChild) {
	 SigChild = FALSE;
	 for (SystemWait(&BuildID, &Abort);
	      BuildID != 0;
	      SystemWait(&BuildID, &Abort)) {
	    Build = BuildID_Build(BuildID);
	    FORBIDDEN(Build == NIL);
	    RBS_Write_Int(Build->JobID);
	    RBS_Write_Int(Abort);
	    Build->BuildID = 0;
	    Build->JobID = 0; }/*while*/; }/*if*/;
      if (FD_ISSET(SocketFD, readfds)) {
	 RBS_Read_Int(&MsgType);
	 switch (MsgType) {
	    case 1: {
	       RBS_Read_Int(&JobID);
	       RBS_Read_Str(JobDirName);
	       RBS_Read_Str(LogFileName);
	       break;}/*case*/;
	    case 2: {
	       RBS_Read_Str(Arg);
	       Local_Add_BuildArg(Arg);
	       break;}/*case*/;
	    case 3: {
	       if (BuildArgV[Num_BuildArgV] != NIL) {
		  free(BuildArgV[Num_BuildArgV]); }/*if*/;
	       BuildArgV[Num_BuildArgV] = 0;
	       Num_BuildArgV = 0;
	       Build = New_Build();
	       Build->JobID = JobID;
	       ChangeDir(&Abort, JobDirName);
	       if (Abort) {
		  SystemError("Cannot find %s on remote machine.\n",
			      JobDirName);
		  SystemError("Trying agin.\n");
		  sleep(5);
		  ChangeDir(&Abort, JobDirName); 
		  if (Abort) {
		     SystemError("Giving up.\n");
		     Exit(1); }/*if*/; }/*if*/;
	       ClearDir(JobDirName);
	       Build->BuildID = SystemExec(BuildArgV[0], BuildArgV, LogFileName);
	       break;}/*case*/;
	    case 4: {
	       RBS_Read_Int(&JobID);
	       Build = JobID_Build(JobID);
	       if (Build != NIL) {
		  SystemInterrupt(Build->BuildID); }/*if*/;  break;}/*case*/;
	    case 5: {
	       RBS_Read_VarDef(); break;}/*case*/;
	    default: {
	       FATALERROR("unexpected message type.\n");
	       };}/*switch*/; }/*if*/; }/*while*/;
   return 0;
   }/*main*/


void
Exit(
   GMC_ARG(int, Status)
   )
   GMC_DCL(int, Status)
{
   tp_Build Build;

   for (Build=FirstBuild; Build!=NIL; Build=Build->Next) {
      if (Build->BuildID != 0) {
	 SystemInterrupt(Build->BuildID); }/*if*/; }/*for*/;
   exit(Status);
   }/*Exit*/


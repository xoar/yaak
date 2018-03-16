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

#include "inc/System.hh"
#include "inc/sys_param.h"
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>

#include "inc/GMC.h"
#include "inc/Host.h"
#include "inc/LogLevel_.h"
#include "inc/Str.h"

tp_Host		FirstHost = NIL;

static int RBS_SocketFD = -1;
static int RBS_Port = -1;


static void
Init_RBS(GMC_ARG_VOID)
{
   struct sockaddr_in InSockAddr;
   struct sockaddr *SockAddrPtr = (struct sockaddr *)&InSockAddr;
   int i, status;
   socklen_t len;

   FORBIDDEN(RBS_SocketFD >= 0);
   RBS_SocketFD = socket(AF_INET, SOCK_STREAM, 0);
   FORBIDDEN(RBS_SocketFD < 0);
   for (i=0; i<sizeof(InSockAddr); i+=1) {
      ((char *)&InSockAddr)[i] = '\0'; }/*for*/;
   InSockAddr.sin_family = AF_INET;
   status = bind(RBS_SocketFD, SockAddrPtr, sizeof(InSockAddr));
   FORBIDDEN(status != 0);
   len = sizeof(InSockAddr);
   status = getsockname(RBS_SocketFD, SockAddrPtr, &len);
   FORBIDDEN(status != 0);
   RBS_Port = InSockAddr.sin_port;
   FORBIDDEN(RBS_Port <= 0);
   status = listen(RBS_SocketFD, 7);	/* because 7 is a lucky number */
   FORBIDDEN(status != 0);
   }/*Init_RBS*/


tp_Str
Host_HostName(
   GMC_ARG(tp_Host, Host)
   )
   GMC_DCL(tp_Host, Host)
{
   return Host->HostName;
   }/*Host_HostName*/


int
Host_FD(
   GMC_ARG(tp_Host, Host)
   )
   GMC_DCL(tp_Host, Host)
{
   return Host->FD;
   }/*Host_FD*/


tp_Host
Host_Next(
   GMC_ARG(tp_Host, Host)
   )
   GMC_DCL(tp_Host, Host)
{
   return Host->Next;
   }/*Host_Next*/


tp_Host
Lookup_Host(
   GMC_ARG(tp_Str, HostName)
   )
   GMC_DCL(tp_Str, HostName)
{
   tp_Host Host;

   if (strcmp(HostName, "LOCAL") == 0) {
      return NIL; }/*if*/;
   for (Host=FirstHost; Host!=NIL; Host=Host->Next) {
      if (HostName == Host->HostName) {
	 return Host; }/*if*/; }/*for*/;
   Host = (tp_Host)malloc(sizeof(tps_Host));
   Host->HostName = HostName;
   Host->FD = -1;
   Host->Next = FirstHost;
   FirstHost = Host;
   return Host;
   }/*Lookup_Host*/


tp_Host
PId_Host(
   GMC_ARG(int, PId)
   )
   GMC_DCL(int, PId)
{
   tp_Host Host;

   for (Host=FirstHost; Host!=NIL; Host=Host->Next) {
      if (Host->RBS_Id == PId) {
	 return Host; }/*if*/; }/*for*/;
   return NIL;
   }/*PId_Host*/


static void
RBS_Close(
   GMC_ARG(tp_Host, Host)
   )
   GMC_DCL(tp_Host, Host)
{
   if (Host->FD < 0) {
      return; }/*if*/;
   Cancel_Builds(Host);
   (void)close(Host->FD);
   Host->FD = -1;
   }/*RBS_Close*/


void
RBS_Done(
   GMC_ARG(tp_Host, Host)
   )
   GMC_DCL(tp_Host, Host)
{
   if (Host->RBS_Id < 0) {
      return; }/*if*/;
   RBS_Close(Host);
   Host->RBS_Id = -1;
   SystemError("Remote build server on %s died.  Will try to restart.\n",
	       Host->HostName);
   }/*RBS_Done*/


static void
RBS_Write_Int(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Host, Host),
   GMC_ARG(int, Int)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Host, Host)
   GMC_DCL(int, Int)
{
   int cc;

   if (Host->FD < 0) {
      *AbortPtr = TRUE;
      return; }/*if*/;
   cc = write(Host->FD, (char *)&Int, sizeof(Int));
   *AbortPtr = (cc != sizeof(Int));
   if (*AbortPtr) {
      RBS_Close(Host); }/*if*/;
   }/*RBS_Write_Int*/


static void
RBS_Read_Int(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Host, Host),
   GMC_ARG(int*, IntPtr)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Host, Host)
   GMC_DCL(int*, IntPtr)
{
   int cc;

   if (Host->FD < 0) {
      *AbortPtr = TRUE;
      return; }/*if*/;
   cc = IPC_Read(Host->FD, (char *)IntPtr, sizeof(*IntPtr));
   *AbortPtr = (cc != sizeof(*IntPtr));
   if (*AbortPtr) {
      RBS_Close(Host); }/*if*/;
   }/*RBS_Read_Int*/


static void
RBS_Write_Str(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Host, Host),
   GMC_ARG(const char*, Str)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Host, Host)
   GMC_DCL(char*, Str)
{
   int cc, len;

   len = strlen(Str);
   RBS_Write_Int(AbortPtr, Host, len);
   if (*AbortPtr) {
      return; }/*if*/;
   if (len > 0) {
      cc = write(Host->FD, Str, len);
      *AbortPtr = (cc != len);
      if (*AbortPtr) {
	 RBS_Close(Host); }/*if*/; }/*if*/;
   }/*RBS_Write_Str*/


static void
RBS_Read_Str(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Host, Host),
   GMC_ARG(char*, Str)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Host, Host)
   GMC_DCL(char*, Str)
{
   int cc, len;

   RBS_Read_Int(AbortPtr, Host, &len);
   if (*AbortPtr) {
      return; }/*if*/;
   if (len > 0) {
      cc = IPC_Read(Host->FD, Str, len);
      *AbortPtr = (cc != len);
      if (*AbortPtr) {
	 RBS_Close(Host); }/*if*/; }/*if*/;
   Str[len] = 0;
   }/*RBS_Read_Str*/


void
RBS_Get_Msg(
   GMC_ARG(tp_Host, Host)
   )
   GMC_DCL(tp_Host, Host)
{
   boolean RBS_Abort, Abort;
   int JobID;

   RBS_Read_Int(&RBS_Abort, Host, &JobID);
   if (RBS_Abort) return;
   RBS_Read_Int(&RBS_Abort, Host, &Abort);
   if (RBS_Abort) return;
   Build_Done(JobID_Build(JobID), Abort);
   }/*RBS_Get_Msg*/


static void
RBS_Write_VarDef(
   GMC_ARG(boolean*, RBS_AbortPtr),
   GMC_ARG(tp_Host, Host),
   GMC_ARG(tp_Str, VarDef)
   )
   GMC_DCL(boolean*, RBS_AbortPtr)
   GMC_DCL(tp_Host, Host)
   GMC_DCL(tp_Str, VarDef)
{
   RBS_Write_Int(RBS_AbortPtr, Host, (int)5);
   if (*RBS_AbortPtr) return;
   RBS_Write_Str(RBS_AbortPtr, Host, VarDef);
   }/*RBS_Write_VarDef*/


static void
Init_RBS_Env(
   GMC_ARG(tp_Host, Host)
   )
   GMC_DCL(tp_Host, Host)
{
   extern char **environ;
   char **env;
   boolean Abort;

   for (env = environ; *env != 0; env += 1) {
      RBS_Write_VarDef(&Abort, Host, *env);
      if (Abort) {
	 return; }/*if*/; }/*for*/;
   }/*Init_RBS_Env*/


void
RBS_Do_Build(
   GMC_ARG(tp_Host, Host),
   GMC_ARG(int, JobID),
   GMC_ARG(tp_FileName, JobDirName),
   GMC_ARG(tp_FileName, LogFileName),
   GMC_ARG(char**, ArgV)
   )
   GMC_DCL(tp_Host, Host)
   GMC_DCL(int, JobID)
   GMC_DCL(tp_FileName, JobDirName)
   GMC_DCL(tp_FileName, LogFileName)
   GMC_DCL(char**, ArgV)
{
   int status, i;
   socklen_t AddrLen;
   char * RBS_ArgV[6];
   tps_Str RBS_CmdPath, PortStr;
   char LocalHostName[MAXHOSTNAMELEN];
   struct sockaddr Addr;
   boolean RBS_Abort;

   if (RBS_Port < 0) Init_RBS();
   if (Host->FD < 0) {
      status = gethostname(LocalHostName, MAXHOSTNAMELEN);
      FORBIDDEN(status != 0);
      (void)sprintf(RBS_CmdPath, "%s/PKGS/%s", OdinDirName, RBS_Cmd);
      (void)sprintf(PortStr, "%d", RBS_Port);
      RBS_ArgV[0] = RBS_Cmd;
      RBS_ArgV[1] = Host->HostName;
      RBS_ArgV[2] = OdinDirName;
      RBS_ArgV[3] = LocalHostName;
      RBS_ArgV[4] = PortStr;
      RBS_ArgV[5] = 0;
      Host->RBS_Id = SystemExec(RBS_CmdPath, RBS_ArgV, (tp_Str)NIL);
      if (Host->RBS_Id <= 0) {
	 SystemError("Could not start remote build server: %s.\n", RBS_CmdPath);
	 Exit(1); }/*if*/;
      AddrLen = sizeof(Addr);
      Unblock_Signals();
      while (Host->FD < 0 && !Signalled) {
	 sleep(1);
	 Host->FD = accept(RBS_SocketFD, &Addr, &AddrLen); }/*while*/;
      Block_Signals();
      if (Host->FD < 0) {
	 SystemError("Remote build server not responding: %s.\n", RBS_CmdPath);
	 Exit(1); }/*if*/;
      Init_RBS_Env(Host); }/*if*/;
   RBS_Write_Int(&RBS_Abort, Host, (int)1);
   if (RBS_Abort) return;
   RBS_Write_Int(&RBS_Abort, Host, JobID);
   if (RBS_Abort) return;
   RBS_Write_Str(&RBS_Abort, Host, JobDirName);
   if (RBS_Abort) return;
   RBS_Write_Str(&RBS_Abort, Host, LogFileName);
   if (RBS_Abort) return;
   for (i = 0; ArgV[i] != NIL; i+=1) {
      RBS_Write_Int(&RBS_Abort, Host, (int)2);
      if (RBS_Abort) return;
      RBS_Write_Str(&RBS_Abort, Host, ArgV[i]);
      if (RBS_Abort) return;
      }/*for*/;
   RBS_Write_Int(&RBS_Abort, Host, (int)3);
   if (RBS_Abort) return;
   }/*RBS_Do_Build*/


void
RBS_Abort_Build(
   GMC_ARG(tp_Host, Host),
   GMC_ARG(int, JobID)
   )
   GMC_DCL(tp_Host, Host)
   GMC_DCL(int, JobID)
{
   boolean RBS_Abort;

   RBS_Write_Int(&RBS_Abort, Host, (int)4);
   if (RBS_Abort) return;
   RBS_Write_Int(&RBS_Abort, Host, JobID);
   }/*RBS_Abort_Build*/


void
RBS_VarDef(
   GMC_ARG(tp_Str, VarDef)
   )
   GMC_DCL(tp_Str, VarDef)
{
   tp_Host Host;
   boolean RBS_Abort;

   for (Host=FirstHost; Host!=NIL; Host=Host->Next) {
      if (Host->FD > 0) {
	 RBS_Write_VarDef(&RBS_Abort, Host, VarDef); }/*if*/; }/*for*/;
   }/*RBS_VarDef*/


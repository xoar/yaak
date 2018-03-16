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
#include <errno.h>
#include <string.h>
#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#include "inc/GMC.h"
#include "inc/Str.h"

extern char *strerror(GMC_P1(int));

extern tp_Str		Author;


int			num_Errors = 0;

boolean			DumpCore;

boolean			Is_IPC_Err = FALSE;

static tp_FilDsc		ErrFD;
static tp_FileName	ErrFileName;


void
Init_Err(GMC_ARG_VOID)
{
   ErrFileName = NIL;
   ErrFD = StdErrFD;
   Reset_Err();
   }/*Init_Err*/


void
Set_IPC_Err(
   GMC_ARG(boolean, Flag)
   )
   GMC_DCL(boolean, Flag)
{
   Is_IPC_Err = Flag;
   }/*Set_IPC_Err*/


void
Set_ErrFile(
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(boolean, IsIPC),
   GMC_ARG(tp_FilDsc, FilDsc)
   )
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(boolean, IsIPC)
   GMC_DCL(tp_FilDsc, FilDsc)
{
   FORBIDDEN(FileName != NIL && IsIPC);
   if (FileName == ErrFileName && IsIPC == Is_IPC_Err && FilDsc == ErrFD) {
      return; }/*if*/;
   if (ErrFD != NIL && ErrFD != StdOutFD && ErrFD != StdErrFD) Close(ErrFD);
   ErrFileName = FileName;
   Is_IPC_Err = IsIPC;
   ErrFD = FilDsc;
   }/*Set_ErrFile*/


void
Save_ErrFile(
   GMC_ARG(tp_FileName*, FileNamePtr),
   GMC_ARG(boolean*, IsIPC_Ptr),
   GMC_ARG(tp_FilDsc*, FilDscPtr)
   )
   GMC_DCL(tp_FileName*, FileNamePtr)
   GMC_DCL(boolean*, IsIPC_Ptr)
   GMC_DCL(tp_FilDsc*, FilDscPtr)
{
   *FileNamePtr = ErrFileName;
   *IsIPC_Ptr = Is_IPC_Err;
   *FilDscPtr = ErrFD;
   }/*Save_ErrFile*/


boolean
IsErr(GMC_ARG_VOID)
{
   FORBIDDEN(ErrFD == StdOutFD || ErrFD == StdErrFD);
   return (ErrFD != NIL);
   }/*IsErr*/


void
Reset_Err(GMC_ARG_VOID)
{
   num_Errors = 0;
   }/*Reset_Err*/


void
Increment_Errors(GMC_ARG_VOID)
{
   num_Errors += 1;
   }/*Increment_Errors*/


int
Num_Errors(GMC_ARG_VOID)
{
   return num_Errors;
   }/*Num_Errors*/


#if NO_STRERROR
extern char *sys_errlist[];
char *strerror(
   GMC_ARG(int, num)
   )
   GMC_DCL(int, num)
{ return sys_errlist[num]; }
#endif


void
SysCallError(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(char*, Message)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(char*, Message)
{
   (void)fprintf((FILE *)FilDsc, "%s: %s.\n", Message, strerror(errno));
   (void)fflush((FILE *)FilDsc);
   }/*SysCallError*/


void
FatalError(
   GMC_ARG(char*, Message),
   GMC_ARG(char*, FileName),
   GMC_ARG(int, LineNum)
   )
   GMC_DCL(char*, Message)
   GMC_DCL(char*, FileName)
   GMC_DCL(int, LineNum)
{
   tps_Str Msg;

   (void)sprintf(Msg, "\"%s\", line %d: %s", FileName, LineNum, Message);
   fatal_err(Msg);
   }/*FatalError*/


#ifdef __STDC__

void
SystemError(char * Fmt, ...)
/*VARARGS 1*/
{
   va_list Args;
   tps_Str Message;

   va_start(Args,Fmt);
   Increment_Errors ();
   (void)vsprintf(Message, Fmt, Args);
   /*select*/{
      if (Is_IPC_Err) {
	 ErrMessage(Message);
      }else{
	 Local_ErrMessage(Message); };}/*select*/;
   va_end(Args);
   }/*SystemError*/

#else

void SystemError(va_alist)
/*VARARGS 1*/
   va_dcl
{
   va_list Args;
   tp_Str Fmt;
   tps_Str Message;

   va_start(Args);
   Fmt = va_arg(Args, char *);
   Increment_Errors ();
   (void)vsprintf(Message, Fmt, Args);
   /*select*/{
      if (Is_IPC_Err) {
	 ErrMessage(Message);
      }else{
	 Local_ErrMessage(Message); };}/*select*/;
   va_end(Args);
   }/*SystemError*/

#endif


#ifdef NO_IPC
void
ErrMessage(
   GMC_ARG(tp_Str, Message)
   )
   GMC_DCL(tp_Str, Message)
{
   Local_ErrMessage(Message);
   }/*ErrMessage*/
#endif


void
Local_ErrMessage(
   GMC_ARG(tp_Str, Message)
   )
   GMC_DCL(tp_Str, Message)
{
   int status;

   if (ErrFD == NIL) {
      FORBIDDEN(ErrFileName == NIL);
      ErrFD = FileName_WFilDsc(ErrFileName, FALSE);
      if (ErrFD == ERROR) {
	 status = fputs("!! Could not open error file !!", (FILE *)StdErrFD);
	 if (status == EOF) SysCallError(StdOutFD, "fputs(Local_ErrMessage)");
	 ErrFD = StdErrFD; }/*if*/; }/*if*/;
   status = fputs(Message, (FILE *)ErrFD);
   if (status == EOF) SysCallError(StdOutFD, "fputs(Local_ErrMessage)");
   (void)fflush((FILE *)ErrFD);
   }/*Local_ErrMessage*/


void
fatal_err(
   GMC_ARG(char*, Message)
   )
   GMC_DCL(char*, Message)
{
   (void)fprintf(stderr, "%s\n", Message);
   (void)fprintf(stderr, "Anomalous Internal State Detected\n");
   (void)fprintf(stderr, "please mail description to %s\n", Author);
   if (DumpCore) {
      (void)fprintf(stderr,
	"'illegal instruction' issued to generate core for analysis\n");
      abort(); }/*if*/;
   exit(1);
   }/*fatal_err*/



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
/* fcntl.h used for open */
#include <fcntl.h>

#include "inc/GMC.h"
#include "inc/Str.h"


tp_FilDsc	StdInFD;
tp_FilDsc	StdOutFD;
tp_FilDsc	StdErrFD;


void
Init_IO(GMC_ARG_VOID)
{
   StdInFD = (tp_FilDsc)stdin;
   StdOutFD = (tp_FilDsc)stdout;
   StdErrFD = (tp_FilDsc)stderr;
   }/*Init_IO*/


boolean
GetIsTTY(GMC_ARG_VOID)
{
   return (isatty(0) == 1);
   }/*GetIsTTY*/


tp_FilDsc
FileName_CFilDsc(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   int fd;
   FILE * FilDscFILE;

   if (FileName == ERROR) return ERROR;
   fd = open(FileName, O_CREAT|O_WRONLY|O_EXCL, 0644);
   if (fd < 0) {
      return ERROR; }/*if*/;
   FilDscFILE = fdopen(fd, "w");
   if (FilDscFILE == NULL) {
      return ERROR; }/*if*/;
   return (tp_FilDsc)FilDscFILE;
   }/*FileName_CFilDsc*/


tp_FilDsc
FileName_FilDsc(
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(char *, Mode),
   GMC_ARG(boolean, RetryFlag)
   )
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(char *, Mode)
   GMC_DCL(boolean, RetryFlag)
{
   FILE * FilDscFILE;

   if (FileName == ERROR) return ERROR;
   FilDscFILE = fopen(FileName, Mode);
   if (FilDscFILE == NULL) {
      if (!RetryFlag) {
	 return ERROR; }/*if*/;
      if (Mode[0] == 'w') {
	 if (Exists(FileName)) {
	    Remove(FileName);
	    FilDscFILE = fopen(FileName, Mode);
	    if (FilDscFILE != NULL) {
	       return (tp_FilDsc)FilDscFILE; }/*if*/; }/*if*/; }/*if*/;
      SysCallError(StdOutFD, "Retrying fopen(FileName_FilDsc)");
      while (FilDscFILE == NULL) {
	 sleep(1);
	 FilDscFILE = fopen(FileName, Mode); }/*while*/;
      Writeln(StdOutFD, "fopen(FileName_FilDsc) succeded."); }/*if*/;
   return (tp_FilDsc)FilDscFILE;
   }/*FileName_FilDsc*/


tp_FilDsc
FileName_WFilDsc(
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(boolean, RetryFlag)
   )
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(boolean, RetryFlag)
{
   return FileName_FilDsc(FileName, "w", RetryFlag);
   }/*FileName_WFilDsc*/


tp_FilDsc
FileName_WBFilDsc(
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(boolean, RetryFlag)
   )
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(boolean, RetryFlag)
{
   return FileName_FilDsc(FileName, "wb", RetryFlag);
   }/*FileName_WBFilDsc*/


tp_FilDsc
FileName_AFilDsc(
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(boolean, RetryFlag)
   )
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(boolean, RetryFlag)
{
   return FileName_FilDsc(FileName, "a", RetryFlag);
   }/*FileName_AFilDsc*/


tp_FilDsc
FileName_RFilDsc(
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(boolean, RetryFlag)
   )
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(boolean, RetryFlag)
{
   return FileName_FilDsc(FileName, "r", RetryFlag);
   }/*FileName_RFilDsc*/


tp_FilDsc
FileName_RWFilDsc(
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(boolean, RetryFlag)
   )
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(boolean, RetryFlag)
{
   return FileName_FilDsc
    (FileName, (Exists(FileName) ? "r+" : "w+"), RetryFlag);
   }/*FileName_RWFilDsc*/


tp_FilDsc
FileName_RWBFilDsc(
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(boolean, RetryFlag)
   )
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(boolean, RetryFlag)
{
   return FileName_FilDsc
    (FileName, (Exists(FileName) ? "r+b" : "w+b"), RetryFlag);
   }/*FileName_RWBFilDsc*/


void
Flush(
   GMC_ARG(tp_FilDsc, FilDsc)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
{
   int status;

   status = fflush((FILE *)FilDsc);
   if (status == EOF) SysCallError(StdOutFD, "fflush(Flush)");
   }/*Flush*/


void
Rewind(
   GMC_ARG(tp_FilDsc, FilDsc)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
{
   FORBIDDEN(FilDsc == ERROR);
   rewind((FILE *)FilDsc);
   }/*Rewind*/


void
Unwind(
   GMC_ARG(tp_FilDsc, FilDsc)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
{
   int status;

   FORBIDDEN(FilDsc == ERROR);
   status = fseek((FILE *)FilDsc, (long)0, 2);
   if (status == -1) SysCallError(StdOutFD, "fseek(Unwind)");
   }/*Unwind*/


void
Close(
   GMC_ARG(tp_FilDsc, FilDsc)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
{
   int status;

   FORBIDDEN(FilDsc == ERROR);
   status = fclose((FILE *)FilDsc);
   if (status == EOF) SysCallError(StdOutFD, "fclose(Close)");
   }/*Close*/


boolean
EndOfFile(
   GMC_ARG(tp_FilDsc, FilDsc)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
{
   FORBIDDEN(FilDsc == ERROR);
   return feof((FILE *)FilDsc);
   }/*EndOfFile*/


void
Write(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(tp_Str, Str)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_Str, Str)
{
   int status;

   FORBIDDEN(FilDsc == ERROR || Str == ERROR);
   status = fputs(Str, (FILE *)FilDsc);
   if (status == EOF) SysCallError(StdOutFD, "fputs(Write)");
   }/*Write*/


void
Writech(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(char, ch)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(char, ch)
{
   int status;

   FORBIDDEN(FilDsc == ERROR);
   status = putc(ch, (FILE *)FilDsc);
   if (status == EOF) SysCallError(StdOutFD, "putc(Writech)");
   }/*Writech*/


void
WriteInt(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(int, Int)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(int, Int)
{
   int status;

   FORBIDDEN(FilDsc == ERROR);
   status = fprintf((FILE *)FilDsc, "%d", Int);
   if (status == EOF) SysCallError(StdOutFD, "fprintf(WriteInt)");
   }/*WriteInt*/


void
Writeln(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(const char*, Str)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_Str, Str)
{
   int status;

   FORBIDDEN(FilDsc == ERROR || Str == ERROR);
   status = fputs(Str, (FILE *)FilDsc);
   if (status == EOF) SysCallError(StdOutFD, "fputs(Writeln)");
   status = putc('\n', (FILE *)FilDsc);
   if (status == EOF) SysCallError(StdOutFD, "putc(Writeln)");
   }/*Writeln*/


void
WriteLine(
   GMC_ARG(tp_FilDsc, FilDsc),
   GMC_ARG(tp_Str, Str)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
   GMC_DCL(tp_Str, Str)
{
   int status;
   tp_Str StrPtr;

   FORBIDDEN(FilDsc == ERROR || Str == ERROR);
   for (StrPtr = Str; *StrPtr != 0; StrPtr++) {
      if (*StrPtr == '\n') {
	 status = putc('\\', (FILE *)FilDsc);
	 if (status == EOF) SysCallError(StdOutFD, "putc(WriteLine)"); }/*if*/;
      status = putc(*StrPtr, (FILE *)FilDsc);
      if (status == EOF) SysCallError(StdOutFD, "putc(WriteLine)"); }/*for*/;
   status = putc('\n', (FILE *)FilDsc);
   if (status == EOF) SysCallError(StdOutFD, "putc(WriteLine)");
   }/*WriteLine*/


int
Readch(
   GMC_ARG(tp_FilDsc, FilDsc)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
{
   return getc((FILE *)FilDsc);
   }/*Readch*/


tp_Str
Readln(
   GMC_ARG(tp_Str, StrBuf),
   GMC_ARG(tp_FilDsc, FilDsc)
   )
   GMC_DCL(tp_Str, StrBuf)
   GMC_DCL(tp_FilDsc, FilDsc)
{
   tp_Str OutStr;
   int Length;

   if (FilDsc == ERROR) return ERROR;
   OutStr = fgets(StrBuf, MAX_Str, (FILE *)FilDsc);
   if (OutStr == NULL) {
      return ERROR; }/*if*/;
   Length = strlen(StrBuf);
   if (Length > 0 && StrBuf[Length-1] == '\n') {
      StrBuf[Length-1] = 0; }/*if*/;
   if (Length == (MAX_Str - 1)) {
      StrBuf[100] = 0;
      SystemError("Line too long, truncated:\n%s\n", StrBuf); }/*if*/;
   return StrBuf;
   }/*Readln*/


tp_Str
ReadLine(
   GMC_ARG(tp_Str, StrBuf),
   GMC_ARG(tp_FilDsc, FilDsc)
   )
   GMC_DCL(tp_Str, StrBuf)
   GMC_DCL(tp_FilDsc, FilDsc)
{
   tp_Str OutStr;
   int Length;

   if (FilDsc == ERROR) return ERROR;
   OutStr = fgets(StrBuf, MAX_Str, (FILE *)FilDsc);
   if (OutStr == NULL) {
      return ERROR; }/*if*/;
   Length = strlen(StrBuf);
   while (Length > 1 && Length < (MAX_Str - 1)
	  && StrBuf[Length-2] == '\\' && StrBuf[Length-1] == '\n') {
      StrBuf[Length-2] = '\n';
      OutStr = fgets(&StrBuf[Length-1], MAX_Str-Length, (FILE *)FilDsc);
      if (OutStr == NULL) {
	 return ERROR; }/*if*/;
      Length = strlen(StrBuf); }/*while*/;
   if (Length > 0 && StrBuf[Length-1] == '\n') {
      StrBuf[Length-1] = 0; }/*if*/;
   if (Length == (MAX_Str - 1)) {
      StrBuf[100] = 0;
      SystemError("Line too long, truncated:\n%s\n", StrBuf); }/*if*/;
   return StrBuf;
   }/*ReadLine*/


boolean
Equal(
   GMC_ARG(tp_FilDsc, FilDsc1),
   GMC_ARG(tp_FilDsc, FilDsc2)
   )
   GMC_DCL(tp_FilDsc, FilDsc1)
   GMC_DCL(tp_FilDsc, FilDsc2)
{
   int ichar1, ichar2;

   FORBIDDEN(FilDsc1 == ERROR || FilDsc2 == ERROR);
   ichar1 = getc((FILE *)FilDsc1);
   ichar2 = getc((FILE *)FilDsc2);
   while (ichar1 == ichar2 && ichar1 != EOF) {
      ichar1 = getc((FILE *)FilDsc1);
      ichar2 = getc((FILE *)FilDsc2); }/*while*/;
   return (ichar1 == ichar2);
   }/*Equal*/


void
FileCopy(
   GMC_ARG(tp_FilDsc, OutFD),
   GMC_ARG(tp_FilDsc, InFD)
   )
   GMC_DCL(tp_FilDsc, OutFD)
   GMC_DCL(tp_FilDsc, InFD)
{
   int ichar, status;

   FORBIDDEN(OutFD == ERROR || InFD == ERROR);
   ichar = getc((FILE *)InFD);
   while (ichar != EOF) {
      status = putc((char)ichar, (FILE *)OutFD);
      if (status == EOF) SysCallError(StdOutFD, "putc(FileCopy)");
      ichar = getc((FILE *)InFD); }/*while*/;
   }/*FileCopy*/


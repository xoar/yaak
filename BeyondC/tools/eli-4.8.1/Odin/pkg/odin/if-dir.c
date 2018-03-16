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
#ifdef HAVE_DIRENT_H
#include <dirent.h>
#else
#include <sys/types.h>
#include <sys/dir.h>
#endif

#include "inc/GMC.h"
#include "inc/FileName.h"
#include "inc/Str.h"


tp_FilDsc
OpenDir(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   tp_FilDsc FilDsc;

   FilDsc = (tp_FilDsc)opendir(FileName);
   if (FilDsc == NULL) {
      return ERROR; }/*if*/;
   return FilDsc;
   }/*OpenDir*/


void
CloseDir(
   GMC_ARG(tp_FilDsc, FilDsc)
   )
   GMC_DCL(tp_FilDsc, FilDsc)
{
#ifdef HAVE_DIRENT_H
   int status;
#endif

   FORBIDDEN(FilDsc == NIL);
#ifdef HAVE_DIRENT_H
   status = closedir((DIR *)FilDsc);
   if (status == -1) SysCallError(StdOutFD, "closedir(CloseDir)");
#else
   (void)closedir((DIR *)FilDsc);
#endif
   }/*CloseDir*/


void
ReadDir(
   GMC_ARG(tp_FileName, FileName),
   GMC_ARG(boolean*, EndPtr),
   GMC_ARG(tp_FilDsc, FilDsc)
   )
   GMC_DCL(tp_FileName, FileName)
   GMC_DCL(boolean*, EndPtr)
   GMC_DCL(tp_FilDsc, FilDsc)
{
#ifdef HAVE_DIRENT_H
   struct dirent *dp;
#else
   struct direct *dp;
#endif
   tps_Str Str;
   size_t sz;

   FORBIDDEN(FilDsc == NIL);
   *EndPtr = FALSE;
   dp = readdir((DIR *)FilDsc);
   if (dp == NULL) {
      *EndPtr = TRUE;
      return; }/*if*/;
#ifdef HAVE_DIRENT_H
   (void)strcpy(Str, dp->d_name);
#else
   (void)strncpy(Str, dp->d_name, (int)dp->d_namlen);
   Str[dp->d_namlen] = 0;
#endif
   sz = snprintf(FileName, MAX_FileName, "%s", Str);
   if (sz >= MAX_FileName) {
      (void)fprintf(stderr, "File name too long (MAX_FileName=%d): %s\n",
                  MAX_FileName, Str);
      exit(1); }/*if*/;
   if (strcmp(FileName, ".") == 0 || strcmp(FileName, "..") == 0) {
      ReadDir(FileName, EndPtr, FilDsc); }/*if*/;
   }/*ReadDir*/


void
ClearDir(
   GMC_ARG(tp_FileName, DirName)
   )
   GMC_DCL(tp_FileName, DirName)
{
   tp_FilDsc FilDsc;
   tps_Str Str;
   boolean End;
   tps_FileName FileName;
   size_t sz;

   FORBIDDEN(DirName == NIL);
   FilDsc = OpenDir(DirName);
   if (FilDsc == ERROR) {
      return; }/*if*/;
   for (ReadDir(Str, &End, FilDsc); !End; ReadDir(Str, &End, FilDsc)) {
      sz = snprintf(FileName, MAX_FileName, "%s/%s", DirName, Str);
      if (sz >= MAX_FileName) {
         (void)fprintf(stderr, "File name too long (MAX_FileName=%d): %s/%s\n",
	             MAX_FileName, DirName, Str);
	 exit(1); }/*if*/;
      Remove(FileName); }/*for*/;
   CloseDir(FilDsc);
   }/*ClearDir*/



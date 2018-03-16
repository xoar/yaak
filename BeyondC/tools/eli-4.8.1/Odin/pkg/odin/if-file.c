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
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>

#include "inc/GMC.h"
#include "inc/Str.h"
#include "inc/FileName.h"
#include "inc/SKind_.h"

static mode_t	ModeMask = 0777;


void
Set_ModeMask(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   int status;
   struct stat buf;

   FORBIDDEN(FileName == ERROR);
   status = stat(FileName, &buf);
   FORBIDDEN(status != 0);
   ModeMask = buf.st_mode;
   (void)umask(ModeMask ^ 0777);
   }/*Set_ModeMask*/


void
Get_FileInfo(
   GMC_ARG(tp_SKind*, SKindPtr),
   GMC_ARG(int*, SysModTimePtr),
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_SKind*, SKindPtr)
   GMC_DCL(int*, SysModTimePtr)
   GMC_DCL(tp_FileName, FileName)
{
   struct stat buf;
   int status;

   FORBIDDEN(FileName == ERROR);

   status = lstat(FileName, &buf);
   if (status != 0) {
      *SKindPtr = SK_NoFile;
      *SysModTimePtr = 0;
      return; }/*if*/;
   *SysModTimePtr = buf.st_mtime;
   /*select*/{
      if ((buf.st_mode & S_IFLNK) == S_IFLNK) {
	 *SKindPtr = SK_SymLink;
	 status = stat(FileName, &buf); /*give automounter a kick*/
      }else if ((buf.st_mode & S_IFDIR) == S_IFDIR) {
	 *SKindPtr = SK_Dir;
      }else if ((buf.st_mode & S_IEXEC) == S_IEXEC) {
	 *SKindPtr = SK_Exec;
      }else if ((buf.st_mode & S_IFREG) == S_IFREG) {
	 *SKindPtr = SK_Reg;
      }else{
	 *SKindPtr = SK_Special; };}/*select*/;
   }/*Get_FileInfo*/


void
MakePlnFile(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_FileName, FileName)
{
   int fd, status;

   *AbortPtr = TRUE;
   fd = open(FileName, O_WRONLY|O_CREAT|O_TRUNC, 0666);
   if (fd < 0) {
      return; }/*if*/;
   status = fchmod(fd, 0666 & ModeMask);
   if (status != 0) {
      (void)close(fd);
      return; }/*if*/;
   status = close(fd);
   if (status != 0) {
      (void)close(fd);
      return; }/*if*/;
   *AbortPtr = FALSE;
   }/*MakePlnFile*/


void
MakeDirFile(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_FileName, FileName)
{
   struct stat buf;
   int status;
   tps_FileName DirName;
   int i;

   FORBIDDEN(FileName == ERROR);

   *AbortPtr = FALSE;
   status = stat(FileName, &buf);
   if (status == 0) {
      FORBIDDEN((buf.st_mode & S_IFDIR) != S_IFDIR);
      return; }/*if*/;
   status = mkdir(FileName, (0777 & ModeMask));
   if (status != 0) {
      i = strlen(FileName) - 2;
      while (i > 0 && FileName[i] != '/') i -= 1;
      if (i < 1) {
	 SystemError("\"%s\": cannot create.\n", FileName);
	 *AbortPtr = TRUE;
	 return; }/*if*/;
      (void)strcpy(DirName, FileName);
      DirName[i] = 0;
      MakeDirFile(AbortPtr, DirName);
      if (*AbortPtr) {
	 return; }/*if*/;
      status = mkdir(FileName, (0777 & ModeMask));
      if (status != 0) {
	 SystemError("\"%s\": cannot create.\n", FileName);
	 *AbortPtr = TRUE;
	 return; }/*if*/; }/*if*/;
   }/*MakeDirFile*/


char *getcwd();

void
GetWorkingDir(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_Str, DirName)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_Str, DirName)
{
   char *WDstat;

   WDstat = getcwd(DirName, MAX_Str);
   *AbortPtr = (WDstat == 0);
   }/*GetWorkingDir*/


#ifndef HAVE_GETCWD
char *
getcwd(
   GMC_ARG(char*, buf),
   GMC_ARG(int, size)
   )
   GMC_DCL(char*, buf)
   GMC_DCL(int, size)
{
   char *result, *getwd();

   result = getwd(buf);
   FORBIDDEN(result != 0 && strlen(result) >= size);
   return result;
   }/*getcwd*/
#endif


void
ChangeDir(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_FileName, DirName)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_FileName, DirName)
{
   int status;

   status = chdir(DirName);
   *AbortPtr = (status != 0);
   }/*ChangeDir*/


boolean
IsExecutable(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   int status;
   struct stat buf;

   status = stat(FileName, &buf);
   return ((status == 0) && ((buf.st_mode & S_IEXEC) == S_IEXEC));
   }/*IsExecutable*/


void
MakeExecutable(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   int status;
   struct stat buf;
   int mode;

   FORBIDDEN(FileName == ERROR);
   status = stat(FileName, &buf);
   if (status == 0) {
      if ((buf.st_mode & S_IEXEC) != S_IEXEC) {
	 mode = ((buf.st_mode | 0111) & ModeMask);
	 status = chmod(FileName, mode); }/*if*/; }/*if*/;
   if (status != 0) {
      SystemError("\"%s\": cannot make executable.\n", FileName); }/*if*/;
   }/*MakeExecutable*/


void
MakeReadOnly(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_FileName, FileName)
{
   int status;
   struct stat buf;
   mode_t NewMode;

   FORBIDDEN(FileName == ERROR);
   status = stat(FileName, &buf);
   if (status != 0) {
      *AbortPtr = TRUE;
      return; }/*if*/;
   NewMode = ((buf.st_mode | 0444) & 0555 & ModeMask);
   if (NewMode == buf.st_mode) {
      *AbortPtr = FALSE;
      return; }/*if*/;
   status = chmod(FileName, NewMode);
   *AbortPtr = (status != 0);
   }/*MakeReadOnly*/


void
SymLink(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_FileName, ToFileName),
   GMC_ARG(tp_FileName, FromFileName)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_FileName, ToFileName)
   GMC_DCL(tp_FileName, FromFileName)
{
   int status;

   FORBIDDEN(ToFileName == ERROR || FromFileName == ERROR);
   *AbortPtr = FALSE;
   status = symlink(FromFileName, ToFileName);
   if (status != 0) {
      SysCallError(StdOutFD, "symlink");
      SystemError("\"%s\": Cannot make symbolic link to %s.\n", ToFileName, FromFileName);
      *AbortPtr = TRUE; }/*if*/;
   }/*SymLink*/


void
FileName_SymLinkFileName(
   GMC_ARG(tp_FileName, SymLinkFileName),
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, SymLinkFileName)
   GMC_DCL(tp_FileName, FileName)
{
   int cc;
   tps_Str buf;
   size_t sz;

   cc = readlink(FileName, buf, MAX_Str - 1);
   if (cc < 0) {
      perror("readlink");
      exit(1); }/*if*/;
   FORBIDDEN(cc == 0);
   buf[cc] = '\0';
   sz = snprintf(SymLinkFileName, MAX_FileName, "%s", buf);
   if (sz >= MAX_FileName) {
      (void)fprintf(stderr, "File name too long (MAX_FileName=%d): %s\n",
                  MAX_FileName, buf);
      exit(1); }/*if*/;
   }/*FileName_SymLinkFileName*/


boolean
IsDirectory_FileName(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   int status;
   struct stat buf;

   status = stat(FileName, &buf);
   return ((status == 0) && ((buf.st_mode & S_IFDIR) == S_IFDIR));
   }/*IsDirectory_FileName*/


boolean
Exists(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   int status;
   struct stat buf;

   FORBIDDEN(FileName == ERROR);
   status = stat(FileName, &buf);
   return (status == 0);
   }/*Exists*/


boolean
Empty(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   int status;
   struct stat buf;

   FORBIDDEN(FileName == ERROR);
   status = stat(FileName, &buf);
   FORBIDDEN(status != 0);
   return (buf.st_size == 0);
   }/*Empty*/


void
FileSize(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(int*, SizePtr),
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(int*, SizePtr)
   GMC_DCL(tp_FileName, FileName)
{
   int status;
   struct stat buf;

   FORBIDDEN(FileName == ERROR);
   *AbortPtr = FALSE;
   *SizePtr = 0;
   status = stat(FileName, &buf);
   if (status != 0) {
      *AbortPtr = TRUE;
      return; }/*if*/;
   *SizePtr = buf.st_size;
   }/*FileSize*/


void
Remove(
   GMC_ARG(tp_FileName, FileName)
   )
   GMC_DCL(tp_FileName, FileName)
{
   int status;

   FORBIDDEN(FileName == ERROR);
   status = unlink(FileName);
   if (status != 0) SystemError("\"%s\": rm failed.\n", FileName);
   }/*Remove*/


void
RemoveDir(
   GMC_ARG(tp_FileName, DirName)
   )
   GMC_DCL(tp_FileName, DirName)
{
   int status;
   tps_Str NFS_Hack;

   FORBIDDEN(DirName == ERROR);
   status = rmdir(DirName);
   if (status != 0) {
      (void)sprintf(NFS_Hack, "rm -f %s/.nfs*", DirName);
      status = system(NFS_Hack);
      status = rmdir(DirName);
      if (status != 0) {
	 SystemError("\"%s\": rmdir failed.\n", DirName); }/*if*/; }/*if*/;
   }/*RemoveDir*/


void
Rename(
   GMC_ARG(boolean*, AbortPtr),
   GMC_ARG(tp_FileName, OldFileName),
   GMC_ARG(tp_FileName, NewFileName)
   )
   GMC_DCL(boolean*, AbortPtr)
   GMC_DCL(tp_FileName, OldFileName)
   GMC_DCL(tp_FileName, NewFileName)
{
   int status;

   FORBIDDEN(OldFileName == ERROR  || NewFileName == ERROR);
   status = rename(OldFileName, NewFileName);
   if (status != 0) {
      SystemError("\"%s\": bad status from rename to %s.\n", OldFileName, NewFileName);
      if (Exists(OldFileName) || !Exists(NewFileName)) {
	 *AbortPtr = TRUE;
	 return; }/*if*/;
      SystemError("  (but it apparently worked).\n"); }/*if*/;
   *AbortPtr = FALSE;
   }/*Rename*/



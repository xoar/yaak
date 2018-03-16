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
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <pwd.h>


#ifdef BSD_SIGNALS
static int	SigBlockMask;
static int	SigUnblockMask;
#else
static sigset_t SigBlockMaskBuf, *SigBlockMask = &SigBlockMaskBuf;
static sigset_t SigUnblockMaskBuf, *SigUnblockMask = &SigUnblockMaskBuf;
#endif

static boolean	SigBlocked = FALSE;

boolean		Signalled = FALSE;
boolean		Handled = FALSE;
boolean		SigChild = FALSE;

static int	sigpipe[2];
static char	sigbuf[4];


static void
Catch_Sig(
   GMC_ARG(int, sig)
   )
   GMC_DCL(int, sig)
/*ARGSUSED*/
{
   int status;

   Signalled = TRUE;
   status = write(sigpipe[1], sigbuf, 1);
   }/*Catch_Sig*/


static void
Catch_SigChild(
   GMC_ARG(int, sig)
   )
   GMC_DCL(int, sig)
/*ARGSUSED*/
{
   int status;

   SigChild = TRUE;
   status = write(sigpipe[1], sigbuf, 1);
   }/*Catch_SigChild*/


void
Init_Sigs(
   GMC_ARG(boolean, NoInterrupt)
   )
   GMC_DCL(boolean, NoInterrupt)
{
#ifdef BSD_SIGNALS
   int Mask;
#else
   struct sigaction actbuf;
   sigset_t MaskBuf, *Mask = &MaskBuf;
#endif
   int status;

   if (SigBlocked) Unblock_Signals();

   status = pipe(sigpipe);
   FORBIDDEN(status != 0);
   status = fcntl(sigpipe[0], F_SETFL, O_NONBLOCK);
   FORBIDDEN(status != 0);
   status = fcntl(sigpipe[1], F_SETFL, O_NONBLOCK);
   FORBIDDEN(status != 0);

#ifdef BSD_SIGNALS
   (void)signal(SIGINT, Catch_Sig);
   (void)signal(SIGCHLD, Catch_SigChild);
   if (NoInterrupt) {
      (void)signal(SIGQUIT, Catch_Sig);
      (void)signal(SIGTERM, Catch_Sig);
      (void)signal(SIGTSTP, SIG_IGN); }/*if*/;
   Mask = sigmask(SIGHUP) | sigmask(SIGINT) | sigmask(SIGQUIT)
      | sigmask(SIGTERM) | sigmask(SIGCHLD);
   SigUnblockMask = sigblock(Mask);
   SigBlockMask = sigblock(Mask);
#else
   status = sigemptyset(&actbuf.sa_mask);
   FORBIDDEN(status != 0);
   actbuf.sa_flags = 0;

   actbuf.sa_handler = Catch_Sig;
   status = sigaction(SIGINT, &actbuf, (struct sigaction *)NULL);
   FORBIDDEN(status != 0);
   actbuf.sa_handler = Catch_SigChild;
   status = sigaction(SIGCHLD, &actbuf, (struct sigaction *)NULL);
   FORBIDDEN(status != 0);
   if (NoInterrupt) {
      actbuf.sa_handler = Catch_Sig;
      status = sigaction(SIGQUIT, &actbuf, (struct sigaction *)NULL);
      FORBIDDEN(status != 0);
      status = sigaction(SIGTERM, &actbuf, (struct sigaction *)NULL);
      FORBIDDEN(status != 0);
      actbuf.sa_handler = SIG_IGN;
      status = sigaction(SIGTSTP, &actbuf, (struct sigaction *)NULL);
      FORBIDDEN(status != 0); }/*if*/;
   status = sigemptyset(Mask);
   FORBIDDEN(status != 0);
   status = sigaddset(Mask, SIGHUP);
   FORBIDDEN(status != 0);
   status = sigaddset(Mask, SIGINT);
   FORBIDDEN(status != 0);
   status = sigaddset(Mask, SIGQUIT);
   FORBIDDEN(status != 0);
   status = sigaddset(Mask, SIGTERM);
   FORBIDDEN(status != 0);
   status = sigaddset(Mask, SIGCHLD);
   FORBIDDEN(status != 0);
   status = sigprocmask(SIG_BLOCK, Mask, SigUnblockMask);
   FORBIDDEN(status != 0);
   status = sigprocmask(SIG_SETMASK, (sigset_t *)NULL, SigBlockMask);
   FORBIDDEN(status != 0);
#endif
   SigBlocked = TRUE;
   }/*Init_Sigs*/


void
Block_Signals(GMC_ARG_VOID)
{
   int status;

   FORBIDDEN(SigBlocked);
   SigBlocked = TRUE;
#ifdef BSD_SIGNALS
   (void)sigsetmask(SigBlockMask);
#else
   status = sigprocmask(SIG_SETMASK, SigBlockMask, (sigset_t *)NULL);
   FORBIDDEN(status != 0);
#endif
   }/*Block_Signals*/


void
Unblock_Signals(GMC_ARG_VOID)
{
   int status;

   FORBIDDEN(!SigBlocked);
   SigBlocked = FALSE;
#ifdef BSD_SIGNALS
   (void)sigsetmask(SigUnblockMask);
#else
   status = sigprocmask(SIG_SETMASK, SigUnblockMask, (sigset_t *)NULL);
   FORBIDDEN(status != 0);
#endif
   }/*Unblock_Signals*/


#ifndef HAVE_UNISTD_H
#include <sys/ioctl.h>
#include <sys/file.h>
pid_t
setsid(GMC_ARG_VOID)
{
   pid_t pgrp;
   int fd;

   pgrp = setpgrp(0, getpid());
   if ((fd = open("/dev/tty", O_RDWR)) >= 0) {
      (void)ioctl(fd, TIOCNOTTY, (char *)0);
      (void)close(fd); }/*if*/;
   return pgrp;
   }/*setsid*/
#endif


void
Lose_ControlTTY(GMC_ARG_VOID)
{
   (void)setsid();
   }/*Lose_ControlTTY*/


int
SystemExec(
   GMC_ARG(const char*, Tool),
   GMC_ARG(char* const *, ArgV),
   GMC_ARG(const char*, LogFileName)
   )
   GMC_DCL(char*, Tool)
   GMC_DCL(char**, ArgV)
   GMC_DCL(char*, LogFileName)
{
   int pid, fd, status;

   pid = fork();
   if (pid == 0) {
      if (LogFileName != NIL) {
	 fd = open("/dev/null", O_RDONLY);
	 status = dup2(fd, 0);
	 FORBIDDEN(status != 0);
	 fd = open(LogFileName, O_WRONLY|O_TRUNC);
	 status = dup2(fd, 1);
	 FORBIDDEN(status != 1);
	 status = dup2(fd, 2);
	 FORBIDDEN(status != 2); }/*if*/;
      if (SigBlocked) Unblock_Signals();
      (void)execv(Tool, ArgV);
      SysCallError(StdOutFD, "execv");
      _exit(1); }/*if*/; /* exit(1) dumps core ... */
   return pid;
   }/*SystemExec*/


int
SystemExecCmd(
   GMC_ARG(const char*, Cmd),
   GMC_ARG(boolean, Interactive)
   )
   GMC_DCL(char*, Cmd)
   GMC_DCL(boolean, Interactive)
{
   int pid;
   tp_Str Shell;

   pid = fork();
   if (pid == 0) {
      Shell = NIL;
      if (Interactive) Shell = GetEnv("SHELL");
      if (Shell == NIL) Shell = "/bin/sh";
      if (SigBlocked) Unblock_Signals();
      (void)execl(Shell, Shell, "-c", Cmd, (char *)0);
      SysCallError(StdOutFD, "execl");
      SystemError("Trying to execute: %s -c %s\n", Shell, Cmd);
      _exit(1); }/*if*/; /* exit(1) dumps core ... */
   return pid;
   }/*SystemExecCmd*/


void
SystemWait(
   GMC_ARG(int*, pidPtr),
   GMC_ARG(boolean*, AbortPtr)
   )
   GMC_DCL(int*, pidPtr)
   GMC_DCL(boolean*, AbortPtr)
{
#ifdef HAVE_WAITPID
   int status;
#else
   union wait status;
#endif

#ifdef HAVE_WAITPID
   *pidPtr = waitpid(-1, &status, WNOHANG);
#else
   *pidPtr = wait3(&status, WNOHANG, 0);
#endif
   if (*pidPtr < 0) {
      /* probably called system() */
      *pidPtr = 0;
      return; }/*if*/;
#ifdef HAVE_WAITPID
   *AbortPtr = (!WIFEXITED(status) || WEXITSTATUS(status) != 0);
#else
   *AbortPtr = (!WIFEXITED(status) || status.w_retcode != 0);
#endif
   }/*SystemWait*/


void
SystemInterrupt(
   GMC_ARG(int, pid)
   )
   GMC_DCL(int, pid)
{
   (void)kill(pid, SIGINT);
   }/*SystemInterrupt*/


tp_Str
GetHome(
   GMC_ARG(tp_Str, Str)
   )
   GMC_DCL(tp_Str, Str)
{
   struct passwd *pwd;

   /*select*/{
      if (strlen(Str) == 0) {
	 pwd = getpwuid(getuid());
      }else{
	 pwd = getpwnam(Str); };}/*select*/;
   if (pwd == NULL) {
      return NIL; }/*if*/;
   return pwd->pw_dir;
   }/*GetHome*/


int
Await_Event(
   GMC_ARG(fd_set*, readfds),
   GMC_ARG(boolean, HaveTask)
   )
   GMC_DCL(fd_set*, readfds)
   GMC_DCL(boolean, HaveTask)
{
   int nfds;
   int count;

   if (HaveTask) count = write(sigpipe[1], sigbuf, 1);
   FD_SET(sigpipe[0], readfds);

   nfds = select(FD_SETSIZE, readfds, (fd_set *)0, (fd_set *)0, NULL);
   if (FD_ISSET(sigpipe[0], readfds)) { 
      count = read(sigpipe[0], sigbuf, sizeof(sigbuf));
   }   
   
   return nfds;
   }/*Await_Event*/

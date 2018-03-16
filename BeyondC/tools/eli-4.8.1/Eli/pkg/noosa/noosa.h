/*
 * $Id: noosa.h,v 1.23 2001/03/23 18:31:15 tony Exp $
 * Copyright (c) 1994-1999 Anthony M. Sloane
 */

/* This file is part of the Eli translator construction system.

Eli is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

Eli is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with Eli; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

#ifndef NOOSA_H
#define NOOSA_H

/* Define MAXPATHLEN */
/* BSD Version */
#include <sys/param.h>
#include "eliproto.h"
#include "obstack.h"
#include "tcl.h"
#include "tk.h"

#if defined(sun) && !defined(__SVR4) && !defined(__svr4__)
#define USE_ONEXIT
#define USE_SIGCONTEXTADDR
#define DECLARE_SHMAT
#endif

#if defined(ultrix)
#define NEED_STRDUP
#endif

#if defined(mips)
#define USE_SIGCONTEXT
#endif

#ifdef USE_SIGCONTEXT
#ifdef PROTO_OK
#define SIG_HANDLER(n) \
static void n (int sig, int code, struct sigcontext *scp)
#else
#define SIG_HANDLER(n) \
static void n (sig, code, scp) \
    int sig, code; \
    struct sigcontext *scp;
#endif
#else
#ifdef USE_SIGCONTEXTADDR
#ifdef PROTO_OK
#define SIG_HANDLER(n) \
static void n (int sig, int code, struct sigcontext scp, char *addr)
#else
#define SIG_HANDLER(n) \
static void n (sig, code, scp, addr) \
    int sig, code; \
    struct sigcontext *scp; \
    char *addr;
#endif
#else
#ifdef PROTO_OK
#define SIG_HANDLER(n) \
static void n (int sig)
#else
#define SIG_HANDLER(n) \
static void n (sig) \
    int sig;
#endif
#endif
#endif

#if defined(sun) || defined(__sun__) || defined(__sun) || defined(__mips) || defined(_AIX) || defined(___AIX__)
#ifdef PROTO_OK
extern char *strdup (const char *);
#else
extern char *strdup ();
#endif
#endif

extern Tcl_Interp *n_interp;
extern char *n_pid, *n_status;

extern void create_comms (), delete_comms ();

#define TCL_CMD(n) \
  extern int n _ANSI_ARGS_((ClientData, Tcl_Interp *, int, Tcl_Obj *CONST []));

TCL_CMD(n_handleCmd)
TCL_CMD(n_handlernameCmd)
TCL_CMD(n_removeCmd)
TCL_CMD(n_enableCmd)
TCL_CMD(n_event_paramsCmd)
TCL_CMD(n_sendbCmd)
TCL_CMD(n_init_signalsCmd)
TCL_CMD(n_finit_signalsCmd)
TCL_CMD(n_wait_childCmd)
TCL_CMD(n_cont_childCmd)
TCL_CMD(n_kill_childCmd)
TCL_CMD(n_lrtree_buildCmd)
TCL_CMD(n_lrtree_drawCmd)

/* Handlers */ 

typedef void (*chandler_func)();

typedef struct {
    char *name;
    chandler_func func;
} chandler;

extern void n_init_handlers ();
extern chandler_func n_get_handler _ANSI_ARGS_((char *));

TCL_CMD(n_token_initCmd)
TCL_CMD(n_find_tokensCmd)
TCL_CMD(n_phrase_initCmd)
TCL_CMD(n_find_phrasesCmd)

/* Parameters to C handlers */

typedef union param param;
union param {
    int i;
    long l;
    char *s;
};

#endif


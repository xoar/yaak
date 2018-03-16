/*
 * $Id: main.c,v 1.46 2013/12/05 21:34:43 profw Exp $
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

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "tcl.h"
#include "tk.h"
#include "noosa.h"

/*
 * Constants
 */

#define SYSTEM_RC_BASE	"noosa.tcl"

#define PROMPT		"noosa> "
#define HELP		"Type \"noosa help\" for a list of commands.\n"

/*
 * Commands
 */

typedef struct {
    char *name;
    Tcl_ObjCmdProc *proc;
} CmdInfo;

TCL_CMD(n_dectohexCmd)
TCL_CMD(n_hextodecCmd)

static CmdInfo noosaCmds[] = {
{ "n_init_signals",  		n_init_signalsCmd },
{ "n_finit_signals", 		n_finit_signalsCmd },
{ "n_handle",    		n_handleCmd },
{ "n_handlername",    		n_handlernameCmd },
{ "n_remove",    		n_removeCmd },
{ "n_enable",    		n_enableCmd },
{ "n_wait_child",    		n_wait_childCmd },
{ "n_cont_child",    		n_cont_childCmd },
{ "n_kill_child",    		n_kill_childCmd },
{ "n_event_params",    		n_event_paramsCmd },
{ "n_sendb",    		n_sendbCmd },
/* Tree drawing support */
{ "n_lrtree_build",		n_lrtree_buildCmd },
{ "n_lrtree_draw",		n_lrtree_drawCmd },
/* Handlers */
{ "n_token_init",		n_token_initCmd },
{ "n_find_tokens",		n_find_tokensCmd },
{ "n_phrase_init",		n_phrase_initCmd },
{ "n_find_phrases",		n_find_phrasesCmd },
/* Number conversions */
{ "n_dectohex",		        n_dectohexCmd },
{ "n_hextodec",		        n_hextodecCmd },
{ NULL,	                 	(Tcl_ObjCmdProc *) NULL }
};

/*
 * Variables
 */

Tcl_Interp *n_interp;
static int n_index = 0;
#ifdef PROFILE
static int n_profile = 0;
#endif
Tk_Window noosawin;
char *n_pid = NULL, *n_status = NULL;

/*
 * usage
 */

void usage ()
{
#ifdef PROFILE
    fprintf (stderr, "usage: noosa [-h|-i|-p] script [arg...]\n");
#else
    fprintf (stderr, "usage: noosa [-h|-i] script [arg...]\n");
#endif
    Tcl_Exit (1);
}

/*
 * help
 */

void help ()
{
    fprintf (stderr, "usage: noosa [-h|-i]\n");
    fprintf (stderr, "       noosa script exe db [arg...]\n");
    fprintf (stderr, "  -h      : produce this message and exit\n");
    fprintf (stderr, "  -i      : produce tclIndex and exit\n");
#ifdef PROFILE
    fprintf (stderr, "  -p      : generate a profile in profile.out\n");
#endif
    fprintf (stderr, "  script  : a file containing Noosa commands\n");
    fprintf (stderr, "  arg     : optional script argument\n");
    fprintf (stderr, "noosa also accepts standard X windows arguments\n");
    Tcl_Exit (1);
}

/*
 * n_dectohexCmd
 */

#ifdef PROTO_OK
int n_dectohexCmd (ClientData clientData, Tcl_Interp *interp,
                   int objc, Tcl_Obj *CONST objv[])
#else
int n_dectohexCmd (notUsed, interp, objc, objv)
    ClientData notUsed;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    long l;
    char buf[100]; /* FIXME: static size */

    if (objc != 2) {
        Tcl_WrongNumArgs (interp, 1, objv, "decint");
	return TCL_ERROR;
    }

    if (Tcl_GetLongFromObj (interp, objv[1], &l) == TCL_ERROR)
        return TCL_ERROR;

    sprintf (buf, "%lx", l);
    Tcl_SetResult (interp, buf, TCL_VOLATILE);

    return TCL_OK;
}

/*
 * n_hextodecCmd
 */

#ifdef PROTO_OK
int n_hextodecCmd (ClientData clientData, Tcl_Interp *interp,
                   int objc, Tcl_Obj *CONST objv[])
#else
int n_hextodecCmd (notUsed, interp, objc, objv)
    ClientData notUsed;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    char *s;
    long l;

    if (objc != 2) {
        Tcl_WrongNumArgs (interp, 1, objv, "hexint");
	return TCL_ERROR;
    }

    s = Tcl_GetStringFromObj (objv[1], NULL);
    l = strtol (s, NULL, 16);
    Tcl_SetObjResult (interp, Tcl_NewLongObj (l));

    return TCL_OK;
}

/*
 * n_exit
 */

#ifdef PROTO_OK
static void n_exit (ClientData clientData)
#else
static void n_exit (clientData)
    ClientData clientData;
#endif
{
    Tcl_Eval (n_interp, "n_killall");
    delete_comms ();
    Tcl_Release (n_interp);
}

/*
 * sighup_handler
 */

SIG_HANDLER (sighup_handler)
{
#ifdef DEBUG
    fprintf (stderr, "noosa: got SIGHUP\n");
#endif
    Tcl_Exit (1);
}

/*
 * Tcl_AppInit
 */

#ifdef PROTO_OK
int Tcl_AppInit (Tcl_Interp *interp)
#else
int Tcl_AppInit (interp)
    Tcl_Interp *interp;
#endif
{
    char *n_lib, pidbuf[10], varbuf[10];
    CmdInfo *cmdinfo;
    struct sigaction actbuf;

    /* Preserve the interpreter so it doesn't get deleted before we exit */
    Tcl_Preserve (interp);

    /* Initialise the state needed by the TCL code */
    if ((n_lib = getenv ("NOOSA_LIB")) == (char *) NULL)
	n_lib = ".";
    Tcl_SetVar2 (interp, "n", "lib", n_lib, TCL_GLOBAL_ONLY);

    /* Save away the interpreter for global use */
    n_interp = interp;

    /* Initialise the interpreter */
    if (Tcl_Init (interp) == TCL_ERROR)
	return TCL_ERROR;

    /* If indexing then just do it and go away */
    if (n_index) {
	if (Tcl_VarEval (interp, "auto_mkindex ", n_lib, " *.tcl",
			 (char *) NULL) == TCL_ERROR)
	    return TCL_ERROR;
	Tcl_Exit (0);
    }

    /* Initialise the window system */
    if (Tk_Init (interp) == TCL_ERROR)
	return TCL_ERROR;

    /* Allow the child to detect us, initialise communications */
    sprintf (pidbuf, "%d", getpid ());
    Tcl_SetVar2 (interp, "env", "NOOSA_PRESENT", pidbuf, TCL_GLOBAL_ONLY);
    create_comms ();
    
    /* Get the main window */
    noosawin = Tk_MainWindow(interp);
    Tk_SetClass (noosawin, "Noosa");

    /* Initialise and load the noosa commands */
    for (cmdinfo = noosaCmds; cmdinfo->name != NULL; cmdinfo++)
	Tcl_CreateObjCommand (interp, cmdinfo->name, cmdinfo->proc,
                              (ClientData) noosawin,
                              (Tcl_CmdDeleteProc *) NULL);
    
    /* Link some C vars to Tcl vars to speed access in event_handler */
    /* Names must be in writable memory as Tcl may modify */
    strcpy (varbuf, "n(status)");
    if (Tcl_LinkVar (interp, varbuf, (char *)&n_status, TCL_LINK_STRING)
	== TCL_ERROR) {
	fprintf (stderr, "noosa: can't link n_status and n(status), %s\n",
		 Tcl_GetStringResult(interp));
	Tcl_Exit (1);
    }
    strcpy (varbuf, "n(pid)");
    if (Tcl_LinkVar (interp, varbuf, (char *)&n_pid, TCL_LINK_STRING)
	== TCL_ERROR) {
	fprintf (stderr, "noosa: can't link n_pid and n(pid), %s\n",
		 Tcl_GetStringResult(interp));
	Tcl_Exit (1);
    }

    /* Set profiling flag */
#ifdef PROFILE
    if (n_profile)
	Tcl_SetVar2 (interp, "n", "profile", "1", TCL_GLOBAL_ONLY);
    else
	Tcl_SetVar2 (interp, "n", "profile", "0", TCL_GLOBAL_ONLY);
#else
    Tcl_SetVar2 (interp, "n", "profile", "0", TCL_GLOBAL_ONLY);
#endif

    /* Set up cleanup functions */
    if (sigemptyset (&actbuf.sa_mask) == -1) {
	perror ("noosa sigemptyset SIGINT");
	Tcl_Exit (1);
    }
    actbuf.sa_flags = 0;
    actbuf.sa_handler = SIG_IGN;
    if (sigaction (SIGINT, &actbuf, (struct sigaction *)0) == -1) {
	perror ("noosa sigaction SIGINT");
	Tcl_Exit (1);
    }
    if (sigemptyset (&actbuf.sa_mask) == -1) {
	perror ("noosa sigemptyset SIGHUP");
	Tcl_Exit (1);
    }
    actbuf.sa_flags = 0;
    actbuf.sa_handler = sighup_handler;
    if (sigaction (SIGHUP, &actbuf, (struct sigaction *)0) == -1) {
	perror ("noosa sigaction SIGHUP");
	Tcl_Exit (1);
    }
    Tcl_CreateExitHandler (n_exit, 0);
	
    /* Set up C handlers */
    n_init_handlers ();

    return TCL_OK;
}

/*
 * main
 */

#ifdef PROTO_OK
int main (int argc, char *argv[])
#else
int main (argc, argv)
    int argc;
    char *argv[];
#endif
{
    /* Parse Noosa-level args */
    if (argc > 1) {
	if (strcmp (argv[1], "-h") == 0)
	    help ();
	else if (strcmp (argv[1], "-i") == 0)
	    n_index = 1;
#ifdef PROFILE
	else if (strcmp (argv[1], "-p") == 0)
	    n_profile = 1;
#endif
    }

    /* Start things going */
    if (n_index)
	Tcl_Main (argc, argv, Tcl_AppInit);
    else
        Tk_Main (argc, argv, Tcl_AppInit);
    return 0;
}


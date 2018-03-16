/*
 * $Id: child.c,v 1.36 2013/08/26 20:15:57 profw Exp $
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
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "tcl.h"
#include "noosa.h"
#include "eliproto.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#ifndef SHM_W
#define SHM_W	0200
#endif

#ifndef SHM_R
#define SHM_R	0400
#endif

#ifdef DECLARE_SHMAT
#ifdef PROTO_OK
extern char *shmat (int shmid, const void *shmaddr, int shmflg);
#else
extern char *shmat ();
#endif
#endif

extern char *strdup _ANSI_ARGS_ ((const char *));

#define MAXMSGSIZE 0x100000

#define TCL_HANDLER 1
#define C_HANDLER 2

typedef struct handler_struct handler;
struct handler_struct {
    char *handlername;
    void *handle;
    int type, id, enable, remove;
    handler *next, *prev;
};
  
static Tcl_HashTable handlers;
static Tcl_HashTable params;
static char *handlername;

static int signals_on = 0;
static struct sigaction old_sigchld_action;

static int shmid;
static char *snbuf, *event_name = NULL;
static int sigusr1, sigusr1_event = 1;

/*
 * sigchild_handler
 */

SIG_HANDLER (sigchild_handler)
{
    /* CAUTION: Don't print here -- even for debugging! */
    waitpid (-1, 0, WNOHANG);
}

/*
 * n_init_signalsCmd
 */

#ifdef PROTO_OK
int n_init_signalsCmd (ClientData clientData, Tcl_Interp *interp,
                       int objc, Tcl_Obj *CONST objv[])
#else
int n_init_signalsCmd (clientData, interp, objc, objv)
    ClientData clientData;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    struct sigaction actbuf;

    if (objc != 1) {
        Tcl_WrongNumArgs (interp, 1, objv, NULL);
	return TCL_ERROR;
    }

    if (!signals_on) {
        if (sigemptyset (&actbuf.sa_mask) == -1) {
            perror ("noosa sigemptyset init");
            Tcl_Exit (1);
        }
        actbuf.sa_flags = 0;
        actbuf.sa_handler = sigchild_handler;
        
        if (sigaction (SIGCHLD, &actbuf, &old_sigchld_action) == -1) {
            perror ("noosa sigaction init");
            Tcl_Exit (1);
        }
        signals_on = 1;
    }

    return TCL_OK;
}

/*
 * n_finit_signalsCmd
 */

#ifdef PROTO_OK
int n_finit_signalsCmd (ClientData clientData, Tcl_Interp *interp,
                        int objc, Tcl_Obj *CONST objv[])
#else
int n_finit_signalsCmd (clientData, interp, objc, objv)
    ClientData clientData;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    if (objc != 1) {
        Tcl_WrongNumArgs (interp, 1, objv, NULL);
	return TCL_ERROR;
    }

    if (signals_on) {
        if (sigaction (SIGCHLD, &old_sigchld_action, (struct sigaction *)0)) {
            perror ("noosa sigaction finit");
            Tcl_Exit (1);
        }
        signals_on = 0;
    }

    return TCL_OK;
}

/*
 * n_wait_childCmd
 */

#ifdef PROTO_OK
int n_wait_childCmd (ClientData clientData, Tcl_Interp *interp,
                     int objc, Tcl_Obj *CONST objv[])
#else
int n_wait_childCmd (clientData, interp, objc, objv)
    ClientData clientData;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    int pid, status, ret;
    
    if (objc != 2) {
        Tcl_WrongNumArgs (interp, 1, objv, NULL);
	return TCL_ERROR;
    }
    
    pid = atoi (Tcl_GetStringFromObj (objv[1], NULL));

#ifdef DEBUG
    fprintf (stderr, "noosa: waiting for child %d\n", pid);
#endif
    wait (0);
#ifdef DEBUG
    fprintf (stderr, "noosa: finished waiting for child %d\n", pid);
#endif

    return TCL_OK;
}

/*
 * n_cont_child
 */

#ifdef PROTO_OK
static int n_cont_child (Tcl_Interp *interp, char *pidbuf)
#else
static int n_cont_child (interp, pidbuf)
    Tcl_Interp *interp;
    char *pidbuf;
#endif
{
    int pid = atoi (pidbuf);

#ifdef DEBUG
    fprintf (stderr, "noosa: continuing %d\n", pid);
#endif

    if (pid == -1) {
	Tcl_AppendResult (interp, "almost continued all your processes",
			  (char *) NULL);
	return TCL_ERROR;
    }
    if (kill (pid, SIGUSR1) == -1) {
	Tcl_AppendResult (interp, Tcl_PosixError(interp), (char *) NULL);
	return TCL_ERROR;
    }
    return TCL_OK;
}

/*
 * n_cont_childCmd
 */

#ifdef PROTO_OK
int n_cont_childCmd (ClientData clientData, Tcl_Interp *interp,
                     int objc, Tcl_Obj *CONST objv[])
#else
int n_cont_childCmd (clientData, interp, objc, objv)
    ClientData clientData;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    if (objc != 2) {
        Tcl_WrongNumArgs (interp, 1, objv, "pid");
	return TCL_ERROR;
    }
    return n_cont_child (interp, Tcl_GetStringFromObj (objv[1], NULL));
}

/*
 * n_kill_childCmd
 */

#ifdef PROTO_OK
int n_kill_childCmd (ClientData clientData, Tcl_Interp *interp,
                     int objc, Tcl_Obj *CONST objv[])
#else
int n_kill_childCmd (clientData, interp, objc, objv)
    ClientData clientData;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    int pid, ret;

    if (objc != 2) {
        Tcl_WrongNumArgs (interp, 1, objv, "pid");
	return TCL_ERROR;
    }

    Tcl_GetIntFromObj (interp, objv[1], &pid);

#ifdef DEBUG
    fprintf (stderr, "noosa: killing child %d\n", pid);
#endif

    if (pid == -1) {
	Tcl_AppendResult (interp, "almost killed all your processes",
			  (char *) NULL);
	return TCL_ERROR;
    }
    ret = kill (pid, SIGHUP);
    if (ret == -1) {
	Tcl_AppendResult (interp, Tcl_PosixError (interp), (char *) NULL);
	return TCL_ERROR;
    }
    return TCL_OK;
}

/*
 * print_mesg
 */

#ifdef PROTO_OK
static void print_mesg (char *cp)
#else
static void print_mesg (cp)
    char *cp;
#endif
{
    int size, i;
    long int l;

    for ( ; *cp != '\0'; cp += size) 
	switch (*cp++) {
	    case 'i': {
                memcpy ((void *)&i, cp, sizeof (int));
		fprintf (stderr, "%d ", i);
		size = sizeof (int);
		break;
	    }

	    case 'l': {
                memcpy ((void *)&l, cp, sizeof (long int));
		fprintf (stderr, "%ld ", l);
		size = sizeof (long int);
		break;
	    }

	    case 's': {
		fprintf (stderr, "'%s' ", cp);	
		size = strlen (cp) + 1;
		break;
	    }

	    default:
		fprintf (stderr, "?%c ", *cp);
                size = 0;
	}
}

/*
 * make_bindings
 * FIXME: assumes two events of the same kind can't overlap in handling
 * because it uses one namespace per event type.
 */

#ifdef PROTO_OK
static void make_bindings (Tcl_Interp *interp, char *event_name, char *args)
#else
static void make_bindings (interp, event_name, args)
    Tcl_Interp *interp;
    char *event_name, *args;
#endif
{
    Tcl_Obj **np;
    Tcl_HashEntry *entry;
    int i;
    long l;

    if ((entry = Tcl_FindHashEntry (&params, event_name)) == NULL)
	return;
    np = (Tcl_Obj **) Tcl_GetHashValue (entry);
    for (; *args != '\0'; np++) {
	switch (*args++) {
	    case 'i':
                memcpy ((void *)&i, args, sizeof (int));
		Tcl_ObjSetVar2 (interp, *np, NULL, Tcl_NewIntObj (i), 0);
		args += sizeof (int);
		break;

	    case 'l':
                memcpy ((void *)&l, args, sizeof (long int));
		Tcl_ObjSetVar2 (interp, *np, NULL, Tcl_NewLongObj (l), 0);
		args += sizeof (long int);
		break;

	    case 's':
		Tcl_ObjSetVar2 (interp, *np, NULL,
				Tcl_NewStringObj (args, -1), 0);
		args += strlen (args) + 1;
		break;
	}
    }
    return; 
}

/*
 * make_pars
 */

#ifdef PROTO_OK
static void make_pars (char *buf, int *parcp, param **parv,
                       Obstack *par_obstkp)
#else
static void make_pars (buf, parcp, parv, par_obstkp)
    char *buf;
    int *parcp;
    param **parv;
    Obstack *par_obstkp;
#endif
{
    char *cp = buf;
    param *pp;

    obstack_init (par_obstkp);
    *parcp = 0;
    for (; *cp != '\0';) {
        (*parcp)++;
        obstack_blank (par_obstkp, sizeof (param));
        pp = (param *) (obstack_next_free (par_obstkp) -
                        sizeof (param));
	switch (*cp++) {
	    case 'i':
                memcpy ((void *)&(pp->i), cp, sizeof (int));
		cp += sizeof (int);
		break;

	    case 'l':
                memcpy ((void *)&(pp->l), cp, sizeof (long int));
		cp += sizeof (long int);
		break;

	    case 's':
                pp->s = cp;
		cp += strlen (cp) + 1;
		break;
	}
    }
    *parv = (param *) obstack_finish (par_obstkp);
}
    
/*
 * make_objs
 */

#ifdef PROTO_OK
static void make_objs (char *buf, int *objcp, Tcl_Obj ***objv,  
                       Obstack *obj_obstkp)
#else
static void make_objs (buf, objcp, objv, obj_obstkp)
    char *buf;
    int *objcp;
    Tcl_Obj ***objv;
    Obstack *obj_obstkp;
#endif
{
    char *cp = buf;
    Tcl_Obj **op;
    int i;
    long l;

    *objcp = 0;
    for (; *cp != '\0';) {
        (*objcp)++;
        obstack_blank (obj_obstkp, sizeof (Tcl_Obj *));
        op = (Tcl_Obj **) (obstack_next_free (obj_obstkp) -
                           sizeof (Tcl_Obj *));
	switch (*cp++) {
	    case 'i':
                memcpy ((void *)&i, cp, sizeof (int));
                *op = Tcl_NewIntObj (i);
		cp += sizeof (int);
		break;

	    case 'l':
                memcpy ((void *)&l, cp, sizeof (long int));
                *op = Tcl_NewLongObj (l);
		cp += sizeof (long int);
		break;

	    case 's':
                *op = Tcl_NewStringObj (cp, -1);
		cp += strlen (cp) + 1;
		break;
	}
    }
    *objv = (Tcl_Obj **) obstack_finish (obj_obstkp);
}
    
/*
 * list_remove
 */

#ifdef PROTO_OK
static void list_remove (Tcl_HashEntry *entry, handler *h)
#else
static void list_remove (entry, h)
    Tcl_HashEntry *entry;
    handler *h;
#endif
{
    if (h->prev == (handler *) NULL)
        Tcl_SetHashValue (entry, h->next);
    else
        h->prev->next = h->next;
    if (h->next != (handler *) NULL)
        h->next->prev = h->prev;
    if (h->type == TCL_HANDLER) {
        Tcl_DecrRefCount ((Tcl_Obj *)h->handle);
        free (h->handlername);
        free (h);
    }    
}

/*
 * n_event
 */

#ifdef PROTO_OK
static void n_event (char *event)
#else
static void n_event (event)
    char *event;
#endif
{
    int parc, ret, bound = 0, pars = 0;
    Obstack par_obstk;
    param *parv;
    Tcl_HashEntry *entry;
    handler *h;

#ifdef DEBUG
    fputs ("noosa: ", stderr);
    print_mesg (event);
    fputc ('\n', stderr);
#endif
    
    /* Get event name */
    event_name = event + 1;

#ifdef DEBUG
    fprintf (stderr, "noosa: event is %s\n", event_name);
#endif
    
    /* Find the handlers for this event, if none return immediately */
    if ((entry = Tcl_FindHashEntry (&handlers, event_name)) == NULL)
	goto retlab;

    /* Invoke each enabled handler */
    for (h = (handler *) Tcl_GetHashValue (entry); h != (handler *) NULL; 
         h = h->next) {
	if (h->enable) {
            handlername = h->handlername;
	    switch (h->type) {

	    case TCL_HANDLER:
#ifdef DEBUG
    		fprintf (stderr, "noosa: handled in Tcl by %s\n",
                         h->handlername);
#endif
                if (!bound) {
                    make_bindings (n_interp, event_name, event);
                    bound = 1;
                }
		ret = Tcl_GlobalEvalObj (n_interp, (Tcl_Obj *)h->handle);
#ifdef DEBUG
    		fprintf (stderr, "noosa: handler %s returned: %d '%s'\n",
			 h->handlername, ret, Tcl_GetStringResult (n_interp));
#endif
		if (ret == TCL_ERROR) {
                    Tcl_VarEval (n_interp, "bgerror {handler \"",
                                 h->handlername, "\" failed: ",
                                 Tcl_GetStringResult (n_interp), "}",
                                 (char *)NULL);
                    goto retlab;
                }
		break;

	    case C_HANDLER:
#ifdef DEBUG
    		fprintf (stderr, "noosa: handled in C\n");
#endif
                if (!pars) {
                    make_pars (event, &parc, &parv, &par_obstk);
                    pars = 1;
                }
		((void (*)()) h->handle) (parc, parv);
		break;

	    default:
                Tcl_VarEval (n_interp, "bgerror {unknown handler type}",
                             (char *)NULL);
                goto retlab;
	    }
	}
    }

 retlab:

    /* Clean up parameter space (if any). */
    if (pars)
        obstack_free (&par_obstk, parv);

    /* Perform any handler removals that have been scheduled. */
    if (entry != (Tcl_HashEntry *)NULL)
        for (h = (handler *) Tcl_GetHashValue (entry); h != (handler *) NULL; 
             h = h->next)
            if (h->remove)
                list_remove (entry, h);

    /* No event being processed any more. */
    event_name = NULL;

#ifdef DEBUG
    fprintf (stderr, "noosa: finished handling\n");
#endif
}

/*
 * msg_handler
 */

#ifdef PROTO_OK
static int msg_handler (Tcl_Event *evPtr, int flags)
#else
static int msg_handler (evPtr, flags)
    Tcl_Event *evPtr;
    int flags; 
#endif
{
#ifdef DEBUG
    fprintf (stderr, "noosa: received message\n");
#endif

    /* Dispatch */
    if (*snbuf == 'e') {
        /* Event */ 
        n_event (snbuf + 1);
        if (strcmp (n_status, "stopped") != 0)
            n_cont_child (n_interp, n_pid);
    } else
        fprintf (stderr, "noosa: unknown message type %c in msg_handler\n",
                 *snbuf);
    return 1;
}

/*
 * sigusr1_handler
 */

SIG_HANDLER (sigusr1_handler)
{
    /* CAUTION: Don't print here -- even for debugging! */
    sigusr1 = 1;
}

/*
 * init_sigusr1_handler
 */

static void init_sigusr1_handler ()
{
    struct sigaction actbuf;

    if (sigemptyset (&actbuf.sa_mask) == -1) {
	perror ("noosa sigemptyset init");
	Tcl_Exit (1);
    }
    actbuf.sa_flags = 0;
    actbuf.sa_handler = sigusr1_handler;
    if (sigaction (SIGUSR1, &actbuf, (struct sigaction *)0) == -1) {
	perror ("noosa sigaction init SIGUSR1");
	Tcl_Exit (1);
    }
}

/*
 * finit_sigusr1_handler
 */

static void finit_sigusr1_handler ()
{
    struct sigaction actbuf;

    if (sigemptyset (&actbuf.sa_mask) == -1) {
	perror ("noosa sigemptyset finit");
	Tcl_Exit (1);
    }
    actbuf.sa_flags = 0;
    actbuf.sa_handler = SIG_IGN;
    if (sigaction (SIGUSR1, &actbuf, (struct sigaction *)0) == -1) {
	perror ("noosa sigaction finit SIGUSR1");
	Tcl_Exit (1);
    }
}

/*
 * event_setup
 */

#ifdef PROTO_OK
static void event_setup (ClientData clientData, int flags)
#else
static void event_setup (clientData, flags)
    ClientData clientData;
    int flags; 
#endif
{
   Tcl_Time t;

    /* If a signal occurred arrange for us not to block */
    if (sigusr1 && sigusr1_event) {
	t.sec = 0;
	t.usec = 0;
	Tcl_SetMaxBlockTime (&t);
    }
}

/*
 * event_check
 */

#ifdef PROTO_OK
static void event_check (ClientData clientData, int flags)
#else
static void event_check (clientData, flags)
    ClientData clientData;
    int flags; 
#endif
{
    if (sigusr1 && sigusr1_event) {
	Tcl_Event *evPtr;
	evPtr = (Tcl_Event *) Tcl_Alloc (sizeof (Tcl_Event));
	evPtr->proc = msg_handler;
	Tcl_QueueEvent (evPtr, TCL_QUEUE_TAIL);
	sigusr1 = 0;
#ifdef DEBUG
	fprintf (stderr, "noosa: queued event\n");
#endif
    }
}

/*
 * create_comms
 */

void create_comms ()
{
    /* Create shared memory region */
    if ((shmid = shmget (getpid (), MAXMSGSIZE,
			 SHM_R | SHM_W | IPC_CREAT)) == -1) {
	perror ("noosa shmget");
	Tcl_Exit (1);
    }
    if ((snbuf = (char *) shmat (shmid, 0, 0)) == (void *) -1) {
	perror ("noosa shmat");
	Tcl_Exit (1);
    }

    /* Initialise event handler and event params tables */
    Tcl_InitHashTable (&handlers, TCL_STRING_KEYS);
    Tcl_InitHashTable (&params, TCL_STRING_KEYS);

    /* Set up event source */
    Tcl_CreateEventSource (event_setup, event_check, (ClientData)0);

    /* Arrange for SIGUSR1 signals to be noticed */
    init_sigusr1_handler ();
}

/*
 * delete_comms
 */

void delete_comms ()
{
    /* Get rid of SIGUSR1 handler */
    finit_sigusr1_handler ();

    /* Delete event source */
    Tcl_DeleteEventSource (event_setup, event_check, (ClientData)0);

    /* Clean up shared memory region */
    if (shmdt (snbuf) == -1) {
	perror ("noosa shmdt snbuf");
	Tcl_Exit (1);
    }
    if (shmctl (shmid, IPC_RMID, 0) == -1) {
	perror ("noosa shmctl IPC_RMID");
	Tcl_Exit (1);
    }
}

/*
 * n_handleCmd
 */

#ifdef PROTO_OK
int n_handleCmd (ClientData clientData, Tcl_Interp *interp,
                 int objc, Tcl_Obj *CONST objv[])
#else
int n_handleCmd (notUsed, interp, objc, objv)
    ClientData notUsed;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    static int id = 0;
    int type, enable, isnew;
    handler *h;
    Tcl_HashEntry *entry;
    char *event, *handlername;

    if (objc < 5) {
        Tcl_WrongNumArgs (interp, 1, objv,
                          "type handlername event handler enableflag");
	return TCL_ERROR;
    } else {
        Tcl_GetIntFromObj (interp, objv[1], &type);
	type = (type ? C_HANDLER : TCL_HANDLER);
    }

    if ((type == TCL_HANDLER) && (objc != 6)) {
        Tcl_WrongNumArgs (interp, 1, objv,
                          "0 handlername event handler enableflag");
	return TCL_ERROR;
    } else if ((type == C_HANDLER) && (objc != 5)) {
        Tcl_WrongNumArgs (interp, 1, objv, "1 handlername event enableflag");
	return TCL_ERROR;
    }

    if ((h = (handler *) malloc (sizeof (handler))) == (handler *) NULL) {
	Tcl_AppendResult (interp, "memory allocation failure",
			  (char *) NULL);
	return TCL_ERROR;
    }

    event = Tcl_GetStringFromObj (objv[3], NULL);
    handlername = Tcl_GetStringFromObj (objv[2], NULL);

#ifdef DEBUG
    fprintf (stderr, "noosa: adding %s handler %s for %s (%d)\n",
	     (type == TCL_HANDLER ? "TCL" : "C"), handlername,
             event, id);
#endif

    h->type = type;
    h->id = id;
    if (type == TCL_HANDLER) {
        char *h_code = Tcl_GetStringFromObj (objv[4], NULL);
        if (Tcl_GetIntFromObj (interp, objv[5], &enable) == TCL_ERROR)
            return TCL_ERROR;
        h->handle = (void *) Tcl_NewStringObj ("namespace eval n_", -1);
        Tcl_AppendStringsToObj (h->handle, event, " {", h_code, "}",
                                (char *) NULL);
   	Tcl_IncrRefCount ((Tcl_Obj *)h->handle);
    } else {
	/* C_HANDLER */
	h->handle = (void *) n_get_handler (handlername);
        if (Tcl_GetIntFromObj (interp, objv[4], &enable) == TCL_ERROR)
            return TCL_ERROR;
    }
    h->enable = enable;
    h->handlername = strdup (handlername);
    h->remove = 0;
    h->prev = (handler *) NULL;
    entry = Tcl_CreateHashEntry (&handlers, event, &isnew);
    if (isnew)
	h->next = (handler *) NULL;
    else {
	h->next = (handler *) Tcl_GetHashValue (entry);
	if (h->next != (handler *) NULL)
	    h->next->prev = h;
    }
    Tcl_SetHashValue (entry, h);
    Tcl_SetIntObj (Tcl_GetObjResult (interp), id);
    id++;
    return TCL_OK;
}

/*
 * n_handlernameCmd
 */

#ifdef PROTO_OK
int n_handlernameCmd (ClientData clientData, Tcl_Interp *interp,
                      int objc, Tcl_Obj *CONST objv[])
#else
int n_handlernameCmd (notUsed, interp, objc, objv)
    ClientData notUsed;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    if (objc != 1) {
        Tcl_WrongNumArgs (interp, 1, objv, "");
	return TCL_ERROR;
    }
    Tcl_AppendResult (interp, handlername, (char *) NULL);
    return TCL_OK;
}

/*
 * n_enableCmd
 */

#ifdef PROTO_OK
int n_enableCmd (ClientData clientData, Tcl_Interp *interp,
                 int objc, Tcl_Obj *CONST objv[])
#else
int n_enableCmd (notUsed, interp, objc, objv)
    ClientData notUsed;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    int id;
    Tcl_HashEntry *entry;
    handler *h;
    char *event;

    if (objc != 4) {
        Tcl_WrongNumArgs (interp, 1, objv, "event id enableflag");
	return TCL_ERROR;
    }

    event = Tcl_GetStringFromObj (objv[1], NULL);
    if ((entry = Tcl_FindHashEntry (&handlers, event)) == NULL)
        return TCL_OK;
    if (Tcl_GetIntFromObj (interp, objv[2], &id) == TCL_ERROR)
        return TCL_ERROR;
    for (h = (handler *) Tcl_GetHashValue (entry); h != (handler *) NULL;
         h = h->next)
        if (h->id == id) {
            if (Tcl_GetIntFromObj (interp, objv[3], &h->enable) == TCL_ERROR)
                return TCL_ERROR;
            break;
        }
    if (h == (handler *) NULL) {
        Tcl_AppendResult (interp, "no handler ",
                          Tcl_GetStringFromObj (objv[2], NULL), " for event ",
                          event, (char *) NULL);
        return TCL_ERROR;
    }	
    return TCL_OK;
}

/*
 * n_removeCmd
 */

#ifdef PROTO_OK
int n_removeCmd (ClientData clientData, Tcl_Interp *interp,
                 int objc, Tcl_Obj *CONST objv[])
#else
int n_removeCmd (notUsed, interp, objc, objv)
    ClientData notUsed;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    int id;
    Tcl_HashEntry *entry;
    handler *h;
    char *event;

    if (objc != 3) {
        Tcl_WrongNumArgs (interp, 1, objv, "event id");
	return TCL_ERROR;
    }

    event = Tcl_GetStringFromObj (objv[1], NULL);
    if ((entry = Tcl_FindHashEntry (&handlers, event)) == NULL) {
        Tcl_AppendResult (interp, "no event type \"", event, "\"",
                          (char *) NULL);
        return TCL_ERROR;
    }
    if (Tcl_GetIntFromObj (interp, objv[2], &id) == TCL_ERROR)
        return TCL_ERROR;

#ifdef DEBUG
    fprintf (stderr, "noosa: removing handler %d for %s\n", id, event);
#endif

    for (h = (handler *) Tcl_GetHashValue (entry); h != (handler *) NULL;
         h = h->next)
        if (h->id == id) {
            if ((event_name != NULL) && (strcmp (event, event_name) == 0)) {
                /* Mark for later removal.  We can't remove here because
                   this removal is happening while handling an event of 
                   this type so we can ruin the event handler list. */
                h->remove = 1;
            } else
                list_remove (entry, h);
            break;
        }
    if (h == (handler *) NULL) {
        Tcl_AppendResult (interp, "no handler ",
                          Tcl_GetStringFromObj (objv[2], NULL), " for event ",
                          event, (char *) NULL);
        return TCL_ERROR;
    }
    return TCL_OK;
}

/*
 * n_event_paramsCmd
 */

#ifdef PROTO_OK
int n_event_paramsCmd (ClientData clientData, Tcl_Interp *interp,
                       int objc, Tcl_Obj *CONST objv[])
#else
int n_event_paramsCmd (notUsed, interp, objc, objv)
    ClientData notUsed;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    Tcl_HashEntry *entry;
    int isnew, i, len, eventlen;
    Tcl_Obj **objs;
    char *buf, *event;

    if (objc < 2) {
        Tcl_WrongNumArgs (interp, 1, objv, "event_name pnames...");
	return TCL_ERROR;
    }

    event = Tcl_GetStringFromObj (objv[1], &eventlen);
    entry = Tcl_CreateHashEntry (&params, event, &isnew);
    if (isnew) {
        objs = (Tcl_Obj **) Tcl_Alloc (sizeof (Tcl_Obj *) * (objc - 2));
        for (i = 2; i < objc; i++) {
            int arglen;
            char *arg = Tcl_GetStringFromObj (objv[i], &arglen);
            len = eventlen + arglen + 7;
            buf = Tcl_Alloc (len);
            sprintf (buf, "::n_%s::%s", event, arg);
            objs[i-2] = Tcl_NewStringObj (buf, len);
        }
        Tcl_SetHashValue (entry, objs);
    } else {
        Tcl_AppendResult (n_interp,
                          "already have event params for event \"",
                          event, "\"", (char *)NULL);
        return TCL_ERROR;
    }	
    return TCL_OK;
}

/*
 * n_sendbCmd
 */

#ifdef PROTO_OK
int n_sendbCmd (ClientData clientData, Tcl_Interp *interp,
                int objc, Tcl_Obj *CONST objv[])
#else
int n_sendbCmd (notUsed, interp, objc, objv)
    ClientData notUsed;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    sigset_t nosigsBuf, usr1sigBuf;
    char *msg, *pid;
    static Tcl_Obj *result, **nobjv;
    static Tcl_Obj *n_result = (Tcl_Obj *)NULL, *n_error = (Tcl_Obj *)NULL;
    static int nobjc = -1;
    static Obstack obj_obstk;

    if (objc != 3) {
        Tcl_WrongNumArgs (interp, 1, objv, "pid msg");
	return TCL_ERROR;
    }

    /* Get arguments */
    pid = Tcl_GetStringFromObj (objv[1], NULL);
    msg = Tcl_GetStringFromObj (objv[2], NULL);

    /* Fill the buffer */
#ifdef DEBUG
    fprintf (stderr, "noosa: command 'c %s'\n", msg);
#endif
    strcpy (snbuf, "c ");
    strcpy (snbuf + 2, msg);

    /* SIGUSR1 signals mean return values or errors */
    sigusr1 = sigusr1_event = 0;

    /* Get the child going again */
#ifdef DEBUG
    fprintf (stderr, "noosa: %d continuing child %s\n", getpid (), pid);
#endif
    if (n_cont_child (interp, pid) != TCL_OK)
	return TCL_ERROR;

    /* If not already signalled, wait for it */
#ifdef DEBUG
    fprintf (stderr, "noosa: waiting for response\n");
#endif

    if (sigemptyset (&nosigsBuf) == -1) {
	perror ("noosa sigemptyset nosigs");
	Tcl_Exit (1);
    }
    if (sigemptyset (&usr1sigBuf) == -1) {
	perror ("noosa sigemptyset usr1sig");
	Tcl_Exit (1);
    }
    if (sigaddset (&usr1sigBuf, SIGUSR1) == -1) {
	perror ("noosa sigaddset usr1sig");
	Tcl_Exit (1);
    }
    if (sigprocmask (SIG_BLOCK, &usr1sigBuf, 0) == -1) {
        perror ("noosa sigprocmask BLOCK");
        Tcl_Exit (1);
    }
    if ((!sigusr1) && (sigsuspend (&nosigsBuf) == -1) && (errno != EINTR)) {
	perror ("noosa pause");
	Tcl_Exit (1);
    }
    if (sigprocmask (SIG_UNBLOCK, &usr1sigBuf, 0) == -1) {
        perror ("noosa sigprocmask UNBLOCK");
        Tcl_Exit (1);
    }
    while (Tcl_DoOneEvent (TCL_ALL_EVENTS | TCL_DONT_WAIT))
	;

#ifdef DEBUG
    fputs ( "noosa: got response: ", stderr);
    print_mesg (snbuf + 1);
    fputc ('\n', stderr);
#endif

    /* Make return value list */
    if (snbuf[1] != '\0') {
        if (nobjc != -1) obstack_free (&obj_obstk, nobjv);
	else obstack_init (&obj_obstk);
        make_objs (snbuf + 1, &nobjc, &nobjv, &obj_obstk);
        result = Tcl_NewListObj (nobjc, nobjv);
    }

    /* Deal with the command response */
    if (snbuf[0] == 'r') {
	if (snbuf[1] == '\0')
	    /* No return value */
	    Tcl_SetVar2 (n_interp, "n", "result", "", TCL_GLOBAL_ONLY);
	else {
            /* Object for n_result variable name */
            if (n_result == (Tcl_Obj *)NULL)
                n_result = Tcl_NewStringObj ("n(result)", -1);
            Tcl_ObjSetVar2 (n_interp, n_result, (Tcl_Obj *) NULL,
                            result, TCL_GLOBAL_ONLY | TCL_PARSE_PART1);
        }
        Tcl_SetVar2 (n_interp, "n", "retstat", "0", TCL_GLOBAL_ONLY);
    } else {
	if (snbuf[0] == '?') {
	    /* Error return */
            if (n_error == (Tcl_Obj *)NULL)
                n_error = Tcl_NewStringObj ("n(error)", -1);
            Tcl_ObjSetVar2 (n_interp, n_error, (Tcl_Obj *) NULL,
                            result, TCL_GLOBAL_ONLY | TCL_PARSE_PART1);
	} else {
	    /* Bad return code */
	    Tcl_SetVar2 (n_interp, "n", "error", snbuf, TCL_GLOBAL_ONLY);
	}
	Tcl_SetVar2 (n_interp, "n", "retstat", "1", TCL_GLOBAL_ONLY);
    }

    /* SIGUSR1 signals mean events again */
    sigusr1 = 0;
    sigusr1_event = 1;

    return TCL_OK;
}


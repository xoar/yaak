/*
 * $Id: list.c,v 1.24 2013/12/05 21:34:43 profw Exp $
 * Copyright (c) 1994-1999 Anthony M. Sloane
 *
 * list.c
 * Module to provide rudimentary linked lists for Tcl.
 *
 * n_llist command:
 *  add ll elem		add elem to the front of ll
 *  foreach ll v cmd    as for foreach on regular lists
 *  revforeach ll v cmd like foreach except backwards from end
 *  free ll             deallocate a linked list
 *  head ll		return the head of the list, error if no elements
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

#ifndef USE_INTERP_ERRORLINE
#error USE_INTERP_ERRORLINE not defined
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tcl.h"
#include "list.h"

typedef struct llelem *ll;
struct llelem {
    char *data;
    ll next, prev;
};

static int init = 1;
static Tcl_HashTable table;

/*
 * strdup (for platforms that need it)
 */

#ifdef NEED_STRDUP
#ifdef PROTO_OK
char *strdup (char *str)
#else
char *strdup (str)
    char *str;
#endif
{
    char *cp = (char *) malloc (strlen(str) + 1);
    
    if (cp != NULL)
	strcpy (cp, str);
    return cp;
}
#else
extern char *strdup _ANSI_ARGS_ ((const char *));
#endif

/*
 * n_llistCmd
 */

#ifdef PROTO_OK
int n_llistCmd (ClientData clientData, Tcl_Interp *interp,
                int objc, Tcl_Obj *CONST objv[])
#else
int n_llistCmd (dummy, interp, argc, argv)
    ClientData dummy;		/* Not used. */
    Tcl_Interp *interp;		/* Current interpreter. */
    int argc;			/* Number of arguments. */
    char **argv;		/* Argument strings. */
#endif
{
    char c;
    int new, result = TCL_OK;
    Tcl_HashEntry *entry;
    ll l, m, val;
    
    if (argc < 3) {
	Tcl_AppendResult (interp, "wrong # args: should be \"", argv[0],
			  " option llistName ?arg ...?\"",
			  (char *) NULL);
	return TCL_ERROR;
    }
    
    if (init) {
	Tcl_InitHashTable (&table, TCL_STRING_KEYS);
	init = 0;
    }
    
    c = argv[1][0];
    
    /* Adding an element to new one, if it's new create it */
    if ((c == 'a') && (strcmp (argv[1], "add") == 0)) {
	
	if (argc != 4) {
	    Tcl_AppendResult (interp, "wrong # args: should be \"",
			      argv[0], " add llistName elem\"",
			      (char *) NULL);
	    return TCL_ERROR;
	}
	
	entry = Tcl_CreateHashEntry (&table, argv[2], &new);
	if (new) {
	    Tcl_SetHashValue (entry, 0);
	    val = (ll) 0;
	} else
	    val = (ll) Tcl_GetHashValue (entry);
	
	if ((l = (ll) malloc (sizeof (*l))) == (ll) NULL) {
	    fprintf (stderr,
		     "llist add: can't malloc new linked list\n");
	    Tcl_Exit (1);
	}
	l->data = strdup (argv[3]);
	l->next = val;
	if (val)
	    val->prev = l;
	Tcl_SetHashValue (entry, l);
	Tcl_ResetResult (interp);
	return TCL_OK;
	
	/* Looping through a list forwards */
    } else if ((c == 'f') && (strcmp (argv[1], "foreach") == 0)) {
	
	if (argc != 5) {
	    Tcl_AppendResult (interp, "wrong # args: should be \"",
			      argv[0],
			      " foreach llistName varName cmd\"",
			      (char *) NULL);
	    return TCL_ERROR;
	}
	
	entry = Tcl_FindHashEntry (&table, argv[2]);
	if (entry == (Tcl_HashEntry *) NULL) {
	    Tcl_ResetResult (interp);
	    return TCL_OK;
	} 
	for (l = (ll) Tcl_GetHashValue (entry); l != (ll) 0;
	     l = l->next) {
	    if (Tcl_SetVar (interp, argv[3], l->data, 0) == NULL) {
		Tcl_SetResult (interp,
			       "couldn't set loop variable",
			       TCL_STATIC);
		result = TCL_ERROR;
		break;
	    }
	    
	    result = Tcl_Eval (interp, argv[4]);
	    if (result != TCL_OK) {
		if (result == TCL_CONTINUE) {
		    result = TCL_OK;
		} else if (result == TCL_BREAK) {
		    result = TCL_OK;
		    break;
		} else if (result == TCL_ERROR) {
		    char msg[100];
		    sprintf (msg,
			     "\n    (\"ll foreach\" body line %d)",
			     interp->errorLine);
		    Tcl_AddErrorInfo(interp, msg);
		    break;
		} else {
		    break;
		}
	    }
	}
	if (result == TCL_OK) {
	    Tcl_ResetResult (interp);
	}
	return result;
	
	/* Looping through a list backwards */
    } else if ((c == 'r') && (strcmp (argv[1], "revforeach") == 0)) {
	
	if (argc != 5) {
	    Tcl_AppendResult (interp, "wrong # args: should be \"",
			      argv[0],
			      " revforeach llistName varName cmd\"",
			      (char *) NULL);
	    return TCL_ERROR;
	}
	
	entry = Tcl_FindHashEntry (&table, argv[2]);
	if (entry == (Tcl_HashEntry *) NULL) {
	    Tcl_ResetResult (interp);
	    return TCL_OK;
	} 
	for (l = m = (ll) Tcl_GetHashValue (entry); m != (ll) 0;
	     l = m, m = m->next)
	    ;
	for (; l != (ll) 0; l = l->prev) {
	    if (Tcl_SetVar (interp, argv[3], l->data, 0) == NULL) {
		Tcl_SetResult (interp,
			       "couldn't set loop variable",
			       TCL_STATIC);
		result = TCL_ERROR;
		break;
	    }
	    
	    result = Tcl_Eval (interp, argv[4]);
	    if (result != TCL_OK) {
		if (result == TCL_CONTINUE) {
		    result = TCL_OK;
		} else if (result == TCL_BREAK) {
		    result = TCL_OK;
		    break;
		} else if (result == TCL_ERROR) {
		    char msg[100];
		    sprintf (msg,
			     "\n    (\"ll revforeach\" body line %d)",
			     interp->errorLine);
		    Tcl_AddErrorInfo(interp, msg);
		    break;
		} else {
		    break;
		}
	    }
	}
	if (result == TCL_OK) {
	    Tcl_ResetResult (interp);
	}
	return result;
	
	/* Return the head */
    } else if ((c == 'h') && (strcmp (argv[1], "head") == 0)) {
	
	if (argc != 3) {
	    Tcl_AppendResult (interp, "wrong # args: should be \"",
			      argv[0], " head llistName\"",
			      (char *) NULL);
	    return TCL_ERROR;
	}
	
	entry = Tcl_FindHashEntry (&table, argv[2]);
	if (entry == (Tcl_HashEntry *) NULL) {
	empty_error:
	    Tcl_AppendResult (interp, "no elements in llist ",
			      argv[2], (char *) NULL);
	    return TCL_ERROR;
	} else {
	    l = (ll) Tcl_GetHashValue (entry);
	    if (l == (ll) 0)
		goto empty_error;
	    else
		Tcl_SetResult (interp, l->data, TCL_VOLATILE);
	}
	return TCL_OK;
	
	/* Freeing a list */
    } else if ((c == 'f') && (strcmp (argv[1], "free") == 0)) {
	
	if (argc != 3) {
	    Tcl_AppendResult (interp, "wrong # args: should be \"",
			      argv[0], " free llistName\"",
			      (char *) NULL);
	    return TCL_ERROR;
	}
	
	entry = Tcl_FindHashEntry (&table, argv[2]);
	if (entry == (Tcl_HashEntry *) NULL) {
	    Tcl_ResetResult (interp);
	    return TCL_OK;
	} 
	l = (ll) Tcl_GetHashValue (entry);
	if (l != (ll) 0) {
	    for (m = l, l = l->next; l != (ll) 0;
		 m = l, l = l->next)
		free (m);
	    free (m);
	}
	Tcl_SetHashValue (entry, 0);
	Tcl_ResetResult (interp);
	return TCL_OK;
	
    } else {
	Tcl_AppendResult (interp, "bad option \"", argv[1],
			  "\": should be alloc, add, foreach, or free",
			  (char *) NULL);
	return TCL_ERROR;
    }
}

/*
 * $Id: handlers.c,v 2.11 2007/02/21 17:12:29 profw Exp $
 * Copyright (c) 1997-1999 Anthony M. Sloane
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
#include <string.h>
#include "tcl.h"
#include "tk.h"
#include "noosa.h"
#include "obstack.h"

static Tcl_HashTable handlers;

/*
 * Token 
 */

typedef struct token {
    char *type, *lexeme;
    int linebeg, cumcolbeg, lineend, cumcolend, len, val, code;
} token;
static Obstack token_obstk;
static token *tokens;
static int ntokens = 0;
static int token_init = 1;

#ifdef PROTO_OK
int n_token_initCmd (ClientData clientData, Tcl_Interp *interp,
                     int objc, Tcl_Obj *CONST objv[])
#else
int n_token_initCmd (notUsed, interp, objc, objv)
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

    token_init = 1;
    return TCL_OK;
}

#ifdef PROTO_OK
static void Token_token (int parc, param *parv)
#else
static void Token_token (parc, parv)
    int parc;
    param *parv;
#endif
{
    token *tp;

#ifdef DEBUG
    fprintf (stderr, "handler: Token_token\n");
#endif

    if (token_init) {
        if (ntokens == 0) {
	    obstack_init (&token_obstk); 
        } else {
	    if (tokens == NULL)
	        tokens = (token *) obstack_finish (&token_obstk);	
	    obstack_free (&token_obstk, tokens);
	    ntokens = 0;
        }
        tokens = NULL;
        token_init = 0;
    }

    obstack_blank (&token_obstk, sizeof (token));
    tp = ((token *) obstack_base (&token_obstk)) + ntokens;
    tp->type = strdup (parv[2].s);
    tp->linebeg = parv[3].i;
    tp->cumcolbeg = parv[4].i;
    tp->lineend = parv[6].i;
    tp->cumcolend = parv[8].i;
    tp->lexeme = strdup (parv[9].s);
    tp->len = parv[10].i;
    tp->val = parv[11].i;
    tp->code = parv[12].i;
    ntokens++;

#ifdef DEBUG
    fprintf (stderr, "handler: Token_token finished\n");
#endif
}

#ifdef PROTO_OK
static void Token_finit (int parc, param *parv)
#else
static void Token_finit (parc, parv)
    int parc;
    param *parv;
#endif
{
    token *tp;

#ifdef DEBUG
    fprintf (stderr, "handler: Token_finit\n");
#endif

    if (!token_init && (tokens == NULL)) {
	obstack_blank (&token_obstk, sizeof (token));
	tp = ((token *) obstack_base (&token_obstk)) + ntokens;
	tp->type = NULL;
	tokens = (token *) obstack_finish (&token_obstk);
    }

#ifdef DEBUG
    fprintf (stderr, "handler: Token_finit finished\n");
#endif
}

/*
 * n_find_tokens
 * FIXME: assumes < 10000 chars per line.
 */

#define TO_COORD(l,c) (((l)*10000)+c)

#ifdef PROTO_OK
int n_find_tokensCmd (ClientData clientData, Tcl_Interp *interp,
                      int objc, Tcl_Obj *CONST objv[])
#else
int n_find_tokensCmd (notUsed, interp, objc, objv)
    ClientData notUsed;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    int sl, sc, s, el, ec, e, ts, te, found = 0, head = 1;
    char *buf, cbuf[30];
    token *tp;
    Tcl_Obj *res;

    if (objc != 5) {
        Tcl_WrongNumArgs (interp, 1, objv,
                          "startline startcol endline endcol");
	return TCL_ERROR;
    }	

    if (tokens == NULL) {
	Tcl_SetResult (interp, "No tokens available\n", TCL_STATIC);
	return TCL_OK;
    }

    if (Tcl_GetIntFromObj (interp, objv[1], &sl) == TCL_ERROR)
        return TCL_ERROR;
    if (Tcl_GetIntFromObj (interp, objv[2], &sc) == TCL_ERROR)
        return TCL_ERROR;
    s = TO_COORD (sl, sc);

    if (Tcl_GetIntFromObj (interp, objv[3], &el) == TCL_ERROR)
        return TCL_ERROR;
    if (Tcl_GetIntFromObj (interp, objv[4], &ec) == TCL_ERROR)
        return TCL_ERROR;
    e = TO_COORD (el, ec);
    
    for (tp = tokens; tp->type != NULL; tp++) {
	ts = TO_COORD (tp->linebeg, tp->cumcolbeg);
	te = TO_COORD (tp->lineend, tp->cumcolend - 1);
	if (((s >= ts) && (s <= te)) || ((e >= ts) && (e <= te)) ||
	    ((s <= ts) && (e >= ts)) || ((s <= te) && (e >= te))) {
	    if (!found) {
                Tcl_SetResult (interp, "\n      Coordinate  Code  Value  Length  Lexeme (Token Name)\n", TCL_STATIC);
                found = 1;
            }

            if (tp->len == 0)
                sprintf (cbuf, "%d,%d", tp->linebeg, tp->cumcolbeg);
            else 
                sprintf (cbuf, "%d,%d-%d,%d", tp->linebeg, tp->cumcolbeg,
                         tp->lineend, tp->cumcolend);

            buf = Tcl_Alloc (1+15+1+4+1+6+1+6+5+strlen(tp->lexeme)+1+1);
	    sprintf (buf, " %15s %4d %6d %6d    '%s'", cbuf, tp->code,
		     tp->val, tp->len, tp->lexeme, tp->type);
	    Tcl_AppendResult (interp, buf, (char *) NULL);
            Tcl_Free (buf);

            if (*tp->type == '\0')
                Tcl_AppendResult (interp, "\n", (char *) NULL);
            else
                Tcl_AppendResult (interp, " (", tp->type, ")\n",
                                  (char *) NULL);
	}
    }
    if (!found)
	Tcl_SetResult (interp, "None\n", TCL_STATIC);
    return TCL_OK;
}

/*
 * Phrase
 */

typedef struct phrase {
    int prod, uses, linebeg, colbeg, lineend, colend, involved;
} phrase;
static Obstack phrase_obstk;
static phrase *phrases;
static int nphrases = 0, nprods = 0;
static char **prodtext;
static int phrase_init = 1;

#ifdef PROTO_OK
int n_phrase_initCmd (ClientData clientData, Tcl_Interp *interp,
                     int objc, Tcl_Obj *CONST objv[])
#else
int n_phrase_initCmd (notUsed, interp, objc, objv)
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

    phrase_init = 1;
    return TCL_OK;
}

#ifdef PROTO_OK
static void Phrase_production (int parc, param *parv)
#else
static void Phrase_production (parc, parv)
    int parc;
    param *parv;
#endif
{
    phrase *pp;

#ifdef DEBUG
    fprintf (stderr, "handler: Phrase_production\n");
#endif

    if (phrase_init) {
        if (nphrases == 0)
	    obstack_init (&phrase_obstk); 
        else {
	    if (phrases == NULL)
	        phrases = (phrase *) obstack_finish (&phrase_obstk);
	    obstack_free (&phrase_obstk, phrases);
	    nphrases = 0;
        }
        phrases = NULL;
        phrase_init = 0;
    }

    obstack_blank (&phrase_obstk, sizeof (phrase));
    pp = ((phrase *) obstack_base (&phrase_obstk)) + nphrases;
    pp->prod = parv[2].i;
    if (pp->prod > nprods)
	nprods = pp->prod;
    pp->uses = parv[3].i;
    pp->linebeg = parv[4].i;
    pp->colbeg = parv[5].i;
    pp->lineend = parv[6].i;
    pp->colend = parv[7].i;
    nphrases++;

#ifdef DEBUG
    fprintf (stderr, "handler: Phrase_production finished\n");
#endif
}

#ifdef PROTO_OK
static void Phrase_finit (int parc, param *parv)
#else
static void Phrase_finit (parc, parv)
    int parc;
    param *parv;
#endif
{
    int i;

#ifdef DEBUG
    fprintf (stderr, "handler: Phrase_finit\n");
#endif

    if (!phrase_init && (phrases == NULL)) {
	phrases = (phrase *) obstack_finish (&phrase_obstk);
	prodtext = (char **) obstack_alloc (&phrase_obstk,
					    (nprods + 1) * sizeof (char *));
	for (i = 0; i <= nprods; i++)
	    prodtext[i] = NULL;
    }

#ifdef DEBUG
    fprintf (stderr, "handler: Phrase_finit finished\n");
#endif
}

/*
 * n_find_phrases
 */

#ifdef PROTO_OK
int n_find_phrasesCmd (ClientData clientData, Tcl_Interp *interp,
                       int objc, Tcl_Obj *CONST objv[])
#else
int n_find_phrasesCmd (notUsed, interp, objc, objv)
    ClientData notUsed;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST objv[];
#endif
{
    int l, c, n, recnum, found = 0;
    phrase *pp;
    char *rp, cbuf[256], buf[500];
    static char *stack = NULL;

    if (objc != 3) {
        Tcl_WrongNumArgs (interp, 1, objv, "line col");
	return TCL_ERROR;
    }	
    if (Tcl_GetIntFromObj (interp, objv[1], &l) == TCL_ERROR)
        return TCL_ERROR;
    if (Tcl_GetIntFromObj (interp, objv[2], &c) == TCL_ERROR)
        return TCL_ERROR;

    if (stack != NULL)
	obstack_free (&phrase_obstk, stack);	
 
    for (n = nphrases, pp = phrases + nphrases - 1; n != 0; n--, pp--)
	if ((((l == pp->linebeg) && (c >= pp->colbeg)) || (l > pp->linebeg)) &&
	    (((l == pp->lineend) && (c <= pp->colend)) || (l < pp->lineend))) {
	    if (prodtext[pp->prod] == NULL) {
		sprintf (cbuf, "n_send get_conc_prod %d", pp->prod);
		if (Tcl_Eval (interp, cbuf) == TCL_ERROR) {
		    Tcl_AppendResult (interp, "error evaluating \"",
				      cbuf, "\"", (char *)NULL);
		    return TCL_ERROR;
		}
		/* Store, removing the quotes */
		rp = prodtext[pp->prod] =
                    strdup (Tcl_GetStringResult (interp) + 1);
		rp[strlen (rp) - 1] = '\0';
	    }
            if ((pp->linebeg == pp->lineend) && (pp->colbeg == pp->colend))
                sprintf (cbuf, "%d,%d", pp->linebeg, pp->colbeg);
            else
                sprintf (cbuf, "%d,%d-%d,%d", pp->linebeg, pp->colbeg,
                         pp->lineend, pp->colend);
	    sprintf (buf, "\n %15s %s", cbuf, prodtext[pp->prod]);
            obstack_grow (&phrase_obstk, buf, strlen(buf));
	    found = 1;
	}

    if (found) {
 	obstack_1grow (&phrase_obstk, '\n');
 	obstack_1grow (&phrase_obstk, '\0');
 	stack = (char *) obstack_finish (&phrase_obstk);
 	Tcl_SetResult (interp, stack, TCL_VOLATILE);
    } else
	Tcl_SetResult (interp, " None\n", TCL_STATIC);
    return TCL_OK;
}

static chandler chandler_table[] = {
    { "Token_finit", Token_finit },
    { "Token_token", Token_token },
    { "Phrase_finit", Phrase_finit },
    { "Phrase_production", Phrase_production },
    { (char *)NULL, 0 }
};

/*
 * n_init_handlers
 */

void n_init_handlers ()
{
    chandler *hp;
    Tcl_HashEntry *entry;
    int isnew;

    Tcl_InitHashTable (&handlers, TCL_STRING_KEYS);
    for (hp = chandler_table; hp->name != (char *)NULL; hp++) {
	entry = Tcl_CreateHashEntry (&handlers, hp->name, &isnew);
	Tcl_SetHashValue (entry, hp->func);
    }
}

/*
 * n_get_handler
 */

#ifdef PROTO_OK
chandler_func n_get_handler (char *name)
#else
chandler_func n_get_handler (name)
    char *name;
#endif
{
    Tcl_HashEntry *entry;

    entry = Tcl_FindHashEntry (&handlers, name);
    if (entry == NULL) {
	fprintf (stderr, "noosa: no handler called '%s'\n", name);
	Tcl_Exit (1);
    }
    return (chandler_func) Tcl_GetHashValue (entry);
}


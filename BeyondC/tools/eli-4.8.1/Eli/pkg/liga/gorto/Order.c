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
/* $Id: Order.c,v 4.9 1999/07/26 08:38:09 mjung Exp $ */
static char rcs_id[]= "$Id: Order.c,v 4.9 1999/07/26 08:38:09 mjung Exp $";

/*======================================================================*
 *									*
 *	FILE:		Main/Order.c					*
 *									*
 *	DESCRIPTION:	Interface to the order implementation		*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Prod.h"
#include "Symb.h"
#include "Visit.h"
#include "Main.h"
#include "Popup.h"
#include "../middle/order/option.h"

#include <stdio.h>
#include <X11/StringDefs.h>


/************************************************************************
 *                        Global order variables			*
 ************************************************************************/

PUBLIC FILE *In=(FILE *) NULL, 
    *Out=(FILE *) NULL, 
    *ProtocolFile=(FILE *) NULL, 
    *LCL=(FILE *) NULL,
    *BuProdFile=(FILE *) NULL;

EXTERN bool	ARRANGE;
PUBLIC AttrEval	ISexp;
/* PUBLIC int	graphstate; */ 
EXTERN int	graphstate;

PUBLIC Boolean Cyclic, DepRemoved = False;
PUBLIC short graphstate_hint;
PUBLIC STATE state;

#ifdef SHOW_TIMES
#include <sys/time.h>
#include <sys/resource.h>

PUBLIC FILE *ClockProt=stdout;
PUBLIC struct timeval old_utime;
#endif


/************************************************************************
 *			    ResetVisitSequence				*
 ************************************************************************/

/* Removes all visit-sequence elements in the given visit-sequence that
 * are not of class VSCOND.
 */

PRIVATE void ResetVisitSequence (prod)
	PRODENTRY *prod;
{
	VSPTR current, next;

	current        = prod->visitseq;
	prod->visitseq = NULL;

	for (; current != NULL; current = next)
	{
		next = current->next;
		if (current->vscls == VSCOND)
		{
			current->next  = prod->visitseq;
			prod->visitseq = current;
		}
		else
			XtFree ((char *)current);
	}
}


/************************************************************************
 *				 SetState				*
 ************************************************************************/

/* Sets the current state of this tool and displays the state in the
 * main window.
 */

PRIVATE String *StateNames[] = {
	& Res.str_direct_rules,
	& Res.str_direct_symbols,
	& Res.str_options,
	& Res.str_transitive,
	& Res.str_induced,
	& Res.str_arrange_option,
	& Res.str_arrange,
	& Res.str_partition,
	& Res.str_partitioned,
	& Res.str_visitseq,
	& Res.str_lifetime,
	& Res.str_info,
	& Res.str_hide,
	& Res.str_unhide,
	& Res.str_direct_dpy,
	& Res.str_transitive_dpy,
	& Res.str_induced_dpy,
	& Res.str_arranged_dpy,
	& Res.str_part_dpy,
	& Res.str_vs_dpy,
	& Res.str_idl,
	& Res.str_output,
	& Res.str_finish,
};

PUBLIC void SetState (newstate)
	STATE newstate;
{
	Arg args[1];

	state = newstate;
	XtSetArg (args[0], XtNlabel, * StateNames[(int) state]); 
	XtSetValues (StateLabel, args, 1);
}


/************************************************************************
 *			       start & stop				*
 ************************************************************************/

#ifdef SHOW_TIMES

PRIVATE void start()
{
	struct rusage usg;

	getrusage (RUSAGE_SELF, &usg);
	old_utime = usg.ru_utime;
}

PRIVATE void stop (name)
	String name;
{
	struct rusage usg;
	double diff;

	getrusage (RUSAGE_SELF, &usg);
	diff = usg.ru_utime.tv_sec - old_utime.tv_sec;
	diff += usg.ru_utime.tv_usec / 1000000.0;
	diff -= old_utime.tv_usec    / 1000000.0;
	fprintf (ClockProt, "%-25s: %8.3f sec\n", name, diff);
}

#define PERFORM(call,name)	{ start(); call; stop(name); }
#else
#define PERFORM(call,name)	call
#endif


/************************************************************************
 *				  DoWork				*
 ************************************************************************/

/* Starts the next step of the order computation, depending on the
 * current value of <state>. It is registered as a XtWorkProc in the 
 * X Toolkit, so it will be called automatically.
 */

/*ARGSUSED*/
PRIVATE Boolean DoWork (client_data)
	XtPointer client_data;
{
	static STATE after_additions;

      /* Flush the X-output before doing the work */
	XSync (dpy, False);

      /* Perform the actual work */
	switch (state)
	{
	case DirectRules:
		graphstate = DIRECT;
		graphstate_hint = T_DIR;
		PERFORM (cons_init_dp(ISexp), "init dp");
		if (TREE_BOTTOM_UP && TREE_COMPLETE)
		{ fprintf (stderr,
			   "BOTTOMUP computations contradict TREE_COMPLETE option");
		  exit(1);
		}
		SetState (DirectSymbols);
		break;

	case DirectSymbols:
		PERFORM (cons_init_ds(), "init ds");
		SetState (ReadOrderOptions);
		break;
		
	case ReadOrderOptions:
		ArrangeComment ("Reason unknown");
		PERFORM (check_cycle(),      "check direct cycles");
		after_additions = DpyDirectGraphs;
		SetState (Cyclic ? ReftabAdditions : TransitiveGraphs);
		break;

	case TransitiveGraphs:
		graphstate = TRANSITIVE;
		graphstate_hint = T_TRAN;
		PERFORM (transitiveclosure(), "transitive graphs");
		PERFORM (check_cycle(),       "check transitive cycles");
		after_additions = DpyTransitiveGraphs;
		SetState (Cyclic ? ReftabAdditions : InducedGraphs);
		break;

	case InducedGraphs:
		graphstate = INDUCED;
		graphstate_hint = T_IND;
		PERFORM (transitiveclosure(), "induced graphs");
		PERFORM (check_cycle(),       "check induced cycles");
		GenTreeDeps (ISexp);
		PERFORM (transitiveclosure(), "induced graphs");
		PERFORM (check_cycle(),       "check induced cycles");
		if (TREE_BOTTOM_UP)
		{ InduceBUAttrs ();
		  PERFORM (transitiveclosure(), "induced graphs");
		  PERFORM (check_cycle(),       "check induced cycles");
		  BUPartition ();
		  InduceBUAttrs ();
		  PERFORM (transitiveclosure(), "induced graphs");
		  PERFORM (check_cycle(),       "check induced cycles");		  
		}
		after_additions = DpyInducedGraphs;
		SetState (Cyclic ? ReftabAdditions : ArrangeOptions);
		break;

	case ArrangeOptions:
		if (ARRANGE)
		{
			ARRANGE = False;
			PERFORM (set_arrangeOption(), "set arrange Options");
		}
		if (ArrangeListEmpty ())
			SetState (Partitions);
		else
		{
			PERFORM (IntroduceArrangeList(),
				 "introduce arrange list");
			SetState (ArrangedGraphs);
		}
		break;

	case ArrangedGraphs:
		graphstate = ARRANGED;
		graphstate_hint = T_ARR;
		PERFORM (transitiveclosure(), "arranged graphs"); 
		PERFORM (check_cycle(),       "check arranged cycles");
		after_additions = DpyArrangedGraphs;
		SetState (Cyclic ? ReftabAdditions : Partitions);
		break;

	case Partitions:
		graphstate = PARTITIONED;
		graphstate_hint = T_PART;
		PERFORM (partit(), "partitions");
		SetState (PartitionedGraphs);
		break;

	case PartitionedGraphs:
		PERFORM (transitiveclosure(), "partitioned graphs");
		PERFORM (check_cycle(),       "check partitioned cycles");
		after_additions = DpyPartitionedGraphs;
		SetState (Cyclic ? ReftabAdditions : VisitSequences);
		break;

	case VisitSequences:
		PERFORM (visitsequence(), "visit sequences");
		if (TREE_BOTTOM_UP)
		{ BUChkProds ();
		  ChkBUInGenTrees ();
		}
		SetState (Lifetimes);
		break;

	case Lifetimes:
		PERFORM (VisitComputeLifetimes(), "lifetimes");
		after_additions = DpyVisitSequences;
		SetState (ReftabAdditions);
		break;

	case ReftabAdditions:
		PERFORM (ComputeRefTabAdditions(), "ref_tab additions");
		SetState (after_additions);
		break;

	case DpyDirectGraphs:
	case DpyTransitiveGraphs:
	case DpyInducedGraphs:
	case DpyArrangedGraphs:
	case DpyPartitionedGraphs:
	case DpyVisitSequences:
		SetListMasks();
#ifdef SHOW_TIMES
		fprintf (ClockProt, "\n");
#endif
		return (True);

	case ConstructOutput:
		PERFORM (write_dataStruct(), "construct output");
		SetState (Output);
		break;

	case Output:
		if (Out != (FILE *) NULL) 
			PERFORM (ligaout(Out,ISexp), "ligaout");
		PERFORM (WriteArrangeList(), "lcl output");
#ifdef SHOW_TIMES
		fprintf (ClockProt, "\n");
#endif
		exit (0);
	case Finish:
		exit (0);
	case HideAttribute:
	case UnHideAttribute:
	break;
	}
	return (False);
}


/************************************************************************
 *				CallOrder				*
 ************************************************************************/

/* Initiates the whole order computation.
 */

PUBLIC void CallOrder ()
{
      /* Register the XtWorkProc <DoWork> to do the actual work */
	DepRemoved = False;
	SetState (DirectRules);
	(void) XtAppAddWorkProc (app_context, DoWork, (XtPointer) NULL);
}


/************************************************************************
 *			       RecomputeCB				*
 ************************************************************************/

/* Callback of the <recompute> menu item.
 */

/*ARGSUSED*/
PUBLIC void RecomputeCB (w, client_data, call_data)
        Widget  w;
        XtPointer client_data;
        XtPointer call_data;
{
	int		i;
	SYMBENTRY	*symb;
	PRODENTRY	*prod;
	ATTRENTRY	*ae;

      /* Check for cyclic induced graphs */
	if ((int)(state) <= (int)(DpyInducedGraphs))
	{
		Message (0, Res.str_no_recomp);
		return;
	}
	
      /* Close all windows */
	ProdCloseAllCB  ((Widget) NULL, (XtPointer) NULL, (XtPointer) NULL);
	SymbCloseAllCB  ((Widget) NULL, (XtPointer) NULL, (XtPointer) NULL);
	VisitCloseAllCB ((Widget) NULL, (XtPointer) NULL, (XtPointer) NULL);

      /* Remove the old dependencies */
	for (i=0; i<=max_entry; i++)
		if (ref_tab[i].etag == SYMB)
		{
			SymbRemoveDependencies (symb = & SE(i),
					DepRemoved ? (T_ARR|T_PART) : T_PART);
			symb->state &= S_CHANGED | S_FORCED;
			symb->part_num = 0;
		}
		else if (ref_tab[i].etag == PROD)
		{
			ProdRemoveDependencies (prod = & PE(i),
					DepRemoved ? (T_ARR|T_PART) : T_PART);
			prod->state &= S_CHANGED;
			ResetVisitSequence (prod);
		}
		else if (ref_tab[i].etag == ATTR)
		{
			ae = & AE(i);
/* component removed	ae->early = 0; */
			ae->part  = 0;
			ae->state &= ~A_CRITICAL;
		}

      /* Register the XtWorkProc <DoWork> to do the actual work */
	SetState (ArrangeOptions);
	DepRemoved = False;
	(void) XtAppAddWorkProc (app_context, DoWork, (XtPointer) NULL);
}


/************************************************************************
 *			   UpdateVisitSequence				*
 ************************************************************************/

PUBLIC void UpdateVisitSequence (prod)
	PRODENTRY *prod;
{
	int pid = prod->prod_def->did;

	ResetVisitSequence (prod);	/* reset visit-sequence */
	graphstate_hint = T_ARR;	/* set hint for ruletransitive() */
	ruletransitive (pid);		/* transitive closure of dp */
	rulevisitsequence (pid);	/* new visit-sequence */
	VisitUpdateProdLifes (prod);	/* new attribute lifetimes */
	RedisplayGraphOfDid (pid);	/* initiate redisplay */
}


/************************************************************************
 *				  QuitCB				*
 ************************************************************************/

/* This is the callback of the quit menu item in the main menu.
 */

/*ARGSUSED*/
PUBLIC void CtlQuitCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
      /* Register the XtWorkProc <DoWork> to do the actual work */
	if (Out != (FILE *) NULL)
		SetState (ConstructOutput);
	else
		SetState (Output);
	(void) XtAppAddWorkProc (app_context, DoWork, (XtPointer) NULL);
}

PUBLIC void QuitCB (w, client_data, call_data)
	Widget	w;
	XtPointer	client_data;
	XtPointer	call_data;
{
      /* Register the XtWorkProc <DoWork> to do the actual work */
	SetState (Finish);
	(void) XtAppAddWorkProc (app_context, DoWork, (XtPointer) NULL);
}

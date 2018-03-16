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
/* $Id: SymbAttrs.c,v 4.3 1998/04/28 14:08:55 ludi Exp $ */
static char rcs_id[]= "$Id: SymbAttrs.c,v 4.3 1998/04/28 14:08:55 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Symb/SymbAttrs.c				*
 *									*
 *	CONTENTS:	Routines dealing with the attribute list of	*
 *			symbols, which represents the current partition	*
 *			of such an symbol				*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

#include "Misc.h"
#include "Prod.h"
#include "Symb.h"
#include "Popup.h"
#include "Main.h"

PRIVATE char Comment[200];


/************************************************************************
 *			         AttrAfter				*
 ************************************************************************/

/* This is the sorting criterium for the attributes in a symbol graph. It
 * returns a boolean value inducating wether <a2> should appear after <a1>.
 */

PUBLIC Boolean AttrAfter (a1, a2)
	ATTRENTRY *a1, *a2;
{
      /* Different partitions: use order of partition numbers */
	if (a1->part != a2->part)
		return (a1->part < a2->part);

      /* Same partitions but different class: 
	 means this symbol is _not_ partitioned! */
	else if (a1->attr_def->class != a2->attr_def->class)
		return (a2->attr_def->class < a1->attr_def->class);

      /* Same partitions and classes: use lexicographic order */
	else
		return (strcmp (a1->attr_def->name, a2->attr_def->name) < 0);
}


/************************************************************************
 *			  SymbRecomputePartition			*
 ************************************************************************/

/* Performs all steps necessary to recompute the partition of the given
 * symbol <symb>. Includes the steps necessary to update the displayed
 * graphs.
 */

PUBLIC void SymbRecomputePartition (symb)
	SYMBENTRY *symb;
{
	SLNODE		*nd;
	PRODENTRY	*prod;
	int		last_pid = 0;

      /* Recompute partition and ref_tab additions */
	UpdatePartition       (symb);	/* Perform partial recomputation */
	SymbUpdateState       (symb);	/* Update symbols state label */
	ProdSortAttributes    (symb);	/* Build linked attribute list */
	SymbMarkCriticalPath  (symb);	/* Mark critical attributes */
	ProdComputeAttrSpaces (symb);	/* Compute vertical dependency spaces */
	ProdComputeAttrSizes  (symb);	/* Compute attribute widths */
	ProdComputeSymbolSize (symb);	/* Compute size of drawn symbol */

      /* Loop over all productions containing this symbol */
	for (nd = symb->hddown; nd != NULL; last_pid = nd->pid, nd = nd->down)
	{
		if (nd->pid == last_pid) continue;

		prod = & PE(nd->pid);
		ProdComputeSize (prod);	/* Recompute productions size */
		ProdResizeWindow(prod);	/* Resize production window */
	}

      /* Redisplay the symbols window */
	InitSAR (symb);
	RedisplayGraphOfDid (symb->symb_def->did);
}


/************************************************************************
 *				 MoveAttr				*
 ************************************************************************/

/* Moves an attribute instance in a symbol.
 */

PUBLIC void MoveAttr (symb, from, to)
	SYMBENTRY	*symb;
	ATTRENTRY	*from, *to;
{
	ATTRENTRY *ae;

      /* Add the arrange comment */
	sprintf (Comment, "Move of attribute %s.%s",
			  symb->symb_def->dname, from->attr_def->name);
	ArrangeComment (Comment);

      /* Delete any arranged partition constraints for this attribute */
	UnarrangeAttr (from);

      /* Find the beginning of the target partitioned attribute set */
	for (ae = to; ae != NULL && CLASS(ae) == CLASS(to); ) ae=ae->last;

      /* Search a critical attribute before the target partition */
	while (ae != NULL && CLASS(ae) != CLASS(to) && !(ae->state&A_CRITICAL))
		ae = ae->last;

      /* Arrange the moved attribute after that critical attribute */
	if (ae)
	{
		if (symb->ds[ae->pos][from->pos] &&
		    !(symb->ds[ae->pos][from->pos] & T_PART))
		{
			Message (symb->symb_def->did, Res.cycle_msg);
			return;
		}
		MakeArrangeNode (symb->symb_def->did, 
				 (SLNODE *) NULL, (SLNODE *) NULL,
				 ae->attr_def->did, from->attr_def->did, True);
	}

      /* Find the end of the target partitioned attribute set */
	for (ae = to; ae != NULL && CLASS(ae) == CLASS(to); ) ae = ae->next;

      /* Search a critical attribute after the target partition */
	while (ae != NULL && CLASS(ae) != CLASS(to) && !(ae->state&A_CRITICAL))
		ae = ae->next;

      /* Arrange the moved attribute before that critical attribute */
	if (ae)
	{
		if (symb->ds[from->pos][ae->pos] &&
		    !(symb->ds[from->pos][ae->pos] & T_PART))
		{
			Message (symb->symb_def->did, Res.cycle_msg);
			return;
		}
		MakeArrangeNode (symb->symb_def->did,
				 (SLNODE *) NULL, (SLNODE *) NULL,
				 from->attr_def->did, ae->attr_def->did, True);
	}
}


/************************************************************************
 *			   AppendFrontPartition				*
 ************************************************************************/

PUBLIC void AppendFrontPartition (symb, content, before)
	SYMBENTRY	*symb;
	ATTRENTRY	*content, *before;
{
      /* Add the arrange comment */
	sprintf (Comment, "Prepend partition for symbol %s containing %s",
		  symb->symb_def->dname, content->attr_def->name);
	ArrangeComment (Comment);

      /* Delete any arranged partition constraints for this attribute */
	UnarrangeAttr (content);

      /* Introduce arrange options */
	if (symb->ds[content->pos][before->pos] &&
	    !(symb->ds[content->pos][before->pos] & T_PART))
		Message (symb->symb_def->did, Res.cycle_msg);
	else
		MakeArrangeNode (symb->symb_def->did,
			 (SLNODE *) NULL, (SLNODE *) NULL,
			 content->attr_def->did, before->attr_def->did, True);
}


/************************************************************************
 *			   AppendRearPartition				*
 ************************************************************************/

PUBLIC void AppendRearPartition (symb, content, after)
	SYMBENTRY	*symb;
	ATTRENTRY	*content, *after;
{
      /* Add the arrange comment */
	sprintf (Comment, "Append partition for symbol %s containing %s",
		  symb->symb_def->dname, content->attr_def->name);
	ArrangeComment (Comment);

      /* Delete any arranged partition constraints for this attribute */
	UnarrangeAttr (content);

      /* Introduce arrange options */
	if (symb->ds[after->pos][content->pos] &&
	    !(symb->ds[after->pos][content->pos] & T_PART))
		Message (symb->symb_def->did, Res.cycle_msg);
	else
		MakeArrangeNode (symb->symb_def->did,
			 (SLNODE *) NULL, (SLNODE *) NULL,
			 after->attr_def->did, content->attr_def->did, True);
}


/************************************************************************
 *			       PerformSplit				*
 ************************************************************************/

PUBLIC void PerformSplit (symb, with, after, before)
	SYMBENTRY	*symb;
	ATTRENTRY	*with, *after, *before;
{
      /* Test for introduction of cycles by the second arrande node */
	if (symb->ds[with->pos][before->pos] &&
	    !(symb->ds[with->pos][before->pos] & T_PART))
	{
		Message (symb->symb_def->did, Res.cycle_msg);
		return;
	}

      /* Add the arrange comment */
	sprintf (Comment, "Split partition of %s with %s between %s and %s",
		  symb->symb_def->dname, with->attr_def->name, 
		  after->attr_def->name, before->attr_def->name);
	ArrangeComment (Comment);

      /* Delete any arranged dependencies for this attribute */
	UnarrangeAttr (with);

      /* Arrange attribute <with> after attribute <after> */
	MakeArrangeNode (symb->symb_def->did,
			 (SLNODE *) NULL, (SLNODE *) NULL,
			 after->attr_def->did, with->attr_def->did, True);

      /* Arrange attribute <with> before attribute <before> */
	MakeArrangeNode (symb->symb_def->did,
			 (SLNODE *) NULL, (SLNODE *) NULL,
			 with->attr_def->did, before->attr_def->did, True);
}


/************************************************************************
 *			    SplitPartition				*
 ************************************************************************/

PUBLIC void SplitPartition (symb, with, after)
	SYMBENTRY	*symb;
	ATTRENTRY	*with, *after;
{
	Boolean		last, next;
	ATTRENTRY	*before;

      /* Test for introduction of cycles */
	if (symb->ds[after->pos][with->pos] &&
	    !(symb->ds[after->pos][with->pos] & T_PART))
	{
		Message (symb->symb_def->did, Res.cycle_msg);
		return;
	}
	
	last = after->last != NULL && CLASS(after->last) == CLASS(after);
	next = after->next != NULL && CLASS(after->next) == CLASS(after);

	if (last && !next)	before = after->last;
	else if (!last && next)	before = after->next;
	else			before = NULL;

	if (before)
	{
		PerformSplit (symb, with, after, before);
		SplitPending = False;
	}
	else
	{
	      /* Not enough information yet, remember that a split is pending */
		SplitAfter   = after;
		SplitPending = True;
	}
}


/************************************************************************
 *			      ArrangeForced				*
 ************************************************************************/

/* Adds the necessary dependencies to yield the current partition.
 */

PUBLIC void ArrangeForced (symb)
	SYMBENTRY	*symb;
{
	ATTRENTRY *i, *j;

	sprintf (Comment, "Force partition of symbol %s",
			  symb->symb_def->dname);
	ArrangeComment (Comment);

	for (i = symb->first_attr; i != NULL; i = i->next)
		for (j = symb->first_attr; j != NULL; j = j->next)
			if (i->part < j->part)
				MakeArrangeNode (symb->symb_def->did,
					(SLNODE *) NULL, (SLNODE *) NULL,
					i->attr_def->did,
					j->attr_def->did, True);
}


/************************************************************************
 *			    StepPathFromStart				*
 ************************************************************************/

PRIVATE Boolean StepPathFromStart (symb, PathFromStart, i, 
			           start, old_start, mask)
	SYMBENTRY	*symb;
	Boolean		*PathFromStart;
	ATTRENTRY	**i, *start, *old_start;
	short		mask;
{
	ATTRENTRY	*j;
	Boolean		path = False;
	DEPENDENCY	*dep;

	for ((*i)=start; 
	     *i != NULL && CLASS(*i)==CLASS(start); *i = (*i)->next)
	{
		if ((*i)->part <= 1)
		{
			path = PathFromStart[(*i)->pos] = True;
			continue;
		}

		PathFromStart[(*i)->pos] = False;
		for (j = old_start; j != start; j = j->next)
		{
			dep = & symb->ds[(*i)->pos][j->pos];

			if (PathFromStart[j->pos] &&
			    *dep && !(*dep & mask))
			{
				path = PathFromStart[(*i)->pos] = True;
				break;
			}
		}
	}
	return (path);
}


/************************************************************************
 *			   ComputePathFromStart				*
 ************************************************************************/

PRIVATE void ComputePathFromStart (symb, PathFromStart)
	SYMBENTRY	*symb;
	Boolean		*PathFromStart;
{
	ATTRENTRY *i, *start, *old_start;

	old_start = start = symb->first_attr;
	for (; start != NULL; old_start = start, start = i)
		if (! StepPathFromStart (symb, PathFromStart, & i, start, 
					old_start, T_PART|T_ARR))
			(void) StepPathFromStart (symb, PathFromStart, & i,
					start, old_start, T_PART);
}


/************************************************************************
 *			      StepPathToEnd				*
 ************************************************************************/

PRIVATE Boolean StepPathToEnd (symb, PathToEnd, i, 
			       start, old_start, mask)
	SYMBENTRY	*symb;
	Boolean		PathToEnd[];
	ATTRENTRY	**i, *start, *old_start;
	short		mask;
{
	ATTRENTRY	*j;
	Boolean		path = False;
	DEPENDENCY	*dep;

	for ((*i)=start; *i != NULL && CLASS(*i)==CLASS(start); *i = (*i)->last)
	{
		if ((*i)->part >= symb->part_num - 1)
		{
			path = PathToEnd[(*i)->pos] = True;
			continue;
		}

		PathToEnd[(*i)->pos] = False;
		for (j = old_start; j != start; j = j->last)
		{
			dep = & symb->ds[j->pos][(*i)->pos];

			if (PathToEnd[j->pos] &&
			    *dep && !(*dep & mask))
			{
				path = PathToEnd[(*i)->pos] = True;
				break;
			}
		}
	}
	return (path);
}


/************************************************************************
 *			     ComputePathToEnd				*
 ************************************************************************/

PRIVATE void ComputePathToEnd (symb, PathToEnd)
	SYMBENTRY	*symb;
	Boolean		PathToEnd[];
{
	ATTRENTRY *i, *start, *old_start;

	old_start = symb->last_attr;
	start = symb->last_attr;

	for (; start != NULL; old_start = start, start = i)
		if (! StepPathToEnd (symb, PathToEnd, & i, start, 
					old_start, T_PART|T_ARR))
			(void) StepPathToEnd (symb, PathToEnd, & i, start,
						old_start, T_PART);
}


/************************************************************************
 *			   SymbMarkCriticalPath				*
 ************************************************************************/

PUBLIC void SymbMarkCriticalPath (symb)
	SYMBENTRY *symb;
{
#define MAX_ATNO 1024
	Boolean PathToEnd[MAX_ATNO], PathFromStart[MAX_ATNO];
	ATTRENTRY *ae;

      /* Accept only partitioned symbols */
	if (symb->attr_num == 0 || !(symb->state & S_PARTITIONED)) return;

/* this check needs to be done earlier: */
	if (symb->attr_num > MAX_ATNO)
	   exit (1);

      /* Fill the arrays */
	ComputePathFromStart (symb, PathFromStart);
	ComputePathToEnd (symb, PathToEnd);

      /* Now mark the critical attributes */
	for (ae = symb->first_attr; ae != NULL; ae = ae->next)
		if (PathFromStart[ae->pos] && PathToEnd[ae->pos])
			ae->state |= A_CRITICAL;
		else
			ae->state &= ~A_CRITICAL;
}

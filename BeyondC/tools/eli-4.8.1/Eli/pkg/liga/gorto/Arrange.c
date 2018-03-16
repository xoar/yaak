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
/* $Id: Arrange.c,v 4.3 1998/04/28 14:07:43 ludi Exp $ */
static char rcs_id[]= "$Id: Arrange.c,v 4.3 1998/04/28 14:07:43 ludi Exp $";

/*======================================================================*
 *									*
 *	FILE:		Misc/Arrange.c					*
 *									*
 *	CONTENTS:	Functions dealing with the global list of	*
 *			introduced arrange options			*
 *									*
 *	AUTHOR:		Volker Niepel					*
 *									*
 *======================================================================*/

/* The functions in this file operate on a global list of currently
 * active arrange options. There are functions to add or remove an option,
 * to register a comment with a group of options and to write the current
 * list in LCL (LIGA Control Language) format.
 */


#include "Misc.h"
#include "Main.h"


/************************************************************************
 *			     Global Variables				*
 ************************************************************************/

/* List of currently active arrange options */
PRIVATE ARRANGE_NODE *ArrangeNodes    = NULL;
PRIVATE ARRANGE_NODE *LastArrangeNode = NULL;

/* Comment to be registered with the next arrange option */
PRIVATE String Comment = (String) NULL;


/************************************************************************
 *			       IntroduceDep				*
 ************************************************************************/

/* Introduces the dependency described by the arrande node <nd> into the 
 * corresponding dependency graph.
 */

PRIVATE void IntroduceDep (nd)
	ARRANGE_NODE *nd;
{
	DEPENDENCY	*dep;
	DETAIL		*det;

      /* Determine the corresponding dependency entry and mark the 
	 production or symbol to be changed and arranged */
	if (ref_tab[nd->did].etag == PROD)
	{
		dep = & PE(nd->did).dp
		  [nd->toNode->start_row + AE(nd->toAid).pos]
		  [nd->fromNode->start_row + AE(nd->fromAid).pos];
		det = & PE(nd->did).dp_detail
		  [nd->toNode->start_row + AE(nd->toAid).pos]
		  [nd->fromNode->start_row + AE(nd->fromAid).pos];
		PE(nd->did).state |= S_CHANGED | S_ARRANGED;
	}
	else
	{
		dep = & SE(nd->did).ds[AE(nd->toAid).pos][AE(nd->fromAid).pos];
		det = & SE(nd->did).ds_detail
				      [AE(nd->toAid).pos][AE(nd->fromAid).pos];
		SE(nd->did).state |= S_CHANGED | S_ARRANGED;
	}

      /* Introduce the dependency */
	if ((!(*dep)) || (*dep & (T_PART|T_ARR)))
	{
		*dep = T_ARR;
		det->arrange.node = nd;
	}
}


/************************************************************************
 *			        NodeInlist				*
 ************************************************************************/

/* Searches the given arrange node <new> in the global list of arrange
 * nodes. The result of this search is returned.
 */

PRIVATE Boolean NodeInList (new)
	ARRANGE_NODE *new;
{
	ARRANGE_NODE *p;

      /* Loop over all arrange nodes, compare <new> with every found node */
	for (p = ArrangeNodes; p != NULL; p = p->next)
		if (p->did      == new->did &&
		    p->fromNode == new->fromNode &&
		    p->toNode   == new->toNode &&
		    p->fromAid  == new->fromAid &&
		    p->toAid    == new->toAid)	
			return (True);

      /* No match found */
	return (False);
}


/************************************************************************
 *			     MakeArrangeNode				*
 ************************************************************************/

/* Appends a new node to the list of currently active arrange options.
 * The flag <introduce> controls the introduction of the corresponding 
 * dependency into the dependency graphs.
 */

PUBLIC void MakeArrangeNode (did, fromNode, toNode, fromAid,  toAid, introduce)
	int		did;
	SLNODE		*fromNode, *toNode;
	int		fromAid, toAid;
	Boolean		introduce;
{
      /* Allocate a new node */
	ARRANGE_NODE *new = XtNew (ARRANGE_NODE);

      /* Fill the new node */
	new->comment	= Comment;
	new->did	= did;
	new->fromNode	= fromNode;
	new->toNode	= toNode;
	new->fromAid	= fromAid;
	new->toAid	= toAid;
	new->next	= NULL;

      /* Check for duplicate list entries */
	if (NodeInList (new))
	{
		XtFree ((char *)new);
		return;
	}

      /* Free the old comment */
	Comment = (String) NULL;

      /* Update the list */
	if (LastArrangeNode != NULL)	LastArrangeNode->next = new;
	else				ArrangeNodes          = new;
	LastArrangeNode = new;

      /* Introduce the corresponding dependency */
	if (introduce) IntroduceDep (new);
}


/************************************************************************
 *			      ArrangeComment				*
 ************************************************************************/

PUBLIC void ArrangeComment (comment)
	String comment;
{
	Comment = XtNewString (comment);
}


/************************************************************************
 *			    RemoveArrangeNode				*
 ************************************************************************/

/* Removes the given node <to_remove> from the list of active arrange
 * options. The corresponding dependency is not removed.
 */

PUBLIC void RemoveArrangeNode (to_remove)
	ARRANGE_NODE *to_remove;
{
	ARRANGE_NODE *current	= ArrangeNodes;
	ARRANGE_NODE *last	= NULL;

      /* Search the node <to_remove> in the node list */
	while (current != NULL && current != to_remove)
	{
		last = current;
		current = current->next;
	}

      /* If found, remove it */
	if (current != NULL)
	{
		if (LastArrangeNode == current) LastArrangeNode = last;

		if (last != NULL)	last->next   = current->next;
		else			ArrangeNodes = current->next;

		if (current->next && current->next->comment == NULL)
			current->next->comment = current->comment;
		else
			XtFree (current->comment);
		XtFree ((char *)current);
	}
}


/************************************************************************
 *			      UnarrangeAttr				*
 ************************************************************************/

PUBLIC void UnarrangeAttr (ae)
	ATTRENTRY *ae;
{
	ARRANGE_NODE	*current, *next;
	SYMBENTRY		*symb;
	ATTRENTRY		*ae1, *ae2;
	DEPENDENCY		*dep;

	current = ArrangeNodes;
	ArrangeNodes = LastArrangeNode = NULL;
	while (current)
	{
		next = current->next;
		if (ref_tab[current->did].etag == SYMB &&
		    (current->fromAid == ae->attr_def->did ||
		     current->toAid   == ae->attr_def->did))
		{
			symb = & SE (current->did);
			ae1  = & AE (current->fromAid);
			ae2  = & AE (current->toAid);
			dep  = & symb->ds[ae2->pos][ae1->pos];

			if ((*dep & T_MASK) == T_ARR) *dep = 0;

			if (next && next->comment == NULL)
				next->comment = current->comment;
			else
				XtFree (current->comment);
			XtFree ((char *)current);
		}
		else
		{
			if (ArrangeNodes)
			{
				LastArrangeNode->next = current;
				LastArrangeNode = current;
			}
			else
				ArrangeNodes = LastArrangeNode = current;
			current->next  = NULL;
		}
		current = next;
	}
}


/************************************************************************
 *			     ResetArrangeList				*
 ************************************************************************/

/* Removes the entire list of arrange nodes.
 */

PUBLIC void ResetArrangeList ()
{
	ARRANGE_NODE *current, *next;

	for (current = ArrangeNodes; current != NULL; current = next)
	{
		next = current->next;
		XtFree (current->comment);
		XtFree ((char *)current);
	}

	ArrangeNodes = NULL;
}


/************************************************************************
 *			   IntroduceArrangeList				*
 ************************************************************************/

/* Introduces all dependencies described by the list of active arrange
 * options. Used mainly for recomputing the dependency graphs.
 */

PUBLIC void IntroduceArrangeList()
{
	ARRANGE_NODE *current;

      /* Call the private function IntroduceDep for all nodes */
	for (current=ArrangeNodes; current!=NULL; current=current->next)
		IntroduceDep (current);
}


/************************************************************************
 *			     ArrangeListEmpty				*
 ************************************************************************/

/* Returns True if the list of active arrange options is empty.
 */

PUBLIC Boolean ArrangeListEmpty()
{
	return (ArrangeNodes == (ARRANGE_NODE *) NULL);
}


/************************************************************************
 *			     WriteArrangeList				*
 ************************************************************************/

/* Writes the list of active arrange options in LIGA control language (LCL). */
/***	CHANGED:							***/
/***	writes all necessary order options in LCL now			***/

PUBLIC void WriteArrangeList ()
{
	ARRANGE_NODE *current;


	if (PART_EARLY)
		fprintf (LCL, "\nORDER:\tPARTITION EARLY;\n");
	else if (PART_LATE)
		fprintf (LCL, "\nORDER:\tPARTITION LATE;\n");

	if (AUTOMATICALLY)
		fprintf (LCL, "\nORDER:\tARRANGE AUTOMATICALLY;\n");

	if (!ArrangeNodes)
		return;

	fprintf (LCL, "\nORDER:\n");
	for (current = ArrangeNodes; current != NULL; current = current->next)
	{
		if (current->comment != NULL)
			fprintf (LCL, "\n\t/* %s */\n", current->comment);

		fprintf (LCL, "\tARRANGE ");
		if (ref_tab[current->did].etag == PROD)
		{
			fprintf (LCL, "IN RULE %s EVAL ",
				PE(current->did).prod_def->dname);

			if (current->fromNode->ord)
				fprintf (LCL, "%s[%d].%s BEFORE ",
				   SE(current->fromNode->sid).symb_def->dname,
				   current->fromNode->ord,
				   AE(current->fromAid).attr_def->name);
			else
				fprintf (LCL, "%s.%s BEFORE ",
				   SE(current->fromNode->sid).symb_def->dname,
				   AE(current->fromAid).attr_def->name);

			if (current->toNode->ord)
				fprintf (LCL, "%s[%d].%s",
				   SE(current->toNode->sid).symb_def->dname,
				   current->toNode->ord,
				   AE(current->toAid).attr_def->name);
			else
				fprintf (LCL, "%s.%s",
				   SE(current->toNode->sid).symb_def->dname,
				   AE(current->toAid).attr_def->name);
		}
		else
		{
			fprintf (LCL, "FOR SYMB %s EVAL %s BEFORE %s",
				SE(current->did).symb_def->dname,
				AE(current->fromAid).attr_def->name,
				AE(current->toAid).attr_def->name);
		}
		if (current->next)
			fprintf (LCL, ",\n");
		else
			fprintf (LCL, ";\n");
	} /* for */
} /* WriteArrangeList() */


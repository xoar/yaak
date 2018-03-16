/* $Id: conflicts.c,v 1.2 2000/04/03 12:50:01 peter Exp $ */
/* $Log: conflicts.c,v $
 * Revision 1.2  2000/04/03 12:50:01  peter
 * Introduction of option "NO_GROUPING"
 * If this option is set, all grouping of variables is supressed,
 * including the grouping requested by system internal grouping
 * directives for CHAIN attributes.  This option usually leads to
 * increased memory and time requirements of the generated processor. It
 * is only recommended during the development of language processors for
 * large specifications, since it may decrease the time required for
 * processor generation.
 *
 * Revision 1.1  1996/02/06 13:30:25  cogito
 * Initial revision
 *
 * Revision 2.5  1991/07/23  17:21:09  cogito
 * expand options: INCLUDING_FUNCTION replaced by INCLUDING ON / OFF
 * order options: new option ARRANGE FAST to cancel default ARRANGE AUTOMATICALLY
 * backend options: new option FREE_TREE (opposite of KEEP_TREE)
 *
 * Revision 2.4  91/05/15  08:32:16  cogito
 * removed unused expand options
 * 
 * Revision 2.3  91/02/21  11:00:17  cogito
 * used casts to prevent type clash warnings
 * 
 * Revision 2.2  91/01/15  18:00:13  cogito
 * new IDL interface
 * 
 * Revision 2.1  90/12/04  14:41:26  cogito
 * new version of option handler
 *  */
static char rcs_id[]= "$Id: conflicts.c,v 1.2 2000/04/03 12:50:01 peter Exp $";

/***********************************************************************\
*	conflicts.c							*
*	Implementation of test function for mutual excluding options	*
*	(only a few rudimentary tests)					*
*									*
*	Written 08/08/90 - 07/23/91	by HaDeS			*
\***********************************************************************/

#include <stdio.h>
#include "opt_liga.h"

int Conflict_Test (opts)
OptCollect opts;
{
	ExpList		expp;
	OrdList		ordp;
	OptList		optp;
	BEList		bep;
	int		option;
	int		error;

	error= 0;

	/* tests for EXPAND */
	if (opts->exp_opts)
	{
		option= -1;
		for (expp= opts->exp_opts; expp; expp= expp->next)
		{
			if (expp->entry->flag == including_on)
				option= (int) including_on;
			else if (expp->entry->flag == including_off)
				option= (int) including_off;
		} /* for */
		if (option>0)
		{
			for (expp= opts->exp_opts; expp; expp= expp->next)
			{
				if ((expp->entry->flag == including_on)
					&& option == (int) including_off)
				{
					errormesg ("mutually excluding options in EXPAND: INCLUDING");
					error++;
				} /* if */
				else if ((expp->entry->flag == including_off)
					&& option == (int) including_on)
				{
					errormesg ("mutually excluding options in EXPAND: INCLUDING");
					error++;
				} /* else if */
			} /* for */
		} /* if */
	} /* if */

	/* tests for ORDER	*/
	if (opts->ord_opts)
	{
		option= -1;
		for (ordp= opts->ord_opts; ordp; ordp= ordp->next)
		{
			if (ordp->entry->flag == arr_auto)
				option= (int) arr_auto;
			else if (ordp->entry->flag == arr_fast)
				option= (int) arr_fast;
		} /* for */
		if (option>0)
		{
			for (ordp= opts->ord_opts; ordp; ordp= ordp->next)
			{
				if ((ordp->entry->flag == arr_auto) && option == (int) arr_fast)
				{
					errormesg ("mutually excluding options in ORDER: ARRANGE");
					error++;
				} /* if */
				else if ((ordp->entry->flag == arr_fast) && option == (int) arr_auto)
				{
					errormesg ("mutually excluding options in ORDER: ARRANGE");
					error++;
				} /* else if */
			} /* for */
		} /* if */
		option= -1;
		for (ordp= opts->ord_opts; ordp; ordp= ordp->next)
		{
			if (ordp->entry->flag == part_early)
				option= (int) part_early;
			else if (ordp->entry->flag == part_late)
				option= (int) part_late;
		} /* for */
		if (option>0)
		{
			for (ordp= opts->ord_opts; ordp; ordp= ordp->next)
			{
				if ((ordp->entry->flag == part_early) && option == (int) part_late)
				{
					errormesg ("mutually excluding options in ORDER: PARTITION");
					error++;
				} /* if */
				else if ((ordp->entry->flag == part_late) && option == (int) part_early)
				{
					errormesg ("mutually excluding options in ORDER: PARTITION");
					error++;
				} /* else if */
			} /* for */
		} /* if */
		option= -1;
		for (ordp= opts->ord_opts; ordp; ordp= ordp->next)
		{
			if (ordp->entry->flag == top_early)
				option= (int) top_early;
			else if (ordp->entry->flag == top_late)
				option= (int) top_late;
		} /* for */
		if (option>0)
		{
			for (ordp= opts->ord_opts; ordp; ordp= ordp->next)
			{
				if ((ordp->entry->flag == top_early)
					&& option == (int) top_late)
				{
					errormesg ("mutually excluding options in ORDER: TOPOLOGICAL");
					error++;
				} /* if */
				else if ((ordp->entry->flag == top_late)
					&& option == (int) top_early)
				{
					errormesg ("mutually excluding options in ORDER: TOPOLOGICAL");
					error++;
				} /* else if */
			} /* for */
		} /* if */
		option= -1;
		for (ordp= opts->ord_opts; ordp; ordp= ordp->next)
		{
			if (ordp->entry->flag == tree_compl)
				option= (int) tree_compl;
			else if (ordp->entry->flag == tree_up)
				option= (int) tree_up;
			else if (ordp->entry->flag == tree_down)
				option= (int) tree_down;
		} /* for */
		if (option>0)
		{
			for (ordp= opts->ord_opts; ordp; ordp= ordp->next)
			{
				if ((ordp->entry->flag == tree_compl)
					&& option != (int) tree_compl)
				{
					errormesg ("mutually excluding options in ORDER: TREE");
					error++;
				} /* if */
				else if ((ordp->entry->flag == tree_up)
					&& option != (int) tree_up)
				{
					errormesg ("mutually excluding options in ORDER: TREE");
					error++;
				} /* else if */
				else if ((ordp->entry->flag == tree_down)
					&& option != (int) tree_down)
				{
					errormesg ("mutually excluding options in ORDER: TREE");
					error++;
				} /* else if */
			} /* for */
		} /* if */
	} /* if */

	/* tests for OPTIM	*/
	if (opts->opt_opts)
	{
		option= -1;
		for (optp= opts->opt_opts; optp; optp= optp->next)
		{
			if (optp->entry->flag == opt_off)
				option= (int) opt_off;
		} /* for */
		if (option>0)
		{
			for (optp= opts->opt_opts; optp; optp= optp->next)
			{
				if ((optp->entry->flag == more_globals)
				 || (optp->entry->flag == no_stack)
				 || (optp->entry->flag == no_vars)
				 || (optp->entry->flag == no_grouping)   
				 || (optp->entry->flag == group_vars)
				 || (optp->entry->flag == group_stacks)
				 || (optp->entry->flag == group_all))
				{
					errormesg ("OPTIM OFF excludes other options for OPTIM");
					error++;
					break;
				} /* if */
			} /* for */
		} /* if */
		option= -1;
		for (optp= opts->opt_opts; optp; optp= optp->next)
		{
			if (optp->entry->flag == no_vars)
				option= (int) no_vars;
			else if (optp->entry->flag == no_stack)
				option= (int) no_stack;
		} /* for */
		if (option>0)
		{
			for (optp= opts->opt_opts; optp; optp= optp->next)
			{
				if ((optp->entry->flag == no_stack)
					&& option == (int) no_vars)
				{
					errormesg ("mutually excluding options in OPTIM: NO_VARIABLES <-> NO_STACKS");
					error++;
				} /* if */
				else if ((optp->entry->flag == no_vars)
					&& option == (int) no_stack)
				{
					errormesg ("mutually excluding options in OPTIM: NO_VARIABLES <-> NO_STACKS");
					error++;
				} /* else if */
			} /* for */
		} /* if */
		option= -1;
		for (optp= opts->opt_opts; optp; optp= optp->next)
		{
			if (optp->entry->flag == group_vars)
				option= (int) group_vars;
			else if (optp->entry->flag == group_stacks)
				option= (int) group_stacks;
			else if (optp->entry->flag == group_all)
				option= (int) group_all;
		} /* for */
		if (option>0)
		{
			for (optp= opts->opt_opts; optp; optp= optp->next)
			{
				if ((optp->entry->flag == group_vars)
					&& option != (int) group_vars)
				{
					errormesg ("mutually excluding options in OPTIM: GROUPING");
					error++;
				} /* if */
				else if ((optp->entry->flag == group_stacks)
					&& option != (int) group_stacks)
				{
					errormesg ("mutually excluding options in OPTIM: GROUPING");
					error++;
				} /* else if */
				else if ((optp->entry->flag == group_all)
					&& option != (int) group_all)
				{
					errormesg ("mutually excluding options in OPTIM: GROUPING");
					error++;
				} /* else if */
			} /* for */
		} /* if */
	} /* if */

	/* tests for BACKEND	*/
	if (opts->be_opts)
	{
		option= -1;
		for (bep= opts->be_opts; bep; bep= bep->next)
		{
			if (bep->entry->flag == case_split)
				option= bep->entry->value;
		} /* for */
		if (option>0)
		{
			for (bep= opts->be_opts; bep; bep= bep->next)
			{
				if ((bep->entry->flag == case_split)
					&& option != bep->entry->value)
				{
					errormesg ("mutually excluding options in BACKEND: SPLIT_CASE");
					error++;
				} /* if */
			} /* for */
		} /* if */
		option= -1;
		for (bep= opts->be_opts; bep; bep= bep->next)
		{
			if (bep->entry->flag == atstacks)
				option= bep->entry->value;
		} /* for */
		if (option>0)
		{
			for (bep= opts->be_opts; bep; bep= bep->next)
			{
				if ((bep->entry->flag == atstacks)
					&& option != bep->entry->value)
				{
					errormesg ("mutually excluding options in BACKEND: ATSTACK_SIZE");
					error++;
				} /* if */
			} /* for */
		} /* if */
		option= -1;
		for (bep= opts->be_opts; bep; bep= bep->next)
		{
			if (bep->entry->flag == keep_tree)
				option= (int) keep_tree;
			else if (bep->entry->flag == free_tree)
				option= (int) free_tree;
		} /* for */
		if (option>0)
		{
			for (bep= opts->be_opts; bep; bep= bep->next)
			{
				if ((bep->entry->flag == keep_tree)
					&& option == (int) free_tree)
				{
					errormesg ("mutually excluding options in BACKEND: to keep or not to keep the tree...");
					error++;
				} /* if */
				else if ((bep->entry->flag == free_tree)
					&& option == (int) keep_tree)
				{
					errormesg ("mutually excluding options in BACKEND: to keep or not to keep the tree...");
					error++;
				} /* else if */
			} /* for */
		} /* if */
	} /* if */

	return (!error);
} /* Conflict_Test() */


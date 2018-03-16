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
/* $Id: exp_io.c,v 4.1 1997/08/29 09:09:06 peter Exp $ */
static char rcs_id[] = "$Id: exp_io.c,v 4.1 1997/08/29 09:09:06 peter Exp $";

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		exp_io.c					*
*	File:		exp_io.c					*
*	Contents:	input/output functions of the expand pass	*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	12 Dec 1990					*
*	Last change:	23 Jul 1991					*
*									*
\***********************************************************************/

#include <stdio.h>
#include <string.h>

#include "LIGA.h"
#include "middle_mem.h"
#include "option_enums.h"
#include "option_types.h"

#include "expconst.h"
#include "exp_types.h"
#include "expand.h"
#include "exp_io.h"

/* * GLOBAL VARIABLES */

OptCollect expand_opts;
OptCollect optim_opts;
OptOption attrspez;

/* * LOCAL VARIABLES */

/* * LOCAL FUNCTIONS */

static
#ifdef __STDC__
void
attrspez_out(ANamesList anl, FILE * file)
#else
void
attrspez_out(anl, file)
   ANamesList anl;
   FILE *file;
#endif
/* write attribute spezification for optim options			 */
{
   int attrcount, idcount;
   ANamesList anp;
   IdList il;

   /* count attributes */
   for (anp = anl, attrcount = 0; anp; anp = anp->next)
      attrcount++;
   (void) fprintf(file, "%d\n", attrcount);

   while (anl)
   {
      /* count identifiers */
      for (il = anl->names, idcount = 0; il; il = il->next, idcount++);
      (void) fprintf(file, "%s %d\n", anl->symbname, idcount);
      /* print all identifiers */
      for (il = anl->names; il; il = il->next)
	 (void) fprintf(file, "%s\n", il->ident);
      anl = anl->next;
   }	/* while */
}/* attrspez_out() */

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
void
eval_exp_opt(void)
#else
void
eval_exp_opt()
#endif
/* evaluate expand options						 */
{
   ExpList expp;

   /* set default values */

   CONST_ATTR = "_const";
   EXP_PROT = 0;
   EXP_INCL = 0;	/* Changed Default INCLUDING ON to INCLUDING OFF */
   INCL_ATTR = "_incl";
   IDENT_INCL = 1;
   CHAIN_PRE_ATTR = "_pre";
   CHAIN_POST_ATTR = "_post";

   NULL_FUNC = "null";
   CREAT_FUNC = "creat";
   CONCAT_FUNC = "concat";

   if (!expand_opts)
      return;

   (void) fprintf(ProtocolFile, "\nOptions for expand:\n");
   (void) fprintf(ProtocolFile, "-------------------\n");
   if (!expand_opts->exp_opts)
   {
      (void) fprintf(ProtocolFile, "\t<none>\n");
      return;
   }	/* if */
   for (expp = expand_opts->exp_opts; expp; expp = expp->next)
   {
      switch (expp->entry->flag)
      {
      case const_attr_name:
	 CONST_ATTR = expp->entry->attrname;
	 (void) fprintf(ProtocolFile,
		 "\tName-prefix for generated CONSTITUENT(S)-attrs is %s\n",
			CONST_ATTR);
	 break;
      case incl_attr_name:
	 INCL_ATTR = expp->entry->attrname;
	 (void) fprintf(ProtocolFile,
		      "\tName-prefix for generated INCLUDING-attrs is %s\n",
			INCL_ATTR);
	 break;
      case chain_pre_name:
	 CHAIN_PRE_ATTR = expp->entry->attrname;
	 (void) fprintf(ProtocolFile,
		      "\tName-prefix for generated CHAIN-PRE-attrs is %s\n",
			CHAIN_PRE_ATTR);
	 break;
      case chain_post_name:
	 CHAIN_POST_ATTR = expp->entry->attrname;
	 (void) fprintf(ProtocolFile,
		     "\tName-prefix for generated CHAIN-POST-attrs is %s\n",
			CHAIN_POST_ATTR);
	 break;
      case includings_separate:
	 (void) fprintf(ProtocolFile,
			"\tINCLUDINGS are not identified\n");
	 IDENT_INCL = 0;
	 break;
      case exp_info:
	 (void) fprintf(ProtocolFile,
			"\tlarge protocol enabled\n");
	 EXP_PROT = 1;
	 break;
      case including_on:
	 (void) fprintf(ProtocolFile,
			"\tINCLUDINGS are expanded\n");
	 EXP_INCL = 1;
	 break;
      case including_off:
	 (void) fprintf(ProtocolFile,
			"\tINCLUDINGS are not expanded\n");
	 EXP_INCL = 0;
	 break;
      default:
	 break;
      }	/* switch */
   }	/* for */

   (void) fprintf(ProtocolFile, "\n");
}/* eval_exp_opt() */

#ifdef __STDC__
void
OptionOut(OptCollect opts, FILE * optim_file)
#else
void
OptionOut(opts, optim_file)
   OptCollect opts;
   FILE *optim_file;
#endif
/* write options for the optim pass					 */
{
   OptList optp;
   int optcount;

   if (!opts->opt_opts)
      return;

   /* count options */
   for (optp = opts->opt_opts, optcount = 0; optp; optp = optp->next, optcount++);
   (void) fprintf(optim_file, "%d %d\n", 3, optcount);
   /* write options */
   for (optp = opts->opt_opts; optp; optp = optp->next)
   {
      switch (optp->entry->flag)
      {
      case opt_off:
      case opt_info:
      case more_globals:
      case no_vars:
      case no_stack:
      case group_vars:
      case group_stacks:
      case group_all:
	 (void) fprintf(optim_file, "%d\n", optp->entry->flag);
	 break;
      case attr_glob_stack:
      case attr_glob_var:
      case attr_group_stack:
      case attr_group_var:
      case attr_treenode:
	 (void) fprintf(optim_file, "%d\n", optp->entry->flag);
	 attrspez_out(optp->entry->attrs, optim_file);
	 break;
      default:
	 return;
      }	/* switch */
   }	/* for */

}/* OptionOut() */

/***********************\
* end of exp_io.c	*
\***********************/

/* HaDeS */

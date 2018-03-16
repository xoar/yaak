/* $Id: opt_input.c,v 4.4 2001/11/05 14:49:55 cogito Exp $ */

static char rcs_id[]= "$Id: opt_input.c,v 4.4 2001/11/05 14:49:55 cogito Exp $";
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

/***********************************************************************\
*	opt_input.c							*
*	Implementation of input function for the option handler		*
*									*
*	Written 07/05/90 - 07/23/91	by HaDeS			*
\***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "option_enums.h"
#include "option_types.h"
#include "opt_input.h"

char *attrspez_readstring(file)
     FILE *file;
{ char buffer[BUFSIZE];
  char *result;
  fscanf(file,"%s",buffer);
  result = (char*) malloc (strlen(buffer)+1);
  if (!result)
    {fprintf(stderr,"attrspez_readstring: malloc returns 0\n");
    }
  strcpy(result,buffer);
  return result;
}

void attrspez_in (file, opto)
FILE		*file;
OptOption	opto;
{
	int		attrcount, idcount;
	int		i, j;
	ANamesList	anl;
	IdList		il;

	(void) fscanf (file, "%d", &attrcount);

	for (i= 0; i<attrcount; i++)
	{
		anl= (ANamesList) malloc (sizeof (struct _anameslist));
                anl->symbname = attrspez_readstring(file);
		anl->names = (IdList)NULL;
		(void) fscanf (file, "%d", &idcount);
		for (j= 0; j<idcount; j++)
		{
			il= (IdList) malloc (sizeof (struct _idlist));
			il->ident=attrspez_readstring(file);
			il->next= anl->names;
			anl->names= il;
		}
		anl->next= opto->attrs;
		opto->attrs= anl;
	}
}

void	ExpInput (optid, file, expo)
int optid;
FILE *file;
ExpOption expo;
{
	switch (optid)
	{
		case const_attr_name:
		case incl_attr_name:
		case chain_pre_name:
		case chain_post_name:
			expo->flag= (expoptflag) optid;
			expo->attrname= (char *) malloc (BUFSIZE);
			(void) fscanf (file, "%s", expo->attrname);
			break;
		case including_on:
		case including_off:
		case exp_info:
		case includings_separate:
			expo->flag= (expoptflag) optid;
			break;
		case expopt_error:
		default:
			expo->flag= expopt_error;
			(void) fprintf (stderr, "error in inputfile: %d\n", optid);
			break;
	}
} /* ExpInput */

void	OrdInput (optid, file, ordo)
int optid;
FILE *file;
OrdOption ordo;
{
	int i;

	switch (optid)
	{
		case part_early:
		case part_late:
		case top_early:
		case top_late:
		case tree_compl:
		case tree_up:
		case tree_down:
		case arr_auto:
		case arr_fast:
			ordo->flag= (ordoptflag) optid;
			break;
		case direct_symb:
		case trans_symb:
		case ind_symb:
		case direct_rule:
		case trans_rule:
		case ind_rule:
		case part_rule:
		case partition:
		case visit_seq:
			ordo->flag= (ordoptflag) optid;
			(void) fscanf (file, "%d", &(ordo->namecount));
			ordo->names= (char **) malloc (sizeof(char *) * ordo->namecount);
			for (i=0; i<ordo->namecount; i++)
			{
				ordo->names[i]= (char *) malloc (BUFSIZE);
				(void) fscanf (file, "%s", ordo->names[i]);
			}
			break;
		case for_symb:
			ordo->flag= (ordoptflag) optid;
			ordo->names= (char **) malloc (sizeof(char *) * 3);
			ordo->names[0]= (char *) malloc (BUFSIZE);
			ordo->names[1]= (char *) malloc (BUFSIZE);
			ordo->names[2]= (char *) malloc (BUFSIZE);
			(void) fscanf (file, "%s %s %s",
				ordo->names[0],
				ordo->names[1],
				ordo->names[2]);
			break;
		case in_rule:
			ordo->flag= (ordoptflag) optid;
			ordo->names= (char **) malloc (sizeof(char *) * 5);
			ordo->names[0]= (char *) malloc (BUFSIZE);
			ordo->names[1]= (char *) malloc (BUFSIZE);
			ordo->names[2]= (char *) malloc (BUFSIZE);
			ordo->names[3]= (char *) malloc (BUFSIZE);
			ordo->names[4]= (char *) malloc (BUFSIZE);
			(void) fscanf (file, "%s %s %d %s %s %d %s",
				ordo->names[0],
				ordo->names[1],
				&(ordo->symbindex1),
				ordo->names[2],
				ordo->names[3],
				&(ordo->symbindex2),
				ordo->names[4]);
			break;
		case ordopt_error:
		default:
			ordo->flag= ordopt_error;
			(void) fprintf (stderr, "error in inputfile: %d\n", optid);
			break;
	}
} /* OrdInput */

void	OptInput (optid, file, opto)
int optid;
FILE *file;
OptOption opto;
{
	switch (optid)
	{
	        case opt_do_incl:
		case opt_no_incl:
		case opt_tree:
		case opt_off:
		case opt_info:
		case more_globals:
		case no_vars:
		case no_stack:
		case group_vars:
		case group_stacks:
		case group_all:
			opto->flag= (optoptflag) optid;
			break;
		case attr_glob_stack:
		case attr_glob_var:
		case attr_group_stack:
		case attr_group_var:
		case attr_treenode:
			opto->flag= (optoptflag) optid;
			attrspez_in (file, opto);
			break;
		case optopt_error:
		default:
			opto->flag= optopt_error;
			(void) fprintf (stderr, "error in inputfile: %d\n", optid);
			break;
	}
} /* OptInput */

void	BEInput (optid, file, beo)
int optid;
FILE *file;
BEOption beo;
{
	switch (optid)
	{
		case do_exp_incl:
		case readable:
		case tree_top_down:
		case exp_no_incl:
		case keep_tree:
		case free_tree:
			beo->flag= (beoptflag) optid;
			break;
		case case_split:
		case atstacks:
		case nodestacks:
			beo->flag= (beoptflag) optid;
			(void) fscanf (file, "%d", &(beo->value));
			break;
		case beopt_error:
		default:
			beo->flag= beopt_error;
			(void) fprintf (stderr, "error in inputfile: %d\n", optid);
			break;
	}
} /* BEInput */

void	OptionInput (opts, file)
OptCollect opts;
FILE *file;
{
	ExpList		expp;
	OrdList		ordp;
	OptList		optp;
	BEList		bep;
	int		pass;
	int		count;
	int		optid;
	int		i;

	if (fscanf (file, "%d %d", &pass, &count) == EOF)
		return;
	switch (pass)
	{
		case 1:		/* options for EXPAND	*/
			for (i= 0; i<count; i++)
			{
				expp= (ExpList) malloc (sizeof(struct _explist));
				expp->entry= (ExpOption) malloc (sizeof(struct _expoption));
				(void) fscanf (file, "%d", &optid);
				ExpInput (optid, file, expp->entry);
				expp->next= opts->exp_opts;
				opts->exp_opts= expp;
			}
			break;
		case 2:		/* options for ORDER	*/
			for (i= 0; i<count; i++)
			{
				ordp= (OrdList) malloc (sizeof(struct _ordlist));
				ordp->entry= (OrdOption) malloc (sizeof(struct _orderoption));
				(void) fscanf (file, "%d", &optid);
				OrdInput (optid, file, ordp->entry);
				ordp->next= opts->ord_opts;
				opts->ord_opts= ordp;
			}
			break;
		case 3:		/* options for OPTIM	*/
			for (i= 0; i<count; i++)
			{
				optp= (OptList) malloc (sizeof(struct _optlist));
if (!optp)
  fprintf(stderr,"malloc sizeof struct _optlist returns 0\n");
				optp->entry= (OptOption) malloc (sizeof(struct _optimoption));
if (!optp->entry)
  fprintf(stderr,"malloc optp->entry returns 0\n");
				optp->entry->attrs=(ANamesList)NULL;
				(void) fscanf (file, "%d", &optid);
				OptInput (optid, file, optp->entry);
				optp->next= opts->opt_opts;
				opts->opt_opts= optp;
			}
			break;
		case 4:		/* options for BACKEND	*/
			for (i= 0; i<count; i++)
			{
				bep= (BEList) malloc (sizeof(struct _belist));
				bep->entry= (BEOption) malloc (sizeof(struct _backendoption));
				(void) fscanf (file, "%d", &optid);
				BEInput (optid, file, bep->entry);
				bep->next= opts->be_opts;
				opts->be_opts= bep;
			}
			break;
		default:
			(void) fprintf (stderr, "error in inputfile: %d\n", optid);
			break;
	}

} /* OptionInput */


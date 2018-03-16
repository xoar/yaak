/* $Log: opt_liga.c,v $
 * Revision 1.4  2001/11/05 17:23:46  cogito
 * *** empty log message ***
 *
 * Revision 1.2  2000/04/03 12:51:13  peter
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
 * Revision 1.8  1992/03/10  10:38:37  cogito
 * in two case statements were missing the break statement
 *
 * Revision 1.7  1991/10/31  15:14:28  cogito
 * Added INCLUDING ON to the optim and backend options.
 * Supressed Effect of some backend options. Theese
 * Options now result in an error.
 *
 * Revision 1.6  1991/07/23  17:20:54  cogito
 * expand options: INCLUDING_FUNCTION replaced by INCLUDING ON / OFF
 * order options: new option ARRANGE FAST to cancel default ARRANGE AUTOMATICALLY
 * backend options: new option FREE_TREE (opposite of KEEP_TREE)
 *
 * Revision 1.5  91/07/02  15:07:35  cogito
 * INCLUDING_FUNCTION will be transfered to optim pass
 * 
 * Revision 1.4  91/05/15  08:32:34  cogito
 * removed unused expand options
 * 
 * Revision 1.3  91/02/21  10:59:46  cogito
 * used casts to prevent type clash warnings
 * 
 * Revision 1.2  91/01/24  14:59:55  cogito
 * added new backend option
 * 
 * Revision 1.1  91/01/15  17:55:22  cogito
 * Initial revision
 *  */
static char rcs_id[]= "$Id: opt_liga.c,v 1.4 2001/11/05 17:23:46 cogito Exp peter $";

/***********************************************************************\
*	opt_liga.c							*
*	Implementation of functions in option handler			*
*									*
*	Written 06/19/90 - 07/02/91	by HaDeS			*
\***********************************************************************/


#include <stdio.h>
#include "opt_liga.h"

/*
** GLOBAL VARIABLE DEFINITIONS
*/

char *exp_fname, *ord_fname, *opt_fname, *be_fname;

/*
** FUNCTION DEFINITIONS
*/

ExpOption	ExpOptEnter1 (id1, id2)
int id1, id2;
{
	ExpOption	result;

	result= (ExpOption) malloc (sizeof (struct _expoption));

	/* compare identifier to keywords	*/
	switch (cmpidkw (id1, exp1kw))
	{
		case 0:
			result->flag= const_attr_name;
			break;
		case 1:
			result->flag= incl_attr_name;
			break;
		case 2:
			result->flag= chain_pre_name;
			break;
		case 3:
			result->flag= chain_post_name;
			break;
		default:
			result->flag= expopt_error;
			errormesg ("Illegal option for EXPAND");
			break;
	} /* switch */

	/* get the second identifier as name	*/
	result->attrname= getelistring (id2);

	return (result);
} /* ExpOptEnter1() */

ExpOption	ExpOptEnter2 (id)
int id;
{
	ExpOption	result;

	result= (ExpOption) malloc (sizeof (struct _expoption));

	/* compare identifier to keywords	*/
	switch (cmpidkw (id, exp2kw))
	{
		case 0:
			result->flag= includings_separate;
			break;
		case 1:
			result->flag= exp_info;
			break;
		default:
			result->flag= expopt_error;
			errormesg ("Illegal option for EXPAND");
			break;
	} /* switch */

	result->attrname= NULL;

	return (result);
} /* ExpOptEnter2() */

ExpOption	ExpOptEnter3 (id)
int id;
{
	ExpOption	result;

	result= (ExpOption) malloc (sizeof (struct _expoption));

	/* compare identifier to keywords	*/
	switch (cmpidkw (id, exp3kw))
	{
		case 0:
			result->flag= including_on;
			break;
		case 1:
			result->flag= including_off;
			break;
		default:
			result->flag= expopt_error;
			errormesg ("Illegal option for EXPAND");
			break;
	} /* switch */

	result->attrname= NULL;

	return (result);
} /* ExpOptEnter3() */


OrdOption	OrdOptEnter1 (id1, id2)
int id1, id2;
{
	OrdOption	result;
	int		keyword1, keyword2;

	result= (OrdOption) malloc (sizeof (struct _orderoption));

	/* compare identifier 1 to keywords	*/
	keyword1= cmpidkw (id1, ord1kw);

	/* compare identifier 2 to keywords	*/
	keyword2= cmpidkw (id2, ord2kw);

	switch (keyword1)
	{
		case 0:
			switch (keyword2)
			{
				case 0:
					result->flag= part_early;
					break;
				case 1:
					result->flag= part_late;
					break;
				default:
					result->flag= ordopt_error;
					errormesg ("Illegal option for ORDER");
					break;
			}
			break;
		case 1:
			switch (keyword2)
			{
				case 0:
					result->flag= top_early;
					break;
				case 1:
					result->flag= top_late;
					break;
				default:
					result->flag= ordopt_error;
					errormesg ("Illegal option for ORDER");
					break;
			}
			break;
		default:
			result->flag= ordopt_error;
			errormesg ("Illegal option for ORDER");
			break;
	}

	result->namecount= 0;
	result->names= NULL;
	result->symbindex1= 0;
	result->symbindex2= 0;

	return result;
} /* OrdOptEnter1() */

OrdOption	OrdOptEnter2 (id, ids)
int id;
IdList ids;
{
	OrdOption	result;
	int		keyword;
	IdList		idpointer;
	int		idcounter;
	char		**strp;

	result= (OrdOption) malloc (sizeof (struct _orderoption));

	/* compare identifier to keywords	*/
	keyword= cmpidkw (id, ord3kw);

	switch (keyword)
	{
		case 0:
			result->flag= direct_symb;
			break;
		case 1:
			result->flag= trans_symb;
			break;
		case 2:
			result->flag= ind_symb;
			break;
		case 3:
			result->flag= direct_rule;
			break;
		case 4:
			result->flag= trans_rule;
			break;
		case 5:
			result->flag= ind_rule;
			break;
		case 6:
			result->flag= part_rule;
			break;
		case 7:
			result->flag= partition;
			break;
		case 8:
			result->flag= visit_seq;
			break;
		default:
			result->flag= ordopt_error;
			errormesg ("Illegal option for ORDER");
			break;
	}

	/* count entries in the list	*/
	idcounter= 0;
	for (idpointer= ids; idpointer; idpointer= idpointer->next)
		idcounter++;

	/* store identifiers from list	*/
	result->namecount= idcounter;
	result->names= (char **) malloc (sizeof (char *)*idcounter);
	strp= result->names;
	for (idpointer= ids; idpointer; idpointer= idpointer->next)
		*(strp++)= idpointer->ident;
	result->symbindex1= 0;
	result->symbindex2= 0;

	return result;
} /* OrdOptEnter2() */

OrdOption	OrdOptEnter3 (id)
int id;
{
	OrdOption	result;
	int		keyword;

	result= (OrdOption) malloc (sizeof (struct _orderoption));

	/* compare identifier to keywords	*/
	keyword= cmpidkw (id, ord4kw);

	switch (keyword)
	{
		case 0:
			result->flag= tree_compl;
			break;
		case 1:
			result->flag= tree_up;
			break;
		case 2:
			result->flag= tree_down;
			break;
		default:
			result->flag= ordopt_error;
			errormesg ("Illegal option for ORDER");
			break;
	}

	result->namecount= 0;
	result->names= NULL;
	result->symbindex1= 0;
	result->symbindex2= 0;

	return result;
} /* OrdOptEnter3() */

OrdOption	OrdOptEnter4 ()
{
	OrdOption	result;

	result= (OrdOption) malloc (sizeof (struct _orderoption));

	result->flag= arr_auto;
	result->namecount= 0;
	result->names= NULL;
	result->symbindex1= 0;
	result->symbindex2= 0;

	return result;
} /* OrdOptEnter4() */

OrdOption	OrdOptEnter7 ()
{
	OrdOption	result;

	result= (OrdOption) malloc (sizeof (struct _orderoption));

	result->flag= arr_fast;
	result->namecount= 0;
	result->names= NULL;
	result->symbindex1= 0;
	result->symbindex2= 0;

	return result;
} /* OrdOptEnter7() */

OrdOption	OrdOptEnter5 (id1, id2, id3)
int id1, id2, id3;
{
	OrdOption	result;

	result= (OrdOption) malloc (sizeof (struct _orderoption));

	result->flag= for_symb;
	result->namecount= 3;
	result->names= (char **) malloc (sizeof (char *) * 3);
	(result->names)[0]= getelistring (id1);
	(result->names)[1]= getelistring (id2);
	(result->names)[2]= getelistring (id3);
	result->symbindex1= 0;
	result->symbindex2= 0;

	return result;
} /* OrdOptEnter5() */

OrdOption	OrdOptEnter6 (id1, id2, id3, val1, id4, id5, val2)
int id1, id2, id3, id4, id5;
int val1, val2;
{
	OrdOption	result;

	result= (OrdOption) malloc (sizeof (struct _orderoption));

	result->flag= in_rule;
	result->namecount= 5;
	result->names= (char **) malloc (sizeof (char *) * 5);
	(result->names)[0]= getelistring (id1);
	(result->names)[1]= getelistring (id2);
	(result->names)[2]= getelistring (id3);
	(result->names)[3]= getelistring (id4);
	(result->names)[4]= getelistring (id5);
	result->symbindex1= val1;
	result->symbindex2= val2;

	return result;
} /* OrdOptEnter6() */


OptOption	OptOptEnter1 (id)
int id;
{
	OptOption	result;
	int		keyword;

	result= (OptOption) malloc (sizeof (struct _optimoption));

	/* compare identifier to keywords	*/
	keyword= cmpidkw (id, opt1kw);

	switch (keyword)
	{
		case 0:
			result->flag= opt_off;
			break;
		case 1:
			result->flag= opt_info;
			break;
		case 2:
			result->flag= more_globals;
			break;
		case 3:
			result->flag= no_vars;
			break;
		case 4:
			result->flag= no_stack;
			break;
		case 5:
			result->flag= no_grouping;
			break;
		default:
			result->flag= optopt_error;
			errormesg ("Illegal option for OPTIM");
			break;
	}

	result->attrs= NULL;

	return (result);
} /* OptOptEnter1() */

OptOption	OptOptEnter2 (id)
int id;
{
	OptOption	result;
	int		keyword;

	result= (OptOption) malloc (sizeof (struct _optimoption));

	/* compare identifier to keywords	*/
	keyword= cmpidkw (id, opt2kw);

	switch (keyword)
	{
		case 0:
			result->flag= group_vars;
			break;
		case 1:
			result->flag= group_stacks;
			break;
		case 2:
			result->flag= group_all;
			break;
		default:
			result->flag= optopt_error;
			errormesg ("Illegal option for OPTIM");
			break;
	}

	result->attrs= NULL;

	return result;
} /* OptOptEnter2() */

OptOption	OptOptEnter3 (flag, names)
int flag;
ANamesList names;
{
	OptOption	result;

	result= (OptOption) malloc (sizeof (struct _optimoption));

	result->flag= (optoptflag) flag;
	result->attrs= names;

	return result;
} /* OptOptEnter3() */

int AttrTypeId1 (id1, id2)
int id1, id2;
{
	int result;
	int keyword1, keyword2;

	/* compare identifier 1 to keywords	*/
	keyword1= cmpidkw (id1, opt3kw);

	/* compare identifier 2 to keywords	*/
	keyword2= cmpidkw (id2, opt4kw);

	switch (keyword1)
	{
		case 0:
			switch (keyword2)
			{
				case 0:
					result= (int) attr_glob_stack;
					break;
				case 1:
					result= (int) attr_glob_var;
					break;
				default:
					result= (int) optopt_error;
					errormesg ("Illegal option for OPTIM");
					break;
			}
			break;
		case 1:
			switch (keyword2)
			{
				case 0:
					result= (int) attr_group_stack;
					break;
				case 1:
					result= (int) attr_group_var;
					break;
				default:
					result= (int) optopt_error;
					errormesg ("Illegal option for OPTIM");
					break;
			}
			break;
		default:
			result= (int) optopt_error;
			errormesg ("Illegal option for OPTIM");
			break;
	}

	return result;
} /* AttrTypeId1() */

int AttrTypeId2 ()
{
	return ((int) attr_treenode);
} /* AttrTypeId2() */


BEOption	BEOptEnter1 (id)
int id;
{
	BEOption	result;
	int		keyword;

	result= (BEOption) malloc (sizeof (struct _backendoption));

	/* compare identifier to keyword	*/
	keyword= cmpidkw (id, be1kw);

	switch (keyword)
	{
		case 0:
			result->flag= readable;
			break;
		case 1:
			result->flag= keep_tree;
			break;
		case 2:
			result->flag= free_tree;
			break;
		default:
			result->flag= beopt_error;
			errormesg ("Illegal option for BACKEND");
			break;
	}

	result->value= 0;

	return (result);
} /* BEOptEnter1() */

BEOption	BEOptEnter2 (id, value)
int id;
int value;
{
	BEOption	result;
	int		keyword;

	result= (BEOption) malloc (sizeof (struct _backendoption));

	/* compare identifier to keyword	*/
	keyword= cmpidkw (id, be2kw);

	/* Modification: The Options SPLIT_CASE intval, ATSTACK_SIZE intval
           and NODESTACK_SIZE intval must not be used any longer. */
	switch (keyword)
	{
	/*	case 0:
			result->flag= case_split;
			break;  */
	/*	case 1:
			result->flag= atstacks;
			break;  */
	/*	case 2:
			result->flag= nodestacks;
			break;  */
		default:
			result->flag= beopt_error;
			errormesg ("Illegal option for BACKEND");
			break;
	}

	result->value= value;

	return (result);
} /* BEOptEnter2() */


OptCollect InitOpts()
{
	OptCollect result;

	result= (OptCollect) malloc (sizeof(struct _optcollect));

	result-> exp_opts= NULL;
	result-> ord_opts= NULL;
	result-> opt_opts= NULL;
	result-> be_opts= NULL;

	return (result);
} /* InitOpts() */

OptCollect JoinOpts(opts1, opts2)
OptCombin opts1;
OptCollect opts2;
{
	switch (opts1->type)
	{
		case exp_ltype:
			opts2->exp_opts= concatExpOList (
						opts1->entry.entry1,
						opts2->exp_opts);
			break;
		case ord_ltype:
			opts2->ord_opts= concatOrdOList (
						opts1->entry.entry2,
						opts2->ord_opts);
			break;
		case opt_ltype:
			opts2->opt_opts= concatOptOList (
						opts1->entry.entry3,
						opts2->opt_opts);
			break;
		case be_ltype:
			opts2->be_opts= concatBEOList (
						opts1->entry.entry4,
						opts2->be_opts);
			break;
		default:
			errormesg ("Internal error #3 - please report");
			break;
	}

	return (opts2);
} /* JoinOpts() */

int Mix_Options (ok, opts)
int ok;
OptCollect opts;
{
	ExpList		expp;
	OrdList         ordp;
	OptList         optp;
	BEList          bep;
	int		error;
	int		automatically;

	if (!ok)
		return (0);

	for (expp= opts->exp_opts; expp; expp= expp->next)
	{
		switch (expp->entry->flag)
		{
		  case including_on:
		  case including_off:
		    optp= (OptList) malloc (sizeof (struct _optlist));
		    optp->entry= (OptOption) malloc (sizeof (struct _optimoption));
		    optp->entry->flag =
		      expp->entry->flag == including_off ? opt_no_incl : opt_do_incl;
		    optp->entry->attrs= (ANamesList) NULL;
		    optp->next= opts->opt_opts;
		    opts->opt_opts= optp;
		    
		    bep= (BEList) malloc (sizeof (struct _belist));
		    bep->entry= (BEOption) malloc (sizeof (struct _backendoption));
		    bep->entry->flag = 
		      expp->entry->flag == including_off ? exp_no_incl : do_exp_incl;
		    bep->entry->value= 0;
		    bep->next= opts->be_opts;
		    opts->be_opts= bep;
		    break;
		  default:
		    break;
		} /* switch */
	} /* for */

	automatically= 0;
	for (ordp= opts->ord_opts; ordp; ordp= ordp->next)
	{
		switch (ordp->entry->flag)
		{
			case tree_up:
				optp= (OptList) malloc (
					sizeof (struct _optlist));
				optp->entry= (OptOption) malloc (
					sizeof (struct _optimoption));
				optp->entry->flag= opt_tree;
				optp->entry->attrs= (ANamesList) NULL;
				optp->next= opts->opt_opts;
				opts->opt_opts= optp;
				break;
			case tree_down:
				bep= (BEList) malloc (
					sizeof (struct _belist));
				bep->entry= (BEOption) malloc (
					sizeof (struct _backendoption));
				bep->entry->flag= tree_top_down;
				bep->entry->value= 0;
				bep->next= opts->be_opts;
				opts->be_opts= bep;
				optp= (OptList) malloc (
					sizeof (struct _optlist));
				optp->entry= (OptOption) malloc (
					sizeof (struct _optimoption));
				optp->entry->flag= opt_tree;
				optp->entry->attrs= (ANamesList) NULL;
				optp->next= opts->opt_opts;
				opts->opt_opts= optp;
				break;
			case arr_auto:
				automatically++;
				break;
			case arr_fast:
				automatically++;
				break;
			default:
				break;
		} /* switch */
	} /* for */

	if (!automatically)
	{
		ordp= (OrdList) malloc (sizeof (struct _ordlist));
		ordp->entry= (OrdOption) malloc (sizeof (struct _orderoption));
		ordp->entry->flag= arr_auto;
		ordp->entry->namecount= 0;
		ordp->entry->names= (char **) NULL;
		ordp->entry->symbindex1= 0;
		ordp->entry->symbindex2= 0;
		ordp->next= opts->ord_opts;
		opts->ord_opts= ordp;
	} /* if */

	return (1);
} /* Mix_Options() */

OptCombin TransferOpts1 (opts)
ExpList opts;
{
	OptCombin result;

	result= (OptCombin) malloc (sizeof(struct _optcombin));

	result->type= exp_ltype;
	result->entry.entry1= opts;

	return (result);
} /* TransferOpts1() */

OptCombin TransferOpts2 (opts)
OrdList opts;
{
	OptCombin result;

	result= (OptCombin) malloc (sizeof(struct _optcombin));

	result->type= ord_ltype;
	result->entry.entry2= opts;

	return (result);
} /* TransferOpts2() */

OptCombin TransferOpts3 (opts)
OptList opts;
{
	OptCombin result;

	result= (OptCombin) malloc (sizeof(struct _optcombin));

	result->type= opt_ltype;
	result->entry.entry3= opts;

	return (result);
} /* TransferOpts3() */

OptCombin TransferOpts4 (opts)
BEList opts;
{
	OptCombin result;

	result= (OptCombin) malloc (sizeof(struct _optcombin));

	result->type= be_ltype;
	result->entry.entry4= opts;

	return (result);
} /* TransferOpts4() */


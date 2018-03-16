/* $Log: output.c,v $
 * Revision 1.7  2001/11/05 17:23:46  cogito
 * *** empty log message ***
 *
 * Revision 1.4  2000/07/17 14:11:07  peter
 * redundant "break;"s removed
 *
 * Revision 1.3  2000/07/17 14:10:15  peter
 * redundant break; removed
 *
 * Revision 1.2  2000/04/03 12:50:44  peter
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
 * Revision 1.3  1992/11/11  09:49:40  cogito
 * *** empty log message ***
 *
 * Revision 1.2  1992/09/23  11:07:50  cogito
 * 'INCLUDING ON' produced an 'output abandoned' message
 *
 * Revision 1.1  1992/03/05  13:18:26  cogito
 * Initial revision
 *
 * Revision 2.5  1991/08/26  14:23:00  cogito
 * *** empty log message ***
 *
 * Revision 2.4  91/07/23  17:20:52  cogito
 * expand options: INCLUDING_FUNCTION replaced by INCLUDING ON / OFF
 * order options: new option ARRANGE FAST to cancel default ARRANGE AUTOMATICALLY
 * backend options: new option FREE_TREE (opposite of KEEP_TREE)
 * 
 * Revision 2.3  91/01/24  14:58:26  cogito
 * added new backend option
 * 
 * Revision 2.2  91/01/15  17:59:08  cogito
 * new IDL interface
 * 
 * Revision 2.1  90/12/04  14:54:30  cogito
 * new version of option handler
 *  */
static char rcs_id[]= "$Id: output.c,v 1.7 2001/11/05 17:23:46 cogito Exp $";

/***********************************************************************\
*	output.c							*
*	Implementation of output function for the option handler	*
*									*
*	Written 07/02/90 - 07/23/91	by HaDeS			*
\***********************************************************************/

#include <stdio.h>
#include "opt_liga.h"

void attrspez_out (anl, file)
ANamesList	anl;
FILE		*file;
{
	int		attrcount, idcount;
	ANamesList	anp;
	IdList		il;

	for (anp= anl, attrcount= 0; anp; anp= anp->next, attrcount++);
	fprintf (file, "%d\n", attrcount);

	while (anl)
	{
		for (il= anl->names, idcount=0; il; il= il->next, idcount++);
		fprintf (file, "%s %d\n", anl->symbname, idcount);
		il= anl->names;
		while (il)
		{
			fprintf (file, "%s\n", il->ident);
			il= il->next;
		}
		anl= anl->next;
	}
}

void	Output(opts, ok)
OptCollect opts;
int ok;
{
	FILE		*expand_file;
	FILE		*order_file;
	FILE		*optim_file;
	FILE		*backend_file;

	ExpList		expp;
	OrdList		ordp;
	OptList		optp;
	BEList		bep;
	int		expcount, ordcount, optcount, becount;
	int		i;

	if (!ok)
		return;
	expand_file= fopen (exp_fname, "w");
	order_file= fopen (ord_fname, "w");
	optim_file= fopen (opt_fname, "w");
	backend_file= fopen (be_fname, "w");

	if ( (expand_file==NULL)
	  || (order_file==NULL)
	  || (optim_file==NULL)
	  || (backend_file==NULL))
	{
		errormesg ("error opening file");
		return;
	}

	/* write option file for EXPAND	*/
	if (opts->exp_opts)
	{
		for (expp= opts->exp_opts, expcount=0; expp; expp=expp->next, expcount++);
		fprintf (expand_file, "%d %d\n", 1, expcount);
		expp= opts->exp_opts;
		while (expp)
		{
			switch (expp->entry->flag)
			{
				case const_attr_name:
				case incl_attr_name:
				case chain_pre_name:
				case chain_post_name:
					fprintf (expand_file, "%d\n%s\n", expp->entry->flag, expp->entry->attrname);
					break;
				case includings_separate:
				case exp_info:
				case including_on:
				case including_off:
					fprintf (expand_file, "%d\n", expp->entry->flag);
					break;
				case expopt_error:
				default:
					errormesg ("output abandoned");
					return;
			}
			expp= expp->next;
		}
	}

	/* write option file for ORDER	*/
	if (opts->ord_opts)
	{
		for (ordp= opts->ord_opts, ordcount=0; ordp; ordp=ordp->next, ordcount++);
		fprintf (order_file, "%d %d\n", 2, ordcount);
		ordp= opts->ord_opts;
		while (ordp)
		{
			switch (ordp->entry->flag)
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
					fprintf (order_file, "%d\n", ordp->entry->flag);
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
					fprintf (order_file, "%d\n", ordp->entry->flag);
					fprintf (order_file, "%d\n", ordp->entry->namecount);
					for (i=0; i<ordp->entry->namecount; i++)
						fprintf (order_file, "%s\n", ordp->entry->names[i]);
					break;
				case for_symb:
					fprintf (order_file, "%d\n", ordp->entry->flag);
					fprintf (order_file, "%s %s %s\n",
						ordp->entry->names[0],
						ordp->entry->names[1],
						ordp->entry->names[2]);
					break;
				case in_rule:
					fprintf (order_file, "%d\n", ordp->entry->flag);
					fprintf (order_file, "%s %s %d %s %s %d %s\n",
						ordp->entry->names[0],
						ordp->entry->names[1],
						ordp->entry->symbindex1,
						ordp->entry->names[2],
						ordp->entry->names[3],
						ordp->entry->symbindex2,
						ordp->entry->names[4]);
					break;
				case ordopt_error:
				default:
					errormesg ("output abandoned");
					return;
			}
			ordp= ordp->next;
		}
	}

	/* write option file for OPTIM	*/
	if (opts->opt_opts)
	{
		for (optp= opts->opt_opts, optcount=0; optp; optp=optp->next, optcount++);
		fprintf (optim_file, "%d %d\n", 3, optcount);
		optp= opts->opt_opts;
		while (optp)
		{
			switch (optp->entry->flag)
			{
			        case opt_do_incl:
				case opt_no_incl:
				case opt_tree:
				case opt_off:
				case opt_info:
				case more_globals:
				case no_vars:
				case no_stack:
  			        case no_grouping:
				case group_vars:
				case group_stacks:
				case group_all:
					fprintf (optim_file, "%d\n", optp->entry->flag);
					break;
				case attr_glob_stack:
				case attr_glob_var:
				case attr_group_stack:
				case attr_group_var:
				case attr_treenode:
					fprintf (optim_file, "%d\n", optp->entry->flag);
					attrspez_out (optp->entry->attrs, optim_file);
					break;
				case optopt_error:
				default:
					errormesg ("output abandoned");
					return;
			}
			optp= optp->next;
		}
	}

	/* write option file for BACKEND	*/
	if (opts->be_opts)
	{
		for (bep= opts->be_opts, becount=0; bep; bep=bep->next, becount++);
		fprintf (backend_file, "%d %d\n", 4, becount);
		bep= opts->be_opts;
		while (bep)
		{
			switch (bep->entry->flag)
			{
			        case do_exp_incl:
				case readable:
				case tree_top_down:
				case exp_no_incl:
				case keep_tree:
				case free_tree:
					fprintf (backend_file, "%d\n", bep->entry->flag);
					break;
				case case_split:
				case atstacks:
				case nodestacks:
					fprintf (backend_file, "%d\n", bep->entry->flag);
					fprintf (backend_file, "%d\n", bep->entry->value);
					break;
				case beopt_error:
				default:
					errormesg ("output abandoned");
					return;
			}
			bep= bep->next;
		}
	}

	fclose (expand_file);
	fclose (order_file);
	fclose (optim_file);
	fclose (backend_file);

} /* Output */


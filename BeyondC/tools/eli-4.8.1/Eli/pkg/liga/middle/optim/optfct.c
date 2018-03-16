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
static char rcs_id[] = "$Id: optfct.c,v 4.4 2000/04/03 12:48:50 peter Exp peter $";

/************************************************/
/* Module  : optfct.c			 */
/* */
/* Contains help routines for all		 */
/* other modules of liga.optim		 */
/* */
/************************************************/

/************************************************/
/* includes                   */
/************************************************/

#include <stdio.h>
#include <string.h>

#include "option_enums.h"
#include "option_types.h"

#include "lookup_idl.h"
#include "OPTIM.h"
#include "OPTIMMacros.h"
#include "optglobal.h"
#include "optidl.h"

#include "printerr.h"
#include "ligaconsts.h"

/************************************************/
/* functions                  */
/************************************************/

void InitOptimOptions( /* void */ );
void HandleOptimizeOption( /* AttrEval */ );
void HandleExpInclOption( /* Visit_Sequences */ );
void HandleVarListOption( /* Visit_Sequences */ );
void HandleStackListOption( /* Visit_Sequences */ );
void HandleTreeListOption( /* Visit_Sequences */ );

Boolean AttrInstanceInSet( /* int, int, SEQAttributes */ );
Boolean InSeqAttrs( /* SEQAttributes, int */ );
Boolean InSeqAction( /* SEQAction, Action */ );
Boolean NewInstance( /* Visit_Seq, Attributes */ );

int SymbId( /* Visit_Seq, int */ );
int ParentId( /* Visit_Seq */ );





/************************************************/
/* InitOptimOptions                */
/************************************************/

void 
InitOptimOptions()
{
   OptList optp;
   ANamesList anl;
   IdList anames;

   fprintf(ProtocolFile, "\n\n\tOptions for OPTIM:\n");

   for (optp = optim_opts->opt_opts; optp; optp = optp->next)
   {
      switch (optp->entry->flag)
      {
      case opt_do_incl:
	 exp_incl_option = TRUE;
	 fprintf(ProtocolFile, "\t--> INCLUDINGS are expanded\n");
	 break;
      case opt_no_incl:
	 exp_incl_option = FALSE;
	 fprintf(ProtocolFile, "\t--> INCLUDINGS are not expanded\n");
	 break;
      case opt_tree:
	 break;
      case opt_off:
	 optimize_option = FALSE;
	 break;
      case opt_info:
	 protocol_option = TRUE;
	 fprintf(ProtocolFile, "\t--> Protocol of Optimization\n");
	 break;
      case more_globals:
	 grammar_option = TRUE;
	 fprintf(ProtocolFile, "\t--> Optimization of multi-visit Attributes is done\n");
	 break;
      case no_vars:
	 no_var_option = TRUE;
	 fprintf(ProtocolFile, "\t--> No Attributes are implemented as Global Variables\n");
	 break;
      case no_stack:
	 no_stack_option = TRUE;
	 fprintf(ProtocolFile, "\t--> No Attributes are implemented as Global Stack\n");
	 break;
      case no_grouping:
	 no_grouping_option = TRUE;
	 fprintf(ProtocolFile, "\t--> No Grouping (grouping deactivated)\n");
	 break;
      case group_vars:
	 var_group_option = TRUE;
	 fprintf(ProtocolFile, "\t--> Variable-Grouping is done\n");
	 break;
      case group_stacks:
	 stack_group_option = TRUE;
	 fprintf(ProtocolFile, "\t--> Stack-Grouping is done\n");
	 break;
      case group_all:
	 group_all_option = TRUE;
	 fprintf(ProtocolFile, "\t--> Variable- and Stack-Grouping is done\n");
	 break;
      case attr_glob_stack:
	 stack_list_option = TRUE;
	 fprintf(ProtocolFile, "\t--> The following Attributes should be implemented as Global Stack\n");
	 for (anl = optp->entry->attrs; anl; anl = anl->next)
	    for (anames = anl->names; anames; anames = anames->next)
	       fprintf(ProtocolFile, "\t\t--> %s.%s\n", anl->symbname, anames->ident);
	 break;
      case attr_glob_var:
	 var_list_option = TRUE;
	 fprintf(ProtocolFile, "\t--> The following Attributes should be implemented as Global Variable\n");
	 for (anl = optp->entry->attrs; anl; anl = anl->next)
	    for (anames = anl->names; anames; anames = anames->next)
	       fprintf(ProtocolFile, "\t\t--> %s.%s\n", anl->symbname, anames->ident);
	 break;
      case attr_group_stack:
	 stack_group_list_option = TRUE;
	 fprintf(ProtocolFile, "\t--> The following Attributes should be in one Stack-Group\n");
	 for (anl = optp->entry->attrs; anl; anl = anl->next)
	    for (anames = anl->names; anames; anames = anames->next)
	       fprintf(ProtocolFile, "\t\t--> %s.%s\n", anl->symbname, anames->ident);
	 break;
      case attr_group_var:
	 var_group_list_option = TRUE;
	 fprintf(ProtocolFile, "\t--> The following Attributes should be in one Variable-Group\n");
	 for (anl = optp->entry->attrs; anl; anl = anl->next)
	    for (anames = anl->names; anames; anames = anames->next)
	       if (!strcmp(anl->symbname, "NO_SYMBOL_NAME"))
		  fprintf(ProtocolFile, "\t\t--> all attributes with name %s\n", anames->ident);
	       else
		  fprintf(ProtocolFile, "\t\t--> %s.%s\n", anl->symbname, anames->ident);
	 break;
      case attr_treenode:
	 tree_list_option = TRUE;
	 fprintf(ProtocolFile, "\t--> The following Attributes should be implemented as TREE NODES\n");
	 for (anl = optp->entry->attrs; anl; anl = anl->next)
	    for (anames = anl->names; anames; anames = anames->next)
	       if (!strcmp(anl->symbname, "NO_SYMBOL_NAME"))
		  fprintf(ProtocolFile, "\t\t--> all attributes with name %s\n", anames->ident);
	       else
		  fprintf(ProtocolFile, "\t\t--> %s.%s\n", anl->symbname, anames->ident);
	 break;
      case optopt_error:
      default:
	 break;
      }	/* switch */
   }	/* for */
   fprintf(ProtocolFile, "\n\n\n");

}/* end of InitOptimOptions */





/************************************************/
/* HandleOptimizeOption              */
/************************************************/

void 
HandleOptimizeOption(root)
   AttrEval root;
{
   SEQDef X;
   Def thisdef;
   SEQAttrdef Y;
   Attrdef attrdef;

   fprintf(ProtocolFile, "\n\n\n   NO OPTIMIZATION DONE\n\n\n");
   fprintf(ProtocolFile, "*****   all attributes become TREE-NODE status !!!   *****\n\n\n");
   foreachinSEQDef(root->defseq, X, thisdef)
   {
      if (typeof(thisdef) == KSymb)
      {
	 foreachinSEQAttrdef(thisdef.VSymb->attrs, Y, attrdef)
	 {
	    attrdef->store = STORTRAT;
	 }
      }
   }

}/* end of HandleOptimizeOption */





/************************************************/
/* HandleExpInclOption               */
/************************************************/

void 
HandleExpInclOption(root)
   Visit_Sequences root;
{
   SEQAttributes X, XX;
   Attributes thisattr, treeattr;

   foreachinSEQAttributes(root->attrs, X, thisattr)
   {
      if (InSeqAttrs(optimroot->tree_attrs, thisattr->attrid))
      {
	 foreachinSEQAttributes(root->tree_attrs, XX, treeattr)
	 {
	    if (treeattr->attrid == thisattr->attrid &&
		treeattr->gen == NOT_EXPANDED_INCLUDING)
	    {
	       removeSEQAttributes(root->attrs, thisattr);
	       attr_array[treeattr->attrid] = treeattr;
	    }
	 }
      }
   }

}/* end of HandleExpInclOption */





/************************************************/
/* HandleVarListOption             */
/************************************************/

void 
HandleVarListOption(root)
   Visit_Sequences root;
{
   ANamesList anl;
   IdList anames;
   Attributes attr;

   anl = GetAttrSpez(optim_opts->opt_opts, attr_glob_var);
   for (anl = optim_opts->opt_opts->entry->attrs; anl; anl = anl->next)
      for (anames = anl->names; anames; anames = anames->next)
      {
	 if (!(attr = GetAttrByName(anl->symbname, anames->ident)))
	 {
	    char errmsgbuff[ERR_BUFF_LEN];

	    err_setpos(0, 0);
	    sprintf(errmsgbuff, "ATTRIBUTE %s.%s does not exist!",
		    anl->symbname, anames->ident);
	    err_print_warning(errmsgbuff);
	    fprintf(ProtocolFile, "*** WARNING:  ATTRIBUTE %s.%s does not exist!\n",
		    anl->symbname, anames->ident);
	    continue;
	 }
	 if (!InSeqAttrs(root->glob_var, attr->attrid))
	 {
	    char errmsgbuff[ERR_BUFF_LEN];
	    err_setpos(0, 0);
	    sprintf(errmsgbuff, "ATTRIBUTE %s.%s can not be implemented as GLOBAL_VARIABLE",
		    anl->symbname, anames->ident);
	    err_print_note(errmsgbuff);
	    fprintf(ProtocolFile, "*** INFO: ATTRIBUTE %s.%s can not be implemented as GLOBAL_VARIABLE ***\n",
		    anl->symbname, anames->ident);
	 }
      }

}/* end of HandleVarListOption */



/************************************************/
/* HandleStackListOption             */
/************************************************/

void 
HandleStackListOption(root)
   Visit_Sequences root;
{
   ANamesList anl;
   IdList anames;
   SEQAttributes Z;
   Attributes thisattr, attr;

   anl = GetAttrSpez(optim_opts->opt_opts, attr_glob_stack);
   for (anl = optim_opts->opt_opts->entry->attrs; anl; anl = anl->next)
      for (anames = anl->names; anames; anames = anames->next)
      {
	 if (!(attr = GetAttrByName(anl->symbname, anames->ident)))
	 {
	    char errmsgbuff[ERR_BUFF_LEN];
	    sprintf(errmsgbuff, "ATTRIBUTE %s.%s does not exist!",
		    anl->symbname, anames->ident);
	    err_setpos(0, 0);
	    err_print_warning(errmsgbuff);
	    fprintf(ProtocolFile, "*** WARNING: ATTRIBUTE %s.%s does not exist!\n",
		    anl->symbname, anames->ident);
	    continue;
	 }
	 foreachinSEQAttributes(root->glob_var, Z, thisattr)
	    if (thisattr->attrid == attr->attrid)
	 {
	    appendfrontSEQAttributes(root->single_visit, thisattr);
	    removeSEQAttributes(root->glob_var, thisattr);
	 }
	 if (!InSeqAttrs(root->single_visit, attr->attrid))
	 {
	    char errmsgbuff[ERR_BUFF_LEN];
	    err_setpos(0, 0);
	    sprintf(errmsgbuff, "ATTRIBUTE %s.%s can not be implemented as GLOBAL_VARIABLE",
		    anl->symbname, anames->ident);
	    err_print_note(errmsgbuff);

	    fprintf(ProtocolFile, "*** INFO: ATTRIBUTE %s.%s can not be implemented as GLOBAL_STACK ***\n",
		    attr->sname, attr->aname);
	 }
      }
}/* end of HandleStackListOption */



/************************************************/
/* HandleTreeListOption             */
/************************************************/

void 
HandleTreeListOption(root)
   Visit_Sequences root;
{
   ANamesList anl;
   IdList anames;
   SEQAttributes Z;
   Attributes thisattr, attr;

   anl = GetAttrSpez(optim_opts->opt_opts, attr_treenode);
   for (anl = optim_opts->opt_opts->entry->attrs; anl; anl = anl->next)
      for (anames = anl->names; anames; anames = anames->next)
      {
	 if (!(attr = GetAttrByName(anl->symbname, anames->ident)))
	 {
	    char errmsgbuff[ERR_BUFF_LEN];

	    err_setpos(0, 0);
	    sprintf(errmsgbuff, "ATTRIBUTE %s.%s does not exist!",
		    anl->symbname, anames->ident);
	    err_print_warning(errmsgbuff);

	    fprintf(ProtocolFile, "*** WARNING: ATTRIBUTE %s.%s does not exist!\n",
		    anl->symbname, anames->ident);
	    continue;
	 }
	 foreachinSEQAttributes(root->attrs, Z, thisattr)
	    if (thisattr->attrid == attr->attrid
		&& !InSeqAttrs(root->tree_attrs, attr->attrid))
	 {
	    appendfrontSEQAttributes(root->tree_attrs, thisattr);
	    removeSEQAttributes(root->attrs, thisattr);
	 }
      }
}/* end of HandleTreeListOption */



/***********************************************************************/
/* AttrInstanceInSet                           */
/* */
/* returns TRUE, iff id.symbno in attributeseq              */
/***********************************************************************/


Boolean 
AttrInstanceInSet(id, symbno, attributeseq)
   int id, symbno;
   SEQAttributes attributeseq;
{
   SEQAttributes X;
   Attributes thisattr;

   foreachinSEQAttributes(attributeseq, X, thisattr)
      if (thisattr->attrid == id && thisattr->symbno == symbno)
      return (TRUE);

   return (FALSE);

}/* end of AttrInstanceInSet */





/************************************************/
/* InSeqAttrs                   */
/************************************************/

Boolean 
InSeqAttrs(seq, attrid)
   SEQAttributes seq;
   int attrid;
{
   SEQAttributes X;
   Attributes cmpattr;

   foreachinSEQAttributes(seq, X, cmpattr)
      if (cmpattr->attrid == attrid)
      return (TRUE);

   return (FALSE);

}/* end of InSeqAttrs */





/************************************************/
/* InSeqAction                   */
/************************************************/

Boolean 
InSeqAction(seq, thisaction)
   SEQAction seq;
   Action thisaction;
{
   SEQAction X;
   Action cmpaction;

   foreachinSEQAction(seq, X, cmpaction)
   {
      switch (typeof(cmpaction))
      {
      case KEval:
	 if (thisaction.VEval->attrid == cmpaction.VEval->attrid)
	    return (TRUE);
	 break;
      case KVisits:
	 if (thisaction.VVisits->symbid == cmpaction.VVisits->symbid &&
	     thisaction.VVisits->ord == cmpaction.VVisits->ord)
	    return (TRUE);
	 break;
      default:
	 break;
      }	/* end of switch */
   }

   return (FALSE);

}/* end of InSeqAction */




/************************************************/
/* NewInstance                  */
/************************************************/

Boolean 
NewInstance(thisvs, attrinst)
   Visit_Seq thisvs;
   Attributes attrinst;
{
   SEQAttributes X;
   Attributes cmpattr;

   foreachinSEQAttributes(thisvs->attrs, X, cmpattr)
      if (cmpattr->attrid == attrinst->attrid &&
	  cmpattr->symbno == attrinst->symbno)
      return (FALSE);

   return (TRUE);

}/* end of NewInstance */



/************************************************/
/* SymbId                     */
/************************************************/

int 
SymbId(thisvs, symbno)
   Visit_Seq thisvs;
   int symbno;
{
   SEQSymbols X;
   Symbols thissymb;

   foreachinSEQSymbols(thisvs->symbs, X, thissymb)
      if (thissymb->symbno == symbno)
      return (thissymb->symbid);

   return 0; /* should not occur */
}/* end of SymbId */



/************************************************/
/* ParentId                     */
/************************************************/

int 
ParentId(thisvs)
   Visit_Seq thisvs;
{
   SEQSymbols X;
   Symbols thissymb;

   foreachinSEQSymbols(thisvs->symbs, X, thissymb)
      if (thissymb->symbno == PARENT_SYMBOL)
      return (thissymb->symbid);

   return 0; /* should not occur */
}/* end of ParentId */

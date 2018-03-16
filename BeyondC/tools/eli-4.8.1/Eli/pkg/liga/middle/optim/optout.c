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
/* $Id: optout.c,v 4.11 1998/08/26 14:30:18 peter Exp $ */
/************************************************/
/* */
/* Version : 1.0                          */
/* */
/* Module  : optout.c                     */
/* */
/* Contains the routines to write out     */
/* results of the module liga.optim       */
/* */
/************************************************/



/************************************************/
/* includes                   */
/************************************************/


#include <stdio.h>
#include <string.h>
#include "LIGA.h"
#include "middle_mem.h"
#include "option_enums.h"
#include "option_types.h"

#include "lookup_idl.h"
#include "OPTIM.h"
#include "OPTIMMacros.h"
#include "optglobal.h"
#include "optidl.h"
#include "optdid.h"

#include "printerr.h"
#include "optout.h"
#include "ligaconsts.h"
#include "list.h"

/************************************************/
/* global variables                */
/************************************************/

int terminalattrcounter = 0;


/************************************************/
/* functions                  */
/************************************************/

char *GlobName( /* Attributes */ );
char *GroupName( /* Group */ );

Boolean IdentAssign( /* Call */ );

void ElimIdentAssignments( /* AttrEval */ );
void PutResultsToInterface( /* Visit_Sequences */ );
void StatisticToListing( /* Visit_Sequences */ );
void WriteAttrStatusToListing( /* Visit_Sequences */ );
void WriteGroupingResultsToListing( /* Visit_Sequences */ );
void WriteVisitSequencesToListing( /* Visit_Sequences, Boolean */ );
void OptResultsOut( /* Visit_Sequences */ );

/************************************************/
/* GlobName                  */
/************************************************/

char * GlobName(attr) Attributes attr;
{
   char *name;

   name = 
     middle_tempMalloc
       (__FILE__,__LINE__,strlen(attr->sname) + 
        strlen(attr->aname) + 2);

   strcpy(name, attr->sname);
   strcat(name, "_");
   strcat(name, attr->aname);
   return (name);
}/* end of GlobName */


/************************************************/
/* GroupName                  */
/************************************************/

char * GroupName(group) Group group;
{
   char *name;

   name = middle_tempMalloc(__FILE__,__LINE__,strlen(group->name) + 1);
   strcpy(name, group->name);
   return (name);
}/* end of GroupName */


/************************************************/
/* IdentAssign                */
/************************************************/

Boolean IdentAssign(call) Call call;
{
   Expr expr1, expr3;
   SEQGroup X;
   Group thisgroup;
   SEQAttributes Y;
   Attributes groupattr;
   Attrdef attrdef1, attrdef3;
   int length = lengthSEQExpr(call->params);
   Boolean attr1ingroup, attr3ingroup;

   /* call must be ASSIGNFCT: */
      if (length != 2)
	 return (FALSE);
      retrievefirstSEQExpr(call->params, expr1);
      retrievelastSEQExpr(call->params, expr3);
      if (typeof(expr3) != KAttracc)
	 return (FALSE);
      attrdef1 = lookup_attrdef(expr1.VAttracc->attrid);
      attrdef3 = lookup_attrdef(expr3.VAttracc->attrid);
      foreachinSEQGroup(optimroot->groups, X, thisgroup)
      {
	 attr1ingroup = attr3ingroup = FALSE;
	 foreachinSEQAttributes(thisgroup->members, Y, groupattr)
	 {
	    if (groupattr->attrid == attrdef1->did)
	       attr1ingroup = TRUE;
	    if (groupattr->attrid == attrdef3->did)
	       attr3ingroup = TRUE;
	    if (attr1ingroup && attr3ingroup)
	       return (TRUE);
	 }
      }
      return (FALSE);
}/* end of IdentAssign */

/************************************************/
/* ElimIdentAssignments            */
/************************************************/

void 
ElimIdentAssignments(root)
   AttrEval root;
{
   SEQAttribution X;
   Attribution attribution;
   SEQAttrrule Y;
   Attrrule attrrule;
   Call call;

   foreachinSEQAttribution(root->attrrules, X, attribution)
   {
      foreachinSEQAttrrule(attribution->attrrules, Y, attrrule)
      {
	 if (typeof(attrrule) == KCall)
	 {
	    call = attrrule.VCall;
	    if (strcmp(call->name, ASSIGNFCT) == 0)
	    {
	       if (IdentAssign (call))
	       {
		  identassigns++;
		  if (!protocol_option)
		  {
		     removeSEQAttrrule(attribution->attrrules, attrrule);
		  }
		  /* HINT: if protocol_option, then attrrule is removed */
		  /* by FUNCTION WriteVisitSequencesToListing     */
	       }
	       totalassigns++;
	    }
	 }
      }
   }

}/* end of ElimIdentAssignments */





/************************************************/
/* PutResultsToInterface             */
/************************************************/

void 
PutResultsToInterface(root)
   Visit_Sequences root;
{
   SEQGroup X;
   Group thisgroup;
   SEQAttributes Y;
   Attributes thisattr;
   SEQAttrdef A;
   Attrdef attrdef;
   SEQDef Z;
   Def def;

   foreachinSEQGroup(root->groups, X, thisgroup)
   {
      foreachinSEQAttributes(thisgroup->members, Y, thisattr)
      {
	 attrdef = lookup_attrdef(thisattr->attrid);
	 if (thisgroup->class == STORGLVA)
	 {
	    attrdef->store = STORGLVA;
	 } else
	 {
	    attrdef->store = STORGLST;
	 }
	 attrdef->globname = GroupName(thisgroup);
      }
   }
   foreachinSEQAttributes(root->glob_var, Y, thisattr)
   {
      attrdef = lookup_attrdef(thisattr->attrid);
      attrdef->store = STORGLVA;
      attrdef->globname = GlobName(thisattr);
   }
   foreachinSEQAttributes(root->single_visit, Y, thisattr)
   {
      attrdef = lookup_attrdef(thisattr->attrid);
      attrdef->store = STORGLST;
      attrdef->globname = GlobName(thisattr);
   }
   foreachinSEQAttributes(root->tree_attrs, Y, thisattr)
   {
      attrdef = lookup_attrdef(thisattr->attrid);
      attrdef->store = STORTRAT;
      if (thisattr->termattr  &&
          thisattr->typeid != VTY  &&  thisattr->typeid != VLTY)
      {
	 terminalattrcounter++;
      }
   }

   fprintf(ProtocolFile, "\n\n");
   foreachinSEQDef(ligaroot->defseq, Z, def)
   {
      if (typeof(def) == KSymb)
      {
	 foreachinSEQAttrdef(def.VSymb->attrs, A, attrdef)
	 {
	    if (attrdef->store == STORUNKN)
	    {
	       char errmsgbuff[ERR_BUFF_LEN];
	       err_setpos(def.VSymb->row, def.VSymb->col);
	       sprintf(errmsgbuff, "ATTRIBUTE %s.%s is defined, but never used.",
		       def.VSymb->dname, attrdef->name);
	       err_print_warning(errmsgbuff);

	       attrdef->store = STORTRAT;
	       fprintf(ProtocolFile, "*** WARNING: Attribute %s.%s is defined by LIDO-Definition, but never used !!\n",
		       def.VSymb->dname, attrdef->name);
	    }
	 }
      }
   }
   fprintf(ProtocolFile, "\n\n");

}/* end of PutResultsToInterface */





/************************************************/
/* StatisticToListing               */
/************************************************/

void 
StatisticToListing(root)
   Visit_Sequences root;
{
   int diff1 = treeattrcounter - terminalattrcounter - inclattrcounter - voidcounter;
   int diff2 = totalassigns - identassigns;

   fprintf(ProtocolFile, "*****          LIGA OPTIMIZER RESULTS          *****");
   fprintf(ProtocolFile, "\n\n\n");
   fprintf(ProtocolFile, "NUMBER OF GLOBAL VARIABLES      : %5d", globvarcounter);
   fprintf(ProtocolFile, "\n\n");
   fprintf(ProtocolFile, "      -> %d OF THESE ATTRIBUTES ARE NEVER USED", neverusedcounter);
   fprintf(ProtocolFile, "\n\n\n");
   fprintf(ProtocolFile, "NUMBER OF GLOBAL STACKS         : %5d", globstackcounter);
   fprintf(ProtocolFile, "\n\n\n");
   fprintf(ProtocolFile, "NUMBER OF TREE NODE COMPONENTS : %5d", treeattrcounter);
   fprintf(ProtocolFile, "\n\n");
   fprintf(ProtocolFile, "   because: -> %3d ATTRIBUTES ARE VOID ATTRIBUTES", voidcounter);
   fprintf(ProtocolFile, "\n");
   fprintf(ProtocolFile, "            -> %3d ATTRIBUTES HAVE TOO LONG LIFETIMES", diff1);
   fprintf(ProtocolFile, "\n");
   fprintf(ProtocolFile, "            -> %3d ATTRIBUTES ARE TERMINAL-ATTRIBUTES", terminalattrcounter);
   fprintf(ProtocolFile, "\n");
   fprintf(ProtocolFile, "            -> %3d ATTRIBUTES ARE ACCESSED BY NOT EXPANDED INCLUDING", inclattrcounter);
   fprintf(ProtocolFile, "\n\n\n");

   fprintf(ProtocolFile, "*****          RESULTS OF GROUPING          *****");
   fprintf(ProtocolFile, "\n\n");
   fprintf(ProtocolFile, "NUMBER OF GENERATED VARIABLE-GROUPS : %5d", vargroupcounter);
   fprintf(ProtocolFile, "\n");
   fprintf(ProtocolFile, "NUMBER OF GENERATED STACK-GROUPS    : %5d", stackgroupcounter);
   fprintf(ProtocolFile, "\n\n");
   fprintf(ProtocolFile, "NUMBER OF DELETED IDENTICAL ASSIGNS : %5d", identassigns);
   fprintf(ProtocolFile, "\n");
   fprintf(ProtocolFile, "    -> NEW NUMBER OF SEMANTIC RULES : %5d", diff2);
   fprintf(ProtocolFile, "\n\n\n");

}/* end of StatisticToListing */





/************************************************/
/* WriteAttrStatusToListing            */
/************************************************/

void 
WriteAttrStatusToListing(root)
   Visit_Sequences root;
{
   SEQGroup X;
   Group thisgroup;
   SEQAttributes Y;
   Attributes attr;

   fprintf(ProtocolFile, "*****     LIST OF ATTRIBUTE-CLASSIFICATIONS     *****");
   fprintf(ProtocolFile, "\n\n");

   foreachinSEQAttributes(root->glob_var, Y, attr)
   {
      fprintf(ProtocolFile, "RESULT FOR ATTR. %s.%s :\n", attr->sname, attr->aname);
      if (attr->not_used)
      {
	 fprintf(ProtocolFile, "   -> VARIABLE: ATTRIBUTE NOT USED IN TREE\n");
      }
      if (attr->termattr)
      {
	 fprintf(ProtocolFile, "   -> ATTRIBUTE OF A TERMINAL SYMBOL\n");
      }
      fprintf(ProtocolFile, "   -> GLOBAL VARIABLE\n");
   }
   fprintf(ProtocolFile, "\n");
   if (group_all_option || var_group_option || var_group_list_option)
   {
      foreachinSEQGroup(root->groups, X, thisgroup)
      {
	 if (thisgroup->class == STORGLVA)
	 {
	    foreachinSEQAttributes(thisgroup->members, Y, attr)
	    {
	       fprintf(ProtocolFile, "RESULT FOR ATTR. %s.%s :\n", attr->sname, attr->aname);
	       if (attr->not_used)
	       {
		  fprintf(ProtocolFile, "   -> VARIABLE: ATTRIBUTE NOT USED IN TREE\n");
	       }
	       if (attr->termattr)
	       {
		  fprintf(ProtocolFile, "   -> ATTRIBUTE OF A TERMINAL SYMBOL\n");
	       }
	       fprintf(ProtocolFile, "   -> GLOBAL VARIABLE\n");
	    }
	 }
      }
   }
   fprintf(ProtocolFile, "\n\n");
   foreachinSEQAttributes(root->single_visit, Y, attr)
   {
      fprintf(ProtocolFile, "RESULT FOR ATTR. %s.%s :\n", attr->sname, attr->aname);
      if (attr->termattr)
      {
	 fprintf(ProtocolFile, "   -> ATTRIBUTE OF A TERMINAL SYMBOL\n");
      }
      fprintf(ProtocolFile, "   -> GLOBAL STACK\n");
   }

   if (group_all_option || stack_group_option || stack_group_list_option)
   {
      foreachinSEQGroup(root->groups, X, thisgroup)
      {
	 if (thisgroup->class != STORGLVA)
	 {
	    foreachinSEQAttributes(thisgroup->members, Y, attr)
	    {
	       fprintf(ProtocolFile, "RESULT FOR ATTR. %s.%s :\n", attr->sname, attr->aname);
	       if (attr->termattr)
	       {
		  fprintf(ProtocolFile, "   -> ATTRIBUTE OF A TERMINAL SYMBOL\n");
	       }
	       fprintf(ProtocolFile, "   -> GLOBAL STACK\n");
	    }
	 }
      }
   }
   fprintf(ProtocolFile, "\n\n");
   foreachinSEQAttributes(root->tree_attrs, Y, attr)
   {
      fprintf(ProtocolFile, "RESULT FOR ATTR. %s.%s :\n", attr->sname, attr->aname);
      if (attr->termattr)
      {
	 fprintf(ProtocolFile, "   -> ATTRIBUTE OF A TERMINAL SYMBOL\n");
      }
      if (attr->gen == NOT_EXPANDED_INCLUDING)
      {
	 fprintf(ProtocolFile, "   -> USED IN INCLUDING, HENCE ...\n");
      }
      fprintf(ProtocolFile, "   -> TREE NODE ATTRIBUTE\n");
   }
   fprintf(ProtocolFile, "\n\n\n");

}/* end of WriteAttrStatusToListing */





/************************************************/
/* WriteGroupingResultsToListing        */
/************************************************/

void 
WriteGroupingResultsToListing(root)
   Visit_Sequences root;
{
   SEQGroup X;
   Group thisgroup;
   SEQAttributes Y;
   Attributes thisattr;
   int counter = 0;

   fprintf(ProtocolFile, "*****     LIST OF GENERATED GROUPS     *****");
   fprintf(ProtocolFile, "\n\n");

   foreachinSEQGroup(root->groups, X, thisgroup)
   {
      fprintf(ProtocolFile, "\n");
      fprintf(ProtocolFile, "MEMBERS OF ");
      switch (thisgroup->class)
      {
      case STORGLVA:
	 fprintf(ProtocolFile, "VARIABLE-GROUP ");
	 break;
      case PFBPFA:
	 fprintf(ProtocolFile, "STACK-GROUP ");
	 break;
      case PFAPFB:
	 fprintf(ProtocolFile, "STACK-GROUP ");
	 break;
      case PPFA:
	 fprintf(ProtocolFile, "STACK-GROUP ");
	 break;
      default:
	 break;
      }	/* end of switch */
      fprintf(ProtocolFile, "%s :", thisgroup->name);
      fprintf(ProtocolFile, "\n");
      counter = 0;
      foreachinSEQAttributes(thisgroup->members, Y, thisattr)
      {
	 counter++;
	 fprintf(ProtocolFile, "   %3d.: %s.%s", counter, thisattr->sname, thisattr->aname);
	 fprintf(ProtocolFile, "\n");
      }
   }
   fprintf(ProtocolFile, "\n\n\n");

}/* end of WriteGroupingResultsToListing */





/************************************************/
/* WriteVisitSequencesToListing        */
/************************************************/

void 
WriteVisitSequencesToListing(root, grouping)
   Visit_Sequences root;
   Boolean grouping;
{
   SEQAttribution X;
   Attribution vs;
   Def def;
   Prod prod;
   SEQAttrrule Y;
   Attrrule action;
   Call call;
   Visit visit;
   Attributes attr;
   Expr eval;

   fprintf(ProtocolFile, "*****     NEW VISIT-SEQUENCES     *****");
   fprintf(ProtocolFile, "\n\n");

   foreachinSEQAttribution(ligaroot->attrrules, X, vs)
   {
      def = lookup_def(vs->prodid);
      prod = def.VProd;
      fprintf(ProtocolFile, "\n*****     VS for rule %s     *****\n", prod->dname);
      foreachinSEQAttrrule(vs->attrrules, Y, action)
	 switch (typeof(action))
      {
      case KVisit:
	 visit = action.VVisit;
	 if (visit->symbno == LEAVE)
	 {
	    fprintf(ProtocolFile, "   LEAVE     to the ancestor for %d. time", visit->ord);
	    fprintf(ProtocolFile, "\n");
	 } else
	 {
	    fprintf(ProtocolFile, "   VISIT     no. %d to symbol no. %d", visit->ord, visit->symbno);
	    fprintf(ProtocolFile, "\n");
	 }
	 break;

      case KCall:
	 call = action.VCall;
	 if (strcmp (call->name, ASSIGNFCT) == 0)
	 {
	    retrievefirstSEQExpr(call->params, eval);
	    attr = LookupAttribute(eval.VAttracc->attrid);
	    fprintf(ProtocolFile, "   EVAL      %s[%d].%s",
		    attr->sname, eval.VAttracc->symbno, attr->aname);
	    if (grouping)
	    {
	       if (IdentAssign(call))
	       {
		  fprintf(ProtocolFile, "     ***  IS DELETED   ***\n");
		  removeSEQAttrrule(vs->attrrules, action);
	       } else
		  fprintf(ProtocolFile, "\n");
	    } else
	       fprintf(ProtocolFile, "\n");
	 } else
		fprintf(ProtocolFile, "   COMPUTE   function '%s' \n", call->name);
	 break;
      default:
	 break;
      }	/* end of switch */
   }
   fprintf(ProtocolFile, "\n\n\n");

}/* end of WriteVisitSequencesToListing */





/************************************************/
/* OptResultsOut                 */
/************************************************/

void 
OptResultsOut(root)
   Visit_Sequences root;
{
   Boolean grouping;

   grouping = group_all_option || var_group_option || var_group_list_option
      || stack_group_option || stack_group_list_option;

   PutResultsToInterface(root);

   if (grouping)
      ElimIdentAssignments(ligaroot);

   StatisticToListing(root);

   if (protocol_option)
   {

      WriteAttrStatusToListing(root);

      if (grouping)
      {
	 WriteGroupingResultsToListing(root);
      }
      WriteVisitSequencesToListing(root, grouping);

   }
}/* end of OptResultsOut */

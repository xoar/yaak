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

/* $Id: optgroup.c,v 4.4 2000/04/03 12:48:22 peter Exp $ */
static char rcs_id[] = "$Id: optgroup.c,v 4.4 2000/04/03 12:48:22 peter Exp $";

/************************************************/
/* */
/* Version : 1.0                          */
/* */
/* Module  : optgroup.c                   */
/* */
/* Contains the routines to build         */
/* groups of global variables             */
/* */
/************************************************/



/************************************************/
/* includes                   */
/************************************************/


#include <stdio.h>
#include <string.h>
#include "LIGA.h"
#include "LIGAMacros.h"
#include "OPTIM.h"
#include "OPTIMMacros.h"

#include "option_enums.h"
#include "option_types.h"

#include "optglobal.h"
#include "optfct.h"
#include "optidl.h"

#include "printerr.h"
#include "ligaconsts.h"
#include "optgroup.h"

/************************************************/
/* global variables               */
/************************************************/

Eval eval;	/* making this structure global will decrease the memory
		 * usage */

/************************************************/
/* functions                  */
/************************************************/

Boolean DisjointLifetime( /* Visit_Seq, Attributes, Attributes */ );
Boolean CheckCanEval( /* Visit_Seq, Attributes, int, int */ );

void HandleVarGroupListOption( /* Visit_Sequences */ );
void GroupGlobVarAttributes( /* Visit_Sequences */ );
void GroupAttributes( /* Visit_Sequences */ );




/************************************************/
/* DisjointLifetime                 */
/************************************************/

Boolean
DisjointLifetime(thisvs, groupattr, attr)
   Visit_Seq thisvs;
   Attributes groupattr, attr;
{
   SEQAttributes X, XX;
   Attributes vsgroupattr, vsattr;

/* fprintf(stderr, "DisjointLifetime\nAttributes in thisvs: \n");
   foreachinSEQAttributes(thisvs->attrs, X, vsgroupattr)
    fprintf(stderr, "\t%s.%s [%d, %d]\n", vsgroupattr->sname, 

   vsgroupattr->aname, vsgroupattr->birth,
		 vsgroupattr->death); */
   foreachinSEQAttributes(thisvs->attrs, X, vsgroupattr) {
      if (vsgroupattr->attrid == groupattr->attrid) {
/*	 fprintf(stderr, "group of %s.%s [%d, %d]\n",
		 vsgroupattr->sname, vsgroupattr->aname, vsgroupattr->birth,
		 vsgroupattr->death);*/

	 foreachinSEQAttributes(thisvs->attrs, XX, vsattr) {
	    if (vsattr->attrid == attr->attrid) {
/*	       fprintf(stderr, "%s.%s [%d, %d]\n",
		vsattr->sname, vsattr->aname, vsattr->birth, vsattr->death);*/
	       if (vsattr->birth == vsattr->death ||
		   vsgroupattr->birth == vsgroupattr->death)
		 return TRUE;
	       if (vsattr->birth == vsgroupattr->birth
		   || vsattr->death == vsgroupattr->death)
		  return (FALSE);
	       if (vsattr->birth < vsgroupattr->birth) {
		  if (vsattr->death > vsgroupattr->birth) /* peter */
		     return (FALSE);
	       } else
		  /* vsattr->birth > vsgroupattr->birth */
	       if (vsgroupattr->death > vsattr->birth)  /* peter */
		  return (FALSE);
	    }	/* if */
	 }	/* foreachin */
      }	/* if */
   }	/* foreachin */

   return (TRUE);
}/* end of DisjointLifetime */



/************************************************/
/* CheckCanEval                 */
/************************************************/

Boolean
CheckCanEval(vs, attr, birth, death)
   Visit_Seq vs;
   Attributes attr;
   int birth, death;
{
   SEQAction X, actionseq = vs->actions;
   Action action;
   Can_Eval thisCE;
   int i, action_counter;

   for (i = 0; i < birth; i++)
      actionseq = tailSEQAction(actionseq);
   action_counter = birth;
   eval->attrid = attr->attrid;	/* structure eval is global variable */
   foreachinSEQAction(actionseq, X, action) {
      if (++action_counter >= death)
	 break;
      switch (typeof(action)) {
      case KEval:
	 if (action.VEval->attrid == attr->attrid)
	    return (FALSE);
	 break;
      case KVisits:
	 if (action.VVisits->symbno != LEAVE) {
	    thisCE = LookupCE(action.VVisits->symbid, action.VVisits->ord);
	    IDLtempAction.VEval = eval;
	    if (InSeqAction(thisCE->actions, IDLtempAction))
	       return (FALSE);
	 }
	 break;
      default:
	 break;
      }	/* end of switch */
   }

   return (TRUE);

}/* end of CheckCanEval */


/************************************************/
/* CheckGrouping                */
/************************************************/

Boolean
CheckGrouping(attr, group)
   Attributes attr;
   Group group;
{
   SEQAttributes X, XX;
   Attributes groupattr, thisattr;
   SEQVisit_Seq Y;
   Visit_Seq thisvs;
   SEQSymbols Z;
   Symbols thissymb;
   Boolean groupattrfound, attrfound, mustanalyze;

   foreachinSEQAttributes(group->members, X, groupattr) {
      foreachinSEQVisit_Seq(optimroot->vi_seq, Y, thisvs) {
	 mustanalyze = FALSE;
	 foreachinSEQSymbols(thisvs->symbs, Z, thissymb) {
	    if (thissymb->symbid == groupattr->symbid ||
		thissymb->symbid == attr->symbid) {
	       mustanalyze = TRUE;
	       break;
	    }
	 }
	 if (mustanalyze) {
	    groupattrfound = FALSE;
	    attrfound = FALSE;
	    foreachinSEQAttributes(thisvs->attrs, XX, thisattr) {
	       if (thisattr->attrid == groupattr->attrid) {
		  groupattrfound = TRUE;
		  if (!CheckCanEval(thisvs, attr,
				    thisattr->birth, thisattr->death))
		     return (FALSE);
	       } else if (thisattr->attrid == attr->attrid) {
		  attrfound = TRUE;
		  if (!CheckCanEval(thisvs, groupattr,
				    thisattr->birth, thisattr->death))
		     return (FALSE);
	       }
	    }
	    if (groupattrfound && attrfound)
	       if (!DisjointLifetime(thisvs, groupattr, attr))
		  return (FALSE);
	 }
      }
   }

   return (TRUE);

}/* end of CheckGrouping */

/* void printinfo()
{
   Attributes thisattr;
   Visit_Seq thisvs;
   Symbols thissymb;
   SEQAttributes X;
   SEQVisit_Seq Y;
   SEQSymbols Z;
   int i=0;
   foreachinSEQVisit_Seq(optimroot->vi_seq, Y, thisvs) {
     fprintf(stderr," visitseq %d\n", ++i);
     foreachinSEQAttributes(thisvs->attrs, X, thisattr) {
       fprintf(stderr, "\t%s.%s [%d, %d]\n", 
	       thisattr->sname, 
	       thisattr->aname, 
	       thisattr->birth, 
	       thisattr->death); 
     }
   }
}
*/

/************************************************/
/* HandleVarGroupListOption            */
/************************************************/

void
HandleVarGroupListOption(root)
   Visit_Sequences root;
{
   OptList optp;
   ANamesList anl;
   SEQAttributes Y, YY, attrlist;
   Attributes firstattr, thisattr, listattr;
   Group group;
   Boolean grouping_possible;

   for (optp = optim_opts->opt_opts; optp; optp = optp->next) {
      if (optp->entry->flag == attr_group_var) {
	 attrlist = MkAttrList();
	 for (anl = optp->entry->attrs; anl; anl = anl->next)
	    attrlist = GetAttrsByName(attrlist, anl, STORGLVA);
	 foreachinSEQAttributes(root->glob_var, Y, thisattr)
	    foreachinSEQAttributes(attrlist, YY, listattr)
	    if (thisattr->attrid == listattr->attrid)
	    removeSEQAttributes(root->glob_var, thisattr);
	 while (!emptySEQAttributes(attrlist)) {
	    retrievefirstSEQAttributes(attrlist, firstattr);
	    group = MkGroup(firstattr, STORGLVA);
	    vargroupcounter++;
	    removefirstSEQAttributes(attrlist);
	    foreachinSEQAttributes(attrlist, Y, thisattr) {
	       if (group->typeid == thisattr->typeid) {
		  grouping_possible = CheckGrouping(thisattr, group);
		  if (!grouping_possible	 && thisattr->gen != 
		        CHAINATTR  ) {
		     char errmsgbuff[ERR_BUFF_LEN];
		     err_setpos(0, 0);
		     sprintf(errmsgbuff, "ATTRIBUTE %s.%s can't be in this GROUP.",
			     thisattr->sname, thisattr->aname);
		     err_print_warning(errmsgbuff);

		     fprintf(ProtocolFile, "*** WARNING: ATTRIBUTE   ");
		     fprintf(ProtocolFile, "%s.%s  ", thisattr->sname, thisattr->aname);
		     fprintf(ProtocolFile, "can`t be in this GROUP\n");
		  }
		  if (grouping_possible) {
		     appendrearSEQAttributes(group->members, thisattr);
		     removeSEQAttributes(attrlist, thisattr);
		  }
	       } else if (thisattr->gen != CHAINATTR) {
		  char errmsgbuff[ERR_BUFF_LEN];
		  err_setpos(0, 0);
		  sprintf(errmsgbuff, "ATTRIBUTE %s.%s can't be in this GROUP.",
			  thisattr->sname, thisattr->aname);
		  err_print_warning(errmsgbuff);

		  fprintf(ProtocolFile, "*** WARNING: ATTRIBUTE   ");
		  fprintf(ProtocolFile, "%s.%s  ", thisattr->sname, thisattr->aname);
		  fprintf(ProtocolFile, "can`t be in this GROUP\n");
	       }
	    }	/* end of foreachinSEQAttributes */
	    appendrearSEQGroup(root->groups, group);
	 }	/* end of while */
      }	/* end of if	 */
   }	/* end of for	 */

}/* end of HandleVarGroupListOption() */





/************************************************/
/* GroupGlobVarAttributes            */
/************************************************/

void
GroupGlobVarAttributes(root)
   Visit_Sequences root;
{
   SEQAttributes X;
   Attributes firstattr, thisattr;
   Group group;

   while (!emptySEQAttributes(root->glob_var)) {
      retrievefirstSEQAttributes(root->glob_var, firstattr);
      group = MkGroup(firstattr, STORGLVA);
      vargroupcounter++;
      removefirstSEQAttributes(root->glob_var);
      foreachinSEQAttributes(root->glob_var, X, thisattr) {
	 if (group->typeid == thisattr->typeid)
	    if (CheckGrouping(thisattr, group)) {
	       appendrearSEQAttributes(group->members, thisattr);
	       removeSEQAttributes(root->glob_var, thisattr);
	    }
      }	/* foreachin */
      appendrearSEQGroup(root->groups, group);
   }	/* while */

}/* end of GroupGlobVarAttributes */





/************************************************/
/* GroupAttributes               */
/************************************************/

void GroupAttributes(root)
     Visit_Sequences root;
{
  eval = NEval;	/* eval is global variable */
  /*    printinfo(); */
  if (no_grouping_option)
    return;
  if (var_group_list_option) 
    {
      (void) HandleVarGroupListOption(root);
    }
  if (group_all_option || var_group_option) 
    {
      (void) GroupGlobVarAttributes(root);
    }
}/* end of GroupAttributes */

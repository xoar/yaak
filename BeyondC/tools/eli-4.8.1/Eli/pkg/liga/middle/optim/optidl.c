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

/* $Id: optidl.c,v 4.5 1998/06/24 10:55:03 peter Exp $ */
static char rcs_id[] = "$Id: optidl.c,v 4.5 1998/06/24 10:55:03 peter Exp $";

/************************************************/
/* */
/* Version : 1.0                          */
/* */
/* Module  : optidl.c                     */
/* */
/* Contains help routines for all         */
/* other modules of liga.optim            */
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
#include "middle_mem.h"
/* Includes for option handling */
#include "option_enums.h"
#include "option_types.h"

#include "optglobal.h"
#include "printerr.h"
#include "optidl.h"
#include "ligaconsts.h"

/*********************************************
* global variables and types                 *
**********************************************/

Attributes *attr_array;
a_Can_Eval *CE_array;
a_Marked *mark_array;
a_Boolean *visit_considered;
Boolean *eval_considered;

/************************************************/
/* functions                  */
/************************************************/

Symbols optim_MkSymbol( /* Symb, int */ );

Visits optim_MkVisit( /* int, int, int */ );

ANamesList GetAttrSpez( /* OptList, optoptflag */ );

Group MkGroup( /* Attributes, int */ );

SEQAttributes GetAttrsByName( /* SEQAttributes, AttrName, int */ );
SEQAttributes MkAttrList( /* no parameter */ );

Attributes MkAttribute( /* Attrdef, Symb */ );
Attributes GetAttrInstance( /* int, int, SEQAttributes */ );
Attributes GetAttrByName( /* String, String */ );
Attributes LookupAttribute( /* int */ );

Can_Eval MkCanEval( /* int, int */ );
Can_Eval LookupCE( /* int, int */ );

Marked LookupMark( /* int, int */ );

void InitAttrArray( /* no parameters */ );
void InitLookupArrays( /* no parameters */ );
void InitEvalVisit( /* Can_Eval */ );
void ResetEvalVisit( /* Can_Eval */ );
void InitMarkArray( /* Can_Eval */ );
void ResetMarkArray( /* Can_Eval */ );






/***********************************************************************/
/* optim_MkSymbol                             */
/***********************************************************************/

Symbols 
optim_MkSymbol(symb_def, symbno)
   Symb symb_def;
   int symbno;
{
   Symbols newsymb;

   newsymb = NSymbols;
   newsymb->symbid = symb_def->did;
   newsymb->symbno = symbno;
   newsymb->name =
      middle_tempMalloc(__FILE__,__LINE__, strlen(symb_def->dname)+1);
   strcpy(newsymb->name, symb_def->dname);

   return (newsymb);
}/* end of optim_MkSymbol */

/***********************************************************************/
/* optim_MkVisit                              */
/***********************************************************************/

Visits 
optim_MkVisit(symbno, ord, symbid)
   int symbno, ord, symbid;
{
   Visits visit;

   visit = NVisits;
   visit->symbno = symbno;
   visit->ord = ord;
   visit->symbid = symbid;

   return (visit);

}/* end of optim_MkVisit */





/***********************************************************************/
/* GetAttrSpez                             */
/***********************************************************************/

ANamesList 
GetAttrSpez(optionseq, key)
   OptList optionseq;
   optoptflag key;
{
   OptList optp;
   int notfound = TRUE;

   optp = optim_opts->opt_opts;
   while (optp && notfound)
   {
      if (optp->entry->flag == key)
	 notfound = FALSE;
      else
	 optp = optp->next;
   }	/* while */
   if (optp)
      return (optp->entry->attrs);
   else
      return ((ANamesList) NULL);
}/* end of GetAttrSpez */



/************************************************/
/* MkGroup                  */
/************************************************/

Group 
MkGroup(attr, key)
   Attributes attr;
   int key;
{
   Group newgroup;

   newgroup = NGroup;
   initializeSEQAttributes(newgroup->members);
   newgroup->groupid = attr->attrid;
   newgroup->typeid = attr->typeid;
   newgroup->class = key;
   newgroup->name =
      middle_tempMalloc(__FILE__,__LINE__,
                        strlen(attr->sname) + strlen(attr->aname) + 1);
   strcpy(newgroup->name, attr->sname);
   strcat(newgroup->name, attr->aname);
   appendrearSEQAttributes(newgroup->members, attr);

   return (newgroup);
}/* end of MkGroup */





/************************************************************************/
/* GetAttrsByName					 */
/* */
/* get attributes which should be implemented in one Group		 */
/************************************************************************/

SEQAttributes 
GetAttrsByName(attrlist, anl, key)
   SEQAttributes attrlist;
   ANamesList anl;
   int key;
{
   IdList anames;
   SEQAttributes X, Z, sourcelist;
   Attributes thisattr, listattr;
   Boolean new, found, newinstance, withsymbol = TRUE;

   if (key == STORGLVA)
      sourcelist = optimroot->glob_var;
   else
      sourcelist = optimroot->single_visit;

   if (!strcmp(anl->symbname, "NO_SYMBOL_NAME"))
      withsymbol = FALSE;

   for (anames = anl->names; anames; anames = anames->next)
   {
      found = FALSE;
      foreachinSEQAttributes(sourcelist, X, thisattr)
      {
	 new = FALSE;
	 if (withsymbol)
	 {
	    if (!strcmp(thisattr->sname, anl->symbname) &&
		!strcmp(thisattr->aname, anames->ident))
	    {
	       new = TRUE;
	       found = TRUE;
	    }
	 } else if (!strcmp(thisattr->aname, anames->ident))
	 {
	    new = TRUE;
	    found = TRUE;
	 }
	 if (found && new)
	 {
	    newinstance = TRUE;
	    foreachinSEQAttributes(attrlist, Z, listattr)
	    {
	       if (listattr->attrid == thisattr->attrid)
	       {
		  newinstance = FALSE;
		  break;
	       }
	    }
	    if (newinstance)
	       appendfrontSEQAttributes(attrlist, thisattr);
	    else
	    {
	       if (withsymbol)
	       {
		  char errmsgbuff[ERR_BUFF_LEN];
		  err_setpos(0, 0);
		  sprintf(errmsgbuff, "ATTRIBUTE %s.%s is multiple declared in OPTION!",
			  anl->symbname, anames->ident);
		  err_print_warning(errmsgbuff);
		  fprintf(ProtocolFile, "*** WARNING: ATTRIBUTE %s.%s ",
			  anl->symbname, anames->ident);
		  fprintf(ProtocolFile, " is multiple declared in OPTION!\n");
	       } else
	       {
		  char errmsgbuff[ERR_BUFF_LEN];
		  err_setpos(0, 0);
		  sprintf(errmsgbuff, "ATTRIBUTES with name .%s are multiple declared in OPTION.",
			  anames->ident);
		  err_print_warning(errmsgbuff);

		  fprintf(ProtocolFile, "*** WARNING: ATTRIBUTES with name .%s ", anames->ident);
		  fprintf(ProtocolFile, " are multiple declared in OPTION!\n");
	       }	/* end of else of if(withsymbol)	 */
	    }	/* end of else of if(newinstance)	 */
	 }	/* end of if(found&&new)		 */
      }	/* end of foreachinSEQAttributes	 */
      if (!found)
      {
	 if (key == STORGLVA)
	 {
	    char errmsgbuff[ERR_BUFF_LEN];
	    err_setpos(0, 0);
	    if (withsymbol)
	    {
	       sprintf(errmsgbuff, "ATTRIBUTE %s.%s is not a global VARIABLE.",
		       anl->symbname, anames->ident);
	       fprintf(ProtocolFile, "*** INFO: ATTRIBUTE %s.%s ",
		       anl->symbname, anames->ident);
	       fprintf(ProtocolFile, " is not a global VARIABLE !\n");
	    } else
	    {
	       sprintf(errmsgbuff, "ATTRIBUTES .%s are not global VARIABLES.",
		       anames->ident);
	       fprintf(ProtocolFile, "*** INFO: ATTRIBUTES with name .%s ", anames->ident);
	       fprintf(ProtocolFile, " are not global VARIABLES !\n");
	    }
	    err_print_note(errmsgbuff);
	 } else
	 {
	    char errmsgbuff[ERR_BUFF_LEN];
	    err_setpos(0, 0);
	    if (withsymbol)
	    {
	       sprintf(errmsgbuff, "ATTRIBUTE %s.%s are not a global STACK.",
		       anl->symbname, anames->ident);
	       fprintf(ProtocolFile, "*** INFO: ATTRIBUTE %s.%s ",
		       anl->symbname, anames->ident);
	       fprintf(ProtocolFile, " are not a global STACK !\n");
	    } else
	    {
	       sprintf(errmsgbuff, "ATTRIBUTES with name .%s are not global STACKS.",
		       anames->ident);
	       fprintf(ProtocolFile, "*** INFO: ATTRIBUTES with name .%s ", anames->ident);
	       fprintf(ProtocolFile, " are not global STACKS !\n");
	    }	/* end of else of if(withsymbol)	 */
	    err_print_note(errmsgbuff);
	 }	/* end of else of if(key==...)		 */
      }	/* end of if(!found)			 */
   }	/* end of for(anames=...)		 */

   return (attrlist);

}/* end of GetAttrsByName */





/***********************************************************************/
/* MkAttrList                             */
/* */
/* returns a pointer to a initialized empty attribute list     */
/***********************************************************************/

SEQAttributes 
MkAttrList()
{
   Eval eval;

   eval = NEval;
   initializeSEQAttributes(eval->params);

   return (eval->params);

}/* end of MkAttrList */





/***********************************************************************/
/* MkAttribute                            */
/***********************************************************************/

Attributes 
MkAttribute(attrdef, symbdef)
   Attrdef attrdef;
   Symb symbdef;
{
   Attributes newattr;

   newattr = NAttributes;
   newattr->attrid = attrdef->did;
   newattr->symbid = symbdef->did;
   newattr->aname = middle_tempMalloc(__FILE__,__LINE__,strlen(attrdef->name) + 1);
   newattr->sname = middle_tempMalloc(__FILE__,__LINE__,strlen(symbdef->dname) + 1);
   strcpy(newattr->aname, attrdef->name);
   strcpy(newattr->sname, symbdef->dname);
   newattr->typeid = attrdef->typeid;
   newattr->class = attrdef->class;
   newattr->gen = attrdef->gen;
   newattr->part = attrdef->part;
   if (symbdef->tornt == SYMBTERM)
   {
      newattr->termattr = TRUE;
   } else
   {
      newattr->termattr = FALSE;
   }
   newattr->BnNF = TRUE;
   newattr->not_used = FALSE;

   return (newattr);
}/* end of MkAttribute */





/***********************************************************************/
/* GetAttrInstance                           */
/* */
/* returns a pointer of attr with attrid and symbno          */
/***********************************************************************/

Attributes 
GetAttrInstance(attrid, symbno, attrlist)
   int attrid, symbno;
   SEQAttributes attrlist;
{
   SEQAttributes X;
   Attributes thisattr;

   foreachinSEQAttributes(attrlist, X, thisattr)
   {
      if (thisattr->attrid == attrid && thisattr->symbno == symbno)
      {
	 return (thisattr);
      }
   }

   return (NULL);

}/* end of GetAttrInstance */





/***********************************************************************/
/* GetAttrByName                            */
/* */
/* returns a pointer to the attribute sname.aname            */
/***********************************************************************/

Attributes 
GetAttrByName(sname, aname)
   String sname, aname;
{
   SEQAttributes X;
   Attributes thisattr;
   Boolean found = FALSE;

   foreachinSEQAttributes(optimroot->attrs, X, thisattr)
   {
      if (strcmp(thisattr->sname, sname) == 0 &&
	  strcmp(thisattr->aname, aname) == 0)
      {
	 found = TRUE;
	 break;
      }
   }
   if (found)
   {
      return (thisattr);
   } else
   {
      return (NULL);
   }

}/* end of GetAttrByName */





/***********************************************************************/
/* LookupAttribute                            */
/* */
/* returns a pointer to the attribute with id did            */
/***********************************************************************/

Attributes 
LookupAttribute(did)
   int did;
{

   return (attr_array[did]);

}/* end of LookupAttribute */





/***********************************************************************/
/* MkCanEcal                               */
/* */
/* returns a pointer to a new allocated CAN_EVAL set            */
/***********************************************************************/

Can_Eval 
MkCanEval(symbid, v)
   int symbid, v;
{
   Can_Eval thisCE;

   thisCE = NCan_Eval;
   initializeSEQAction(thisCE->actions);
   initializeSEQMarked(thisCE->marks);
   thisCE->symbid = symbid;
   thisCE->ord = v;

   return (thisCE);

}/* end of MkCanEval */





/******************************************************************/
/* LookupCE                           */
/* */
/* returns a pointer to the Can_Eval set with id [symbid,ord]   */
/******************************************************************/

Can_Eval 
LookupCE(symbid, ord)
   int symbid, ord;
{
   return (CE_array[symbid][ord]);

}/* end of LookupCE */





/******************************************************************/
/* LookupMark                          */
/* */
/* returns a pointer to the Can_Eval set with id [symbid,ord]   */
/******************************************************************/

Marked 
LookupMark(symbid, ord)
   int symbid, ord;
{

   return (mark_array[symbid][ord]);

}/* end of LookupMark */





/***********************************************************************/
/* InitAttrArray                            */
/* */
/* builds the attribute_arraytable of dids               */
/***********************************************************************/

void 
InitAttrArray()
{
   SEQAttributes X;
   Attributes thisattr;
   attr_array =
      (Attributes*) middle_tempMalloc
         (__FILE__,__LINE__,(max_definitions+1) *sizeof(Attributes));

   foreachinSEQAttributes(optimroot->attrs, X, thisattr)
      attr_array[thisattr->attrid] = thisattr;

}/* end of InitAttrArray */





/************************************************/
/* InitLookupArrays              */
/************************************************/

void 
InitLookupArrays()
{
   int i, j;

      CE_array = (a_Can_Eval*) 
               middle_tempMalloc(__FILE__,__LINE__,(max_definitions+1) * sizeof(Can_Eval) * MAX_VISITS);
   mark_array = (a_Marked*) 
                middle_tempMalloc(__FILE__,__LINE__,(max_definitions+1) * sizeof(Marked) * MAX_VISITS);
   visit_considered = (a_Boolean *) 
                      middle_tempMalloc(__FILE__,__LINE__,(max_definitions+1) * sizeof(Boolean) * MAX_VISITS);
   eval_considered = (Boolean *) 
                      middle_tempMalloc(__FILE__,__LINE__,(max_definitions+1) * sizeof(Boolean));

   for (i = 0; i < max_definitions+1; i++)
   {   for (j = 0; j < MAX_VISITS; j++)
       {
	 CE_array[i][j] = NULL;
	 mark_array[i][j] = NULL;
	 visit_considered[i][j] = FALSE;
       }
       eval_considered[i] = FALSE;
   }
}/* end of InitLookupArrays */


/************************************************/
/* InitEvalVisit                */
/************************************************/

void 
InitEvalVisit(thisCE)
   Can_Eval thisCE;
{
   SEQAction X;
   Action thisaction;

   foreachinSEQAction(thisCE->actions, X, thisaction)
      switch (typeof(thisaction))
   {
   case KEval:
      eval_considered[thisaction.VEval->attrid] = TRUE;
      break;
   case KVisits:
      visit_considered[thisaction.VVisits->symbid][thisaction.VVisits->ord] = TRUE;
      break;
   default:
      break;
   }	/* end of switch */

}/* end of InitEvalVisit */





/************************************************/
/* ResetEvalVisit                */
/************************************************/

void 
ResetEvalVisit(thisCE)
   Can_Eval thisCE;
{
   SEQAction X;
   Action thisaction;

   foreachinSEQAction(thisCE->actions, X, thisaction)
      switch (typeof(thisaction))
   {
   case KEval:
      eval_considered[thisaction.VEval->attrid] = FALSE;
      break;
   case KVisits:
      visit_considered[thisaction.VVisits->symbid][thisaction.VVisits->ord] = FALSE;
      break;
   default:
      break;
   }	/* end of switch */

}/* end of ResetEvalVisit */





/************************************************/
/* InitMarkArray                */
/************************************************/

void 
InitMarkArray(thisCE)
   Can_Eval thisCE;
{
   SEQMarked X;
   Marked thismark;

   foreachinSEQMarked(thisCE->marks, X, thismark)
      mark_array[thismark->symbid][thismark->ord] = thismark;

}/* end of InitMarkArray */





/************************************************/
/* ResetMarkArray                */
/************************************************/

void 
ResetMarkArray(thisCE)
   Can_Eval thisCE;
{
   SEQMarked X;
   Marked thismark;

   foreachinSEQMarked(thisCE->marks, X, thismark)
      mark_array[thismark->symbid][thismark->ord] = NULL;

}/* end of ResetMarkArray */

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

/* $Id: exptrav.c,v 4.2 1998/04/28 14:26:13 ludi Exp $ */

static char rcs_id[] = "$Id: exptrav.c,v 4.2 1998/04/28 14:26:13 ludi Exp $";

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		exptrav.c					*
*	File:		exptrav.c					*
*	Contents:	functions to travel through attainable graph	*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	20 Mar 1991					*
*	Last change:	08 Jun 1992 UKas (CONSTITUENT(S) corrected)	*
*									*
\***********************************************************************/

#include <stdio.h>
#include <string.h>
#include "middle_mem.h"
#include "LIGA.h"
#include "LIGAMacros.h"

/* Includes for option handling */
#include "option_enums.h"
#include "option_types.h"

#include "ligaconsts.h"
#include "expconst.h"
#include "exp_types.h"
#include "expref.h"
#include "expidl.h"
#include "expand.h"
#include "expincl.h"
#include "expchain.h"
#include "expconstit.h"
#include "exptrav.h"
#include "exp_prot.h"


/* * GLOBAL VARIABLES */

int inclcount;	/* number of different INCLUDING constructs	 */
int constscount;	/* number of CONSTITUENT(S) constructs		 */

int markedsymbs;	/* number of symbols marked for chain		 */
int markedprods;	/* number of productions marked for chain	 */
int newattrs;	/* total number of new attributes		 */

char *newattrname;	/* name for new attributes			 */


/* * LOCAL FUNCTIONS */

#ifdef __STDC__
static char* msg_compose_4(char *s1, char *s2, char *s3, char*s4)
#else
static char* msg_compose_4(s1, s2, s3, s4)
char *s1, *s2, *s3, *s4;
#endif
{ char *tmp=middle_tempMalloc(__FILE__, __LINE__,
			      strlen(s1)+strlen(s2)+
			      strlen(s1)+strlen(s2)+1);
  sprintf(tmp, "%s%s%s%s",s1,s2,s3,s4);
  return tmp;
}

static int
#ifdef __STDC__
equal_includings(IncNode incl1, IncNode incl2)
#else
equal_includings(incl1, incl2)
   IncNode incl1, incl2;
#endif
/* compare lists of INCLUDING attributes for IncNodes incl1, incl2	 */
{
   SEQSymbattr tmp1, tmp2;
   Symbattr sptr, sattr;
   int found;

   if (incl1->dep != incl2->dep)
   {
      return (FALSE);
   }	/* if */
   /* search for all attributes in list of incl1 in list of incl2	 */
   foreachinSEQSymbattr(inclattrsOfIncluding(incl1->incl), tmp1, sattr)
   {
      foreachinSEQSymbattr(inclattrsOfIncluding(incl2->incl), tmp2, sptr)
      {
	 found = (symbdefOfSymbattr(sattr) == symbdefOfSymbattr(sptr)
		  && attrdefOfSymbattr(sattr) == attrdefOfSymbattr(sptr));
	 if (found)
	    break;
      }	/* foreachinSEQSymbattr */
      if (!found)
	 return (FALSE);
   }	/* foreachinSEQSymbattr */

   /* search for all attributes in list of incl2 in list of incl1	 */
   foreachinSEQSymbattr(inclattrsOfIncluding(incl2->incl), tmp1, sattr)
   {
      foreachinSEQSymbattr(inclattrsOfIncluding(incl1->incl), tmp2, sptr)
      {
	 found = (symbdefOfSymbattr(sattr) == symbdefOfSymbattr(sptr)
		  && attrdefOfSymbattr(sattr) == attrdefOfSymbattr(sptr));
	 if (found)
	    break;
      }	/* foreachinSEQSymbattr */
      if (!found)
	 return (FALSE);
   }	/* foreachinSEQSymbattr */

   return (TRUE);
}/* equal_includings() */

static void
#ifdef __STDC__
append_incl(Including incl, int pid, int tid, int dep)
#else
append_incl(incl, pid, tid, dep)
   Including incl;
   int pid;
   int tid;
   int dep;
#endif
/* append INCLUDING construct to global list of includings		 */
/* and assign names for attributes to be generated 			 */
{
   IncNode new;
   IncNode iptr;
   int found;

   new = (IncNode) middle_tempMalloc(__FILE__, __LINE__, sizeof(struct IncNode));
   if (!new)
      deadly("expand: out of memory\n");
   new->prodid = pid;
   new->typeid = tid;
   new->dep = dep;
   new->incl = incl;

   if (IDENT_INCL)
   {
      /* search for identical INCLUDINGs */
      found = FALSE;
      for (iptr = includings; iptr && !found; iptr = iptr->next)
      {
	 if (equal_includings(iptr, new))
	 {
	    found = TRUE;
	    /* copy name of attribute to be generated */
	    genattrOfIncluding(new->incl) =
	       genattrOfIncluding(iptr->incl);
	    /* insert into list of identical constructs */
	    new->next = iptr->next;
	    new->same = iptr->same;
	    iptr->same = new;
	 }	/* if */
      }	/* for */

      if (!found)
      {
	 /* no identical INCLUDING found */

	 /* create new attribute name */
	 (void) sprintf(newattrname, "%s%d",
			INCL_ATTR, inclcount++);
	 genattrOfIncluding(new->incl) =
	    (char *) middle_Malloc(__FILE__, __LINE__, strlen(newattrname) + 1);
	 if (!genattrOfIncluding(new->incl))
	    deadly("expand: out of memory\n");
	 (void) strcpy(genattrOfIncluding(new->incl),
		       newattrname);

	 /* insert INCLUDING into global list */
	 new->same = (IncNode) NULL;
	 new->next = includings;
	 includings = new;
      }	/* if */
   }
   /* if */
   else
   {
      /* create new attribute name */
      (void) sprintf(newattrname, "%s%d", INCL_ATTR, inclcount++);
      genattrOfIncluding(new->incl) =
	 (char *) middle_Malloc(__FILE__, __LINE__, strlen(newattrname) + 1);
      if (!genattrOfIncluding(new->incl))
	 deadly("expand: out of memory\n");
      (void) strcpy(genattrOfIncluding(new->incl), newattrname);

      /* insert INCLUDING into global list */
      new->same = (IncNode) NULL;
      new->next = includings;
      includings = new;
   }	/* else */
}/* append_incl() */

static int
#ifdef __STDC__
check_incl(Including incl, int pid, int dep)
#else
check_incl(incl, pid, dep)
   Including incl;
   int pid;
   int dep;
#endif
/* check INCLUDING construct						 */
{
   int tid;
   Symb symb;
   SEQSymbattr tmp1, traveller;
   Symbattr sa1, sa2;
   SEQAttrdef tmp2;
   Attrdef ad;

   /* remove terminals from Symbattr list: */
   /* low level IDL avoids quadratic list search */

   LSymbattr travlist = incl->inclattrs;
   LSymbattr *tailaddr = &(incl->inclattrs); /* target for next link */

   while (travlist) {
	if (torntOfSymb(symbref(symbdefOfSymbattr(travlist->value))) 
		!= SYMBTERM) {
		(*tailaddr) = travlist;		/* keep this link */
		tailaddr = &(travlist->next);	/* target for next link */
	}
	travlist = travlist->next;
   }
   (*tailaddr) = (LSymbattr)0;
   /* end of remove terminals */
   
   /* production must not be root production */
   if (lhsOfProd(prodref(pid)) == root_sid)
   {
      print_err(
		rowOfIncluding(incl),
		colOfIncluding(incl),
		"INCLUDING in root production", INRT_ERRID);
      (void) fprintf(ProtocolFile,
		     "\n*** ERROR  INCLUDING in root production %s\n\n",
		     dnameOfProd(prodref(pid)));
   }
   /* list of attributes to be included must not be empty */
   if (emptySEQSymbattr(inclattrsOfIncluding(incl)))
   {
      print_err(
		rowOfIncluding(incl),
		colOfIncluding(incl),
		"invalid INCLUDING: no attributes", NAII_ERRID);
      (void) fprintf(ProtocolFile,
		     "\n*** ERROR  invalid INCLUDING: no attributes, ");
      (void) fprintf(ProtocolFile,
		     "line %d, col %d in production %s\n\n",
		     rowOfIncluding(incl),
		     colOfIncluding(incl),
		     dnameOfProd(prodref(pid)));
   }	/* if */

   /* search definition of first attribute in list of INCLUDING */
   retrievefirstSEQSymbattr(inclattrsOfIncluding(incl), sa1);
   symb = symbref(symbdefOfSymbattr(sa1));
   foreachinSEQAttrdef(attrsOfSymb(symb), tmp2, ad)
   {
      if (didOfAttrdef(ad) == attrdefOfSymbattr(sa1))
	 break;
   }	/* foreachinSEQAttrdef */

   /* get type id of the attribute */
   tid = typeidOfAttrdef(ad);

   /* the tests below will be performed only */
   /* for lists with more than one entry */
   if (emptySEQSymbattr(tailSEQSymbattr(inclattrsOfIncluding(incl))))
      return (dep ? DIDVOID : tid);

   /* attributes in list must not be on same symbol */
   foreachinSEQSymbattr(inclattrsOfIncluding(incl), traveller, sa1)
   {
      foreachinSEQSymbattr(tailSEQSymbattr(traveller), tmp1, sa2)
      {
	 if (symbdefOfSymbattr(sa1) == symbdefOfSymbattr(sa2))
	 {
	    print_err(
		      rowOfIncluding(incl),
		      colOfIncluding(incl),
		      "multiple symbol occurrence in INCLUDING",
		      IMSO_ERRID);
	    (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	    (void) fprintf(ProtocolFile,
			   "multiple symbol occurrence in INCLUDING, ");
	    (void) fprintf(ProtocolFile,
			   "line %d, col %d in production %s\n\n",
			   rowOfIncluding(incl),
			   colOfIncluding(incl),
			   dnameOfProd(prodref(pid)));
	 }	/* if */
      }	/* foreachinSEQSymbattr */
   }	/* foreachinSEQSymbattr */

   if (dep)
      return (DIDVOID);

   /* compare all types in attribute list of INCLUDING */
   foreachinSEQSymbattr(inclattrsOfIncluding(incl), tmp1, sa1)
   {
      symb = symbref(symbdefOfSymbattr(sa1));
      foreachinSEQAttrdef(attrsOfSymb(symb), tmp2, ad)
      {
	 if (didOfAttrdef(ad) == attrdefOfSymbattr(sa1))
	    break;
      }	/* foreachinSEQAttrdef */

      /* compare types */
      if (typeidOfAttrdef(ad) != tid)
      {
	 print_err(
		   rowOfIncluding(incl),
		   colOfIncluding(incl),
		   "type conflict in INCLUDING", ITYP_ERRID);
	 (void) fprintf(ProtocolFile,
			"\n*** ERROR  type conflict in INCLUDING, ");
	 (void) fprintf(ProtocolFile,
			"line %d, col %d in production %s\n\n",
			rowOfIncluding(incl),
			colOfIncluding(incl),
			dnameOfProd(prodref(pid)));
      }	/* if */
   }	/* foreachinSEQSymbattr */
   return (dep ? DIDVOID : tid);
}/* check_incl() */

static void
#ifdef __STDC__
ins_chainacc(Chainacc ca, int pid, Call call, int isdef)
#else
ins_chainacc(ca, pid, call, isdef)
   Chainacc ca;
   int pid;
   Call call;
   int isdef;
#endif
/* search chain node and enter reference to chain access		 */
{
   ChainNode cn;
   ChAccNode newcan;

   /* search for chain node */
   for (cn = chains; cn && cn->did != chainidOfChainacc(ca); cn = cn->next);

   /* entry must have been found */
   if (!cn)
   {
      print_err(rowOfChainacc(ca), colOfChainacc(ca),
		"Internal error #1 in exptrav.c", NO_ERRID);
      return;
   }	/* if */
   /* create new node for list of chain accesses */
   newcan = (ChAccNode) middle_tempMalloc(__FILE__, __LINE__, sizeof(struct ChAccNode));
   if (!newcan)
      deadly("expand: out of memory\n");
   newcan->acc = ca;
   newcan->prodid = pid;
   newcan->symbdid = ith_symbol_of_prod(symbnoOfChainacc(ca), pid);
   newcan->accall = call;
   newcan->isdef = isdef;
   /* insert node into list */
   newcan->next = cn->accesses;
   cn->accesses = newcan;
}/* ins_chainacc() */

static int
#ifdef __STDC__
equal_constits(ConstNode constit1, ConstNode constit2)
#else
equal_constits(constit1, constit2)
   ConstNode constit1, constit2;
#endif
/* compare CONSTITUENT(S) constructs					 */
{
   SEQSymbattr tmp1, tmp2;
   SEQExpr stmp1, stmp2;
   Expr shexp1, shexp2;
   Symbattr sptr, sattr;
   int found;

   /* both must be either CONSTITUENT or CONSTITUENTS */
   if (singleOfConstit(constit1->constit)
       != singleOfConstit(constit2->constit))
      return (FALSE);

   if (constit1->dep != constit2->dep)
      return (FALSE);

   if (!singleOfConstit(constit1->constit))	/* UK */
      /* compare names of types and functions */
      if (strcmp(constit1->list_name, constit2->list_name)
	  || strcmp(constit1->concat_name, constit2->concat_name)
	  || strcmp(constit1->creat_name, constit2->creat_name)
	  || strcmp(constit1->empty_name, constit2->empty_name))
	 return (FALSE);

   /* equal shielding symbols */
   foreachinSEQExpr(constit1->shield_symbs, stmp1, shexp1)
   {
      found = FALSE;
      foreachinSEQExpr(constit2->shield_symbs, stmp2, shexp2)
      {
	 found = vOfVal(ExprToVal(shexp1)) ==
	    vOfVal(ExprToVal(shexp2));
	 if (found)
	    break;
      }
      if (!found)
	 return (FALSE);
   }
   foreachinSEQExpr(constit2->shield_symbs, stmp2, shexp2)
   {
      found = FALSE;
      foreachinSEQExpr(constit1->shield_symbs, stmp1, shexp1)
      {
	 found = vOfVal(ExprToVal(shexp1)) ==
	    vOfVal(ExprToVal(shexp2));
	 if (found)
	    break;
      }
      if (!found)
	 return (FALSE);
   }

   /* search for all attributes in list of constit1 in list of constit2 */
   foreachinSEQSymbattr(constattrsOfConstit(constit1->constit), tmp1, sattr)
   {
      found = FALSE;
      foreachinSEQSymbattr(constattrsOfConstit(constit2->constit), tmp2, sptr)
      {
	 found = (symbdefOfSymbattr(sattr) == symbdefOfSymbattr(sptr)
		  && attrdefOfSymbattr(sattr) == attrdefOfSymbattr(sptr));
	 if (found)
	    break;
      }	/* foreachinSEQSymbattr */
      if (!found)
	 return (FALSE);
   }	/* foreachinSEQSymbattr */

   /* search for all attributes in list of constit2 in list of constit1 */
   foreachinSEQSymbattr(constattrsOfConstit(constit2->constit), tmp1, sattr)
   {
      found = FALSE;
      foreachinSEQSymbattr(constattrsOfConstit(constit1->constit), tmp2, sptr)
      {
	 found = (symbdefOfSymbattr(sattr) == symbdefOfSymbattr(sptr)
		  && attrdefOfSymbattr(sattr) == attrdefOfSymbattr(sptr));
	 if (found)
	    break;
      }	/* foreachinSEQSymbattr */
      if (!found)
	 return (FALSE);
   }	/* foreachinSEQSymbattr */

   return (TRUE);
}/* equal_constits() */

static void
#ifdef __STDC__
append_const(Constit constit, Call call, int parmno, int pid, int tid,
	     char *t_name, char *c_name, char *s_name, char *e_name,
	     int dep, SEQExpr shield)
#else
append_const(constit, call, parmno, pid, tid,
	     t_name, c_name, s_name, e_name, dep, shield)
   Constit constit;
   Call call;
   int parmno;
   int pid;
   int tid;
   char *t_name;
   char *c_name;
   char *s_name;
   char *e_name;
   int dep;
   SEQExpr shield;
#endif
/* append CONSTITUENT(S) construct to global list of constituent(s)s	 */
/* and assign names for attributes to be generated 			 */
{
   ConstNode new;
   ConstNode cptr;
   SEQSymbattr tmp1;
   Symbattr sa;
   Symb symb;
   SEQAttrdef tmp2;
   Attrdef ad;
   int found;
   CoSyNode cs;
   SyAttrNode san;

   new = (ConstNode) middle_tempMalloc(__FILE__, __LINE__, sizeof(struct ConstNode));
   if (!new)
      deadly("expand: out of memory\n");
   new->prodid = pid;
   new->typeid = tid;
   new->dep = dep;
   new->constit = constit;
   new->constcall = call;
   new->parmno = parmno;
   new->shield_symbs = shield;

   /* look at subtree specification */
   if (subtreeOfConstit(constit))
   {
      new->subdid = ith_symbol_of_prod(subtreeOfConstit(constit), pid);
   }
   /* if */
   else
   {
      new->subdid = 0;
   }	/* else */

   if (singleOfConstit(constit))
   {
      new->list_tid = DIDNON;
      new->list_name = "ERRType";
      new->concat_name = "ERRconcat";
      new->creat_name = "ERRcreat";
      new->empty_name = "ERRempty";
   }
   /* if */
   else
   {
      if (t_name)
      {
	 new->list_name = t_name;
	 new->list_tid = name_typeid(t_name);
      }
      /* if */
      else
      {
	 /* get type id of list type */
	 new->list_tid = list_typeid(tid, &(new->list_name));
      }	/* else */

      if (c_name)
      {
	 new->concat_name = c_name;
      }
      /* if */
      else
      {
	 new->concat_name = middle_Malloc(__FILE__, __LINE__, 
				   strlen(CONCAT_FUNC) +
				   strlen(new->list_name) + 1);
	 (void) sprintf(new->concat_name, "%s%s",
			CONCAT_FUNC,
			new->list_name);
      }	/* else */

      if (s_name)
      {
	 new->creat_name = s_name;
      }
      /* if */
      else
      {
	 new->creat_name = middle_Malloc(__FILE__, __LINE__, 
				  strlen(CREAT_FUNC) +
				  strlen(new->list_name) + 1);
	 (void) sprintf(new->creat_name, "%s%s",
			CREAT_FUNC,
			new->list_name);
      }	/* else */

      if (e_name)
      {
	 new->empty_name = e_name;
      }
      /* if */
      else
      {
	 new->empty_name = middle_Malloc(__FILE__, __LINE__, 
				  strlen(NULL_FUNC) +
				  strlen(new->list_name) + 1);
	 (void) sprintf(new->empty_name, "%s%s",
			NULL_FUNC,
			new->list_name);
      }	/* else */
   }	 /* else */

   /* search for identical CONSTITUENT(S)s */
   for (cptr = constituents; cptr; cptr = cptr->next)
   {
      if (equal_constits(cptr, new))
      {
	 /* copy name of attribute to be generated */
	 genattrOfConstit(new->constit) =
	    genattrOfConstit(cptr->constit);

	 new->cancelled = cptr->cancelled;
	 new->src = cptr->src;

	 /* insert into list of identical constructs */
	 new->next = cptr->next;
	 new->same = cptr->same;
	 cptr->same = new;

	 /* work is done */
	 return;
      }	/* if */
   }	/* for */

   /* no identical CONSTITUENT(S) found */

   new->cancelled = FALSE;
   new->src = (CoSyNode) NULL;

   /* build list of source symbols and attributes */
   foreachinSEQSymbattr(constattrsOfConstit(constit), tmp1, sa)
   {
      /* get symbol and attribute definition */
      symb = symbref(symbdefOfSymbattr(sa));
      foreachinSEQAttrdef(attrsOfSymb(symb), tmp2, ad)
      {
	 if (didOfAttrdef(ad) == attrdefOfSymbattr(sa))
	    break;
      }	/* foreachinSEQAttrdef */

      /* search for symbol entry */
      found = FALSE;
      for (cs = new->src; cs; cs = cs->next)
      {
	 if (cs->symbdid == didOfSymb(symb))
	 {
	    found = TRUE;
	    break;
	 }	/* if */
      }	/* for */

      if (found)
      {
	 /* search for attribute entry */
	 found = FALSE;
	 for (san = cs->attrs; san; san = san->next)
	 {
	    if (san->ad == ad)
	    {
	       found = TRUE;
	       break;
	    }	/* if */
	 }	/* for */
	 /* if the attribute was found,	 */
	 /* we don't have to enter it	 */
	 if (!found)
	 {
	    san = (SyAttrNode) middle_Malloc(__FILE__, __LINE__, sizeof(struct SyAttrNode));
	    if (!san)
	       deadly("expand: out of memory\n");
	    san->ad = ad;
	    san->next = cs->attrs;
	    cs->attrs = san;
	 }	/* if */
      }
      /* if */
      else
      {
	 cs = (CoSyNode) middle_Malloc(__FILE__, __LINE__, sizeof(struct CoSyNode));
	 san = (SyAttrNode) middle_Malloc(__FILE__, __LINE__, sizeof(struct SyAttrNode));
	 if (!cs || !san)
	    deadly("expand: out of memory\n");
	 cs->symbdid = didOfSymb(symb);
	 cs->attrs = san;
	 san->ad = ad;
	 san->next = (SyAttrNode) NULL;
	 cs->next = new->src;
	 new->src = cs;
      }	/* else */
   }	/* foreachinSEQSymbattr */

   if (singleOfConstit(constit))
   {
      /* cancel if multiple attributes at one source symbol */
      for (cs = new->src; cs; cs = cs->next)
      {
	 if (cs->attrs->next)
	 {
	    new->cancelled = TRUE;
	    break;
	 }	/* if */
      }	/* for */
   }	/* if */
   /* create new attribute name */
   (void) sprintf(newattrname, "%s%d", CONST_ATTR, constscount++);
   genattrOfConstit(new->constit) = (char *) middle_Malloc(__FILE__, __LINE__, strlen(newattrname) + 1);
   if (!genattrOfConstit(new->constit))
      deadly("expand: out of memory\n");
   (void) strcpy(genattrOfConstit(new->constit), newattrname);

   /* insert CONSTITUENT(S) into global list */
   new->same = (ConstNode) NULL;
   new->next = constituents;
   constituents = new;
}/* append_const() */

static int
#ifdef __STDC__
check_constit(Constit constit, int pid, int dep)
#else
check_constit(constit, pid, dep)
   Constit constit;
   int pid;
   int dep;
#endif
/* check CONSTITUENT(S) construct					 */
{
   int tid;
   Symb symb;
   SEQSymbattr tmp1, traveller;
   Symbattr sa1, sa2;
   SEQAttrdef tmp2;
   Attrdef ad;

   /* list of attributes to be derived must not be empty */
   if (emptySEQSymbattr(constattrsOfConstit(constit)))
   {
      print_err(
		rowOfConstit(constit),
		colOfConstit(constit),
		"invalid CONSTITUENT(S): no attributes", NAIC_ERRID);
      (void) fprintf(ProtocolFile,
		     "\n*** ERROR  invalid CONSTITUENT(S): no attributes, ");
      (void) fprintf(ProtocolFile,
		     "line %d, col %d in production %s\n\n",
		     rowOfConstit(constit),
		     colOfConstit(constit),
		     dnameOfProd(prodref(pid)));
   }	/* if */
   /* search definition of first attribute in list of CONSTITUENT(S) */
   retrievefirstSEQSymbattr(constattrsOfConstit(constit), sa1);
   symb = symbref(symbdefOfSymbattr(sa1));
   foreachinSEQAttrdef(attrsOfSymb(symb), tmp2, ad)
   {
      if (didOfAttrdef(ad) == attrdefOfSymbattr(sa1))
	 break;
   }	/* foreachinSEQAttrdef */

   /* get type id of the attribute */
   tid = typeidOfAttrdef(ad);

   /* the tests below will be performed only */
   /* for lists with more than one entry */
   if (emptySEQSymbattr(tailSEQSymbattr(constattrsOfConstit(constit))))
      return (dep ? DIDVOID : tid);

   /* attributes of CONSTITUENT must not be on same symbol */
   if (singleOfConstit(constit))
      foreachinSEQSymbattr(constattrsOfConstit(constit), traveller, sa1)
   {
      foreachinSEQSymbattr(tailSEQSymbattr(traveller), tmp1, sa2)
      {
	 if (symbdefOfSymbattr(sa1) == symbdefOfSymbattr(sa2))
	 {
	    print_err(
		      rowOfConstit(constit),
		      colOfConstit(constit),
		      "multiple symbol occurrence in CONSTITUENT",
		      CMSO_ERRID);
	    (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	    (void) fprintf(ProtocolFile,
			   "multiple symbol occurrence in CONSTITUENT, ");
	    (void) fprintf(ProtocolFile,
			   "line %d, col %d in production %s\n\n",
			   rowOfConstit(constit),
			   colOfConstit(constit),
			   dnameOfProd(prodref(pid)));
	 }	/* if */
      }	/* foreachinSEQSymbattr */
   }	/* foreachinSEQSymbattr */
   if (dep)
      return (DIDVOID);

   /* compare all types in attribute list of CONSTITUENT(S) */
   foreachinSEQSymbattr(constattrsOfConstit(constit), tmp1, sa1)
   {
      symb = symbref(symbdefOfSymbattr(sa1));
      foreachinSEQAttrdef(attrsOfSymb(symb), tmp2, ad)
      {
	 if (didOfAttrdef(ad) == attrdefOfSymbattr(sa1))
	    break;
      }	/* foreachinSEQAttrdef */

      /* compare types */
      if (typeidOfAttrdef(ad) != tid)
      {
	 print_err(
		   rowOfConstit(constit),
		   colOfConstit(constit),
		   "type conflict in CONSTITUENT(S)", CTYP_ERRID);
	 (void) fprintf(ProtocolFile,
			"\n*** ERROR  type conflict in CONSTITUENT(S), ");
	 (void) fprintf(ProtocolFile,
			"line %d, col %d in production %s\n\n",
			rowOfConstit(constit),
			colOfConstit(constit),
			dnameOfProd(prodref(pid)));
      }	/* if */
   }	/* foreachinSEQSymbattr */
   return (tid);
}/* check_constit() */


/* * GLOBAL FUNCTIONS */

/* * functions for INCLUDING expansion */

int
#ifdef __STDC__
incl_in_call(Call call, int pid, int dep)
#else
incl_in_call(call, pid, dep)
   Call call;
   int pid;
   int dep;
#endif
/* find all INCLUDING constructs in the given call and add them to the	 */
/* global list. Return number of INCLUDINGs found			 */
/* *** recursive function ***					 */
{
   int incl_count;
   SEQExpr tmp;
   Expr param;
   int param_count;
   int tid;
   int in_dep;

   incl_count = 0;
   param_count = 0;
   foreachinSEQExpr(paramsOfCall(call), tmp, param)
   {
      param_count++;
      in_dep = dep
	 || (param_count > 1 && !strcmp(nameOfCall(call), DEPFCT));
      if (typeof(param) == KCall)
      {
	 /* recursive function call */
	 incl_count += incl_in_call(
				    ExprToCall(param), pid, in_dep);
      }
      /* if */
      else if (typeof(param) == KIncluding)
      {
	 incl_count++;
	 in_dep |= !strcmp(nameOfCall(call), VOIDFCT);
	 tid = check_incl(ExprToIncluding(param), pid, in_dep);
	 append_incl(ExprToIncluding(param), pid, tid, in_dep);
      }	/* else */
   }	/* foreachinSEQExpr */

   return (incl_count);
}/* incl_in_call() */

void
#ifdef __STDC__
mark_incl_trans(int sid, IncNode incptr)
#else
mark_incl_trans(sid, incptr)
   int sid;
   IncNode incptr;
#endif
/* mark transport symbols and productions for INCLUDING			 */
/* *** recursive function ***					 */
{
   SNode symbs;
   int prod;

   /* avoid marked symbols */
   /* (this guarantees termination of recursion) */
   if (symbflag(sid) != no_sflag)
      return;

   /* root symbol must not be marked */
   if (sid == root_sid)
   {
      print_err(
		rowOfIncluding(incptr->incl),
		colOfIncluding(incptr->incl),
		"in some contexts none of the INCLUDING symbols is found",
		OPIN_ERRID);
      (void) fprintf(ProtocolFile, "\n*** ERROR  ");
      (void) fprintf(ProtocolFile,
	     "in some contexts none of the INCLUDING symbols is found, ");
      (void) fprintf(ProtocolFile,
		     "line %d, col %d in production %s\n",
		     rowOfIncluding(incptr->incl),
		     colOfIncluding(incptr->incl),
		     dnameOfProd(prodref(incptr->prodid)));
   }	/* if */
   symbflag(sid) = trnsp_symb;
   markedsymbs++;
   protout(ProtocolFile,"   ");
   gen_incl_attr(sid, incptr);
   newattrs++;

   /* mark all productions with the symbol on the rhs */
   for (symbs = symbrdown(sid); symbs; symbs = symbs->down)
   {
      prod = symbs->prodid;

      /* ignore source productions */
      if (prodflag(prod) & start_prod)
	 continue;

      /* ignore already marked productions */
      if (prodflag(prod) & trans_prod)
	 continue;

      prodflag(prod) |= trans_prod;
      markedprods++;

      /* call function recursively to mark lhs symbol for transfer */
      mark_incl_trans(lhsOfProd(prodref(prod)), incptr);
   }	/* for */
}/* mark_incl_trans() */



void
#ifdef __STDC__
chain_in_call(Call call, int pid)
#else
chain_in_call(call, pid)
   Call call;
   int pid;
#endif
/* find all CHAINACC constructs in the given call and add them to their	 */
/* chain nodes in the global list					 */
/* *** recursive function ***					 */
{
   SEQExpr start;
   SEQExpr tmp;
   Expr param;

   /* search for chain access on lhs of assignment */
   if (!strcmp(nameOfCall(call), ASSIGNFCT))
   {
      retrievefirstSEQExpr(paramsOfCall(call), param);
      if (typeof(param) == KChainacc)
	 ins_chainacc(ExprToChainacc(param), pid, call, TRUE);
      start = tailSEQExpr(paramsOfCall(call));
   }
   /* if */
   else
   {
      start = paramsOfCall(call);
   }	/* else */
   foreachinSEQExpr(start, tmp, param)
   {
      switch (typeof(param))
      {
      case KCall:
	 /* recursive function call */
	 chain_in_call(ExprToCall(param), pid);
	 break;
      case KChainacc:
	 ins_chainacc(ExprToChainacc(param), pid, call, FALSE);
	 break;
      }	/* switch */
   }	/* foreachinSEQExpr */
}/* chain_in_call() */

void
#ifdef __STDC__
mark_chain_trans(int sid, ChainNode ch, ChAccNode can, int pid, int first)
#else
mark_chain_trans(sid, ch, can, pid, first)
   int sid;
   ChainNode ch;
   ChAccNode can;
   int pid;
   int first;
#endif
/* mark chain symbols and productions					 */
/* *** recursive function ***					 */
{
   SNode symbs;
   int prod;

   /* avoid symbols marked otherwise than chain start symbol */
   /* (this guarantees termination of recursion) */
   if (symbflag(sid) != no_sflag && !first)
      return;

   /* root symbol must not be marked */
   if (sid == root_sid)
   {
      if (pid == can->prodid)
      {
	 print_err(
		   rowOfChainacc(can->acc),
		   colOfChainacc(can->acc),
		   msg_compose_4("Illegal CHAIN access at root symbol: ",
				 dnameOfSymb(symbref(can->symbdid)),
				 ".", 
				 dnameOfChain(ch->chain)),
		   OPCH_ERRID);
	 (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	 (void) fprintf(ProtocolFile,
			"Illegal CHAIN access at root symbol %s ",
			dnameOfSymb(symbref(can->symbdid)));
	 (void) fprintf(ProtocolFile,
			"in line %d, col %d of production %s\n",
			rowOfChainacc(can->acc),
			colOfChainacc(can->acc),
			dnameOfProd(prodref(pid)));
	 ch->cancelled = TRUE;
      }
      /* if */
      else
      {  
	 print_err(rowOfProd(prodref(pid)),
		   colOfProd(prodref(pid)),
		   msg_compose_4("CHAINSTART missing above chain use: ",
				 dnameOfSymb(symbref(can->symbdid)),
				 ".", 
				 dnameOfChain(ch->chain)),
		   OPCH_ERRID);
	 (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	 (void) fprintf(ProtocolFile, "%s",
			msg_compose_4("CHAINSTART missing above chain use: ",
				 dnameOfSymb(symbref(can->symbdid)),
				 ".", 
				 dnameOfChain(ch->chain)));
	 (void) fprintf(ProtocolFile,
			"in production %s\n",
			dnameOfProd(prodref(pid)));
	 ch->cancelled = TRUE;
      }	/* else */
   }	/* if */
   if (symbflag(sid) == no_sflag)
   {
      symbflag(sid) = chain_symb;
      markedsymbs++;
      gen_chain_attr(
		     sid,
		     pregenattrOfChainStart(ch->starts->start),
		     postgenattrOfChainStart(ch->starts->start),
		     typeidOfChain(ch->chain));
      newattrs += 2;
   }	/* if */
   /* mark all productions with the symbol on the rhs */
   for (symbs = symbrdown(sid); symbs; symbs = symbs->down)
   {
      prod = symbs->prodid;

      /* ignore marked productions (start_prod and trans_prod) */
      if (prodflag(prod) != no_pflag && prodflag(prod) != target_prod)
	 continue;

      prodflag(prod) |= trans_prod;
      markedprods++;

      /* call function recursively to mark lhs symbol for chain */
      if (first)
      {
	 mark_chain_trans(
			  lhsOfProd(prodref(prod)),
			  ch, can,
			  symbs->prodid, FALSE);
      }
      /* if */
      else
      {
	 mark_chain_trans(
			  lhsOfProd(prodref(prod)),
			  ch, can,
			  pid, FALSE);
      }	/* else */
   }	/* for */
}/* mark_chain_trans() */

/* * functions for CONSTITUENT(S) expansion */

int
#ifdef __STDC__
constits_in_call(Call call, int pid, int dep)
#else
constits_in_call(call, pid, dep)
   Call call;
   int pid;
   int dep;
#endif
/* find all CONSTITUENT(S) constructs in the given call and add them to	 */
/* the global list. return number of CONSTITUENT(S)s found		 */
/* *** recursive function ***					 */
{
   int counter;
   SEQExpr tmp;
   SEQExpr nameseq;
   SEQExpr shieldseq;
   int hasshield;
   Expr shexp;
   Val shval;
   Expr param;
   Expr namexpr, cexpr;
   int param_count;
   int in_dep;
   int tid;
   char *name1, *name2, *name3, *name4;

   counter = 0;
   param_count = 0;
   foreachinSEQExpr(paramsOfCall(call), tmp, param)
   {
      param_count++;
      in_dep = dep ||
	 (param_count > 1 && !strcmp(nameOfCall(call), DEPFCT));
      name1 = NULL;
      name2 = NULL;
      name3 = NULL;
      name4 = NULL;
      shieldseq = (SEQExpr) NULL;
      cexpr = param;

      if ((typeof(cexpr) == KCall) &&
	  (!strcmp(nameOfCall(ExprToCall(cexpr)), WITHFCT)))
      {
	 nameseq = tailSEQExpr(paramsOfCall(ExprToCall(cexpr)));

	 /* retrieve first name */
	 if (!emptySEQExpr(nameseq))
	 {
	    retrievefirstSEQExpr(nameseq, namexpr);
	    if (typeof(namexpr) != KName)
	    {
	       print_err(
			 rowOfCall(ExprToCall(cexpr)),
			 colOfCall(ExprToCall(cexpr)),
			 "Internal error #2 in exptrav.c",
			 NO_ERRID);
	       return (0);
	    }	/* if */
	    name1 = nOfName(ExprToName(namexpr));
	    nameseq = tailSEQExpr(nameseq);
	 }	/* if */
	 /* retrieve second name */
	 if (!emptySEQExpr(nameseq))
	 {
	    retrievefirstSEQExpr(nameseq, namexpr);
	    if (typeof(namexpr) != KName)
	    {
	       print_err(
			 rowOfCall(ExprToCall(cexpr)),
			 colOfCall(ExprToCall(cexpr)),
			 "Internal error #3 in exptrav.c",
			 NO_ERRID);
	       return (0);
	    }	/* if */
	    name2 = nOfName(ExprToName(namexpr));
	    nameseq = tailSEQExpr(nameseq);
	 }	/* if */
	 /* retrieve third name */
	 if (!emptySEQExpr(nameseq))
	 {
	    retrievefirstSEQExpr(nameseq, namexpr);
	    if (typeof(namexpr) != KName)
	    {
	       print_err(
			 rowOfCall(ExprToCall(cexpr)),
			 colOfCall(ExprToCall(cexpr)),
			 "Internal error #4 in exptrav.c",
			 NO_ERRID);
	       return (0);
	    }	/* if */
	    name3 = nOfName(ExprToName(namexpr));
	    nameseq = tailSEQExpr(nameseq);
	 }	/* if */
	 /* retrieve fourth name */
	 if (!emptySEQExpr(nameseq))
	 {
	    retrievefirstSEQExpr(nameseq, namexpr);
	    if (typeof(namexpr) != KName)
	    {
	       print_err(
			 rowOfCall(ExprToCall(cexpr)),
			 colOfCall(ExprToCall(cexpr)),
			 "Internal error #5 in exptrav.c",
			 NO_ERRID);
	       return (0);
	    }	/* if */
	    name4 = nOfName(ExprToName(namexpr));
	 }	/* if */
	 retrievefirstSEQExpr(
			      paramsOfCall(ExprToCall(cexpr)),
			      cexpr);
      }	/* WITHFCT */
      if ((typeof(cexpr) == KCall) &&
	  (!strcmp(nameOfCall(ExprToCall(cexpr)), SHIELDFCT)))
      {
	 shieldseq = tailSEQExpr(paramsOfCall(
					      ExprToCall(cexpr)));
	 retrievefirstSEQExpr(
			      paramsOfCall(ExprToCall(cexpr)),
			      cexpr);
	 hasshield = TRUE;
      }
      /* SHIELDFCT */
      else
	 hasshield = FALSE;

      if (typeof(cexpr) == KCall)
      {
	 /* recursive function call */
	 in_dep |= !strcmp(nameOfCall(ExprToCall(cexpr)),
			   VOIDFCT);
	 counter += constits_in_call(
				     ExprToCall(cexpr), pid, in_dep);
	 continue;
      }	/* Call of other function */
      if (typeof(cexpr) == KConstit)
      {
	 if (!hasshield)
	 {	/* set default shielding */
	    shval = NVal;
	    rowOfVal(shval) = 0;
	    colOfVal(shval) = 0;
	    if (subtreeOfConstit(ExprToConstit(cexpr)))
	    {
	       /* default is subtree symbol */
	       vOfVal(shval) =
		  ith_symbol_of_prod(
				     subtreeOfConstit(
						ExprToConstit(cexpr)), pid);
	       shexp = ValToExpr(shval);
	       appendfrontSEQExpr(shieldseq, shexp);
	    } else
	    {	/* default is lhs symbol */
	       vOfVal(shval) =
		  lhsOfProd(prodref(pid));
	       shexp = ValToExpr(shval);
	       appendfrontSEQExpr(shieldseq, shexp);
	    }	/* else */
	 }
	 tid = check_constit(ExprToConstit(cexpr), pid, in_dep);
	 append_const(ExprToConstit(cexpr), call, param_count,
		      pid, tid, name1, name2, name3, name4,
		      in_dep, shieldseq);
	 counter++;
	 continue;
      }	/* Constit */
   }	/* foreachinSEQExpr */

   return (counter);
}/* constits_in_call() */

void
#ifdef __STDC__
set_symb_flag(int sid, ConstNode cptr)
#else
set_symb_flag(sid, cptr)
   int sid;
   ConstNode cptr;
#endif
{/* mark symbol sid if not yet marked */
   /* a constituent(s) symbol has been found in a subtree */
   if (!(symbflag(sid) & trnsp_symb))
   {
      symbflag(sid) |= trnsp_symb;
      markedsymbs++;
      protout(ProtocolFile,"   ");
      gen_constit_attr(sid, cptr);
      newattrs++;
   }	/* if */
}/* set_symb_flag */

void
#ifdef __STDC__
set_trans_prod(int prod)
#else
set_trans_prod(prod)
   int prod;
#endif
{/* mark production for transport */
   if (!(prodflag(prod) & trans_prod))
   {
      prodflag(prod) |= trans_prod;
      markedprods++;
/*      protout(ProtocolFile,
	      "      production %s\n",
	      dnameOfProd(prodref(prod)));
*/
   }	/* if */
}/* set_trans_prod */

#ifdef __STDC__
void
clear_visited(void)
#else
void
clear_visited()
#endif
/* clear visited symbol flags                                */
{
   SEQDef tmp;
   Def def;

   foreachinSEQDef(defseqOfAttrEval(IdlStruct), tmp, def)
   {
      if (typeof(def) == KSymb)
      {
	 symbvisited(didOfDef(def)) = FALSE;
      }	/* if */
   }	/* foreachinSEQDef */
}/* clear_visited() */

int
#ifdef __STDC__
rec_reach_constit_src(int sid, ConstNode cptr)
#else
rec_reach_constit_src(sid, cptr)
   int sid;
   ConstNode cptr;
#endif
/* recursive depth first search: CONSTITUENT(S) source is reachable from sid
 * without passing a shielded symbol source symbols themselves are
 * investigated only if not recurring on exit: TRUE: a path is found; trnsp
 * flags are set for sid and symbols on that path FALSE: no path found in
 * this search; there may be a path (due to results of outer recursions) */
{
   SNode symbs;
   SNode rhsymbs;
   int prod;

   /* all productions of sid are visited or will be visited in an outer
    * recursion or a path from sid to source has been found previously */
   if (symbvisited(sid) || (symbflag(sid) & trnsp_symb))
      return (symbflag(sid) & trnsp_symb);

   /* all productions of sid are visited here until source is found, if it is
    * reachable */
   symbvisited(sid) = TRUE;

   /* examine all productions with the symbol on the lhs */
   for (symbs = symbldown(sid); symbs; symbs = symbs->down)
   {
      prod = symbs->prodid;

      /* examine subtrees of all symbols on the rhs */
      for (rhsymbs = prodright(prod)->right;
	   rhsymbs;
	   rhsymbs = rhsymbs->right)
      {
	 /* source symb found */
	 if ((symbflag(rhsymbs->symbdid) & src_symb))
	 {
	    set_symb_flag(sid, cptr);
	    return (TRUE);
	 }	/* if */
	 /* don't step into shielded subtrees */
	 if (symbflag(rhsymbs->symbdid) & shield_symb)
	    continue;

	 /* look for indirect reachability */
	 if (rec_reach_constit_src(rhsymbs->symbdid, cptr))
	 {
	    set_symb_flag(sid, cptr);
	    return (TRUE);
	 }	/* if */
      }	/* for */
   }	/* for */
   return (FALSE);
}/* rec_reach_constit_src */


int
#ifdef __STDC__
reach_constit_src(int sid, ConstNode cptr)
#else
reach_constit_src(sid, cptr)
   int sid;
   ConstNode cptr;
#endif
/* depth first search: CONSTITUENT(S) source is reachable from sid without
 * passing a shielded symbol if sid is a source itself, it must derive a
 * source recursively on exit: TRUE: a path is found; trnsp flags are set for
 * sid and symbols on that path FALSE: there is no such path completechk is
 * set for sid */
{
   int res;

   if (symbflag(sid) & trnsp_symb)
      return (TRUE);

   if (symbcompletechk(sid))
      return (FALSE);

   res = rec_reach_constit_src(sid, cptr);
   clear_visited();

   if (!res)
      symbcompletechk(sid) = TRUE;

   return (res);
}/* reach_constit_src */

int
#ifdef __STDC__
mark_constit_trans(int sid, ConstNode cptr)
#else
mark_constit_trans(sid, cptr)
   int sid;
   ConstNode cptr;
#endif
/* mark transport productions for CONSTITUENT(S)			 */
/* *** recursive function ***					 */
{
   SNode symbs;
   SNode rhsymbs;
   int prod;
   int nfound;

   /* is the source reachable from sid ? */
   if (!reach_constit_src(sid, cptr))
      return (FALSE);

   /* are the productions of sid already analyzed in an outer recursion ? */
   if (symbprodvisited(sid))
      return (TRUE);
   symbprodvisited(sid) = TRUE;

   /* examine all productions with the symbol on the lhs */
   for (symbs = symbldown(sid); symbs; symbs = symbs->down)
   {
      prod = symbs->prodid;
      nfound = 0;

      /* examine subtrees of all symbols on the rhs */
      for (rhsymbs = prodright(prod)->right;
	   rhsymbs;
	   rhsymbs = rhsymbs->right)
      {
	 /* look for direct source symbol	 */
	 if (symbflag(rhsymbs->symbdid) & src_symb)
	 {
	    set_trans_prod(prod);
	    /* mark as source production */
	    prodflag(prod) |= start_prod;
	    nfound++;
	 }	/* if src_symb */
	 /* don't step into shielded subtrees */
	 if (symbflag(rhsymbs->symbdid) & shield_symb)
	    continue;

	 /* look for indirect reachability */
	 if (reach_constit_src(rhsymbs->symbdid, cptr))
	 {
	    set_trans_prod(prod);
	    (void) mark_constit_trans(rhsymbs->symbdid, cptr);
	    nfound++;
	 }	/* if reach_constit_src */
	 if ((nfound > 1) && singleOfConstit(cptr->constit))
	 {
	    /* multiple CONSTITUENT symbols reachable */
	    print_err(
		      rowOfProd(prodref(prod)),
		      colOfProd(prodref(prod)),
		      "multiple CONSTITUENT symbols in this context",
		      COML_ERRID);
	    if (!cptr->cancelled)
	       print_err(
			 rowOfConstit(cptr->constit),
			 colOfConstit(cptr->constit),
			 "multiple CONSTITUENT symbols",
			 COML_ERRID);
	    (void) fprintf(ProtocolFile, "\n*** ERROR  ");
	    (void) fprintf(ProtocolFile,
			   "multiple CONSTITUENT symbols ");
	    (void) fprintf(ProtocolFile,
			   "in production %s in line %d, col %d\n\n",
			   dnameOfProd(prodref(prod)),
			   rowOfProd(prodref(prod)),
			   rowOfProd(prodref(prod)));
	    cptr->cancelled = TRUE;
	 }	/* nfound > 1 */
	 /* no CONSTITUENT symbol reachable is reported on expansion */
      }	/* for prodright */
   }	/* for symbldown */
   return (symbflag(sid) & trnsp_symb);
}/* mark_constit_trans() */


/***********************\
* end of exptrav.c	*
\***********************/

/* HaDeS */

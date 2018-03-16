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
/* $Id: expidl.c,v 4.1 1997/08/29 09:09:06 peter Exp $ */
static char rcs_id[] = "$Id: expidl.c,v 4.1 1997/08/29 09:09:06 peter Exp $";

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		expidl.c					*
*	File:		expidl.c					*
*	Contents:	functions for the IDL data structures		*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	18 Feb 1991					*
*	Last change:	25 Sep 1991					*
*									*
\***********************************************************************/

#include <stdio.h>
#include <string.h>

#include "LIGA.h"
#include "LIGAMacros.h"

/* Includes for option handling */
#include "option_enums.h"
#include "option_types.h"

#include "ligaconsts.h"
#include "expconst.h"
#include "exp_types.h"
#include "exp_io.h"
#include "expand.h"
#include "expref.h"
#include "expidl.h"
#include "middle_mem.h"

/* * GLOBAL VARIABLES */

AttrEval IdlStruct;

/* * GLOBAL FUNCTIONS */

int
#ifdef __STDC__
ith_symbol_of_prod(int index, int pid)
#else
ith_symbol_of_prod(index, pid)
   int index;
   int pid;
#endif
/* get the did of the symbol with the given index in the production	 */
{
   SNode sptr;

   /* check entry of reference table */
   if (exp_ref_tab[pid].entry_tag != prod_entry)
   {
      print_err(0, 0, "Internal error #1 in expidl.c", NO_ERRID);
      return (0);
   }	/* if */
   /* walk through list of symbols in this production */
   for (sptr = prodright(pid); sptr && index; sptr = sptr->right)
      index--;

   /* check if symbol has been found */
   if (sptr)
      return (sptr->symbdid);
   else
      return (0);
}/* ith_symbol_of_prod() */

void
#ifdef __STDC__
gen_assign(
	   Attribution attrib,
	   int row, int col,
	   int s1no, int a1did,
	   int s2no, int a2did,
	   int isvoid)
#else
gen_assign(attrib, row, col, s1no, a1did, s2no, a2did, isvoid)
   Attribution attrib;
   int row, col;
   int s1no, a1did;
   int s2no, a2did;
   int isvoid;
#endif
/* generate new assignment						 */
{
   Call new;
   Expr expr;
   Attracc access;
   Name v_name;

   /* initialize call */
   new = NCall;
   nameOfCall(new) = ASSIGNFCT;
   initializeSEQExpr(paramsOfCall(new));
   rowOfCall(new) = row;
   colOfCall(new) = col;

   /* initialize left hand side of new assignment */
   access = NAttracc;
   symbnoOfAttracc(access) = s1no;
   attridOfAttracc(access) = a1did;
   rowOfAttracc(access) = row;
   colOfAttracc(access) = col;
   ExprToAttracc(expr) = access;
   appendrearSEQExpr(paramsOfCall(new), expr);

   /* initialize right hand side of new assignment */
   access = NAttracc;
   symbnoOfAttracc(access) = s2no;
   attridOfAttracc(access) = a2did;
   rowOfAttracc(access) = row;
   colOfAttracc(access) = col;
   ExprToAttracc(expr) = access;
   appendrearSEQExpr(paramsOfCall(new), expr);

   /* append special name to mark assignments to VOID attributes */
   if (isvoid)
   {
      v_name = NName;
      nOfName(v_name) = TNVOID;
      rowOfName(v_name) = row;
      colOfName(v_name) = col;
      ExprToName(expr) = v_name;
      appendrearSEQExpr(paramsOfCall(new), expr);
   }	/* if */
   /* insert new assignment into attribution */
   ExprToCall(expr) = new;
   appendrearSEQAttrrule(attrrulesOfAttribution(attrib), expr);

}/* gen_assign() */

void
#ifdef __STDC__
gen_incl_attr(int sid, IncNode incptr)
#else
gen_incl_attr(sid, incptr)
   int sid;
   IncNode incptr;
#endif
/* generate attribute for INCLUDING expansion				 */
{
   Attrdef newattr;
   char *name;

   name = genattrOfIncluding(incptr->incl);

   newattr = NAttrdef;

   protout(ProtocolFile, "%s.%s\n", dnameOfSymb(symbref(sid)), name);
   didOfAttrdef(newattr) = newdid();
   nameOfAttrdef(newattr) = (char *) middle_Malloc(__FILE__, __LINE__, strlen(name) + 1);
   if (!nameOfAttrdef(newattr))
      deadly("expand: out of memory\n");
   (void) strcpy(nameOfAttrdef(newattr), name);
   rowOfAttrdef(newattr) = rowOfIncluding(incptr->incl);
   colOfAttrdef(newattr) = colOfIncluding(incptr->incl);
   typeidOfAttrdef(newattr) = incptr->typeid;
   classOfAttrdef(newattr) = ATCLINH;
   storeOfAttrdef(newattr) = STORUNKN;
   genOfAttrdef(newattr) = GENINCL;
   prodidOfAttrdef(newattr) = 0;

   appendfrontSEQAttrdef(attrsOfSymb(symbref(sid)), newattr);
   /***** IMPORTANT NOTE: *****/
   /* The new attribute must always be appended at the *front* 	 */
   /* of the list. The function to replace INCLUDING constructs	 */
   /* by accesses to the new attribute relies on the fact that the	 */
   /* new attribute is the first attribute in the list.		 */
}/* gen_incl_attr() */

void
#ifdef __STDC__
gen_chain_attr(int sid, char *name1, char *name2, int typeid)
#else
gen_chain_attr(sid, name1, name2, typeid)
   int sid;
   char *name1, *name2;
   int typeid;
#endif
/* generate attributes for CHAIN expansion				 */
{
   Attrdef newattr;
   ANamesList attrnameslist;
   IdList attrid;

   /* generate inherited (pre) attribute */
   newattr = NAttrdef;
   didOfAttrdef(newattr) = newdid();
   nameOfAttrdef(newattr) = (char *) middle_Malloc(__FILE__, __LINE__, strlen(name1) + 1);
   if (!nameOfAttrdef(newattr))
      deadly("expand: out of memory\n");
   (void) strcpy(nameOfAttrdef(newattr), name1);
   rowOfAttrdef(newattr) = rowOfSymb(symbref(sid));
   colOfAttrdef(newattr) = colOfSymb(symbref(sid));
   typeidOfAttrdef(newattr) = typeid;
   classOfAttrdef(newattr) = ATCLINH;
   storeOfAttrdef(newattr) = STORUNKN;
   genOfAttrdef(newattr) = GENCHAIN;
   prodidOfAttrdef(newattr) = 0;
   appendfrontSEQAttrdef(attrsOfSymb(symbref(sid)), newattr);

   /* generate synthesized (post) attribute */
   newattr = NAttrdef;
   didOfAttrdef(newattr) = newdid();
   nameOfAttrdef(newattr) = (char *) middle_Malloc(__FILE__, __LINE__, strlen(name2) + 1);
   if (!nameOfAttrdef(newattr))
      deadly("expand: out of memory\n");
   (void) strcpy(nameOfAttrdef(newattr), name2);
   rowOfAttrdef(newattr) = rowOfSymb(symbref(sid));
   colOfAttrdef(newattr) = colOfSymb(symbref(sid));
   typeidOfAttrdef(newattr) = typeid;
   classOfAttrdef(newattr) = ATCLSYNT;
   storeOfAttrdef(newattr) = STORUNKN;
   genOfAttrdef(newattr) = GENCHAIN;
   prodidOfAttrdef(newattr) = 0;
   appendfrontSEQAttrdef(attrsOfSymb(symbref(sid)), newattr);

   /***** IMPORTANT NOTE: *****/
   /* The new attributes must always be appended at the *front* 	 */
   /* of the list. The synthesized attribute must be the first and	 */
   /* the inherited attribute is the second attribute in the list.	 */
   /* The function to replace CHAIN accesses by accesses to the	 */
   /* new attributes relies on this fact.				 */

   /* build grouping-option for optim: */

   attrnameslist = (ANamesList) middle_Malloc(__FILE__, __LINE__, sizeof(struct _anameslist));
   attrid = (IdList) middle_Malloc(__FILE__, __LINE__, sizeof(struct _idlist));
   if (!attrnameslist || !attrid)
      deadly("expand: out of memory\n");
   attrnameslist->symbname = (char *) middle_Malloc(__FILE__, __LINE__, 
				     strlen(dnameOfSymb(symbref(sid))) + 1);
   if (!attrnameslist->symbname)
      deadly("expand: out of memory\n");
   (void) strcpy(attrnameslist->symbname, dnameOfSymb(symbref(sid)));
   attrid->next = (IdList) NULL;
   attrid->ident = (char *) middle_Malloc(__FILE__, __LINE__, strlen(name1) + 1);
   if (!attrid->ident)
      deadly("expand: out of memory\n");
   (void) strcpy(attrid->ident, name1);
   attrnameslist->names = attrid;
   attrnameslist->next = attrspez->attrs;
   attrspez->attrs = attrnameslist;
   /***
   *  *
   *  *
   ***/
   attrid = (IdList) middle_Malloc(__FILE__, __LINE__, sizeof(struct _idlist));
   if (!attrid)
      deadly("expand: out of memory\n");
   attrid->ident = (char *) middle_Malloc(__FILE__, __LINE__, strlen(name2) + 1);
   if (!attrid->ident)
      deadly("expand: out of memory\n");
   (void) strcpy(attrid->ident, name2);
   attrid->next = (IdList) attrnameslist->names;
   attrnameslist->names = attrid;
   /***
   *  * falls die Attributnamen jeweils separat mit eigenem Symboleintrag
   *  * gespeichert werden muessen, dann muss der obige Teil durch den
   *  * untenstehenden ersetzt werde. Anderenfalls kann das Stueck unten
   *  * geloescht werden.
   ***/
#if 0
   attrnameslist = (ANamesList) middle_Malloc(__FILE__, __LINE__, sizeof(struct _anameslist));
   attrid = (IdList) middle_Malloc(__FILE__, __LINE__, sizeof(struct _idlist));
   if (!attrnameslist || !attrid)
      deadly("expand: out of memory\n");
   attrnameslist->symbname = (char *) middle_Malloc(__FILE__, __LINE__, 
				     strlen(dnameOfSymb(symbref(sid))) + 1);
   if (!attrnameslist->symbname)
      deadly("expand: out of memory\n");
   (void) strcpy(attrnameslist->symbname, dnameOfSymb(symbref(sid)));
   attrid->next = (IdList) NULL;
   attrid->ident = (char *) middle_Malloc(__FILE__, __LINE__, strlen(name2) + 1);
   if (!attrid->ident)
      deadly("expand: out of memory\n");
   (void) strcpy(attrid->ident, name2);
   attrnameslist->names = attrid;
   attrnameslist->next = attrspez->attrs;
   attrspez->attrs = attrnameslist;
#endif
}/* gen_chain_attr() */

void
#ifdef __STDC__
gen_constit_attr(int sid, ConstNode cptr)
#else
gen_constit_attr(sid, cptr)
   int sid;
   ConstNode cptr;
#endif
/* generate attribute for CONSTITUENT(S) expansion			 */
{
   Attrdef newattr;
   char *name;

   name = genattrOfConstit(cptr->constit);

   newattr = NAttrdef;

   protout(ProtocolFile, "%s.%s\n", dnameOfSymb(symbref(sid)), name);
   didOfAttrdef(newattr) = newdid();
   nameOfAttrdef(newattr) = (char *) middle_Malloc(__FILE__, __LINE__, strlen(name) + 1);
   if (!nameOfAttrdef(newattr))
      deadly("expand: out of memory\n");
   (void) strcpy(nameOfAttrdef(newattr), name);
   rowOfAttrdef(newattr) = rowOfConstit(cptr->constit);
   colOfAttrdef(newattr) = colOfConstit(cptr->constit);

   /* the type of the attribute depends on the construct */
   if (singleOfConstit(cptr->constit))
   {
      typeidOfAttrdef(newattr) = cptr->typeid;
   }
   /* if */
   else
   {
      typeidOfAttrdef(newattr) = cptr->list_tid;
   }	/* else */

   classOfAttrdef(newattr) = ATCLSYNT;
   storeOfAttrdef(newattr) = STORUNKN;
   genOfAttrdef(newattr) = GENCONST;
   prodidOfAttrdef(newattr) = 0;

   appendfrontSEQAttrdef(attrsOfSymb(symbref(sid)), newattr);
   /***** IMPORTANT NOTE: *****/
   /* The new attribute must always be appended at the *front* of 	 */
   /* the list. The function to replace CONSTITUENT(S) constructs	 */
   /* by accesses to the new attribute relies on the fact that the	 */
   /* new attribute is the first attribute in the list.		 */
}/* gen_constit_attr() */

int
#ifdef __STDC__
list_typeid(int tid, char **name)
#else
list_typeid(tid, name)
   int tid;
   char **name;
#endif
/* get or create did of the list type of tid				 */
{
   SEQDef tmp;
   Def def;
   Def listdef;
   Typedef newtype;

   /* list type of VOID is predefined */
   if (tid == DIDVOID)
   {
      *name = TNVOLI;
      return (DIDVOLI);
   }	/* if */
   /* search for definition of tid */
   foreachinSEQDef(defseqOfAttrEval(IdlStruct), tmp, def)
   {
      if (typeof(def) == KTypedef && didOfDef(def) == tid)
	 break;
   }	/* foreachinSEQDef */

   if (!listedtoOfTypedef(DefToTypedef(def)))
      /* create new list type */
   {
      (void) fprintf(ProtocolFile,
		     "\n***\tcreating list type %s%s\n",
		     dnameOfDef(def), LIST_SUFFIX);

      newtype = NTypedef;
      didOfTypedef(newtype) = newdid();
      dnameOfTypedef(newtype) = (char *) middle_Malloc(__FILE__, __LINE__, 
						strlen(dnameOfDef(def)) +
						strlen(LIST_SUFFIX) + 1);
      if (!dnameOfTypedef(newtype))
	 deadly("expand: out of memory\n");
      (void) sprintf(dnameOfTypedef(newtype),
		     "%s%s", dnameOfDef(def), LIST_SUFFIX);
      rowOfTypedef(newtype) = 0;
      colOfTypedef(newtype) = 0;
      listedtoOfTypedef(newtype) = 0;
      extnameOfTypedef(newtype) = (char *) NULL;

      /* insert new type definition into the definition list */
      IDLtempDef = TypedefToDef(newtype);
      appendrearSEQDef(defseqOfAttrEval(IdlStruct), IDLtempDef);

      /* the given type is now listed to the new type */
      listedtoOfTypedef(DefToTypedef(def)) = didOfTypedef(newtype);

      /* copy name of list type */
      *name = (char *) middle_Malloc(__FILE__, __LINE__, strlen(dnameOfTypedef(newtype)) + 1);
      if (!(*name))
	 deadly("expand: out of memory\n");
      (void) strcpy(*name, dnameOfTypedef(newtype));

      return (didOfTypedef(newtype));
   }	/* if */
   /* search for name of list type */
   foreachinSEQDef(defseqOfAttrEval(IdlStruct), tmp, listdef)
   {
      if (typeof(listdef) == KTypedef
	  && didOfDef(listdef) == listedtoOfTypedef(DefToTypedef(def)))
	 break;
   }	/* foreachinSEQDef */

   /* copy name of list type */
   *name = (char *) middle_Malloc(__FILE__, __LINE__, strlen(
				dnameOfTypedef(DefToTypedef(listdef))) + 1);
   if (!(*name))
      deadly("expand: out of memory\n");
   (void) strcpy(*name, dnameOfTypedef(DefToTypedef(listdef)));

   return (listedtoOfTypedef(DefToTypedef(def)));
}/* list_typeid() */

int
#ifdef __STDC__
name_typeid(char *name)
#else
name_typeid(name)
   char *name;
#endif
/* retrieve did of definition of the given type name			 */
{
   SEQDef tmp;
   Def tdef;
   Typedef newtype;

   /* search for definition of a type with this name */
   foreachinSEQDef(defseqOfAttrEval(IdlStruct), tmp, tdef)
   {
      if (typeof(tdef) == KTypedef
	  && !strcmp(dnameOfDef(tdef), name))
      {
	 return (didOfDef(tdef));
      }	/* if */
   }	/* foreachinSEQDef */

   /* create new type definition for this name */
   newtype = NTypedef;
   didOfTypedef(newtype) = newdid();
   dnameOfTypedef(newtype) = (char *) middle_Malloc(__FILE__, __LINE__, strlen(name) + 1);
   if (!dnameOfTypedef(newtype))
      deadly("expand: out of memory\n");
   (void) strcpy(dnameOfTypedef(newtype), name);
   rowOfTypedef(newtype) = 0;
   colOfTypedef(newtype) = 0;
   listedtoOfTypedef(newtype) = 0;
   extnameOfTypedef(newtype) = (char *) NULL;

   /* insert new type definition into the definition list */
   IDLtempDef = TypedefToDef(newtype);
   appendrearSEQDef(defseqOfAttrEval(IdlStruct), IDLtempDef);

   return (didOfTypedef(newtype));
}/* name_typeid() */

/***********************\
* end of expidl.c	*
\***********************/

/* HaDeS */

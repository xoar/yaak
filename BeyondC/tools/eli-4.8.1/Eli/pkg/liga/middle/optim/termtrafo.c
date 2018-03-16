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
/* $Id: termtrafo.c,v 4.9 1999/07/08 16:52:33 uwe Exp $ */

/* Transformation of Non-Literal Terminal Accesses and Coordinate Accesses

   See the driver procedure TransformTerms for explanations.
*/

#include "LIGA.h"
#include "LIGAMacros.h"
#include "liga_func.h"
#include "lookup_idl.h"
#include "ligaconsts.h"
#include "do_optim.h"
#include <stdio.h>
#include <string.h>

#include "termtrafo.h"

static AttrEval idlstruct;
static int MAXDID;

static Prod production; /* the current production */
static Symb lhssymbdef; /* lhs symbol of the current production */

/* generated for the current production: */
static SEQAttrdef newtermattrs; /* terminals attrs */
static Attrdef coordattr, lineattr, colattr; /* coordinate attrs */
static int hascoordattr, haslineattr, hascolattr;
static SEQAttrrule newassigns; /* assigns for generated attrs */

#if defined (__cplusplus) || defined(__STDC__)
static int FindTypeDid (char *typename)
#else
static int FindTypeDid (typename) char *typename;
#endif
{ SEQDef defs; Def def;

  foreachinSEQDef (defseqOfAttrEval(idlstruct), defs, def)
	if (typeof(def) == KTypedef &&
	    strcmp (dnameOfDef (def), typename) == 0)
		return didOfDef (def);
  return DIDNON;
}

#if defined (__cplusplus) || defined(__STDC__)
static int FindTermTypeDid (int termno)
#else
static int FindTermTypeDid (termno) int termno;
#endif
/* yields the Did of the type of the termno-th NonLitTerm in the current
   production */
{ SEQEntity rhs;
  Entity ent;
  int marked = 0;

  rhs = rhsOfProd(production);
  while (!emptySEQEntity (rhs))
  {
    retrievefirstSEQEntity (rhs, ent);
    if (marked && typeof (ent) == KLiteral)
    { if (termno > 1)
      { termno--;
        marked = 0;
      } else
      { /* terminal found, next is its type: */
        retrievefirstSEQEntity (tailSEQEntity (rhs), ent);
        return FindTypeDid 
                (strOfLiteral (EntityToLiteral (ent)));
      }
    }
    if (!marked && typeof (ent) == KLiteral &&
        strlen (strOfLiteral (EntityToLiteral (ent))) == 0)
         marked = 1; /* the mark preceeding a terminal is found */
    else marked = 0;

    rhs = tailSEQEntity (rhs);
  }
  return DIDNON;
}

#if defined (__cplusplus) || defined(__STDC__)
static int GenTermRuleAttr (int termno, int line, int col)
#else
static int GenTermRuleAttr (termno, line, col) int termno, line, col;
#endif
/* generates a rule attribute for the termno-th NonLitTerm of 
   the current production,
   if the attribute does not yet exist
*/
{  SEQAttrdef attrs;
   Attrdef newattr, attrdef;
   char *sname, name[24], numb[4];
   Attrrule comp;
   Expr TmpExpr, termvalex;

   foreachinSEQAttrdef(newtermattrs, attrs, attrdef)
	if (prodidOfAttrdef (attrdef) == termno)
		return didOfAttrdef(attrdef); /* attr exists */

   strcpy(name, "TERM_");
   sprintf(numb, "%d", termno);
   strcat(name, numb);
   sname = (char *) malloc (strlen(name) + 1);
   if (!sname) optim_deadly ("terminal replace: out of memory\n");
   (void) strcpy(sname, name);

   newattr =
     MkAttrdef
       (++MAXDID,
        sname, line, col,
	FindTermTypeDid (termno),
	ATCLSYNT, 
	termno, /* prodid component used for encoding, substituted later */ 
	STORTRAT, GENTERM, 0, "");

   appendfrontSEQAttrdef (newtermattrs, newattr);

   /* generate assignment for this attribute: */
   TmpExpr =
     AttraccToExpr (MkAttracc (0, didOfAttrdef (newattr), line, col));
   termvalex =
      ValToExpr (MkVal (termno, line, col));
   comp =
     CallToAttrrule
       (MkCall
          (ASSIGNFCT,
           AppFrontSEQExpr
	     (TmpExpr,
              creatSEQExpr
	         (CallToExpr
		    (MkCall
		       (TERMFCT, 
			creatSEQExpr (termvalex),
                        line, col)))),
           line, col));

   appendfrontSEQAttrrule (newassigns, comp);
   return didOfAttrdef(newattr);
}/* GenTermRuleAttr */

#define ISCOORD 0
#define ISLINE  1
#define ISCOL   2

#if defined (__cplusplus) || defined(__STDC__)
static int GenCoordAttr (int which, int line, int col)
#else
static int GenCoordAttr (which, line, col) int which, line, col;
#endif
/* generates a rule attribute for the
	coordinate of type POSITION if which == ISCOORD,
	line of type int if which == ISLINE,
	column of type int if which == ISCOL
   if not yet existent 
*/
{  Attrdef newattr;
   Attrrule comp;
   Expr TmpExpr;

   switch (which)
   { case ISCOORD:
       if (hascoordattr) return didOfAttrdef(coordattr);
       break;
     case ISLINE:
       if (haslineattr) return didOfAttrdef(lineattr);
       break;
     case ISCOL:
       if (hascolattr) return didOfAttrdef(colattr);
       break;
   }

   newattr =
     MkAttrdef
       (++MAXDID, 
        (which == ISCOORD ? "_pos" : (which == ISLINE ? "_line" : "_col")),
        line, col,
        (which == ISCOORD ? DIDCOORD : DIDINT),
        ATCLSYNT, 
	didOfProd (production),
	STORTRAT, GENTERM, 0, "");

   switch (which)
   { case ISCOORD:
       hascoordattr = 1; coordattr = newattr; break;
     case ISLINE:
       haslineattr = 1; lineattr = newattr; break;
     case ISCOL:
       hascolattr = 1; colattr = newattr; break;
   }

   /* generate the assignment for this attribute: */
   TmpExpr =
      AttraccToExpr (MkAttracc (0, didOfAttrdef (newattr), line, col));
   comp =
     CallToAttrrule
       (MkCall
          (ASSIGNFCT,
	   AppFrontSEQExpr
	     (TmpExpr,
              creatSEQExpr
	         (NameToExpr
		    (MkName
		       ((which == ISCOORD ? "COORDREF" : 
                        (which == ISLINE ? "LINE" :
			 "COL")),
                        line, col)))),
           line, col));

   appendfrontSEQAttrrule(newassigns, comp);
   return didOfAttrdef(newattr);
}/* GenCoordAttr */

#if defined (__cplusplus) || defined(__STDC__)
static void SubstArgAcc (Expr ex, int doit, SEQExpr listelem)
#else
static void SubstArgAcc (ex, doit, listelem)
    Expr ex; int doit; SEQExpr listelem;
#endif
/* Recursively substitutes accesses to node construction arguments
   in ex by accesses to generated attribute.

   doit==0 indicates that we are on the rhs of an assign to a tree
   node attribute, and no executable function is applied so far.
   If recursion ends in this state, the assign will be unchanged.

   A substituted expression is assigned to listelem->value.
*/
{
  switch (typeof (ex))
  {
    case KName:
    { Name na = ExprToName (ex);
      /* substitute COORDREF;
         substitute LINE, COL if doit: */
      if (strcmp (nOfName (na), "COORDREF") == 0)
      { Expr attrex;
        int coordattr;
        coordattr = GenCoordAttr (ISCOORD, rowOfName (na), colOfName (na));
	attrex =
	  AttraccToExpr
	    (MkAttracc (0, coordattr, rowOfName (na), colOfName (na)));
	listelem->value =
	  CallToExpr
	    (MkCall
	       (ADRFCT,
	        creatSEQExpr (attrex),
		rowOfName (na), colOfName (na)));
      } else
      if (doit && strcmp (nOfName (na), "LINE") == 0)
      {
        if (hascoordattr)
        { Expr attrex;
	  attrex =
	    AttraccToExpr
	      (MkAttracc (0, didOfAttrdef (coordattr),
	                  rowOfName (na), colOfName (na)));
          listelem->value =
	    CallToExpr
	      (MkCall
                 (LINEACCFCT,
	          creatSEQExpr (attrex),
		  rowOfName (na), colOfName (na)));
	} else
	  listelem->value =
	    AttraccToExpr
	      (MkAttracc
	        (0,
		 GenCoordAttr (ISLINE, rowOfName (na), colOfName (na)),
		 rowOfName (na), colOfName (na)));
      } else
      if (doit && strcmp (nOfName (na), "COL") == 0)
      {
        if (hascoordattr)
        { Expr attrex;
	  attrex =
	    AttraccToExpr
	      (MkAttracc (0, didOfAttrdef (coordattr),
	                  rowOfName (na), colOfName (na)));
          listelem->value =
	    CallToExpr
	      (MkCall
                 (COLACCFCT,
	          creatSEQExpr (attrex),
		  rowOfName (na), colOfName (na)));
	} else
	  listelem->value =
	    AttraccToExpr
	      (MkAttracc
	        (0,
		 GenCoordAttr (ISCOL, rowOfName (na), colOfName (na)),
		 rowOfName (na), colOfName (na)));
      }
      return;
    }

    case KCall:
      /* if doit substitute TERMFCT recursively
         else determine doit for substitution in the parameters: */
      if (doit)
      { Call ca = ExprToCall (ex);
	SEQExpr pars; Expr par;
        if (strcmp (TERMFCT, nameOfCall (ca)) == 0)
	{ Expr termex;
	  int termattr;

	  retrievefirstSEQExpr (paramsOfCall (ca), termex);
	  termattr =
	    GenTermRuleAttr
	      (vOfVal (ExprToVal (termex)), rowOfCall (ca), colOfCall (ca));
	  listelem->value =
	     AttraccToExpr
	       (MkAttracc (0, termattr, rowOfCall (ca), colOfCall (ca)));
	  return;
	}
	/* call of other function: */
	foreachinSEQExpr (paramsOfCall (ca), pars, par)
	   SubstArgAcc (par, 1, pars);
      } else
      { Call ca = ExprToCall (ex);
        char *name = nameOfCall (ca);
	int doitdown = 1;
	SEQExpr pars; Expr par;

	if ((strcmp (IDFCT, name) == 0) ||
	    (strcmp (BOTTOMUPFCT, name) == 0) ||
	    (strcmp ("IDENTICAL", name) == 0) ||
	    (strcmp (DEPFCT, name) == 0))
	   doitdown = 0;
	foreachinSEQExpr (paramsOfCall (ca), pars, par)
	   SubstArgAcc (par, doitdown, pars);
      }
      return;
      
    /* nothing to be done in the following cases: */
    case KAttracc:
    case KLiteral:
    case KVal:
    case KIncluding:
    default: /* Chainacc or Constit should be removed by expand */
      return;
  }/* switch */
}/* SubstArgAcc */

#if defined (__cplusplus) || defined(__STDC__)
static void AssignOrPlain (Call compcall)
#else
static void AssignOrPlain (compcall) Call compcall;
#endif
{
  if (strcmp (ASSIGNFCT, nameOfCall (compcall)) == 0)
  { Expr lhsex, rhsex;
    retrievefirstSEQExpr (paramsOfCall (compcall), lhsex);
    retrievefirstSEQExpr (tailSEQExpr (paramsOfCall (compcall)), rhsex);
    if (typeof (lhsex) == KAttracc)
    { Attrdef attrdef;
      attrdef = lookup_attrdef (attridOfAttracc (ExprToAttracc (lhsex)));
      if (storeOfAttrdef (attrdef) == STORTRAT)
      { /* suppress substitution if the expression is simple: */
         SubstArgAcc (rhsex, 0, tailSEQExpr (paramsOfCall (compcall)));
         return;
      }
    }
    SubstArgAcc (rhsex, 1, tailSEQExpr (paramsOfCall (compcall)));
    return;
  }

  { SEQExpr exprs; Expr ex;
  /* plain call: */
  foreachinSEQExpr (paramsOfCall (compcall), exprs, ex)
     SubstArgAcc (ex, 1, exprs);
  }
}/* AssignOrPlain */

#if defined (__cplusplus) || defined(__STDC__)
void TransformTerms (AttrEval ae, int max)
#else
void TransformTerms (ae, max) AttrEval ae; int max;
#endif
/* Driver procedure to be called (after order and before treecon).
   Checks all computations for occurrences of access to non-literal
   terminals or coordinates. Those are supplied as arguments of the
   Node construction call and have to be stored immediately into
   an attribute that is allocated in the tree node.

   New attributes are created for that purpose, and computations
   are added: Attracc(0, new) = ArgumentAccess (...).
   The backend will move the computations into the code of the
   tree construction functions.

   Only in cases where the original computation has already
   the form Attracc(0, attr) = ArgumentAccess (...), and
   attr is a tree node attribute, the above transformation is
   not applied.

   Access to COORDREF causes always an attribute be generated
   for storing the coordinate value, in order to keep the value
   that is referenced by the pointer.

   This transformation is save for bottom-up computations, because
   it does not move executable code.
*/
{ SEQAttribution attribs; Attribution attrib;

  idlstruct = ae;
  MAXDID = max;

  /* consider all rules: */
  foreachinSEQAttribution(attrrulesOfAttrEval(idlstruct), attribs, attrib)
  { Def def;
    SEQAttrrule comps; Attrrule comp;
    Attrdef atdef;

    def = lookup_def(prodidOfAttribution (attrib));
    production = DefToProd (def);
    def = lookup_def(lhsOfProd(production));
    lhssymbdef = DefToSymb (def);
    newtermattrs = nullSEQAttrdef();
    hascoordattr = 0; haslineattr = 0; hascolattr = 0;

    /* consider all computations of this rule: */
    foreachinSEQAttrrule(attrrulesOfAttribution(attrib), comps, comp)
      if (typeof (comp) == KCall) /* skip visits */
         AssignOrPlain (AttrruleToCall (comp));

    /* add generated terminal attrs: */
    while (!emptySEQAttrdef (newtermattrs))
    {
      retrievefirstSEQAttrdef (newtermattrs, atdef);
      /* reset term codes in col of attr defs: */
      prodidOfAttrdef(atdef) = didOfProd (production);
      appendfrontSEQAttrdef (attrsOfSymb(lhssymbdef), atdef);
      newtermattrs = tailSEQAttrdef (newtermattrs);
    }

    /* add generated coordinate attrs: */
    if (hascoordattr)
       appendfrontSEQAttrdef (attrsOfSymb(lhssymbdef), coordattr);
    if (haslineattr)
       appendfrontSEQAttrdef (attrsOfSymb(lhssymbdef), lineattr);
    if (hascolattr)
       appendfrontSEQAttrdef (attrsOfSymb(lhssymbdef), colattr);

    /* add the generated assignments: */
    while (!emptySEQAttrrule (newassigns))
    {
      retrievefirstSEQAttrrule (newassigns, comp);
      appendfrontSEQAttrrule (attrrulesOfAttribution(attrib), comp);
      newassigns = tailSEQAttrrule (newassigns);
    }
  }/* end foreachinSEQAttribution */
}/* TransformTerms */

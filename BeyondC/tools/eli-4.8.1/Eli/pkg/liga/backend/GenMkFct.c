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
#include "global.h"
#include "LIGA.h"
#include "LIGAMacros.h"
#include "ligaconsts.h"
#include "lookup_idl.h"
#include "ptg_gen.h"
#include "bottomup.h"
#include "csm.h"
#include "idn.h"

#include "GenMkFct.h"
#include "DynSpace.h"
#include "ProdIter.h"

static Def tmpDef;

/* adaption of different pointer lists to single VoidPtrList implementation: */

#include "VoidPtrList.h"

typedef VoidPtrList AbsSymbPtrList;
#define NULLAbsSymbPtrList NULLVoidPtrList
#define HeadAbsSymbPtrList(l) ((AbsSymbPtr)(HeadVoidPtrList(l)))
#define TailAbsSymbPtrList(l) TailVoidPtrList(l)
#define ConsAbsSymbPtrList(e,l) ConsVoidPtrList((VoidPtr)e, l)

typedef VoidPtrList AbsProdPtrList;
#define NULLAbsProdPtrList NULLVoidPtrList
#define HeadAbsProdPtrList(l) ((AbsProdPtr)(HeadVoidPtrList(l)))
#define TailAbsProdPtrList(l) TailVoidPtrList(l)
#define ConsAbsProdPtrList(e,l) ConsVoidPtrList((VoidPtr)e, l)

#define NULLVoidPtr ((VoidPtr)0)

/* representation of a symbol and its productions: */
typedef struct {
   int            symbdid;
   AbsProdPtrList prodlst;
   VoidPtr        mark;
} AbsSymb, *AbsSymbPtr;

/* representation of a chain production or of
   a list element production: */
typedef struct {
   int        proddid;
   AbsSymbPtr lhssymb, rhssymb;
} AbsProd, *AbsProdPtr;

/* symbol entries of all symbols in abstract productions: */
static AbsSymbPtrList AnySymbs = NULLAbsSymbPtrList;
static AbsSymbPtrList TermSymbs = NULLAbsSymbPtrList;

static AbsSymbPtr FindSymb (symbdid, symblist) 
    int symbdid; AbsSymbPtrList *symblist;
/* returns the symbol entry for symbdid in symblist; 
   generates it if not yet contained
*/
{ AbsSymbPtr     newsymb;
  AbsSymbPtrList symbl;
  symbl = *symblist;
  while (symbl) 
  {
    if (HeadAbsSymbPtrList(symbl)->symbdid == symbdid)
	return HeadAbsSymbPtrList(symbl);
    symbl = TailAbsSymbPtrList(symbl);
  }
  newsymb = (AbsSymbPtr) DynAlloc (VoidPtrListSpace, sizeof (AbsSymb));
  newsymb->symbdid = symbdid;
  newsymb->mark = NULLVoidPtr;
  newsymb->prodlst = NULLAbsProdPtrList;
  (*symblist) = ConsAbsSymbPtrList(newsymb, *symblist);
  return (newsymb);
}/* FindSymb */

static AbsProdPtr NewAbsProd (proddid, lhsdid, rhsdid)
	int proddid, lhsdid, rhsdid;
/* associates a new production to the list of its lhs symbol
*/
{ AbsProdPtr prod = 
      (AbsProdPtr) DynAlloc (VoidPtrListSpace, sizeof (AbsProd));
  prod->proddid = proddid;
  prod->lhssymb = FindSymb (lhsdid, &AnySymbs);
  prod->rhssymb = FindSymb (rhsdid, &AnySymbs);
  prod->lhssymb->prodlst = 
      ConsAbsProdPtrList (prod, prod->lhssymb->prodlst);
  return prod;
}/* NewAbsProd */

static void UnsetMarks ()
/* resets the marks of all symbols in AnySymbs */
{ AbsSymbPtrList symblist = AnySymbs;
  while (symblist != NULLAbsSymbPtrList) 
  { (HeadAbsSymbPtrList (symblist))->mark = NULLVoidPtr;
    symblist = TailAbsSymbPtrList (symblist);
  }
}/* UnsetMarks */

static void PropagateMarks ()
/* on entry:
     some symbols are marked - 
     by productions to be applied for coercion
   on exit:
     the marks are propagated in levels to reachable symbols
     s.th. the shortest path is kept
*/
{ int changed;
  do
  { /* consider all symbols: */
    AbsSymbPtrList symblist = AnySymbs;
    changed = 0;
    while (symblist != NULLAbsSymbPtrList)
    { AbsSymbPtr sy = HeadAbsSymbPtrList (symblist);
      /* for each marked symbol the mark is propagated to
	 those rhs symbols that are not yet marked: */
      if (sy->mark)
      { AbsProdPtrList prodlst = sy->prodlst;
        while (prodlst != NULLAbsProdPtrList)
        { AbsProdPtr prod = HeadAbsProdPtrList (prodlst);
	  if (!prod->rhssymb->mark)
	  { prod->rhssymb->mark = sy->mark;
            changed = 1;
	  }
          prodlst = TailAbsProdPtrList (prodlst);
	}
      }
      symblist = TailAbsSymbPtrList (symblist);
    }
  } while (changed);
}/* PropagateMarks */

/* global variables for headers and implementations of Mk-functions: */
static PTGNode GenMkHdr = PTGNULL, GenMkFct = PTGNULL;

void GenMkSymb (sydid) int sydid;
/* constructs the Mk-function for symbol sydid */
{ AbsSymbPtr     symb;
  PTGNode        fct;
  PTGNode        syname;
  AbsProdPtrList prodlst;
  AbsSymbPtrList symblist;

  tmpDef = lookup_def (sydid);
  symb = FindSymb (sydid, &AnySymbs);
  syname = PTGAsIs (dnameOfDef (tmpDef));
  fct = PTGMkSymbFctHead (syname);

  /* compute coercion checks: */
  UnsetMarks ();

  /* mark the first level symbols with their productions: */
  prodlst = symb->prodlst;
  while (prodlst != NULLAbsProdPtrList)
  { AbsProdPtr prod = HeadAbsProdPtrList (prodlst);
    if (!prod->rhssymb->mark)
       prod->rhssymb->mark = prod;
    prodlst = TailAbsProdPtrList (prodlst);
  }

  /* propagate the first level marks 
     along chain productions to deeper levels: */
  PropagateMarks ();

  /* generate a check for each reachable symbol: */
  symblist = AnySymbs;
  while (symblist != NULLAbsSymbPtrList)
  { AbsSymbPtr sy = HeadAbsSymbPtrList (symblist);
    if (sy->mark)
    { PTGNode symbname, prodname;
      tmpDef = lookup_def (sy->symbdid);
      symbname = PTGAsIs (dnameOfDef (tmpDef));
      tmpDef = lookup_def (((AbsProdPtr)sy->mark)->proddid);
      prodname = PTGAsIs (dnameOfDef (tmpDef));
      fct = PTGSeq (fct, PTGMkSymbFctChk (symbname, prodname));
    }
    symblist = TailAbsSymbPtrList (symblist);
  }

  fct = PTGSeq (fct, PTGMkSymbFctTail (syname));
  GenMkFct = PTGSeq (GenMkFct, fct);
  GenMkHdr = PTGSeq (GenMkHdr, PTGMkSymbHeader (syname));
}/* GenMkSymb */

#define LISTOFPROD (-1)
#define CHAINPROD (-2)
#define IGNOREPROD (-3)

static void GenMkProd (prod, kind) Prod prod; int kind;
/* constructs the Mk-function for plain or chain production prod */
{ 
  SEQEntity ents;
  char *prodnamestring;
  PTGNode fct, prodname; 
  int symcnt = 0, termcnt = 0;
  int OldStyle = 0; /* prod is generated for an old style terminal */

  PTGNode
      parmprotos=PTGNULL, parmnames=PTGNULL, monTermCalls=PTGNULL,
      parmspecs=PTGNULL, treeassigns=PTGNULL;

  tmpDef = ProdToDef(prod);
  prodnamestring = dnameOfDef(tmpDef);
  prodname = PTGAsIs(prodnamestring);

  /* to be removed when old style terminals are not allowed anymore */
  if (strncmp (prodnamestring, "_RNT_", 5) == 0) /* generated rule */
  {
    GenMkHdr = PTGSeq (GenMkHdr, PTGOldTermDefine (prodnamestring+5));
    OldStyle = 1;
  }
 
  /* consider the elements of the rhs;
     HasMoreEntities and NextEntity encapsulate the encoding
     of generated symbols and of non-literal terminals */
  ents = rhsOfProd (prod);
  while (HasMoreEntities (&ents))
  { Entity ent; int isGen, isNonLit; char *typename;
    NextEntity (&ents, &ent, &isGen, &isNonLit, &typename);

    if (typeof(ent) == KSymbol)
    /* nonterminal: */
    { Symbol tmpSymbol = EntityToSymbol(ent);
      Def tmpDef;
      char *symname;
      PTGNode parmname;

      tmpDef  = lookup_def (didOfSymbol(tmpSymbol));
      symname = dnameOfDef (tmpDef);
      symcnt++;

      parmname = PTGDescName (PTGNumb (symcnt));
      parmnames = PTGSeq (parmnames, PTGComElem (parmname));
      parmspecs = PTGSeq (parmspecs, PTGMkTreeParmSpec (parmname));
      parmprotos = PTGSeq (parmprotos, PTGMkProtoSpec (parmname));
      if (isGen)
	   treeassigns = PTGSeq (treeassigns,
	      PTGGenTreeAssign (parmname, symname));
      else treeassigns = PTGSeq (treeassigns,
	      PTGTreeAssign (parmname, symname, prodnamestring, symcnt));
    } else 

    if (typeof(ent) == KLiteral && isNonLit) 
    /* non-literal terminal: */
    { Literal tmpLiteral = EntityToLiteral(ent);
      char *termname = strOfLiteral (tmpLiteral);
      int index = GetIndexInProd (prod, ent);
      int id, cd;

      /* check is to be removed when old style terminals are not allowed anymore */
      if (!OldStyle) 
      { /* collect the terminal names to generate a macro for each */
        mkidn (termname, strlen(termname), &cd, &id);
        (void)FindSymb (id, &TermSymbs);
      }
      termcnt++;
      parmnames = PTGSeq (parmnames, PTGNonLitTermName (termcnt));
      parmspecs = PTGSeq (parmspecs, 
	PTGNonLitTermSpec (typename, termcnt));
      parmprotos = PTGSeq (parmprotos,
	PTGNonLitTermProto (typename, termcnt));
      monTermCalls = PTGSeq (monTermCalls,
        PTGMonTermCall 
          (typename, 
           termname, (index == 0 ? PTGNULL : PTGMonIndex (index)),
           termcnt));
    }
  }/* while rhs */

  fct = PTGMkProdFct
	  (prodname,
	   parmnames,
	   parmspecs,
	   kind == CHAINPROD ? 
             PTGSeq (treeassigns, PTGAsIs ("\n_COPYCOORD(_currn)")) :
             PTGSeq (treeassigns, PTGAsIs ("\n_SETCOORD(_currn)")),
	   BottomUpVisits ? PTGTreeConVisit() : PTGNULL,
	   parmprotos,
	   PTGSeq (PTGNonLitTermAct (prodname), monTermCalls));

  GenMkFct = PTGSeq (GenMkFct, fct);
  GenMkHdr = PTGSeq (GenMkHdr, PTGMkProcHeader (prodname, parmprotos));
}/* GenMkProd */

static void GenMkList (prod) Prod prod;
/* constructs the Mk-function for the list production prod 
   prod is the listroot production
*/
{ PTGNode prodname, lstsymbname;
  PTGNode elemfcts = PTGNULL, termacts = PTGNULL,
	  elemcoerce = PTGNULL;
  Entity ent;
  int lstdid;
  Symbol tmpSymbol;
  AbsProdPtrList lstelemprods, lep;
  AbsSymbPtrList symblist;

  prodname = PTGAsIs (dnameOfProd (prod));
  /* the only rhs symbol is the generated list symbol named LST_listrule */
  retrievefirstSEQEntity (rhsOfProd(prod), ent);
  tmpSymbol = EntityToSymbol(ent);
  lstdid = didOfSymbol(tmpSymbol);
  tmpDef = lookup_def (lstdid);
  lstsymbname = PTGAsIs (dnameOfDef(tmpDef)+4); /* remove LST_ */

  /* for each list element symbol make a function: */
  lep = (FindSymb (lstdid, &AnySymbs))->prodlst;
  lstelemprods = lep;
  while (lstelemprods != NULLAbsProdPtrList)
  { PTGNode elemname, elemprod;
    AbsProdPtr lstelemprod = HeadAbsProdPtrList (lstelemprods);
    tmpDef = lookup_def (lstelemprod->rhssymb->symbdid);
    elemname = PTGAsIs (dnameOfDef(tmpDef));
    tmpDef = lookup_def (lstelemprod->proddid);
    elemprod = PTGAsIs (dnameOfDef(tmpDef));

    /* collect the element functions: */
    elemfcts = PTGSeq (elemfcts, 
	PTGListElemFct (elemname, prodname, lstsymbname));
    /* collect terminal actions: */
    termacts = PTGSeq (termacts, 
        PTGListTermact (elemname, prodname));

    lstelemprods = TailAbsProdPtrList (lstelemprods);
  }

  /* generate the coercion selection for list elements: */
  UnsetMarks ();

  /* mark each list element symbol with itself: */
  lstelemprods = lep;
  while (lstelemprods != NULLAbsProdPtrList)
  { AbsProdPtr prod = HeadAbsProdPtrList (lstelemprods);
    if (!prod->rhssymb->mark)
	prod->rhssymb->mark = prod->rhssymb;
    lstelemprods = TailAbsProdPtrList (lstelemprods);
  }

  /* propagate the first level marks 
     along chain productions to deeper levels: */
  PropagateMarks ();

  /* for each reachable symbol generate a call
     of the element function that is marked for the symbol: */
  symblist = AnySymbs;
  while (symblist != NULLAbsSymbPtrList)
  { AbsSymbPtr sy = HeadAbsSymbPtrList (symblist);
    if (sy->mark)
    { PTGNode symbname, elemname;
      tmpDef = lookup_def (sy->symbdid);
      symbname = PTGAsIs (dnameOfDef (tmpDef));
      tmpDef = lookup_def (((AbsSymbPtr)sy->mark)->symbdid);
      elemname = PTGAsIs (dnameOfDef (tmpDef));

      elemcoerce = PTGSeq (elemcoerce, 
         PTGListElemChk (symbname, elemname, prodname));
    }
    symblist = TailAbsSymbPtrList (symblist);
  }

  GenMkHdr = PTGSeq (GenMkHdr, PTGListFunctsHdr (prodname));
  GenMkFct = 
     PTGSeq 
        (GenMkFct, 
	  PTGSeq
	    (elemfcts,
	     PTGListFuncts
	         (prodname,
		  lstsymbname,
		  elemcoerce,
		  BottomUpVisits ? PTGTreeConVisit() : PTGNULL,
		  termacts
		 )));
}

void GenMkFcts (ae) AttrEval ae;
/* generate Mk-function headers and implementations */
{ SEQDef defs; Def def;
  AbsSymbPtrList terms;

  /* initialize dyn space: */
  (void)ConsVoidPtrList((void*)0, NULLVoidPtrList);

  /* extract productions: chain, listof root, and list elements: */
  foreachinSEQDef (defseqOfAttrEval (ae), defs, def)
     if (typeof (def) == KProd)
     { Prod prod = DefToProd (def);
       int lhsdid = lhsOfProd(prod);
       Def lhsdef;
       lhsdef = lookup_def (lhsdid); /* 2 statements since there is no
                                        union initialization in classic C */
       if (emptySEQEntity (rhsOfProd (prod)))
       { if (strncmp (dnameOfDef(lhsdef), "LST_", 4)== 0)
	     /* generated empty list production: */
	     colOfDef(def) = IGNOREPROD;
             /* user defined empty production */
       } else 
       { /* non-empty: */
         Entity ent;
         retrievefirstSEQEntity (rhsOfProd (prod), ent);
         if (typeof (ent) == KSymbol)
         { Symbol tmpSymbol;
           int rhsdid; Def rhsdef;
	   tmpSymbol = EntityToSymbol(ent);
           rhsdid = didOfSymbol(tmpSymbol);
           rhsdef = lookup_def (rhsdid);

           if (strncmp (dnameOfDef(lhsdef), "LST_", 4) == 0)
           { /* generated binary list element production, 
		represents a list element */
             NewAbsProd (didOfDef(def), lhsdid, rhsdid);
             colOfDef(def) = IGNOREPROD;
	   } else /* lhs is not a LST_ symbol: */
             if (emptySEQEntity (tailSEQEntity (rhsOfProd (prod)))) 
             { /* one symbol on rhs: */
               if (strncmp (dnameOfDef(rhsdef), "LST_", 4) == 0)
                  /* list root production */
                  colOfDef(def) = LISTOFPROD;
	       else
               { /* user defined chain production: */
                 NewAbsProd (didOfDef(def), lhsdid, rhsdid);
                 colOfDef(def) = CHAINPROD;
	       }
	     }
	 }
       }
     }

  /* generate symbol functions: */
  foreachinSEQDef (defseqOfAttrEval (ae), defs, def)
     if (typeof (def) == KSymb &&
	 strncmp (dnameOfDef(def), "LST_", 4) != 0)
	 GenMkSymb (didOfDef (def));

  /* generate rule functions: */
  foreachinSEQDef (defseqOfAttrEval (ae), defs, def)
     if (typeof (def) == KProd && colOfDef(def) != IGNOREPROD) 
     { Prod prod = DefToProd (def);
	 if (colOfDef(def) == LISTOFPROD)
	      GenMkList (prod);
	 else GenMkProd (prod, colOfDef(def));
     }

  /* generate macros for non-literal terminal symbols: */
  terms = TermSymbs;
  while (terms != NULLAbsSymbPtrList)
  {  AbsSymbPtr term = HeadAbsSymbPtrList (terms);
     GenMkHdr = PTGSeq (GenMkHdr,
        PTGNonLitTermDefine (StringTable(term->symbdid)));
     terms = TailAbsSymbPtrList (terms);
  }

  PTGOutFile ("treecon.h", PTGTreeConHeader (GenMkHdr));
  PTGOutFile ("nodeptr.h", PTGNodePtrHeader ());
  PTGOutFile ("treecon.c", PTGSeq (PTGTreeConFileHead(), GenMkFct));
}/* GenMkFcts */

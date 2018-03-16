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
/* $Id: showproc.c,v 4.5 1998/04/28 14:30:00 ludi Exp $ */

static char rcs_id[] = "$Id: showproc.c,v 4.5 1998/04/28 14:30:00 ludi Exp $";

/***********************************************************************\
*									*
*		Implementation of a LIGA pass				*
*		    -- Interface Analyzer --				*
*									*
*	Module:		Show    					*
*	File:		showproc.c	      				*
*	Author:		U. Kastens					*
*									*
\***********************************************************************/

#include <stdio.h>
#include <string.h>

/*
 * #include "global.h"	included by LIGA.h #include "LIGA.h"	included by
 * lookup_idl.h #include "LIGAMacros.h"	included by lookup_idl.h
 */

#include "lookup_idl.h"
#include "liga_func.h"
#include "ligaconsts.h"

#include "showproc.h"
#include "ptg_gen.h"
#include "map_errors.h"

#define IsLast(x)	(x->next == NULL)

static PTGNode Unknown;

PTGNode MakeCoord (line, col) int line, col;
{
   int ind, nline;
   MapCoord(line, &ind, &nline);
   return (PTGCoord(PTGFileRef(PTGNumb(ind)),
		    PTGNumb(nline), PTGNumb(col)));
}/* MakeCoord */

PTGNode GetDefName (did) int did;
{
   Def d;
   if (did > DIDNON)
   {
      d = lookup_def(did);
      if (d.IDLclassCommon != (CPDef) 0)
	 return (PTGName(dnameOfDef(d)));
      else
	 return (Unknown);
   } else
      return (Unknown);
}/* GetDefName */

PTGNode GetAttrName (did) int did;
{
   Attrdef d;
   if (did > DIDNON)
   {
      d = lookup_attrdef(did);
      if (d != (Attrdef) 0)
	 return (PTGName(nameOfAttrdef(d)));
      else
	 return (Unknown);
   } else
      return (Unknown);
}/* GetAttrName */

SEQString prodterms; /* list of production terminal names */

PTGNode GetTermAcc (termno) int termno;
{ SEQString terms = prodterms; char *name;

  while (!emptySEQString (terms))
  { if (termno-- == 1)
    { retrievefirstSEQString (terms, name);
      return PTGName (name);
    }
    terms = tailSEQString (terms);
  }
  return Unknown;
}/* GetTermAcc */

SEQint prodsymsdid; /* list of dids for symbols of the current production */
SEQint prodsymsindex; /* list of indices for those symbols;
                         0 if one occurrence; 1 for first of several */

void InitProdSyms ()
{ initializeSEQint (prodsymsdid);
  initializeSEQint (prodsymsindex);
}

void EnterProdSym (did) int did;
{ SEQint dids = prodsymsdid, indices = prodsymsindex;
  int curdid, curindex;
  int occcnt = 0;
  while (!emptySEQint (dids))
  { retrievefirstSEQint (dids, curdid);
    retrievefirstSEQint (indices, curindex);
    if (curdid == did)
    { occcnt++;
      if (curindex == 0)
         prodsymsindex->value = 1;
    }
    dids = tailSEQint (dids);
    indices = tailSEQint (indices);
  }
  appendrearSEQint (prodsymsdid, did);
  appendrearSEQint (prodsymsindex, (occcnt ? occcnt+1 : 0));
}/* EnterProdSym */

static int rhscnt;

PTGNode GetIndexedProdSym (sympos) int sympos;
{ SEQint dids = prodsymsdid, indices = prodsymsindex;
  int curdid, curindex;

  if (sympos > rhscnt)
     return Unknown;

  while (sympos != 0 && !emptySEQint (dids))
  { dids = tailSEQint (dids);
    indices = tailSEQint (indices);
    sympos--;
  }
  if (emptySEQint (dids))
    return Unknown;
  else
  { retrievefirstSEQint (dids, curdid);
    retrievefirstSEQint (indices, curindex);
    if (curindex > 0)
      return PTGSymbolIndex (GetDefName (curdid), PTGNumb (curindex));
    else
      return GetDefName (curdid);
  }
}/* GetIndexedProdSym */

static PTGNode TrExpr ();

static int IsInitCycle;

PTGNode TrCall (c) Call c;
{ SEQExpr params; Expr param;

  params = paramsOfCall (c);

  if (strcmp (ASSIGNFCT, nameOfCall (c)) == 0) 
  { Expr lhs, rhs; PTGNode plhs, prhs;

    retrievefirstSEQExpr(params, lhs);
    if (typeof (lhs) == KAttracc)
    {  Attracc at = ExprToAttracc (lhs);
       plhs = PTGAttrAcc (GetIndexedProdSym (symbnoOfAttracc (at)),
                          GetAttrName (attridOfAttracc (at)));
    } else
    if (typeof (lhs) == KChainacc)
    {  Chainacc at = ExprToChainacc (lhs);
       plhs = PTGAttrAcc (GetIndexedProdSym (symbnoOfChainacc (at)),
                          GetDefName (chainidOfChainacc (at)));
    } else
       plhs = Unknown;

    if (emptySEQExpr(tailSEQExpr (params)))
       prhs = Unknown;
    else
    {  retrievefirstSEQExpr(tailSEQExpr (params), rhs);
       prhs = TrExpr (rhs);
    }

    return PTGAssign (plhs, prhs);
  } else

  if (strcmp (TERMFCT, nameOfCall (c)) == 0) 
  {  Val v;
     if (emptySEQExpr(params)) return Unknown;
     retrievefirstSEQExpr(params, param);
     if (typeof (param) == KVal)
          v = ExprToVal (param);
     else return Unknown;
     return GetTermAcc (vOfVal (v));
  } else
  if (strcmp (LINEACCFCT, nameOfCall (c)) == 0) 
  {
     return PTGLine ();
  } else
  if (strcmp (COLACCFCT, nameOfCall (c)) == 0) 
  {
     return PTGCol ();
  } else
  if (strcmp (ADRFCT, nameOfCall (c)) == 0) 
  {
     return PTGAddr ();
  } else
  if (strcmp (STRINGFCT, nameOfCall (c)) == 0)
  {
     if (emptySEQExpr(params)) return Unknown;
     retrievefirstSEQExpr(params, param);
     if (typeof (param) == KLiteral)
           return PTGName (strOfLiteral (ExprToLiteral (param)));
     else  return Unknown;
  } else
  if (strcmp (CHARFCT, nameOfCall (c)) == 0) 
  {
     if (emptySEQExpr(params)) return Unknown;
     retrievefirstSEQExpr(params, param);
     if (typeof (param) == KLiteral)
           return PTGCChar (strOfLiteral (ExprToLiteral (param)));
     else  return Unknown;
  } else
  if (strcmp (FLOATFCT, nameOfCall (c)) == 0) 
  {
     if (emptySEQExpr(params)) return Unknown;
     retrievefirstSEQExpr(params, param);
     if (typeof (param) == KLiteral)
           return PTGName (strOfLiteral (ExprToLiteral (param)));
     else  return Unknown;
  } else
  if (strcmp (DEPFCT, nameOfCall (c)) == 0) 
  {
   if (emptySEQExpr(params)) return Unknown;
   retrievefirstSEQExpr(params, param);
     return TrExpr (param);
  } else
  if (strcmp (WITHFCT, nameOfCall (c)) == 0)
  {
     return PTGConstituents ();
  } else
  if (strcmp (SHIELDFCT, nameOfCall (c)) == 0)
  {
     return PTGConstituent_s ();
  } else
  if (strcmp (ORDERFCT, nameOfCall (c)) == 0) 
  {
     return PTGOrder ();
  } else
  if (strcmp (VOIDFCT, nameOfCall (c)) == 0) 
  {
     if (emptySEQExpr(params)) return Unknown;
     retrievefirstSEQExpr(params, param);
     return TrExpr (param);
  } else
  if (strcmp (IDFCT, nameOfCall (c)) == 0) 
  {
     if (emptySEQExpr(params)) return Unknown;
     retrievefirstSEQExpr(params, param);
     return TrExpr (param);
  } else
  if (strcmp (IFFCT, nameOfCall (c)) == 0) 
  {
     return PTGIf ();
  } else
  if (strcmp (INITCYCLEFCT, nameOfCall (c)) == 0) 
  {
     IsInitCycle = 1;
     if (emptySEQExpr(params)) return Unknown;
     retrievefirstSEQExpr(params, param);
     return TrExpr (param);
  } else
  if (strcmp (LOOPFCT, nameOfCall (c)) == 0) 
  {
     if (emptySEQExpr(params)) 
        return PTGIterate (Unknown);
     if (emptySEQExpr(tailSEQExpr(params)))
        return PTGIterate (Unknown);
     retrievefirstSEQExpr(tailSEQExpr (params), param);
     if (typeof (param) != KAttracc) 
     {  Attracc at = ExprToAttracc (param);
        return PTGIterate 
                 (PTGAttrAcc (GetIndexedProdSym (symbnoOfAttracc (at)),
                              GetAttrName (attridOfAttracc (at))));
     }
     else
        return PTGIterate (Unknown);
  } else 
  { /* other function: */
    return PTGCall (PTGName (nameOfCall (c)));
  }
}/*TrCall*/

static
PTGNode TrExpr (e) Expr e;
{
  switch (typeof (e)) {

  case KLiteral:
  { /* should not occur; is encapsulated in type call */
    return Unknown;
  }

  case KVal:
    return PTGNumb (vOfVal (ExprToVal (e)));

  case KName:
    return PTGName (nOfName(ExprToName(e)));

  case KAttracc:
  { Attracc at = ExprToAttracc (e);
    return PTGAttrAcc (GetIndexedProdSym (symbnoOfAttracc (at)),
                       GetAttrName (attridOfAttracc (at)));
  }

  case KChainacc:
  { Chainacc at = ExprToChainacc (e);
    return PTGAttrAcc (GetIndexedProdSym (symbnoOfChainacc (at)),
                       GetDefName (chainidOfChainacc (at)));
  }

  case KCall:
    return TrCall (ExprToCall (e));

  case KConstit:
    if (singleOfConstit (ExprToConstit (e)))
         return PTGConstituent ();
    else return PTGConstituents ();

  case KIncluding:
    return PTGIncluding ();

  default:
    return Unknown;
  }
}/* TrExpr */

SEQString termnames = (SEQString)0; /* list of terminal names */
SEQString termtypes = (SEQString)0; /* list of terminal types */

void EnterTerminal (name, type) char *name, *type;
{ SEQString names = termnames;
  char* curname;
  
  while (!emptySEQString (names))
  { retrievefirstSEQString (names, curname);
    if (strcmp (curname, name) == 0)
	return;
    names = tailSEQString (names);
  }
  appendfrontSEQString (termnames, name);
  appendfrontSEQString (termtypes, type);
}/* EnterTerminal */

PTGNode GetTerminals ()
{ SEQString names = termnames, types = termtypes;
  char *curname, *curtype;
  PTGNode res = PTGNULL;
  
  while (!emptySEQString (names))
  { retrievefirstSEQString (names, curname);
    retrievefirstSEQString (types, curtype);
    res = PTGSeq (res, PTGTerminalDef (curname, curtype));
    names = tailSEQString (names);
    types = tailSEQString (types);
  }
  return res;
}/* GetTerminals */

PTGNode ShowProduction (did) int did;
{
   PTGNode res, pname, plhs;
   Prod AProd;
   Def d;
   int lhs;
   SEQEntity rhs;
   Entity ent;

#define NEUTRAL  0
#define MARKED   1
#define TERMSEEN 2
   int state = NEUTRAL;
   
   if (did > DIDNON)
      d = lookup_def(did);
   else
      return (PTGNULL);

   if (typeof(d) != KProd)
      return (PTGNULL);
   AProd = DefToProd(d);
   lhs = lhsOfProd(AProd);

   InitProdSyms ();
   EnterProdSym (lhs);
   initializeSEQString (prodterms);

   res = PTGNULL;
   rhscnt = 0;
   plhs = PTGSymbol(GetDefName(lhs)); rhscnt++;
   pname = PTGName(dnameOfDef(d));

   rhs = rhsOfProd(AProd);
   while (!emptySEQEntity (rhs))
   { retrievefirstSEQEntity (rhs, ent);
     if (typeof (ent) == KLiteral)
     {  Literal ALiteral;
        char *str, *termname;
	ALiteral = EntityToLiteral(ent);
	str = strOfLiteral(ALiteral);
        if (strlen (str) == 0)
	   state = MARKED;
	else
	if (state == MARKED)
	{ /* output terminal name: */
	  res = PTGSeq(res, PTGSymbol (PTGName(str)));
	  termname = str;
          appendrearSEQString (prodterms, str);
	  state = TERMSEEN;
	}
	else
	if (state == TERMSEEN)
	{ /* ignore terminal type, collect terminal definition: */
	  EnterTerminal (termname, str);
	  state = NEUTRAL;
	}
	else /* state == NEUTRAL */
	{ /* output literal terminal: */
          res = PTGSeq(res, PTGLiteral(PTGName(str)));
	}
     }/* Literal */
     else
     if (typeof (ent) == KSymbol)
     { Symbol ASymbol;
       int did;
       ASymbol = EntityToSymbol(ent);
       did = didOfSymbol(ASymbol);
       EnterProdSym (did);
       if (state == MARKED)
             res = PTGSeq(res, PTGGenSymbol(GetDefName(did)));
       else  res = PTGSeq(res, PTGSymbol(GetDefName(did)));
       rhscnt++;
       state = NEUTRAL;
     }/* Symbol */
     rhs = tailSEQEntity (rhs);
  }

  return (PTGVisitRule(pname, plhs, res));
}/* ShowProduction */


void PAttrEval (AAttrEval) AttrEval AAttrEval;
{
   SEQDef TRdefseq;
   Def ADef;
   SEQAttribution TRattrrules;
   Attribution AAttribution;
   /* ===================process a AttrEval======================= */
   PTGNode Comma, ColSemi, Semicol, NewLine;
   PTGNode TreeStore, StackStore;
   PTGNode OrigChain, OrigConst, OrigIncl;
   PTGNode AttrLists;
   PTGNode NTerms, Terms, AllVisits;
   int NTermCnt = 0;

   init_did_table(AAttrEval->defseq);

   Unknown = PTGUnknown();
   Comma = PTGComma();
   ColSemi = PTGColSemi();
   Semicol = PTGSemicol();
   NewLine = PTGNewLine();

   TreeStore = PTGTreeStore();
   StackStore = PTGStackStore();
   OrigChain = PTGOrigChain();
   OrigConst = PTGOrigConst();
   OrigIncl = PTGOrigIncl();

   /* symbols only : */
   NTerms = PTGNONTERM();

   /* attribute lists */
   AttrLists = PTGNULL;

   foreachinSEQDef(defseqOfAttrEval(AAttrEval), TRdefseq, ADef)
   {
      char *dname;
      dname = dnameOfDef(ADef);

      switch (typeof(ADef))
      {
      case KChain:
	    break;

      case KTypedef:
	    break;

      case KSymb:
	 {
	    Symb ASymb;
	    int tornt;
	    SEQAttrdef TRattrs;
	    Attrdef AAttrdef;
	    ASymb = DefToSymb(ADef);
	    tornt = torntOfSymb(ASymb);
	    /* ===================process a Symb========================== */

	    /* symbols only : */
	    if (tornt == SYMBNONT)
	    {
	       if (NTermCnt > 0)
		  NTerms = PTGSeq(NTerms, Comma);
	       if ((NTermCnt++ % 5) == 0)
		  NTerms = PTGSeq(NTerms, NewLine);
	       NTerms = PTGSeq(NTerms, PTGName(dname));
	    } else
	    {
	       /* there are no terminals defined anymore */
	    }

	    /* attribute lists */
	    AttrLists = PTGSeq (AttrLists,
	                        PTGAttrListHead
				  (PTGNONTERM(), PTGName(dname)));

	    foreachinSEQAttrdef(attrsOfSymb(ASymb), TRattrs, AAttrdef)
	    {
	       char *name;
	       int row;
	       int col;
	       int typeid;
	       int class;
	       int prodid;
	       int store;
	       int gen;
	       int part;
	       char *globname;
	       PTGNode adecl, ainfo, a1, a2, a3;
	       name = nameOfAttrdef(AAttrdef);
	       row = rowOfAttrdef(AAttrdef);
	       col = colOfAttrdef(AAttrdef);
	       typeid = typeidOfAttrdef(AAttrdef);
	       class = classOfAttrdef(AAttrdef);
	       prodid = prodidOfAttrdef(AAttrdef);
	       store = storeOfAttrdef(AAttrdef);
	       gen = genOfAttrdef(AAttrdef);
	       part = partOfAttrdef(AAttrdef);
	       globname = globnameOfAttrdef(AAttrdef);
	       /* ==============process a Attrdef=================== */
	       /* attribute lists */
	       a1 = GetDefName(typeid);
	       if (class == ATCLSYNT)
		  a2 = PTGSYNT();
	       else if (class == ATCLINH)
		  a2 = PTGINH();
	       else
		  a2 = Unknown;
	       a3 = (IsLast(TRattrs) ? PTGSpace2() : Comma);
	       adecl = PTGAttrDecl(PTGName(name), a1, a2, a3);

	       if (store == STORGLVA)
		  a1 = PTGVarStore(PTGName(globname));
	       else if (store == STORGLST)
		  a1 = StackStore;
	       else if (store == STORTRAT)
		  a1 = TreeStore;
	       else
		  a1 = Unknown;

	       if (gen == GENINCL)
		  a2 = OrigIncl;
	       else if (gen == GENCONST)
		  a2 = OrigConst;
	       else if (gen == GENCHAIN)
		  a2 = OrigChain;
	       else if (prodid > 0)
		  a2 = PTGOrigRule(GetDefName(prodid));
	       else
		  a2 = PTGNULL;

	       a3 = MakeCoord(row, col);
	       ainfo = PTGAttrInfo(PTGNumb(part), a1, a2, a3);
	       AttrLists = PTGSeq(AttrLists, PTGSeq(adecl, ainfo));
	       /* ============end of Attrdef========================== */
	       /* ============end of Symb============================= */
	    }	/* foreachinSEQAttrdef */

	    AttrLists = PTGSeq(AttrLists, PTGSeq(NewLine, Semicol));
	    /* ===============end of Symb============================= */
	    break;
	 }	/* Symb */

      case KProd:
	    break;
      }	/* switch Def */
   }/* foreachinSEQDef */

   /* symbols only : */
   NTerms = PTGSeq(NTerms, ColSemi);

   /* visit sequences */
   AllVisits = PTGNULL;

   foreachinSEQAttribution(attrrulesOfAttrEval(AAttrEval), TRattrrules, AAttribution)
   {
      int prodid;
      SEQAttrrule TRattrrules;
      Attrrule AAttrrule;
      prodid = prodidOfAttribution(AAttribution);
      /* ===================process a Attribution======================= */

      /* visit sequences */
      AllVisits = PTGSeq (AllVisits, ShowProduction(prodid));

      IsInitCycle = 0;
      foreachinSEQAttrrule(attrrulesOfAttribution(AAttribution), 
                           TRattrrules, AAttrrule)
      {
	 switch (typeof(AAttrrule))
	 {
	 case KCall:
	    {
	       Call ACall = AttrruleToCall(AAttrrule);
	       PTGNode pcoord = 
                  MakeCoord (rowOfCall (ACall), colOfCall (ACall));
               PTGNode pcall = TrCall (ACall);

               AllVisits = PTGSeq (AllVisits,
                                  PTGComputation (pcall, pcoord));
               if (IsInitCycle)
                  AllVisits = PTGSeq (AllVisits, PTGLabel ());
               IsInitCycle = 0;
               break;
	    }/* Call */

	 case KVisit:
	    {
	       Visit AVisit;
	       int symbno;
	       int ord;
	       AVisit = AttrruleToVisit(AAttrrule);
	       symbno = symbnoOfVisit(AVisit);
	       ord = ordOfVisit(AVisit);
	       /* ===================process a Visit=====  =============== */
	       /* visit sequences */
	       if (symbno == 0)
		  AllVisits = PTGSeq(AllVisits, PTGLeave(PTGNumb(ord)));
	       else
		  AllVisits = PTGSeq (AllVisits,
				      PTGVisit(PTGNumb(ord), 
                                               GetIndexedProdSym(symbno)));
	       /* ===================end of Visit========================== */
	       break;
	    }/* Visit */

	 case KTransfer:
	    {  /* TRANSFER is obsolete */
	    }/* Transfer */

	 case KChainStart:
	    {
	       ChainStart AChainStart;
	       int row;
	       int col;
	       AChainStart = AttrruleToChainStart(AAttrrule);
	       row = rowOfChainStart(AChainStart);
	       col = colOfChainStart(AChainStart);
	       /* ===========process a ChainStart======================= */
	       /* visit sequences */
	       AllVisits = PTGSeq(AllVisits,
				  PTGChainStart(MakeCoord(row, col)));
	       /* ==========end of ChainStart========================== */
	       break;
	    }/* ChainStart */

	 default:;
	 }/* switch Attrrule */
      }	/* foreachinSEQAttrrule */

      /* visit sequences */
      AllVisits = PTGSeq(AllVisits, NewLine);
      /* =================end of Attribution========================== */
   }/* foreachinSEQAttribution */

   {
      int ind;
      char *name;
      PTGNode filenames;

      filenames = PTGNULL;
      ind = 0;
      do
      {
	 name = GetErrMapFileName(ind);
	 if (strlen(name) == 0)
	    break;
	 filenames = PTGSeq(filenames,
			    PTGFileAssoc(
				  PTGFileRef(PTGNumb(ind)), PTGName(name)));
	 ind++;
      } while (1);
      filenames = PTGFileList(filenames);
      /* symbols only : */
      Terms = PTGSeq (GetTerminals (), NewLine);
      PTGOutFile("symbols.info", PTGSeq (PTGSeq (Terms, NTerms), NewLine));

      /* attribute lists */
      PTGOutFile("attrs.info", PTGSeq(PTGSeq(filenames, AttrLists), NewLine));

      /* visit sequences */
      PTGOutFile("visit.info", PTGSeq(PTGSeq(filenames, AllVisits), NewLine));
   }
   /* ===================end of AttrEval========================== */
}/* PAttrEval */

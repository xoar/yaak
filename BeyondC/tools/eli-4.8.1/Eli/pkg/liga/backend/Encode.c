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
/* $Id: Encode.c,v 4.5 2001/11/05 14:51:03 cogito Exp $ */
/* Copyright, 1995, AG-Kastens, University Of Paderborn  */

#include "global.h"
#include "LIGA.h"
#include "LIGAMacros.h"
#include "ligaconsts.h"
#include "lookup_idl.h"
#include "ptg_gen.h"

#include "ProdSectList.h"
#include "Encode.h"
#include "DynSpace.h"

/* a list of productions ordered by non increasing number of sections: */
/* also used by GenMon.c */
ProdSectPtrList	prodsectlist = NULLProdSectPtrList;

int cmpsect (l, r) VoidPtr l, r;
/* compare function: yields r->sectno - l->sectno */
{
return ((ProdSectPtr)r)->sectno - ((ProdSectPtr)l)->sectno;
}

void ProdSectno (proddef, sectno)
/* enter a new production and its number of sections into the list */
	Prod proddef; int sectno;
{	ProdSectPtr	prodsect;

prodsect = (ProdSectPtr) DynAlloc (VoidPtrListSpace, sizeof (ProdSect));
prodsect->proddef = proddef;
prodsect->sectno = sectno;

prodsectlist = 
	OrderedInsertVoidPtrList (prodsectlist, (VoidPtr)prodsect, cmpsect);
}/* ProdSectno */

static PTGNode EncodeSymbsProds (ae) AttrEval ae;
/* encodes the symbols and
   encodes the rules in non-ascending order of section numbers
*/
{	int	symcode = 0, rulecode = 0;
	PTGNode	res = PTGNULL;
	ProdSectPtrList	prods;
	SEQDef defs; Def def;

foreachinSEQDef (defseqOfAttrEval (ae), defs, def)
	if (typeof(def) == KSymb) {
		res = PTGSeq(res, PTGDefine(
				PTGSymbCode (PTGAsIs (dnameOfDef(def))),
				PTGNumb (symcode++)));
	}

prods = prodsectlist;
while (prods != NULLProdSectPtrList) {
	res = PTGSeq (res,
	PTGDefine (
		PTGRuleCode (PTGAsIs (dnameOfProd (
			(HeadProdSectPtrList (prods))->proddef))),
		PTGNumb (rulecode++)));
	prods = TailProdSectPtrList (prods);
}
return (res);
}/* EncodeSymbsProds */


PTGNode VisitMapHead ()
/* generate a header for the map array of each section number */
{	int     sectno = 0;
	PTGNode res = PTGNULL;

if (prodsectlist) sectno = HeadProdSectPtrList (prodsectlist)->sectno;
while (sectno) {
	res = PTGSeq (res, PTGVisitMapExtern (PTGNumb (sectno)));
	sectno--;
}
return (res);
}/* VisitMapHead */

PTGNode VisitMaps ()
/* for each section number generate the array map of rules that have
   at least as many sections
*/
{	int	sectno = 0;
	ProdSectPtrList	prods;
	PTGNode	res = PTGNULL;
	PTGNode	namelist, comma, newline;
	int	cnt;

comma = PTGComma ();
newline = PTGNewLine ();
if (prodsectlist) sectno = HeadProdSectPtrList (prodsectlist)->sectno;
while (sectno > 0) {
	prods = prodsectlist;
	namelist= PTGNULL; cnt = 0;
	while ((prods != NULLProdSectPtrList) &&
		(HeadProdSectPtrList (prods)->sectno >= sectno)) {
		if (cnt++ != 0)
			namelist = PTGSeq (namelist, comma);
		if (cnt % 5 == 0)
			namelist = PTGSeq (namelist, newline);
		namelist = PTGSeq (namelist,
		PTGVisitCast(PTGVisitProcName (
			PTGNumb (sectno),
			PTGAsIs (dnameOfProd (
				HeadProdSectPtrList (prods)->proddef)))));
		prods = TailProdSectPtrList (prods);
	}
	res = PTGSeq (res,
		PTGVisitArray (PTGNumb (sectno), namelist));
	sectno--;
}
return (res);
}/* VisitMaps */

PTGNode LhsMap ()
/* generate an array that maps rule codes to the codes of their lhs symbols */
{	ProdSectPtrList	prods;
	PTGNode	namelist, comma, newline;
	int	cnt;
	Def	lhsdef;

comma = PTGComma ();
newline = PTGNewLine ();
prods = prodsectlist;
namelist= PTGNULL; cnt = 0;
while (prods != NULLProdSectPtrList) {
	if (cnt++ != 0)
		namelist = PTGSeq (namelist, comma);
	if (cnt % 5 == 0)
		namelist = PTGSeq (namelist, newline);
	lhsdef = lookup_def (lhsOfProd (HeadProdSectPtrList (prods)->proddef));
	namelist = PTGSeq (namelist,
		PTGSymbCode (PTGAsIs (dnameOfDef (lhsdef))));

	prods = TailProdSectPtrList (prods);
}
return PTGLhsArray (namelist);
}/* LhsMap */

void Encodings (ae) AttrEval ae;
/* generate files for rule and symbol encodings
   and mappings from rules to visits and to lhs symbols
*/
{ SEQAttribution s; Attribution ruleattrib;
  SEQAttrrule ars; Attrrule atrule;
  Def proddef;
  Prod prod;
  Visit vs;
  int sectno;

/* initialize dyn space: */
(void)ConsVoidPtrList((void*)0, NULLVoidPtrList);

/* enter section number for each rule into ordered list: */
foreachinSEQAttribution (attrrulesOfAttrEval (ae), s, ruleattrib) {
	proddef = lookup_def (prodidOfAttribution (ruleattrib));
	prod = DefToProd (proddef);
        sectno = 0;
	foreachinSEQAttrrule (attrrulesOfAttribution(ruleattrib), ars, atrule)
		if (typeof (atrule) == KVisit) {
			vs = AttrruleToVisit (atrule);
			if (symbnoOfVisit (vs) == 0)
				sectno = ordOfVisit (vs);
		}
	ProdSectno (prod, sectno);
}

PTGOutFile("nodecode.h", PTGEncodeFile (EncodeSymbsProds (ae)));
PTGOutFile ("visitmap.h", PTGVisitMapHead (VisitMapHead ()));
PTGOutFile ("visitmap.c", PTGVisitMapFile (VisitMaps ()));
PTGOutFile("nodecode.c", PTGFile (LhsMap ()));
}

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
/* $Id: incl.c,v 4.2 1997/08/29 07:55:18 peter Exp peter $ */

/* LIGA backend module		*/
/* including translation	*/
/* U. Kastens, 30. 12. 91	*/
/* including source access corrected */

#include <string.h>

#include "global.h"
/*
#include "LIGA.h"
#include "LIGAMacros.h"
*/
#include "lookup_idl.h"
#include "ligaconsts.h"
#include "ptg_gen.h"

#include "backvisit.h"
#include "incl.h"
#include "bool.h"
#include "visitcmp.h"

static Attrdef	tmpAttrdef;
static Def	tmpDef;

static SEQExpr incllist = NULL;

void InsertIncl (inc)
	Including	inc;
{	bool	found = false;
	SEQExpr	se;
	Expr	ex;
	Symbattr	sa;

retrievefirstSEQSymbattr (inclattrsOfIncluding (inc), sa);
tmpAttrdef = lookup_attrdef (attrdefOfSymbattr (sa));
if (typeidOfAttrdef (tmpAttrdef)
	== DIDVOID)
	return;

foreachinSEQExpr (incllist, se, ex) {
	if (strcmp (genattrOfIncluding (inc),
			genattrOfIncluding (ExprToIncluding (ex))) == 0)
		found = true;
}
ex = IncludingToExpr (inc);
if (!found) incllist = appendfrontSEQExpr (incllist, ex);
}/*InsertIncl*/

void GenVarDecls ()
{	SEQExpr 	se;
	Expr    	ex;
	char		*tp;
	Symbattr 	sa;
	Including	inc;

foreachinSEQExpr (incllist, se, ex) {
	inc = ExprToIncluding (ex);
	retrievefirstSEQSymbattr (inclattrsOfIncluding (inc), sa);

	tmpAttrdef = lookup_attrdef (attrdefOfSymbattr (sa));
	tmpDef = lookup_def (typeidOfAttrdef (tmpAttrdef));
	tp = dnameOfDef (tmpDef);

	globvardecls = PTGSeq (globvardecls,
		PTGDecl (PTGPtrTo (PTGAsIs (tp)),
		PTGInclGlobName (PTGAsIs (genattrOfIncluding (inc)))));
	globvarextern = PTGSeq (globvarextern,
		PTGExternDecl (PTGPtrTo (PTGAsIs (tp)),
		PTGInclGlobName (PTGAsIs (genattrOfIncluding (inc)))));
}
}/*GenVarDecls*/

void FindInclExprSeq (se)
	SEQExpr	se;
{	SEQExpr	ses;
	Expr	ex;

foreachinSEQExpr (se, ses, ex)
	if (typeof (ex) == KIncluding)
		InsertIncl (ExprToIncluding (ex));
	else if (typeof (ex) == KCall)
		FindInclExprSeq (paramsOfCall (ExprToCall (ex)));
}/*FindInclExprSeq*/

void TrInclVars (ae)
	AttrEval	ae;
{	SEQAttribution	as;
	Attribution	ab;
	SEQAttrrule	ats;
	Attrrule	ar;

foreachinSEQAttribution (attrrulesOfAttrEval (ae), as, ab)
foreachinSEQAttrrule (attrrulesOfAttribution (ab), ats, ar)
if (typeof (ar) == KCall)
	FindInclExprSeq (paramsOfCall (AttrruleToCall (ar)));

GenVarDecls ();
}/*TrInclVars*/

int	currlhs;	/* both set by TrInclSect */
int	currsectno;	/* used by CurrAttrDid in TrIncluding */

int CurrAttrDid (inc)
	Including       inc;
{	SEQSymbattr     sas;
	Symbattr        sa;
	Attrdef		ad;

foreachinSEQSymbattr (inclattrsOfIncluding (inc), sas, sa) {
	ad = lookup_attrdef (attrdefOfSymbattr (sa));
	if ((currlhs == symbdefOfSymbattr (sa)) &&
	    (currsectno >= partOfAttrdef (ad)))
		return (attrdefOfSymbattr (sa));
}
return (DIDNON);
}/*CurrAttrDid*/

void TrInclSect (sydef, sectno, decls, pre, post)
	Symb		sydef;
	int		sectno;
	PTGNode		*decls, *pre, *post;
/* must be called before any TrIncluding of this section */
{	SEQExpr 	se;
	Expr    	ex;
	char		*tp;
	Attrdef		ad;
	int		attrdid;
	Including	inc;
	PTGNode		loc, glob;

currlhs = didOfSymb (sydef);
currsectno = sectno;

foreachinSEQExpr (incllist, se, ex) {
	inc = ExprToIncluding (ex);
	attrdid = CurrAttrDid (inc);
	if (attrdid != DIDNON) {
		/* startup code for including produces code */
		NoComputation = false;
		ad = lookup_attrdef (attrdid);
		tmpDef = lookup_def (typeidOfAttrdef (ad));
		tp = dnameOfDef (tmpDef);
		loc = PTGInclLocName (PTGAsIs (genattrOfIncluding (inc)));
		glob = PTGInclGlobName (PTGAsIs (genattrOfIncluding (inc)));

		(*decls) = PTGSeq (*decls,
			PTGDecl (PTGPtrTo (PTGAsIs (tp)), loc));

		(*pre) = PTGSeq (*pre,
			PTGInclPre (loc, glob, glob,
				PTGTreeAttrName (
					PTGAsIs (nameOfAttrdef (ad)))));

		(*post) = PTGSeq (*post,
			PTGInclPost (glob, loc));
	}
}
}/*TrInclSect*/

PTGNode TrIncluding (inc)
	Including	inc;
{	int		attrdid;

attrdid = CurrAttrDid (inc);
if (attrdid != DIDNON)
	return (PTGContent (
		PTGInclLocName (PTGAsIs (genattrOfIncluding (inc)))));
else
	return (PTGContent (
		PTGInclGlobName (PTGAsIs (genattrOfIncluding (inc)))));
}/*TrIncluding*/

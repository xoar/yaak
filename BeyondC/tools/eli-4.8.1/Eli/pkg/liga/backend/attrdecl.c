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
/* $Id: attrdecl.c,v 4.3 2001/11/05 14:51:03 cogito Exp $ */

/* LIGA backend module		*/
/* attribute declarations	*/

#include <string.h>
#include "global.h"
/*
#include "LIGA.h"
#include "LIGAMacros.h"
*/
#include "ligaconsts.h"
#include "lookup_idl.h"
#include "ptg_gen.h"

#include "idn.h"
/* for identification of variable identifiers */

#include "backvisit.h"
#include "attrdecl.h"
#include "bool.h"

static Def	tmpDef;

#define GENTREEATTR     "GENTREE"
#define IsGenAttr(aname) (strcmp (nameOfAttrdef (aname), GENTREEATTR) == 0)


bool IsVoidAttr (ad)
	Attrdef	ad;
{	int	tpdid;

tpdid = typeidOfAttrdef (ad);
return ((tpdid == DIDVOID) || (tpdid == DIDVOLI));
}

bool HasTreeAttrs (aseq)
	SEQAttrdef	aseq;
{	Attrdef		ad;
	SEQAttrdef	as;

foreachinSEQAttrdef (aseq, as, ad) {
	if ((storeOfAttrdef (ad) == STORTRAT) &&
	    (! IsVoidAttr (ad)) &&
	    (! IsGenAttr (ad)))
		return (true);
}
return (false);
}/*HasTreeAttrs*/

PTGNode TreeAttrDecls (aseq, prodid)
	SEQAttrdef aseq; int prodid;
/* translates the tree attributes in aseq;
   if prodid == DIDNON then only the non production attributes,
   else only the production attributes for that prodid
*/
{	Attrdef		ad;
	SEQAttrdef	as;
	PTGNode		res = PTGNULL;

foreachinSEQAttrdef (aseq, as, ad) {
	if ((storeOfAttrdef (ad) == STORTRAT) &&
	    (! IsVoidAttr (ad)) &&
	    (! IsGenAttr (ad))) {
		tmpDef = lookup_def(typeidOfAttrdef (ad));
		if (prodidOfAttrdef(ad) == prodid)
			res = PTGSeq (res,
				PTGAttrComp (
					dnameOfDef (tmpDef),
					nameOfAttrdef (ad)));
	}
}
return res;
}/*TreeAttrDecls*/

void TrNodeTypes (alldefs) SEQDef alldefs;
/* translates symbol and rule definitions into node types */
{ SEQDef defs; Def def;
  PTGNode typeres = PTGNULL;
  PTGNode structres = PTGNULL;

/* generate pointer type defs: */
  foreachinSEQDef (alldefs, defs, def)
  switch (typeof(def)) {
  case KSymb:
	typeres = PTGSeq (typeres,
		PTGSymbTypeDef (dnameOfDef(def)));
	break;
  case KProd:
	typeres = PTGSeq (typeres,
	  	PTGProdTypeDef (dnameOfDef(def)));
	break;
  }

/* generate symbol node types and rule node types: */
  foreachinSEQDef (alldefs, defs, def)
  switch (typeof(def)) {
  case KSymb:
	structres = PTGSeq (structres,
		PTGSymbStructDecl (
			dnameOfDef(def),
			TreeAttrDecls (attrsOfSymb(DefToSymb(def)), DIDNON)));
	break;
  case KProd: {
	PTGNode descs = PTGNULL; int descscnt = 1;
	Symb lhsdef;
	SEQEntity rhs; Entity ent;
	int IsListofGenProd;

	foreachinSEQEntity (rhsOfProd(DefToProd(def)), rhs, ent) {
		if (typeof(ent) == KSymbol) {
			tmpDef = lookup_def(didOfSymbol(EntityToSymbol(ent)));
			descs = PTGSeq (descs,
				PTGSubTreeComp (
					dnameOfDef (tmpDef),
					descscnt++));
		}
	}
	tmpDef = lookup_def(lhsOfProd(DefToProd(def)));
	lhsdef = DefToSymb (tmpDef);
	IsListofGenProd = (strncmp (dnameOfDef(tmpDef), "LST_", 4) == 0);
	structres = PTGSeq (structres,
		PTGProdStructDecl (
			dnameOfDef(def),
			TreeAttrDecls (attrsOfSymb(lhsdef), DIDNON),
			(IsListofGenProd && descscnt == 1 ?
				PTGListDescs() /* empty list rule */
				: descs),
			TreeAttrDecls (attrsOfSymb(lhsdef), didOfDef(def))
		));
	break;
	}
  }

PTGOutFile ("node.h", PTGNodeTypeFile (typeres, structres));
}/* TrNodeTypes */


static int varcnt = 1;

void VarAttrDecls (aseq)
	SEQAttrdef	aseq;
{	Attrdef		ad;
	SEQAttrdef	as;
	char		*tp;
	int		cmp, lg, dummy;

foreachinSEQAttrdef (aseq, as, ad) {
	tmpDef = lookup_def (typeidOfAttrdef (ad));
	tp = dnameOfDef (tmpDef);
	if ((storeOfAttrdef (ad) == STORGLVA) &&
	    (! IsVoidAttr (ad)) &&
	    (! IsGenAttr (ad))) {
		cmp = varcnt;
		lg = strlen (globnameOfAttrdef (ad));
		mkidn (globnameOfAttrdef (ad), lg, &cmp, &dummy);
		if (cmp == varcnt) {/* new identifier */
			varcnt++;
			globvardecls = PTGSeq (globvardecls,
			PTGDecl (
				PTGAsIs (tp),
				PTGVarAttrName (
					PTGAsIs (globnameOfAttrdef (ad)))));
			globvarextern = PTGSeq (globvarextern,
			PTGExternDecl (
				PTGAsIs (tp),
				PTGVarAttrName (
					PTGAsIs (globnameOfAttrdef (ad)))));
		}
	}
}
}/*VarAttrDecls*/


PTGNode StackAttrDecls (aseq, visit, sympos)
	SEQAttrdef	aseq;
	int		visit, sympos;
{	Attrdef		ad;
	SEQAttrdef	as;
	PTGNode		res, attrname;
	char		*tp;

res = PTGNULL;

foreachinSEQAttrdef (aseq, as, ad) {
	if ((storeOfAttrdef (ad) == STORGLST) &&
	    (! IsVoidAttr (ad)) &&
	    (! IsGenAttr (ad)) ) {
		attrname = PTGRhsStackAttrName (
			PTGNumb (sympos),
			PTGAsIs (nameOfAttrdef (ad)));

		tmpDef = lookup_def (typeidOfAttrdef (ad));
		tp = dnameOfDef (tmpDef);

		res = PTGSeq (res, PTGDecl (PTGAsIs (tp), attrname));
	}
}
return (res);
}/*StackAttrDecls*/


PTGNode StackAttrParamSpecs (aseq, visit)
	SEQAttrdef	aseq;
	int		visit;
{	Attrdef		ad;
	SEQAttrdef	as;
	PTGNode		res, attrname;
	char		*tp;

res = PTGNULL;

foreachinSEQAttrdef (aseq, as, ad) {
	if ((storeOfAttrdef (ad) == STORGLST) &&
	    (partOfAttrdef (ad) <= visit) &&
		/* all visits after lifetime begin */
	    (! IsVoidAttr (ad)) &&
	    (! IsGenAttr (ad)) ) {
		attrname = PTGLhsStackAttrName (
				PTGAsIs (nameOfAttrdef (ad)));

		tmpDef = lookup_def (typeidOfAttrdef (ad));
		tp = dnameOfDef (tmpDef);
		res = PTGSeq (res, PTGDecl (PTGPtrTo (PTGAsIs (tp)), attrname));
	}
}
return (res);
}/*StackAttrParamSpecs*/

PTGNode StackAttrParamProtos (aseq, visit)
	SEQAttrdef	aseq;
	int		visit;
{	Attrdef		ad;
	SEQAttrdef	as;
	PTGNode		res, attrname;
	char		*tp;

res = PTGNULL;

foreachinSEQAttrdef (aseq, as, ad) {
	if ((storeOfAttrdef (ad) == STORGLST) &&
	    (partOfAttrdef (ad) <= visit) &&
		/* all visits after lifetime begin */
	    (! IsVoidAttr (ad)) &&
	    (! IsGenAttr (ad)) ) {
		attrname = PTGLhsStackAttrName (
				PTGAsIs (nameOfAttrdef (ad)));

		tmpDef = lookup_def (typeidOfAttrdef (ad));
		tp = dnameOfDef (tmpDef);

		res= PTGSeq (PTGProto(PTGPtrTo(PTGAsIs (tp)), attrname), res);
	}
}
return(res);
}/*StackAttrParamProtos*/

PTGNode StackAttrNames (aseq, visit)
	SEQAttrdef	aseq;
	int		visit;
{	Attrdef		ad;
	PTGNode		res;
	SEQAttrdef	as;

res = PTGNULL;

foreachinSEQAttrdef (aseq, as, ad) {
	if ((storeOfAttrdef (ad) == STORGLST) &&
	    (partOfAttrdef (ad) <= visit) &&
		/* all visits after lifetime begin */
	    (! IsVoidAttr (ad)) &&
	    (! IsGenAttr (ad)) ) {
		res = PTGComSeq (PTGLhsStackAttrName (
				PTGAsIs (nameOfAttrdef (ad))),
				res);
	}
}
return (res);
}/*StackAttrNames*/

PTGNode StackArgs (aseq, visit, sympos)
	SEQAttrdef	aseq;
	int		visit, sympos;
{	Attrdef		ad;
	SEQAttrdef	as;
	PTGNode		res;

res = PTGNULL;

foreachinSEQAttrdef (aseq, as, ad) {
	if ((storeOfAttrdef (ad) == STORGLST) &&
	    (partOfAttrdef (ad) <= visit) &&
		/* all visits after lifetime begin */
	    (! IsVoidAttr (ad)) &&
	    (! IsGenAttr (ad)) ) {
		res = PTGComSeq (PTGAddr (
			PTGRhsStackAttrName (
				PTGNumb (sympos),
				PTGAsIs (nameOfAttrdef (ad)))),
			res);
	}
}
return (res);
}/*StackArgs*/

PTGNode StackProtos (aseq, visit, sympos)
	SEQAttrdef	aseq;
	int		visit, sympos;
{	Attrdef		ad;
	SEQAttrdef	as;
	PTGNode		res;
	char*           tp;

res = PTGNULL;

foreachinSEQAttrdef (aseq, as, ad) {
	if ((storeOfAttrdef (ad) == STORGLST) &&
	    (partOfAttrdef (ad) <= visit) &&
		/* all visits after lifetime begin */
	    (! IsVoidAttr (ad)) &&
	    (! IsGenAttr (ad)) ) {
	        tmpDef = lookup_def(typeidOfAttrdef(ad));
		tp = dnameOfDef(tmpDef);
		res = PTGComSeq (PTGPtrTo (PTGAsIs (tp)), res);
	}
}
return (res);
}/*StackProtos*/

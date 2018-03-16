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
/* $Id: expr.c,v 4.5 1999/11/24 12:41:29 uwe Exp peter $ */

/* LIGA backend module		*/
/* expression translation	*/
/* U. Kastens, 5. 11. 91	*/

#include <string.h>

#include "err.h"
#include "global.h"
/*
#include "LIGA.h"
#include "LIGAMacros.h"
*/
#include "ligaconsts.h"
#include "lookup_idl.h"
#include "ptg_gen.h"

#include "expr.h"
#include "attr.h"
#include "attrdecl.h"
#include "incl.h"
#include "bool.h"
#include "backvisit.h"
#include "visitcmp.h"

#define IsGenAttr(aname) (strcmp (nameOfAttrdef (aname), GENTREEATTR) == 0)

/* the cycle attributes of the current visit-section;
   reset for each section by TrSection in backvisit.h:
*/
static SEQint currcycleattrs;

void NewSection ()
{
  initializeSEQint (currcycleattrs);
}

POSITION coord;

PTGNode pppNoVal;

#define MANY 1000

bool CheckArgNr (c, l, u)
	Call	c;
	int	l, u;
{	int	i = 0;
	SEQExpr es;
	Expr	e;

foreachinSEQExpr (paramsOfCall (c), es, e) i++;

if (i < l) {
	coord.line = rowOfCall (c);
	coord.col = colOfCall (c);
	message (DEADLY, "argument(s) missing", 0, &coord);
	return (true);
} else if (i > u) {
	coord.line = rowOfCall (c);
	coord.col = colOfCall (c);
	message (FATAL, "too many arguments", 0, &coord);
	return (true);
}
return (false);
}/*CheckArgNr*/

char* GetSymbName (pos)
	int	pos;
{	Def	tmpDef;
	Symb	sydef;
if (pos == 0) {
	tmpDef = lookup_def (lhsOfProd (currproddef));
	sydef = DefToSymb (tmpDef);
} else	sydef = SymbDefInRhs (rhsOfProd (currproddef), pos);
return (dnameOfSymb(sydef));
}/* GetSymbName */

static bool InAssign, IsInitCycle;

PTGNode TrCall (c, context)
	Call	c;
	int	context;
{	SEQExpr params;
	Expr	e1, e2, e3;
	Attrdef	atdef;
	PTGNode	res = PTGNULL;

params = paramsOfCall (c);
if (strcmp (ASSIGNFCT, nameOfCall (c)) == 0) {
	SEQExpr modifiers;

	if (CheckArgNr (c, 2, MANY)) return (PTGNULL);
	retrievefirstSEQExpr(params, e1);
	retrievefirstSEQExpr(tailSEQExpr (params), e2);
	modifiers = tailSEQExpr (tailSEQExpr (params));
	while (!emptySEQExpr(modifiers)) 
	{	retrievefirstSEQExpr(modifiers, e3);
		if ((typeof (e3) == KName) &&
			(strcmp (nOfName (ExprToName (e3)), TNVOID) == 0))
			return (PTGNULL);
		modifiers = tailSEQExpr (modifiers);
	}
	if (typeof (e1) == KAttracc) 
        {
		InAssign = true; IsInitCycle = false;
		atdef  = 
                  lookup_attrdef 
                    (attridOfAttracc (ExprToAttracc (e1)));

		if (IsVoidAttr (atdef))
		   res = TrExpr (e2, isstmt);
		else 
                {  PTGNode lhscode = TrExpr (e1, isval);
                   Attracc lhsattr = ExprToAttracc (e1);

                   /* a value assignment produces code: */
		   NoComputation = false;
                   LhsAttrSymbNo = symbnoOfAttracc (lhsattr);
                   LhsAttrCode = lhscode;
                   LhsAttrdef = atdef;

		   if (IsGenAttr (atdef))
		      res = 
                        PTGGenAssign 
                          (lhscode,
                           GetSymbName (symbnoOfAttracc (lhsattr)),
			   TrExpr (e2, isval));
		   else
                      res = PTGAssign (lhscode, TrExpr (e2, isval));
		}

		if (IsInitCycle) 
                {
			/* keep attrid for loop check; loops may
			   refer to this cycle attribute only within
			   the current visit-section: */
			currcycleattrs = 
				appendfrontSEQint (currcycleattrs,
					attridOfAttracc (ExprToAttracc (e1)));
			/* end of loop check*/

			/* a value assignment produces code: */
			NoComputation = false;
			res = PTGSeq (PTGStmt (res),
				PTGLabel (PTGLabName (
					PTGAsIs (nameOfAttrdef (atdef)),
					PTGNumb (symbnoOfAttracc (
						ExprToAttracc (e1))))));
		}
		InAssign = false;
		return (res);
	} else {/* an illegal assignment: */
		NoComputation = false;
		return (PTGAssign (TrExpr (e1, isval), TrExpr (e2, isval)));
	}
} else
/* The following calls are not marked by NoComputation = false
   if can be ignored in case that they themselves are a
   plain computation which is not contained in a larger construct.
*/
if (strcmp (TERMFCT, nameOfCall (c)) == 0) {
        Val v;
        if (context == isstmt) return (PTGNULL);
        if (CheckArgNr (c, 1, 1)) return (PTGNULL);
        retrievefirstSEQExpr(params, e1);
        if (typeof (e1) == KVal)
                v = ExprToVal (e1);
        else    return (PTGNULL);
	CallHasTermAcc = true;
        return PTGNonLitTermAcc (vOfVal (v));
} else
if (strcmp (LINEACCFCT, nameOfCall (c)) == 0) {
        if (context == isstmt) return (PTGNULL);
        if (CheckArgNr (c, 1, 1)) return (PTGNULL);
        retrievefirstSEQExpr(params, e1);
        return PTGLineSelect (TrExpr (e1, isval));
} else
if (strcmp (COLACCFCT, nameOfCall (c)) == 0) {
        if (context == isstmt) return (PTGNULL);
        if (CheckArgNr (c, 1, 1)) return (PTGNULL);
        retrievefirstSEQExpr(params, e1);
        return PTGColSelect (TrExpr (e1, isval));
} else
if (strcmp (ADRFCT, nameOfCall (c)) == 0) {
        if (context == isstmt) return (PTGNULL);
        if (CheckArgNr (c, 1, 1)) return (PTGNULL);
        retrievefirstSEQExpr(params, e1);
        return PTGAddr (TrExpr (e1, isval));
} else
if (strcmp (STRINGFCT, nameOfCall (c)) == 0) {
        Literal lit;
        if (context == isstmt) return (PTGNULL);
        if (CheckArgNr (c, 1, 1)) return (PTGNULL);
        retrievefirstSEQExpr(params, e1);
        if (typeof (e1) == KLiteral)
                lit = ExprToLiteral (e1);
        else    return (PTGNULL);
        return (PTGC_Str (strOfLiteral (lit)));
} else
if (strcmp (CHARFCT, nameOfCall (c)) == 0) {
        Literal lit;
        if (context == isstmt) return (PTGNULL);
        if (CheckArgNr (c, 1, 1)) return (PTGNULL);
        retrievefirstSEQExpr(params, e1);
        if (typeof (e1) == KLiteral)
                lit = ExprToLiteral (e1);
        else    return (PTGNULL);
/* translation to C char to be added */
        return (PTGSeq (PTGAsIs ("'"),
                PTGSeq (PTGAsIs (strOfLiteral (lit)),
                        PTGAsIs ("'"))));
} else
if (strcmp (FLOATFCT, nameOfCall (c)) == 0) {
        Literal lit;
        if (context == isstmt) return (PTGNULL);
        if (CheckArgNr (c, 1, 1)) return (PTGNULL);
        retrievefirstSEQExpr(params, e1);
        if (typeof (e1) == KLiteral)
                lit = ExprToLiteral (e1);
        else    return (PTGNULL);
        return (PTGAsIs (strOfLiteral (lit)));
} else
if (strcmp (DEPFCT, nameOfCall (c)) == 0) {
	if (CheckArgNr (c, 1, MANY)) return (PTGNULL);
	retrievefirstSEQExpr(params, e1);
	return (TrExpr (e1, context));
} else
if (strcmp (ORDERFCT, nameOfCall (c)) == 0) {
	/* code producing expression */
	NoComputation = false;
	if (context == isstmt) {
		if (CheckArgNr (c, 0, MANY)) return (PTGNULL);
		return (TrSeqStmt (params));
	} else {
		if (CheckArgNr (c, 1, MANY)) return (PTGNULL);
		return (TrOrdSeq (params, context));
	}
} else
if (strcmp (VOIDFCT, nameOfCall (c)) == 0) {
/* VOIDFCT indicates dummy dependency argument */
	CheckArgNr (c, 1, 1);
	if (context == isval) {
		coord.line = rowOfCall (c);
		coord.col = colOfCall (c);
		message (FATAL,
		"internal error: VOID in value context", 0, &coord);
	} else if (context == isvoid)
		return (pppNoVal);
	return (PTGNULL);
} else
if (strcmp (IDFCT, nameOfCall (c)) == 0) {
/* IDFCT inserted by frontend for expressions on outmost level */
	CheckArgNr (c, 1, 1);
	retrievefirstSEQExpr(params, e1);
	return (TrExpr (e1, context));
} else
if (strcmp ("APPLY", nameOfCall (c)) == 0) {
	/* code producing expression */
	NoComputation = false;
	if (CheckArgNr (c, 1, MANY)) return (PTGNULL);
	retrievefirstSEQExpr(params, e1);
	return (PTGCall (
			PTGProcExpr (TrExpr (e1, isval)),
			TrSeqExpr (tailSEQExpr (params))));
} else
if (strcmp ("$MON", nameOfCall (c)) == 0) {
   /* "$MON" (rhs, Val (symbolnumber), Name("attrname"))
      Indicates void assign turned into plain computation.
      Extract symbol number and attr name for monitoring:
   */
   CheckArgNr (c, 3, 3);
   retrievefirstSEQExpr(params, e1);
   retrievefirstSEQExpr(tailSEQExpr (params), e2);
   retrievefirstSEQExpr (tailSEQExpr (tailSEQExpr (params)), e3);
   MonVoidAssign = 1;
   MonVoidSymbNo = vOfVal (ExprToVal (e2));
   MonVoidAttr = nOfName (ExprToName (e3));
   return TrExpr (e1, context);
} else
if (strcmp (BOTTOMUPFCT, nameOfCall (c)) == 0) {
	if (CheckArgNr (c, 1, 1)) return (PTGNULL);
	retrievefirstSEQExpr(params, e1);
	return (TrExpr (e1, context));
} else
if (strcmp (IFFCT, nameOfCall (c)) == 0) {
	/* code producing expression */
	NoComputation = false;
	if (context == isstmt) {
		if (CheckArgNr (c, 2, 3)) return (PTGNULL);
		retrievefirstSEQExpr(params, e1);
		retrievefirstSEQExpr(tailSEQExpr (params), e2);
		if (emptySEQExpr (tailSEQExpr (tailSEQExpr (params))))
			return (PTGIfStmt (
					TrExpr (e1, isval),
					PTGStmt (TrExpr (e2, isstmt)),
					PTGNULL));
		else {
			retrievefirstSEQExpr(
				tailSEQExpr (tailSEQExpr (params)), e3);
			return (PTGIfStmt (
					TrExpr (e1, isval),
					PTGStmt (TrExpr (e2, isstmt)),
					PTGStmt (TrExpr (e3, isstmt))));
		}
	} else	if (context == isval) {
		if (CheckArgNr (c, 3, 3)) return (PTGNULL);
		retrievefirstSEQExpr(params, e1);
		retrievefirstSEQExpr(tailSEQExpr (params), e2);
		retrievefirstSEQExpr (tailSEQExpr (tailSEQExpr (params)), e3);
		return (PTGIfExpr (
				TrExpr (e1, isval),
				TrExpr (e2, isval),
				TrExpr (e3, isval)));
	} else { /* context == isvoid */
		if (CheckArgNr (c, 2, 3)) return (PTGNULL);
		retrievefirstSEQExpr(params, e1);
		retrievefirstSEQExpr(tailSEQExpr (params), e2);
		if (emptySEQExpr (tailSEQExpr (tailSEQExpr (params))))
			return (PTGIfExpr (
					TrExpr (e1, isval),
					PTGToNoVal (TrExpr (e2, isvoid)),
					pppNoVal));
		else {
			retrievefirstSEQExpr(
				tailSEQExpr (tailSEQExpr (params)), e3);
			return (PTGIfExpr (
					TrExpr (e1, isval),
					PTGToNoVal (TrExpr (e2, isvoid)),
					PTGToNoVal (TrExpr (e3, isvoid))));
		}
	}
} else
if (strcmp (INITCYCLEFCT, nameOfCall (c)) == 0) {
	/* code producing expression */
	NoComputation = false;
	if (CheckArgNr (c, 1, 1)) return (PTGNULL);
	retrievefirstSEQExpr(params, e1);
	if (!InAssign) {
		coord.line = rowOfCall (c);
		coord.col = colOfCall (c);
		message (FATAL, "INITCYCLE must be in attribute computation", 
			0, &coord);
		return (PTGNULL);
	}
	IsInitCycle = true;
	return (TrExpr (e1, context));
} else
if (strcmp (LOOPFCT, nameOfCall (c)) == 0) {
	PTGNode condition, iter, label;

	/* code producing expression */
	NoComputation = false;
	if (CheckArgNr (c, 3, 3)) return (PTGNULL);
	coord.line = rowOfCall (c);
	coord.col = colOfCall (c);
	if (context == isval) {
		message (FATAL, "loop must be in VOID context", 0, &coord);
		return (PTGNULL);
	}

	retrievefirstSEQExpr(params, e1);
	condition = TrExpr (e1, isval);

	retrievefirstSEQExpr(tailSEQExpr (params), e2);
	retrievefirstSEQExpr(tailSEQExpr (tailSEQExpr (params)), e3);

	if (typeof (e2) == KAttracc) {
		SEQint l = currcycleattrs; int cycleat;
		/* an INITCYCLE forthe cycle attribute used here 
		   must have been seen in the current visit-section:*/
		while (!emptySEQint(l)) {
			retrievefirstSEQint (l, cycleat);
			if (cycleat == attridOfAttracc (ExprToAttracc (e2)))
				break;
			l = tailSEQint(l);
		}
		if (emptySEQint(l)) {
			coord.line = rowOfCall (c);
			coord.col = colOfCall (c);
			message (ERROR,
				"iteration involves attributes of upper context",
				0, &coord);
		}
		/* end of loop check */

		atdef = lookup_attrdef (attridOfAttracc (ExprToAttracc (e2)));
		label =	PTGLabName (PTGAsIs (nameOfAttrdef (atdef)),
				PTGNumb (symbnoOfAttracc (
						ExprToAttracc (e2))));
		if (IsVoidAttr (atdef)) {
			iter = TrExpr (e3, isstmt);
		} else	iter = PTGAssign (
				TrExpr (e2, isval), TrExpr (e3, isval));
		return (PTGLoop (condition, PTGStmt (iter), label));
	} else {
		message (FATAL, "2nd argument of loop must be an attribute", 
			0, &coord);
		return (PTGNULL);
	}
} else {
	/* call of user function; code producing expression */
	NoComputation = false;
	return (PTGCall (
		PTGAsIs (nameOfCall (c)), TrSeqExpr (params)));
}
}/*TrCall*/

PTGNode TrExpr (e, context)
	Expr	e;
	int	context;
{

switch (typeof (e)) {

case KLiteral:
{	char *str;
/* should not occur; is encapsulated in type call */
if (context == isstmt) return (PTGNULL);
str = strOfLiteral (ExprToLiteral (e));
return (PTGC_Str (str));
}

case KVal:
if (context == isstmt) return (PTGNULL);
return (PTGNumb (vOfVal (ExprToVal (e))));

case KName:
{	Name na;
na = ExprToName (e);
if (strcmp ("COORDREF", nOfName(na)) == 0) {
	CallHasTermAcc = true;
	return PTGCoordAccess();
} else if (strcmp ("LINE", nOfName(na)) == 0) {
	CallHasTermAcc = true;
	return PTGLineAccess();
} else if (strcmp ("COL", nOfName(na)) == 0) {
	CallHasTermAcc = true;
	return PTGColAccess();
}
/* may be a macro name that may stand for a code producing expression */
NoComputation = false;
return (PTGAsIs (nOfName(na)));
}

case KAttracc:
if (context == isstmt) return (PTGNULL);
if (context == isvoid) return (pppNoVal);
/* context == isval */
if (IsVoidAttr (lookup_attrdef (
		attridOfAttracc (ExprToAttracc (e))))) {
	coord.line = rowOfAttracc (ExprToAttracc (e));
	coord.col = colOfAttracc (ExprToAttracc (e));
	message (FATAL,
		"internal error: VOID attribute in value context", 0, &coord);
	return (PTGNULL);
}
return (TrAttracc (ExprToAttracc (e)));

case KCall:
return (TrCall (ExprToCall (e), context));

case KIncluding:
if (context == isstmt) return (PTGNULL);
if (context == isvoid) return (pppNoVal);
/* context == isval */
/* code producing expression */
NoComputation = false;
return (TrIncluding (ExprToIncluding (e)));

default: /* Chainacc or Constit should be removed by expand */
return (PTGNULL);
}
}/*TrExpr*/

PTGNode TrSeqExpr (s)
	SEQExpr s;
{	SEQExpr es;
	Expr	e;
	PTGNode res;

if (emptySEQExpr (s)) return (PTGNULL);

retrievefirstSEQExpr(s, e);
res = TrExpr (e, isval);

foreachinSEQExpr (tailSEQExpr (s), es, e)
	res = PTGSeqCom (res, TrExpr (e, isval));

return (res);
}/*TrSeqExpr*/

PTGNode TrSeqStmt (s)
	SEQExpr s;
{	SEQExpr es;
	Expr	e;
	PTGNode res;

res = PTGNULL;

foreachinSEQExpr (s, es, e)
	res = PTGSeq (res, PTGStmt (TrExpr (e, isstmt)));

return (res);
}/*TrSeqExpr*/

PTGNode TrOrdSeq (params, context)
	SEQExpr	params;
	int	context;
{	Expr	e1;
	PTGNode	res;

retrievefirstSEQExpr(params, e1);
params = tailSEQExpr (params);

if (emptySEQExpr (params))	/* the only argument */
	return (TrExpr (e1, context));

res = TrExpr (e1, isvoid);	/* the first of several args */
retrievefirstSEQExpr(params, e1); /* the second argument */
params = tailSEQExpr (params);

while (!emptySEQExpr (params)) {	/* more than 2 args, */
					/* more after e1, */
					/* e1 has to be translated */
	res = PTGSeqCom (res, TrExpr (e1, isvoid));
	retrievefirstSEQExpr(params, e1);
	params = tailSEQExpr (params);
}
/* e1 is last arg */
if (context == isval)
	return (PTGParen (PTGSeqCom (res, TrExpr (e1, isval))));
else /* context == isvoid */
	return (PTGParen (PTGSeqCom (res,
			PTGSeqCom (TrExpr (e1, isvoid), pppNoVal))));
}/* TrOrdSeq */

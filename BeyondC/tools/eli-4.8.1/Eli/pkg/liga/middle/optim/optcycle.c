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
/* $Id: optcycle.c,v 4.1 1997/08/29 09:13:34 peter Exp peter $ */
static char rcs_id[] = "$Id: optcycle.c,v 4.1 1997/08/29 09:13:34 peter Exp peter $";

#include <string.h>
#include "global.h"
#include "LIGA.h"
#include "LIGAMacros.h"
#include "liga_func.h"
#include "ligaconsts.h"

#include "optcycle.h"

static SEQAttrrule lastinitcycle;
static SEQAttrrule lastloop;

#define NextSEQAttrrule(s) s->next

static
void FindCycleFct (ca, containedin)
	Call		ca;
	SEQAttrrule	containedin;
{	Expr		arg;
if (strcmp(nameOfCall (ca), ASSIGNFCT) == 0) {
	retrievefirstSEQExpr(tailSEQExpr(paramsOfCall(ca)), arg);
	if (typeof(arg) == KCall) {
		ca = ExprToCall (arg);
		FindCycleFct (ca, containedin);
	}
} else
if (strcmp(nameOfCall (ca), DEPFCT) == 0) {
	retrievefirstSEQExpr(paramsOfCall(ca), arg);
	if (typeof(arg) == KCall) {
		ca = ExprToCall (arg);
		FindCycleFct (ca, containedin);
	}
} else
if (strcmp(nameOfCall (ca), INITCYCLEFCT) == 0) {
	lastinitcycle = containedin;
} else
if (strcmp(nameOfCall (ca), LOOPFCT) == 0) {
	lastloop = containedin;
}
}/* FindCycleFct */

static
void AppendAttrToLoop (attr)
	Attracc	attr;
{	Call	ca;
	Attrrule	ar;
attr = CpAttracc (attr);
ca = MkCall (	VOIDFCT, 
		AppFrontSEQExpr (AttraccToExpr (attr), nullSEQExpr()), 
		rowOfAttracc (attr), colOfAttracc (attr));
ar = CallToAttrrule (ca);
NextSEQAttrrule (lastloop) =
	AppFrontSEQAttrrule (ar, NextSEQAttrrule (lastloop));
}/* AppendAttrToLoop */

static
void ChkSection (sectbegin)
	SEQAttrrule	sectbegin;
{	SEQAttrrule	xSEQAttrrule;
	Attrrule	attrrule;
	Call		ca;
	Expr		arg;
	Attracc		attr;

for (	xSEQAttrrule = sectbegin; 
	((xSEQAttrrule != nullSEQAttrrule()) && (xSEQAttrrule != lastinitcycle));
	xSEQAttrrule = NextSEQAttrrule (xSEQAttrrule)) {
	retrievefirstSEQAttrrule (xSEQAttrrule, attrrule);

	if (typeof(attrrule) == KCall) {
		ca = AttrruleToCall (attrrule);
		if (strcmp(nameOfCall (ca), ASSIGNFCT) == 0) {
			retrievefirstSEQExpr(paramsOfCall(ca), arg);
			if (typeof(arg) == KAttracc) {
				attr = ExprToAttracc (arg);
				AppendAttrToLoop (attr);
			}
		}
	}
}/* for to lastinitcycle */
}/* ChkSection */

void ExtendLifeOverCycles (root)
	AttrEval root;
{	SEQAttribution	xSEQAttribution;
	Attribution	thisvs;
	SEQAttrrule	xSEQAttrrule;
	Attrrule	attrrule;
	Visit		vs;
	Call		ca;
	SEQAttrrule	sectbegin;

foreachinSEQAttribution(attrrulesOfAttrEval (root), xSEQAttribution, thisvs) {
	sectbegin = attrrulesOfAttribution (thisvs);
	lastinitcycle = nullSEQAttrrule(); lastloop = nullSEQAttrrule();
	foreachinSEQAttrrule(attrrulesOfAttribution (thisvs), xSEQAttrrule, attrrule) {
	switch (typeof(attrrule)) {
	case KVisit:
		vs = AttrruleToVisit (attrrule);
		if (symbnoOfVisit (vs) == 0) {/* end of section */
			if ((lastinitcycle != nullSEQAttrrule()) &&
				(lastloop != nullSEQAttrrule()))
				ChkSection (sectbegin);
			sectbegin = NextSEQAttrrule (xSEQAttrrule);
			lastinitcycle = nullSEQAttrrule(); lastloop = nullSEQAttrrule();
		}
		break;
	case KCall:
		ca = AttrruleToCall (attrrule);
		FindCycleFct (ca, xSEQAttrrule);
		break;
	default:;
	}/* switch (typeof(attrrule)) */
	}/* foreachinSEQAttrrule */
}/* foreachinSEQAttribution */
}/* ExtendLifeInCycles */


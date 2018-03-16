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
/* $Id: attr.c,v 4.3 2001/11/05 14:51:03 cogito Exp peter $ */

/* LIGA backend module		*/
/* attribute access		*/
#include <string.h>

#include "global.h"
/*
#include "LIGA.h"
#include "LIGAMacros.h"
*/
#include "lookup_idl.h"
#include "ligaconsts.h"
#include "ptg_gen.h"

#include "attr.h"

#define GENTREEATTR     "GENTREE"
#define IsGenAttr(aname) (strcmp (nameOfAttrdef (aname), GENTREEATTR) == 0)

PTGNode TrAttracc (a)
	Attracc	a;
{	Attrdef	adef;
	PTGNode attrname;

adef = lookup_attrdef (attridOfAttracc (a));
if (IsGenAttr (adef))
/* predefined attribute represents the tree itself */
	if (symbnoOfAttracc (a) == 0)
		return (PTGAsIs ("_currn"));
	else	return (PTGSelectPtr (
				PTGAsIs ("_currn"),
				PTGDescName (PTGNumb (symbnoOfAttracc (a)))));
else
/* normal attribute */
switch (storeOfAttrdef (adef)) {
case STORGLVA:
	return (PTGVarAttrName (PTGAsIs (globnameOfAttrdef (adef))));
case STORGLST:
/*	if (prodidOfAttrdef (adef) == DIDNON)
*/
	if (1)
		attrname = PTGAsIs (nameOfAttrdef (adef));
	else	attrname = PTGRuleAttrName (
				PTGNumb (prodidOfAttrdef (adef)),
				PTGAsIs (nameOfAttrdef (adef)));

	if (symbnoOfAttracc (a) == 0)
		return (PTGContent (PTGLhsStackAttrName (attrname)));
	else
		return (PTGRhsStackAttrName (
				PTGNumb (symbnoOfAttracc (a)),
				attrname));
case STORTRAT:
	if (symbnoOfAttracc (a) == 0)
		return (PTGSelectPtr(
			PTGAsIs ("_currn"),
			PTGTreeAttrName (PTGAsIs (nameOfAttrdef (adef)))));
	else
		return (PTGSelectPtr (
			PTGAsIs ("_currn"),
			PTGSelectPtr (
				PTGDescName (PTGNumb (symbnoOfAttracc (a))),
				PTGTreeAttrName (
					PTGAsIs (nameOfAttrdef (adef))))));
default:
	return (PTGNULL);
}
}/*TrAttracc*/


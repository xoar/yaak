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
/* $Id: attrdecl.h,v 4.3 2001/11/05 14:51:03 cogito Exp $ */

/* LIGA backend module		*/
/* attribute declarations	*/
/* U. Kastens, 5. 11. 91	*/

extern int IsVoidAttr (/*
	Attrdef	ad;
*/);

extern int HasTreeAttrs (/*
	SEQAttrdef      aseq;
*/);

extern void TrNodeTypes (/*
	SEQDef alldefs;
*/);

extern PTGNode TreeAttrDecls (/*
	SEQAttrdef	aseq;
*/);

extern void VarAttrDecls (/*
	SEQAttrdef	aseq;
*/);

extern PTGNode RuleStackAttrDecls (/*
        SEQAttrdef      aseq;
        int             ruleid, visit;
*/);

extern PTGNode StackAttrDecls (/*
	SEQAttrdef	aseq;
	int		visit, sympos;
*/);

extern PTGNode StackAttrParamSpecs (/*
	SEQAttrdef	aseq;
	int		visit;
*/);

extern PTGNode StackAttrParamProtos (/*
	SEQAttrdef	aseq;
	int		visit;
*/);

extern PTGNode StackAttrNames (/*
	SEQAttrdef	aseq;
	int		visit;
*/);

extern PTGNode StackArgs (/*
	SEQAttrdef	aseq;
	int		visit, sympos;
*/);

extern PTGNode StackProtos (/*
	SEQAttrdef	aseq;
	int		visit, sympos;
*/);


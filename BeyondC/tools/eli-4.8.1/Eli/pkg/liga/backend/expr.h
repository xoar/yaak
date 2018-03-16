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
/* $Id: expr.h,v 4.1 1997/08/29 07:54:24 peter Exp $ */

/* LIGA backend module		*/
/* expression translation	*/
/* U. Kastens, 5. 11. 91	*/

#define isstmt	0
#define isval	1
#define isvoid	2

extern PTGNode pppNoVal;

/* NewSection is called from backvisit.h to indicate
   the start of a new visit-section;
   used for loop check.
*/
extern void NewSection ();

extern PTGNode TrCall (/*
	Call c;
	int     context;
*/);

extern PTGNode TrExpr (/*
	Expr e;
	int	context;
*/);

extern PTGNode TrSeqExpr (/*
	SEQExpr s;
*/);

extern PTGNode TrSeqStmt (/*
	SEQExpr s;
*/);

extern PTGNode TrOrdSeq (/*
	SEQExpr params;
	int	context;
*/);

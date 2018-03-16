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
/* $Id: backvisit.h,v 4.3 1997/08/29 07:54:24 peter Exp $ */

/* LIGA backend module		*/
/* visit sequence procedures	*/
/* U. Kastens, 19. 7. 91	*/

/*number of visit procedures for split of file visiprocs.c: */
#define MAXVSFILE 500

#include "ptg_gen.h"
#include "LIGA.h"

/* switches monitoring info on; is set by command line option: */
extern int GenMonitorSwitch;

/* pass info on removed void assigns from expr.c to backvisit.c: */
extern int MonVoidAssign;
extern int MonVoidSymbNo;
extern char *MonVoidAttr;


extern Prod currproddef;
extern PTGNode globvardecls, globvarextern;

/* The following variables are set in expr.c */
/* CallHasTermAcc indicates a terminal access in current computation */
extern int CallHasTermAcc; 

/* LhsAttrCode indicates a value assignment;
   LhsAttrSymbNo and Attrdef are then also set
*/
extern PTGNode LhsAttrCode;
extern int LhsAttrSymbNo;
extern Attrdef LhsAttrdef;

extern Symb SymbDefInRhs (/*
        SEQEntity       rhs;
        int             pos;
*/);

extern void TrAttrEval (/*
        AttrEval        ae;
*/);

extern void TrAttribution (/*
	Attribution	a;
	PTGNode *pprocs, *pheader;
*/);

extern SEQAttrrule TrVisitSection (/*
	SEQAttrrule	arules;
	PTGNode		* pdecls, * pstmts;
	SEQEntity	rhs;
*/);

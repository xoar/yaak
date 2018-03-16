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
/* $Id: visitcmp.c,v 4.3 2001/11/05 14:51:03 cogito Exp $ */

#include "ptg_gen.h"
#include "bool.h"
#include "visitcmp.h"

int NoComputation;
	/* Indicates that current visit procedure has no computations.
	   Is set true by InitVisitCmp and CompareVisits
	   May be set false by expr.c or backvisit.c
	*/

#define MAXPROCCMP	20
	/* number of reusable visit procedures, must be > 1 */
#define MAXVSCMP	4
	/* number of decendent visits in a reusable visit procedure plus 1 */
	/* must be > 0 */
	/* these constants are no limitation for processing LIDO */

static int	vsdescno [MAXPROCCMP][MAXVSCMP],
		vsordno  [MAXPROCCMP][MAXVSCMP];
static PTGNode	vsprocname [MAXPROCCMP];

static int top, topvs;

void InitVisitCmp (procs, hdrs)
	PTGNode *procs, *hdrs;
{
/* initialize with totally empty visit procedure: */
vsdescno[0][0] = 0; vsordno[0][0] = 0;
vsprocname[0] = PTGAsIs ("_VS0Empty");
(*procs) = PTGSeq (*procs, PTGPredefVSProc (vsprocname[0], PTGNULL));
(*hdrs) = PTGSeq (*hdrs, PTGPredefVSHeader (vsprocname[0]));
top = 1; topvs = 0;
NoComputation = true;
}/* InitVisitCmp */

void EnterVisitCmp (desc, ord)
        int desc, ord;
{
if (NoComputation && (topvs < MAXVSCMP)) {
	vsdescno[top][topvs] = desc;
	vsordno[top][topvs++] = (desc == 0 ? 0 : ord);
}
}/* EnterVisitCmp */

PTGNode CompareVisits (name)
        PTGNode name;
{
if (	NoComputation &&
	(topvs > 0) && (topvs <= MAXVSCMP) &&
	(vsdescno[top][topvs-1] == 0) && (vsordno[top][topvs-1] == 0)) {
		/* look for a visit procedure equal to the top one: */
		int i,j;
		for (i=0; i<top; i++) {
			j = 0;
			while (	(vsdescno[top][j] == vsdescno[i][j]) &&
				(vsordno[top][j] == vsordno[i][j]))
				if (j == (topvs-1)) {
					topvs = 0;
					return (PTGDefineVS (name,
							vsprocname[i]));
				} else j++;
		}/* end for */
		/* top visit procedure is unique */
		if (top < (MAXPROCCMP-1))
			vsprocname[top++] = name; /* keep it */
}
/* no visit procedure equal to the top one found */
topvs = 0;
NoComputation = true;
return (PTGNULL);
}/* CompareVisits */

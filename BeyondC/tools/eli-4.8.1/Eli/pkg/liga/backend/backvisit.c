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
/* $Id: backvisit.c,v 4.10 2001/11/05 14:51:03 cogito Exp $ */

/* LIGA backend module		*/
/* visit sequence procedures	*/
/* U. Kastens, 30. 1. 97	*/

#include <string.h>
#include "global.h"
#include "ligaconsts.h"
#include "lookup_idl.h"
#include "ptg_gen.h"
#include "LIGAMacros.h"

#include "backvisit.h"
#include "attrdecl.h"
#include "expr.h"
#include "incl.h"
#include "bool.h"
#include "bottomup.h"
#include "visitcmp.h"

/* switches monitoring info on; is set by command line option: */
int GenMonitorSwitch = 0;

/* pass info on removed void assigns from expr.c to backvisit.c: */
int MonVoidAssign;
int MonVoidSymbNo;
char *MonVoidAttr;

/* Function that eliminates the marker from rule attr names: */
#define RAMARKER "_RuleAttr_"

static char* StripRuleAttrMark (nam) char* nam;
{ char *startOfMark = strstr(nam, RAMARKER);
  if (startOfMark)
  { /* remove the RAMARKER substring from a rule attribute's name */ 
    char *plainname = malloc (strlen(nam));
    char *p1, *p2;
    for (p1=nam, p2=plainname; p1 != startOfMark; p1++, p2++)
      *p2 = *p1;
    *p2 = 0;
    return plainname;
  } else return nam;
}

#define IsGenAttr(aname) (strcmp (nameOfAttrdef (aname), GENTREEATTR) == 0)

char *GetBaseName (n)
        char    *n;
{return (*n == '$' ? n+1 : n);
}/*GetBaseName*/

Def tmpDef;
Prod currproddef;
int globvsproccnt = 0;
PTGNode globvardecls = PTGNULL, globvarextern = PTGNULL;

PTGNode TermAccs = PTGNULL;

void TrAttrEval (ae)
	AttrEval	ae;
{	SEQDef		defs;
	Def		def;
	SEQAttribution	s;
	Attribution	a;
	PTGNode		procs, header;
	char		procfilename[20], filenum[4];
	int		filecnt = 1;

/* generate node.h: */
TrNodeTypes (defseqOfAttrEval (ae));

/* generate visitprocs.[ch]: */
pppNoVal = PTGNoVal ();

TrInclVars (ae);

foreachinSEQDef (defseqOfAttrEval (ae), defs, def)
	if (typeof (def) == KSymb)
		VarAttrDecls (attrsOfSymb (DefToSymb (def)));

procs = PTGSeq (PTGVisitProcFileHead (), globvardecls);
procs = PTGSeq (procs, PTGRootProc(
		BottomUpVisits ? PTGNULL : PTGRootVisit()));

header = PTGNULL;

InitVisitCmp (&procs, &header);

strcpy (procfilename, "visitprocs.c");

foreachinSEQAttribution (attrrulesOfAttrEval (ae), s, a) {
	TrAttribution (a, &procs, &header);
	if (globvsproccnt > MAXVSFILE) {
		PTGOutFile (procfilename, PTGFile (procs) );
		strcpy (procfilename, "visitprocs");
		sprintf (filenum, "%d", filecnt++);
		strcat (procfilename, filenum);
		strcat (procfilename, ".c");
		procs = PTGSeq (PTGVisitProcFileHead (), globvarextern);
		globvsproccnt = 0;
	}
}

if (globvsproccnt>0) 
	PTGOutFile (procfilename, PTGFile (procs) );

PTGOutFile ("visitprocs.h", PTGVisitHeader (header) );
PTGOutFile ("treeact.h", PTGFile (TermAccs));
}/* TrAttrEval */

static bool lhshastreeattrs;

void TrAttribution (a, pprocs, pheader)
	Attribution	a;
	PTGNode *pprocs, *pheader;
{	PTGNode		decls, stmts, epilog, stackattrs, sameproc, procname,
	                specs, protos, typename;
	Prod		proddef;
	Symb		lhs;
	SEQEntity	rhs;
	SEQAttrrule	arules;
	int		sectno;
	char		*prodname;

tmpDef = lookup_def (prodidOfAttribution (a));
proddef = DefToProd (tmpDef);
currproddef = proddef;
prodname = GetBaseName (dnameOfProd (proddef));
rhs = rhsOfProd (proddef);
tmpDef = lookup_def (lhsOfProd (proddef));
lhs = DefToSymb (tmpDef);

lhshastreeattrs = HasTreeAttrs (attrsOfSymb (lhs));

TermAccs = PTGSeq (TermAccs, PTGTreeActHead (prodname));

sectno = 1;
arules = attrrulesOfAttribution (a);

while (arules) {
	decls = PTGNULL;
	stmts = PTGNULL;
	epilog = PTGNULL;

	TrInclSect (lhs, sectno, &decls, &stmts, &epilog);
	arules = TrVisitSection (arules, &decls, &stmts, rhs);

	stackattrs = StackAttrNames (attrsOfSymb (lhs), sectno);
	if (stackattrs != PTGNULL) NoComputation = false;

	procname = PTGVisitProcName (PTGNumb (sectno), PTGAsIs (prodname));
	sameproc = CompareVisits (procname);
	if (sameproc != PTGNULL)
		(*pheader) = PTGSeq (*pheader, sameproc);
	else {
		specs = StackAttrParamSpecs(attrsOfSymb(lhs), sectno);
		protos = StackAttrParamProtos(attrsOfSymb(lhs), sectno);

		typename = PTGProdPtrTypeName (PTGAsIs (prodname));
		(*pheader) = PTGSeq (*pheader,
			PTGVisitProcHeader (procname, typename, protos));
		(*pprocs) = PTGSeq (*pprocs,
			PTGVisitProcHead (
				procname, 
				stackattrs,
				typename,
				specs,
				decls, 
				stmts, 
				epilog, 
				protos));
	}
	sectno++;
}
globvsproccnt += (sectno-1);
}/*TrAttribution*/


Symb SymbDefInRhs (rhs, pos)
	SEQEntity	rhs;
	int		pos;
{	Entity		ent;
	bool		search = true;

while (search) {					/* not EBNF */
	retrievefirstSEQEntity (rhs, ent);
	if (typeof (ent) == KSymbol)
		if (--pos == 0) search = false;
	rhs = tailSEQEntity (rhs);
}
tmpDef = lookup_def (didOfSymbol (EntityToSymbol (ent)));
return (DefToSymb (tmpDef));
}/*SymbDefInRhs*/

PTGNode CollectStackDecls (rhs, sectstart)
	SEQEntity	rhs;
	SEQAttrrule	sectstart;
{	int		desccnt = 0;
	SEQEntity	rhstravel;
	Entity		ent;
	SEQAttrrule	artravel;
	Attrrule	ar;
	PTGNode		res = PTGNULL;
	Symb		sydef;

/* count descendents: */
foreachinSEQEntity (rhs, rhstravel, ent)
	if (typeof (ent) == KSymbol) desccnt++;

while (desccnt > 0) { /* for all descendents: */
	foreachinSEQAttrrule (sectstart, artravel, ar) {
		if ((typeof (ar) == KVisit) && 
		    (symbnoOfVisit (AttrruleToVisit (ar)) == desccnt)) {
			/* there follows a visit to this descendent;
			   declare its stack attributes: */
			sydef = SymbDefInRhs (rhs, desccnt);
			res = PTGSeq (res,
				StackAttrDecls (
					attrsOfSymb (sydef),
					ordOfVisit (AttrruleToVisit (ar)),
					desccnt));
			break; /* to next desccnt */
		}
	}
	desccnt--;
}
return (res);
}/* CollectStackDecls */

/* The following variables are set in expr.c */
/* CallHasTermAcc indicates a terminal access in current computation */
int CallHasTermAcc;

/* LhsAttrCode indicates a value assignment;
   LhsAttrSymbNo and Attrdef are then also set
*/
PTGNode LhsAttrCode;
int LhsAttrSymbNo;
Attrdef LhsAttrdef;


SEQAttrrule TrVisitSection (arules, pdecls, pstmts, rhs)
	SEQAttrrule	arules;
	PTGNode		* pdecls, * pstmts;
	SEQEntity	rhs;
{	Attrrule	arule;
	Visit		vs;
	Symb		sydef;
	int		descno, vsord;
	int		more;
	SEQAttrrule	sectstart;
	PTGNode		stackparms;
	PTGNode         stackprotos;
	PTGNode		stackdecls;

/* indicate start of a new visit-section for loop check in expr.h: */
NewSection ();

sectstart = arules;
more = (arules != NULL);

stackdecls = CollectStackDecls (rhs, arules);

while (more) 
{
	retrievefirstSEQAttrrule (arules, arule);
	if (typeof (arule) == KCall) 
	{ Call thiscall = AttrruleToCall(arule);
	  PTGNode callres;
	  CallHasTermAcc = 0;

	  /* translate a single computation: */

          /* The variable LhsAttrCode is set in TrCall
             to indicate that a non-VOID assign is translated.
             Then LhsAttrdef and LhsAttrSymbNo are also set.
          */
          LhsAttrCode = PTGNULL;
          MonVoidAssign = 0;
	  callres = TrCall (thiscall, isstmt);

	  if (CallHasTermAcc)
	     TermAccs = 
               PTGSeq (TermAccs, 
		       PTGDefineLine (callres));
	  else if (callres != PTGNULL)
	  { callres = 
              PTGSeq
                (PTGStmt (callres),
                 PTGSpecLineInfo (rowOfCall (thiscall)));

#ifdef MONITOR_GEN
            if (GenMonitorSwitch)
            { /* add monitoring information: */
              if (LhsAttrCode == PTGNULL)
              { /* a plain computation: */
	        if (MonVoidAssign)
		    /* has been a VOID attribute assign,
                       the attribute name is recovered: */
		  callres =
		    PTGSeq
		      (callres,
		       PTGMonVoidAssign
		         ((MonVoidSymbNo == 0 ?
			     PTGThisNode () :
			     PTGDescNode (MonVoidSymbNo)),
			  StripRuleAttrMark (MonVoidAttr),
			  rowOfCall (thiscall), colOfCall (thiscall)));
		else /* a normal plain computation: */
                  callres =
                    PTGSeq 
                      (callres, 
                       PTGMonPlainCompCall
                         (rowOfCall (thiscall), colOfCall (thiscall)));
	      } else
              { /* a value assign: */
                Def tpdef;
		tpdef = lookup_def (typeidOfAttrdef (LhsAttrdef));
		/* The following attributes are not considered: 
		   generated attributes for 
		   INCLUDING, CONSTITUENTS, and for coordinates
		   and terminals
		 */
                if (genOfAttrdef(LhsAttrdef) == GENCONST ||
		    genOfAttrdef(LhsAttrdef) == GENINCL ||
		    genOfAttrdef(LhsAttrdef) == GENTERM)
		    /* do nothing */;
		else if (IsGenAttr (LhsAttrdef))
		    /* generated tree insertion: */
   		    callres = PTGSeq (callres,
                     PTGMonTreeInsertion
                       (PTGDescNode (LhsAttrSymbNo),
                        LhsAttrSymbNo));
		else if (prodidOfAttrdef (LhsAttrdef) == 0)
		     /* symbol attribute computation: */
  		    callres = PTGSeq (callres,
                     PTGMonAttrCompCall
                       (dnameOfDef (tpdef),
                        (LhsAttrSymbNo == 0 ?
                           PTGThisNode () :
                           PTGDescNode (LhsAttrSymbNo)),
                        1, /* is a symbol attribute */
                        nameOfAttrdef (LhsAttrdef),
                        LhsAttrCode,
                        rowOfCall (thiscall),
                        colOfCall (thiscall)));
		   else /* rule attribute computation: */
  		    callres = PTGSeq (callres,
                     PTGMonAttrCompCall
                       (dnameOfDef (tpdef),
                        PTGThisNode (),
                        0, /* is a rule attribute */
                        StripRuleAttrMark (nameOfAttrdef (LhsAttrdef)),
                        LhsAttrCode,
                        rowOfCall (thiscall),
                        colOfCall (thiscall)));
	      }/* end of a value assign */
	    }/* end of monitoring information */
#endif
            (*pstmts) = PTGSeq (*pstmts, callres);
	  }

	} else if (typeof (arule) == KVisit) {
		vs = AttrruleToVisit (arule);
		descno = symbnoOfVisit (vs);
		vsord = ordOfVisit (vs);

		if (BottomUpVisits && (vsord == 1) && (descno > 0)) {
			/* omit this visit */
		} else
		if (descno) {	/* descendant visit */
			sydef = SymbDefInRhs (rhs, descno);

			stackparms = StackArgs (attrsOfSymb (sydef),
					vsord, descno);
			if (stackparms != PTGNULL) NoComputation = false;
			if (lhshastreeattrs) NoComputation = false;
			stackprotos = StackProtos(attrsOfSymb(sydef),
					vsord, descno);
			(*pstmts) =
			PTGSeq (*pstmts,
			  PTGDescVisit (
			    PTGNumb (vsord),
			    PTGDescName (PTGNumb (descno)),
			    stackparms,
			    stackprotos));

			EnterVisitCmp (descno, vsord);
		} else {	/* ancestor visit, section completed */
			EnterVisitCmp (descno, vsord);
			more = 0;
		}/* ancestor */
	}/* visit */

	arules = tailSEQAttrrule (arules);
}/* while */

if (!NoComputation) /* there is a computation or a stack argument in
			a visit call: */
	(*pdecls) = PTGSeq (*pdecls, stackdecls);

return (arules);
}/*TrVisitSection*/

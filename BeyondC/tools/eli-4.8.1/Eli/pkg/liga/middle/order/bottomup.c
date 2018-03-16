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
/* $Id: bottomup.c,v 4.12 1997/08/29 09:16:01 peter Exp $ */

#include "err.h"

#include "ligaconsts.h"
#include "reftab.h"
#include "initdp.h"
#include "printerr.h"
#include "depmod.h"
#include "option.h"
#include "do_order.h"
#include "LIGAMacros.h"
#include "liga_func.h"
#include "ordout.h"

#include "bottomup.h"

static char *BUAttrState = "direct";

/* Dependencies may be added for bottom-up or generated trees.
   They are classified to be induced dependencies.
   Done by depmod functions.
*/
static
void MarkBUAttr (aid) int aid;
{ Attrdef ad;
  char errmsgbuff[ERR_BUFF_LEN];

  ref_tab[aid].entry.attr.bottomup = 1;

  ad = ref_tab[aid].entry.attr.attr_def;
  sprintf(errmsgbuff,
	  "%s.%s is %s BOTTOMUP attribute\n",
          ref_tab[ref_tab[aid].entry.attr.symbdid]
		.entry.symb.symb_def->dname,
	  ad->name,
	  BUAttrState);
#ifndef GORTO
  fprintf(ProtocolFile, "%s", errmsgbuff);
#endif

  if (classOfAttrdef (ad) == ATCLINH)
  { if (typeidOfAttrdef (ad) != DIDVOID &&
	typeidOfAttrdef (ad) != DIDVOLI)
    { err_setpos (rowOfAttrdef (ad), colOfAttrdef (ad));
      err_print_error ("bottom up INH value computation");
      fprintf(ProtocolFile,
	      "*** ERROR *** bottom up INH value computation\n");
    }
  }
}

#define IsGenAttr(adef)	\
	(strcmp (nameOfAttrdef (adef), GENTREEATTR) == 0)

int NeedsCode (ca) Call ca;
/* returns true iff ex produces code in void context */
{ char *name = nameOfCall (ca);

  if (strcmp (ASSIGNFCT, name) == 0)
  { Expr lex, rex; Attracc lattr; Attrdef ad;
    retrievefirstSEQExpr (paramsOfCall (ca), lex);
    retrievefirstSEQExpr (tailSEQExpr (paramsOfCall (ca)), rex);
    lattr = ExprToAttracc (lex);
    ad = ref_tab[attridOfAttracc (lattr)].entry.attr.attr_def;

    if (typeidOfAttrdef (ad) != DIDVOID &&
	typeidOfAttrdef (ad) != DIDVOLI)
    {
	if (IsGenAttr (ad) && typeof (rex) == KName &&
	    strcmp (nOfName (ExprToName (rex)), "VOID") == 0)
             return 0; /* dummy gentree attr computation */
	else return 1; /* value assignment needs code */
    }

    /* assign to VOID attribute: */
    if (typeof (rex) == KCall)
       return NeedsCode (ExprToCall (rex));
    else
    if (typeof (rex) == KName)
        return 1; /* may be cpp identifier */
    else
	return 0; /* attribute or literal does not need code */
  }/* end ASSIGNFCT */

  if ((strcmp (STRINGFCT, name) == 0) ||
      (strcmp (CHARFCT, name) == 0) ||
      (strcmp (FLOATFCT, name) == 0))
	return 0; /* unused literal */

  if ((strcmp (DEPFCT, name) == 0) ||
      (strcmp (VOIDFCT, name) == 0) ||
      (strcmp (IDFCT, name) == 0) ||
      (strcmp (BOTTOMUPFCT, name) == 0) ||
      (strcmp ("IDENTICAL", name) == 0))
  { Expr param;
    /* check first parameter: */
    retrievefirstSEQExpr (paramsOfCall (ca), param);

    if (typeof (param) == KCall)
       return NeedsCode (ExprToCall (param));
    else
    if (typeof (param) == KName)
         return 1; /* may be cpp identifier */
    else return 0; 
  }

  return 1; /* other function call needs code */
}/* NeedsCode */

void ChkBUComp (ca) Call ca;
/* on entry: ca is an ASSIGNFCT to be executed BOTTOMUP */
{ Expr lex, rex;
  int aid; Attrdef ad;

  retrievefirstSEQExpr (tailSEQExpr (paramsOfCall (ca)), rex);
  if (typeof (rex) != KCall) 
	return;
  if (strcmp (BOTTOMUPFCT, nameOfCall (ExprToCall (rex))) != 0)
	return;

  TREE_BOTTOM_UP = TRUE;

  retrievefirstSEQExpr (paramsOfCall (ca), lex);
  aid = attridOfAttracc (ExprToAttracc (lex));
  MarkBUAttr (aid);

  ad = ref_tab[aid].entry.attr.attr_def;
  if (classOfAttrdef (ad) == ATCLINH)
  { if (NeedsCode (ca))
    { err_setpos (rowOfCall (ca), colOfCall (ca));
      err_print_error ("bottom up INH code computation");
      fprintf(ProtocolFile, 
	      "*** ERROR *** bottom up INH code computation");
    }
  }
}/* ChkBUComp */

/************************************************************************
     int lidoposition(rulepos, pid)                                  
     returns the lido index of the rulepos'th symbol in rule pid     
     returns NONE, if this symbol occurs only once                   
     lidoposition is used for the generation of error messages       
     like "Computation of X[2].a is missing ..." or                  
     "Computation of X[0].b occurs multiply ..."                     
 ***********************************************************************/

int lidoposition(rulepos, pid)
int rulepos, pid;
{ int i = 0;
  SLNODE *symbolinfo=ref_tab[pid].entry.prod.hdright;  
  SLNODE *symbol=symbolinfo;  
  int occ_count = 0;
  int occ_total = 0; 

  /* compute symbol information for the rulepos'th symbol */
  for (;i<rulepos;i++) 
    symbolinfo = symbolinfo->right; 

  /* compute number of occurrences */
  while (symbol != NULL) 
  { if (symbol->sid == symbolinfo->sid) 
      occ_total++;                /* one more occurrence */
    if (symbol == symbolinfo) 
      occ_count = occ_total;      /* remember count for the symbol in */
				  /* question */
    symbol = symbol->right;
  }

  /* compute result */
  if (occ_total == 1) 
      return NONE;             /* lido index not necessary in this */
  			       /* case */
  else 
     return occ_count;         /* occ_total >1 */
}

static
void DepMessage (pid, tosid, tosno, toaid, fromsid, fromsno, fromaid, msg)
  int pid, tosid, tosno, toaid, fromsid, fromsno, fromaid;
  char *msg;
{ char errmsgbuff[ERR_BUFF_LEN];
  char toindex[16], fromindex[16];
  int topos = lidoposition(tosno,pid);
  int frompos = lidoposition(fromsno,pid);
  PRODENTRY *prod = &ref_tab[pid].entry.prod;
  SYMBENTRY *tosymb = &ref_tab[tosid].entry.symb;
  SYMBENTRY *fromsymb = &ref_tab[fromsid].entry.symb;

  if (topos == NONE)
       toindex[0] = '\0';
  else sprintf(toindex,"[%d]",topos);
  if (frompos == NONE)
       fromindex[0] = '\0';
  else sprintf(fromindex,"[%d]",frompos);

  err_setpos (prod->prod_def->row, prod->prod_def->col);
  sprintf
    (errmsgbuff,
     "in RULE %s: dependence %s%s.%s <- %s%s.%s %s",
     prod->prod_def->dname,
     tosymb->symb_def->dname,
     toindex,
     ref_tab[toaid].entry.attr.attr_def->name,
     fromsymb->symb_def->dname,
     fromindex,
     ref_tab[fromaid].entry.attr.attr_def->name,
     msg
    );
     err_print_error (errmsgbuff);
     fprintf(ProtocolFile, 
	     "*** ERROR *** %s\n",errmsgbuff);
}

void InduceBUAttrs ()
{ int pid, changed;

  if (!TREE_BOTTOM_UP) return;
  BUAttrState = "induced";
/* The property of an attribute to be bottomup is propagated
   backward along dependencies.
   Let (fromsno,fromaid) -> (tosno,toaid) be in a rule graph, 
   and toaid be bottomup.
   Then fromaid is also marked bottomup if one of the following
   holds
	tosno = 0, toaid is SYNT, fromsno = 0
		the computation of (tosno,toaid) will be executed
		after all subtrees are made and possibly visited
		several times
		only its preconditions on lhs attrs and
		hence to left uncles have to be solved
	tosno > 0, toaid is INH, fromsno = 0, fromaid is INH
	tosno > 0, toaid is INH, 0 < fromsno < tosno
		(tosno,toaid) is a virtual computation
		its preconditions to the left and to left uncles
		have to be solved
*/
  do
  {
    changed = 0;
    for (pid = min_entry; pid <= max_entry; pid++)
    if (ref_tab[pid].etag == PROD)
    { PRODENTRY *prod = &ref_tab[pid].entry.prod;
      SLNODE *toslnptr; int tosno = -1;
      for (toslnptr = prod->hdright;
	   toslnptr != NULL; toslnptr = toslnptr->right)
      { SYMBENTRY *tosymb = &ref_tab[toslnptr->sid].entry.symb;
        int tosymatno;
        tosno++;
        for (tosymatno = 0; tosymatno < tosymb->attr_num; tosymatno++)
	{ int toaid = lookup_attr(toslnptr->sid, tosymatno);
          if (ref_tab[toaid].entry.attr.bottomup)
	  { SLNODE *fromslnptr; int fromsno = -1;
            for (fromslnptr = prod->hdright;
		 fromslnptr != NULL; fromslnptr = fromslnptr->right)
            { SYMBENTRY *fromsymb = &ref_tab[fromslnptr->sid].entry.symb;
              int fromsymatno;
	      fromsno++;
              for (fromsymatno = 0; fromsymatno < fromsymb->attr_num;
		   fromsymatno++)
	      { int fromaid = lookup_attr(fromslnptr->sid, fromsymatno);
	        int fromclass = ref_tab[fromaid].entry.attr.attr_def->class;
	        int toclass = ref_tab[toaid].entry.attr.attr_def->class;

		if (((tosno==0 && toclass==ATCLSYNT &&
		      fromsno==0
		     ) ||
		     (tosno>0 && toclass==ATCLINH &&
		      ((fromsno==0 && fromclass==ATCLINH
		       ) ||
		       (0<fromsno && fromsno<tosno)
		      )
		     )
		    ) &&
		    !(ref_tab[fromaid].entry.attr.bottomup) &&
		    DPDependson 
                      (pid, toslnptr, tosymatno, fromslnptr, fromsymatno))
                { MarkBUAttr (fromaid);
		  changed = 1;
		}
	      }
	    }
	  }
	}
      }
    }
  } while (changed);
#ifndef GORTO
  fprintf(ProtocolFile,"\n");
#endif

/* insert dependences
   0<i: (i, INH BU) -> (i, SYNT)
   0<i<j: (i, BU) -> (j, any)
   complain if opposite dependence exists
   note: to -> from in the code below, because above code is reused
*/
    for (pid = min_entry; pid <= max_entry; pid++)
    if (ref_tab[pid].etag == PROD)
    { PRODENTRY *prod = &ref_tab[pid].entry.prod;
      SLNODE *toslnptr; int tosno = 0;
      for (toslnptr = prod->hdright->right;
	   toslnptr != NULL; toslnptr = toslnptr->right)
      { SYMBENTRY *tosymb = &ref_tab[toslnptr->sid].entry.symb;
        int tosymatno;
        tosno++; /* = 1, 2, ... */
        for (tosymatno = 0; tosymatno < tosymb->attr_num; tosymatno++)
	{ int toaid = lookup_attr(toslnptr->sid, tosymatno);
          if (ref_tab[toaid].entry.attr.bottomup)
	  { SLNODE *fromslnptr; int fromsno = tosno-1;
            for (fromslnptr = toslnptr;
		 fromslnptr != NULL; fromslnptr = fromslnptr->right)
            { SYMBENTRY *fromsymb = &ref_tab[fromslnptr->sid].entry.symb;
              int fromsymatno, fromaid;
	      fromsno++; /* = tosno + 0, 1, 2, ... */
              for (fromsymatno = 0; fromsymatno < fromsymb->attr_num;
		   fromsymatno++)
	      { fromaid = lookup_attr(fromslnptr->sid, fromsymatno);
	        if (tosno < fromsno ||
	            (ref_tab[toaid].entry.attr.attr_def->class 
		        == ATCLINH &&
		     ref_tab[fromaid].entry.attr.attr_def->class 
		        == ATCLSYNT))
                { if (DPDependson 
                       (pid, 
			toslnptr, tosymatno, 
			fromslnptr, fromsymatno))
                    DepMessage (pid,
				toslnptr->sid, tosno, toaid, 
				fromslnptr->sid, fromsno, fromaid, 
				"is illegal for bottom-up"
			       );
		  else
		    DPSetDepend (pid,
				 fromslnptr, fromsymatno,
				 toslnptr, tosymatno,
				 0, /* non-direct dependency */
				 0
				);
		}
	      }
	    }
	  }
	}
      }
    }
}/* InduceBUAttrs */

/*======================================================
   Find productions that may not be created implicitly
   from above due to bottom-up computations.
*/

#if 0
/* deactivated; should be done by maptool */

/* The symbols that occur as a left brother in some production
   are computed once and cached in the list LeftBrothers:
   This check is deactivated; it is performed by the maptool now.
*/
static SEQint LeftBrothers;
static int brothersdone = 0;

static
int HasRightBrother (sid) int sid;
{ int proddid;

  if (!brothersdone)
  { SLNODE *rhs;
    /* check all rhs occurrences for a right brother: */
    for (proddid = min_entry; proddid <= max_entry; proddid++)
      if (ref_tab[proddid].etag == PROD)
         for (rhs = ref_tab[proddid].entry.prod.hdright->right;
              rhs; rhs = rhs->right)
         if (rhs->right != NULL && !(inSEQint (LeftBrothers, rhs->sid)))
            appendfrontSEQint (LeftBrothers, rhs->sid);
    brothersdone = 1;
  }

  return (inSEQint (LeftBrothers, sid));
}
#endif

static int hasBUcode, hasearlyvisit;

static
void ChkUptoLeave (pid) int pid;
{ VSPTR visitseq = ref_tab[pid].entry.prod.visitseq;
  hasBUcode = 0;
  hasearlyvisit = 0;
  
  for (; visitseq; visitseq = visitseq->next)
    switch (visitseq->vscls)
    { case VSVISIT:
          if (visitseq->vsinfo.visit.vssno == 0)
	     return;
	  if (visitseq->vsinfo.visit.vsord > 1)
	     hasearlyvisit = 1; /* early down visit */
	  break;
      case VSASSIG:
          if (NeedsCode (visitseq->vsinfo.assig.idldef))
	     hasBUcode = 1;
	  break;
      case VSCOND:
          if (NeedsCode (visitseq->vsinfo.cond.idldef))
             hasBUcode = 1;
          /* a plain computation should not occur in BU phase */
	  break;
    }
  return;
}

void BUChkProds ()
/* Print names of productions that may not be created implicitly
   from above due to bottom-up computations.
*/
{ int proddid;

  for (proddid = min_entry; proddid <= max_entry; proddid++)
  if (ref_tab[proddid].etag == PROD)
  { 
    ChkUptoLeave (proddid);
    if ((hasBUcode || hasearlyvisit) &&
        /* not root production: */
        !(ref_tab[LhsDidOfProd(proddid)].entry.symb.hddown->down == NULL))
    { 
#ifndef GORTO
      fprintf (ProtocolFile,
               "RULE %s: ",
	       dnameOfProd (ref_tab[proddid].entry.prod.prod_def));
      print_syntax (proddid);
      fprintf (ProtocolFile,
	       "%s %s\n\n",
               (hasBUcode ? "has early code;" : ""),
               (hasearlyvisit? "has early subtree visit;" : ""));
#endif
      fprintf (BuProdFile, "%s\n",
               dnameOfProd (ref_tab[proddid].entry.prod.prod_def));
    }
  }
}

/***************************************************************
	Generated Trees

Insertion of a generated tree is marked in lido by $ X
on the right-hand side of a rule. Such a symbol X, the
root of a generated tree, has the predefined attribute
GENTREEATTR. GENTREEATTR depends on the computation
of the tree to be inserted.

All other INH attributes of such a symbol X are made dependent
on GENTREEATTR, in order to ensure that none of them
can be used before the computed tree is inserted into
the whole tree.
This is done by GenTreeDeps. It is called after the
induce phase in order to better specify the source of
conflicts.

Bottom-up computations may not be scheduled in any part
of a generated tree.
Hence, the set of symbols that may occur in a generated
tree is computed transitively from their roots.
It is checked if any of these symbols has a bottomup attribute.
***************************************************************/

static
bool HasGenAttr (sydef) Symb sydef;
{
   SEQAttrdef ads;
   Attrdef ad;
   foreachinSEQAttrdef(attrsOfSymb(sydef), ads, ad)
      if (IsGenAttr(ad))
      return (TRUE);
   return (FALSE);
}/* HasGenAttr */

static
void EnterGenDeps (sydef) Symb sydef;
{  SEQAttrdef ads; Attrdef ad;
   int sid, genattrpos, attrpos;
   sid = didOfSymb(sydef);
   
   foreachinSEQAttrdef(attrsOfSymb(sydef), ads, ad)
      if (IsGenAttr(ad))
      {  genattrpos = GetSymAttrPos (didOfAttrdef (ad));
	 break;
      }

   foreachinSEQAttrdef(attrsOfSymb(sydef), ads, ad)
      if (!IsGenAttr(ad))
      {  attrpos = GetSymAttrPos (didOfAttrdef (ad));
         if (DSDependson (sid, genattrpos, attrpos))
	 { char errmsgbuff[ERR_BUFF_LEN];
	   err_setpos (rowOfSymb(sydef), colOfSymb(sydef));
	   sprintf (errmsgbuff,
		    "creation of generated tree may not depend on %s.%s",
		    dnameOfSymb(sydef),
		    nameOfAttrdef (ad)
		   );
	   err_print_error (errmsgbuff);
	   fprintf (ProtocolFile,
		    "*** ERROR *** %s\n",errmsgbuff);
	 } else
	     DSSetDepend (sid, attrpos, genattrpos);
      }
}/* EnterGenDeps */

static SEQint GenTreeRoots, GenTreeSymbs;

void GenTreeDeps (ae) AttrEval ae;
{
   SEQDef defs; Def d;
   SEQint tobechecked;

   /* find the symbols that act as roots of computed trees,
      add artificial dependencies:
   */
   initializeSEQint (GenTreeRoots);
   foreachinSEQDef(defseqOfAttrEval(ae), defs, d)
   if (typeof(d) == KSymb)
   {
      if (HasGenAttr(DefToSymb(d)))
      {  appendfrontSEQint (GenTreeRoots, didOfDef (d));
#ifndef GORTO
	 fprintf (ProtocolFile,
		  "%s is the root of a computed subtree\n",
		  dnameOfDef (d));
#endif
	 EnterGenDeps (DefToSymb (d));
      }
   }

  /* find the symbols that may occur in a computed tree: */
  initializeSEQint (GenTreeSymbs);
  tobechecked = GenTreeRoots;
  while (!emptySEQint (tobechecked))
  { int symbdid;
    SLNODE *symbocc;
    
    retrievefirstSEQint (tobechecked, symbdid);
    tobechecked = tailSEQint (tobechecked);
    appendfrontSEQint (GenTreeSymbs, symbdid);
#ifndef GORTO
    fprintf (ProtocolFile,
	     "%s may occur in a computed subtree\n",
	     ref_tab[symbdid].entry.symb.symb_def->dname);
#endif
    /* consider all rules with symbdid as lhs: */
    for (symbocc = ref_tab[symbdid].entry.symb.hddown;
	 symbocc != NULL; symbocc = symbocc->down)
      if (ref_tab[symbocc->pid].entry.prod.hdright == symbocc)
      { /* pid has symbdid as lhs; consider rhs: */
        SLNODE *rhsocc;
	for (rhsocc = symbocc->right;
	     rhsocc != NULL; rhsocc = rhsocc->right)
	  if (!(inSEQint (tobechecked, rhsocc->sid)) &&
	      !(inSEQint (GenTreeSymbs, rhsocc->sid)))
             appendfrontSEQint (tobechecked, rhsocc->sid);
      }
  }
#ifndef GORTO
  fprintf (ProtocolFile, "\n");
#endif
}/* GenTreeDeps */

void ChkBUInGenTrees ()
/* check whether GenTreeSymbs have a bottomup attribute */
{ 
  while (!emptySEQint (GenTreeSymbs))
  { int symbdid; SEQAttrdef satd; Attrdef atd;
    retrievefirstSEQint (GenTreeSymbs, symbdid);
    GenTreeSymbs  = tailSEQint (GenTreeSymbs);
    foreachinSEQAttrdef
       (attrsOfSymb(ref_tab[symbdid].entry.symb.symb_def), satd, atd)
       if (ref_tab[didOfAttrdef (atd)].entry.attr.bottomup)
       { char errmsgbuff[ERR_BUFF_LEN];
         err_setpos (rowOfAttrdef (atd), colOfAttrdef (atd));
	 sprintf (errmsgbuff,
		  "%s.%s can not be computed bottom-up in a computed tree",
		  dnameOfSymb(ref_tab[symbdid].entry.symb.symb_def),
		  nameOfAttrdef (atd));
	 err_print_error (errmsgbuff);
	 fprintf (ProtocolFile,
		  "*** ERROR *** %s\n",errmsgbuff);
       }
  }
#ifndef GORTO
   fprintf (ProtocolFile, "\n");
#endif
}/* ChkBUInGenTrees */

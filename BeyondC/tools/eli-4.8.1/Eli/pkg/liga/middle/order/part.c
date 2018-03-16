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
/* $Id: part.c,v 4.7 1998/04/28 14:28:56 ludi Exp $ */
static char rcs_id[] = "$Id: part.c,v 4.7 1998/04/28 14:28:56 ludi Exp $";

/****************************************************************
*                                                               *
*       Module  : part.c                                        *
*       compute the partitions of attributes for the		*
*       symbols.                                                *
*                                                               *
****************************************************************/

/* include */
#include "ligaconsts.h"
#include "printerr.h"
#include "option.h"
#include "do_order.h"
#include "reftab.h"
#include "depmod.h"
#include "allocate.h"

#include "induce.h"
#include "part.h"

/* global variables */
static int *AttrRank;      /* array used in early and late;
                              number of still relevant dependencies per attr
			      AttrRank[atno]==0: atno is ready to be scheduled
			   */

#define ODD(x)          ((x)%2 == 1)
#define EVEN(x)         ((x)%2 == 0)

#define IsRootSym(symb) ((symb)->hddown->down == NULL)

/********************************************************
* 	void early()	 			 	*
*    	for each attribute of this symbol,		*
*	compute the earliest attribute partition set    *
*	to which the attribute can be allocated.	*
********************************************************/
static
void early (sid) int sid;
{
   int currpartno;
   int aid, atno, notassigned;
   bool foundone;
   SYMBENTRY *symb = &ref_tab[sid].entry.symb;
   
/* This function is only called if there are attributes. */

   /* initialize AttrRank:
      AttrRank[atno] == n: there are n dependences from non scheduled
                           attrs to atno
   */
   for (atno = 0; atno < symb->attr_num; atno++)
   { int fromatno, cnt = 0;
     for (fromatno = 0; fromatno < symb->attr_num; fromatno++)
         if (DSDependson (sid, atno, fromatno))
	    cnt++;
     AttrRank[atno] = cnt;
   }

   notassigned = symb->attr_num;	/* number of not yet assigned attrs */
   currpartno = 0;

   do
   {
      foundone = FALSE;
      for (atno = 0; atno < symb->attr_num; atno++)
      {
	 aid = lookup_attr (sid, atno);
	 if (AttrRank[atno] == 0 && /* ready to be scheduled */
	     ((EVEN (currpartno) &&
	       ref_tab[aid].entry.attr.attr_def->class == ATCLINH
	      ) ||
	      (ODD (currpartno) &&
	       ref_tab[aid].entry.attr.attr_def->class == ATCLSYNT
	      )
	     ))
	 { int toatno;
	 
	   AttrRank[atno] = -1;
	   foundone = TRUE;
	   notassigned--;
	   ref_tab[aid].entry.attr.part = currpartno;

	   /* decrease the AttrRank[to] which depend on atno: */
	   for (toatno = 0; toatno < symb->attr_num; toatno++)
	       if (DSDependson (sid, toatno, atno))
		  AttrRank[toatno]--;
	 }/* foundone */
      }/* for candidates */

      if (notassigned > 0 && !foundone)
	 currpartno++;

   } while (notassigned > 0);

   ref_tab[sid].entry.symb.part_num =
      (EVEN (currpartno) ? (currpartno + 1) : (currpartno));
   /* assert: currpartno > 0 and ODD (currpartno) */
   
   for (atno = 0; atno < symb->attr_num; atno++)
   { aid = lookup_attr(sid, atno);
     partOfAttrdef (ref_tab[aid].entry.attr.attr_def)
        = ref_tab[aid].entry.attr.part / 2 + 1;
   }
}/* early() */



/********************************************************
* 	void late()	 			 	*
*    	for each attribute of this symbol,		*
*	compute the latest attribute partition set      *
*	to which the attribuet can be allocated.	*
********************************************************/
static
void late (sid) int sid;
{
   SYMBENTRY *symb = &ref_tab[sid].entry.symb;
   int currpartno, maxpartno;
   int aid, atno, notassigned;
   bool foundone;

/* This function is only called if there are attributes. */

   /* bottomup attrs are already scheduled (part 0 and 1),
      dependences (any BU -> any non-BU) exist,
      the graph is acyclic
      We here schedule only non-BU attrs
      If TREE_BOTTOM_UP there will be at least parts 0,1,2,3 (possibly empty)
      else              there will be at least parts 0,1 (possibly empty)
   */

   /* initialize AttrRank:
      AttrRank[atno] == n: there are n dependences from atno to
			   non scheduled attrs
   */
   notassigned = symb->attr_num;	/* number of not yet assigned attrs */
   for (atno = 0; atno < symb->attr_num; atno++)
   { 
      aid = lookup_attr(sid, atno);
      if (ref_tab[aid].entry.attr.bottomup && !IsRootSym (symb))
	  /* symbol is not the root; bottomup attrs are treated normal */
      {  notassigned--;
         AttrRank[atno] = -1;
      } else
      { int toatno, cnt = 0;
        for (toatno = 0; toatno < symb->attr_num; toatno++)
         if (DSDependson (sid, toatno, atno))
	    cnt++;
        AttrRank[atno] = cnt;
      }
   }

   /* we start with a large odd maxpartno
      the partition numbers are scaled down 
      when we know how many are needed:
   */
   maxpartno =
     (EVEN (symb->attr_num) ? (symb->attr_num + 3) : (symb->attr_num + 2));
   currpartno = maxpartno;

   do
   {
      foundone = FALSE;
      for (atno = 0; atno < symb->attr_num; atno++)
      {  aid = lookup_attr(sid, atno);
	 if (AttrRank[atno] == 0 && /* ready to be scheduled */
	     ((EVEN (currpartno) &&
	       ref_tab[aid].entry.attr.attr_def->class == ATCLINH
	      ) ||
	      (ODD (currpartno) &&
	       ref_tab[aid].entry.attr.attr_def->class == ATCLSYNT
	      )
	     ))
         { int fromatno;
	 
           AttrRank[atno] = -1;
	   foundone = TRUE;
	   notassigned--;
	   ref_tab[aid].entry.attr.part = currpartno;

	   /* decrease the AttrRank[from] which atno depends on: */
	   for (fromatno = 0; fromatno < symb->attr_num; fromatno++)
	       if (DSDependson (sid, atno, fromatno))
		  AttrRank[fromatno]--;
	 }/* foundone */
      }

      if (notassigned > 0 && !foundone)
      {	 currpartno--; /* next partition */

	 /* check for system error: */
         if (currpartno < 0 ||
	     (currpartno < 2 && TREE_BOTTOM_UP && !IsRootSym (symb)))
	 { char errmsgbuff[ERR_BUFF_LEN];
	   err_setpos (rowOfSymb(symb->symb_def),
		      colOfSymb(symb->symb_def));
           sprintf (errmsgbuff,
		    "system error: partition number below limit for symbol %s",
		    dnameOfSymb(symb->symb_def));
	   err_print_error (errmsgbuff);
	   fprintf (ProtocolFile, "*** ERROR *** %s\n", errmsgbuff);
	   goto panic;
	 }
      }
   } while (notassigned > 0);

panic:
   /* currpartno is the temp number of the earliest non empty partition */

   /* the first is an INH one, i.e. EVEN: */
   if (ODD (currpartno)) currpartno--;

   /* we need a partition pair for bottomup; but not at the root: */
   if (TREE_BOTTOM_UP && !IsRootSym (symb))
      currpartno -= 2;

#ifndef GORTO
   if (IsRootSym (symb))
      fprintf (ProtocolFile, "\nRoot symbol is %s\n\n",
	       dnameOfSymb(symb->symb_def));
#endif

   /* currpartno is the temp number of the partition that should be 0 
      scale the temp numbers down:
   */
   maxpartno -= currpartno;

   ref_tab[sid].entry.symb.part_num = maxpartno;

   for (atno = 0; atno < symb->attr_num; atno++)
   { aid = lookup_attr(sid, atno);
     if (!(ref_tab[aid].entry.attr.bottomup) || IsRootSym (symb))
        ref_tab[aid].entry.attr.part -= currpartno;
     partOfAttrdef (ref_tab[aid].entry.attr.attr_def)
        = ref_tab[aid].entry.attr.part / 2 + 1;
   }
}/* late() */

/********************************************************
*	void add_deps()					*
*	add the dependencies from attribute partition   *
* 	to ds and transitivly close each ds and dp   	*
********************************************************/
static
void add_deps (sid) int sid;
{  SYMBENTRY *symb = &ref_tab[sid].entry.symb;
   int atno, attrno;
   int atid, attrid, atpart;

   for (atno = 0; atno < symb->attr_num; atno++)
   {
      atid = lookup_attr (sid, atno);
      atpart = ref_tab[atid].entry.attr.part;

      for (attrno = atno; attrno < symb->attr_num; attrno++)
      {
	 attrid = lookup_attr (sid, attrno);
	 /* add the dependencies: later assigned depend on earlier assigned */
	 if (atpart > ref_tab[attrid].entry.attr.part)
	    DSSetDepend (sid, atno, attrno);
	 else if (atpart < ref_tab[attrid].entry.attr.part)
	    DSSetDepend (sid, attrno, atno);
      }
   }

   /* transitively close symb->ds */
   if (ref_tab[sid].entry.symb.part_num >= 1 && AUTOMATICALLY)
   {  /* first term is always true!? */
      bool changed;
#ifndef GORTO
      symb->changed=FALSE;
      distributedeps(sid, &changed);
      transitiveclosure();
#else
      distributedeps(sid, &changed);
      if (changed)
	 transitiveclosure();
#endif
   }
}/* add_deps() */

/********************************************************
* 	void symbpartition()				*
*	compute the partition of symbol did.		*
********************************************************/

void symbpartition (sid) int sid;
{
   SYMBENTRY *symb = &ref_tab[sid].entry.symb;

   /* initialize the number of partitions for the case of no attrs: */
   if (TREE_BOTTOM_UP && !IsRootSym (symb))
        symb->part_num = 3;
   else symb->part_num = 1;

   /* is partitioning necessary? */
   if (symb->attr_num <= 0)
      return;

   /* is partitioning possible? */   
#ifndef GORTO
   if (symb->cyclic)
      return;
#else
   if (symb->state & S_CYCLIC)
      return;
   else
      symb->state |= S_PARTITIONED;
#endif

      if (PART_LATE || TREE_BOTTOM_UP)
	 late (sid);
      else
         early (sid);

      /* add new dependencies */
      add_deps (sid);
}/* symbpartition */


/********************************************************
* 	void partit()					*
*	compute the partition of attributes of 		*
*	symbols.					*
********************************************************/

void partit()
{ int did;

  /* allocate array AttrRank; to be used in early and late: */
  AttrRank =
      (int*) Allocate
          (__FILE__,__LINE__, sizeof (int) * (MaxSymbAttrNum+1));

  for (did = min_entry; did <= max_entry; did++)
      if (ref_tab[did].etag == SYMB)
	 symbpartition (did);

}/* partit() */

void BUPartition ()
/* makes rough partitions:
   BU INH = 0, BU SYNT = 1; others = 2
   and propagates the resulting dependencies
*/
{ int did;

  for (did = min_entry; did <= max_entry; did++)
  if (ref_tab[did].etag == SYMB)
  { SYMBENTRY *symb = &ref_tab[did].entry.symb;
    int atno, symbhasbottomup = 0;

    if (IsRootSym (symb))
       continue;
       
    for (atno = 0; atno <= symb->attr_num - 1; atno++)
    { int atid = lookup_attr(did, atno);
      if (ref_tab[atid].entry.attr.bottomup)
      { symbhasbottomup = 1; break;
      }
    }
    if (!symbhasbottomup) continue;
    
    for (atno = 0; atno <= symb->attr_num - 1; atno++)
    { int atid = lookup_attr(did, atno);
      int atclass = ref_tab[atid].entry.attr.attr_def->class;

      if (ref_tab[atid].entry.attr.bottomup)
      {
	  if (atclass == ATCLINH)
	  {
	      ref_tab[atid].entry.attr.part = 0;
	  }
	  else
	  {
	      ref_tab[atid].entry.attr.part = 1;
	  }
      }
      else
      {
	  ref_tab[atid].entry.attr.part = 2;
      }
    }
    symb->part_num = 3;
    add_deps (did);
  }
}/* BUPartition */

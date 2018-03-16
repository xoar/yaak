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
/* $Id: induce.c,v 4.4 1997/08/29 09:16:01 peter Exp $ */
static char rcs_id[] = "$Id: induce.c,v 4.4 1997/08/29 09:16:01 peter Exp $";

#include "allocate.h"
#include "reftab.h"
#include "depmod.h"

#include "induce.h"

#ifndef GORTO

/************************************/
/* function versions for liga order */
/************************************/

/****************************************************************
*       void  ruletransitive()                                  *
*       compute the transitive  graphs for                      *
*       rule #pid and transpose the new dependencies to         *
*       the ds of symbols occurring in this rule.               *
****************************************************************/
void
ruletransitive(pid)
   int pid;

{  PRODENTRY *prod = &ref_tab[pid].entry.prod;
   int maxatno = prod->check_row;     /* first dimension of dp (row) */
   int maxword = prod->check_col;     /* second dimension of dp (column) */

   SYMBENTRY *symb;       /* for symbols of the production */
   SLNODE *slnptr;        /* linked list of symbols for productions */
   int attrnum;           /* number of attributes of symbols */
   int startcol;          /* starting column for symbol attributes */

   register int atno1, atno2, word;  /* loop counters */

   if (maxatno > 0)       /* if there are attritbutes in this rule */
   { /* transitively close dp. Warshal's algorithm */
     for (slnptr = prod->hdright;slnptr;slnptr=slnptr->right)
     { /* for all symbols: */
       int rowpos = slnptr->start_row;
       symb = &ref_tab[slnptr->sid].entry.symb;
       startcol= slnptr->start_col;
       attrnum = symb->attr_num;
       for (atno2 = 0; atno2 < attrnum; atno2++, rowpos++)
       { /* for all attributes of this symbol */
	 unsigned int mask = 0x1 << atno2 % WORD_LENGTH;
         /* bitmask saying "something depends on atno2 */
	 int colpos = startcol+atno2/WORD_LENGTH;
         for (atno1 = 0; atno1 < maxatno; atno1++)
	 { /* for all attributes of the production */
           if (prod->dp[atno1][colpos] & mask)
	   { /* if atno2 depends on atno1 */
	     for (word = 0; word <= maxword; word++)
	     { /* make all attributes that depend on atno2 */
	       /* also dependent on atno1 */
               prod->dp[atno1][word] |= prod->dp[rowpos][word];
             } /* for word */
           } /* if atno2 depends on atno1 */
	 } /* for all attributes of the production */
       } /* for all attributes of this symbol */
     } /* for all symbols */

     /* check if symbol graphs have become cyclic */
     /* copy symbol graphs to the graphs ds for all symbols */
     /* see if ds has changed, if yes propagate changes to all */
     /* affected production graphs dp */
  
     for (slnptr = prod->hdright; slnptr; slnptr = slnptr->right)
     { /* for all symbols */
       int startrow = slnptr->start_row;
       symb = &ref_tab[slnptr->sid].entry.symb;
       attrnum = symb->attr_num;
       startcol= slnptr->start_col;
       for (atno2 = 0; atno2 < attrnum; atno2++)
       { /* for all attributes of symbol */
	 /* check circularity */
	 if (prod->dp[startrow + atno2][startcol + atno2 / WORD_LENGTH]
             & 0x1 << atno2 % WORD_LENGTH)
	 {  symb->cyclic = TRUE;
	    prod->cyclic = TRUE;
	 }
	 /* transpose into ds */
	 for (word = 0; word < (attrnum - 1) / WORD_LENGTH + 1; word++)
	 { /* for all columns used by the attributes of this symbol */
	   unsigned int set = symb->ds[atno2][word] |
		              prod->dp[startrow + atno2][startcol + word];
	   if (symb->ds[atno2][word] != set)
	   { /* symbol graph ds should be changed */
	     symb->ds[atno2][word] = set;
	     symb->changed = TRUE;
	   } /* symbol graph ds should be changed */
	 } /* for all columns used by the attributes of this symbol */
       } /* for all attributes of symbol */

      if (graphstate > TRANSITIVE) /* we are computing induced or */
				   /* partitioned graphs */
	if (symb->changed /* && ! symb->cyclic UK 09.04.2010 */) 
	  { /* propagate symbol changes */
	    int changed;
	    distributedeps(slnptr->sid,&changed);
	    symb->changed=FALSE;
	  } /* propagate symbol changes */
      }	/* for all symbols */

   } /* if there exist attributes in this rule */
} /* end of ruletransitive() */


/****************************************************************
*	void distributedeps () 					*
* 	distribute the symbol attribute dependencies to  	*
* 	rules. 							*
****************************************************************/

void
distributedeps(sid, changed)
   int sid;
   bool *changed;
{
   SLNODE *slnptr;
   SYMBENTRY *symb = &ref_tab[sid].entry.symb;
   int attrnum= symb->attr_num;
   register int atno, word;

   *changed = FALSE;

   for (slnptr = symb->hddown; slnptr; slnptr = slnptr->down)
   { /* for all places where symbol occurs */
     PRODENTRY *prod = &ref_tab[slnptr->pid].entry.prod;
     int startcol = slnptr->start_col;
     int startrow = slnptr->start_row;
     for (atno = 0; atno < attrnum; atno++)
     { /* for all attributes of symbol */
       for (word = 0; word < (attrnum-1) / WORD_LENGTH + 1; word++)
       { /* for all words occupied by the symbols attributes */
	 if (symb->ds[atno][word] != 
             prod->dp[atno + startrow][word + startcol])
	 { /* propagate changes to production graphs */
	   prod->dp[atno + startrow][word + startcol] = symb->ds[atno][word];
	   *changed = TRUE;
	   prod->changed = TRUE;
	 } /* propagate changes to production graphs */
       } /* for all words occupied by the symbols attributes */
     } /* for all attributes of symbol */
   } /* for all places where symbol occurs */
}/* end of distributedeps () */


void
distributealldeps()
{
   bool symbchanged;
   int did;
   SYMBENTRY *symb;
   for (did = min_entry; did <= max_entry; did++)
   { /* for all identifiers */
     if (ref_tab[did].etag == SYMB)
     { /* it is a grammar symbol */
       symb = &ref_tab[did].entry.symb;
       if (symb->changed /* && !symb->cyclic */)
       { symb->changed = FALSE;
         distributedeps(did, &symbchanged);
       } /* if changed */
     } /* it is a grammar symbol */
   } /* for all identifiers */
}/* end of distributealldeps () */


/* we sort productions */
static int *sortedprods = (int*)0;            /* sorted production did's */
static int pcount=0;                          /* number of productions */  

static int attrs(pid)                         /* number of attributes in a */
	int pid;          		       /* prod */
{ return ref_tab[pid].entry.prod.check_row-1;
} /* attrs() */

static void sortprods()
{ int pid;           /* production id */
  int i,j;           /* counters for selection sort */
  int min;           /* minimum position for selection sort */

  /* count productions */
  for (pid = min_entry; pid <= max_entry; pid++)
      if (ref_tab[pid].etag == PROD)
        pcount ++;

  /* allocate sortedprods array */
  sortedprods = (int*) Allocate(__FILE__,__LINE__,pcount*sizeof(int));

  /* enter pids into sortedprods array */
  pcount=0;
  for (pid = min_entry; pid <= max_entry; pid++)
      if (ref_tab[pid].etag == PROD)
        sortedprods[pcount++] = pid;
 
  /* sort sortedprods array according to number of attributes per prod */
  for (i=0;i<pcount-1;i++) 
    { min = i;
      for (j=i+1;j < pcount;j++) 
	if (attrs(sortedprods[j])<attrs(sortedprods[min])) 
          min=j;
      /* exchange elements */
      pid = sortedprods[min];
      sortedprods[min] = sortedprods[i];
      sortedprods[i] = pid;
    } 
}

/****************************************************************
*       void transitiveclosure() 				*
*       transitively close attribute dependency graphs of 	*
*       both rules and symbols.					*
****************************************************************/
void
transitiveclosure()
{
   bool changed;
   int prodno;
   PRODENTRY *prod;
   /* check if productions have been sorted */
   if (!sortedprods) 
      sortprods();
   do
   { changed = FALSE; 
     for (prodno = 0; prodno < pcount; prodno++)
     { /* for all productions */
       prod = &ref_tab[sortedprods[prodno]].entry.prod;
       if (prod->changed /* && !prod->cyclic */)
       { changed=TRUE;
	 prod->changed = FALSE;
	 ruletransitive(sortedprods[prodno]);
       }
     }
   } while (changed);
} /* end of transitiveclosure () */


#else 
/**********************/
/* now GORTO versions */
/**********************/

/* imported from Gorto: */
extern short graphstate_hint;

void ruletransitive (pid) int pid;
{
   PRODENTRY *prod;
   SYMBENTRY *symb;
   bool changed, newsymbcycle, newrulecycle;
   int atno, maxatno;
   int check_row, maxword;
   int atntno;
   SLNODE *slnptr;
   DEPENDENCY *dp, *dep, *dep2;
   DEP_VECTOR *dp_row, *dp_row2, *ds_row;

   newrulecycle = FALSE;
   prod = &ref_tab[pid].entry.prod;
   maxatno = prod->check_row - 1;
   check_row = prod->check_row;
   maxword = prod->check_col;

   if (maxatno >= 0)
   {	/* if there are attritbutes in this rule */

      /* transitively close prod.dp */
      do
      {
	 changed = FALSE;
	 dp_row = &prod->dp[maxatno];
	 for (; dp_row >= &prod->dp[0]; dp_row--)
	 {

	    dp = &(*dp_row)[0];
	    dp_row2 = &prod->dp[0];
	    for (slnptr = prod->hdright; slnptr != NULL; slnptr = slnptr->right)
	    {

	       symb = &ref_tab[slnptr->sid].entry.symb;
	       for (atntno = 0; atntno < symb->attr_num; atntno++, dp++, dp_row2++)

		  if (*dp)
		  {
		     dep = &(*dp_row)[maxatno];
		     dep2 = &(*dp_row2)[maxatno];
		     for (; dep >= &(*dp_row)[0]; dep--, dep2--)

			if (*dep2 && !(*dep))
			{
			   changed = TRUE;
			   *dep = T_TRAN | graphstate_hint;
			   prod->dp_detail[maxatno - (&prod->dp[maxatno] - dp_row)]
			      [maxatno - (&(*dp_row)[maxatno] - dep)].
			      transitive.over_atno = slnptr->start_row + atntno;
			}
		  }
	    }
	 }
      } while (changed);

      dp_row = &prod->dp[0];
      for (slnptr = prod->hdright; slnptr != NULL; slnptr = slnptr->right)
      {

	 newsymbcycle = FALSE;
	 symb = &ref_tab[slnptr->sid].entry.symb;
	 ds_row = &symb->ds[0];
	 for (atno = 0; atno < symb->attr_num; atno++, dp_row++, ds_row++)
	 {

	    /* check circularity for both dp and ds */

	    if ((*dp_row)[slnptr->start_row + atno])
	    {
	       newrulecycle = TRUE;
	       newsymbcycle = TRUE;
	    }
	    /* transpose into ds */

	    dep = &(*ds_row)[symb->attr_num - 1];
	    dep2 = &(*dp_row)[slnptr->start_row + symb->attr_num - 1];
	    for (; dep >= &(*ds_row)[0]; dep--, dep2--)

	       if (!(*dep) && *dep2)
	       {
		  *dep = *dep2;
		  {
		     *dep = T_IND | graphstate_hint;
		     if ((*dep2 & T_TRAN) || !(*dep2 & T_IND))
			symb->ds_detail[atno]
			   [symb->attr_num - 1 -
			    (&(*ds_row)[symb->attr_num - 1] - dep)].
			   induced.from = slnptr;
		  }
		  symb->state |= S_CHANGED;
	       }
	 }

	 if (newsymbcycle)
	    symb->state |= S_CYCLIC;
      }

      if (newrulecycle)
      {
	 prod->state |= S_CYCLIC;
      }
   }	/* if there exist attributes in this rule */
   return;
}/* end of ruletransitive() */

/****************************************************************
*	void distributedeps () 					*
* 	distribute the symbol attribute dependencies to  	*
* 	rules. 							*
****************************************************************/

void
distributedeps(sid, changed)
   int sid;
   bool *changed;
{
   SLNODE *slnptr;
   PRODENTRY *prod;
   SYMBENTRY *symb;
   int maxatno;
   DEPENDENCY *dp, *ds;
   DEP_VECTOR *dp_row, *ds_row;

   *changed = FALSE;
   symb = &ref_tab[sid].entry.symb;
   for (slnptr = symb->hddown; slnptr != NULL; slnptr = slnptr->down)
   {
      prod = &ref_tab[slnptr->pid].entry.prod;
      maxatno = slnptr->start_row + symb->attr_num - 1;
      dp_row = &prod->dp[maxatno];
      ds_row = &symb->ds[symb->attr_num - 1];
      for (; ds_row >= &symb->ds[0]; dp_row--, ds_row--)
      {

	 dp = &(*dp_row)[maxatno];
	 ds = &(*ds_row)[symb->attr_num - 1];
	 for (; ds >= &(*ds_row)[0]; dp--, ds--)

	    if (*ds && !(*dp))
	    {
	       if (*ds & (T_DIR | T_IND))
	       {
		  *dp = T_IND | graphstate_hint;
		  prod->dp_detail
		     [maxatno - (&prod->dp[maxatno] - dp_row)]
		     [maxatno - (&(*dp_row)[maxatno] - dp)]
		     .induced.from =
		     symb->ds_detail
		     [symb->attr_num - 1 -
		      (&symb->ds[symb->attr_num - 1] - ds_row)]
		     [symb->attr_num - 1 -
		      (&(*ds_row)[symb->attr_num - 1] - ds)]
		     .induced.from;
	       } else
	       {
		  *dp = T_IND | graphstate_hint;
		  prod->dp_detail
		     [maxatno - (&prod->dp[maxatno] - dp_row)]
		     [maxatno - (&(*dp_row)[maxatno] - dp)]
		     .induced.from = (SLNODE *) NULL;
	       }
	       *changed = TRUE;
	       prod->state |= S_CHANGED;
	    }
      }
   }

   /* changed = (*changed || symb->changed); */
   return;

}/* end of distributedeps () */

/****************************************************************
*       void transitiveclosure() 				*
*       transitively close attribute dependency graphs of 	*
*       both rules and symbols.					*
****************************************************************/

void
transitiveclosure()
{
   bool changed, symbchanged;
   int did;
   PRODENTRY *prod;
   SYMBENTRY *symb;

   do
   {
      for (did = min_entry; did <= max_entry; did++)
	 if (ref_tab[did].etag == PROD)
	 {
	    prod = &ref_tab[did].entry.prod;
	    if ((prod->state & S_CHANGED)/*  && !(prod->state & S_CYCLIC) */)
	    {
	       ruletransitive(did);
	       prod->state &= ~S_CHANGED;
	    }
	 }
      changed = FALSE;

      if (graphstate > TRANSITIVE)
	 for (did = min_entry; did <= max_entry; did++)
	    if (ref_tab[did].etag == SYMB)
	    {
	       symb = &ref_tab[did].entry.symb;
	       if ((symb->state & S_CHANGED) /* && !(symb->state & S_CYCLIC)*/)
	       {
		  symb->state &= ~S_CHANGED;
		  distributedeps(did, &symbchanged);
		  changed = changed || symbchanged;
	       }
	    }
   } while (changed);

   return;
}/* end of transitiveclosure () */
#endif

static
void DSInitDirDeps (sid)
	int sid;
{
   int atnum = ref_tab[sid].entry.symb.attr_num;
   int pid;
   int row, col_word, st_row, st_col_word;
   SLNODE *slnptr;

   slnptr = ref_tab[sid].entry.symb.hddown;
   while (slnptr != NULL)
   {

     pid = slnptr->pid;
     st_row = slnptr->start_row;
#ifndef GORTO
     st_col_word = slnptr->start_col;

     for (row = 0; row < atnum; row++)
       for (col_word = 0; col_word < (atnum - 1) / WORD_LENGTH + 1; col_word++)
       {
	  ref_tab[sid].entry.symb.init_ds[row][col_word] |=
	     ref_tab[pid].entry.prod.init_dp[st_row + row][st_col_word + col_word];
	  ref_tab[sid].entry.symb.ds[row][col_word] |=
	     ref_tab[pid].entry.prod.init_dp[st_row + row][st_col_word + col_word];
       }
#else
    st_col_word = slnptr->start_row;

    for (row = 0; row < atnum; row++)
       for (col_word = 0; col_word < atnum; col_word++)
       {
	  if (ref_tab[pid].entry.prod.dp
	      [st_row + row][st_col_word + col_word] & T_DIR)
	  {
	     ref_tab[sid].entry.symb.ds[row][col_word] = T_DIR;
	     ref_tab[sid].entry.symb.ds_detail[row][col_word]
		.induced.from = slnptr;
	  }
       }
#endif
    slnptr = slnptr->down;	/* next occurrence of this symbol */
  }
}

/****************************************************************
*                                                               *
*    void cons_init_ds()                                        *
*    construct the initial dependency graph for each symbol.    *
*    the dependency relations in the init_dp's are projected    *
*    into the init_ds's.                                        *
*                                                               *
****************************************************************/

void cons_init_ds()
{
   int i;
   for (i = 0; i < max_entry; i++)

      if ((ref_tab[i].etag == SYMB) &&
	  (ref_tab[i].entry.symb.attr_num > 0))
      {

	 /* construct the initial dependency graph of this symbol */
	 DSInitDirDeps (i);
      }
}/* cons_init_ds() */

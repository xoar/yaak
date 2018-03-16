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
/* $Id: reftab.c,v 4.3 1997/08/29 09:16:01 peter Exp $ */
static char rcs_id[] = "$Id: reftab.c,v 4.3 1997/08/29 09:16:01 peter Exp $";

/************************************************************************
*									*
*       Version : 1.0    						*
*	Module  : reftab.c						*
*       Author  : Jiyang Liu						*
*       Routines to initialize and access the reference table		*
*       ref_tab[].							*
*									*
************************************************************************/

#include "err.h"
#include "allocate.h"

#include "reftab.h"

/* exported variables: */

ALLENTRIES *ref_tab;
int max_entry, min_entry; /* the index range of ref_tab */

int graphstate;

int ord_max_did = 0; /* the largest did ever used,
                        may be incremented beyond max_entry */

int ord_DefSymbNum;  /* the number of symbols */
int ord_DefRuleNum;  /* the number of rules */
int DefAttrNum;      /* the total number of attributes */
int MaxRhsLen = 0;   /* the maximal number of rhs symbols */
int MaxRuleAttrs = 0;/* the maximal number of attrs in a rule */
int MaxSymbAttrNum = 0; /* maximal number of attributes per symbol */

void find_max_did (IS) AttrEval IS;
{
   SEQDef x;
   SEQAttrdef y;
   Attrdef attrdef;
   Def def;
   int did, attrcnt;

   /* determine ord_max_did */
#define MAX_DID(d) (((d)>(ord_max_did))?(d):(ord_max_did))

   ord_DefSymbNum = 0;
   ord_DefRuleNum = 0;
   DefAttrNum = 0;

   foreachinSEQDef(IS->defseq, x, def)
   {
      switch (typeof(def))
      {
      case KSymb:
	 ord_DefSymbNum++;
	 did = def.VSymb->did;
	 ord_max_did = MAX_DID(did);
	 attrcnt = 0;
	 foreachinSEQAttrdef(def.VSymb->attrs, y, attrdef)
	 {
	    DefAttrNum++;
	    attrcnt++;
	    did = attrdef->did;
	    ord_max_did = MAX_DID(did);
	 }
	 if (attrcnt > MaxSymbAttrNum)
	    MaxSymbAttrNum = attrcnt;
	 break;

      case KProd:
      {  int rhscnt = 0;
         SEQEntity entlist; Entity ent;
	 
	 ord_DefRuleNum++;
	 did = def.VProd->did;
	 ord_max_did = MAX_DID(did);
	 /* find length of right-hand side: */
         foreachinSEQEntity(rhsOfProd(def.VProd), entlist, ent)
	   if (typeof(ent) == KSymbol)
	      rhscnt++;
         if (rhscnt > MaxRhsLen)
	    MaxRhsLen = rhscnt;
	 break;
      }
      case KChain:
	 did = def.VChain->did;
	 ord_max_did = MAX_DID(did);
	 break;
      
      case KTypedef:
	 did = def.VTypedef->did;
	 ord_max_did = MAX_DID(did);
	 break;

      }	/* switch */
   }
}/* find_max_did */

/****************************************************************
*	int lookup_attr () 					*
*	look up the did of an attribute occurrence using	*
*	the symbol's did and the attr's pos.			*
****************************************************************/

int lookup_attr (sid, pos) int sid, pos;
{
   SYMBENTRY *symb;
   SEQAttrdef restattrs;
   Attrdef attr;
   int atno;

   symb = &ref_tab[sid].entry.symb;
   atno = 0;

   foreachinSEQAttrdef(symb->symb_def->attrs, restattrs, attr)
      if (atno != pos)
        atno++;
      else
        return (attr->did);

   return 0; /* try to find non existen attr */
}/* lookup_attr () */

/**********************************************************
* 							  *
*   void ins_right_list();				  *
*   append a symbol node at the end of prod. symbol list  *
*                                                         *
**********************************************************/
static
void ins_right_list(p) SLNODE *p;
{
   static SLNODE *curptr;

   if (ref_tab[p->pid].entry.prod.hdright == NULL)
      ref_tab[p->pid].entry.prod.hdright = p;
   else
      curptr->right = p;

   curptr = p;
}/* ins_right_list() */

/**************************************************************
* 							      *
*   void ins_down_list();				      *
*   append a symbol node at the end of same-name symbol list  *
*                                                             *
**************************************************************/
static
void ins_down_list(p) SLNODE *p;
{
   SLNODE *last;

   if (ref_tab[p->sid].entry.symb.hddown == NULL)
      ref_tab[p->sid].entry.symb.hddown = p;
   else
   {
      last = ref_tab[p->sid].entry.symb.hddown;
      while (last->down != NULL)
	 last = last->down;
      last->down = p;
   }
}/* ins_down_list() */

/**************************************************************************
*									  *
* void sl_cons();							  *
* construct the linked symbol list for production no. pid and build the   *
* links through those symbol occurrences with 				  *
* the same symbol name (did) 					          *
*									  *
**************************************************************************/
static
void sl_cons(pid, row, col)
   int pid;
   int *row, *col;	/* the number of rows and columns of the init_dp of
			 * this production, they are used in allocating space
			 * for the production's init_dp.  */
{
   int n;
   int cur_row, cur_col;
   SLNODE *slnptr;
   SEQEntity x;
   Entity entity;

   /* the lhs symbol in a prod. */
   cur_row = cur_col = 0;

   slnptr = (SLNODE *) Allocate(__FILE__,__LINE__,sizeof(SLNODE));
   slnptr->pid = pid;
   slnptr->start_row = cur_row;
   slnptr->start_col = cur_col;
   slnptr->sid = ref_tab[pid].entry.prod.prod_def->lhs;
   slnptr->right = NULL;
   slnptr->down = NULL;
   ins_right_list(slnptr);	/* insert into the prod. symbol list */
   ins_down_list(slnptr);	/* insert into the same-name symbol list */

   n = ref_tab[slnptr->sid].entry.symb.attr_num;
   if (n)
   {
      cur_row += n;
      cur_col += (n - 1) / WORD_LENGTH + 1;
   }
   /* processing the rhs symbols */

   foreachinSEQEntity(ref_tab[pid].entry.prod.prod_def->rhs, x, entity)
      switch (typeof(entity))
   {
   case KOpt:
   case KStar:
   case KPlus:
   case KDelim:
   case KDelopt:
      /* case KUnit: */
   case KLiteral:
      break;

   case KSymbol:
      slnptr = (SLNODE *) Allocate(__FILE__,__LINE__,sizeof(SLNODE));
      slnptr->pid = pid;
      slnptr->sid = entity.VSymbol->did;
      slnptr->start_row = cur_row;
      slnptr->start_col = cur_col;
      slnptr->down = NULL;
      slnptr->right = NULL;
      ins_right_list(slnptr);
      ins_down_list(slnptr);

      n = ref_tab[slnptr->sid].entry.symb.attr_num;
      if (n)
      {
	 cur_row += n;
	 cur_col += (n - 1) / WORD_LENGTH + 1;
      }
      break;

   default:
      /* wrong entity */
      break;

   }	/* end of switch */
   *row = cur_row;
   *col = cur_col;
}/* sl_cons() */

/************************************************************************
*									*
* 	void order_init_ref_tab(IS)						*
*	initialize the reference table: ref_tab[] which is indexed 	*
*	by the did of symbols, productions, and attributes.		*
*									*
************************************************************************/

void order_init_ref_tab (IS) AttrEval IS;
{
   SEQDef x;
   SEQAttrdef y;
   Def def;
   Attrdef attrdef;
   int did, i, j;
   int pos;
   int sid;
   int row_num, col_num;

   ref_tab =
     (ALLENTRIES *) Allocate
         (__FILE__,__LINE__,(ord_max_did + 1) * sizeof(ALLENTRIES));

   /* enter information in ref_tab */
   for (did = 0; did <= ord_max_did; did++)
      ref_tab[did].etag = EMPTY;

   min_entry = 99999;
   max_entry = 0;
   did = 0;

   foreachinSEQDef(IS->defseq, x, def)
   {
      switch (typeof(def))
      {
      case KSymb:
	 did = def.VSymb->did;
	 ref_tab[did].etag = SYMB;
	 ref_tab[did].entry.symb.symb_def = def.VSymb;
	 ref_tab[did].entry.symb.hddown = NULL;
#ifndef GORTO
	 ref_tab[did].entry.symb.ds = (BITMATRIX) NULL;
	 ref_tab[did].entry.symb.init_ds = (BITMATRIX) NULL;
         ref_tab[did].entry.symb.changed = TRUE;
	 ref_tab[did].entry.symb.cyclic = FALSE;
#else
	 ref_tab[did].entry.symb.ds = (DEP_MATRIX) NULL;
	 ref_tab[did].entry.symb.ds_detail = (DET_MATRIX) NULL;
	 ref_tab[did].entry.symb.attr_num = 0;
	 ref_tab[did].entry.symb.part_num = 0;
	 ref_tab[did].entry.symb.state = 0;
	 ref_tab[did].entry.symb.first_attr = (ATTRENTRY*) NULL;
	 ref_tab[did].entry.symb.last_attr = (ATTRENTRY*) NULL;
	 ref_tab[did].entry.symb.length = 0;
	 ref_tab[did].entry.symb.sar = (SAR*) NULL;
#endif
	 break;

      case KProd:
	 did = def.VProd->did;
	 ref_tab[did].etag = PROD;
	 ref_tab[did].entry.prod.prod_def = def.VProd;
	 ref_tab[did].entry.prod.hdright = NULL;
#ifdef GORTO
	 ref_tab[did].entry.prod.visitseq = (VSPTR) NULL; 
	 ref_tab[did].entry.prod.check_col = 0; 
	 ref_tab[did].entry.prod.check_row = 0; 
	 ref_tab[did].entry.prod.state = 0;
	 ref_tab[did].entry.prod.par = (PAR*) NULL;
#endif
	 break;
      }	/* switch */

      if (max_entry < did)
	 max_entry = did;
      if (min_entry > did)
	 min_entry = did;

      if (typeof(def) == KSymb)
      {

	 /* extract the attribute definitions of this symbol and enter them
	  * into ref_tab, allocating space for init_ds and ds, and initialize
	  * them. */

	 pos = 0;
	 sid = did;	/* save the did of this symbol */
	 foreachinSEQAttrdef(def.VSymb->attrs, y, attrdef)
	 {
	    did = attrdef->did;
	    ref_tab[did].etag = ATTR;
	    ref_tab[did].entry.attr.attr_def = attrdef;
	    ref_tab[did].entry.attr.pos = pos++;
	    ref_tab[did].entry.attr.bottomup = 0;
	    ref_tab[did].entry.attr.part = 0; 
	    ref_tab[did].entry.attr.symbdid = sid;
	    if (max_entry < did)
	       max_entry = did;
	    if (min_entry > did)
	       min_entry = did;
	 }
	 /* enter the number of attributes of this symbol */

#ifndef GORTO
         ref_tab[sid].entry.symb.attr_num = pos;
	 if (pos)
	 {
	    /* allocating space for init_ds and ds */
	    /* the extra  row is used to compute the transitive and induced
	     * graphs	   */

	    ref_tab[sid].entry.symb.init_ds =
	       (BITMATRIX) Allocate
	          (__FILE__,__LINE__,sizeof(BITVECTOR) * (1 + pos));
	    ref_tab[sid].entry.symb.ds =
	       (BITMATRIX) Allocate
	          (__FILE__,__LINE__,sizeof(BITVECTOR) * (1 + pos));

	    for (i = 0; i < 1 + pos; i++)
	    {
	       ref_tab[sid].entry.symb.init_ds[i] =
		  (BITVECTOR) Allocate
		     (__FILE__,__LINE__,
		      sizeof(unsigned int) * ((pos - 1) / WORD_LENGTH + 1));
	       ref_tab[sid].entry.symb.ds[i] =
		  (BITVECTOR) Allocate
		      (__FILE__,__LINE__,
		       sizeof(unsigned int) * ((pos - 1) / WORD_LENGTH + 1));
	    }
	    /* initialize init_ds  and ds */

	    for (i = 0; i < 1 + pos; i++)
	       for (j = 0; j < (pos - 1) / WORD_LENGTH + 1; j++)
	       {
		  ref_tab[sid].entry.symb.init_ds[i][j] = 0;
		  ref_tab[sid].entry.symb.ds[i][j] = 0;
	       }
	 }
#else
         ref_tab[sid].entry.symb.attr_num = pos;
	 if (pos)
	 {
	    ref_tab[sid].entry.symb.state = S_CHANGED;

	    /* allocating space for init_ds and ds */
	    /* the extra  row is used to compute the transitive and induced
	     * graphs	   */

	    ref_tab[sid].entry.symb.ds =
	       (DEP_MATRIX) Allocate
	               (__FILE__,__LINE__,
		        sizeof(DEP_VECTOR) * (1 + pos));
	    ref_tab[sid].entry.symb.ds_detail =
	       (DET_MATRIX) Allocate
	               (__FILE__,__LINE__,
		        sizeof(DET_VECTOR) * (1 + pos));

	    for (i = 0; i < 1 + pos; i++)
	    {
	       ref_tab[sid].entry.symb.ds[i] =
		  (DEP_VECTOR) Allocate
		       (__FILE__,__LINE__,
		        sizeof(DEPENDENCY) * (1 + pos));
	       ref_tab[sid].entry.symb.ds_detail[i] =
		  (DET_VECTOR) Allocate
		       (__FILE__,__LINE__,
		        sizeof(DETAIL) * (1 + pos));
	       for (j = 0; j < 1 + pos; j++)
		  ref_tab[sid].entry.symb.ds[i][j] = 0;
	    }
	 }
#endif

      } else if (typeof(def) == KProd)
      {

	 /* construct the symbol list, allocating space for init_dp, and
	  * initialize init_dp. this implementation is based on the fact that
	  * in the input file "exp_idl", symbol definitions come before
	  * productions */
#ifndef GORTO
	 ref_tab[did].entry.prod.changed = TRUE;
	 ref_tab[did].entry.prod.cyclic = FALSE;
#else
	 ref_tab[did].entry.prod.state = S_CHANGED;
	 ref_tab[did].entry.prod.vs = (VSINFO *) NULL;
#endif
	 ref_tab[did].entry.prod.visitseq = NULL;

	 /* build the symbol list */
	 sl_cons(did, &row_num, &col_num);


	 /* allocating space for init_dp and dp, the last row of init_dp is
	  * used to check the consistency and completeness of the attribute
	  * grammar and the space is freed afterwards.  */

#ifndef GORTO
	 ref_tab[did].entry.prod.init_dp =
	    (BITMATRIX) Allocate(__FILE__,__LINE__,sizeof(BITVECTOR) * (1 + row_num));
	 ref_tab[did].entry.prod.dp =
	    (BITMATRIX) Allocate(__FILE__,__LINE__,sizeof(BITVECTOR) * (1 + row_num));
	 for (i = 0; i < row_num + 1; i++)
	 {
	    ref_tab[did].entry.prod.init_dp[i] =
	       col_num ?
	       (BITVECTOR) Allocate(__FILE__,__LINE__,sizeof(unsigned int) * col_num)
	       : (BITVECTOR) NULL;
	    ref_tab[did].entry.prod.dp[i] =
	       col_num ?
	       (BITVECTOR) Allocate(__FILE__,__LINE__,sizeof(unsigned int) * col_num)
	       : (BITVECTOR) NULL;
	 }

	 ref_tab[did].entry.prod.check_row = row_num;
	 ref_tab[did].entry.prod.check_col = col_num - 1;

	 /* initialize init_dp and dp */
	 for (i = 0; i <= row_num; i++)
	    for (j = 0; j < col_num; j++)
	    {
	       ref_tab[did].entry.prod.init_dp[i][j] = 0;
	       ref_tab[did].entry.prod.dp[i][j] = 0;
	    }
#else
	 ref_tab[did].entry.prod.dp =
	    (DEP_MATRIX) Allocate
	           (__FILE__,__LINE__,
		    sizeof(DEP_VECTOR) * (1 + row_num));
	 ref_tab[did].entry.prod.dp_detail =
	    (DET_MATRIX) Allocate
	           (__FILE__,__LINE__,
		    sizeof(DET_VECTOR) * (1 + row_num));
	 for (i = 0; i < row_num + 1; i++)
	 {
	    ref_tab[did].entry.prod.dp[i] =
	       (DEP_VECTOR) Allocate
	           (__FILE__,__LINE__,
		    sizeof(DEPENDENCY) * (1 + row_num));
	    ref_tab[did].entry.prod.dp_detail[i] =
	       (DET_VECTOR) Allocate
	           (__FILE__,__LINE__,
		    sizeof(DETAIL) * (1 + row_num));
	    for (j = 0; j < row_num + 1; j++)
	       ref_tab[did].entry.prod.dp[i][j] = 0;
	 }
	 /* kalle: why using row_num instead of col_num ???? */
	 ref_tab[did].entry.prod.check_row = row_num;
	 ref_tab[did].entry.prod.check_col = col_num - 1;

	 ref_tab[did].entry.prod.vs = (VSINFO *) NULL;
#endif
         if (row_num - 1 > MaxRuleAttrs)
	    MaxRuleAttrs = row_num - 1;
      }
   }

/* enter a reference to the computation sequence of each RULE: */
  { SEQAttribution x; Attribution attribution;
    foreachinSEQAttribution(IS->attrrules, x, attribution)
      ref_tab[attribution->prodid].entry.prod.computations =
         attribution->attrrules;
  }
}/* order_init_ref_tab() */

void order_finl_ref_tab()
{
}


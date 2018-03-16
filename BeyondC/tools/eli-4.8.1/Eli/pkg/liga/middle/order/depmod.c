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
/* $Id: depmod.c,v 1.3 1997/08/29 09:16:01 peter Exp $*/

#include "reftab.h"

#include "depmod.h"

/* imported from Gorto: */
extern short graphstate_hint;

#define sgl 0x00000001

SLNODE *GetSymbOfProd (pid, sno) int pid, sno;
{ SLNODE *symptr = ref_tab[pid].entry.prod.hdright;
  int i = 0;
  while (symptr && i++ < sno)
    symptr = symptr->right;
  return symptr;
}

int DPAttrIsDefined (prodid, symptr, attrid)
	int prodid; SLNODE *symptr; int attrid;
{
#ifndef GORTO
 return
  (ref_tab[prodid].entry.prod.init_dp
	[ref_tab[prodid].entry.prod.check_row]
	[symptr->start_col + ref_tab[attrid].entry.attr.pos / WORD_LENGTH]
		  & sgl << (ref_tab[attrid].entry.attr.pos % WORD_LENGTH));
#else
 return
  (ref_tab[prodid].entry.prod.dp
	[ref_tab[prodid].entry.prod.check_row]
	[symptr->start_row + ref_tab[attrid].entry.attr.pos]);
#endif
}

void DPAttrSetDefined (prodid, symptr, attrid)
	int prodid; SLNODE *symptr; int attrid;
{
#ifndef GORTO
  ref_tab[prodid].entry.prod.init_dp
	[ref_tab[prodid].entry.prod.check_row]
	[symptr->start_col + ref_tab[attrid].entry.attr.pos / WORD_LENGTH]
		  |= sgl << (ref_tab[attrid].entry.attr.pos % WORD_LENGTH);
#else
  ref_tab[prodid].entry.prod.dp
	[ref_tab[prodid].entry.prod.check_row]
	[symptr->start_row + ref_tab[attrid].entry.attr.pos]
		= 1;
#endif
}

void DPSetDepend
  (prodid, tosymptr, tosymatno, fromsymptr, fromsymatno, kind, line)
	int prodid;
	SLNODE *tosymptr; int tosymatno;
	SLNODE *fromsymptr; int fromsymatno;
	int kind; /* dependency kind for non-gorto: 1 == direct */
	int line; /* source line */
{ PRODENTRY *prod = &ref_tab[prodid].entry.prod;
  int torow = tosymptr->start_row + tosymatno;
  
#ifndef GORTO
  int col_word, col_bit;
  col_word = fromsymptr->start_col + fromsymatno / WORD_LENGTH;
  col_bit = fromsymatno % WORD_LENGTH;

  if (!(prod->dp [torow] [col_word] & (0x1 << col_bit)))
  { if (kind == 1)
      prod->init_dp [torow] [col_word] |= sgl << col_bit;
    prod->dp [torow] [col_word] |= sgl << col_bit;
    prod->changed = TRUE;
  }
#else
  int fromcol = fromsymptr->start_row + fromsymatno;
  if (!(prod->dp[torow][fromcol]))
  { prod->dp [torow][fromcol] |= graphstate_hint;
    prod->dp_detail [torow][fromcol].direct.row = line;
    prod->state |= S_CHANGED;
  }
#endif
}

int DPDependson (pid, tosymptr, tosymatno, fromsymptr, fromsymatno)
	int pid, tosymatno, fromsymatno;
	SLNODE *tosymptr, *fromsymptr;
{
  return
#ifndef GORTO
    ref_tab[pid].entry.prod.dp
	[tosymatno + tosymptr->start_row]
	[fromsymatno / WORD_LENGTH + fromsymptr->start_col]
    & (0x1 << (fromsymatno % WORD_LENGTH));
#else
    ref_tab[pid].entry.prod.dp
	[tosymatno + tosymptr->start_row]
	[fromsymatno + fromsymptr->start_row];
#endif
}

int DSDependson (sid, tosymatno, fromsymatno)
	int sid, tosymatno, fromsymatno;
{ SYMBENTRY *symb = &ref_tab[sid].entry.symb;
#ifndef GORTO
  return (symb->ds[tosymatno][fromsymatno / WORD_LENGTH]
	  & (0x1 << (fromsymatno % WORD_LENGTH)));
#else
  return (symb->ds[tosymatno][fromsymatno]);
#endif
}

void DSSetDepend (sid, tosymatno, fromsymatno)
	int sid, tosymatno, fromsymatno;
{ SYMBENTRY *symb = &ref_tab[sid].entry.symb;

  if (DSDependson (sid, tosymatno, fromsymatno))
     return;
#ifndef GORTO
  symb->ds[tosymatno][fromsymatno / WORD_LENGTH] |=
     0x1 << fromsymatno % WORD_LENGTH;
  symb->changed = TRUE;
#else
  symb->ds[tosymatno][fromsymatno] |= graphstate_hint;
  symb->state |= S_CHANGED;
#endif
}

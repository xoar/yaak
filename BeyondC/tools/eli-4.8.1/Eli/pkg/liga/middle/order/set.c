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
/* $Id: set.c,v 4.2 1997/08/29 09:16:01 peter Exp $ */
static char rcs_id[] = "$Id: set.c,v 4.2 1997/08/29 09:16:01 peter Exp $";

/********************************************************
*       Module  : set.c                                 *
*       Version : 1.0					*
*       Author  : Jiyang Liu				*
*	contains functions for set maunipulations	*
********************************************************/

/* Angepasst zur Anbindung an GORTO (Graphical Order Tool). Alle Aenderungen
 * sind mit #ifdef GORTO gekennzeichnet.
 * 
 * 26.04.90	Volker Niepel */

#include "allocate.h"

#include "set.h"

#define MAXBITNO ((sizeof(unsigned int)*8)-1)
#define sgl 0x00000001

/* ASSERT: for any function the argument maxwordno >= 0.
   maxwordno is the graetest word index of the set.
*/

/*******************************************/
/* Functions for both gorto and non-gorto: */

/********************************************************
*	bool isemptyset(s, maxwordno)			*
*       test whether set s is empty			*
********************************************************/

bool isemptyset (s, maxwordno)
   BITVECTOR s; int maxwordno;
{
   int word;
   for (word = 0; word <= maxwordno; word++)
      if (s[word] != 0)
	 return (FALSE);

   return (TRUE);
}/* isemptyset() */

/********************************************************
*  bool issubset (s1, s2, maxwordno)			*
*  test if s1 is a subset of s2. maxwordno is the  	*
*  largest word number of the two bit vectors		*
*  restriction: subset only tests the subset 		*
*  relation of two bitvectors with identical length	*
********************************************************/

bool issubset (s1, s2, maxwordno)
   BITVECTOR s1, s2; int maxwordno;
{
   int word, bit;

   for (word = 0; word <= maxwordno; word++)
      for (bit = 0; bit <= MAXBITNO; bit++)
	 if ((s1[word] & (sgl << bit)) && !(s2[word] & (sgl << bit)))
	    return (FALSE);

   return (TRUE);
}/* issubset() */

/********************************************************
*  bool ismemberset (b, w, s)                  		*
*  test if bit b in word w of set s is one.		*
********************************************************/

bool ismemberset (b, w, s) int b, w; BITVECTOR s;
{
   if (s[w] & (sgl << b))
      return (TRUE);
   else
      return (FALSE);
}/* ismemberset() */

/********************************************************
*  void addtoset (b, w, s)                              *
*  turn bit b in word w of set s into one.		*
********************************************************/

void addtoset (b, w, s) int b, w; BITVECTOR s;
{
   s[w] |= (sgl << b);
}/* addtoset() */

/********************************************************
*  void delfromset (b, w, s)                            *
*  turn bit b in word w of set s into zero.             *
********************************************************/

void delfromset (b, w, s) int b, w; BITVECTOR s;
{
   s[w] &= ~(sgl << b);
}/* delfromset() */


/********************************************************
*  BITVECTOR mkemptyset (maxwordno)                     *
*  allocate space for a new set and initialize it to    *
*  empty, return the pointer to it.			*
********************************************************/

BITVECTOR mkemptyset (maxwordno) int maxwordno;
{
   int word;
   BITVECTOR s;

   s = (BITVECTOR) Allocate
        (__FILE__,__LINE__,sizeof(unsigned int) * (maxwordno + 1));

   for (word = 0; word <= maxwordno; word++)
      s[word] = 0;

   return (s);
}/* mkemptyset() */

/********************************************************
*  void copyset (source, target, maxwordno)             *
*  copy set source to set target.			*
*  restriction: the two sets must be of equal size.	*
********************************************************/

void copyset(source, target, maxwordno)
   BITVECTOR source, target; int maxwordno;
{
   int word;
   for (word = 0; word <= maxwordno; word++)
      target[word] = source[word];
}/* copyset() */

/********************************************************
*  void unionset (source, target, maxwordno)            *
*  compute the union of the two sets source and target  *
*  and the result is in set target.			*
********************************************************/

void unionset(source, target, maxwordno)
   BITVECTOR source, target; int maxwordno;
{
   int word;
   for (word = 0; word <= maxwordno; word++)
      target[word] |= source[word];
}/* unionset() */

/********************************************************
*  void diffset (source, target, maxwordno)             *
*  target <= target - source 				*
********************************************************/

void diffset(source, target, maxwordno)
   BITVECTOR source, target; int maxwordno;
{
   int word, bit;
   for (word = 0; word <= maxwordno; word++)
      for (bit = 0; bit <= MAXBITNO; bit++)
	 if (source[word] & (sgl << bit))
	    target[word] &= ~(sgl << bit);
}/* diffset() */

#ifdef GORTO

/*************************************************************
   The functions dep_is_subset, copy_dep_to_set, dep_unionset
   are to be used only in the Gorto variant to access the
   Gorto specific data structure
*/

#include "reftab.h"

/********************************************************
*  bool dep_is_subset (s1, s2, prod)			*
********************************************************/

bool dep_is_subset(s1, s2, prod)
   DEP_VECTOR s1;
   BITVECTOR s2;
   PRODENTRY *prod;
{
   SLNODE *nd;
   int atno, atnum;
   DEPENDENCY *dep;

   for (nd = prod->hdright; nd != NULL; nd = nd->right)
   {
      atnum = ref_tab[nd->sid].entry.symb.attr_num;
      dep = &s1[nd->start_row];
      for (atno = 0; atno < atnum; atno++)
      {
	 if (*dep && !(s2[nd->start_col + atno / WORD_LENGTH] &
		       sgl << atno % WORD_LENGTH))
	    return (FALSE);
	 dep++;
      }
   }
   return (TRUE);
}/* dep_is_subset() */

/********************************************************
*  void copy_dep_to_set (source, target, prod)		*
********************************************************/

void copy_dep_to_set (source, target, prod)
   DEP_VECTOR source;
   BITVECTOR target;
   PRODENTRY *prod;
{
   SLNODE *nd;
   int atno, atnum;
   DEPENDENCY *dep;

   for (atno = 0; atno <= prod->check_col; atno++)
      target[atno] = 0;

   for (nd = prod->hdright; nd != NULL; nd = nd->right)
   {
      atnum = ref_tab[nd->sid].entry.symb.attr_num;
      dep = &source[nd->start_row];
      for (atno = 0; atno < atnum; atno++)
      {
	 if (*dep)
	    target[nd->start_col + atno / WORD_LENGTH] |=
	       sgl << atno % WORD_LENGTH;
	 dep++;
      }
   }
}/* copy_dep_to_set() */


/********************************************************
*  void dep_unionset (source, target, prod)		*
********************************************************/

void dep_unionset (source, target, prod)
   DEP_VECTOR source;
   BITVECTOR target;
   PRODENTRY *prod;
{
   SLNODE *nd;
   int atno, atnum;
   DEPENDENCY *dep;

   for (nd = prod->hdright; nd != NULL; nd = nd->right)
   {
      atnum = ref_tab[nd->sid].entry.symb.attr_num;
      dep = &source[nd->start_row];
      for (atno = 0; atno < atnum; atno++)
      {
	 if (*dep)
	    target[nd->start_col + atno / WORD_LENGTH] |=
	       sgl << atno % WORD_LENGTH;
	 dep++;
      }
   }
}/* dep_unionset() */
#endif


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
/* $Id: ProdIter.h,v 1.1 1999/08/05 13:07:23 uwe Exp $ */

#ifndef PRODITER
#define PRODITER

/*=================================================
  Iterator module for stepping through productions
  =================================================*/

#include "global.h"
#include "LIGA.h"

#if defined(__STDC__) || defined(__cplusplus)
extern int HasMoreEntities (SEQEntity *iter);
/* returns false iff the iterator has reached the end 
   of the production */
#else
extern int HasMoreEntities ();
#endif

#if defined(__STDC__) || defined(__cplusplus)
extern void NextEntity 
/* increments the iterator to the next symbol;
   a call has no effect if HasMoreEntities yields false */
  (SEQEntity *iter,  /* travels through the sequence */
   Entity *ent,      /* holds the current Entity */
   int *isGen,       /* true iff the current Symbol is a tree insertion */
   int *isNonLit,    /* true iff the current Literal is non-literal terminal */
   char **nonLitType /* the type name of a non-literal terminal */
  );
#else
extern void NextEntity ();
#endif

#if defined(__STDC__) || defined(__cplusplus)
extern int GetIndexInProd (Prod prod, Entity thisEnt);
/* determine the index of a symbol occurrences in a production */
/* returns 0 if the production has exactly one occurrence of 
             the symbol thisEnt
   returns n if the production has more than one occurrence of
             the symbol thisEnt, and thisEnt is the n-th occurrence

   thisEnt is an arbitrary nonterminal or terminal occurrence
   of the right-hand side of the production prod.

   In case of a nonterminal the left-hand side is considered
   when counting occurrences.
*/
#else
extern int GetIndexInProd ();
#endif
#endif






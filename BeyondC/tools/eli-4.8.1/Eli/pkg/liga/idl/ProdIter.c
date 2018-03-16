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
#include <string.h>

#include "ProdIter.h"
#include "LIGAMacros.h"

/*=================================================
  Iterator module for stepping through productions

  The right-hand side of a production (rhsOfProd) is 
  a sequence of type SEQEntity. (The left-hand side symbol 
  is part of the production definition - lhsOfProd.)

  Each Entity is a Unit that has coordinate components
  rowOfUnit, colOfUnit.

  Each Unit is either a
  Symbol with a didOfSymbol representing a nonterminal or a
  Literal with strOfLiteral representing a literal terminal.

  A Literal with an empty string is used as a MARKER for
  2 purposes:

  a. mark a tree insertion symbol
     X ::= u $ G v
     ...u MARKER Symbol(G) v...

  b. mark a non-literal terminal
     X ::= u Ident v
     ...u MARKER Literal("Ident") Literal("int") v...
     The name of the non-literal terminal is followed
     by its type name.
*/

#if defined(__STDC__) || defined(__cplusplus)
int HasMoreEntities (SEQEntity *iter)
#else
int HasMoreEntities (iter) SEQEntity *iter;
#endif
{ return *iter != NULL; }

#if defined(__STDC__) || defined(__cplusplus)
void NextEntity 
/* a call has no effect if HasMoreEntities yields false */
  (SEQEntity *iter,  /* travels through the sequence */
   Entity *ent,      /* holds the current Entity */
   int *isGen,       /* true iff the current Symbol is a tree insertion */
   int *isNonLit,    /* true iff the current Literal is non-literal terminal */
   char **nonLitType /* the type name of a non-literal terminal */
  )
#else
void NextEntity (iter, ent, isGen, isNonLit, nonLitType)
   SEQEntity *iter;
   Entity *ent;    
   int *isGen;     
   int *isNonLit;  
   char **nonLitType;
#endif
{ Literal lit; char *strg; Entity typeEnt;

  if (*iter == NULL) return;
  retrievefirstSEQEntity(*iter, (*ent));
  *iter = (*iter)->next;

  if (typeof(*ent) == KSymbol)
  { *isGen = 0; return; } /* a nonterminal */

  lit = EntityToLiteral((*ent));
  strg = strOfLiteral (lit);
  if (strlen(strg) != 0)
  { *isNonLit = 0; return; } /* a literal terminal */

  /* we found a marker; skip it: */
  retrievefirstSEQEntity(*iter, (*ent));
  *iter = (*iter)->next;

  if (typeof(*ent) == KSymbol)
  { *isGen = 1; return; } /* a tree insertion symbol */

  /* it is a non-literal terminal; get its type: */
  retrievefirstSEQEntity(*iter, typeEnt);
  *iter = (*iter)->next;

  *isNonLit = 1;
  lit = EntityToLiteral(typeEnt);
  *nonLitType = strOfLiteral (lit);
                          /* a non-literal terminal */
}
/* end of production iterator */
/*====================================================*/

#if defined(__STDC__) || defined(__cplusplus)
int GetIndexInProd (Prod prod, Entity thisEnt)
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
int GetIndexInProd (prod, thisEnt) Prod prod; Entity thisEnt;
#endif
{ int thisOcc = 0;   /* the ordinal number of the occurrence of thisEnt */
  int totalOcc = 0;  /* the total number of occurrences of thisEnt */
  int isSymb = typeof (thisEnt) == KSymbol; 
  Symbol thisSymb; Literal thisLit;
  SEQEntity ents; Entity ent; int isGen, isNonLit; char *typename;

  if (isSymb) 
  { thisSymb = EntityToSymbol (thisEnt);
    if (didOfSymbol (thisSymb) == lhsOfProd (prod))
       totalOcc = 1;
  } else
    thisLit = EntityToLiteral(thisEnt);
   
  ents = rhsOfProd (prod);
  while (HasMoreEntities (&ents))
  { NextEntity (&ents, &ent, &isGen, &isNonLit, &typename);
    if (typeof (ent) == KSymbol)
    { if (isSymb)
      { Symbol symb = EntityToSymbol (ent);
        if (didOfSymbol (symb) == didOfSymbol (thisSymb))
        { totalOcc++;
          if (rowOfSymbol (symb) == rowOfSymbol (thisSymb) &&
              colOfSymbol (symb) == colOfSymbol (thisSymb))
             thisOcc = totalOcc;
	}
      }
    } else
    if (typeof (ent) == KLiteral)
    { if (!isSymb)
      { Literal lit = EntityToLiteral(ent);
        if (strcmp (strOfLiteral(lit), strOfLiteral(thisLit)) == 0)
        { totalOcc++;
          if (rowOfLiteral (lit) == rowOfLiteral (thisLit) &&
              colOfLiteral (lit) == colOfLiteral (thisLit))
             thisOcc = totalOcc;
	}
      }
    }
  }
  if (totalOcc == 1) return 0; else return thisOcc;
}/*GetIndexInProd*/
/*======================================================*/

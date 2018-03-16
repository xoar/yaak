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
/*$Id: exp_prot.c,v 4.2 1997/08/29 09:09:06 peter Exp $*/

#include <stdio.h>
#include <string.h>
#include "LIGA.h"
#include "LIGAMacros.h"
#include "liga_func.h"
#include "ligaconsts.h"
#include "expref.h"
#include "exp_types.h"
#include "lookup_idl.h"
#include "linemap.h"

#if defined (__cplusplus) || defined(__STDC__)
extern void prot_position(FILE *prot, int line, int col)
#else
extern void prot_position(prot, line, col)
FILE *prot;
int line;
int col;
#endif
{ fprintf(prot,"file %s, line %d:%d\n",
	  map_file(line), map_line(line), col);
}

#if defined (__cplusplus) || defined(__STDC__)
extern void prot_rule(FILE *prot, int pid)
#else
extern void prot_rule(prot, pid)
FILE *prot;
int pid;
#endif
{ Prod AProd;
  int lhs;
  int out_state=0;  /* state number used in rule output */
  SEQEntity TRrhs;
  Entity AEntity;
  (void) fprintf(prot,
		 "%s: ",
		 dnameOfProd(prodref(pid)));
  AProd = prodref(pid);
  lhs = lhsOfProd(AProd);
  fprintf(prot, "%s ::= ",
	  dnameOfSymb(symbref(lhs)));

  foreachinSEQEntity(rhsOfProd(AProd), TRrhs, AEntity)
    {
      switch (typeof(AEntity))
	{
	case KUnit:
	  {
            switch (typeof(EntityToUnit(AEntity)))
	      {
	      case KSymbol:
		  fprintf(prot, 
			  "%s ",
			  dnameOfSymb(symbref(didOfSymbol(EntityToSymbol(AEntity)))));

                  break;
	      case KLiteral:
		  /* if the literal is empty ('') the following 2 literals
                     denote a terminal symbol and its type.
                     for rule output only the middle element of this triple
                     is relevant */ 
		  if (strlen(strOfLiteral(EntityToLiteral(AEntity)))==0)
                  { 
		      /* empty string */
		      out_state = 2;
		  }
		  else if (out_state == 2)
		  { 
		      /* last literal was empty */
		      fprintf(prot, 
			      "%s ", 
			      strOfLiteral(EntityToLiteral(AEntity)));
		      out_state = 1;
		  }
		  else if (out_state == 1)
		  { 
		      /* last literal was the terminal name */
		      out_state = 0;
		  }
		  else if (out_state==0)
		  { 
		      /* normal state */
		      fprintf(prot, 
			      "'%s' ", 
			      strOfLiteral(EntityToLiteral(AEntity)));
		  }
		  break;
	      }
            break;
	  }	  
	default:;
	} /* switch Entity */
    }    /* foreachinSEQEntity */
  fprintf(prot,"\n");
}


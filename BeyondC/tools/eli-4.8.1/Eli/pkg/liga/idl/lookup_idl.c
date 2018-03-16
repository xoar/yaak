/* $Id: lookup_idl.c,v 4.1 1997/08/29 08:26:49 peter Exp $ */
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

/****************************************
*					*
*	Version : 1.0			*
*					*
*	Module  : lookup_idl.c		*
*					*
*					*
*****************************************/


/****************************************
* includes				*
*****************************************/

#include "lookup_idl.h"

/****************************************
* global variables			*
*****************************************/

all_defs *array_of_defs;	/* array allocated dynamically */

/****************************************
* init_did_table			*
*****************************************/

int 
init_did_table(DS)
   SEQDef DS;
{

   /* builds the table of dids; returns the number of definitions */

   SEQDef x;
   Def def;
   SEQAttrdef y;
   Attrdef attrdef;
   int did, max_def = 0;

   foreachinSEQDef(DS, x, def)
   {

      switch (typeof(def))
      {

      case KTypedef:
	 did = def.VTypedef->did;
	 break;
      case KSymb:
	 did = def.VSymb->did;
	 break;
      case KProd:
	 did = def.VProd->did;
	 break;
      case KChain:
	 did = def.VChain->did;
	 break;

      };	/* of case */

      /* find out the highest did */

      if (max_def < did)
	 max_def = did;

      /* if def is a Symb, retrieve its attributes */

      if (typeof(def) == KSymb)
      {

	 foreachinSEQAttrdef((def.VSymb)->attrs, y, attrdef)
	 {
	    if (max_def < attrdef->did)
	       max_def = attrdef->did;
	 };

      };

   };

   array_of_defs= (all_defs*) malloc((max_def+1)* sizeof(all_defs));

   /* initialize array by some reasonable value:*/
   { Typedef tdef;
     tdef = NTypedef;
     tdef->did = 0;
     tdef->dname = "Unknown";
     tdef->row = 1;
     tdef->col = 1;
     tdef->listedto = 0;
     tdef->extname = "";
     def.VTypedef = tdef;
     for (did=0; did<=max_def; did++) array_of_defs[did].def = def;
   }
   foreachinSEQDef(DS, x, def)
   {

      switch (typeof(def))
      {

      case KTypedef:
	 did = def.VTypedef->did;
	 break;
      case KSymb:
	 did = def.VSymb->did;
	 break;
      case KProd:
	 did = def.VProd->did;
	 break;
      case KChain:
	 did = def.VChain->did;
	 break;

      };	/* of case */

      /* insert definition at its place */

      array_of_defs[did].def = def;

      /* if def is a Symb, retrieve its attributes */

      if (typeof(def) == KSymb)
      {

	 foreachinSEQAttrdef((def.VSymb)->attrs, y, attrdef)
	 {
	    array_of_defs[attrdef->did].attrdef = attrdef;
	 };

      };

   };

   return (max_def);
}


void free_did_table()
{ free(array_of_defs);
}

/****************************************
* lookup_def				*
*****************************************/

Def 
lookup_def(did)
{

   /* returns a pointer to the definition with id did */

   return (array_of_defs[did].def);
}


/****************************************
* lookup_attrdef			*
*****************************************/

Attrdef 
lookup_attrdef(did)
{

   /* returns a pointer to the attributedefinition with id did */

   return (array_of_defs[did].attrdef);
}

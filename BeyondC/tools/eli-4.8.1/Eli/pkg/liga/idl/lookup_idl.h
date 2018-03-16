/* $Id: lookup_idl.h,v 4.1 1997/08/29 08:26:49 peter Exp $ */
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

#ifndef LOOKUP_IDL_H
#define LOOKUP_IDL_H

/*********************************************
*                                            *
*       Version : 1.0                        *
*                                            *
*       Module  : lookup_idl.h               *
*                                            *
*                                            *
**********************************************/


/*********************************************
* includes                                   *
**********************************************/

#include "LIGA.h"
#include "LIGAMacros.h"


/*********************************************
* functions                                  *
**********************************************/

extern int init_did_table();
extern Def lookup_def();
extern Attrdef lookup_attrdef();
extern void free_did_table();

/*********************************************
* global variables and types                 *
**********************************************/

typedef union
{
   Def def;
   Attrdef attrdef;
} all_defs;

extern all_defs *array_of_defs;

#endif

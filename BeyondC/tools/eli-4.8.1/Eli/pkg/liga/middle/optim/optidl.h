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
/* $Id: optidl.h,v 4.3 1997/08/29 09:13:34 peter Exp $ */

/************************************************/
/* */
/* Version : 1.0				 */
/* */
/* Module  : optidl.h			 */
/* */
/* Contains global declarations		 */
/* */
/************************************************/

#include "eliproto.h"

/************************************************
* global variables and types			*
************************************************/

extern Attributes *attr_array;
typedef Can_Eval a_Can_Eval[MAX_VISITS];
extern a_Can_Eval *CE_array;
typedef Marked a_Marked[MAX_VISITS];
extern a_Marked *mark_array;
typedef Boolean a_Boolean[MAX_VISITS];
extern a_Boolean *visit_considered;
extern Boolean *eval_considered;

/************************************************/
/* functions                  */
/************************************************/

extern Symbols optim_MkSymbol( /* Symb, int */ );

extern Visits optim_MkVisit( /* int, int, int */ );

extern ANamesList GetAttrSpez( /* OptList, optoptflag */ );

extern Attribution GetAttribution( /* int */ );

extern Call GetAssign( /* SEQAttrrule, Eval */ );
extern Call GetCondition( /* SEQAttrrule, Eval */ );
extern Call MkCall( /* int, int */ );

extern Group MkGroup( /* Attributes, int */ );

extern SEQAttributes GetAttrsByName( /* SEQAttributes, AttrName, int */ );
extern SEQAttributes MkAttrList( /* no parameter */ );

extern Attributes MkAttribute( /* Attrdef, Symb */ );
extern Attributes GetAttrInstance( /* int, int, SEQAttributes */ );
extern Attributes GetAttrByName( /* String, String */ );
extern Attributes LookupAttribute( /* int */ );

extern Can_Eval MkCanEval( /* int, int */ );
extern Can_Eval LookupCE( /* int, int */ );

extern Marked LookupMark( /* int, int */ );

extern void InitLookupArrays( /* no parameters */ );
extern void InitEvalVisit( /* Can_Eval */ );
extern void ResetEvalVisit( /* Can_Eval */ );
extern void InitMarkArray( /* Can_Eval */ );
extern void ResetMarkArray( /* Can_Eval */ );
extern void InitAttrArray ELI_ARG((void));


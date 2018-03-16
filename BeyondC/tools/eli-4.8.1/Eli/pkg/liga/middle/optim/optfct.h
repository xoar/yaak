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

/* $Id: optfct.h,v 4.1 1997/08/29 09:13:34 peter Exp $ */

/************************************************/
/* */
/* Version : 1.0                          */
/* */
/* Module  : optfct.h                     */
/* */
/* Contains declarations of help routines */
/* for all other modules of liga.optim    */
/* */
/************************************************/



/************************************************/
/* functions                  */
/************************************************/

extern void InitOptimOptions( /* AttrEval */ );
extern void HandleOptimizeOption( /* AttrEval */ );
extern void HandleExpInclOption( /* Visit_Sequences */ );
extern void HandleVarListOption( /* Visit_Sequences */ );
extern void HandleStackListOption( /* Visit_Sequences */ );
extern void HandleTreeListOption( /* Visit_Sequences */ );

extern Boolean AttrInstanceInSet( /* int, int, SEQAttributes */ );
extern Boolean InSeqAttrs( /* SEQAttributes, int */ );
extern Boolean InSeqAction( /* SEQAction, Action */ );
extern Boolean NewInstance( /* Visit_Seq, Attributes */ );

extern int SymbId( /* Visit_Seq, int */ );
extern int ParentId( /* Visit_Seq */ );

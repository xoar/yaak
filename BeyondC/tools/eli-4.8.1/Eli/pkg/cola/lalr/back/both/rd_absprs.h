/*
** $Id: rd_absprs.h,v 1.3 1997/08/29 08:38:08 mjung Exp $
*/

/* (C) Copyright 1997 University of Paderborn */

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

/******************************************************************************/
/* filename: rd_absprs.h                      first edit   : 29 . 6 . 89      */
/* author  : Christian Zeitel                 last change  : 14 .11 . 89      */
/******************************************************************************/

/******************************** CONTENTS ************************************
*                                                                             *
*  This is the interface between the calling module build_copa and the        *
*  answering module rd_absprs.                                                *
*                                                                             *
******************************************************************************/

extern  readtype *rd_absprs(/* readtype pt_data; p_comar Comar_root;   */ 
			    /* absparsertype Abs_parser; char addinfo; */);

  /*   Optimizes the parsing-tables.
   *
   *   on entry-
   *      pt_data is uninitialized. It is the interfacevector to the 
   *      optimization.
   *      Comar_root contains the internal IDL-C-representation of the CFG
   *      after transformation from EBNF to BNF.
   *      Abs_parser contains the  internal IDL-C-representation of the abstract
   *      parser.
   *      If addinfo is not zero, additional information about the generating 
   *      process is printed to standard-output at various points. 
   *   on exit-
   *     *pt_data contains all important informations about the concrete parser.
   *      The value pt_data is returned.
   *   
   * 
   ***/  

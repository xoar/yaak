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

/*
** $Id: cmrprvdefs.h,v 1.3 1997/08/29 08:38:08 mjung Exp $
*/

/******************************************************************************/
/* filename: comarprivdefs.h                   first edit   : 23 . 5 . 89     */
/* author  : Christian Zeitel                  last  Change : 24 . 1 . 90     */
/******************************************************************************/

/******************************** CONTENTS *************************************
 *             								       *
 *  This header-file is the interface between the calling-module rd_absprs and *
 *  the answering-module  comarprivdefs. 				       *
 *        functions:  6(7)*  |  variables:  0  |  types:  0                    *
 *									       *
 *  (*: if name TESTOPT is set during compiling )			       *
 *                                           				       *
 *************************** FUNCTION DECLARATIONS ****************************/



extern  void Initadt_cpd(/*short *not, *non, *nop, p_cmar comar_root; */);

  /*  Initializes the module comarprivdefs and allocates storage for the 
   *  interface pt_data.
   *
   *   on entry-
   *      *not points to a uninitialized variable,
   *      *non points to a uninitialized variable,
   *      *nop points to a uninitialized variable.
   *      comar_root contains the root of the COMAR-datastructure.
   *   on exit-
   *      *not contains the number of terminals of the CFG
   *      *non contains the number of nonterminals of the CFG after translation 
   *      from EBNF to BNF.
   *      *nop contains the number of productions of the CFG after translation 
   *      from EBNF to BNF.
   *      stuctures have been built up to access on  symb- or def-entries of the
   *      COMAR-datastructure in O(1)-time via its sid or did.
   *
   ***/



extern  symb_entry Get_symbentry(/* short sid; */);

  /*  Returns the COMAR-symb_entry with sid-index sid.
   *
   *   on entry-
   *      sid contains the sid-index of a COMAR-symb_entry.
   *   on exit-
   *      the symb_entry with sid-value of sid is returned.
   * 
   ***/



extern  short Get_length(/* SEQunit rhs; */);

  /*  Returns the length of the righthandside of a production,
   *   on entry-
   *      rhs contains the unit-sequence of the righthandside of a production.
   *   on exit-
   *      the lentgh of the righthandside of this production is returned.
   *  
   ***/


#ifdef TESTOPT /* only compiled for controll-purposes */

extern  char *Get_prs(/* SEQunit rhs; short lhsdid; */);

  /*  Returns the symbolstring of a produktion.
   *
   *   on entry-
   *      rhs contains the unit-sequence of the righthandside of a production.
   *      lhsdid contains the lhsdid of the lefthandside nonterminal of this 
   *      production.
   *   on exit-
   *      a pointer to the symbolstring of a production is returned.
   *
   ***/

#endif



extern short *Get_rhs(/* SEQunit rhs; short length */);

  /*  Returns the righthandside of a production.
   *
   *   on entry-
   *      rhs contains the unit-sequence of the righthandside of a production.
   *      length contains the length of the righthandside in rhs.
   *   on exit-
   *      A not-COMAR-symbolsequence od rhs is returned. If length is zero,
   *      NULL is returned.
   *
   ***/




extern  short  Get_sxcode(/* def_entry termdef; */);

  /*  Returns the sxcode used by the scannergenerator for a terminal given
   *  by the COMAR-did termdef.
   *
   *   on entry-
   *      termdef contains a poinetr to a COMAR-definition-node
   *      of a terminal-symbol.
   *   on exit-
   *      the sxcode of the scannergenerator used for this terminal is returned.
   *
   ***/


extern  short Get_prodcode(/* def_entry proddef; */);

  /*  Returns the productioncode used by the semantic analysis for a production
   *  given by the COMAR-did proddef.
   *
   *   on entry-
   *      proddef contains a pointer to a COMAR-definition-node
   *      of a production.
   *   on exit-
   *      the productioncode of the semantic analysis for this production is
   *      returned. If this production belongs to the abstract Syntax, its 
   *      code has a negative sign.
   *
   ***/

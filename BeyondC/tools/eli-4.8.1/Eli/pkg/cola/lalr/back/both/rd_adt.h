/*
** $Id: rd_adt.h,v 1.3 1997/08/29 08:38:08 mjung Exp $
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
/* filename: rd_adt.h                          first edit   : 23 . 5 . 89     */
/* author  : Christian Zeitel                  last change  : 25 . 1 . 90     */
/******************************************************************************/

/****************************** CONTENTS ***************************************
 *  									       *
 * This header-file is the interface between the calling module rd_absprs and  *
 *  the answering module rd_adt.					       *
 *		functions:  16(20)*  |  variables:  0  |  types:  0	       *
 *									       *
 * (*: if name TESTOPT is set during compiling )			       *
 *									       *
 ************************* FUNCTION DECLARATIONS ******************************/



extern  readtype *Init_optif(/* readtype pt_data;         */
                             /* short not, non, nop, nos; */
                             /* char rhsinfo;             */);

  /*  Allocates store for interfacevector pt_data and initializes it.
   *
   *   on entry-
   *      pt_data has no store and is uninitialized.
   *      not contains the number of terminals of the CFG,
   *      non contains the number of nontermials of the CFG,
   *	  nop contains the number of productions of the CFG and
   *      nos contains the number of states of the abstract parser for the CFG.
   *      If rhsinfo = OFF, store for 14 pointers to short is allocated for 
   *      pt_data; if rhsinfo = ON, store for 14+p pointers is allocated for
   *      pt_data, where p is the number of productions.
   *      
   *   on exit-
   *      store is allocted for pt_data and pt_data is initialized. Returned is
   *      the pointer pt_data.
   *
   ***/
   

extern  void Initadt_rd(/* readtype pt_data; */);

  /*  Initializes module rd_adt.
   *    
   *   on entry-
   *      pt_data is pointer pointing to NULL. 
   *   on exit-
   *      The vector didconverter, local in module rd_adt, has been initialized,
   *      some components of pt_data are linked with local pointers in module
   *      rd_adt. If option TESTOPT is set during compiling, the controloutput- 
   *      file TESTOUT.bt is initialized.
   *
   ***/



extern  void Mk_termentry(/* short  sxcode, did; */);

  /*  Insert a terminalsymbol with scannerdefined sxcode sxcode and  COMAR-did
   *  did in module rd_adt.
   *
   *   on entry-
   *      sxcode contains the scannerdefined sxcode of a terminalsymbol.
   *      did contains the COMAR-did of this terminal.
   *   on exit-
   *      if lsx is the local sxcode of the terminal in module BUILDPRS,
   *      in rd_adt local exist local structures, in which lsx is assigned
   *      to did and which sxcode is assigned to lsx.
   *
   ***/




#ifdef TESTOPT /* only compiled for controll-purposes! */

extern  void Mk_termsymbentry(/* char *termsymb; */);
 
  /*  Inserts a terminalsymbol in its stringrepresentation into module rd_adt.
   *
   *   on entry-
   *      termsymb points to the terminals characterstring.
   *   on exit- 
   *      if lsx is the local sxcode of the terminal in module BUILDPRS,
   *      in rd_adt exists a local structure, in which termsymb is assigned 
   *      lsx.
   *
   ***/

#endif





extern  void Mk_skipentry(/* short  did; */);
  
 /*  Inserts a skipsymbol given by its COMAR-did into module rd_adt.
  *
  *   on entry-
  *      did contains the COMAR-did of the skip-terminalsymbol.
  *   on exit -
  *      if lsx is the local sxcode of the terminal in module BUILDPRS,
  *      in rd_adt exists  a local structure, in which the property
  *      IS_SKIPSYMBOL is assigned to lsx.
  *
  ***/





extern  void Mk_sepaentry(/* short  did; */); 

 /*  Inserts a sepasymbol given by its COMAR-did into module rd_adt.
  *
  *   on entry-
  *      did contains the COMAR-did of the sepa-terminalsymbol.
  *   on exit -
  *      if lsx is the local sxcode of the terminal in module BUILDPRS,
  *      in rd_adt exists  a local structure, in which the property
  *      IS_SEPASYMBOL is assigned to lsx.
  *
  ***/             




extern  void Mk_bracentry(/* short  did;  */);

  /*  Inserts a bracketsymbol given by its COMAR-did into module rd_adt.
   *
   *   on entry-
   *      did contains the COMAR-did of the bracket-terminalsymbol.
   *   on exit -
   *      if lsx is the local sxcode of the terminal in module BUILDPRS,
   *      in rd_adt exists  a local structure, in which the property
   *      IS_BRACKETSYMBOL is assigned to lsx.
   *
   ***/                            




extern  void Mk_stopentry(/*short did, *pt_dataentry; */ );

  /*  Inserts the local sxcode (in module BUILDPRS) of the parser-internal
   *  EOF-code  given by its COMAR-did into module rd_adt.
   *  
   *  on entry-
   *     did contains the COMAR-did of the parserinternal EOF-symbol,
   *     *pt_dataentry is undefined.
   *  on exit -
   *     *pt_dataentry contains the local sxcode of the parser-internal
   *     EOF-code in module BUILDPRS.
   *
   ***/




extern  void Mk_ntermentry(/* short did; */);

  /*  Inserts a nonterminal given by its COMAR-did into module rd_adt.
   *
   *   on entry-
   *      did contains the COMAR-did of the nonterminal.
   *   on exit-
   *      if lnc is the local code of the nonterminal in module BUILDPRS, 
   *      in rd_adt exists a local structure, in which did is assigned to 
   *      lnc.
   *
   ***/





#ifdef TESTOPT /* only compiled for test-purposes! */

extern void Mk_ntermsymbentry(/*char *ntermsymb; */);
 
  /*  Inserts a nonterminal given by its characterstring into module rd_adt.
   *
   *   on entry-
   *      ntermsymb points to the characterstring of the nonterminal.
   *   on exit-
   *      if lnc is the local code of the nonterminal in module BUILDPRS,
   *      in rd_adt exists a local structure, in which ntermsymb is assigned
   *      to lnc.
   *
   ***/

#endif





extern void Mk_prodentry(/* short  did, lhsdid, length, prodcode; */);

  /*  Inserts a production, given by its COMAR-did, its COMAR-did of the
   *  lefthandside nonterminal, its righthandside length and it productioncode
   *  used in the semantic analysis into module rd_adt.
   *  
   *   on entry-
   *      did contains the COMAR-did of the production,
   *      lhsdid contains the lhsdid of its lefthandside nonterminal,
   *      length contains thr length of its righthand side and
   *      prodcode contains the productioncode of this production used by
   *      the smenantic analysis.
   *   on exit-
   *      if lpc is the local code of the production in module BUILDPRS,
   *      in rd_adt exist local structures in which lpc is assignd to did
   *      and in which lhsdid, lentgh and prodcode are assigned lpc.
   *
   ***/



extern short Get_intprodcode(/* short did; */);
  
  /*  Returns the internal prodcode in module BUILDPRS for the production
   *  with COMAR-did did.
   *
   *   on entry-
   *      did contains the COMAR-did of the production.
   *   on exit-
   *      The internal Productioncode in module BUILDPRS for this production
   *      is returned.
   *
   ***/




#ifdef TESTOPT /* only compiled for test-purposes! */

extern  void Mk_pstrentry(/* char *prodstring; */);

  /*  Inserts a production given by its characterstring into module rd_adt.
   *  
   *   on entry-
   *      prodstring points to characterstring of the production.
   *   on exit- 
   *      the productionstring is printed to the "TESTOUT.bt"-file.
   ***/

#endif





extern  void Mk_rhsentry(/* short proddid; *rhsdisseq; */
                         /* readtype  pt_data;         */);

  /*  Inserts the didsequence of the righthandside of a production given
   *  by its COMAR-did into module rd_adt.
   *
   *   on entry-
   *      prodid contains the COMAR-did of a production.
   *      *rhsseq contains the COMAR-did-sequence of the righthandside-symbols
   *      of this production, pt_data is the interfacevector to optimization.
   *   on exit-
   *      the codes in rhsdidseq are converted to the internal codes for module
   *      BUILDPRS and the whole converted sequence is inserted in vector 
   *      pt_data.
   *
   ***/





extern  void Mk_errsymbentry(/* short  state, errsymbdid; */);

  /*  Inserts an errorsymbol of the continuation-automaton given by
   *  its COMAR-did which is assigned to a parser-state given by its 
   *  number into rd_adt.
   *
   *   on entry-
   *      state contains the number of the parser-state used by the
   *      IDL-structure of the abstract parser and errsymbdid contains the
   *      COMAR-did of the errorsymbol, belonging to that state.
   *   on exit-
   *      if lcd is the local code of the errorsymbol in module BUILDPRS, 
   *      in rd_adt exists a sturcture in which  lcd is assigned state.
   *
   ***/





extern  void Mk_shiftentry(/* short  state, gramsymb, nextstate; */);

  /*  Inserts the shiftentry of a parsertable given by a state, a grammarsymbol
   *  and the successor-state into rd_adt.
   *  
   *   on entry-
   *      state contains the number of the parser-state used by the
   *      IDL-structure of the abstract parser, 
   *      gramsymb contains the COMAR-did of the grammarsymbol (terminal or
   *      nonterminal!) and
   *      nextstate contains the number of the successorstate used by the
   *      IDL-structure of the abstract parser.
   *   on exit-
   *      in rd_adt exist vectors aliaised with the terminal- and 
   *      nonterminal-parsertable in interfacevector pt_data.
   *      If lcd is the local code for gramsymb in BUILTAB, the shiftentry
   *      is inserted at row-position state and collumn-position lcd in the 
   *      corresponding parsertable.
   *
   ***/





extern  void Mk_reduceentry(/* short state, gramsymb, rule; */);

  /*  Inserts the reduceentry of a parsertable given by a state, a grammarsymbol
   *  and the rulencode into module rd_adt.
   *  
   *   on entry-
   *      state contains the number of the parser-state used by the
   *      IDL-structure of the abstract parser,
   *      gramsymb contains the COMAR-did of the grammarsymbol (terminal or
   *      nonterminal!) and rule contains the COMAR-did or the rule.
   *   on exit-
   *      in rd_adt exist vectors aliaised with the terminal- and 
   *      nonterminal-parsertable in interfacevector pt_data.
   *      If lcd is the local code for gramsymb in BUILTAB, the reduceentry
   *      is inserted at row-position state and collumn-position lcd in the 
   *      corresponding parsertable.
   *
   ***/



    


extern  void Mk_shredentry(/* short state, gramsymb, rule; */); 

  /*  Inserts the shiftreduceentry of a parsertable given by a state, 
   *  a grammarsymbol and the rulencode into module rd_adt.
   *  
   *   on entry-
   *      state contains the number of the parser-state used by the
   *      IDL-structure of the abstract parser,
   *      gramsymb contains the COMAR-did of the grammarsymbol (terminal or
   *      nonterminal!) and rule contains the COMAR-did or the rule.
   *   on exit-
   *      in rd_adt exist vectors aliaised with the terminal- and 
   *      nonterminal-parsertable in interfacevector pt_data.
   *      If lcd is the local code for gramsymb in BUILTAB, the shiftreduceentry
   *      is inserted at row-position state and collumn-position lcd in the 
   *      corresponding parsertable.
   *
   ***/              





extern  void Mk_acceptentry(/* short state, gramsymb; */);

  /*  Inserts the acceptentry of a parsertable given by a state and  
   *  a grammarsymbol into module rd_adt.
   *  
   *   on entry-
   *      state contains the number of the parser-state used by the
   *      IDL-structure of the abstract parser and
   *      gramsymb contains the COMAR-did of the grammarsymbol (terminal or
   *      nonterminal!) .
   *   on exit-
   *      in rd_adt exist vectors aliaised with the terminal- and 
   *      nonterminal-parsertable in interfacevector pt_data.
   *      If lcd is the local code for gramsymb in BUILDPRS, the acceptentry 
   *      is inserted at row-position state and collumn-position lcd in the 
   *      corresponding parsertable.
   ***/





#ifdef TESTOPT /* only compiled for test-purposes! */

extern  void Write_tables( /* nix */ );

  /*  Prints all important data for the concrete parser in a readable form 
   *  on file TESTOUT.bt.
   *
   *   on entry- 
   *      all important data structures are initialized.
   *   on exit-
   *       all important datas for the concrete parser are printed out on 
   *       a file named "TESTOUT.bt"
   *
   ***/

#endif

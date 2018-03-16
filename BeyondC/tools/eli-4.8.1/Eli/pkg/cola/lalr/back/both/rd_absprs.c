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
** $Id: rd_absprs.c,v 1.5 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: rd_absprs.c,v 1.5 1997/08/29 08:38:08 mjung Exp $";

/******************************************************************************/
/* filename: rd_absprs.c                       first edit   :  8 . 6 . 89     */
/* author  : Christian Zeitel                  last  change : 25 .11 . 89     */
/******************************************************************************/

/******************************* INTRODUCTION **********************************
 *                                                                             *
 *  This module receives all informations which are important for constructing *
 *  a concrete parser. It collects them in a small datastructure which         *
 *  consists only of short-values or lists of short-values and passes this     *
 *  structure to the optimization.                                             *
 *                                                                             *
 *  INPUT: the following input is passed from  module build_copa :             *
 *  ------                                                                     *
 *     -empty interface-datastructure which is filled up with informations in  *
 *        this module and then passed to the optimization in vector *pt_data   *
 *     -internal representation of the IDL-C-structure of the                  *
 *        COMAR-datastructure of the CFG                                       *
 *     -internal representation of the IDL-C-structure of the abstract parser  *
 *     -option, if additional information about the state of the               *
 *        generation-process shall be printed on standardoutput in addinfo     *
 *                                                   			       *
 *                                                                             *
 *  OUTPUT: the vector *pt_data is passed to the optimization. It contains 14  *
 *  ------- fix entries with following meanings:                               *
 *                                                                             *
 *   *(*pt_data)[0]  :  number of terminalsymbols.                             *
 *    (*pt_data)[1]  :  the not-optimized terminal-parsertable                 *
 *    (*pt_data)[2]  :  vector to convert internal to external sxcode          *
 *   *(*pt_data)[3]  :  number of nonterminalsymbols                           *
 *    (*pt_data)[4]  :  the not-optimized nonterminal-parsertable              *
 *   *(*pt_data)[5]  :  number of productions                                  *
 *    (*pt_data)[6]  :  vector to assign a production the code of it's         *
 *                      lefthandside nonterminal                               *
 *    (*pt_data)[7]  :  vector to assign a production it's length              *
 *    (*pt_data)[8]  :  vector to convert internal to external productioncodes *
 *   *(*pt_data)[9]  :  number of states of the LALR(1)-stack-automaton        *
 *    (*pt_data)[10] :  continuaton-automaton which assigns a symbol to a state*
 *    (*pt_data)[11] :  symbols for an efficient error-recovery: skip-symbols, *
 *                      list separators or semantic brackets and the semantic- *
 *		        property for each terminal   	                       *
 *   *(*pt_data)[12] :  a pointer to the EOF-sxcode used by the parser 	       *
 *   *(*pt_data)[13] :  the external productioncode for the startproduction    *
 *                                                                             *
 *   *(*pt_data)[14] - *(*pt_data)[14+p] are sequences of the righthandsides   *
 *                      of all productions. p is the number of productions.    *
 *									       *
 ********************************* CONTENTS ************************************
 *                                                                             *
 *  The module rd_absprs consists of only one function called rd_absprs too.   *
 *  It communicates with two ADT over various functions, forming the           *
 *  interfaces to these ADT. Each ADT is canned in a single module.            *
 *  The header-files for these modules are:                                    *
 *                                                                             *
 *  comarprivdefs.h :datastructures for fast access to COMAR-data-objects      *
 *         rd_adt.h :datastuctures which would complicate rd_absprs too much   *
 *                                                                             *
 *  rd_absprs can be devided into three steps:                                 *
 *                                                                             *
 *   STEP 1: initialize the ADT-modules and allocate storage for the           *
 *   ------- interfacevector *pt_data.                                         *
 *                                                			       *
 *   STEP 2: walk through the IDL-C-COMAR-structure of the CFG and keep        *
 *   ------- the codes for terminal-symbols, nonterminalsymbols, productions   *
 *           and errorrecoverysymbol in special data-stuctures                 *
 *									       *
 *   STEP 3: walk through the IDL-C-COMAR-structure of the CFG and read the    *
 *   ------- righthand-sides of all productions				       *
 *                                                    			       *
 *   STEP 4: walk through the IDL-C-structure of the abstract parser and       *
 *   ------- insert the entries for terminal-,  nonterminal-parsertable        *
 *           and continuationautomaton into the corresponding datastructure    *
 *           of the interfacevector *pt_data.                                  *
 *                                                      		       *
 ********************************* INTERFACES **********************************
 *									       *
 *  There are two interfaces connecting rd_absprs and it's ADT-modules, which  *
 *  are pointed out above. Their exact functions are described in the          *
 *  corresponding .h- and .c -files .A short description is also given here:   *
 *    									       *
 *   rd_absprs <=> rd_adt : this interface contains 20 functions:              *
 *   --------------------                   				       *
 *									       *
 *    -Init_optif	 : allocates storage for interface-vector *pt_data and *
 *    			   initializes some values in this vector.             *
 *                                                                             *
 *    -Initadt_rd        : initializes the module rd_adt by setting initial    *
 *                         values for internal data-structures.                *
 *                                                                             *
 *    -Mk_termentry      : inserts the sxcode and the CMR-did of a terminal    *
 *                         into ADT-module rd_adt.                             *
 *									       *
 *    -Mk_termsymbentry  : inserts a termnial in its string-representation     *
 *                         into rd_adt. This function is only compiled,if the  *
 *                         name TESTOPT is set during compilation              *
 *									       *
 *    -Mk_skipentry      : inserts the CMR-did of a skip-terminal into rd_adt. *
 *									       *
 *    -Mk_sepaentry      : inserts the CMR-did of a sepa-terminal into rd_adt. *
 *									       *
 *    -Mk_bracentry      : inserts the CMR-did of a bracket-term. into rd_adt  *
 *									       *
 *    -Mk_stopentry      : inserts the CMR-did of the parser-internal EOF-code *
 *			   and the pointer (*pt_data)[12] into rd_adt.	       *
 * 									       *
 *    -Mk_ntermentry     : inserts the CMR-did of a nonterminal into rd_adt    *
 *   									       *
 *    -Mk_ntermsymbentry : inserts a nonterminal in its string-representation  *
 *                         into rd_adt.( only compiled by setting TESTOPT !)   *
 *									       *
 *    -Mk_prodentry      : inserts the CMR-did of the lefthandside-nonterminal,*
 *                         the CMR-did, the length and the sema-code of a      *
 *			   production into rd_adt.			       *
 *									       *
 *    -Get_intprodcode   : Gets the for module BUILDPRS internal prodcode for  *
 *			   a production given by its COMAR-did.                *
 *									       *
 *    -Mk_pstrentry      : inserts the string-representation of the            *
 *			   righthandside of a production and the CMR-did       *
 *                         of the lefthandside nonterminal of this production  *
 *                         into rd_adt.					       *
 *			   ( only compiled by setting name TESTOPT !)          *
 *									       *
 *    -Mk_rhsentry       : inserts the symbols-sequence of the righthand-sides *
 *                         into rd_adt.					       *
 *       								       *
 *    -Mk_errsymbentry   : inserts  a statenumber and the CMR-did of the       *
 *                         errorsymbol of this state for the                   *
 *                         continuation-automaton into rd_adt.		       *
 *			   						       *
 *    -Mk_shiftentry     : inserts for a statenumber, a CMR-did of a terminal  *
 * 			   or a nonterminalsymbol and a following-state a      *
 *			   SHIFT-entry into rd_adt.			       *
 *									       *
 *    -Mk_reduceentry    : inserts for a statenumber, a CMR-did of a terminal  *
 *			   or a nonterminalsymbol and a CMR-did of a rule      *
 *			   a REDUCE-entry into rd_adt.			       *
 *   									       *
 *    -Mk_shredentry     : inserts for a statenumber, a CMR-did of a terminal  *
 *			   or a nonterminalsymbol and a CMR-did of a rule      *
 *			   a  SHIFTREDUCE-entry into bt-adt.		       *
 *									       *
 *    -Mk_acceptentry    : inserts for a statenumber and a CMR-did of a        *
 *  			   terminal or nonterminalsymbol an ACCEPT-entry       *
 *                         into rd_adt.                                        *
 *                							       *
 *    -Write_tables      : prints all important tables for the concrete parser *
 *                         on file TESTOUT.bt for controll. (only compiled by  *
 *                         setting name TESTOPT !)			       *
 *									       *
 *									       *
 *  							    		       *
 *   rd_absprs <=> comarprivdefs :  This interface contains 7 functions:       *
 *   ----------------------------					       *
 *								               *
 *    -Initadt_cpd      : initializes the module comarprivdefs. Input is the   *
 *			  CMR-root, which keeps the definition- and symbol-list*
 *			  and returned is a pointer to the optimization-inter- *
 *			  face pt_data.					       *
 *  									       *
 *    -Get_symbentry    : gets the symbentry from the CMR-symbollist for a     *
 *                        given CMR-sid.                                       *
 *    									       *
 *    -Get_length       : gets the length of the righthandside of a production *
 *                        for a given CMR-did of this production.              *
 *   									       *
 *    -Get_prs          : gets a production in its string-representation for a *
 * 			  given CMR-unit-sequence of the righthandside and the *
 *      		  CMR-did of the lefthandside-nonterminal of this      *
 *		 	  production.   				       *
 *									       *
 *    -Get_rhs          : gets the symbolsequence of a righthandside of a pro- *
 *			  duction for a given COMAR-unit-sequence              *
 *                      						       *
 *    -Get_sxcode       : gets a syntaxcode of a terminal used in the scanner  *
 *                        given by its definitionentry in the                  *
 *                        COMAR-definitionlist.                                *
 *                 							       *
 *    -Get_prodcode     : gets the productioncode used by the semantic         *
 *                        analysis for a given COMAR-definitionentry           *
 *                        of this production.  				       *
 *									       *
 ***************************** TYPEDEFINITION *********************************/

typedef  short   *readtype[];

/***************************** INCLUDE-FILES **********************************/


#include  <stdio.h>

#include  <string.h>

#include  "comar.h"
#include  "prsiface.h"
#include  "name.h"
#include  "cmrprvdefs.h"

#include  "rd_adt.h"

#include  "error.h"


/********************************** MACROS ************************************/

#define strequal(str1, str2)  ! strcmp(str1, str2)

#define NO	0

#define YES	1

/************************** INTERNAL DECLARATIONS *****************************/

readtype  *rd_absprs( pt_data, Comar_root, Abs_parser, rhsinfo, addinfo )

   readtype       *pt_data;    /* interfacevector to optimization        */

   p_comar         Comar_root; /* keeps CMR symb- and def-list           */

   absparsertype   Abs_parser; /* IDL-strucrure of the abstract parser   */

   char            rhsinfo;    /* if rhsinfo = 1, the righthandsides of  */
                               /* all produktions are read               */

   char            addinfo;    /* if addinfo = 1, additional information */
                               /* at various  points is printed          */


   {

    /* variables needed for STEP 1: */
    /*------------------------------*/
      short         numbterm,    /* number of terminals     */

                    numbnterm,   /* number of nonterminals  */

                    numbprod;    /* number of productions   */



    /* variables needed for STEP 2: */
    /*------------------------------*/
      def_entry     def;

      SEQdef_entry  traversalseqdef;

      symb_entry    se;

      char         *symb;

      prop_entry    property;

      SEQprop_entry traversalseqprop;

      char	   pa_eof_found  = NO,/*=YES if the parser-internal EOF-code  */
				      /* is found			      */
		   st_prod_found = NO;/*=YES if the startproduction is found  */



    /* variables needed for STEP 3: */
    /*------------------------------*/
      Rowtype       row;

      SEQRowtype    traversalseqrow;

      Entrytype     entry;

      SEQEntrytype  traversalseqent;

      short         i = 0 ; /* statenumber */




      if(addinfo)
              printf("  C**module rd_absprs:started!\n");


    /*============== STEP 1: INITIALIZE ADT-MODULES AND ALLOCATE STORE========*/

      Initadt_cpd( &numbterm, &numbnterm, &numbprod, Comar_root );

      pt_data =

      Init_optif( pt_data, numbterm, numbnterm, numbprod,
                  lengthSEQRowtype(Abs_parser->ParsingTab), rhsinfo );

      Initadt_rd( *pt_data );


      if(addinfo)
              printf("  C**module rd_absprs:ADT-modules initialized !\n");



    /*============== STEP 2: WALK THROUGH IDL-COMAR-STRUCTURE ================*/

      foreachinSEQdef_entry(Comar_root->definitions, traversalseqdef, def) {



         switch( typeof( def ) ) { /* branch over class-members of def */

            case Kp_term  : /* skip the empty string */
                            se =Get_symbentry(def.IDLclassCommon->sid);
			    if( strequal(se.IDLclassCommon->str, "") ) break;

			    Mk_termentry(Get_sxcode(def),
                                         def.IDLclassCommon->did);

#ifdef TESTOPT              /* only compiled for testoutput */
			    se = Get_symbentry(def.IDLclassCommon->sid);
                  	    Mk_termsymbentry(se.IDLclassCommon->str);
#endif
                            /* walk through property-list */
                            foreachinSEQprop_entry(def.IDLclassCommon->prop,
                                                   traversalseqprop, property){

                                se =Get_symbentry(property.IDLclassCommon->sid);
                                symb = se.IDLclassCommon->str;

                                if(strequal(symb, SKIP))
				    Mk_skipentry(property.IDLclassCommon->did);
                                else if(strequal(symb, SEPA))
                                    Mk_sepaentry(property.IDLclassCommon->did);
				else if(strequal(symb, BRACKET))
				    Mk_bracentry(property.IDLclassCommon->did);
				else if(strequal(symb, STOP)) {
				    Mk_stopentry(property.IDLclassCommon->did,
						                (*pt_data)[12]);
				      pa_eof_found = YES;
				     }
				else /* nix */;

			    }/* foreachinSEQprop */

 			    break;



            case Kp_nterm : Mk_ntermentry(def.IDLclassCommon->did);

#ifdef TESTOPT             /* only compiled for testoutput ! */
		           se = Get_symbentry(def.IDLclassCommon->sid);
                           Mk_ntermsymbentry(se.IDLclassCommon->str);
#endif
                           break;



             case Kp_prod  : Mk_prodentry(def.IDLclassCommon->did,
                                          def.Vp_prod->lhsdid,
                                          Get_length(def.Vp_prod->rhs),
                                          Get_prodcode(def)
                                          );

#ifdef TESTOPT               /* only compiled for testoutput ! */
                             Mk_pstrentry(Get_prs(def.Vp_prod->rhs,
                                          def.Vp_prod->lhsdid)
                                         );
#endif
			     /* walk through property-list */
                             foreachinSEQprop_entry(def.IDLclassCommon->prop,
                                                 traversalseqprop, property)  {

                                se =Get_symbentry(property.IDLclassCommon->sid);
                                symb = se.IDLclassCommon->str;

                                if(strequal(symb, "_START")) {
                                   *(*pt_data)[13] =
                                       Get_intprodcode(def.IDLclassCommon->did);
                                    st_prod_found = YES;
				}

		             }/* foreachinSEQprop */

                             break;


             default       : /*nix*/

                             break;

           }/*switch*/

      }/*foreachinSEQdef_entry*/

      if ( ! pa_eof_found )
	        errmsg( RD_ABSPRS, NOEOFERR, ABORT, DUMMY );

      if ( ! st_prod_found )
 		errmsg( RD_ABSPRS, NOSTPRODERR, ABORT, DUMMY );


      if(addinfo)
        printf("  C**module rd_absprs:walked through IDL-C-COMAR-structure!\n");

    /*========== STEP 3: READ THE RIGTHHANDSIDES OF ALL PRODUCTIONS  =========*/

      if( rhsinfo ) {

         foreachinSEQdef_entry(Comar_root->definitions, traversalseqdef, def)
      	   if( typeof( def ) == Kp_prod )
      		 Mk_rhsentry(
                              def.IDLclassCommon->did,
      		              Get_rhs(
                                       def.Vp_prod->rhs,
      		                       Get_length(def.Vp_prod->rhs)
      		                      ),
      		             *pt_data
      		            );

         if(addinfo)
            printf("  C**module rd_absprs:read productions righthand-sides!\n");

      }/* if */

    /*========== STEP 4: WALK THROUGH IDL-ABSPARSER-INTERFACE ================*/




      foreachinSEQRowtype(Abs_parser->ParsingTab, traversalseqrow, row)  {


        Mk_errsymbentry(i, row->Errsymb);

        foreachinSEQEntrytype(row->Entries, traversalseqent, entry)  {


          switch( typeof(entry) ) {/* branch over class-members of entry */

            case Kshift   : Mk_shiftentry(i, entry.IDLclassCommon->CMR_DT_index,
                                             entry.Vshift->NextState);
                            break;


            case Kreduce  : Mk_reduceentry(i,entry.IDLclassCommon->CMR_DT_index,
                                             entry.Vreduce->Rule);
                            break;


            case Kshiftred: Mk_shredentry(i, entry.IDLclassCommon->CMR_DT_index,
                                             entry.Vshiftred->Rule);
                            break;


            case Kaccept  : Mk_acceptentry(i,
                                           entry.IDLclassCommon->CMR_DT_index);
                            break;


            default       : /*nix*/
                            break;

          }/*switch*/


        }/*foreachinSEQEntrytype*/


        i++; /* set next state */


      }/*foreachinSEQRowtype*/



      if(addinfo)
          printf("  C**module rd_absprs:walked through IDL-abstr.-prs-if. !\n");


/*============================================================================*/



#ifdef TESTOPT /* only compiled for testoutput ! */

      Write_tables();

#endif

      return( pt_data );

   }/* rd_absprs */

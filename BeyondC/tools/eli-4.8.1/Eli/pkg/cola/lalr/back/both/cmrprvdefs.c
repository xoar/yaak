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
** $Id: cmrprvdefs.c,v 1.6 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: cmrprvdefs.c,v 1.6 1997/08/29 08:38:08 mjung Exp $";

/******************************************************************************/
/* filename: comarprivdefs.c                   first edit   : 23 . 5 . 89     */
/* author  : Christian Zeitel                  last change  :  3 . 7 . 90     */
/******************************************************************************/

/********************************* CONTENTS ************************************
 *    									       *
 *  This is the implementation of module comarprivdefs. The maintasks are  :   *
 *   - getting an access to symb- or def-entries of the COMAR-structure in     *
 *     O(1)-time via its sid or did.					       *
 *   - getting the length of the righthandside of a production.		       *
 *   - getting the characterstring of the righthandside of a production for    *
 *     controlpurposes							       *
 *   - getting the sxcode of a terminal used by the scanner from the           *
 *     COMAR-datastructure.						       *
 *   - getting the code of a production used by the semantic analysis from     *
 *     the COMAR-datastructure.						       *
 * 									       *
 ******************************* INCLUDE-FILES ********************************/

#include <stdio.h>
#include <string.h>

#include "comar.h"
#include "error.h"

/****************************** FUNCTION-MACROS *******************************/

#define GETSYMB(def) fastsymblist[def.IDLclassCommon->sid].IDLclassCommon->str 
/* gets the symbolstring of a grammarsymbol with definition def in           */
/* the COMAR-deflist 							     */

#define GETDEF(ein) fastdeflist[ein.Vp_elunit->did]
/* gets the defentry-node of a COMAR-did in a p_elunit -classmember in a node*/
/* of class unit                                                             */

#define ISNOSEM(def) typeof(fastsymblist[def.IDLclassCommon->sid]) == Kp_string
/* is true if def defines a not-semantic terminal			     */

#define strequal(str1, str2)   ! strcmp(str1, str2)


/**************************** CONSTANT MACROS *********************************/

#define SYMBLISTSIZE   2048 /* legal length of COMAR-symbollist      */

#define DEFLISTSIZE    8192 /* legal length of COMAR-definitionlist  */
/* The greatest with Eli processed grammar needed more than 3072
 * for DEFLISTSIZE. See also rdt_adt.c .
 */

#define PRODSTRINGSIZE 800  /* for string which collects the         */
                            /*  stringrepresentation of a production */
#define NIL	      -1


/************************** INTERNAL DECLARATIONS *****************************/


static  symb_entry fastsymblist[SYMBLISTSIZE];
/* permits an O(1)-access on a symbentry-node over its sid */

static  def_entry fastdeflist[DEFLISTSIZE];
/* permits an O(1)-access on a defentry-node over its did  */




void  Initadt_cpd(nt, nn, np, comar_root)
 
     short    *nt,          /* number of terminals of the CFG 		     */
              *nn,          /* number of nonterminals of the CFG             */
              *np;          /* number of productions of the CFG   	     */
     p_comar  comar_root;   /* contains the root of the IDL-comar-structure  */


    /* Initializes module comarprivdefs.
     * Initadt_cpd has can be devided in three main steps:
     *
     * STEP 1: walk linear through the COMAR-symbollist and connect each  
     * ------- symbolnode with that element of fastsymblist indexed with the
     *         sid of the node.
     * STEP 2: walk linear through the COMAR-definitionlist and connect each
     * ------- definitionnode with that element of fastdeflist indexed with the
     *         did of the node. Simultaneously count all different occurencies
     *         of terminals, nontermnials and productions.
     * STEP 3: return the number of terminals, the number of nonterminals and 
     * ------- the number of productions to module rd_absprs.
     *
     ***/

     {  /* variables needed for STEP 1: */
        /*------------------------------*/
        SEQsymb_entry  traversalseqsymb;
           symb_entry  symb;
           short       sid;

        /* variables needed for STEP 2: */
        /*------------------------------*/
        SEQdef_entry  traversalseqdef; 
           def_entry  def;
           short      did;

         /* variables needed for STEP 3: */
         /*------------------------------*/        
    	 register short tc = 0, /* counts terminals    */
                        nc = 0, /* counts nonterminals */
                        pc = 0; /* counts productions  */

      /*=== STEP 1: WALK THROUGH SYMB-LIST ===================================*/

         foreachinSEQsymb_entry(comar_root->symbols, traversalseqsymb, symb) {

            	 sid = symb.IDLclassCommon->sid;
           	 if ( sid >= SYMBLISTSIZE ) 
			errmsg(COMARPRIVDEFS, OUTOFRANGEERR1, ABORT, DUMMY);
		 fastsymblist[sid] = symb; 

    	 }/* foreachinSEQsymb_entry */



      /*=== STEP 2: WALK THROUGH DEF-LIST ====================================*/

         foreachinSEQdef_entry(comar_root->definitions, traversalseqdef, def) {

                 did = def.IDLclassCommon->did;

                 /* count term-,nterm- and proddefinitions */
                 if ( ( typeof(def) == Kp_term ) &&
                     ( !strequal(GETSYMB(def), "") ) ) tc++;
                 else if ( typeof(def) == Kp_nterm )   nc++;
                 else if ( typeof(def) == Kp_prod  )   pc++;
      		 else /* nix */ ;

                 if ( did >= DEFLISTSIZE ) 
			errmsg(COMARPRIVDEFS, OUTOFRANGEERR2, ABORT, DUMMY);
                 fastdeflist[did] = def;

         }/* foreachinSEQdef_entry */

      /*=== STEP 3: RETURN SYMBOL- AND PRODUCTION-COUNTER ====================*/

         /*  return terminalcounter    */
         *nt = tc;
         /*  return nonterminalcounter */
         *nn = nc;
         /*  return productioncounter  */
         *np = pc;

       }/* Initadt_cpd */





symb_entry Get_symbentry( sid )
       
           short  sid;
        
          /* on entry :
           *     - sid contains the sid-index of a symb-entry.
           * on exit  :
           *     - the symbentry of the COMAR-list with sid sid is returned.
           *
           ***/

           { if ( sid >= SYMBLISTSIZE ) 
			errmsg(COMARPRIVDEFS, OUTOFRANGEERR1, ABORT, DUMMY);

             return (fastsymblist[sid]);

           }/* Get_symbentry */




short Get_length( rhs )

      SEQunit rhs;

      /* gets the length of the righthandside of a production given by its 
       * COMAR-unit-sequence. It is assumed, that rhs is a linear list without
       * any branches only containing COMAR-p_elunit-nodes.
       *  
       *  on entry-
       *     rhs contains the unitsequence of the righthandside of a production.
       *  on exit-
       *     the length of the righthandside of this production is returned.
       *
       ***/

       {  SEQunit   traversalsequnit;
	     unit   un;
             short  length = 0 ;

             /* walk linear through unit-list and count every */
             /*      node which type is not Kp_other          */

             foreachinSEQunit(rhs, traversalsequnit, un) {

               if(typeof(un) != Kp_elunit)
            		errmsg(COMARPRIVDEFS, BADNODEERR, ABORT, DUMMY);
               else if(typeof(GETDEF(un)) == Kp_other) /* nix */ ;
               else if(strequal(GETSYMB(GETDEF(un)), ""))  return (length);
                    /* empty string on righthandside ! */
               else length++ ;

             }/* foreachinSEQunit */

             return (length);

       }/* Get_length */



               
#ifdef TESTOPT /* only compiled for controlpurposes ! */

char  *Get_prs( rhs, lhsdid )

       SEQunit rhs;
       short   lhsdid;

       /* gets the stringrepresentation of a production given by a 
        * COMAR-unitsequence for its righthandside and the COMAR-did for
        * the lefthandside-nonterminal.
        *
        *  on entry-
        *     rhs contains the unitsequence of the righthandside of a production
        *     lhsdid contains the COMAR-did of the lefthandside-nonterminal of
        *     this production.
        *  on exit-
        *     a pointer to the stringrepresentation of this production is 
        *     returned.
        *
  	***/
 
        { SEQunit  traversalsequnit;
          
	     unit  un;
             short length; /* contains the free space in vector prodstring  */
             char  prodstring[PRODSTRINGSIZE];

          /* insert string of the lefthandsidenonterminal into string       */
          /* prodstring             					    */

          sprintf(prodstring, "%-12s :  ",GETSYMB(fastdeflist[lhsdid]));

          /* walk linear through unitsequence and append each string of a   */
          /* productionsymbol at the rear of string prodstring.             */
          /* Skip the empty string and enclose not semantic terminals into  */
  	  /* brackets.							    */

          foreachinSEQunit(rhs, traversalsequnit, un) {

            if(typeof(un) != Kp_elunit) 
			errmsg(COMARPRIVDEFS, BADNODEERR, ABORT, DUMMY);
            else if(typeof(GETDEF(un)) == Kp_other) /* nix, cause no symbol */ ;
            else if(strequal(GETSYMB(GETDEF(un)),""))/*nix,cause empty string*/;
            else if((typeof(GETDEF(un)) == Kp_term)&&(ISNOSEM(GETDEF(un)))) {

                    length = PRODSTRINGSIZE - strlen(prodstring);
                    if(strncat(prodstring, "'", 1) == NULL)
			      errmsg(COMARPRIVDEFS, PSTOVFLERR, ABORT, DUMMY);
                    if((strncat(prodstring, GETSYMB(GETDEF(un)), length))==NULL)
                              errmsg(COMARPRIVDEFS, PSTOVFLERR, ABORT, DUMMY);
		    if(strncat(prodstring, "'", 1) == NULL)
			      errmsg(COMARPRIVDEFS, PSTOVFLERR, ABORT, DUMMY);

         	 }                    
            else {
   		   length = PRODSTRINGSIZE - strlen(prodstring);
                   if((strncat(prodstring, GETSYMB(GETDEF(un)),length)) == NULL)
                              errmsg(COMARPRIVDEFS, PSTOVFLERR, ABORT, DUMMY);

                 }

            if(strncat(prodstring, " ", 1) == NULL)
			errmsg(COMARPRIVDEFS, PSTOVFLERR, ABORT, DUMMY); 

          }/* foreachinSEQunit */

          return(prodstring);

        }/* Get_prs */

#endif






short *Get_rhs( rhs, rhslen )

       SEQunit rhs;     /* COMAR-unit-sequence of the righthandside */
                        /* of a production                          */
       short   rhslen;  /* length of this righthandside             */
       
       /* returns the didsequence of the rigthhandside of a production
        * given by it COMAR-unit-sequence.
        *
        *  on entry-
        *     rhs is COMAR-unit-sequence of a righthandside of a production,
        *     rhslen is the length of this righthandside.
        *  on exit-
        *     the COMAR-did-sequence of this righthandside is returned.
        *
        ***/
        
        {  SEQunit   traversalsequnit;
	      unit   un;
	      short  *rhsdidseq = NULL;
	      
	   register short actpos = 0;
	   
	   
	   if( rhslen ) {
	   
	        /* allocate space */
	   	if((rhsdidseq = (short *)malloc(rhslen * sizeof(short)))==NULL)
	   		errmsg(COMARPRIVDEFS, NOSPACEERR, ABORT, "rhsdidseq");
	        
	        /* get the did-sequence */
	        foreachinSEQunit(rhs, traversalsequnit, un)
	        	if( typeof(GETDEF(un)) != Kp_other &&
	        	   ! strequal(GETSYMB(GETDEF(un)),"") )
	        	   rhsdidseq[actpos++] = GETDEF(un).IDLclassCommon->did;
	   }
	   
	   return( rhsdidseq );
	   
	}/* Get_rhs */	
	   	
 
       

short  Get_sxcode( termdef )

       def_entry  termdef; /* a terminal-definition-entry of the */
                           /* COMAR-definitionlist               */

       /* Gets the sxcode for a terminal with the COMAR-definition-entry termdef
        * and which is used by the scanner.
	*
	*  on entry-
	*     termdef is the COMAR-definition-entry of a terminal.
        *  on exit-
        *     the the sxcode of this terminal, used by the scanner is returned.
	*
	***/

	{  SEQprop_entry  traversalseqprop;
	      prop_entry  property;
	      char       *symbol;

           /* walk linear through property-list of the definition-node       */
           /* termdef, search for a property which sid points to a           */
           /* symbolentry with string "_SEM_SXCODE" or "_NOSEM_SXCODE        */
           /* and return the value of the p_nval-node of this property-node. */

           foreachinSEQprop_entry( termdef.IDLclassCommon->prop,
                                   traversalseqprop, property )  {
                                   
              symbol =  GETSYMB(property);
              
     	      if(strequal(symbol, "_SEM_SXCODE"))/* semantic terminal */
                   return (-((property.Vp_prop_val->val).Vp_nval->val));

              if(strequal(symbol, "_NOSEM_SXCODE"))/* not-semantic terminal */
                   return ((property.Vp_prop_val->val).Vp_nval->val);
                   
            }/* foreachinSEQprop_entry */

           errmsg(COMARPRIVDEFS, NOSXCODEERR, ABORT, GETSYMB(termdef));
           return 0;
         }/* Get_sxcode */






 
short   Get_prodcode( proddef )

        def_entry  proddef; /* a production-definition-entry of the */
                            /* COMAR-definitionlist                 */

       /* Gets the code for a production with the COMAR-definition-entry proddef
        * and which is used by the semantic analysis.
	*
	*  on entry-
	*     def is the COMAR-definition-entry of a production.
        *  on exit-
        *     the code of this production used by the semantic
        *     analysis is returned. If this production belongs to the abstract
	*     syntax, its code used by the semantic analysis is returned, else
	*     NIL is returned.
	*
	***/

	{  SEQprop_entry  traversalseqprop;
	      prop_entry  property;
           
           /* walk linear through the property-list of the definition-node */
           /* proddef, search for a property which sid points to a         */
           /* symbolentry with string "SEMA_PRODCODE" and return the value */
           /* of the p_nval-node of this property-node.                    */

           foreachinSEQprop_entry( proddef.IDLclassCommon->prop,
                                               traversalseqprop, property )  {

               if( strequal(GETSYMB(property), "_SEMA_PRODCODE") )
                        return( (property.Vp_prop_val->val).Vp_nval->val );

           }/* foreachinSEQprop_entry */
           
           return( NIL );
	   
        }/* Get_prodcode */

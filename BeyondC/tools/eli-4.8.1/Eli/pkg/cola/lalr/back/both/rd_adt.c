/*
** $Id: rd_adt.c,v 1.6 2007/02/23 10:53:13 peter Exp $
*/
static char rcs_id[]= "$Id: rd_adt.c,v 1.6 2007/02/23 10:53:13 peter Exp $";

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
/* filename: rd_adt.c                          first edit   : 23 . 5 . 89     */
/* author  : Christian Zeitel                  last  Change : 23 . 3 . 90     */
/******************************************************************************/

/********************************** CONTENTS ***********************************
 *  									       *
 *  This is the implementation of module rd_adt. It contains functions and     *
 *  datastructures, which extract all relevant informations for the concrete   *
 *  parser from the IDL-C-datastructures of COMAR and the abstract-parser      *
 *  interface. the following facts are important to know:		       *
 *									       *
 *  (1) In module rd_adt the components of vector pt_data ( interfacevector to *
 *  optimization ) are linked to local names ( see function Initadt_bt  ).     *
 *  Note, that changes in pt_data must also be made in this module by changing *
 *  the corresponding links !						       *
 *									       *
 *  (2) Respopnsible for a fast retrieval of in rd_adt local codes for         *
 *  grammarobjects given by their COMAR-did is the vector didconverter.        *
 *  It assigns an integer-number to every COMAR-did. A positive integer is the *
 *  local code in rd_adt for a terminal or a production. A negative integer is *
 *  in rd_adt the local code for a nonterminal after its negation and          *
 *  decrementation  by two :						       *
 *                         didconverter	     local code for a terminal or      *
 *			    +---+---+	    +----------------------->          *
 *   did of a grammar-object|   |   |  	    |-(local code for a nonterminal)-2 *
 *   ---------------------->|   |   |-------+----------------------->          *
 *			    +---+---+       | or local code for a production   *
 *			    |   |   |       +----------------------->          *
 *			    |   |   |					       *
 *			    +---+---+					       *
 *			    .   .   .					       *
 *			    .   .   .   				       *
 *			    .   .   .					       *
 *									       *
 *  (3) Entries in the terminal-parsertable are compressed to two bytes to     *
 *  make them fit for two-byte short-values. A single entry is composed as     *
 *  follows:	      							       *
 *  									       *
 *  									       *
 *              +-----------------------------------------------+	       *
 *              |ACTIONFIELD|           OPERANDFIELD            |	       *
 *              +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+	       *
 *              |15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|  BITNUMBER   *
 *              +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+ 	       *
 *               0  0  0  1 ->    SHIFT					       *
 *               0  0  1  0 ->    REDUCE          bitsettings for	       *
 *               0  1  0  0 ->    SHIFTRED        corresponding actions        *
 *               1  0  0  0 ->    ACCEPT				       *
 *               0  0  0  0 ->    ERROR   				       *
 *									       *
 *									       *
 *									       *
 *  (4) Entries in the nonterminal-parsertable are compressed to two bytes to  *
 *  make them fit for two-byte short-values. A single entry is  composed as    *
 *  follows:	      							       *
 *  									       *
 *  									       *
 *              +-----------------------------------------------+	       *
 *              |ACTIONFIELD|           OPERANDFIELD            |	       *
 *              +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+	       *
 *              |15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|  BITNUMBER   *
 *              +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+ 	       *
 *               0  1  1  0 ->    SHIFT_NT	  bitsettings for	       *
 *               1  0  0  1 ->    SHRED_NT        corresponding actions        *
 *               0  0  0  0 ->    INSIGNIFICANT   			       *
 *									       *
 *									       * 
 *  (5) A terminal can be semantic, be a skip-symbol, be a list separator or a *
 *  semantic bracket. This properties are coded together in a single short     *
 *  value for one terminal.						       *
 *  If the terminal is a skipsymbol, bit number zero is set ,                  *
 *  if the terminal is a list separator, bit number one is set and 	       *
 *  if the terminal is a semantic bracket, bit number two is set.	       *
 *  if the terminal is semantic, bit number three is set.		       *
 *									       *
 *  (6) A reduction of a production causes a connection if its code has a      *
 *  negative sign.							       *
 *									       *
 ******************************* INCLUDE-FILES ********************************/

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "error.h"

/*********************************** MACROS ***********************************/

#define TINDEX( state, termsymb )   tc * state + didconverter[termsymb]
/* calculates the terminalparsertable-index in the linear vector ttab for    */
/* a state given by state and a terminal given by its COMAR-did in termsymb  */

#define NINDEX( state, ntermsymb )  nc * state - didconverter[ntermsymb] -2
/* calculates the nonterminalparsertable-index in the linear vector ntab for */
/* a state given by state and a nonterminal given by its COMAR-did ntermsymb */

#define IS_TERM( did ) didconverter[did] >= 0
/* tests if a grammarsymbol given by its COMAR-did did is a terminal	     */

#define MAXENTRYCODE   4095

#define  sht sizeof(short)

#define IS_SEMANTIC( termcode )    termcode < 0
/* tests if a terminal given by its local code in module BUILDPRS is semantic */

#ifdef TESTOPT /* only compiled for controlpurposes ! */

#define WRTSTARLN fprintf(fp,"*************************************************\
*******************************\n");

#define WRTMINLN fprintf(fp,"--------------------------------------------------\
------------------------------\n");

#define WRTEQLN fprintf(fp,"===================================================\
=============================\n");

#define OPERAND( entry )         ( entry & 0x0FFF )
/* masks the highest four bits of a tableentry to retrieve the operand         */

#define IS_SHIFTACT( entry )       entry & 0x1000
/* tests if the action of a ttable-entry is a shiftaction by masking bit 12    */

#define IS_SHIFT_NTACT( entry )  ( entry & 0x6000 ) == 0x6000
/* tests if the action of a ntable-enrty is a shift_nt-action by testing       */
/* bit 13 and bit 14 whether they are both set				       */

#define IS_REDUCEACT( entry )      entry & 0x2000
/* tests if the action of a ttable-entry is a reduceaction by masking bit 13  */

#define IS_SHREDACT( entry )       entry & 0x4000
/* tests if the action of a ttable-entry is a shiftredaction by masking bit 14 */

#define IS_SHRED_NTACT( entry )  ( entry & 0x9000 ) == 0x9000
/* tests if the action of a ntable-entry is a shiftred_nt-action by testing    */
/* bit 15 and bit 12 whether they are both set				       */

#define IS_ACCEPTACT( entry )      entry & 0x8000
/* tests if the action of a ttable-entry is an acceptentry by masking bit 15   */

#define IS_NO_ERROR( entry )       entry & 0xF000
/* <>0 iff entry is no error-entry in a parsertable			       */

#define IS_SKIPSYMBOL( termcode )  termcode & 0x0001
/* tests if a terminal given by its local code in module BUILDPRS is a        */
/* skipsymbol								      */

#define IS_SEPASYMBOL( termcode )  termcode & 0x0002
/* tests if a terminal given by its local code in module BUILDPRS is a        */
/* list separator              						      */

#define IS_BRACSYMBOL( termcode )  termcode & 0x0004
/* tests if a terminal given by its local code in module BUILDPRS is a        */
/* semantic bracket							      */

#define IS_SEMAN( termcode )  termcode & 0x0008
/* tests if a terminal given by its local code in module BUILDPRS is semantic */

#define IS_ABSTR( prodcode )  prodcode >= 0
/* tests if a production belongs to the abstract syntax			      */

#define NL_3 fprintf(fp, "\n\n\n");
/* prints three newlines on file TESTOUT.bt				      */

#endif

/***************************** CONSTANT-MACROS ********************************/

#define DEFLISTSIZE    8192 /* legal length of COMAR-definitionlist  */
/* The greatest with Eli processed grammar needed more than 3072
 * for DEFLISTSIZE. See also cmrprvdefs.c .
 */

#define NIL               -1 /* initial value for the vector didconverter */

#define SHIFTMASK     0x1000 /* sets the property "is shiftentry"         */

#define SHIFT_NTMASK  0x6000 /* sets the property "is shift_ntentry"      */

#define REDUCEMASK    0x2000 /* sets the property "is reduceentry"        */

#define SHIFTREDMASK  0x4000 /* sets the property "is shiftreduceentry"   */

#define SHRED_NTMASK  0x9000 /* sets the property "is shred_ntentry"      */

#define ACCEPTMASK    0x8000 /* sets the property "is acceptenrty"        */

#define SKIPMASK      0x0001 /* sets the property "is skipsymbol"         */

#define SEPAMASK      0x0002 /* sets the property "is sepasymbol"         */

#define BRACMASK      0x0004 /* sets the property "is bracsymbol"         */

#define SEMAMASK      0x0008 /* sets the property "is semantic"		  */

#define NOTSEMA       0x0007 /* deletes the bit for property "is semantic"*/

#ifdef TESTOPT  /* only compiled for controlpurposes */

#define SYMBSTRSIZE   300

#define NIL 	     -1

#endif

/****************************** PIVATE VARIABLES ******************************/

typedef  short *readtype[];

static short tc, /* number of terminalsymbols      */
             nc, /* number of nonterminalsymbols   */
             pc, /* number of productions          */
             sc, /* number of parser-states        */

             termcounter  = 0, /* local code for the actual terminal    */
             ntermcounter = 0, /* local code for the actual nonterminal */
             prodcounter  = 0, /* local code for the actual production  */

             didconverter[DEFLISTSIZE], /* meaning see above */

            *ttab,        /* the terminalparsertable       		      */
     	    *termlist,    /* the coversion-vector local code to scanner-code  */
            *errsymblist, /* vector for skip- sepa- and bracket-symbols       */
            *ntab,        /* the nonterminalparsertable		              */
            *prodlhslist, /* vector with the local codes for lefthanside      */
		          /* nonterminal of productions		              */
            *prodlenlist, /* vector with the length of the righthandsides     */
                          /* of the productions			              */
            *prodlist,    /* the conversion-vector local code to sema-code    */
	    *contaut,     /* the vector for the continuation-automaton        */
	     stopdid=NIL; /* the COMAR-did of the parserinternal EOF-Symbol   */

#ifdef TESTOPT /* only compiled for controlpurposes ! */

static FILE *fp; /* filepointer to file "TESTOUT.bt" (collecting testoutput) */

static char *termsymblist[DEFLISTSIZE], /* vector with stringrepresentations  */
					/* of terminalsymbols		      */
            *ntermsymblist[DEFLISTSIZE];/* vector with stringrepresentations  */
					/* of nonterminalsymbols	      */
static short *pa_eof, /* the local sxcode of the parser-internal EOF-code     */
	     *st_prod;/* the internal productioncode of the startproduction   */

#endif


/***************************** PUBLIC FUNCTIONS *******************************/

readtype  *Init_optif( pt_data, not, non, nop, nos, rhsinfo )
      
     readtype *pt_data;   /* interfacevector to optimization   */
     short     not,       /* number of terminals of the CFG    */
               non,       /* number of nonterminals of thr CFG */
               nop,       /* number of productions of the CFG  */
               nos;       /* number of states of the CFG       */
     char      rhsinfo;   /* if rhsinfo is zero, 14 pointers are allocated */
                          /* for vector pt_data, else 14+p where p is the  */
                          /* number of productions                         */
 
    /*  Aloctes store for vector *pt_data and initializes it.
     *  For the generator of a tabledriven parser 14 pointers to short are
     *  allocated, for the generator of the directly programmed parser 
     *  15 + number if productions  pointers to short are allocated.
     *  All entries in listcomponents of pt_data are initialized with zero.
     *  The valuecomponents of pt_data are initialized with the values of
     *  not, non, nop and nos at the correct positions.
     *
     ***/
     
     
     { 
  	       
  	if(( pt_data = (readtype *)malloc( 
  	                (14+(rhsinfo ? nop : 0)) * sizeof( short *)) ) == NULL )
		errmsg(RD_ADT, NOSPACEERR, ABORT, "*pt_data");
	
        if( (((*pt_data)[0]  = (short *)calloc(1, sht        )) == NULL ) ||
            (((*pt_data)[1]  = (short *)calloc(1, nos*not*sht)) == NULL ) ||
            (((*pt_data)[2]  = (short *)calloc(1, not*sht    )) == NULL ) || 
            (((*pt_data)[3]  = (short *)calloc(1, sht        )) == NULL ) || 
            (((*pt_data)[4]  = (short *)calloc(1, nos*non*sht)) == NULL ) || 
            (((*pt_data)[5]  = (short *)calloc(1, sht        )) == NULL ) || 
            (((*pt_data)[6]  = (short *)calloc(1, nop*sht    )) == NULL ) || 
            (((*pt_data)[7]  = (short *)calloc(1, nop*sht    )) == NULL ) || 
            (((*pt_data)[8]  = (short *)calloc(1, nop*sht    )) == NULL ) ||
            (((*pt_data)[9]  = (short *)calloc(1, sht        )) == NULL ) ||
            (((*pt_data)[10] = (short *)calloc(1, nos*sht    )) == NULL ) ||
            (((*pt_data)[11] = (short *)calloc(1, not*sht    )) == NULL ) ||
	    (((*pt_data)[12] = (short *)calloc(1, sht        )) == NULL ) ||
            (((*pt_data)[13] = (short *)calloc(1, sht        )) == NULL )  )
        		errmsg(RD_ADT, NOSPACEERR, ABORT, "pt_data");

        

        /*  initialize terminalcounter in *pt_data     */
        *((*pt_data)[0]) = not;
        /*  initialize nonterminalcounter *in pt_data  */
        *((*pt_data)[3]) = non;
        /*  initialize productioncounter *in pt_data   */
        *((*pt_data)[5]) = nop;
        /*  initialize statecounter in *pt_data        */
        *((*pt_data)[9]) = nos;
        
        return( pt_data );
       
     }/* Init_optif */




void Initadt_rd( pt_data )

     readtype pt_data; /* interfacevector to optimization */

    /* Initializes the module rd_adt,i.e. the vector didconverter 
     * initialized with NIL and in rd_adt local names are connected with
     * components of interface-vector pt_data. If the name TESTOPT was set
     * during compiling this module,  the file "TESTOUT.bt" is opened and a
     * protocoll-head is printed on this file.
     *
     ***/

     {  register short i;

        /* init vector didconverter */
        for(i=0; i < DEFLISTSIZE; didconverter[i++] = NIL );

        /* connect in rd_adt local names to the components of pt_data */
        tc           =   *pt_data[0];
        ttab         =    pt_data[1];
        termlist     =    pt_data[2];
        nc           =   *pt_data[3];
        ntab         =    pt_data[4];
        pc           =   *pt_data[5];
        prodlhslist  =    pt_data[6];
        prodlenlist  =    pt_data[7];
        prodlist     =    pt_data[8];
        sc           =   *pt_data[9];
        contaut      =    pt_data[10];
        errsymblist  =    pt_data[11];

#ifdef TESTOPT /* only compiled for controlpurposes ! */

	pa_eof =  pt_data[12];
        st_prod = pt_data[13];
        if( (fp = fopen("TESTOUT.bt", "w")) == NULL )  
     		errmsg(RD_ADT, FILEERR, ABORT, "TESTOUT.bt"); 

        /* print protocollhead on file "TESTOUT.bt" */
        fprintf(fp," Testoutput of PGBE-Module build_copa \n");
        WRTEQLN
	NL_3 
        fprintf(fp,"A. Characteristics of the concrete grammar\n");
        fprintf(fp,"   after translation from EBNF to BNF\n");
        WRTSTARLN
        NL_3
        fprintf(fp,"A.1. Listing of the grammar: \n\n");
#endif

      }/* Initadt_rd */





void Mk_termentry( sxcode, did )

     short sxcode, /* sxcode of a terminal used by the scanner */
              did; /* COAMR-did of this terminal               */

    /* inserts the local code of the terminal (lcd) with COMAR-did did into 
     * vector didconverter and inserts the sxcode used by the scanner into 
     * vector termlist:
     *
     *         didconverter         termlist
     *           +-+-+                +-+-+
     *      did  | | |     lcd        | | |  sxcode
     *   ------->| | |--------------->| | |------------->
     *           +-+-+ 		      +-+-+
     *           | | |		      | | | 
     *    	 | | |                | | |
     *           +-+-+		      +-+-+
     *	         . . .		      . . . 
     *           . . . 		      . . .
     *           . . .		      . . .
     *
     *      on entry: lcd = termcounter
     *      on exit : termcounter = lcd + 1
     *
     ***/

     {
       if( did >= DEFLISTSIZE )
		errmsg(RD_ADT, LISTTOOBIGERR, ABORT, DUMMY);

       didconverter[did] = termcounter;
       if( IS_SEMANTIC( sxcode ) ) { 
       		errsymblist[termcounter] |= SEMAMASK;
       		sxcode = -sxcode;
       } 
       termlist[termcounter++] = sxcode;
     
     }/* Mk_termentry */




#ifdef TESTOPT /* only compiled for controlpurpopses ! */

void Mk_termsymbentry( termsymb )

     char *termsymb; /* a pointer to the stringrepresentation of a terminal */

    /*  Inserts a pointer to a terminalstring contained in termsymb into the 
     *  vector termsymblist at the position of the local code for this 
     *  terminal in module BUILDPRS.
     *
     ***/

     {
        termsymblist[termcounter-1] = termsymb;

     }/* Mk_termsymbentry */

#endif




void Mk_skipentry( did )

     short did; /* the COMAR-did of a terminal, which is a skipsymbol */

    /*  Inserts the property "is skipsymbol" into vector errsymblist at the 
     *  position of the local code in module BUILDPRS for the terminal with
     *  COMAR-did did. The property "is skipsymbol" is true, iff bit number
     *  zero is set .
     *
     ***/

     {  
        /* if( did == stopdid )
        		errmsg(RD_ADT, STOPWARN, CONTINUE, DUMMY);
         */

        if( errsymblist[didconverter[did]] & NOTSEMA )
        		errmsg(RD_ADT, SKIPWARN, CONTINUE, DUMMY);
        
        errsymblist[didconverter[did]] |=  SKIPMASK;

     }/* Mk_skipentry */




               
void Mk_sepaentry( did )

     short did; /* the COMAR-did of a terminal, which is a list separator */

    /*  Inserts the property "is sepasymbol" into vector errsymblist at the 
     *  position of the local code in module BUILDPRS for the terminal with
     *  COMAR-did did. The property "is sepasymbol" is true, iff bit number
     *  one is set .
     *
     ***/

     {   
        
        /* if( did == stopdid )
        		errmsg(RD_ADT, STOPWARN, CONTINUE, DUMMY);
        */

        if( errsymblist[didconverter[did]] )
        		errmsg(RD_ADT, SEPAWARN, CONTINUE, DUMMY);
        		
        errsymblist[didconverter[did]]  |=  SEPAMASK;

     }/* Mk_sepaentry */  




void Mk_bracentry( did )

     short did; /* the COMAR-did of a terminal, which is a semantic bracket */

    /*  Inserts the property "is skipsymbol" into vector errsymblist at the 
     *  position of the local code in module BUILDPRS for the terminal with
     *  COMAR-did did. The property "is bracsymbol" is true, iff bit number
     *  two is set .
     *
     ***/

     {  
        /* if( did == stopdid )
        		errmsg(RD_ADT, STOPWARN, CONTINUE, DUMMY);
        */

        if( errsymblist[didconverter[did]] )
        		errmsg(RD_ADT, BRACWARN, CONTINUE, DUMMY);
        		
        errsymblist[didconverter[did]]  |=  BRACMASK;

     }/* Mk_bracentry */ 




void Mk_stopentry( did, pt_dataentry )

     short  did,          /* the COMAR-did of the parser-internal EOF-code */
	   *pt_dataentry; /* a pointer to an element in vector pt_data     */

    /*  Inserts the in module BUILDPRS local sxcode into an element of the 
     *  interface-vector pt_data.
     *
     ***/

     {   
         /* if( errsymblist[didconverter[did]] )
          		errmsg(RD_ADT, STOPWARN, CONTINUE, DUMMY);
          */

         stopdid = did;
          		
	*pt_dataentry = didconverter[did];
     
     }/* Mk_stopentry */




void Mk_ntermentry( did )

     short did; /* the COMAR-did of a nonterminal */

    /*  Inserts a nonterminal with COMAR-did did at position did into vector
     *  didconverter. The entry contains the local code for this nonterminal 
     *  in module BUILDPRS. It has a negative sign to distinguish it from 
     *  terminals or productions, which is important  for functions inserting 
     *  entries into the terminal- or the nonterminal-parsertable.
     *
     ***/

     {
        if ( didconverter[did] == NIL ) 
        	didconverter[did] = -(++ntermcounter)-1;

     }/* Mk_ntermentry */





#ifdef TESTOPT /* only compiled for controlpurposes ! */

void Mk_ntermsymbentry( ntermsymb )

     char *ntermsymb; /* a pointer to a nonterminalstring */
     
    /*  inserts a pointer to a nonterminalstring given by ntermsymb into 
     *  vector ntermsymblist at position lcd where lcd is the local code 
     *  for this nonterminal in module BUILDPRS.
     *
     ***/

     {
        ntermsymblist[ntermcounter-1] = ntermsymb;

     }/* Mk_ntermsymbentry */

#endif




void Mk_prodentry( did, lhsdid, length, prodcode )

     short  did,      /* the COMAR-did of a production                      */
            lhsdid,   /* the COMAR-did of the lefthandside nonterminal of   */
                      /* this production				    */
            length,   /* the length of the righthandside of this production */
            prodcode; /* the code of this production used in the semantic   */
                      /* analysis					    */

    /*  Inserts a production given by its COMAR-did at the position of its
     *  local code (lcd) in module BUILDPRS into vector didconverter. Its 
     *  lefthandside nonterminal is inserted in vector ntermlist at the  
     *  position of the nonterminals local code in module BUILDPRS, if it
     *  isn't inserted yet. Then the nonterminal local code in module rd_adt
     *  is inserted into the vector prodlhslist at position lcd.
     *  The length of this production which is given by length is inserted 
     *  in vector prodlenlist at position lcd. The productioncode used in 
     *  the semantic analysis which is given by prodcode is inserted in vector
     *  prodlist.
     *
     ***/

     {
        didconverter[did] = prodcounter;
        if(didconverter[lhsdid]==NIL)
        	didconverter[lhsdid] = -(++ntermcounter)-1;
        prodlhslist[prodcounter] = -didconverter[lhsdid]-2;
        prodlenlist[prodcounter] = length;
        prodlist[prodcounter++] = prodcode;
 
     }/* Mk_prodentry */
     



     
     
short Get_intprodcode( did )
  
      short  did;    /* COMAR-did of a production */
     
     /*  Returns the internal prodcode in module BUILDPRS for the production
      *  with the COMAR-did did.
      *
      ***/
     
      {  
         return( didconverter[did] );
     
      }/* Get_intprodcode */






#ifdef TESTOPT /* only compiled for controlpurposes ! */

void Mk_pstrentry( prodstring )

     char  *prodstring; /* the stringrepresentation of a production */

    /*  Writes the stringrepresentation of a production given by prodstring
     *  and its length on file "TESTOUT.bt".
     *
     ***/

     { short is_abstract;/* =1 <=> the current production belongs to the  */
			 /* abstract Syntax			  	  */

       is_abstract = ( prodlist[prodcounter-1] >= 0 );
       fprintf(fp, "rule %-3d=  %s.\n", prodcounter-1, prodstring);
       fprintf(fp, "length   : %-5d .\nprodcode : %-5d .\nrule is %s.\n\n",
					 prodlenlist[prodcounter-1]
				       , ( is_abstract ?
						 prodlist[prodcounter-1]
					       : NIL
					 )
				       , ( is_abstract ?
				                 "abstract"
					       : "not abstract"
				         ) );

     }/* Mk_pstrentry */

#endif





void Mk_rhsentry( proddid, rhsdidseq, pt_data )

     short     proddid,    /* COMAR-did of a production        */
              *rhsdidseq;  /* the COMARdid-sequence of the     */
                           /* righthandside of this production */
     readtype  pt_data;    /* interfacevector to optimization  */
     
     /* first each COMAR-did of a symbol in rhsseq is transformed to its
      * internal code for module BUILDPRS. Then, if didconverter[proddid] = i,
      * rhsseq is assigned to (*pt_data)[14+i], where i is the internal code
      * in module BUILDPRS for the production with COMAR-did, proddid.
      *
      ***/
      
      {
          register short i, length;
          
          length = prodlenlist[didconverter[proddid]];
          
          for( i = 0; i < length; i++ )
          	rhsdidseq[i] = didconverter[rhsdidseq[i]];
         
          pt_data[14+didconverter[proddid]] = rhsdidseq;
                    
          
      }/* Mk_rhsentry */
          





void Mk_errsymbentry( state, errsymbdid )

     short      state, /* the number of a parserstate        		     */
           errsymbdid; /* the COMAR-did of the errorsymbol belonging to this */
                       /* state in the continuation-automaton 		     */

    /*  errsymbdid is the COMAR-did of the errorsymbol belonging to the state
     *  given by state in the continuation-automaton for error-recovery. The 
     *  local code in module BUILDPRS is inserted into vector contaut at
     *  position state.
     *
     ***/

     {
        contaut[state] = didconverter[errsymbdid] ;

     } /* Mk_errsymbentry */




void Mk_shiftentry( state, gramsymb, nextstate )

     short  state,     /* the number of a parserstate                       */
            gramsymb,  /* the COMAR-did of a grammarsymbol                  */
            nextstate; /* the successorstate belonging to to the shiftentry */
                       /* of state and gramsymb				    */

    /*  First it is determined, whether gramsymb represents a terminal or a 
     *  nonterminal. Assumed, gramsymb is a nonterminal, then lncd is the local
     *  code for this nonterminal in module BUILDPRS, iff
     *  didconverter[gramsymb] = -lncd-2. If lsscd is the  local code of the 
     *  successorstate given by nextstate, lsscd is compressed into the
     *  two-byte shiftentry as described in the CONTENTS-chapter in this
     *  file. Depending on the kind of gramsymb ( terminal or nonterminal )
     *  this shiftentry is inserted into the corresponding parsertable.
     *
     ***/

     {  
        if ( nextstate > MAXENTRYCODE) 
               errmsg(RD_ADT, ENTRYTOOBIGERR, ABORT, DUMMY);
        if( IS_TERM(gramsymb) ) 
             ttab[TINDEX(state, gramsymb)] = --nextstate | SHIFTMASK;
        else ntab[NINDEX(state, gramsymb)] = --nextstate | SHIFT_NTMASK;

     }/* Mk_shiftentry */






void Mk_reduceentry( state, gramsymb, rule )

     short  state,     /* the number of a parserstate                   */
            gramsymb,  /* the COMAR-did of a grammarsymbol              */
            rule;      /* the the COMAR-did of the rule beeing reduced  */

    /*  First it is determined, whether gramsymb represents a terminal or a 
     *  nonterminal. Assumed, gramsymb is a nonterminal, then lncd is the local
     *  code for this nonterminal in module BUILDPRS, iff
     *  didconverter[gramsymb] = -lncd-2. If lpcd is the local code of the 
     *  rule beeing reduced given by didconverter[rule], lpcd is compressed into
     *  the two-byte shiftentry as described in the CONTENTS-chapter in this
     *  file. Depending on the kind of gramsymb ( terminal or nonterminal )
     *  this reduceentry is inserted into the corresponding parsertable.
     *
     ***/

     { 
        if( didconverter[rule] > MAXENTRYCODE ) 
		errmsg(RD_ADT, ENTRYTOOBIGERR, ABORT, DUMMY);
        if( IS_TERM(gramsymb) ) 
             ttab[TINDEX(state, gramsymb)] = didconverter[rule] | REDUCEMASK;
        else ntab[NINDEX(state, gramsymb)] = didconverter[rule] | REDUCEMASK;

     }/* Mk_reduceentry */






void Mk_shredentry( state, gramsymb, rule )

     short  state,     /* the number of a parserstate                   */
            gramsymb,  /* the COMAR-did of a grammarsymbol              */
            rule;      /* the the COMAR-did of the rule beeing reduced  */

    /*  First it is determined, whether gramsymb represents a terminal or a 
     *  nonterminal. Assumed, gramsymb is a nonterminal, then lncd is the local
     *  code for this nonterminal in module BUILDPRS, iff
     *  didconverter[gramsymb] = -lncd-2. If lpcd is the local code of the 
     *  rule beeing reduced given by didconverter[rule], lpcd is compressed into
     *  the two-byte shiftreduceentry as described in the CONTENTS-chapter in 
     *  this file. Depending on the kind of gramsymb ( terminal or nonterminal )
     *  this shiftreduceentry is inserted into the corresponding parsertable.
     *
     ***/

     {
        if( didconverter[rule] > MAXENTRYCODE )
		errmsg(RD_ADT, ENTRYTOOBIGERR, ABORT, DUMMY);  
        if( IS_TERM(gramsymb) ) 
             ttab[TINDEX(state, gramsymb)] = didconverter[rule] | SHIFTREDMASK;
        else ntab[NINDEX(state, gramsymb)] = didconverter[rule] | SHRED_NTMASK;

     }/* Mk_shredentry */




void Mk_acceptentry( state, gramsymb )

     short  state,     /* the number of a parserstate      */
            gramsymb;  /* the COMAR-did of a grammarsymbol */

    /*  First it is determined, whether gramsymb represents a terminal or a 
     *  nonterminal. Assumed, gramsymb is a nonterminal, then lncd is the local
     *  code for this nonterminal in module BUILDPRS, iff
     *  didconverter[gramsymb] = -lncd-2.
     *  Depending on the kind of gramsymb ( terminal or nonterminal )
     *  this acceptentry is inserted into the corresponding parsertable.
     *
     ***/

     {  
        if( IS_TERM(gramsymb) ) 
             ttab[TINDEX(state, gramsymb)] = ACCEPTMASK;
        else ntab[NINDEX(state, gramsymb)] = ACCEPTMASK;

     }/* Mk_acceptentry */



#ifdef TESTOPT  /* only compiled for control-purposes !*/

void Write_tables( ) 

    /* Prints out all important datas for the concrete parser */

     { register short i,j;     /* loopcounters */

       short  no_skip = 1,  /* =0 <=> a skipsymbol exist */
              no_sepa = 1,  /* =0 <=> a sepasymbol exist */
              no_brac = 1,  /* =0 <=> a bracsymbol exist */

	      entry, /* a listentry */

              no_entry = 1; /* =0 if there is an entry in the terminal- or    */
   	   	  	    /* nonterminal-parsertable for a symbol and some  */
			    /* state					      */

       char symbstr[SYMBSTRSIZE]; /* for enclosing a string of a not semantic */
				  /* terminal in brackets		      */

       fprintf(fp, "A2. Number of terminals   : %-3d\n\n", tc);
       fprintf(fp, "A3. Number of nonterminals: %-3d\n\n", nc);
       fprintf(fp, "A4. Number of productions : %-3d\n\n", pc);
       WRTEQLN
       NL_3

       fprintf(fp, "B. Characteristics of the abstract parser:\n\n");
       fprintf(fp, "B1. Number of states     : %-3d\n\n", sc);
       fprintf(fp, "B2. Listing of the transitiontables :\n");
       fprintf(fp, "    (Error-entries are omitted!)\n");
       fprintf(fp, "    (state_0 is starting-state!)\n\n\n");


       fprintf(fp, "B2.1. Terminaltable columnwise:\n");
       NL_3
       for(j=0; j < tc; j++)  {
         WRTSTARLN
	 fprintf(fp, "Termsymb: %-15s|   sxcode : %-5d |   %-15s \n",
                     termsymblist[j], termlist[j],
		     (IS_SEMAN(errsymblist[j]) ? "is semantic":"not semantic"));
	 WRTMINLN
	 for(i=0; i < sc; i++)  {
	     entry = ttab[i * tc + j];
	     if (IS_NO_ERROR(entry))  {
                no_entry = 0;
	        if(IS_SHIFTACT(entry)) 
	           fprintf(fp, "state_%-5d =>  action: shift   ,  state: %3d\n",
                         i,  OPERAND(entry));
	        else if(IS_REDUCEACT(entry))
	 	   fprintf(fp, "state_%-5d =>  action: reduce  ,  rule : %3d\n",
                         i,  OPERAND(entry));
	        else if(IS_SHREDACT(entry)) 
                   fprintf(fp, "state_%-5d =>  action: shiftred,  rule : %3d\n",
                         i,  OPERAND(entry));
                else if(IS_ACCEPTACT(entry))
		   fprintf(fp, "state_%-5d =>  action: accept\n", i);
                else /* action is error */;
             }
          }
          if( no_entry )
              fprintf(fp, "no entry for terminalsymbol %-15s !\n", 
							termsymblist[j]);
          no_entry = 1;
	}

        WRTSTARLN
	NL_3

        fprintf(fp, "B2.2. Nonterminaltable columnwise:\n");
        NL_3
	for(j=0; j < nc; j++)  {
          WRTSTARLN
	  fprintf(fp, "Nontermsymb: %-20s\n", ntermsymblist[j]);
          WRTMINLN
	  for(i=0; i < sc; i++)  {
	      entry = ntab[i * nc + j];
	      if (IS_NO_ERROR(entry))  {
  	         no_entry = 0;
		 if(IS_SHIFT_NTACT(entry))
		    fprintf(fp, "state_%-5d =>  action: shift_nt, state: %3d\n",
                           i, OPERAND(entry));
                 else if(IS_SHRED_NTACT(entry)) 
                    fprintf(fp, "state_%-5d =>  action: shred_nt, rule : %3d\n",
                           i, OPERAND(entry));
                 else /* action is error */;
               }
            }
            if( no_entry )
                fprintf(fp, "no entry for nonterminalsymbol %-15s !\n",
							 ntermsymblist[j]);
            no_entry = 1;
	  }

	  WRTSTARLN
          NL_3
          WRTEQLN
	  fprintf(fp, "C.   Characteristics of the error-recovery\n\n");
	  fprintf(fp, "C1.  Listing of the continuation-automaton\n\n");
	  fprintf(fp, "     state            symbol\n");
	  for(i=0; i < sc; i++)  {
             strcpy(symbstr, "'");
	     strcat(symbstr, termsymblist[contaut[i]]);
	     strcat(symbstr, "'");
	     fprintf(fp, "     %-3d              %-30s\n", i,
             		   IS_SEMAN(errsymblist[contaut[i]]) ?
			         termsymblist[contaut[i]]
			       : symbstr
             );
	  }
	  WRTMINLN
	  NL_3

	  fprintf(fp, "C2. Listing of the skipsymbols\n\n"); 
          for(i=0; i < tc; i++)  {
 	     strcpy(symbstr, "'");
	     strcat(symbstr, termsymblist[i]);
	     strcat(symbstr, "'");
             if( IS_SKIPSYMBOL(errsymblist[i]) )  {
          	     no_skip = 0;
		     fprintf(fp, "\t%-30s\n", 
			          IS_SEMAN(errsymblist[i]) ?
				       termsymblist[i]		
            			     : symbstr
		     );
             }
          }
          if( no_skip ) fprintf(fp, "no skipsymbols!\n");
	  WRTMINLN              
	  NL_3

          fprintf(fp, "C3. Listing of the list-separator symbols\n\n");
	  for(i=0; i < tc; i++)  {
	     strcpy(symbstr, "'");
	     strcat(symbstr, termsymblist[i]);
	     strcat(symbstr, "'");
             if( IS_SEPASYMBOL(errsymblist[i]) )  {
                      no_sepa = 0;
		      fprintf(fp, "\t%-30s\n", 
			          IS_SEMAN(errsymblist[i]) ?
				       termsymblist[i]		
            			     : symbstr	
		      );
             }  
          }
          if( no_sepa ) fprintf(fp, "no sepasymbols!\n"); 
	  WRTMINLN  
	  NL_3

	  fprintf(fp, "C4. Listing of the semantic-bracket symbols\n\n");
	  for(i=0; i < tc; i++)  {
	     strcpy(symbstr, "'");
	     strcat(symbstr, termsymblist[i]);
	     strcat(symbstr, "'");
             if( IS_BRACSYMBOL(errsymblist[i]) )  {
  		      no_brac = 0;
		      fprintf(fp, "\t%-30s\n", 
			          IS_SEMAN(errsymblist[i]) ?
				       termsymblist[i]		
            			     : symbstr	
		      );
             }
          }
          if( no_brac ) fprintf(fp, "no bracketsymbols!\n");
          WRTMINLN
          NL_3
	  WRTEQLN

          fprintf(fp, "D. EOF-codes\n\n");
          fprintf(fp, "D.1. EOF-symbol used by the parser: '%s'.\n" 
  							,termsymblist[*pa_eof]);
	  fprintf(fp, "D.2. Productioncode of the startproduction : %d.\n",
	  	                  ( ( IS_ABSTR( prodlist[*st_prod] ) ) ?
	  	                   	prodlist[*st_prod]
	  	                      : NIL
	  	                  )
	  	  );
	  	  
	  WRTMINLN
	  

	  fclose(fp);

        }/* Write_tables */

#endif

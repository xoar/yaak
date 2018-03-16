/*
** $Id: cmrtool.c,v 1.15 1998/09/18 07:48:01 mjung Exp $
*/
static char rcs_id[]= "$Id: cmrtool.c,v 1.15 1998/09/18 07:48:01 mjung Exp $";

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
/* filename: cmrtool.c                         first edit   :  4 . 7 . 90     */
/* author  : Christian Zeitel                  last Change  : 10 . 7 . 90     */
/******************************************************************************/

/******************************** CONTENTS *************************************
 *   									       *
 *  This tool adds the sxcodes of the terminals used by the scanner and the    *
 *  productioncodes used by the semantic analysis in property-nodes  to the    *
 *  property-lists of the definition-nodes in the COMAR-data-structure         *
 *  belonging to the corresponding  terminals or productions. 		       *
 *  									       *
 *  INPUT:  -COMAR-datastructure in parameter Comar_root.	  	       *
 *  ------                                                                     *
 *									       *
 *  OUTPUT: -COMAR-datastructure with inserted sxcodes for terminals and       *
 *  -------  productioncodes for productions. Productions of the abstract      *
 *	     grammar are marked. Code for the interface to the semantic ana-   *
 *           lysis is written to file "semprods.h".                            *
 *									       *
 ******************************* INCLUDE FILES ********************************/

#include  <stdio.h>
#include  <string.h>

#include  "comar.h"
#include  "name.h"
#include  "cmrlib.h"

#include  "error.h"
/****************************** CONSTANT MACROS *******************************/

#define  strequal(str1, str2)  ! strcmp(str1, str2)

#define  NO  0

#define  YES 1

/****************************** FUNCTION-MACROS *******************************/

#define  GETSYMB( ent )  fastsymblist[ent.IDLclassCommon->sid]\
.IDLclassCommon->str
/* Gets the symbolstring of terminal given by its COMAR-definition-entry */
/* or its COMAR-property-entry.  					 */

#define GETDEF( did )  fastdeflist[did]
/* Gets a COMAR-definition-entry for its COMAR-did */

#define IN_SYMBLIST( txtstr ) typeof(symb) == Kp_string   && \
    		              strequal(symb.IDLclassCommon->str, txtstr )
/* is true, if the string represented by txtstr */
/* is defined in COMAR-symbollist 		*/

#ifndef ELI_OLD

#define Is_semantic( def ) typeof(fastsymblist[def.IDLclassCommon->sid])\
== Kp_name

/* unquoted terminals are those with a p_name-symbol-entry */

#endif  

/**************************** PRIVATE VARIABLES *******************************/

static  symb_entry *fastsymblist; /* fast access on a symbol-entry by its */
                                  /* COMAR-sid                            */
      
static  def_entry  *fastdeflist;  /* fast access on a definition-entry by */
                                  /* its COMAR-did                        */

/**************************** PRIVATE FUNCTIONS *******************************/

#ifdef ELI_OLD /* adaption to old ELI-version */

static char Is_semantic( symbol, deflist )

       char         *symbol;  /* a terminal-symbol         */

       SEQdef_entry  deflist; /* the COMAR-definition-list */
       
      /* The input of "Is_semantic" is the text-string of a terminal-symbol
       * and the COMAR-definitionlist. "Is_semantic" returns YES, if this
       * terminal is semantic, else it returns NO.
       *
       ***/

       {  def_entry     def;

          SEQdef_entry  traversalseqdef;
          
          foreachinSEQdef_entry(deflist, traversalseqdef, def)  {
              
              if( typeof(def) == Kp_prod )
                  if( strequal(GETSYMB(GETDEF(def.Vp_prod->lhsdid)),symbol) )
                        return(YES);
                        
          }/* foreachinSEQdef_entry */
          
          return(NO);
          
       }/* Is_semantic */

#endif

static char Is_abstract( def, connection )

    def_entry  def;        /* COMAR-definition-entry for a production */
    
    char     **connection; /* an address of a stringpointer for       */
                           /* a connection-text                       */
    
   /* The input of "Is_abstract" is a COMAR-definition-entry def for a 
    * production and an address connection of a stringpointer. "Is_abstract" 
    * returns YES, if this production belongs to the abstract syntax, else it 
    * returns NO. If the production belongs to the abstract syntax, *connection
    * returns a pointer to the text of the corresponding connection as a side-
    * effect.
    *
    ***/
    
    {   def_entry     def1;
        unit          un;
        SEQunit       traversalsequnit;
        prop_entry    property;
        SEQprop_entry traversalseqprop;
        char	*str;
	short	result = NO;

        *connection = "\0"; 
        foreachinSEQunit( def.Vp_prod->rhs, traversalsequnit, un )  {
            
            def1 = GETDEF(un.Vp_elunit->did );
            
            if( typeof(def1) == Kp_other ) 
                   foreachinSEQprop_entry(def1.IDLclassCommon->prop,
                                                    traversalseqprop, property){

                     if(strequal(GETSYMB(property),CONNECTION)) {
                        /* structure-connection found */
			str = *connection;
                       	*connection = (char *)malloc(strlen(*connection) + 
						     strlen(GETSYMB(def1)) + 
						     1);
			strcpy(*connection, str);
			strcat(*connection, GETSYMB(def1));
                       	result = YES;
                     }
                       
                   }/* foreachinSEQprop_entry */
                   
        }/* foreachinSEQunit */
        
        return(result);
        
    }/* Is_abstract */                                 
                    
/***************************** PUBLIC FUNCTION ********************************/

void cmrtool( Comar_root )

p_comar  Comar_root; /* COMAR-datastructure */

/* cmrtool inserts a productioncode in the COMAR-datastructure for each 
 * production belonging to the abstract syntax. It also inserts a syntaxcode
 * for each terminalsymbol into the COMAR-datastructure. These insertions are
 * done in a specific way which is expected by the parsergenerator-backend.
 *
 ***/
 
{     symb_entry     symb;

      SEQsymb_entry  traversalseqsymb;

      def_entry      def;

      SEQdef_entry   traversalseqdef;

      prop_entry     property;

      SEQprop_entry  traversalseqprop;

      value          valnode;
      
      char          *symbol;
      
      char          *connection;
      
      short          prodcounter = 1;
      
      FILE          *fp;      /* pointer to file "semprods.h"            */
      
      short          ssxsid;  /* the sid for symblist-entry with string  */
                              /* "_SEM_SXCODE"                           */
      short          nssxsid; /* the sid for symblist-entry with string  */
                              /* "_NOSEM_SXCODE"                         */
      short          sasid;   /* the sid for symblist-entry with string  */
                              /*  "_SEMA_PRODCODE"                       */
      
      short sgla_found = NO;/*checks, if "_SEM_SXCODE" is already in symblist */
      
      short nsgla_found = NO;/*checks,if"_NOSEM_SXCODE" is already in symblist*/
  
      short sema_found = NO;/*checks,if "_SEMA_PRODCODE"is already in symblist*/

      short eof_found = NO;/*checks, if the EOF-code is found                 */

      short sxcode; /* keeps the sxcode for a terminal                        */

/*=============== BUILD FASTSYMBLIST AND FASTDEFLIST =========================*/

       if( ( fastsymblist = ( symb_entry *)malloc((cmrlib_getmaxsid 
             (Comar_root->symbols)+1) * sizeof( symb_entry ) ) ) == NULL )
             	    errmsg( CMRTOOL, NOSPACEERR, ABORT, "fastsymblist" );

       foreachinSEQsymb_entry( Comar_root->symbols, traversalseqsymb, symb )  {

               fastsymblist[symb.IDLclassCommon->sid] = symb;

               if ( IN_SYMBLIST( "_SEM_SXCODE" ) )  {

                      sgla_found  = YES; /* string already in COMAR-symblist */
                      ssxsid      =  symb.IDLclassCommon->sid;

               } else if ( IN_SYMBLIST( "_NOSEM_SXCODE" ) )  {

                      nsgla_found  = YES; /* string already in COMAR-symblist */
                      nssxsid      = symb.IDLclassCommon->sid;

               } else if ( IN_SYMBLIST( "_SEMA_PRODCODE" ) ) {

     		      sema_found = YES; /* string already in COMAR-symblist */
                      sasid      = symb.IDLclassCommon->sid;
               } else /* nix */;

        }/* foreachinSEQsymb_entry */

        if( ( fastdeflist = ( def_entry *)malloc((cmrlib_getmaxdid
             (Comar_root->definitions)+1) * sizeof( def_entry ) ) ) == NULL )
             	    errmsg( CMRTOOL, NOSPACEERR, ABORT, "fastdeflist" );

        foreachinSEQdef_entry( Comar_root->definitions, traversalseqdef, def) {

               fastdeflist[def.IDLclassCommon->did] = def;
        }     

/*=============== INSERT SX-CODE AND PRODCODE ================================*/

       /* insert two new symbols into the symbollist if they aren't yet */

       if ( ! sgla_found ) { /* "_SEM_SXCODE" isn't yet in symbollist */

                symb.Vp_string      = Np_string;
                ssxsid = lengthSEQsymb_entry(Comar_root->symbols) + 1;
                symb.Vp_string->str = "_SEM_SXCODE";
                symb.Vp_string->sid = ssxsid;
                appendrearSEQsymb_entry(Comar_root->symbols, symb);

       }
       
       if ( ! nsgla_found ) { /* "_NOSEM_SXCODE" isn't yet in symbollist */

                symb.Vp_string      = Np_string;
                nssxsid = lengthSEQsymb_entry(Comar_root->symbols) + 1;
                symb.Vp_string->str = "_NOSEM_SXCODE";
                symb.Vp_string->sid = nssxsid;
                appendrearSEQsymb_entry(Comar_root->symbols, symb);

       }

       if ( ! sema_found ) { /* "_SEMA_PRODCODE" isn't yet in symbollist */

                symb.Vp_string      = Np_string;             
                sasid = lengthSEQsymb_entry(Comar_root->symbols) + 1;
                symb.Vp_string->str = "_SEMA_PRODCODE";
                symb.Vp_string->sid = sasid;
                appendrearSEQsymb_entry(Comar_root->symbols, symb);
       } 

       /* walk through the definitionlist and insert new properties for */
       /* sxcodes and prodcodes at the corresponding definition-entries */
       
       if( ( fp = fopen("semprods.h", "w") ) == NULL )
                 errmsg( CMRTOOL, FILEERR, ABORT, "semprods.h" );
       
       fprintf(fp,"switch( action ) {\n");

       foreachinSEQdef_entry(Comar_root->definitions, traversalseqdef, def)  {

          switch( typeof(def) )  {

             case Kp_term: /*insert a sxcode */

 			    /* skip the empty string      */ 
			    if( strequal(GETSYMB(def), "") ) break;
			   foreachinSEQprop_entry(def.IDLclassCommon->prop,
                                                    traversalseqprop, property){

                                symbol = GETSYMB(property);
                                if(strequal(symbol,CODE)){
                                      valnode = property.Vp_prop_val->val;
                                   goto L_1;
                                }
                            }/* foreachinSEQprop_entry */
                            
                   L_1:     sxcode = valnode.Vp_nval->val;

                           /*  initialize a value-node    */
					       
		           valnode.Vp_nval      = Np_nval;
		   	   valnode.Vp_nval->val = sxcode;

                            /* initialize a property-node */
                 	    property.Vp_prop_val      = Np_prop_val;
                            property.Vp_prop_val->val = valnode;
                            property.Vp_prop_val->sid = 
#ifdef ELI_OLD /* adaption to old ELI-version */
                            (Is_semantic(GETSYMB(def), Comar_root->definitions)?
#else          /* adaption to new ELI-version */
                            (Is_semantic(def)?
#endif
                                ssxsid 
                              : nssxsid 
                            );
 			    property.Vp_prop_val->did = def.IDLclassCommon->did;

                            /* insert a new property-node into property-list */
                            appendfrontSEQprop_entry(def.Vp_term->prop,
						                      property);
			    break;
 
       	      case Kp_prod: if( Is_abstract(def, &connection) ) {
       	                        
       	                        /* generate code for interface to */
       	                        /* semantic analysis              */
       	                        
       	                        fprintf(
       	                                fp, 
       	                                "\tcase (OFFSET+%d) : %s break;\n",
       	                                prodcounter,
       	                                connection
       	                               );
       	                               
       	                        /* insert a productioncode  */
       	                        
			        /*  initialize a value-node */
			        valnode.Vp_nval      = Np_nval;
			        valnode.Vp_nval->val = prodcounter; 
                       
                                /* initialize a property-node  */
			        property.Vp_prop_val      = Np_prop_val;
			        property.Vp_prop_val->val = valnode;
                                property.Vp_prop_val->sid = sasid;
 			        property.Vp_prop_val->did = 
 			        			def.IDLclassCommon->did;

                                /* insert a property-node into property-list */
                                appendfrontSEQprop_entry(def.Vp_prod->prop,
						                      property);
                                prodcounter++;
			    }
 			    break;

               default    : /*nix*/ break;

            }/* switch */

         }/* foreachinSEQdef_entry */

	 fprintf(fp,"}\n");
         fclose(fp);
         
#ifdef MONITOR
    {
	FILE *prodsfile;
	SEQunit traversalsequnit;
	unit un;
	int count;
        char *cp;

	prodsfile = fopen ("mon_cprods.h", "w");
	fprintf (prodsfile,
		 "#ifdef MONITOR\nchar *conc_prods[] = {\n");
	foreachinSEQdef_entry (Comar_root->definitions, traversalseqdef, def) {
	    switch (typeof (def)) {
            case Kp_prod:
		fprintf (prodsfile, "\"%s : ",
			 GETSYMB (GETDEF (def.Vp_prod->lhsdid)));
  	        foreachinSEQunit (def.Vp_prod->rhs, traversalsequnit, un) {
		    def_entry d;
		    d = GETDEF (un.Vp_elunit->did);
		    if (typeof (d) == Kp_term) {
                        fputc ('\'', prodsfile);
                        for (cp = GETSYMB (d); *cp != '\0'; cp++) {
                            if (*cp == '"')
                                fputc ('\\', prodsfile);
                            fputc (*cp, prodsfile);
                        }
                        fputs ("' ", prodsfile);
		    } else if (typeof (d) == Kp_nterm)
              	        fprintf (prodsfile, "%s ", GETSYMB (d));
		}
            	fprintf (prodsfile, ".\",\n");           
	    }
	}  
	fprintf (prodsfile, "(char *) 0\n};\n\nint ntlen[] = {\n");
	foreachinSEQdef_entry (Comar_root->definitions, traversalseqdef, def) {
	    switch (typeof (def)) {
            case Kp_prod:
		count = 0;
  	        foreachinSEQunit (def.Vp_prod->rhs, traversalsequnit, un) {
		    def_entry d;
		    d = GETDEF (un.Vp_elunit->did);
		    if (typeof (d) == Kp_nterm)
              	        count++;
		}
            	fprintf (prodsfile, "%d,\n", count);           
	    }
	}  
	fprintf (prodsfile, "};\n#else\n");
	fprintf (prodsfile, "/* To avoid messages about empty files*/\n");
	fprintf (prodsfile, "static int _dapto;\n#endif\n");
	fclose (prodsfile);
    }
#endif

         free( (char *)fastsymblist );
         free( (char *)fastdeflist );
	 return;
}/* cmrtool */

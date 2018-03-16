/*
** $Id: BUILDPRS.c,v 1.6 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: BUILDPRS.c,v 1.6 1997/08/29 08:38:08 mjung Exp $";

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
/* filename: BUILDPRS.c                       first edit   : 23 .  8 . 89     */
/* author  : Christian Zeitel                 last  change :  5 . 10 . 90     */
/******************************************************************************/

/******************************* CONTENTS **************************************
 *									       *
 * This module constructs the optimized parsing tables for a concrete LALR(1)- *
 * parser, based on the  abstract parser, constructed by Karl-Josef Prott.     *
 *                                                                             *
 * If macro "FILEOPT" is not set, the module has the following I/O-behaviour:  *
 *									       *
 * INPUT :                                                                     *
 * ------                                                                      *
 *  -file with the external IDL-C COMAR-datastructure of the CFG               *
 *  -file with the external IDL-C structure of the abstract parser             *
 *   if option TABDRIV is set :						       *
 *  -value which determines the terminaltable-optmization                      *
 *  -value which determines the nonterminaltable-optimization		       *
 *   if option DIRPROG is set :					               *
 *  -values which determine the T-table-code-optimization		       *
 *  -values which determine the N-table-code-optimization		       *
 *                                                                             *
 * If macro TABDRIV is set, the following parameters are possible :            *
 * ================================================================	       *
 * -v          : verbose Informations about the generation-process	       *
 *		 are printed to stdin					       *
 * -p          : the results of optimizations are printed on file opt.out.     *
 * -r          : the the Chain-Rule-Elimination is performed		       *
 * -c <name>   : the name of the file containing the external 		       *
 *		 representation of the COMAR-file			       *
 * -n <name>   : the name determines the N-table table-optimization	       *
 * -t <name>   : the name determines the N-table table-optimization	       *
 * <name>      : the name of the file containing the external representation   *
 *		 of the Abstract-Parser-file				       *
 *									       *
 * If macro DIRPROG is set, the following parameters are possible :            *
 * ================================================================            *
 * -v          : see above						       *
 * -p          : see above						       *
 * -r          : see above						       *
 * -s          : the Minimal-Stack-Checking is performed		       *
 * -m          : function-macros instead of C-functions are implemented on     *
 *               the N-table codeoptimization				       *
 * -C <letter> : the implementation of jump-tables is determined    	       *
 * -c <name>   : see above						       *
 * -n <number> : the N-table codesharing is performed. <number> determines     *
 *               the number of common states which a significant entry in a    *
 *		 N-table row must share					       *
 * -t <number> : the T-table-codesharing is performed. <number> determines     *
 *		 the number of common actions for two selected T-table-rows    *
 * <name>      : see above					               *
 * 									       *
 * The parameters for the COMAR-file and the Abstract-Parser-File must occur   *
 * in each case, the remaining parameters are optional.			       *
 * 									       *
 * OUTPUT : if macro TABDRIV is set:					       *
 * -------- the tables needed by the parser are printed on file "ptabs.h".     *
 *          if macro DIRPROG is set: 				      	       *
 *          the code for the directly programmed parser in file "pcode.h"      *
 *          and additional tables needed for error-recovery are printed on     *
 *          file "ptabs.h".						       *
 *                                                                             *
 * If macroname "FILEOPT" is set the backend-options are passed over a file    *
 * instead of the backend-command-inputline. The backend-output is the same    *
 * as if "FILEOPT" is not set. Each line of the option-file may contain not    *
 * more then one option. If one option is accepted, the rest of the line is    *
 * skipped. A Line containing an option which is not accepted is also skipped. *
 * Lines beginning with the character '#' are skipped and can be used for      *
 * commands. The following options are recognized:                             *
 *                                                                             *
 * OPT_INFO       : causes the same as option "-p"                             *
 * T_TAB <name>   : causes the same as option "-t <name>" in the tabledriven   *
 *                  case.                                                      *
 * N_TAB <name>   : causes the same as option "-n <name>" in the tabledriven   *
 *                  case.                                                      *
 * MIN_T <number> : causes the same as option "-t <number>" in the directly    *
 *                  executable case.                                           *
 * MIN_N <number> : causes the same as option "-n <number>" in the directly    *
 *                  executable case.                                           *
 * MACROS         : causes the same as option "-m" in the directly executable  *
 *                  case.                                                      *
 * MIN_STACK_CTL  : causes the same as option "-s" in the directly executable  *
 *                  case.                                                      *
 * SWITCH         : causes the same as option "-C S" in the directly           *
 *                  executable case.                                           *
 *									       *
 * A call of the backend where macro "FILEOPT" was set during compilation must *
 * have the following form :                                                   *
 *                                                                             *
 *     backend <comarfile> <absparserfile> [ <optionfile> ]                    *
 *                                                                             *
 * If <optionfile> is omitted, default-values are chosen by the backend.       *
 *                                                                             *
 ****************************** INCLUDE FILES *********************************/
 
#include <stdio.h>
 
#include <string.h>

#include "comar.h"    /* Interface to COMAR-IDL-C-structure of the CFG */

#include "prsiface.h" /* Interface to the IDL-C-structure of the       */
		      /* abstract parser                               */
 
#include "error.h"    /* Interface to error-logging 		       */

#include "build_copa.h"
		     /* interface to generator-module for tables or    */
		     /* code of the concrete parser                    */

#ifdef DIRPROG

#include <ctype.h>

#endif

/*******************************  MACROS **************************************/

#define strequal( str1, str2 )  (! strcmp( str1, str2 ))

#define NO	0

#define YES	1

#ifdef DIRPROG

#define IFTHEN  'I'

#define SWITCH  'S'

#endif

/******************************************************************************/

#ifdef  TABDRIV  /* a tabledriven parser is generated         */

#include "tabsopttype.h"

#endif

#ifdef  DIRPROG  /* a directly executable parser is generated */

#include "codeopttype.h"

static char isnumber(str)
   char *str;
   
   /* returns YES, if "str" represents an integer, else NO.
    *
    ***/
   
   {  while(*str != '\0')
        if( !isdigit( *(str++) ) )
           return(NO);
      return(YES);
   } /* is_number */

#endif
                                     

#ifndef FILEOPT

main( argc, argv )
      int    argc;
      char  *argv[];
      
{
   FILE         *fp_comar,
   
   		*fp_prsiface;
   		
   p_comar       Comar_root;
   
   absparsertype Abs_parser;
   
   static  optkindtype  optkind  =

#ifdef  TABDRIV /* a tabledriven parser is generated        */

	{ "RDS", "RDS", NO };/* names to determine the tableoptimizations */
#endif

#ifdef  DIRPROG /* a directly programed parser is generated */

	{ NO, NO, NO, IFTHEN, NO, NO, 0, 0 };
	                      /* values to determine the codeoptimization */
#endif
   
   char          addinfo = NO,/* = 1, if additional information during the   */
   			       /* whole generating-process is printed out on  */
   			       /* standardoutput 			      */
   
                 optinfo = NO,/* = YES,if additional information during table-*/
                 	       /*optimization is printed out on file "opt.out"*/
                 apafnd  = NO,/* controls if the name of the abstract-parser-*/
                               /* is declared only once			      */
   		
   		*cmrname = NULL,/* filename for the COMAR-datastructure       */
   		
   		*apaname = NULL;/* filename for the absstract-parser-interface*/
   		

/************************************ MAIN ************************************/       
   while( --argc > 0 )  {
   		++argv;
   		
   		if( (*argv)[0] == '-'  &&  strlen( *argv ) >= 2 )  {
   		 
   			if( (*argv)[1] != 'p' &&
   		            (*argv)[1] != 'v' &&
   			    (*argv)[1] != 'r' &&
   			    (*argv)[1] != 'c' &&
                            (*argv)[1] != 'n' &&
   			    (*argv)[1] != 't'
  
#ifdef TABDRIV					
						  )
#endif

#ifdef DIRPROG
					      &&
   			    (*argv)[1] != 'm' &&
   			    (*argv)[1] != 's' &&
   			    (*argv)[1] != 'C'    )
#endif
   			    	     errmsg(BUILDPRS, OPTIONERR, ABORT, *argv);
   	        }
   	        if( strequal( *argv, "-" ) )
   	        	 errmsg(BUILDPRS, OPTIONERR, ABORT, *argv);
   		else if( strequal( *argv, "-p") )
   		/* additional informations are printed out */
   		/* on file "opt.out" during optimization   */
   		 		 optinfo = YES;
   		else if( strequal( *argv, "-v") )
   		/* additional informations are printed to stan- */
   		/* dardout during the whole generating-process  */
   				 addinfo = YES;
   		else if( strequal( *argv, "-r") ) 
   		/* on option -r the switch for chain-rule   */
   		/* elimination is switched on               */
   		                 optkind.chainrule = YES;
   		else if( strequal( *argv, "-c") )  { 
   		/* the next element of argv is */
   		/* the name of the COMAR-file  */
   			         if( argc != 1 )
   				 	cmrname = *(++argv);	
   				 argc--; 
   	        }
   		else if( strequal( *argv, "-n") )  { 
#ifdef TABDRIV
   		/* the next element of argv is the name which  */
   		/* determines the N-table-optimization         */
   		     	         if( argc != 1 ) 
   				 	optkind.ntaboptkind  = 
   				 	      *(++argv);
#endif

#ifdef DIRPROG  
                /* the next element of argv is the minimal  */
                /* number of common states which an entry   */  
                /* of the N-table must share		    */
                		optkind.nttrapo = YES;
                		if( argc != 1 )
                			if( isnumber(*(++argv)) )
                			      optkind.nocomstat = atoi(*argv);
                			else
                			      errmsg( 
                			 	      BUILDPRS,
                			              BADNUM1ERR,
                			              ABORT,
                			 	     *argv
                			 	    ); 

#endif
                		argc--;
   	        }
   		else if( strequal( *argv, "-t") )  { 
#ifdef TABDRIV
   		/* the next element of argv is the name which */
   		/*determines the nonterminaltable-optimization*/
   		     	         if( argc != 1 ) 
   				 	optkind.ttaboptkind  = 
   				 	      *(++argv);
#endif

#ifdef DIRPROG
                /* the next element of argv is the minimal    */
                /* number of common actions which rows selec- */
                /* ted by the T-table-Code-sharing must share */
                		optkind.codeshare= YES;
                		if( argc != 1 )
                		        if( isnumber(*(++argv)) )
                			      optkind.nocomacts = atoi(*argv);
                			else
                			      errmsg( 
                			 	      BUILDPRS,
                			              BADNUM2ERR,
                			              ABORT,
                			 	     *argv
                			 	    );
#endif
   			        argc--;
   		}
#ifdef DIRPROG
   		else if( strequal( *argv, "-m") ) 
   		/* a function-macro instead of a C-function  */
   		/* is implemented on N-table code-sharing    */
   		                 optkind.macfunc = YES;
   		else if( strequal( *argv, "-s") ) 
   		/* the Minimal-Stack-Checking-Optimization- */
   		/* option is switchewd on                   */
   		                 optkind.stackcheck = YES;  
   		else if( strequal( *argv, "-C") ) {
   		/* the next element of argv is the value which  */
   		/* determines the implementation of jump-tables */
   		                 if( argc != 1 ) {
   		                 	*(++argv); 
   		                	if( strlen(*argv) != 1
   		                     	   || ( (*argv)[0] != 'I'
   		                      	     && (*argv)[0] != 'S')  )
   		                 		errmsg(
   		                 	        	BUILDPRS, 
   		                 	        	BADSEQERR,
   		                 	        	ABORT,
   		                 	               *argv
   		                 	      	      );
   		                 	optkind.condseq = (*argv)[0];
   		                 }
   		                 argc--;
   		}
           
#endif
   		else {	/* the name of the abstract-parser-file */

   	        	if( ! apafnd )  {
   	        	        apafnd = YES;
   	   			apaname = *argv;
   	   		}
   	   		else 
   	   			errmsg( BUILDPRS, DOUBLEAPAERR, ABORT, *argv );
   	   	}
   		     

   }/* while */
   
   if( apaname == NULL )
   	errmsg( BUILDPRS, NOAPAERR, ABORT, DUMMY );
   	
   if( cmrname == NULL )
   	errmsg( BUILDPRS, NOCMRERR, ABORT, DUMMY );
   
#ifdef DIRPROG
   if( ! optkind.nttrapo )
   		optkind.macfunc = NO;
#endif
   
   optkind.chainrule = NO; /* isn't implemented yet */
   		
   if ((fp_comar = fopen(cmrname, "r")) == NULL)
		errmsg(BUILDPRS, FILEERR, ABORT, cmrname);
		
   if ((fp_prsiface = fopen(apaname, "r")) == NULL)
		errmsg(BUILDPRS, FILEERR, ABORT, apaname);
		
   Comar_root = INPUT(fp_comar);/* convert external to internal IDL-format */
   fclose(fp_comar);   

   Abs_parser = ReadAbsparser(fp_prsiface);/* convert ext. to int. IDL-format */
   fclose(fp_prsiface);
   
   /* build the parsing-tables if option TABDRIV is set    */
   /* else construct code for a directly programed parser  */
   build_copa( addinfo, optinfo, optkind, Comar_root, Abs_parser );
   
}/* main */

#else /* macro "FILEOPT" is defined */

#ifdef TABDRIV

static char ttabopt[5] = "RDS"; /* saves the string for T-table-optimization */
static char ntabopt[5] = "RDS"; /* saves the string for N-table-optimization */

#endif


#define LINESIZE 80

#define OPTSIZE  20

#define PARSIZE  20


static void read_options( optkind, fp_option, optinfo )

      optkindtype  *optkind;   /* points to the structure for    */
                               /* the optimization methods       */
      FILE         *fp_option; /* file with backend-options      */
      char         *optinfo;   /* for printing additional in-    */
                               /* formation about backend-       */
                               /* optimization on file "opt.out" */
      
 /*  The backend-options in file "fp_option" points to are selected and 
  *  written to the corresponding components of structure "optkind".
  *
  ***/
  
  {  char inline1[LINESIZE],/* input-line from option-file                   */
          optstr[OPTSIZE],  /* string of an option-symbol                    */
          parstr[PARSIZE];  /* string for the parameter of an option-symbol  */
                            /* an option and its parameter must stand in the */
                            /* same line                                     */
     
     
     fgets(inline1, LINESIZE, fp_option);
     
     while( !feof(fp_option) ){  
     	   if( inline1[0] == '#' || !strlen(inline1) ) goto  cnt_lab; 
     	   /* skip a comment-line or an empty line */
     	   strcpy(optstr, "");
     	   sscanf(inline1, "%s %s", optstr, parstr );
     	   if( strequal( optstr, "" ) ) goto cnt_lab;
     	
     	   if(strequal( optstr, "OPT_INFO" )){ 
     	   /* additional informations are printed out */
           /* on file "opt.out" during optimization   */
     		*optinfo = YES; 
     		goto cnt_lab; 
           }
        
#ifdef TABDRIV

           if(strequal( optstr, "T_TAB" ))
           /* selection of the T-table optimization */
                strncpy(ttabopt, parstr, 4);
           else if(strequal( optstr, "N_TAB" ))
           /* selection of the N-table optimization */
                strncpy(ntabopt, parstr, 4);
#endif

#ifdef DIRPROG

          if(strequal( optstr,  "MIN_T" )) {
          /* selection for constructing common code from the T-Table */
                optkind->codeshare = YES;
                if( isnumber(parstr) )
                        optkind->nocomacts = atoi(parstr);
                else 
                        errmsg( BUILDPRS, BADNUM2ERR, ABORT, parstr );
          }
          else if( strequal( optstr, "MIN_N" )) {
          /* selection for constructing common code from the N-Table */
                optkind->nttrapo   = YES;
                if( isnumber(parstr) )
                        optkind->nocomstat = atoi(parstr);
                else 
                        errmsg( BUILDPRS, BADNUM1ERR, ABORT, parstr );
          }
          else if( strequal( optstr, "MACROS" ))
          /* a function-macro instead of a C-function  */
          /* is implemented on N-table code-sharing    */
                optkind->macfunc = YES;
          else if( strequal( optstr, "MIN_STACK_CTL" ))
          /* the Minimal-Stack-Checking-Optimization- */
          /* option is switchewd on                   */
                optkind->stackcheck = YES;
          else if( strequal( optstr, "SWITCH" ))
          /* jump-tables are implemented as switch-statements */
                optkind->condseq = SWITCH;
#endif
           
cnt_lab : fgets(inline1, LINESIZE, fp_option);

     }/* while */
     
     optkind->chainrule = NO; /* isn't implemented yet */
     
#ifdef DIRPROG

     if( !optkind->nttrapo )
     	optkind->macfunc = NO;
     	
#endif

#ifdef TABDRIV
     
     optkind->ntaboptkind = ntabopt;
     optkind->ttaboptkind = ttabopt;
     
#endif     
     	      
   }/* read_options */


int main( argc, argv )
      int    argc;
      char  *argv[];
      
{
   FILE         *fp_comar,    /* filepointer for COMAR-datastructure       */
   		*fp_prsiface, /* filepointer for the data-structure of     */
   		              /* the abstract parser                       */
   		*fp_option;   /* filepointer for file with backend-options */
   char          optinfo = NO,/* if switched on, additional informatiion   */
                              /* about the optimization is printed on file */
                              /* "opt.out"                                 */
                 addinfo = NO;
   p_comar       Comar_root;  /* the IDL-COMAR-datastructure               */
   absparsertype Abs_parser;  /* the IDL-datastructure for the abstract    */
                              /* parser                                    */
   

   		
   static  optkindtype  optkind  =

#ifdef  TABDRIV  /* a tabledriven parser is generated        */

	{ "RDS", "RDS", NO };
        /* default-names to determine the tableoptimizations */
#endif

#ifdef  DIRPROG /* a directly executable parser is generated */

	{ NO, NO, NO, IFTHEN, NO, NO, 0, 0 };
	           /* predefined values to determine the codeoptimization */
#endif

   if( argc != 3 && argc != 4 )
                errmsg( BUILDPRS, BKEUSERERR, ABORT, DUMMY );
   
   if ((fp_comar = fopen(argv[1], "r")) == NULL)
		errmsg(BUILDPRS, FILEERR, ABORT, argv[1]);
		
   if ((fp_prsiface = fopen(argv[2], "r")) == NULL)
		errmsg(BUILDPRS, FILEERR, ABORT, argv[2] );

   if( argc == 4 ) {
   
           if ((fp_option = fopen(argv[3], "r")) == NULL)
		        errmsg(BUILDPRS, FILEERR, ABORT, argv[3]);
		        
           read_options( &optkind, fp_option, &optinfo );
           
   }

   Comar_root = INPUT(fp_comar);/* convert external to internal IDL-format */
   fclose(fp_comar);   

   Abs_parser = ReadAbsparser(fp_prsiface);/* convert ext. to int. IDL-format */
   fclose(fp_prsiface);

   /* build the parsing-tables if option TABDRIV is set    */
   /* else construct code for a directly programed parser  */
   /* first parameter "addinfo" is always switched off     */
   build_copa( addinfo, optinfo, optkind, Comar_root, Abs_parser );
   
}/* main */

#endif /* FILEOPT */


   		    
   
   
   
   

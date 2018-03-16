/*
** $Id: wrthelpfunc.c,v 1.10 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: wrthelpfunc.c,v 1.10 1997/08/29 08:38:08 mjung Exp $";

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
/* filename: wrthelpfunc.c                    first edit   : 10 .11 . 89      */
/* author  : Christian Zeitel                 last change  : 10 . 8 . 90      */
/******************************************************************************/

/******************************** CONTENTS *************************************
 *									       *
 *  This is the implementation of module wrthelpfunc. It prints the optimized  *
 *  parsertables obtained by a special optmization-method and additional tables*
 *  needed by the concrete parser and which are not obtained by optimization on*
 *  file "ptabs.h".							       *
 *									       *
 ****************************** INCLUDE FILES *********************************/

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "tabsopttype.h"
#include "ptg_gen.h"

#include "wrthelpfunc.h"

/****************************** FUCTION-MACROS ********************************/

#define SIXTEENITEMS( itemcount )  !( itemcount & 0x000F )
/* is true, if 16 items in an outputline are printed, false else */

#define SEVENITEMS( itemcount )  itemcount == 7
/* is true, if  7 items in an outputline are printed, false else */

#define UPPERTETRADE( byte )  byte & 0xF0
/* is true, if the upper tetrade in the bytevalue byte is set, false else */ 

/***************************** CONSTANT-MACROS ********************************/

#define SKIPMASK      0x0001 /* tests the property "is skipsymbol"         */

#define SEPAMASK      0x0002 /* tests the property "is sepasymbol"         */

#define BRACMASK      0x0004 /* tests the property "is bracsymbol"         */
 
#define SEMAMASK      0x0008 /* tests the property "is semantic"           */

#define OFFSET             9 /* is added to a production-code              */

#define NIL		  -1

#define NO                 0

#define YES                1

#define HEX		   0

#define DEC		   1

#define NTAB               0

#define TTAB               1

#define ITEMSPERLINE      11

#define MAXCHARCODE       255

#define MAXSHORTCODE      (1 << 16) - 1

#define MINCHARCODE      -128

#define HALFCHARCODE      127

/******************************************************************************/



typedef  short  *readtype[];

/*============================================================================*/
/*============================================================================*/
/*===================					======================*/
/*===================      INTERFACE-VARIABLES          ======================*/
/*===================           TO MODULE               ======================*/
/*===================            WRTFUNC                ======================*/
/*===================					======================*/
/*============================================================================*/
/*============================================================================*/


short  minterm, /* code of the biggest scannerdefined syntaxcode  */
       maxterm; /* code of the smallest scannerdefined syntaxcode */
       
       

/*============================================================================*/
/*============================================================================*/
/*===================					======================*/
/*===================         INTERNAL FUNCTIONS        ======================*/
/*===================					======================*/
/*============================================================================*/
/*============================================================================*/



static void print_sematab( fp_sema, terminflist )
     
     FILE    *fp_sema;     /* filepointer to file with semantic informati-    */                           /* for terminals                                   */
     char    *terminflist; /* contains the same information as errsymblist    */
                           /* stored in another way                           */
                           
    /*  print_sematab prints a vector "semlst" with the semantic Informations
     *  about the terminalsymbols on file "seminf.h"
     *
     ***/                     
                           
     {  register char bitposition = 0,/*shows the actual bitposition in a byte*/
     		      entry = 0x00;   /* an entry in vector "semlst"          */
     		      
        register short itemcount = 0, /* counts the items in a printed line   */
        	       bound,         /* upper bound for the print-loop       */
        	       i;             /* loop-index			      */
     
     
                         
        fprintf(fp_sema, "/* semantic informations about terminals */\n\n\n");
        fprintf(fp_sema, "#define BASE\t%d\n\n\n", minterm);
        fprintf(fp_sema, "static char semalst[] =  {\n\n");
        
        bound = ( (unsigned short)( maxterm - minterm + 1 ) >> 1 ) + 1;
        
        for( i = 0; i < bound; i++ )  {
          if( bitposition == 8 )  {
          
                  if( SIXTEENITEMS( ++itemcount ) ) {
                                 itemcount  = 0;
                                 fprintf(fp_sema, "\n");
                          }
                          
                  if( UPPERTETRADE( entry ) )
                  
                          fprintf(fp_sema, "0x%-2x,", entry);
                  else
                          fprintf(fp_sema, "0x0%-1x,", entry);
                          
                          
                  entry       = 0x00;
                  bitposition = 0;
          }
          else  {
                 entry |= (char)(( (unsigned char)(terminflist[i] & 0x10) >> 4 ) 
                 		                   << (bitposition + 1));
                 entry |= (char)((terminflist[i] & 0x01) << bitposition);                
                 bitposition += 2;
          }
                
        }/* for i */
      
        if( UPPERTETRADE( entry ) )
                  fprintf(fp_sema, "\n0x%-2x\t};\n", entry);
        else
                  fprintf(fp_sema, "\n0x0%-1x\t};\n", entry);
        
    }/* print_sematab */
      
      						
      		
/*============================================================================*/
/*============================================================================*/
/*===================					======================*/
/*===================      INTERFACE-FUNCTIONS          ======================*/
/*===================           TO MODULE               ======================*/
/*===================            WRTFUNC                ======================*/
/*===================					======================*/
/*============================================================================*/
/*============================================================================*/



void print_table( table, tabname, fp, toobigforchar, numberbase, tabsize )
        
     short  *table;         /* table which is printed   */
     char   *tabname;       /* name of the table        */
     FILE   *fp;            /* filepointer to file on   */
                            /* which table is printed   */
     char    toobigforchar, /* =1, if a value of table  */
                            /* doesn't fit into a byte  */
             numberbase;    /* = HEX if a hex-table and */
                            /* = DEC if a decimal-table */
                            /* is printed               */          
     int     tabsize;       /* size of table            */

  /*  Prints the table given by table with name tabname on file fp points to.
   *  tabsize is the size of table. If numberbase = HEX, hexnumbers are 
   *  printed, if numberbase = DEC, decimal numbers are printed.
   *  If toobigforchar = YES, basetype short is printed for the printed table,
   *  if toobigforchar = NO, basetype unsigned char is printed for the printed
   *  table.
   *
   ***/
   
   {  register int i;         /* loop-index */
   
      if( toobigforchar )
                fprintf(fp, "static unsigned short %s [] =  {\n\n", tabname );
      else
                fprintf(fp, "static unsigned char %s [] =  {\n\n", tabname );
      
      if( numberbase == DEC )  {

      		fprintf(fp, " %6d", *table );
      		
      }
      else  {  /* numberbase == HEX */
				/* Kalle: 0x%4x replaced by 0x%04x */
       		if( *table )
       			fprintf(fp, " 0x%04x", (unsigned short)*table );
       		else
       			fprintf(fp, " 0x0000");
       			
      }
      
      
      for( i = 1; i < tabsize; i++ )  {
                
                if( !( i % ITEMSPERLINE ) )
                        fprintf(fp, "\n" );
                
                if( numberbase == DEC )
               		 fprintf(fp, ",%6d", table[i] );
               		  
                else/* numberbase == HEX */
                
				/* Kalle: 0x%4x replaced by 0x%04x */
                	 if(  table[i] )
                	 	     fprintf(
                	 	     	      fp, 
                	 	     	      ",0x%04x",
                	 	     	      (unsigned short)table[i] 
                	 	     	    );
                         else
                                     fprintf(fp, ",0x0000" );
                                                    
      }/*for i*/
      
      fprintf(fp, "\n};\n\n\n\n");
      
    }/* print_table */



void print_fixtabs( fp, fp_sema, pt_data )
        
     FILE    *fp,          /* the filepointer to file "ptabs.h"               */
             *fp_sema;     /* filepointer to file with semantic informati-    */
                           /* for terminals                                   */
     readtype pt_data;     /* contains all important datas of the con. parser */

  /*  Prints the tables which are not generated by optimization on file
   *  fp is pointing to. The semantic informations about terminals are
   *  written on the file fp_sema is pointing to.
   *
   ***/

  {
         register short  i;          /* loopindex                             */
         register char   bitposition;/* shows the actual bitposition in a byte*/
         register char   itemcount;  /* counts the items per output-line      */
         
         short  index,      /* index in vector terminflist                 */ 
                span,       /* maxterm - minterm + 1              	   */
                bound,      /* upper bound in loops            		   */
                sepacount=0,/* counter for the listseparators              */
               *prodlist,   /* vector to convert internal to       	   */
                            /* external productioncodes         	   */  
               *termlist,   /* vector to convert internal to               */
                            /* external syntaxcodes               	   */ 
               *lhslist,    /* vector to assign each production the code   */
                            /* of its lefthandside nonterminal             */ 
               *lenlist,    /* vector to assign each production its length */  
               *contlist,   /* continuation-automaton which assigns each   */ 
                            /* state an error-symbol                       */
               *errsymblist;/* assigns each terminal its semantic property */  
                            /* and  the error-recovery-properties          */  
         unsigned char 
                entry,        /* an entry in terminflist      	              */
                odd,          /* <>0, if a certain short-value is odd         */
                toobigforchar,/* <>0, if a value is greater than 255          */
               *terminflist;  /* contains the same information as errsymblist */
                              /* stored in another way                        */
                              
        bound    = *pt_data[0];
        termlist =  pt_data[2];
        minterm  =  maxterm = termlist[0];

        
        /* search for the biggest and the smallest scannerdefined sxcode */
        for( i = 0; i < bound; i++ )  {
        
                        if( termlist[i] > maxterm ) 
                                        maxterm = termlist[i];
                        if( termlist[i] < minterm )
                                        minterm = termlist[i];
                                        
        }
        span = maxterm - minterm + 1;
        
        /* count the list-separators */
        errsymblist =  pt_data[11];
        
        for( i = 0; i < bound; i++ )
        	if( errsymblist[i] & SEPAMASK )
        		sepacount++;
        
        /**************************************************************/
        /********** print out  constants ******************************/
        /**************************************************************/
        fprintf(fp, "/* generated constants */\n\n\n");
        fprintf(fp, "#define BASE\t\t%d\n\n", minterm );
        fprintf(fp, "#define PAEOF\t\t%d\n\n", termlist[*pt_data[12]] );
        fprintf(
                 fp,
                 "#define STPROD\t\t%d%s",
                 *pt_data[13],
                 sepacount ? "\n\n" : "\n\n\n\n"
               );    
        if( sepacount )
        	fprintf(fp, "#define NUOFSEPAS\t%d\n\n\n\n", sepacount);
          
        /**************************************************************/
        /********** print out tables **********************************/
        /**************************************************************/
        fprintf(fp, "/* generated tables which are not */\n");
        fprintf(fp, "/* changable by optimization      */\n\n\n");
        
        /**************************************************************/
        /********* conninf contains for each production the infor- ****/
        /********* mation if its reduction causes a connection     ****/
        /**************************************************************/
        bound       = *pt_data[5];
        prodlist    =  pt_data[8];

	/*** no need for conninf since conncode can do it as well ***/
/*      entry       =  0x00;
 *      bitposition =  0;
 *      itemcount   =  0;
 *       
 *      fprintf(fp, "static char conninf[]  =  {\n\n");
 *       
 *      for( i = 0; i < bound; i++ )  {
 *       
 *                       if( bitposition == 8 ) {
 *                       
 *                               itemcount++;
 *                               
 *                               if( UPPERTETRADE( entry ) )
 *                                       fprintf(fp, "0x%-2x,",entry );
 *                               else
 *                                       fprintf(fp, "0x0%-1x,", entry );
 *                                       
 *                               entry        = 0x00;
 *                               bitposition  = 0;
 *                               
 *                               if( SIXTEENITEMS( itemcount ) ) 
 *                                       fprintf(fp, "\n" );
 *                       }
 *                       
 *                      if( prodlist[i] >= 0 )
 *                              
 *                              entry |=  (char)(1 << bitposition);
 *
 *                       bitposition++;
 *       }
 *      
 *      if( UPPERTETRADE( entry ) )
 *              fprintf(fp, "\n0x%-2x\t};\n\n\n\n",entry );
 *      else
 *              fprintf(fp, "\n0x0%-1x\t};\n\n\n\n", entry );
 */
        /***********************************************************/
        /********* conncode assigns each production its  ***********/
        /********* code used by the semantic analysis    ***********/
        /***********************************************************/
        toobigforchar = NO;
        
        for( i = 0; i < bound; i++ ) 
                if ( prodlist[i] + OFFSET > MAXCHARCODE ) {
                        toobigforchar = YES;
                        break;
                }
                
        if( toobigforchar )
                fprintf(fp, "static short conncode[]  =  {\n");
        else
                fprintf(fp, "static unsigned char conncode[]  =  {\n");
        
        for( i = 0; i < bound; i++ )  {
        
                        if( SIXTEENITEMS( i ) )
                                fprintf(fp, "\n");
                                
                        fprintf(
                                 fp,
                                 "%4d%c", 
                                 (prodlist[i] < 0) ? 0 : prodlist[i] + OFFSET, 
                                 (i == bound-1 ? ' ' : ',')
                               );                             
        }/* for */
        fprintf(fp,"\n};\n\n\n\n");
        
        /***************************************************************/
        /********* lhs assigns each production the code ****************/
        /********* code of its lefthandside nonterminal ****************/
        /***************************************************************/
        lhslist       =  pt_data[6];
        toobigforchar =  NO;
        
        for( i = 0; i < bound; i++ )
                if (lhslist[i] > MAXCHARCODE ) {
                        toobigforchar = YES;
                        break;
                }
        
        print_table( lhslist, "lhs", fp, toobigforchar, DEC, bound );
                     
        /**************************************************************/
        /********* len assigns each production its length *************/
        /**************************************************************/
        lenlist       = pt_data[7];
        toobigforchar = NO;
        
        for( i = 0; i < bound; i++ ) 
                if (lenlist[i] > MAXCHARCODE ) {
                        toobigforchar = YES;
                        break;
                }
        
        print_table( lenlist, "len", fp, toobigforchar, DEC, bound );
        
        /*************************************************************/
        /********* cont assigns each state an error-symbol ***********/
        /*************************************************************/
        bound    = *pt_data[9];
        contlist =  pt_data[10];
        toobigforchar = NO;
        
        for( i = 0; i < bound; i++ ) 
                if ( contlist[i] > MAXCHARCODE ) {
                        toobigforchar = YES;
                        break;
                }
                
        if( toobigforchar )
                fprintf(fp, "static short cont[]  =  {\n");
        else
                fprintf(fp, "static unsigned char cont[]  =  {\n");
        
        for( i = 0; i < bound; i++ )  {
                        if( SIXTEENITEMS( i ) )
                                fprintf(fp, "\n");
                        fprintf(fp, "%4d%c", 
                           termlist[contlist[i]], ( i == bound-1 ? ' ' : ',') );      
        }/* for i */
        
        fprintf(fp,"\n};\n\n\n\n");

        /*************************************************************/
        /*** print the list seps  containing the list-separators *****/
        /*************************************************************/                 bound       = *pt_data[0];
        
        if( sepacount ) {
        
           if( maxterm > MAXCHARCODE )
        	  toobigforchar = YES;
           else
        	  toobigforchar = NO;
        
           if( toobigforchar )
                  fprintf(fp, "static short seps[]  =  {\n\n");
           else
                  fprintf(fp, "static unsigned char seps[]  =  {\n\n");
        
           itemcount = 0;
           
           for( i = 0; i < bound; i++ )
           	  if( errsymblist[i] & SEPAMASK )   {
           	             	        
           	  	if( SIXTEENITEMS( ++itemcount ) )
           	             	  fprintf(fp, "\n" );

           	  	fprintf(
           	  	         fp,
           	  	         "%4d%c",
           	  	         termlist[i],
           	  	         ( itemcount == sepacount ? '\n' : ',')
           	  	       );
           	  }/* if */
            
           fprintf(fp, "};\n\n\n\n");
           	  
        }/* if( sepacount ) */
        
        /************************************************************/
        /********* terminf assigns each terminal the properties *****/
        /********* - if it is an unsave restarting-point ************/
        /********* - if it is a  semantic bracket        ************/
        /************************************************************/
        
        if((terminflist = (unsigned char *)calloc( ((span+1) >> 1)+1, sizeof(unsigned char))) == NULL)
                  errmsg(WRTHELPFUNC, NOSPACEERR, ABORT, DUMMY);
        
        for( i = 0; i < bound; i++ )  {
                        index = ( termlist[i] - minterm ) >> 1;     /* div 2 */
                        odd   = ( termlist[i] - minterm ) & 0x0001; /* mod 2 */
                        if( errsymblist[i] & SKIPMASK )
                                        terminflist[index] |= 
                                                      ( odd ? 0x40 : 0x04 );
                        if( errsymblist[i] & BRACMASK )
                                        terminflist[index] |= 
                                                      ( odd ? 0x20 : 0x02 );
                        if( errsymblist[i] & SEMAMASK )
                                        terminflist[index] |= 
                                                      ( odd ? 0x10 : 0x01 );
        }/* for i */
        
        bound = ( span + 1 ) >> 1;
        entry = 0x00;
        fprintf(fp, "static char terminf[]  =  {\n");
        
        for( i = 0; i < bound; i += 2 )  {
                        if( SIXTEENITEMS( i>>1 ) )
                                fprintf(fp, "\n");
                        
                        entry |= (unsigned char)(terminflist[i] & 0x06) >> 1;
                        entry |= (unsigned char)(terminflist[i] & 0x60) >> 3;
                        entry |= (terminflist[i+1] & 0x06) << 3;
                        entry |= (terminflist[i+1] & 0x60) << 1;
                                
                        if( UPPERTETRADE( entry ) )
                                fprintf(fp, "0x%-2x%c", 
                                   entry, (i >= bound-1 ? ' ' : ',') );                
                        else
                                fprintf(fp, "0x0%-1x%c",
                                   entry, (i >= bound-1 ? ' ' : ',') ); 
                        
                        entry = 0x00;
                             
        }/* for i */
        
        fprintf(fp,"\n};\n\n\n\n");
        
        /**************************************************************/
        /*************** print_sematab prints the se-  ****************/
        /*************** mantic functions about ter-   ****************/
        /*************** minals on file "seminf.h"     ****************/
        /**************************************************************/
        
        print_sematab( fp_sema, (char*)terminflist );
        
   }/* print_fixtabs */



      

void print_label( tabkind, fp, optkind )

     char  tabkind; /* T for terminaltabe, N for nonterminaltable        */
     FILE *fp;      /* filepointer to file on which the label is printed */
     char  optkind; /* specifies the optimization-method            */
        
  /*  print_label prints a macro-name for the selected optimization-method
   *  given by optkind and the selected table ( terminal or nonterminal )
   *  on file given by filepointer fp.
   *
   ***/
   
   { 
      PTGNode	node;
      
      if( tabkind == NTAB )
      {
        fprintf(fp, "/* macro for accessing the nonterminal-table */\n");
	switch (optkind)
	{
	  case _MRCSA: node = PTGNOPT_RCSA(); break;
	  case _MGCS:  node = PTGNOPT_GCS(); break;
	  case _MLES:  node = PTGNOPT_LES(); break;
	  case _MRDS:  node = PTGNOPT_RDS(); break;
	  case _MSDS:  node = PTGNOPT_SDS(); break;
	  case _MRCSB: node = PTGNOPT_RCSB(); break;
	}
	PTGOutFPtr(fp, node);
      }
      else
      {
	fprintf(fp, "/* macro for accessing the terminal-table */\n");
	switch (optkind)
	{
	  case _MRCSA: node = PTGTOPT_RCSA(); break;
	  case _MGCS:  node = PTGTOPT_GCS(); break;
	  case _MLES:  node = PTGTOPT_LES(); break;
	  case _MRDS:  node = PTGTOPT_RDS(); break;
	  case _MSDS:  node = PTGTOPT_SDS(); break;
	  case _MRCSB: node = PTGTOPT_RCSB(); break;
	}
	PTGOutFPtr(fp, node);
      }

   }/* print_label */



void print_errmat( fp, not, nos, noc, rowptr, colptr, ttab )

     FILE  *fp;    /* the filepointer to file "ptabs.h"                 */
     short  not,   /* number of terminals 			        */
            nos,   /* number of states					*/
            noc,   /* number of columns in the commpressed errormatrix  */
           *rowptr,/* if rowptr[i] == i, the row is printed 		*/
           *colptr,/* if colptr[j] == j, the column  is printed         */
           *ttab;  /* terminaltable 					*/
 
  /*  Prints the negated error-matrix sigmap on the file, fp is pointing to.
   *
   ***/
   
   {    register int   itemcount = 0; /* counts the items in a printed line   */
        register short i, j;          /* loop-indicees			      */
        register char  entry,         /* entry in the compressed error-matrix */
        	       bitpos,        /* shows the actual bitposition in entry*/
                       start = YES;   /* = NO after the first print           */


        fprintf(fp, "static unsigned char sigmap[][%d] =  {\n\n", noc );
        for( i = 0; i < nos; i++ )
                if( rowptr[i] == i )  {
                        bitpos = 0;
                        entry  = 0x00;
                        
                        for( j = 0; j < not; j++ )
                        
                                if( colptr[j] == j )  {
                                        
                                        if( ttab[ i * not + j ] )
                                                entry |= (char)( 1 << bitpos );
                                        
                                        if( ++bitpos == 8 )  {
                                        
                                                itemcount++;
                                                
                                                if( UPPERTETRADE( entry ) )  {
                                                
                                                    fprintf(fp, "%c0x%-2x",
                                                    ((start == YES)? ' ' : ','),
                                                    (unsigned char)entry );     
                                                }
                                                else {
                                                
                                                    fprintf(fp, "%c0x0%-1x",
                                                    ((start == YES)? ' ' : ','),
                                                    (unsigned char)entry );
                                                }
                                                start   = NO;
                                                bitpos  = 0;
                                                entry   = 0x00;
                                                
                                                if( SIXTEENITEMS( itemcount ) )
                                                        fprintf(fp, "\n");
                                                        
                                        }
                                 }
                                
                                 if( bitpos != 0 )  { /* print actual byte */
                                 
                                        itemcount++;
                                        
                                        if( UPPERTETRADE( entry ) )
                                                fprintf(fp, "%c0x%-2x",
                                                    ((start == YES)? ' ' : ','),
                                                    (unsigned char)entry );
                                        else
                                                fprintf(fp, "%c0x0%-1x",
                                                    ((start == YES)? ' ' : ','),
                                                    (unsigned char)entry );
                                        
                                        start = NO;
                                        
                                        if( SIXTEENITEMS( itemcount ) )
                                                fprintf(fp, "\n");
                                }
                }
        
        fprintf(fp,"\n};\n\n\n\n" );
     
     }/* print_errmat */





void print_GCSptab( fp, tabkind, size, noc, ptab )

     FILE  *fp;      /* the filepointer to file "ptabs.h"            */
     char   tabkind; /* = TTAB for T-table, =NTAB for N-Table        */
     short  size,    /* number of entries in the optimzed parsetable */
            noc,     /* number of columns in parse-table ptab        */
           *ptab;    /* optimized terminaltable or nonterminaltable  */
  
  /*  Prints the parsertable ptab for which tabkind decides, if it is a 
   *  terminal- or a nonterminal-parsertable on the file fp is pointing to.
   *  Optimization-method is the Graph-Colouring-Scheme.
   *
   ***/
   
   {  register  int  i; /* loopindex */
      
      fprintf(
      	       fp,
      	       "static unsigned short %ctab[][%d] =  {\n",
      	       ( ( tabkind == TTAB ) ? 't' : 'n' ),
               noc
               
             );
        
      for( i = 0; i < size; i++ ) {
        
                if( !( i % ITEMSPERLINE ) )
                        fprintf(fp, "\n");
                
                if ( ptab[i] )
                        fprintf(
                                 fp,
                                 "0x%-4x%c", 
                                 (unsigned short)ptab[i],
                                 (i == size-1 ? ' ' : ',')
                               );                
                else
                        fprintf(fp, "0x0000%c", (i == size-1 ? ' ' : ',') );
        
      }/* for i */
                
      fprintf(fp, "\n};\n\n\n\n" );
        
        
   }/* print_GCSptab */






void print_LESptab( fp, tabkind, nor, noc, ptab, opt_data )

     FILE    *fp;       /* the pointer to file "ptabs.h"		 */
     char     tabkind;  /* =TTAB for the T-Table, =NTAB for the N-Table  */
     short    nor,      /* number of rows in ptab                        */
              noc,      /* number of columns in ptab		 	 */
             *ptab;     /* terminal-table or nonterminal-table           */
     opttype *opt_data; /* results about the LES-optimization            */
  
  /*  Prints the parsertable ptab for which tabkind decides, if it is a 
   *  terminal- or a nonterminal-parsertable on the file,fp is pointing to.
   *  Optimization-method is the Line-Elimination-Scheme.
   *
   ***/	
   
   {
      register char  itemcount  = -1;/* counts the items printed in a line   */
      register short i, j;           /* loopindicees			     */
      register int   entrycount =  0,/* counts the number of enties in ptab  */
          	     noe;            /* the number of entries in ptab        */
      short  elrows, /* number of eliminated rows     			     */
             elcols, /* number of eliminated columns			     */
            *rowptr, /* rowmapping from not-optimized to optimized ptab      */
            *colptr, /* column-mapping from not-optimized to optimized ptab  */
             maxscan;/* highest scan-number                                  */
             
                        
        if( tabkind == TTAB ) {
            elrows    = opt_data->ttabopt.LES.elrows;
            elcols    = opt_data->ttabopt.LES.elcols;
            rowptr    = opt_data->ttabopt.LES.decrow;
            colptr    = opt_data->ttabopt.LES.deccol;
            maxscan   = opt_data->ttabopt.LES.scans;
         }
         else  {
            elrows    = opt_data->ntabopt.LES.elrows;
            elcols    = opt_data->ntabopt.LES.elcols;
            rowptr    = opt_data->ntabopt.LES.decrow;
            colptr    = opt_data->ntabopt.LES.deccol;
            maxscan   = opt_data->ntabopt.LES.scans;
        }
            

        if( elrows == nor || elcols == noc )
            
                /* all rows and columns are eliminated */
                fprintf(
                         fp,
                         "static unsigned short %ctab[][1] = { 0x0000 };\n\n\n\n",
                         ( (tabkind == TTAB) ? 't' : 'n' )
                         
                       );
                
        else  {
                noe       =  ( noc - elcols ) * ( nor - elrows );
                fprintf(
                         fp, 
                         "static unsigned short %ctab[][%d] = {\n\n",
                         ( ( tabkind == TTAB) ? 't' :'n' ),
                         noc - elcols 
                       );
                
                for( i = 0; i < nor; i++ )
                
                        if( rowptr[i] == maxscan )
                        
                                for( j = 0; j < noc; j++ )
                                
                                        if( colptr[j] == maxscan )  {
                                        
                                              entrycount++;
                                              
                                              if( ++itemcount == ITEMSPERLINE) { 
                                                   fprintf(fp,"\n");
                                                   itemcount = 0;
                                              }
                                              
                                              if( ptab[ i * noc + j ] )
                                              
                                                  fprintf(
                                                           fp,
                                                           "0x%-4x%c",
                                                           ( unsigned short )   
                                                           ptab[ i * noc + j ],
                                                           ( entrycount == noe ?
                                                              '\n' 
                                                            : ','
                                                           )
                                                          );
                                              else
                                                  fprintf( 
                                                           fp,
                                                           "0x0000%c",
                                                           ( entrycount == noe ?
                                                              '\n' 
                                                            : ','
                                                           )
                                                         );
                                        }
                                        
                fprintf(fp, "\n};\n\n\n\n" );
                
         }/* else */
         
      }/* print_LESptab */






void print_LESeltab( val, dec, scans, name, fp, size )

     short *val,   /* vector containing the eliminated values 		*/
           *dec,   /* scan-numbers, on which the values were eliminated */
            scans; /* highest scan-number				*/
     char  *name;  /* name of the printed table				*/
     FILE  *fp;    /* filepointer to file "ptabs.h"			*/
     short  size;  /* size of the printed table				*/
  
  /*  Prints the table of eliminated values for the
   *  rows or the columns of the terminal- or a nonterminal-parsertable
   *  computed during the Line-Elimination-Scheme on the file fp is pointing to.
   *
   ***/
   
   {  register short i;             /* loop-index */
          
      fprintf(fp, "static unsigned short %s[] = {\n", name );
      
      for( i = 0; i < size; i++ ) {
      		
      		if( !( i % ITEMSPERLINE ) )
      			fprintf(fp, "\n" );
      			
      		if( dec[i] == scans )
      			fprintf(
      				 fp, 
      				 "%6d%c",
      				 val[i],
      				 (( i == size -1 ) ? ' ' : ',' )
      			       );
      		else 
      		        if( val[i] )	
				fprintf(
      				 	fp, 
      				 	"0x%-4x%c",
      				 	(unsigned short)val[i],
      				 	(( i == size -1 ) ? ' ' : ',' )
      			       	       );
      			else
      				fprintf(
      				         fp,
      				         "0x0000%c",
      				         (( i == size -1 ) ? ' ' : ',' )
      			       	       );
      }/* for i */
      
      fprintf(fp, "\n};\n\n\n\n");
    
    }/* print_LESeltab */






void print_SDSptab( fp, tabkind, nor, noc, ptab, firstptr, lastptr )

     FILE  *fp;       /* filepointer to file "ptabs.h"                     */
     char   tabkind;  /* =TTAB for T-Table, =NTAB for N-Table              */
     short  nor,      /* number of rows of ptab				   */
            noc,      /* number of columns of ptab			   */
           *ptab,     /* terminaltable or nonterminaltable		   */
           *firstptr, /* rowptr[i] is the first significant entry in row i */
           *lastptr;  /* lastptr[i] is the last significant entry in row i */
			  
  /*  Prints the parsertable optimized by method Signifcant-Distance-Scheme on
   *  the file fp is pointing to. firstptr[i] gives the index of the fifst sig-
   *  nificant entry in row i, lastptr[i] gives the last significant entry in
   *  row i.
   *
   ***/
   
   {  register short i, j;          /* loopindicees                           */
      register char itemcount = -1; /* counts the items ina line for printing */
      
      
      fprintf(
               fp,
               "static unsigned short %ctab[] = {\n\n",
               ( (tabkind == TTAB) ? 't' :'n' )
               
             );
      
      
      for( i = 0; i < nor; i++)
      
             if( lastptr[i] != NIL )
             		
             		for( j = firstptr[i] ; j <= lastptr[i]; j++ ) {
             			
             			itemcount++;
             			
             			if( itemcount == ITEMSPERLINE  )  {
             				fprintf(fp, "\n" );
             				itemcount = 0;
             			}
             			
             			if( ptab[ i * noc + j ] )
             		
             		            fprintf(
             		        	     fp,
             		        	     "0x%-4x,",
             		        	     (unsigned short)ptab[ i * noc + j ]
             		        
             		                   );
             		        else
             		           fprintf( fp, "0x0000,");
             		           
             		}/* for j */
             		
      fprintf(fp, "\n0x0000};\n\n\n\n");
      
    }/* print_SDSptab */





void print_rptrtab( fp, tabkind, nor, rowptr )

     FILE  *fp;      /* filepointer to file "ptabs.h"        */
     char   tabkind; /* =TTAB for T-table, =NTAB for N-Table */
     short  nor;     /* length of rowpointertable            */
     int   *rowptr;  /* rowpointertable                      */
  
  /*  Prints the rowpointer-table which is used by optimization-methods 
   *  Row-Displacement-Scheme and Significant-Distance-Scheme on the
   *  file fp is pointing to.
   *
   ***/ 
   
   {  register short  i;	      /* loop-index			    */
      register char   itemcount = -1; /* counts the items printed in a line */
      int min =  0, /* stores the minimum of vector rowptr  */
          max = -1; /* stores the maximum of vector rowptr  */
      /* names of the base-types for the printed array rowptr[] */
      static char *typename[4] = { "int", "short", "char", "unsigned char" };
            
      
      
      for( i = 0; i < nor; i++ )  {
      
         if( rowptr[i] < min ) min = rowptr[i];
         if( rowptr[i] > max ) max = rowptr[i];
         
      }/* for i */
      
      if( max > MAXSHORTCODE ) 
                /* base-type of the printed array is int   */
      		i = 0;
      else if( max > MAXCHARCODE  &&  max <= MAXSHORTCODE )
      		/* base-type of the printed array is short */
      		i = 1;
      else if( min < 0 && min >= MINCHARCODE && max <= HALFCHARCODE )
                /* base-type of the printed array is char  */
                i = 2;
      else if( min >= 0 && max <= MAXCHARCODE )
      		/* base-type of the printed array is unsigned char  */
      		i = 3;
      
      fprintf(
               fp, 
               "static %s %crowptr[] = {\n",
               typename[i],
               ( (tabkind == TTAB) ? 't' : 'n')
             );
             
      for( i = 0; i < nor; i++ ) {
        
        	itemcount++;
        	
        	if( !( i % ITEMSPERLINE ) )
        		fprintf(fp, "\n");
         	
         	
         	fprintf(
         	         fp, 
         	         "%6d%c",
         	         rowptr[i],
         	         ( (i == nor -1) ? ' ' : ',' )
         	         
         	       );
      }/* for i */
      
      fprintf(fp, "\n};\n\n\n\n");
      
   }/* print_rptrtab */


      

void print_RCSAptab( fp, tabkind, nor, noc, ptab, termlist )

     FILE *fp;       /* the filepointer to file "ptabs.h"      */
     char tabkind;   /* = TTAB for T-table, =NTAB for N-Table  */
     short nor,      /* number of rows of ptab                 */
           noc,      /* number of columns of ptab              */
          *ptab,     /* T-table or N-table                     */
          *termlist; /* maps internal to external syntaxcodes  */
			   
  /*  Prints the parsertable ptab for which tabkind decides, if it is a 
   *  terminal- or a nonterminal-parsertable on the file fp is pointing to.
   *  Optimization-method is the simple Row-Column-Scheme, which is
   *  only used for test-purposes.
   *
   ***/
   
   {  register short i, j;         /* loop-indicees			      */
      register int   entry;        /* entry in the printed ptab		      */
      register char  itemcount = 0;/* counts the number of items for printing */
      
      
      
      fprintf(
      		fp, 
      		"static int %ctab[]  =  {\n\n", 
      		( (tabkind == TTAB) ? 't' : 'n')
             );
         
      for( i = 0; i < nor; i++ )
                for( j = 0; j < noc; j++ )  {
                
                                if( ptab[i * noc + j] )  {
                                
                                        entry = (int)(ptab[i * noc + j] << 16)
                                                       | ( (tabkind == TTAB) ? 
                                                              (int)termlist[j]
                                                            : (int)j
                                                         );
                                        fprintf(fp, "0x%-8x,", entry );
                                        
                                        if( SEVENITEMS( ++itemcount ) ) {
                                                fprintf(fp, "\n");
                                                itemcount = 0;
                                        }
                                }
                }/* for j*/
                 
     fprintf(fp, "\n0x0\t};\n\n\n\n");
   
   }/* print_RCSAptab */





void print_RCSAbase( fp, tabkind, nor, noc, ptab )

     FILE *fp;       /* the filepointer to file "ptabs.h"      */
     char tabkind;   /* = TTAB for T-table, =NTAB for N-Table  */
     short nor,      /* number of rows of ptab                 */
           noc,      /* number of columns of ptab              */
          *ptab;     /* T-table or N-table                     */     
  
  /*  Prints helping-vector base on file fp is pointing to. Its needed for
   *  determing an entry in the parsertable produced by function print_TSTptab.
   *
   ***/
   
   {  register  short i,j,            /* loop-indicees                        */
   		      sigentcount = 0;/* number of signifcant entries in a row*/
      register  char  itemcount = -1; /* counts the items printed in a line   */
      
      
      fprintf(
               fp,
               "static int %cbase[]  =  { 0,\n\n",
               (( tabkind == TTAB ) ? 't' : 'n')
             );
         
      for( i = 0; i < nor; i++ )  {
         
                for( j = 0; j < noc; j++ ) 
                 
                        if( ptab[i * noc +j] )
                                 sigentcount++;
                                 
                if( ++itemcount  == ITEMSPERLINE ) {
                        fprintf(fp, "\n");
                        itemcount = 0;
                }
                
                fprintf(fp, "%6d,", sigentcount);
                
      }/* for i */
         
      fprintf(fp, "\n0\t};\n\n\n\n");
         
   }/* print_RCSAbase */



	    

void print_RCSBptab(fp, tabkind, nor, noc, ptab, rowptr, termlist)

     FILE *fp;       /* the filepointer to file "ptabs.h"      */
     char tabkind;   /* = TTAB for T-table, =NTAB for N-Table  */
     short nor,      /* number of rows of ptab                 */
           noc,      /* number of columns of ptab              */
          *ptab,     /* T-table or N-table                     */
          *rowptr,   /* mpas the rows of the optimized parse-  */
                     /* table to the rows of the not-optimized */
                     /* parse-table			       */
          *termlist; /* maps internal to external syntaxcodes  */
  
  /*  Prints the parsertable ptab for which tabkind decides, if it is a 
   *  terminal- or a nonterminal-parsertable on the file, fp is pointing to.
   *  Optimization-method is the Row-Column-Scheme.
   *
   ***/
   
   {  register short i, j;         /* loop-indicees			      */
      register int   entry;        /* entry in the printed ptab		      */
      register char  itemcount = 0;/* counts the number of items for printing */
      
      
      
      fprintf(
      		fp, 
      		"static int %ctab[]  =  {\n\n", 
      		( (tabkind == TTAB) ? 't' : 'n')
             );
         
      for( i = 0; i < nor; i++ )
      
         if( rowptr[i] == i )
         
                for( j = 0; j < noc; j++ )  {
                
                                if( ptab[i * noc + j] )  {
                                
                                        entry = (int)(ptab[i * noc + j] << 16)
                                                       | ( (tabkind == TTAB) ? 
                                                              (int)termlist[j]
                                                            : j
                                                         );
                                        fprintf(fp, "0x%-8x,", entry );
                                        
                                        if( SEVENITEMS( ++itemcount ) ) {
                                                fprintf(fp, "\n");
                                                itemcount = 0;
                                        }
                                }
                }/* for j*/
                 
     fprintf(fp, "\n0x0\t};\n\n\n\n");
   
   }/* print_RCSBptab */





void print_RCSBbase( fp, tabkind, nor, noc, ptab, rowptr )

     FILE *fp;       /* the filepointer to file "ptabs.h"      */
     char tabkind;   /* = TTAB for T-table, =NTAB for N-table  */
     short nor,      /* number of rows of ptab                 */
           noc,      /* number of columns of ptab              */
          *ptab,     /* T-table or N-table                     */
          *rowptr;   /* mpas the rows of the optimized parse-  */
                     /* table to the rows of the not-optimized */
                     /* parse-table			       */ 
  
  /*  Prints the helping-vector base on file fp is pointing to. Its needed for
   *  determing an entry in the parsertable produced by function print_RCSptab.
   *
   ***/
   
   {  register  short i,j,             /*loop-index                          */
   		      sigentcount = 0; /*number of signifcant entries in a row*/
      register  char  itemcount   = -1;/*counts the items printed in a line   */
      
      
      fprintf(
               fp,
               "static int %cbase[]  =  { 0,\n\n",
               (( tabkind == TTAB ) ? 't' : 'n')
             );
         
      for( i = 0; i < nor; i++ )  {
      
          if( rowptr[i] == i )  {
         
                for( j = 0; j < noc; j++ ) 
                 
                        if( ptab[i * noc +j] )
                                 sigentcount++;
                                 
                if( ++itemcount  == ITEMSPERLINE ) {
                        fprintf(fp, "\n");
                        itemcount = 0;
                }
                
                fprintf(fp, "%6d,", sigentcount);
                
          }/* if */
                
      }/* for i */
         
      fprintf(fp, "\n0\t};\n\n\n\n");
         
   }/* print_RCSBbase */

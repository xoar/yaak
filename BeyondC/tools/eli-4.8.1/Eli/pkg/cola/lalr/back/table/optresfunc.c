/*
** $Id: optresfunc.c,v 1.5 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: optresfunc.c,v 1.5 1997/08/29 08:38:08 mjung Exp $";

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
/* filename: optresfunc.c                     first edit   :  7 .11 . 89      */
/* author  : Christian Zeitel                 last change  : 10 . 7 . 90      */
/******************************************************************************/

/******************************** CONTENTS *************************************
 *									       *
 *  This file contains the implementation of module optresfunc. It contains    *
 *  functions to write the results of every optimization-scheme on file        *
 *  fp_opt is pointing to. 						       *
 *									       *
 *******************************INCLUDE-FILES *********************************/

#include <stdio.h>

#include <string.h>

#include "opthelptype.h"

#include "tabsopttype.h"

/****************************** CONSTANT-MACROS *******************************/

#define OPERANDMASK   0x0FFF

#define ACTIONMASK    0x000F

#define GCS_OPT       0

#define LES_OPT       1

#define RDS_OPT       2

#define SDS_OPT       3

#define RCS_OPT       4

#define MINLINE  "-----------------------------------------------------------\n"

#define STARLINE "***********************************************************\n"

#define ROW           0

#define COL           1

#define NTAB          0

#define TTAB          1

#define NO	      0

#define YES	      1

#define NIL          -1

#define ITEMSPERLINE 11

/******************************************************************************/

/*============================================================================*/
/*============================================================================*/
/*==================                                    ======================*/
/*==================       INTERNAL DECLARATIONS        ======================*/
/*==================        				======================*/
/*============================================================================*/
/*============================================================================*/

static char *rcword[2] = { "row", "column" },
   	    *ntword[2] = { "nonterminal-table", "terminal-table" };
   	    
   	    

static char *conv_tabval( value )

		 unsigned short value;
		
	  /*  converts an entry of a terminal- or nonterminal-parsertable into a 
	   *  symbolic string.
	   *
	   ***/
	   
	   {  static char *actlst[10] = { "error", "shift ","reduce", "", "shred ", "",
						    "shr_nt", "", "accept", "sht_nt"  };
				      /* actlst contains the parsertableactions     */
	      char s[7];              /* the symbolstring obtained from value       */
	      static char
		   returnstring[15];  /* symbolstring which is returned             */
	      
	      register short i, j,    /* loopindices */
			     n;
	      
	      register char c, 
			    index;   /* index of actlst */
	      
		  
	      i     =  0;
	      n     =  value & OPERANDMASK;
	      index =  ( value >> 12 ) & (unsigned short)ACTIONMASK;
      
      if( index == 0 || index == 8 )
      		return( actlst[index] );
       
      do {
      	
      	s[i++] = n % 10 + '0';
      	
      }
      while( ( n /= 10 ) > 0 );
      
      s[i] = '\0';
      
      /* invert string s */
      for( i = 0, j = strlen( s ) - 1; i < j; i++, j--) {
      		c    = s[i];
      		s[i] = s[j];
      		s[j] = c;
      
      }
      
      strcpy( returnstring, "");
      
      /* compose action and operand */
      strcat( returnstring, actlst[index] );
      strcat( returnstring, "  " );
      strcat( returnstring, s );
      
      return( returnstring );

   }/* conv_tabval */






static short no_of_sigents( row, len )

        short   *row,  /* a row in a parse table  */
                 len;  /* length of this line     */
                 
 /*  sigent returns the number of significant entries in row row
  *  of a parse-table.
  *
  ***/
  
  {  register  short   i,
                       counter = 0;
     
     for( i = 0; i < len; i++ )
     
        if( row[i] ) 
                counter++;
     
     return( counter );
     
  }/* no_of_sigents */




static void print_opthead( fp_opt, optkind, tabkind )

	FILE *fp_opt; /* pointer to the file on which the optimizationre- */
		      /* sults are printed				  */
	char  optkind,/* the selected optimization-method		  */
	      tabkind;/* kind of parsertable- T-table or N-table          */
	
	
 /*  Prints a protocoll-head containing the informations which optimization-
  *  method was applicated to a parse-table and which kind of parse-table
  *  was optimized.
  *
  ***/
  
  {  static char *tabnames[2] =  {
                      "*            nonterminal-table               *",
  	              "*              terminal-table                *" 
     };
     
     char *starline = "**********************************************";
     char *textline = "*  Optimization-Results for Application of   *";
     
     static char *optschemes[5] =   {
     
     		      "*    the Graph-Colouring-Scheme  to the      *",
     		      "*    the Line-Elimination-Scheme to the      *",
     		      "*    the Row-Displacement-Scheme to the      *",
     		      "*  the Significant-Distance-Scheme to the    *",
     		      "*       the Row-Column-Scheme to the         *"
     };
         
     
     fprintf(fp_opt, "%s\n", starline );
     fprintf(fp_opt, "%s\n", textline );
     fprintf(fp_opt, "%s\n", optschemes[ optkind ] );
     fprintf(fp_opt, "%s\n", tabnames[ tabkind ] );
     fprintf(fp_opt, "%s\n", starline );
     fprintf(fp_opt, "\n\n" );
     
  }/* print_opthead */





static void print_storesize( fp_opt, oldsize, optsize )

	FILE *fp_opt;/* pointer to the file on which the optimizationre- */
		     /* sults are printed				 */
	int oldsize, /* size of the notoptimized parsetable              */
	    optsize; /* size of the optimized parsetable                 */
	    
 /*  Prints the size of the not optimized parsetable, the size of the opti-
  *  mized parse-table and the percentage optimized size/ notoptimized size
  *  on the file fp_opt is pointing to.
  *
  ***/
  
  { char *text1 = "storagesize of the notoptimized parse-table    : ",
         *text2 = "storagesize of the optimized parse-table       : ",
         *text3 = "percentage optimized size / notoptimized size  : ";
    
    
    fprintf(fp_opt, "\n\n");
    fprintf(fp_opt, MINLINE );
    fprintf(fp_opt, "%s%-5d byte\n", text1, oldsize);
    fprintf(fp_opt, "%s%-5d byte\n", text2, optsize);
    fprintf(fp_opt, "%s%4.2f %%\n", text3, 100.0 * optsize / oldsize );
    fprintf(fp_opt, MINLINE );
    fprintf(fp_opt, "\n\n");
    
  }/* print_storesize */





static void print_errmatoptres( fp_opt, rowptr, colptr, size, nos, not )

	FILE *fp_opt;  /* pointer to the file on which the optimizationre- */
		       /* sults are printed				   */
	short *rowptr, /* maps each rowindex of the terminaltable on the   */
		       /* smallest rowindex the first row is equal with    */
	      *colptr, /* the same with columns				   */
	       size,   /* size of the compressed errormatrix               */
	       nos,    /* number of states 				   */
	       not;    /* number of terminals				   */

 /* Prints the optimizationresults for compressing the negated error-matrix 
  * on the file fp_opt is pointing to.
  *
  ***/
  
  {  register short i; /* loopindex */
     
     
     
     fprintf(fp_opt,"(A) outfactoring of the negated error-matrix :\n\n");
     fprintf(fp_opt,"The following rows of the error-matrix are equal:\n\n");
     fprintf(fp_opt,"(The second row is the row with the smallest index )\n");
     fprintf(fp_opt,"(for which the first and the second row are equal !)\n\n");
     
     
     for( i = 0; i < nos; i++ )
        fprintf(fp_opt, "row %-3d is equal to row %-3d\n", i, rowptr[i] );
             
     fprintf(fp_opt,"\n\n");
     fprintf(fp_opt,"The following columns of the error-matrix are equal :");
     fprintf(fp_opt,"\n\n");
     fprintf(fp_opt,"(The second column is the column with the          )\n");
     fprintf(fp_opt,"(smallest index for which the first and the second )\n");
     fprintf(fp_opt,"(column are equal !                                )");
     fprintf(fp_opt,"\n\n");

             
     for( i = 0; i < not; i++ )
     	fprintf(fp_opt, "column %-3d is equal to column %-3d\n",i,colptr[i] );
             
     fprintf(fp_opt,"\n\n");
     fprintf(fp_opt,"size of the compressed errormatrix : %-3d byte\n", size );
     fprintf(fp_opt, MINLINE );
     fprintf(fp_opt, "\n\n");
     
  }/* print_errmatoptres */
                    

     
  			     
	
/*============================================================================*/
/*============================================================================*/
/*==================                                    ======================*/
/*==================       INTERFACE-FUNCTIONS          ======================*/
/*==================        TO MODULE OPTFUNC		======================*/
/*==================                    		======================*/
/*============================================================================*/
/*============================================================================*/


void print_GCSoptres( fp_opt, tabkind, opt_data, pt_data, colourmap, 
		      partition, sortinfo, rowcolkind    )


     FILE          *fp_opt;    /* pointer to the file on which the           */
		               /* optimizationresults are printed	     */
     char           tabkind;   /* =TTAB for T-table, = NTAB for N-table      */
     opttype       *opt_data;  /* interface from optimization-module         */
                               /* to output-module                           */
     readtype       pt_data;   /* interface from input-module to             */
      			       /* optimization-module                        */
     short         *colourmap; /* colourmap[i] counts the number of rows or  */
                               /* columns which are coloured with colour     */
                               /* number i                                   */ 
     partitiontype  partition; /* the nodepartition induced by the colouring */
     char           sortinfo,  /* =YES if the nodes of the collisiongraph are*/
     			       /* sorted with decreasing node-degree as key  */
                    rowcolkind;/* = ROW if the rows are optimized, = COL if  */
                    	       /* the columns are optimized		     */    			    
  /*  prints the optimization-results of optimization-method Row-Column-Scheme
   *  on file fp_opt points to.
   *
   ***/
   
   {  short nos, /* number of states              */
   	    not, /* number of terminals           */
   	    non, /* number of nonterminals   	  */      
   	    norc;/* number of rows or columns of  */
   	    	 /* the optimized parse-table     */
   	    	 
   	    	 
   	    	 
   	    	 
   	    	 
      static char *rctext[2] = { "Results of the row-colouring",
   	                         "Results of the column-colouring"
   	                       },
   	   
   	          *nttext[4]  = { "for the nonterminal-table:",
   	                          "for the terminal-table:",
   	                          "for the rowoptimized nonterminaltable:",
   	                          "for the rowoptimized terminaltable:"
   	                        },
   	   
   	          *text1      = "are/is coloured with colour number ",
   	          *itemstring = "ABC"; 
      
      
      static   short  help; /* saves the value of norc for sizecomputation  */
      register short  i, j; /* loop-indices 				    */ 
      
      register char   itemcount = -1; /* counts the items of a printed line */
   	   
   	   
      
      
      nos = *pt_data[9];
      
      if( tabkind == TTAB )
                not = *pt_data[0];
      else
      		non = *pt_data[3];
      
      
      if( rowcolkind == ROW ) {
      		print_opthead( fp_opt, GCS_OPT, tabkind );
 		if( sortinfo )
      		   fprintf(fp_opt, "sort-heuristic for graph-colouring !\n\n");
      		else
      		   fprintf(fp_opt, "no heuristic for graph-colouring !\n\n");
      }

      
      if( tabkind == TTAB && rowcolkind == ROW )
      	    print_errmatoptres( 
      				 fp_opt,
      			 	 opt_data->ttabopt.GCS.sigrowptr,
      			 	 opt_data->ttabopt.GCS.sigcolptr,
      			 	 ( opt_data->ttabopt.GCS.sigmaxrowind + 1 ) *
      			 	 ((opt_data->ttabopt.GCS.sigmaxcolind + 8)>>3 ),
      			 	 nos,
      			 	 not
      		       	       );
      		       	          
		       	       
      fprintf(
               fp_opt,
               "\n\n(%c) %s\n    %s\n\n\n",
               itemstring[ tabkind + rowcolkind ],
               rctext[rowcolkind], nttext[tabkind + rowcolkind * 2] 
             );
             
      
            if( tabkind == TTAB )	       	       
      		if( rowcolkind == ROW )
	       	       
       			norc = opt_data->ttabopt.GCS.maxrowind + 1;
       		else
                	norc = opt_data->ttabopt.GCS.maxcolind + 1;
      else
       		if( rowcolkind == ROW )
	       	       
       			norc = opt_data->ntabopt.GCS.maxrowind + 1;
       		else
                	norc = opt_data->ntabopt.GCS.maxcolind + 1;
                
       
       fprintf(
                fp_opt, 
                "number of colours for %s-colouring: %-3d\n\n",
                rcword[rowcolkind],
                norc
              );
                
       for( i = 0; i < norc; i++ )  {
                
            fprintf(
                     fp_opt,
                     "%-3d %s(s) %s %-3d :\n",
                     colourmap[i] + 1,
                     rcword[rowcolkind],
                     text1,
                     i
                   );
                               
            fprintf(fp_opt, STARLINE );
                        
            itemcount = 0;
                        
            for( j = 0; j <= colourmap[i]; j++ ) {
                                
                      fprintf(
                               fp_opt, "%4d%c",
                               partition[i][j],
                               ( j == colourmap[i] ? '\n' : ',' ) 
                             );
                               
                      if( ++itemcount == ITEMSPERLINE )  {
                               fprintf(fp_opt, "\n" );
                               itemcount = 0;
                      }
                               
            }/* for j */
                               
            fprintf(fp_opt, MINLINE);
                        
       }/* for i */
       
       if( rowcolkind == COL )
         print_storesize(  
       			  fp_opt, 
       			  nos * ( tabkind == TTAB ? not : non ) * sizeof(short),
       			  norc * help * sizeof( short)
       		        );
       
       
       fprintf(fp_opt, "\n\n");
       help = norc;
   
   }/* print_GCSoptres */
               
      		
      			  


void print_LESoptres(  fp_opt, tabkind, opt_data, pt_data, orderinfo )

     FILE          *fp_opt;    /* pointer to the file on which the      */
		               /* optimizationresults are printed       */
     char           tabkind;   /* =TTAB for T-table, = NTAB for N-table */
     opttype       *opt_data;  /* interface from optimization-module    */
                               /* to output-module                      */
     readtype       pt_data;   /* interface from input-module to        */
      			       /* optimization-module                   */
     char           orderinfo; /* = ROW, if rows are eliminated first,  */ 
     			       /* else = COL				*/

  /*  prints the optimization-results of optimization-method
   *  Line-Elimination-Scheme on file fp_opt points to.
   *
   ***/
   
   { short   nos,    /* number of states				  */
             nont,   /* number of terminals or number of nonterminals     */
            *rowval, /* row i is eliminated with rowval[i] 		  */
            *decrow, /* decrow[i] is the scannumber, on which row[i]      */
                     /* was eliminated					  */
            *colval, /* column i is eliminated with colval[i]		  */
            *deccol, /* deccol[i] is the scannumber, on which  column[i]  */
                     /* was eliminated					  */
             elrows, /* number of eliminated rows			  */
             elcols, /* number of eliminated columns 			  */
             scanmax;/* highest number of scans				  */
             
      char  *text1 = ": eliminated at scan ",
            *text2 = ", value is";
             
      register short i,j; /* loopindices */
        
   
      nos    = *pt_data[9];
   
      if( tabkind == TTAB ) {
      
      		rowval   =  opt_data->ttabopt.LES.rowval;
      		decrow   =  opt_data->ttabopt.LES.decrow;
      		colval   =  opt_data->ttabopt.LES.colval;
      		deccol   =  opt_data->ttabopt.LES.deccol;
      		elrows   =  opt_data->ttabopt.LES.elrows;
     		elcols   =  opt_data->ttabopt.LES.elcols;
     		scanmax  =  opt_data->ttabopt.LES.scans;
     		nont     = *pt_data[0];
      }
      else  {
                rowval   =  opt_data->ntabopt.LES.rowval;
      		decrow   =  opt_data->ntabopt.LES.decrow;
      		colval   =  opt_data->ntabopt.LES.colval;
      		deccol   =  opt_data->ntabopt.LES.deccol;
      		elrows   =  opt_data->ntabopt.LES.elrows;
     		elcols   =  opt_data->ntabopt.LES.elcols;
     		scanmax  =  opt_data->ntabopt.LES.scans;
     		nont     = *pt_data[3];
      }
      
      
      print_opthead( fp_opt, LES_OPT, tabkind );
      
      if( tabkind == TTAB )
      	     print_errmatoptres( 
      				 fp_opt,
      			 	 opt_data->ttabopt.LES.sigrowptr,
      			 	 opt_data->ttabopt.LES.sigcolptr,
      			 	 ( opt_data->ttabopt.LES.sigmaxrowind + 1 ) *
      			 	 ((opt_data->ttabopt.LES.sigmaxcolind + 8)>>3 ),
      			 	 nos,
      			 	 nont
      		       	       );      
             
      fprintf(fp_opt, "\n\n\n" );
      fprintf(
               fp_opt, 
      	       "(%c) Results of the row-column \n",
      	       ( tabkind == TTAB ?  'B' : 'A' )
      	     );
      fprintf(fp_opt, "    elimination of the %s: \n\n", ntword[tabkind] );
      
      fprintf(
               fp_opt, 
               "%ss are tried to eliminate first at begin !\n\n",
               rcword[orderinfo]
             );
                  
      fprintf(fp_opt, "%-3d rows eliminated:\n", elrows);
      fprintf(fp_opt, STARLINE );
                  
      for( i = 0; i < nos; i++ )
                  
                if( decrow[i] != scanmax ) { 
                        
                      fprintf(
                               fp_opt, 
                               "row %3d %s %3d%s %s\n",
                               i,
                               text1,
                               decrow[i],
                               text2, 
                               conv_tabval( rowval[i] )
                             );
                                      
                      fprintf(fp_opt, MINLINE );
                }
                        
      fprintf(fp_opt, "\n\n\n");
      fprintf(fp_opt, "%-3d columns eliminated:\n", elcols);
      fprintf(fp_opt, STARLINE );
                  
      for( j = 0; j < nont; j++ )
                  
                if( deccol[j] != scanmax ) { 
                        
                        fprintf(
                                 fp_opt,
                                 "column %3d %s %3d%s %s\n",
                                 j,
                                 text1,
                                 deccol[j],
                                 text2, 
                                 conv_tabval( colval[j] )
                               );
                                      
                        fprintf(fp_opt, MINLINE );
                }
                  
       fprintf(fp_opt, "\n\n\n");
       
       print_storesize(
            		fp_opt,  
            	        nos * nont *  sizeof( short ),
                        (nos-elrows) * (nont-elcols) * sizeof( short )
                      );
                        
   }/* print_LESoptres */







void print_RDSoptres( fp_opt, tabkind, opt_data, pt_data )

     FILE          *fp_opt;    /* pointer to the file on which the      */
		               /* optimizationresults are printed       */
     char           tabkind;   /* =TTAB for T-table, = NTAB for N-table */
     opttype       *opt_data;  /* interface from optimization-module    */
                               /* to output-module                      */
     readtype       pt_data;   /* interface from input-module to        */
      			       /* optimization-module                   */

  /*  prints the optimization-results of optimization-method
   *  Row-Displacement-Scheme on file fp_opt points to.
   *
   ***/
   
   {  int   *rowptr;
      short  nos;
             
      register short i;
      
      
      
      nos    = *pt_data[9];
      rowptr = ( ( tabkind == TTAB ) ?   opt_data->ttabopt.RDS.rowptr 
      				     :   opt_data->ntabopt.RDS.rowptr );

      print_opthead( fp_opt, RDS_OPT, tabkind );
      
      if( tabkind == TTAB )
            print_errmatoptres( 
      				 fp_opt,
      			 	 opt_data->ttabopt.RDS.sigrowptr,
      			 	 opt_data->ttabopt.RDS.sigcolptr,
      			 	 ( opt_data->ttabopt.RDS.sigmaxrowind + 1 ) *
      			 	 ((unsigned short)(opt_data->ttabopt.RDS.sigmaxcolind + 8)>>3 ),
      			 	 nos,
      			        *pt_data[0]
      		       	       );
      
      fprintf(
               fp_opt, 
               "(%c) Results of the Row-Displacement-Scheme :\n\n",
               ( (tabkind == TTAB) ? 'B' : 'A' )
             );
             
      for( i = 0; i < nos; i++ )
      	      fprintf(fp_opt, "row %-3d fits at position %-3d\n", i, rowptr[i]);
      
      print_storesize(
                       fp_opt, 
                       nos* *pt_data[(tabkind == TTAB) ? 0 : 3] * sizeof(short),
                        ( tabkind == TTAB ? 
                            opt_data->ttabopt.RDS.size 
                          : opt_data->ntabopt.RDS.size
                        ) * sizeof(short)
                     );
                  
   }/* print_RDSoptres */
      
      
      


void print_SDSoptres( fp_opt, tabkind, opt_data, pt_data )

     FILE          *fp_opt;    /* pointer to the file on which the      */
		               /* optimizationresults are printed       */
     char           tabkind;   /* =TTAB for T-table, = NTAB for N-table */
     opttype       *opt_data;  /* interface from optimization-module    */
                               /* to output-module                      */
     readtype       pt_data;   /* interface from input-module to        */
      			       /* optimization-module                   */
      			       
      			       
  /*  prints the optimization-results of optimization-method
   *  Significant-Distance-Scheme on file fp_opt points to.
   *
   ***/

   {   short *first,
             *last,
              nos,
              len;
              
       register int   size = 0;
       register short i;
       
       
       
       nos = *pt_data[9];
       len = *pt_data[(tabkind == TTAB) ? 0 : 3 ];
       
       if( tabkind == TTAB ) {
       		first = opt_data->ttabopt.SDS.firstptr;
       		last  = opt_data->ttabopt.SDS.lastptr;
       }
       else  {
                first = opt_data->ntabopt.SDS.firstptr;
       		last  = opt_data->ntabopt.SDS.lastptr;
       }
   
   
       print_opthead( fp_opt, SDS_OPT, tabkind );
       
       
       for( i = 0; i < nos; i++ )  {
       
       	    fprintf(fp_opt, "row %-3d:\n", i );
       	    
       	    if( last[i] == NIL || first[i] == len )
       	    
       	    	fprintf( fp_opt, "   empty row !\n");
       	    	
       	    else  {
       	    
       	        fprintf(
       	                 fp_opt,
       	                 "   position of the first significant entry: %-3d\n",
       	                 first[i]
       	               );
       	            
       	        fprintf(
       	                 fp_opt,
       	                 "   position of the last  significant entry: %-3d\n",
       	                 last[i]
       	               );
       	               
       	        size += last[i] - first[i] + 1;
       	        
       	    }
       	        
       	}/* for i */
       	
       	print_storesize(
       			 fp_opt,
       			 nos * len * sizeof(short),
       			 size * sizeof(short)
       		       );
       
   }/* print_SDSoptres */
       			  


void print_RCSoptres( fp_opt, tabkind, opt_data, pt_data, mrginfo )

     FILE          *fp_opt;    /* pointer to the file on which the      */
		               /* optimizationresults are printed       */
     char           tabkind;   /* =TTAB for T-table, =NTAB for N-table  */
     opttype       *opt_data;  /* interface from optimization-module    */
                               /* to output-module                      */
     readtype       pt_data;   /* interface from input-module to        */
      			       /* optimization-module                   */
     char           mrginfo;   /* if =1, equal rows are eliminated      */

  /*  prints the optimization-results of optimization-method
   *  Row-Column-Scheme on file fp_opt points to.
   *
   ***/
   
   {   short  *ptab,
      	      *rowptr,
      	       nos,
      	       noc,
      	       noofsigents;
      	       
       char *text1 = " is equal to row ";
       
       register short i; 
       register int   storecount = 0;
       
       
       
       
       nos  = *pt_data[9];
       
       if( tabkind == TTAB ) {
       
       		noc  = *pt_data[0];
       		ptab =  pt_data[1];
                if( mrginfo )
                	rowptr = opt_data->ttabopt.RCS.rowptr;
       }
       else  {
       		noc  = *pt_data[3];
       		ptab =  pt_data[4];
                if( mrginfo )
                	rowptr = opt_data->ntabopt.RCS.rowptr;
       }
      
       print_opthead( fp_opt, RCS_OPT, tabkind );
       
       if( mrginfo ) {
        
           fprintf(
       	            fp_opt,
       	            "The follwing rows of the %s are equal:\n\n",
       	            ntword[tabkind]
       	          );
       	      
           fprintf(
                    fp_opt,
                    "( the second rowindex is the smallest rowindex     )\n"
                  );
           fprintf(
                    fp_opt,
                    "( for which the first and the second row are equal )\n"
                  );
           fprintf(fp_opt, "\n");
       
           for( i = 0; i < nos; i++ )
               if(  rowptr[i] == i )  {
                        noofsigents = no_of_sigents(ptab + i * noc, noc );
                        storecount += noofsigents;
                        fprintf(
                                fp_opt, 
                                "row %-3d%s%-3d    [ %s%-3d ]\n",
                                i,
                                text1,
                                rowptr[i],
                                "number of significant entries: ",
                                noofsigents
                               );                      
               }
               else
                        fprintf(
                                fp_opt, 
                                "row %-3d%s%-3d\n",
                                i,
                                text1,
                                rowptr[i]
                               );
       }/* if( mrginfo ) */
       else  {
       
           for( i = 0; i < nos; i++ ) {
                    noofsigents = no_of_sigents(ptab + i * noc, noc );
                    storecount += noofsigents;
                    fprintf(
                             fp_opt, 
                             "row %-3d has %-3d significant entries\n",
                             i,
                             noofsigents
                            );                      
           }
           
       }
        
       print_storesize( 
        		 fp_opt,
        		 nos * noc * sizeof(short),
        		 storecount * sizeof(short)
        	      );
        	       
    }/* print_RCSoptres */

/*
** $Id: optfunc.c,v 1.5 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: optfunc.c,v 1.5 1997/08/29 08:38:08 mjung Exp $";

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
/* filename: optfunc.c                        first edit   : 29 .  8 . 89     */
/* author  : Christian Zeitel                 last  change : 10 .  7 . 90     */
/******************************************************************************/

/******************************* CONTENTS **************************************
 *									       *
 *  This is the implementation of module optfunc. It contains the functions    *
 *  which perform the possible optimization-methods on the terminal- and non-  *
 *  terminalparser-table. 						       *
 *									       *
 ****************************** INCLUDE-FILES *********************************/

#include <stdio.h>

#include "tabsopttype.h"

#include "opthelptype.h"

#include "opthelpfunc.h"

#include "optresfunc.h"

/***************************** CONSTANT-MACROS ********************************/

#define  GCS_OPT   0

#define  LES_OPT   1

#define  RDS_OPT   2

#define  NTAB      0

#define  TTAB      1

#define  ROW       0

#define  COL       1

/******************************************************************************/

/*============================================================================*/
/*==================                          		======================*/
/*==================        FUNCTIONS FOR		======================*/
/*==================     OPTIMIZATION-METHOD            ======================*/
/*==================    GRAPH COLOURING SCHEME		======================*/
/*==================					======================*/
/*============================================================================*/


void Tmk_GCSopt( pt_data, opt_data, optinfo, fp_opt, addinfo, sortinfo )

     readtype  pt_data;  /*interface from input-module to optimization-module */
     opttype  *opt_data; /*interface from optimization-module to output-module*/
     char      optinfo;  /* =1,if an analysis of the optimization is printed  */
     		         /* on file "opt.out", = 0 else 		      */
     FILE      *fp_opt;  /* filepointer for controlloutput of                 */
      		         /* optimization is only used if optinfo = 1          */
     char      addinfo,  /* =1,if additional messages are printed to stan-    */
                         /* dardinput during the generation-process, = 0 else */
               sortinfo; /* =1, if nodes in the collisiongraph are  sorted by */
               		 /* decreasing degree, else = 0.		      */

      /*  Tmk_GCSopt performs the optimization-method Graph-Colouring-Scheme
       *  on the terminaltable .
       *
       ***/

       { graphtype  *graph;    /*graph for colouring rows or columns          */
         partitiontype
         	    *partition;/* the nodepartition of graph induced by the   */
         		       /* colouring				      */
          short     *ttab,     /* the terminaltable			      */
         	    *ropt_ttab,/* the rowoptimized terminal-table	      */
         	    *termlist, /* maps the scannerdefined sxcodes to the par- */
         	    	       /* defined sxcodes			      */
         	    *colourmap,/* colourmap[i] is the number of nodes in graph*/
         	    	       /* coloured with colour number i		      */
         	     nos,      /* number of states 			      */
         	     not;      /* number of terminals			      */



         if( addinfo )
         	 printf("    C**function Tmk_GCSopt:started !\n");

         ttab     =  pt_data[1];
         not      = *pt_data[0];
         nos      = *pt_data[9];
         termlist =  pt_data[2];

         /********************************************************************/
         /*** generation of the mapping from external to internal sxcode  ****/
         /********************************************************************/

         opt_data->ttabopt.GCS.convtermlist = conv_termlist( termlist, not );

         /********************************************************************/
         /*************  generation of the negated error-matrix  *************/
         /********************************************************************/

         gen_errormatrix( ttab, nos, not, opt_data, GCS_OPT );

      	 graph =

         alloc_graph( ( (nos > not) ? nos : not ), NULL );

         init_graph( nos , *graph );

         colourmap =

         alloc_colourmap( ( (nos > not) ? nos : not ), NULL );

         /*******************************************************************/
         /**************** row-colouring of the terminaltable ***************/
         /*******************************************************************/

         build_collisiongraph( ttab, nos, not, *graph, 1 );

         if( sortinfo )
         	qsort_nodes( *graph, 0, nos - 1 );

         opt_data->ttabopt.GCS.rowind =

         colour_graph(
         	        *graph,
            		 nos,
         	        &(opt_data->ttabopt.GCS.maxrowind),
         	         colourmap
         	     );

         partition =

         alloc_partition( NULL,colourmap,opt_data->ttabopt.GCS.maxrowind );

         gen_partition( *graph, *partition, colourmap, nos );

         if( optinfo )
         	print_GCSoptres( fp_opt,
         			 TTAB,
         			 opt_data,
         			 pt_data,
         			 colourmap,
         			*partition,
         			 sortinfo,
         			 ROW
         		       );

         ropt_ttab =

         merge_rows( NULL,
        	     ttab,
        	    *partition,
        	     colourmap,
         	     opt_data->ttabopt.GCS.maxrowind,
         	     not
         	   );

         init_graph( not , *graph );

         reset_colourmap( not, colourmap );

         /***************************************************************/
         /****  column-colouring of the rowoptimized terminal-table  ****/
         /***************************************************************/

         build_collisiongraph( ropt_ttab,
                               opt_data->ttabopt.GCS.maxrowind + 1,
         	               not,
         	              *graph,
         	               not
         	             );

         if( sortinfo )
         	qsort_nodes( *graph, 0, not - 1 );

         opt_data->ttabopt.GCS.colind =

         colour_graph(
         	       *graph, not,
         	       &(opt_data->ttabopt.GCS.maxcolind),
         	         colourmap
         	     );

         partition =

         alloc_partition(partition,colourmap,opt_data->ttabopt.GCS.maxcolind);

         gen_partition( *graph, *partition, colourmap, not );

         if( optinfo )
         	print_GCSoptres( fp_opt,
         	 		  TTAB,
         			  opt_data,
         			  pt_data,
         			  colourmap,
         			 *partition,
         			  sortinfo,
         			  COL
         			 );

         opt_data->ttabopt.GCS.ttab =

         merge_cols( opt_data->ttabopt.GCS.ttab,
         	     ropt_ttab,
         	     partition,
         	     colourmap,
         	     opt_data->ttabopt.GCS.maxcolind,
         	     opt_data->ttabopt.GCS.maxrowind + 1,
         	     not
         	   );


    }/* Tmk_GCSopt */






void Nmk_GCSopt( pt_data, opt_data, optinfo, fp_opt, addinfo, sortinfo )

     readtype  pt_data;  /*interface from input-module to optimization-module */
     opttype  *opt_data; /*interface from optimization-module to output-module*/
     char      optinfo;  /* =1,if an analysis of the optimization is printed  */
     		         /* on file "opt.out", = 0 else 		      */
     FILE      *fp_opt;  /* filepointer for controlloutput of                 */
      		         /* optimization is only used if optinfo = 1          */
     char      addinfo,  /* =1,if additional messages are printed to stan-    */
                         /* dardinput during the generation-process, = 0 else */
               sortinfo; /* =1, if nodes in the collisiongraph are  sorted by */
               		 /* decreasing degree, else = 0.		      */

      /*  Nmk_GCSopt performs the optimization-method Graph-Colouring-Scheme
       *  on the nonterminaltable .
       *
       ***/

       { graphtype  *graph;    /*graph for colouring rows or columns          */
         partitiontype
         	    *partition;/* the nodepartition of graph induced by the   */
         		       /* colouring				      */
          short     *ntab,     /* the nonterminaltable			      */
         	    *ropt_ntab,/* the rowoptimized nonterminal-table	      */
         	    *colourmap,/* colourmap[i] is the number of nodes in graph*/
         	    	       /* coloured with colour number i		      */
         	     nos,      /* number of states 			      */
         	     non;      /* number of nonterminals		      */



         if( addinfo )
         	 printf("    C**function Nmk_GCSopt:started !\n");

         ntab     =  pt_data[4];
         non      = *pt_data[3];
         nos      = *pt_data[9];

         graph =

         alloc_graph( ( (nos > non) ? nos : non ), NULL );

         init_graph( nos , *graph );

         colourmap =

         alloc_colourmap( ( (nos > non) ? nos : non ), NULL );

         /****************************************************************/
         /************* row-colouring of the nonterminaltable ************/
         /****************************************************************/

         build_collisiongraph( ntab, nos, non, *graph, 1 );

         if( sortinfo )
         	qsort_nodes( *graph, 0, nos - 1 );

         opt_data->ntabopt.GCS.rowind =

         colour_graph(
                       *graph,
         	        nos,
         	       &(opt_data->ntabopt.GCS.maxrowind),
         	        colourmap
         	     );

         partition =

         alloc_partition(NULL, colourmap, opt_data->ntabopt.GCS.maxrowind);

         gen_partition( *graph, *partition, colourmap, nos );

         if( optinfo )
         	print_GCSoptres(
         	                 fp_opt,
         			 NTAB,
         			 opt_data,
         			 pt_data,
         			 colourmap,
         		        *partition,
         			 sortinfo,
         			 ROW
         		       );

         ropt_ntab =

         merge_rows(
         	     NULL,
         	     ntab,
       		    *partition,
       		     colourmap,
         	     opt_data->ntabopt.GCS.maxrowind,
         	     non
         	   );

         init_graph( non , *graph );

         reset_colourmap( non, colourmap );

         /****************************************************************/
         /*** column-colouring of the rowoptimized nonterminal-table   ***/
         /****************************************************************/

         build_collisiongraph(
         		       ropt_ntab,
                               opt_data->ntabopt.GCS.maxrowind + 1,
         		       non,
         	              *graph,
         	               non
         	             );

         if( sortinfo )
         	qsort_nodes( *graph, 0, non - 1 );

         opt_data->ntabopt.GCS.colind =

         colour_graph(
         		*graph,
         		 non,
         	        &(opt_data->ntabopt.GCS.maxcolind),
         	         colourmap
         	     );

         partition =

         alloc_partition(partition, colourmap, opt_data->ntabopt.GCS.maxcolind);

         gen_partition( *graph, *partition, colourmap, non );

         if( optinfo )
         	print_GCSoptres(
         	                 fp_opt,
         			 NTAB,
         			 opt_data,
         			 pt_data,
         			 colourmap,
         			*partition,
         			 sortinfo,
         			 COL
         		       );

         opt_data->ntabopt.GCS.ntab =

         merge_cols( opt_data->ntabopt.GCS.ntab,
         	     ropt_ntab, partition,
         	     colourmap,
         	     opt_data->ntabopt.GCS.maxcolind,
         	     opt_data->ntabopt.GCS.maxrowind + 1,
         	     non
         	   );


    }/* Nmk_GCSopt */





/*============================================================================*/
/*==================                          		======================*/
/*==================        FUNCTIONS FOR		======================*/
/*==================     OPTIMIZATION-METHOD            ======================*/
/*==================   LINE ELIMINATION SCHEME		======================*/
/*==================					======================*/
/*============================================================================*/
void Tmk_LESopt( pt_data, opt_data, optinfo, fp_opt, addinfo, orderinfo )

     readtype  pt_data;  /*interface from input-module to optimization-module */
     opttype  *opt_data; /*interface from optimization-module to output-module*/
     char      optinfo;  /* =1,if an analysis of the optimization is printed  */
     		         /* on file "opt.out", = 0 else 		      */
     FILE      *fp_opt;  /* filepointer for controlloutput of                 */
      		         /* optimization is only used if optinfo = 1          */
     char      addinfo,  /* =1,if additional messages are printed to stan-    */
                         /* dardinput during the generation-process, = 0 else */
               orderinfo;/* =1, if the algorithm tries to eliminate columns   */
                         /* at the beginning				      */

      /*  Tmk_LESopt performs the optimization-method Line-Elimination-Scheme
       *  on the terminaltable .
       *
       ***/

      {  lestype   lesval;   /* contains all important results about the    */
      			     /* row-column-scheme			    */
         short     nos,      /* number of states			    */
         	   not,      /* number of terminals			    */
         	  *termlist, /* list to convert external to internal sxcode */
         	  *ttab;     /* terminaltable				    */



          if( addinfo )
      	  	  printf("    C**function Tmk_LESopt:started !\n");


      	  ttab     =   pt_data[1];
      	  not      =  *pt_data[0];
      	  nos      =  *pt_data[9];
      	  termlist =   pt_data[2];

         /*******************************************************************/
         /*** generation of the mapping from external to internal sxcode  ***/
         /*******************************************************************/

         opt_data->ttabopt.LES.convtermlist = conv_termlist( termlist, not );

         /*******************************************************************/
         /*************  generation of the negated error-matrix  ************/
         /*******************************************************************/

         gen_errormatrix( ttab, nos, not, opt_data, LES_OPT );

      	 /*******************************************************************/
      	 /****** perform Line-Elimination-Scheme on the terminal-table  *****/
      	 /*******************************************************************/

      	 elim_rowcol( &lesval, ttab, nos, not, orderinfo );

         opt_data->ttabopt.LES.decrow  =  lesval.decrow;
         opt_data->ttabopt.LES.deccol  =  lesval.deccol;
         opt_data->ttabopt.LES.rowval  =  lesval.rowval;
         opt_data->ttabopt.LES.colval  =  lesval.colval;
         opt_data->ttabopt.LES.scans   =  lesval.scans;
         opt_data->ttabopt.LES.elrows  =  lesval.elrows;
         opt_data->ttabopt.LES.elcols  =  lesval.elcols;

         if( optinfo )
         	print_LESoptres( fp_opt, TTAB, opt_data, pt_data, orderinfo );


      }/* Tmk_LESopt */





void Nmk_LESopt( pt_data, opt_data, optinfo, fp_opt, addinfo, orderinfo )

     readtype  pt_data;  /*interface from input-module to optimization-module */
     opttype  *opt_data; /*interface from optimization-module to output-module*/
     char      optinfo;  /* =1,if an analysis of the optimization is printed  */
     		         /* on file "opt.out", = 0 else 		      */
     FILE      *fp_opt;  /* filepointer for controlloutput of                 */
      		         /* optimization is only used if optinfo = 1          */
     char      addinfo,  /* =1,if additional messages are printed to stan-    */
                         /* dardinput during the generation-process, = 0 else */
               orderinfo;/* =1, if the algorithm tries to eliminate columns   */
                         /* at the beginning				      */

      /*  Nmk_LESopt performs the optimization-method Line-Elimination-Scheme
       *  on the nonterminaltable .
       *
       ***/

      {  lestype  lesval;    /* contains all important results about the    */
      			     /* row-column-scheme			    */
         short     nos,      /* number of states			    */
         	   non,      /* number of nonterminals			    */
         	  *ntab;     /* nonterminaltable			    */



          if( addinfo )
      	  	  printf("    C**function Nmk_LESopt:started !\n");


      	  ntab     =   pt_data[4];
      	  non      =  *pt_data[3];
      	  nos      =  *pt_data[9];

      	 /*******************************************************************/
      	 /**** perform Line-Elimination-Scheme on the nonterminal-table  ****/
      	 /*******************************************************************/

      	 elim_rowcol( &lesval, ntab, nos, non, orderinfo );

         opt_data->ntabopt.LES.decrow  =  lesval.decrow;
         opt_data->ntabopt.LES.deccol  =  lesval.deccol;
         opt_data->ntabopt.LES.rowval  =  lesval.rowval;
         opt_data->ntabopt.LES.colval  =  lesval.colval;
         opt_data->ntabopt.LES.scans   =  lesval.scans;
         opt_data->ntabopt.LES.elrows  =  lesval.elrows;
         opt_data->ntabopt.LES.elcols  =  lesval.elcols;

         if( optinfo )
         	print_LESoptres( fp_opt, NTAB, opt_data, pt_data, orderinfo );

      }/* Nmk_LESopt */




/*============================================================================*/
/*==================                          		======================*/
/*==================           FUNCTIONS FOR		======================*/
/*==================        OPTIMIZATION-METHOD         ======================*/
/*==================      ROW DISPLACEMENT SCHEME	======================*/
/*==================					======================*/
/*============================================================================*/

void Tmk_RDSopt( pt_data, opt_data, optinfo, fp_opt, addinfo )

     readtype  pt_data;  /*interface from input-module to optimization-module */
     opttype  *opt_data; /*interface from optimization-module to output-module*/
     char      optinfo;  /* =1,if an analysis of the optimization is printed  */
     		         /* on file "opt.out", = 0 else 		      */
     FILE      *fp_opt;  /* filepointer for controlloutput of                 */
      		         /* optimization is only used if optinfo = 1          */
     char      addinfo;  /* =1,if additional messages are printed to stan-    */
                         /* dardinput during the generation-process, = 0 else */


      /*  Tmk_RDSopt performs the optimization-method Row-Displacement-Scheme
       *  on the terminaltable .
       *
       ***/

      {  rdstype   rdsval;   /* contains all important results about the    */
      			     /* row-displacement-scheme			    */
         short     nos,      /* number of states			    */
         	   not,      /* number of terminals			    */
         	  *termlist, /* list to convert external to internal sxcode */
         	  *ttab;     /* terminaltable				    */



          if( addinfo )
      	  	  printf("    C**function Tmk_RDSopt:started !\n");


      	  ttab     =   pt_data[1];
      	  not      =  *pt_data[0];
      	  nos      =  *pt_data[9];
      	  termlist =   pt_data[2];

         /*******************************************************************/
         /*** generation of the mapping from external to internal sxcode  ***/
         /*******************************************************************/

         opt_data->ttabopt.RDS.convtermlist = conv_termlist( termlist, not );

         /*******************************************************************/
         /*************  generation of the negated error-matrix  ************/
         /*******************************************************************/

         gen_errormatrix( ttab, nos, not, opt_data, RDS_OPT );

      	 /*******************************************************************/
      	 /****** perform Row-Displacement-Scheme on the terminal-table  *****/
      	 /*******************************************************************/

      	 compress_ptab( &rdsval, ttab, nos, not );

         opt_data->ttabopt.RDS.rowptr  =  rdsval.rowptr;
         opt_data->ttabopt.RDS.ttab    =  rdsval.optab;
         opt_data->ttabopt.RDS.size    =  rdsval.size;

         if( optinfo )
         	print_RDSoptres( fp_opt, TTAB, opt_data, pt_data );

      }/* Tmk_RDSopt */




void Nmk_RDSopt( pt_data, opt_data, optinfo, fp_opt, addinfo )

     readtype  pt_data;  /*interface from input-module to optimization-module */
     opttype  *opt_data; /*interface from optimization-module to output-module*/
     char      optinfo;  /* =1,if an analysis of the optimization is printed  */
     		         /* on file "opt.out", = 0 else 		      */
     FILE      *fp_opt;  /* filepointer for controlloutput of                 */
      		         /* optimization is only used if optinfo = 1          */
     char      addinfo;  /* =1,if additional messages are printed to stan-    */
                         /* dardinput during the generation-process, = 0 else */


      /*  Nmk_RDSopt performs the optimization-method Row-Displacement-Scheme
       *  on the nonterminaltable .
       *
       ***/

      {  rdstype   rdsval;   /* contains all important results about the    */
      			     /* row-displacement-scheme			    */
         short     nos,      /* number of states			    */
         	   non,      /* number of nonterminals			    */
         	  *ntab;     /* nonterminaltable			    */



          if( addinfo )
      	  	  printf("    C**function Nmk_RDSopt:started !\n");


      	  ntab     =   pt_data[4];
      	  non      =  *pt_data[3];
      	  nos      =  *pt_data[9];

      	 /*******************************************************************/
      	 /**** perform Row-Displacement-Scheme on the nonterminal-table  ****/
      	 /*******************************************************************/

      	 compress_ptab( &rdsval, ntab, nos, non );

         opt_data->ntabopt.RDS.rowptr  =  rdsval.rowptr;
         opt_data->ntabopt.RDS.ntab    =  rdsval.optab;
         opt_data->ntabopt.RDS.size    =  rdsval.size;

         if( optinfo )
         	print_RDSoptres( fp_opt, NTAB, opt_data, pt_data );

      }/* Nmk_RDSopt */



/*============================================================================*/
/*==================                          		======================*/
/*==================        FUNCTIONS FOR		======================*/
/*==================      OPTIMIZATION-METHOD           ======================*/
/*==================  SIGNIFICANT-DISTANCE-SCHEME	======================*/
/*==================					======================*/
/*============================================================================*/

void Tmk_SDSopt( pt_data, opt_data, optinfo, fp_opt, addinfo )

     readtype  pt_data;  /*interface from input-module to optimization-module */
     opttype  *opt_data; /*interface from optimization-module to output-module*/
     char      optinfo;  /* =1,if an analysis of the optimization is printed  */
     		         /* on file "opt.out", = 0 else 		      */
     FILE      *fp_opt;  /* filepointer for controlloutput of                 */
      		         /* optimization is only used if optinfo = 1          */
     char      addinfo;  /* =1,if additional messages are printed to stan-    */
                         /* dardinput during the generation-process, = 0 else */


      /*  Tmk_SDSopt performs the optimization-method
       *  Significant-Distance-Scheme on the terminaltable .
       *
       ***/

      {  sdstype  sdsval;    /* contains all important results about the    */
      			     /* significant-distance-scheme		    */
         short     nos,      /* number of states			    */
         	   not,      /* number of terminals			    */
         	  *ttab,     /* terminaltable			 	    */
         	  *termlist; /* maps the external to internal sxcodes       */



          if( addinfo )
      	  	  printf("    C**function Tmk_SDSopt:started !\n");


      	  ttab     =   pt_data[1];
      	  not      =  *pt_data[0];
      	  nos      =  *pt_data[9];
          termlist =   pt_data[2];

         /*******************************************************************/
         /*** generation of the mapping from external to internal sxcode  ***/
         /*******************************************************************/

         opt_data->ttabopt.SDS.convtermlist = conv_termlist( termlist, not );

      	 /*******************************************************************/
      	 /**** perform Significant-Distance-Scheme on the terminal-table  ***/
      	 /*******************************************************************/

      	 clip_insigs( &sdsval, ttab, nos, not );

         opt_data->ttabopt.SDS.firstptr  =  sdsval.first;
         opt_data->ttabopt.SDS.lastptr   =  sdsval.last;
         opt_data->ttabopt.SDS.rowptr    =  sdsval.rowptr;

         if( optinfo )
         	print_SDSoptres( fp_opt, TTAB, opt_data, pt_data );

      }/* Tmk_SDSopt */




void Nmk_SDSopt( pt_data, opt_data, optinfo, fp_opt, addinfo )

     readtype  pt_data;  /*interface from input-module to optimization-module */
     opttype  *opt_data; /*interface from optimization-module to output-module*/
     char      optinfo;  /* =1,if an analysis of the optimization is printed  */
     		         /* on file "opt.out", = 0 else 		      */
     FILE      *fp_opt;  /* filepointer for controlloutput of                 */
      		         /* optimization is only used if optinfo = 1          */
     char      addinfo;  /* =1,if additional messages are printed to stan-    */
                         /* dardinput during the generation-process, = 0 else */


      /*  Nmk_SDSopt performs the optimization-method
       *  Significant-Distance-Scheme on the nonterminaltable .
       *
       ***/

      {  sdstype  sdsval;  /* contains all important results about the    */
      			     /* significant-distance-scheme		    */
         short     nos,      /* number of states			    */
         	   non,      /* number of nonterminals			    */
         	  *ntab;     /* nonterminaltable			    */



          if( addinfo )
      	  	  printf("    C**function Nmk_SDSopt:started !\n");


      	  ntab     =   pt_data[4];
      	  non      =  *pt_data[3];
      	  nos      =  *pt_data[9];

      	 /*******************************************************************/
      	 /*** perform Significant-Distance-Scheme on the nonterminal-table  */
      	 /*******************************************************************/

      	 clip_insigs( &sdsval, ntab, nos, non );

         opt_data->ntabopt.SDS.firstptr  =  sdsval.first;
         opt_data->ntabopt.SDS.lastptr   =  sdsval.last;
         opt_data->ntabopt.SDS.rowptr    =  sdsval.rowptr;

         if( optinfo )
         	print_SDSoptres( fp_opt, NTAB, opt_data, pt_data );

      }/* Nmk_SDSopt */


/*============================================================================*/
/*==================                          		======================*/
/*==================        FUNCTIONS FOR		======================*/
/*==================     OPTIMIZATION-METHOD            ======================*/
/*==================      ROW COLUMN SCHEME		======================*/
/*==================					======================*/
/*============================================================================*/


void Tmk_RCSopt( pt_data, opt_data, optinfo, fp_opt, addinfo, mrginfo )

     readtype  pt_data;  /*interface from input-module to optimization-module */
     opttype  *opt_data; /*interface from optimization-module to output-module*/
     char      optinfo;  /* =1,if an analysis of the optimization is printed  */
     		         /* on file "opt.out", = 0 else 		      */
     FILE      *fp_opt;  /* filepointer for controlloutput of                 */
      		         /* optimization is only used if optinfo = 1          */
     char      addinfo,  /* =1,if additional messages are printed to stan-    */
                         /* dardinput during the generation-process, = 0 else */
               mrginfo;  /* =1,if equal lines are merged, else =0             */


      /*  Tmk_RCSopt performs the optimization-method Row-Column-Scheme on
       *  the terminaltable .
       *
       ***/

      {	 short   nos,    /* number of states    			   */
      	         not,    /* number of terminals				   */
      	        *ttab;   /* the terminaltable  				   */
      	 rcstype rcsval; /* contains the results of the Row-Column-Scheme */


      	  if( addinfo )
      	  	  printf("    C**function Tmk_RCSopt:started !\n");

      	  if( mrginfo ) {

      	        nos  = *pt_data[9];
      	        not  = *pt_data[0];
      	        ttab =  pt_data[1];

      	        /*************************************************************/
                /** perform the Row Column-Scheme on the terminal-table   ****/
      	        /*************************************************************/

      	        search_eqrows( &rcsval, ttab, nos, not );

      	        opt_data->ttabopt.RCS.rowptr    = rcsval.rowptr;
      	        opt_data->ttabopt.RCS.rowind    = rcsval.rowind;
      	        opt_data->ttabopt.RCS.maxrowind = rcsval.maxrowind;

      	  }

      	  if( optinfo )
         	print_RCSoptres( fp_opt, TTAB, opt_data, pt_data, mrginfo );


      }/* Tmk_RCSopt */






void Nmk_RCSopt( pt_data, opt_data, optinfo, fp_opt, addinfo, mrginfo )

     readtype  pt_data;  /*interface from input-module to optimization-module */
     opttype  *opt_data; /*interface from optimization-module to output-module*/
     char      optinfo;  /* =1,if an analysis of the optimization is printed  */
     		         /* on file "opt.out", = 0 else 		      */
     FILE      *fp_opt;  /* filepointer for controlloutput of                 */
      		         /* optimization is only used if optinfo = 1          */
     char      addinfo,  /* =1,if additional messages are printed to stan-    */
                         /* dardinput during the generation-process, = 0 else */
               mrginfo;  /* if =1, equal rows are merged                      */


      /*  Nmk_RCSopt performs the optimization-method Row-Column-Scheme on
       *  the nonterminaltable .
       *
       ***/

      {	 short   nos,    /* number of states    			   */
      	         non,    /* number of nonterminals			   */
      	        *ntab;   /* the nonterminaltable  			   */
      	 rcstype rcsval; /* contains the results of the Row-Column-Scheme  */



      	  if( addinfo )
      	  	  printf( "    C**function Tmk_RCSopt:started !\n");

      	  if( mrginfo ) {

      	        nos  = *pt_data[9];
      	        non  = *pt_data[3];
      	        ntab =  pt_data[4];

      	        /*************************************************************/
                /** perform the Row Column-Scheme on the nonterminal-table   */
      	        /*************************************************************/

      	        search_eqrows( &rcsval, ntab, nos, non );

      	        opt_data->ntabopt.RCS.rowptr    = rcsval.rowptr;
      	        opt_data->ntabopt.RCS.rowind    = rcsval.rowind;
      	        opt_data->ntabopt.RCS.maxrowind = rcsval.maxrowind;

      	  }

      	  if( optinfo )
         	print_RCSoptres( fp_opt, NTAB, opt_data, pt_data, mrginfo );


       }/* Nmk_RCSopt */

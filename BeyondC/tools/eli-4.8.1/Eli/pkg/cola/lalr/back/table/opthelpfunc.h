/*
** $Id: opthelpfunc.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* filename: opthelpfunc.h                    first edit   :  3 .11 . 89      */
/* author  : Christian Zeitel                 last change  : 23 . 3 . 89      */
/******************************************************************************/

/******************************** CONTENTS *************************************
 *									       *
 *  This is the interface between the calling module optfunc and the answering *
 *  opthelpfunc.							       *
 *		functions:  17 |  variables: 0 | types: 0		       *
 *									       *
 ************************** FUNCTION DECLARATIONS *****************************/

/*============================================================================*/
/*============================================================================*/
/*======================				======================*/
/*======================        GENERAL FUNCTIONS       ======================*/
/*======================				======================*/
/*============================================================================*/
/*============================================================================*/

extern  short *conv_termlist(/* short *termlist, not; */);

  /*  conv_termlist returns a pointer to the list which maps the 
   *  scannerdefined sxcodes on the sxcodes used internally by module
   *  BUILDPRS.
   *
   ***/




extern  void  gen_errormatrix(/* short *ttab, nos, not;           */
			      /* opttype *opt_data; char optkind; */);
  
  /*  gen_errormatrix constructs the negated error-matrix and writes it
   *  to interface opt_data. optkind indicates, which optimization-method
   *  invoked gen_errormatrix.
   *
   ***/


/*============================================================================*/
/*============================================================================*/
/*======================				======================*/
/*======================   FUNCTIONS FOR GCS-METHOD     ======================*/
/*======================				======================*/
/*============================================================================*/
/*============================================================================*/



extern  graphtype *alloc_graph(/* short noofnodes; graphtype *graph; */);

  /*  alloc_graph allocates store for noofnodes nodes of the collisionsgraph
   *  graph. Returned is a pointer to the allocated graph.
   *
   ***/





extern  void init_graph(/* short noofnodes; graphtype graph; */);
  
  /*  init_graph initializes the nodes of the collisiongraph 
   *  allocated with alloc_graph.
   *
   ***/





extern  short *alloc_colourmap(/* short size, *colourmap; */);

  /*  alloc_colourmap allocates store for the colourmap, which assigns
   *  each colour the number of rows or columns coloured with this colour.
   *
   ***/





extern  void reset_colourmap(/* short size, *colourmap; */);

  /*  reset_colourmap sets all components of colourmap to zero.
   *
   ***/





extern  void  build_collisiongraph(/*  short *ptab, nor, noc;          */
				   /*  graphtype graph;  short offset; */);

  /*  build_collisiongraph constructs the collisiongraph for rows or columns
   *  of a parsetable.
   *
   ***/





extern  void qsort_nodes(/* graphtype graph; short l, r; */);

  /*  qsort_nodes sorts the nodelist of graph with nodedegree as key in
   *  decreasing order.
   *
   ***/




extern  short *colour_graph(/* graphtype graph; short noofnodes; */
                            /* short *maxcolour, *colourmap;     */);

  /*  colour_graph colours the nodes of the collisiongraph graph. Returned
   *  is a pointer to a list which maps the nodes on their colours.
   *
   ***/






extern  partitiontype *alloc_partition(/* partitiontype *partition;      */
				       /* short *colourmap, maxcolour;   */);

  /*  alloc_partition allocates store for the nodepartition partition which
   *  is induced by the nodecolouring. Returned is a pointer to the 
   *  notinitialized nodepartition.
   *
   ***/






extern  void gen_partition(/* graphtype graph; partitiontype partition; */
			   /* short *colourmap, noofnodes;		*/); 

  /*  gen_partition  generates the nodepartition induced by 
   *  the coloured graph and writes it to partition. 
   *
   ***/






extern  short *merge_rows(/* short *ropt_ptab, *ptab;            */
                          /* partitiontype partition;            */
                          /* short *colourmap, maxcolour, noc;   */);

  /*  merge_rows generates and returns the rowoptimized version of 
   *  parsertable  ptab after merging all rows with the same colour
   *  for each colour.
   *
   ***/




 
extern  short *merge_cols(/* short *copt_ptab, *ptab;                 */
                          /* partitiontype partition;                 */
                          /* short *colourmap, maxcolour, nor, noc;   */);
                           
  /*  merge_rows generates and returns the columnoptimized version of 
   *  parsertable  ptab after merging allrows with the same colour
   *  for each colour.
   *
   ***/





/*============================================================================*/
/*============================================================================*/
/*======================				======================*/
/*======================   FUNCTIONS FOR LES-METHOD     ======================*/
/*======================				======================*/
/*============================================================================*/
/*============================================================================*/

extern  void elim_rowcol(/* lestype *lesval; short *ptab, nor, noc; */
			 /* char orderinfo;			    */);

  /*  elim_rowcol eliminates alternating rows and columns of the 
   *  parsertable ptab. The results of the algorithm are returned in
   *  value *lesval.
   *
   ***/





/*============================================================================*/
/*============================================================================*/
/*======================				======================*/
/*======================   FUNCTIONS FOR RDS-METHOD     ======================*/
/*======================				======================*/
/*============================================================================*/
/*============================================================================*/

extern  void compress_ptab(/* rdstype *rdsval; short *ptab, nor, noc; */);

  /*  compress_ptab  tries to compress the parsertable ptab by using
   *  the Row-Displacement-Scheme. The results of the algorithm are
   *  returned in value *rdsval.
   *
   ***/






/*============================================================================*/
/*============================================================================*/
/*======================				======================*/
/*======================   FUNCTIONS FOR SDS-METHOD     ======================*/
/*======================				======================*/
/*============================================================================*/
/*============================================================================*/


extern  void clip_insigs(/* sdstype *sdsval; short *ptab, nor, noc; */);

  /*  clip_insigs tries to clip heading and trailing insignificant entries 
   *  in each row of the parsertable ptab. The results of the algorithm 
   *  are returned in value *sdsval.
   *
   ***/





/*============================================================================*/
/*============================================================================*/
/*======================				======================*/
/*======================   FUNCTIONS FOR RCS-METHOD     ======================*/
/*======================				======================*/
/*============================================================================*/
/*============================================================================*/ 
extern  void search_eqrows(/* rcstype *rcsval; short *ptab, nor, noc; */);

  /*  search_eqrows searches equal rows in the parsertable ptab. The results
   *  of the algorithm are returned in value *rcsval.
   *
   ***/

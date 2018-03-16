/*
** $Id: opthelpfunc.c,v 1.5 2007/02/23 10:57:27 peter Exp $
*/
static char rcs_id[]= "$Id: opthelpfunc.c,v 1.5 2007/02/23 10:57:27 peter Exp $";

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
/* filename: opthelpfunc.c                    first edit   :  13 .11 . 89     */
/* author  : Christian Zeitel                 last change  :   3 . 9 . 89     */
/******************************************************************************/

/******************************** CONTENTS *************************************
 *									       *
 *  This is the implementation of module opthelpfuncs. It contains all func-   *
 *  tions needed for optimize the T- or the N-table.   			       *
 *									       *
 ****************************** INCLUDE-FILES *********************************/

#include <stdlib.h>

#include "tabsopttype.h"

#include "opthelptype.h"

#include "error.h"

/***************************** CONSTANT-MACROS ********************************/

#define NIL    -1

#define YES 	1

#define NO 	0

#define ROW	0

#define COL 	1

#define GCS_OPT 0

#define LES_OPT 1

#define RDS_OPT 2

/************************** FUNCTION DECLARATIONS *****************************/


/*############################################################################*/
/*############################################################################*/
/*#########################			   ###########################*/
/*#########################   INTERNAL FUNCTIONS   ###########################*/
/*#########################			   ###########################*/
/*############################################################################*/
/*############################################################################*/


static char rows_eq( line1, line2, len )
  
        short *line1, /* line1 and line2 are rows in a terminal- or in a     */
              *line2, /* nonterminal-parsertable. len is the number of ter-  */
               len;   /* minals or the number of nonterminals                */        
 /*  rows_eq tests if the rows line1 and line2, both with length len are equal .
  *  The returned value is 0 if they are not equal and 1 if they are equal .
  *
  ***/
  
  {  register short i;
  
     for( i = 0; i < len; i++ )
     
        if( line1[i] != line2[i] )
                return( NO );
                
     return( YES );

  }/* rows_eq */




static  char  lines_comp1( line1, line2, len, offset )

        short  *line1, /* line1 and line2 are rows or columns in a terminal-  */
               *line2, /* or in a nonterminal-parse table. len is the legth of*/
                len,   /* a row or a column and offset is the length of a     */
                offset;/* row or 1.                                           */          
                  
 /*  lines_comp1 returns YES, if at every position of row or column line1 and
  *  row or column line2 are either two significant entries or two
  *  error-entries, else it returns NO.
  *
  ***/  
  
  {  register  short i;
     
     line1 -= offset;
     line2 -= offset;
  
     for( i = 0; i < len; i++ )  {
	
	line1 += offset;
	line2 += offset;
     
        if( ( *line1 && ! *line2  ) || ( ! *line1 && *line2 ) )
                return( NO );
		
     }/* for i */
                
     return( YES );
     
  }/* lines_comp1 */





static  char  lines_comp2( line1, line2, len, offset )

        short  *line1, /* line1 and line2 are rows or columns in a terminal-  */
               *line2, /* or in a nonterminal-parse table. len is the legth of*/
                len,   /* the row or the column and offset is the length of a */
                offset;/* row or one                                          */                  
 /*  lines_comp1 returns YES, iff at every position of row or column line1 and 
  *  row or column line2 are compatible entries, i.e. both entries have the 
  *  same value or one of both entries is an error-entry.
  *
  ***/  
  
  {  register  short i;
  
     line1 -= offset;
     line2 -= offset;

     for( i = 0; i < len; i++ )  {

	line1 += offset;
	line2 += offset;
     
        if( *line1 &&  *line2  && *line1 != *line2  ) 
                return( NO );

     }/* for i */
                
     return( YES );
     
  }/* lines_comp2 */







static char scan_line( line, len, offset, val, dv )
 
       short *line,  /* a column in the terminaltable                         */
              len,   /* length of line                                        */
              offset,/* =1, if a row is scanned, = number of columns of the   */
                     /* parse-table, if a column is scanned                   */
             *val,   /* if line contains only significant entries with the    */
                     /* same value, *val contains this value on               */
             *dv;    /* dv[i] =j, iff row/column i is eliminated on scan j of*/
                     /* rows/columns                                         */             
       
  /*  The result of scan_line is YES, if only significant entries with the same 
   *  value occur in line. In this case *val contains this value on exit.
   *  In each other case the result of scan_line is NO.
   *
   ***/
   
   {  register short i, j,   /* loopindices                                   */
                     value;  /* if only significant entries with the same     */
                             /* value occur in line, line contains this value */      
      
      for( i = 0; i < len; i++ )
        
                if( *(line  + i * offset)  && dv[i] == NIL ) {
                
                        /* a significant value was found  */
                        value = *(line + i * offset);
                        
                        /* test the rest of line */
                        for( j = i + 1; j < len; j++ )
                                if( *(line + j * offset) 
                                   && *(line + j * offset) != value
                                   && dv[j] == NIL )
                                        return( NO );
                       *val = value;
                        /* all significant entries in */
                        /* line have the same value   */
                        return( YES );
                        
                }/* for i */
                
                /* at this point all elements are marked or insignificant  */
                
               *val = 0;
        
                for( i = 0; i < len; i++ )
			if( dv[i] == NIL )
                                /* an insignificant entry was found */
                                return( YES );
                                
                /* all entries are marked */            
                return( NO );
                
   }/* scan_line */




static short get_firstsigpos( row, len )

       short *row, /* row in a parse-table */
       	      len; /* length of row        */
       	      
 /*  get_firstsigpos returns the position of the first significant entry
  *  counted from the lefthand side of row. If row contains only insignifi-
  *  cant entries, get_firstsigpos returns the length of row.
  *
  ***/
  
  {  register short i;
     
     
     for( i = 0; i < len; i++ )
     		if( row[i] )
     			return( i );
     			
     return( len );
   
  }/* get_firstsigpos */




 
static short get_lastsigpos( row, len )

       short *row, /* row in a parse-table */
       	      len; /* length of row        */
       	      
 /*  get_lastsigpos returns the position of the last significant entry
  *  counted from the righthand side of row. If row contains only insignifi-
  *  cant entries, get_firstsigpos returns NIL.
  *
  ***/
  
  {  register short i;
     
     
     for( i = len -1; i >= 0; i-- )
     		if( row[i] )
     			return( i );
     			
     return( NIL );
   
   }/* get_lastsigpos */





static void mix_rows( row1, row2, len )
       
       short *row1, /* row in a parse-table				 */
       	     *row2, /* row in a parse-table with the same length as row1 */
       	      len;  /* length of row1 and row2 				 */
       	      
 /*  mix_rows merges row2 with row1. row1 contains the result, row2 is not
  *  changed. At the end of procedure mix_rows row1[i] = row2[i] if row2[i] 
  *  is significant and row1[i] was insignificant at the beginning of mix_rows.
  *
  ***/
  
  {  register short i;
     
     
     for( i = 0; i < len; i++ )
     		if( row2[i] )
     			row1[i] = row2[i];
     			
  }/* mix_rows */




/*############################################################################*/
/*############################################################################*/
/*#########################			   ###########################*/
/*#########################  INTERFACE FUNCTIONS   ###########################*/
/*#########################       TO MODULE        ###########################*/
/*#########################        OPTFUNC         ###########################*/
/*#########################			   ###########################*/
/*############################################################################*/
/*############################################################################*/




/*============================================================================*/
/*============================================================================*/
/*======================				======================*/
/*======================        GENERAL FUNCTIONS       ======================*/
/*======================				======================*/
/*============================================================================*/
/*============================================================================*/

short *conv_termlist( termlist, not )

     short  *termlist,/* maps the scannerdefined sxcodes */
                      /* to the parserdefined sxcodes    */
             not;     /* number of terminals             */
                 
 /*  conv_termlist returns a vector mapping the external syntaxcodes used by
  *  the scanner to the internal syntaxcodes used by the parser.
  *
  ***/
  
  {  short   maxterm,  /* the biggest scannerdefined sxcode  */
            *convlist; /* the inversion of vector termlist   */
     
     register short i;
     
     
     maxterm  = termlist[0];
     
     /* search for the biggest and the smallest */
     /* scannerdefined syntaxcode               */
     
     for( i = 0; i < not; i++ )
            if( termlist[i] > maxterm )
                   maxterm = termlist[i];
     
     /* vector convlist is the inversion of vector termlist */
     
     if( (convlist = (short *)calloc(1,( maxterm + 1 ) * sizeof(short)))==NULL )
                errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "convlist" );
     
     for( i = 0; i < not; i++ )
            convlist[ termlist[i] ] = i;
            
     return( convlist );
     
  }/* conv_termlist */




void  gen_errormatrix( ttab, nos, not, opt_data, opt_kind )
                              
        short     *ttab,    /* terminaltable                      */
                   nos,     /* number of states                   */
                   not;     /* number of terminals                */
        opttype   *opt_data;/* interface from optimization-module */
                            /* to output-module                   */
        char       opt_kind;/* kind of optimization               */
              
 /*  gen_errormatrix compresses rows and columns of
  *  the negated errormatrix. An entry in the negated errormatrix is true,
  *  iff there is a significant entry at the same position in the termi-
  *  naltable.
  *
  ***/
  
  {  short  rowindcount  = 0, /* counts the rows of the      */
                              /* compressed error-matrix     */
            colindcount  = 0, /* counts the columns of       */
                              /* the compressed error-matrix */
           *rowind,    /* maps the rownumbers of ttab to the rownumbers    */
                       /* of the compressed error-matrix                   */
           *rowptr,    /* maps each rownumber of the error-matrix to the   */
                       /* the smallest rownumber for which the two rows    */
                       /* are equal                                        */
           *colind,    /* maps the columnnumbers of ttab to the column-    */
                       /* numbers of the compressed error-matrix           */
           *colptr;    /* maps each columnnumber of the error-matrix to    */
                       /* the smallest columnnumber for which the two      */
                       /* columns are equal                                */
     register short i, j; /* loop-indices */
     
     /* allocate store for row- and column-vectors */
     if( ( ( rowptr = (short *)malloc( nos * sizeof(short) ) ) == NULL )  ||
         ( ( rowind = (short *)malloc( nos * sizeof(short) ) ) == NULL )  ||
         ( ( colptr = (short *)malloc( not * sizeof(short) ) ) == NULL )  ||
         ( ( colind = (short *)malloc( not * sizeof(short) ) ) == NULL )     )
                  errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "opt_data" );
                  
     
     switch( opt_kind )  {
     
          case GCS_OPT :    opt_data->ttabopt.GCS.sigrowptr = rowptr;
                            opt_data->ttabopt.GCS.sigrowind = rowind;
                            opt_data->ttabopt.GCS.sigcolptr = colptr;
                            opt_data->ttabopt.GCS.sigcolind = colind;
                            break;
                        
           
          case LES_OPT :    opt_data->ttabopt.LES.sigrowptr = rowptr;
                            opt_data->ttabopt.LES.sigrowind = rowind;
                            opt_data->ttabopt.LES.sigcolptr = colptr;
                            opt_data->ttabopt.LES.sigcolind = colind;
                            break;
          
          case RDS_OPT :    opt_data->ttabopt.RDS.sigrowptr = rowptr;
                            opt_data->ttabopt.RDS.sigrowind = rowind;
                            opt_data->ttabopt.RDS.sigcolptr = colptr;
                            opt_data->ttabopt.RDS.sigcolind = colind;
                            break;
                        
          default      :    /* nix */;
                            break;
                        
     }/* switch */
     
     
     /* compress rows of the negated errormatrix */
     
     for( i = 0; i < nos; i++ )  {
     
            rowptr[i] = i;
            
            for( j = 0; j < i; j++ )
                   
                   if( lines_comp1( ttab + i * not, ttab + j * not, not, 1 ) ) {
                   
                           rowptr[i] = j;
                           break;
                           
                   }
                   
            if( rowptr[i] == i )
            
                  rowind[i] = rowindcount++;
            else
                  rowind[i] = rowind[rowptr[i]];
            
            
     }/* for i */
     
     
     /* compress columns of the negated errormatrix */
     
     for( i = 0; i < not; i++ )  {
     
            colptr[i] = i;
            
            for( j = 0; j < i; j++ )
                   
                   if( lines_comp1( ttab + i, ttab + j, nos, not ) )  {
                   
                           colptr[i] = j;
                           break;
                           
                   }
            
            if( colptr[i] == i )
                  colind[i] = colindcount++;
            else
                  colind[i] = colind[colptr[i]];
            
     }/* for i */
     
     switch( opt_kind )  {
     
        case  GCS_OPT :  opt_data->ttabopt.GCS.sigmaxrowind  = rowindcount - 1;
                         opt_data->ttabopt.GCS.sigmaxcolind  = colindcount - 1;
                         break;
                        
        case  LES_OPT :  opt_data->ttabopt.LES.sigmaxrowind  = rowindcount - 1;
                         opt_data->ttabopt.LES.sigmaxcolind  = colindcount - 1;
                         break;
                         
        case  RDS_OPT :  opt_data->ttabopt.RDS.sigmaxrowind  = rowindcount - 1;
                         opt_data->ttabopt.RDS.sigmaxcolind  = colindcount - 1;
                         break;
                        
        default       :  /* nix */;
                         break;
                        
     }/* switch */
     
     
  }/* gen_errormatrix */
  
  

/*============================================================================*/
/*============================================================================*/
/*======================				======================*/
/*======================   FUNCTIONS FOR GCS-METHOD     ======================*/
/*======================				======================*/
/*============================================================================*/
/*============================================================================*/



graphtype  *alloc_graph( noofnodes, graph )

        short        noofnodes; /* number of nodes in graph     */
        graphtype   *graph;     /* graph needed to colour rows  */
                                /* or columns of a parse table  */
        
 /*  graph is a vector of pointers to nodes. alloc_graph allocates store for 
  *  the pointervector and for the nodes. Returned is the start-address of 
  *  graph.
  *
  ***/
  
  {  register short i;
  
     if((graph = (graphtype *)malloc(noofnodes * sizeof(nodetype *)) ) == NULL )
              errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "graph" );
     
     for( i = 0; i < noofnodes; i++ )
     
     if( ( (*graph)[i] = (nodetype *)malloc( sizeof( nodetype ) ) ) == NULL )                 
              errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "graph" );
                 
     return( graph );
                 
  }/* alloc_graph */





void init_graph( noofnodes, graph )

        short        noofnodes; /* number of nodes of graph     */
        graphtype    graph;     /* graph needed to colour rows  */
                                /* or columns of a parse table  */
        
 /*  init_graph initializes the nodes of graph
  *
  ***/
  
  {  register short i;
  
     for( i = 0; i < noofnodes; i++ )  {
     
            graph[i]->degree      = 0;
            graph[i]->nodeindex   = i;
            graph[i]->colourindex = NIL;
            graph[i]->adjlist     = NULL;
            
     }/* for i */
     
  }/* init_graph */





short *alloc_colourmap( size, colourmap )

        short  size,      /* size of vector colourmap                   */
              *colourmap; /* colourmap[i] counts the number of rows or  */
                          /* columns which are coloured with colour     */
                          /* number i                                   */
      
 /*  alloc_colourmap allocates store for vector colourmap. Returned is the
  *  start-address of colourmap.
  *
  ***/
  
  {  
     if( ( colourmap = ( short *)calloc( 1, size * sizeof( short ) )) == NULL )              
              errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "colourmap" );
              
     return( colourmap );
              
  }/* alloc_colourmap */






void reset_colourmap( size, colourmap )

     short  size,      /* size of vector colourmap                   */
           *colourmap; /* colourmap[i] counts the number of rows or  */
                       /* columns which are coloured with colour     */
                       /* number i                                   */
              
 /*  reset_colourmap sets each entry in colourmap to zero.
  *
  ***/
  
  {  register short i;
  
     for( i = 0; i < size; i++ )
     
                colourmap[i] = 0;
                
  }/* reset_colourmap */
  
  
 
  


void build_collisiongraph( ptab, nor, noc, graph ,offset)
 
     short     *ptab,  /* parse table                             */
                nor,   /* number of rows in ptab                  */
                noc;   /* number of columns in ptab               */
     graphtype  graph; /* graph needed to colour columns of ptab  */
     short      offset;/* =1 if the collisiongraph for rows is    */
                       /* build, = noc, if the collisiongraph for */
                       /* columns is build                        */


 /*  build_colgraph constructs the collisiongraph for the rows or
  *  columns of ptab.
  *
  ***/
  
  {  adjlisttype  *adjlistelem,
                  *help;
                  
     register short i, j, 
                    bound,
                    length;
     
     bound   = ( offset == 1 ? nor : noc );
     
     length  = ( offset == 1 ? noc : nor );
     
     for( i = 0; i < bound; i++ )
     
          for( j = 0; j < i; j++ )
          
                    if( ! lines_comp2( ptab + i * ( offset == 1 ? noc : 1 ),
                                       ptab + j * ( offset == 1 ? noc : 1 ),
                                       length, 
                                       offset
                                     ) 
                      )
                    {
                    
                         /* add node with index j to adja-  */
                         /* cencelist of node with index i  */        
                         if( (adjlistelem = 
                             (adjlisttype *)malloc( sizeof( adjlisttype ) )  )  
                             					     == NULL )
                             errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "adjlist");
                                 
                         graph[i]->degree++;
                         adjlistelem->info = graph[j];
                         help              = graph[i]->adjlist;
                         graph[i]->adjlist = adjlistelem;
                         adjlistelem->next = help;
                         
                         /* add node with index i to adja-  */
                         /* cencelist of node with index j  */
                         if( (adjlistelem = 
                           (adjlisttype *)malloc( sizeof( adjlisttype ) )  )                                                                       == NULL ) 
                             errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "adjlist");
                             
                         graph[j]->degree++;
                         adjlistelem->info = graph[i];
                         help              = graph[j]->adjlist;
                         graph[j]->adjlist = adjlistelem;
                         adjlistelem->next = help;
                         
                    }/* if */
                    
  }/* build_collisiongraph */






void qsort_nodes( graph, l, r )

                graphtype  graph;
     register   short      l,r;
        
 /*  qsort_nodes sort the deegrees of graph in decreasing order with Quicksort.
  *
  ***/
  
  {  register   short  i,j,
                pivot;
     nodetype  *help;
     
     i     = l;
     j     = r;
     pivot = graph[(l+r)/2]->degree;
     
     do  {
     
        while( graph[i]->degree > pivot ) i++;
        while( graph[j]->degree < pivot ) j--;
        
        if( i <= j )  {
                help     = graph[i];
                graph[i] = graph[j];
                graph[j] = help;
                i++;
                j--;
        }/* if */
        
      }
      while( i <= j );
      
      if( l < j ) qsort_nodes( graph, l, j );
      if( i < r ) qsort_nodes( graph, i, r );
      
   }/* qsort_nodes */







short *colour_graph( graph, noofnodes, maxcolour, colourmap )
 
       graphtype   graph;      /* graph which is coloured       */
       short       noofnodes,  /* number of nodes of graph      */
                  *maxcolour,  /* the biggest colournumber      */
                               /* graph is coloured with        */
                  *colourmap;  /* colourmap[i] counts the nodes */
                               /* coloured with colour number i */

 /*  colour_graph colours the collision-graph graph. Returned is a pointer
  *  to vector nodecolptr.
  *
  *  on entry-
  *      graph[i]->colourindex = NIL for every i,
  *      noofnodes contains the number of nodes.
  *
  *  on exit-
  *      graph[i]->colourindex contains the colourindex 
  *      of node graph[i]->nodeindex,
  *      *maxcolour contains the highest colourindex,
  *      colourmap[i] is a list containing the nodes coloured with colour i,
  *      nodecolptr[i] = j, iff node i is coloured with colour j.
  *
  ***/
  
  {  adjlisttype  *adjlist;    /* adjacecelist of a node            */
     short         degree,     /* degree of a node                  */
                   colour = 0, /* the actual highest colour-index   */
                  *nodecolptr; /* maps the nodes to the colours     */
                               /* they are coloured with            */
     char          collision;  /* =YES,iff the actualnode cannot be */
                               /* coloured with the actual colour   */
     register short  i, j, k;  /* loop- indices                     */
     
     
     /* allocate store for vector nodecolptr */
     if( (nodecolptr = (short *)malloc( noofnodes * sizeof( short ) ) ) == NULL)                
                errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "nodecolptr" );
     
     for( i = 0; i < noofnodes; i++ )  {
     
                degree  = graph[i]->degree;
                
                for( j = 0; j <= colour; j++ ) {
                
                        collision = NO;
                        adjlist = graph[i]->adjlist;
                        
                        for( k = 0; k <  degree; k++ )
                        
                                if( adjlist->info->colourindex == j )  {
                                
                                          collision = YES;
                                          break;
                                }
                                else
                                          adjlist = adjlist->next;
                                         
                        if( ! collision )  {
                        
                                /* colour with colour number j */
                                nodecolptr[ graph[i]->nodeindex ] = j;
                                graph[i]->colourindex = j;
                                colourmap[j]++;
                                break;
                        }
                        
                }/* for j */
                
                if( collision )  {
                
                        /* colour with a new colour */
                        nodecolptr[ graph[i]->nodeindex ] = ++colour;
                        graph[i]->colourindex = colour;
                        colourmap[ colour ]++;
                }
                
     }/* for i */
     
    *maxcolour = colour;
    
     return( nodecolptr );
     
  }/* colour_graph */






partitiontype *alloc_partition( partition, colourmap, maxcolour )
 
       partitiontype *partition;/* the nodepartition induced by the colouring */
       short         *colourmap,/* maps the colours on lists of nodes which   */
                                /* having the same colour                     */
                      maxcolour;/* the biggest clolourindex graph is coloured */
                                /* with                                       */
                                                
 /*  alloc_partition allocates store for the nodepartition of the coloured 
  *  graph. Returned is a pointer to partition.
  *
  ***/
  
  {  register short i;
  
     
     if( ( partition = (partitiontype *)malloc((maxcolour +1)* sizeof(short *)))
     								 == NULL )                
              errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "partition" );
                
     for( i = 0; i <= maxcolour; i++ )  {
                if( ( (*partition)[i] = (short *)malloc( colourmap[i] * 
                                                     sizeof(short) ) ) == NULL )                          
                          errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "partition" );
                colourmap[i] = NIL;
     }/* for i */
     
     return( partition );
     
  }/* alloc_partition */






void gen_partition( graph, partition, colourmap, noofnodes )

     graphtype      graph;    /* the coloured graph                        */ 
     partitiontype  partition;/* the nodepartition induced by the colouring*/
     short         *colourmap,/* maps the colours on lists of nodes which  */
                              /* having the same colour                    */ 
                    noofnodes;/* number of nodes of graph                  */
                                        
 /*  gen_partition generates the nodepartition of the coloured graph.
  *  partition[i] is the vector containing all indizees of nodes coloured
  *  with colour number i.
  *
  ***/
  
  {  register short i;
  
     for( i = 0; i < noofnodes; i++ )
         partition[graph[i]->colourindex][++colourmap[graph[i]->colourindex]]                                            
         					       =  graph[i]->nodeindex;
           
  }/* gen_partition */






short *merge_rows( ropt_ptab, ptab, partition, colourmap, maxcolour, noc) 

        partitiontype  partition; /*the row-partition induced by the colouring*/        
        short    *ropt_ptab, /* the row-optimized parse table                 */                
       *ptab,                /* the input-parse-table                         */
                 *colourmap, /* like in alloc_partition                       */
                  maxcolour, /* like in alloc_partition                       */
                  noc;       /* number of columns of ptab                     */
                                    
 /*  merge_rows generates the row-optimized parse-table by merging all rows
  *  indexed by a single vector in partitionvector partition. row i in 
  *  vector ropt_ptab is obtained by merging all rows of ptab which stand
  *  in vector partition[i]. Returned is the start-address of the row-optimized  
  *  parse-table.
  *
  ***/
  
  {  register short i, j, k;
     
     /* allocate store for vector ropt_ptab */
     if( ( ropt_ptab = (short *)calloc(1, (maxcolour+1) * noc* sizeof(short) ) ) 
     								== NULL )                
     errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "ropt_ptab" );
     
     for( i = 0; i <= maxcolour; i++ )
     
                for( j = 0; j < noc; j++ )
                
                        for( k = 0; k <= colourmap[i]; k++ )
                                
                                if( ptab[ partition[i][k] * noc + j ] )  {
                                
                                       /* the first significant entry is taken*/
                                       ropt_ptab[ i * noc + j ] =
                                             ptab[ partition[i][k] * noc + j ];
                                       break;
                                }

      return( ropt_ptab );
      
  }/* merge_rows */






 
short *merge_cols( copt_ptab, ptab, partition, colourmap, maxcolour, nor, noc )

       partitiontype partition;/* the column-partition induced               */ 
                              /* by the colouring                            */ 
       short    *copt_ptab,/* the column-optimized parse table               */ 
                *ptab,     /* the input-parse table                          */ 
                *colourmap,/* like in alloc_partition                        */
                 maxcolour,/* like in alloc_partition                        */ 
                 nor,      /* number of rows in ptab                         */ 
                 noc;      /* number of columns in ptab                      */ 
                                  
 /*  merge_cols generates the column-optimized parse-table by merging all 
  *  columns indexed by a single vector in partitionvector partition. 
  *  column i in vector copt_ptab is obtained by merging all columns of
  *  ptab which stand in vector partition[i]. Returned is the start-address to
  *  the column-optimized parse-table.
  *
  ***/
  
  {  register short i, j, k;
     
     /* allocate store for vector copt_ptab */
     if( ( copt_ptab = (short *)calloc(1, (maxcolour+1) * nor* sizeof(short) ) )
     								       == NULL )
     		    errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "copt_ptab" );
     
     for( i = 0; i <= maxcolour; i++ )
     
                for( j = 0; j < nor; j++ )
                
                        for( k = 0; k <= colourmap[i]; k++ )
                                
                                if( ptab[ partition[i][k] + noc * j ] )  {
                                
                                       /* the first significant entry is taken*/
                                       copt_ptab[ i + ( maxcolour +1 ) * j ] =
                                             ptab[ partition[i][k] + noc * j ];
                                       break;
                                }

     return( copt_ptab );
     
  }/* merge_cols */





/*============================================================================*/
/*============================================================================*/
/*======================				======================*/
/*======================    FUNCTION FOR LES-METHOD     ======================*/
/*======================				======================*/
/*============================================================================*/
/*============================================================================*/


void  elim_rowcol( lesval, ptab, nor, noc, orderinfo )
        
      lestype *lesval;     /* contains all important informations    */
                           /* about the row- and column-elimination  */
      short    *ptab,      /* a parse-table                          */ 
                nor,       /* number of rows of ptab                 */
                noc;       /* number of columns of ptab              */
      char      orderinfo; /* =ROW, if it is tried to eliminate rows */
      			   /* at the beginning, =COL, if it is tried */
      			   /* to eliminate columns at the bebinning  */
                  
  /*  elim_rowcol tries to eliminate alternately rows and columns from
   *  ptab. The results are returned in value of type lestype.
   *
   ***/
   
   {  short   scancount = 0, /* counts the number of row- and column-scans   */
             *decrow,        /* if row i is eliminated, decrow[i] is the     */
                             /* scan-number on which it was eliminated       */
             *rowval,        /* vector storing the values of the eliminated  */
                             /* rows   					     */
             *deccol,        /* if column i is eliminated, deccol[i] is the  */
             		     /* scan-number on which it was eliminated       */
             *colval,        /* vector storing the values of the eliminated  */
             		     /* columns				             */
              value;         /* the value of an eliminated row or column     */
           
      register short  i, j,  /* loop-indices */
                      count;
                      
      register char   rowfound,/* =YES, iff a row for elimination is found    */
                      colfound;/* =YES, iff a column for elimination is found */
                      
                      
                      
      /* allocate store */               
      if( ( decrow = (short *)malloc( nor * sizeof(short) ) )  ==  NULL )
                errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "decrow" );
      
      if( ( deccol = (short *)malloc( noc * sizeof(short) ) )  ==  NULL )
                errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "deccol" );
      
      if( ( rowval = (short *)malloc( nor * sizeof(short) ) )  ==  NULL )
                errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "rowval" );
      
      if( ( colval = (short *)malloc( noc * sizeof(short) ) )  ==  NULL )
                errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "colval" ); 
      
      
      /* initialize vectors */
      for( i = 0; i < nor; i++ )
                decrow[i] = NIL;
                
      for( j = 0; j < noc; j++ )
                deccol[j] = NIL;
      
      
      /* eliminate rows and columns */
      do {
           rowfound = NO;
           colfound = NO;
           
           scancount++;
           
           if( scancount == 1 && orderinfo == COL )
           		goto colfirst;
           
           for( i = 0; i < nor; i++ )
           
                if( decrow[i] == NIL )
                     if((rowfound = scan_line(ptab + i*noc,noc,1,&value,deccol))){
                            decrow[i] =  scancount;
                            rowval[i] =  value;
                            break;
                     }
                     
           scancount++;
           
         colfirst: /* it is tried to eliminate columns first */
         
           for( j = 0; j < noc; j++ )
           
                if( deccol[j] == NIL )
                     if((colfound = scan_line(ptab + j,nor,noc,&value,decrow))){
                            deccol[j] =  scancount;
                            colval[j] =  value;
                            break;
                     }
         
      }
      while( rowfound || colfound );
         
      count = 0;
         
      for( i = 0; i < nor; i++ )
         
                if( decrow[i] == NIL )  {
                
                        rowval[i] = count++;
                        decrow[i] = scancount;
                }
                
      lesval->elrows  =  nor - count;
         
      count            = 0;
         
      for( j = 0; j < noc; j++ )
         
                if( deccol[j] == NIL )  {
                
                        colval[j] = count++;
                        deccol[j] = scancount;
                }
                
      lesval->elcols  =  noc - count;
      lesval->decrow  =  decrow;
      lesval->deccol  =  deccol;
      lesval->rowval  =  rowval;
      lesval->colval  =  colval;
      lesval->scans   =  scancount;
         
   }/* elim_rowcol */





/*============================================================================*/
/*============================================================================*/
/*======================				======================*/
/*======================   FUNCTIONS FOR RDS-METHOD     ======================*/
/*======================				======================*/
/*============================================================================*/
/*============================================================================*/

void compress_ptab( rdsval, ptab, nor, noc )

     rdstype *rdsval; /* contains the results of the RDS-Scheme */
     short   *ptab,   /* T-table or N-table                     */
              nor,    /* number of rows of ptab                 */
              noc;    /* number of columns of ptab              */


  /*  compress_ptab  tries to compress the parsertable ptab by using
   *  the Row-Displacement-Scheme. The results of the algorithm are
   *  returned in value *rdsval.
   *
   ***/
   
   {  int   *rowptr,  /* rowptr[i] is the startposition of row i in ptab    */
             minsect, /* minsect is the minimal section for which the       */
                      /* fittness of all rows is tested 		    */
             upper,   /* upper bound for testing a row                      */
             lower,   /* lower bound for testing a row			    */
             length;  /* length of the optimized parse-table		    */
            
       short *optab;  /* the optimized parse-table                          */
       
       char   ready;  /* =YES, iff the mainloop of the algorithm terminates */
       
       register short i; /* loopindex    */
       register int   j; /* loopindex    */
       
       
       
       
       /* allocate store */
       if((rowptr = rdsval->rowptr = (int *)malloc(nor * sizeof( int )))== NULL)
      		errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "rowptr" );
       if((optab=rdsval->optab= (short *)calloc(1,nor*noc*sizeof(short)))==NULL)
                errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "optab" );
       
       
       
       /* initialize tables */
       for( i = 1; i < nor; i++ )
       		rowptr[i] = NIL;
       		
       i = 0;
       
       while( ( length = get_lastsigpos( ptab+ i * noc, noc ) ) == NIL ) 
       		i++;/* skip empty rows */
       
       for( j = 0; j <= length; j++ )
       		optab[j] = *(ptab + i * noc + j);
       		/* the actual end of the merged parse-table optab is the */
       		/* the last significant entry of the first not-empty row */
       
       upper = minsect = length;
       lower = 0;
       
       rowptr[0] = 0;
       
       /* compress parse-table ptab */
       do  {
       	   
       	   for( i = 1; i < nor; i++ )
       	   
       	       if( rowptr[i] == NIL )
       	       
       	           /* find a fitting position for row i */
       	   	   for( j = lower; j <= upper; j++ )
       	   	   
       	   		if( lines_comp2(optab + j, ptab + i * noc, noc, 1) ) {
       	   		        /* row i fits */
       	   			rowptr[i] = j;
       	   			
       	   			if( ( length = get_lastsigpos(ptab+i*noc, noc) )
       	   						                == NIL )
       	   			        /* row i is empty */
       	   				break;
       	   			      
       	   			if( j + length > upper )
       	   				/* row i enhances the   */
       	   				/* upper bound of optab */
       	   				upper = j + length;
       	   			      
       	   			mix_rows( optab + j, ptab + i * noc, length +1);
       	   			
       	   		        break;
       	   				
       	   	        }/* if */
       	   
       	   ready = YES;
       	   
       	   /* test if there are rows which are not merged yet */
       	   for( i = 0; i < nor; i++ )
       	   
       	   	if( rowptr[i] == NIL )  { /* row i is not merged */
       	   		ready = NO;
       	   		if( upper == minsect )  {
       	   			minsect = upper + 1;
       	   			lower   = upper = minsect;
       	   		}
       	   		else  {
       	   		        lower   = minsect + 1;
       	   		        minsect = upper;
       	   		}
       	   		break;
       	   		
       	   	}/* if */
       	   
       }
       while( ! ready );
       
       rdsval->size = upper + 1;
       
   }/* compress_ptab */
       	   	
       	

/*============================================================================*/
/*============================================================================*/
/*======================				======================*/
/*======================   FUNCTIONS FOR SDS-METHOD     ======================*/
/*======================				======================*/
/*============================================================================*/
/*============================================================================*/


void clip_insigs( sdsval, ptab, nor, noc )

     sdstype *sdsval; /* contains the results of the SDS-Scheme */
     short   *ptab,   /* T-table or N-table                     */
              nor,    /* number of rows of ptab                 */
              noc;    /* number of columns of ptab              */

  /*  clip_insigs tries to clip heading and trailing insignificant entries 
   *  in each row of the parsertable ptab. The results of the algorithm 
   *  are returned in value *sdsval.
   *
   ***/
   
   {  int   *rowptr; /* rowptr[i] is the startposition of row i in ptab    */
      short *first,  /* first[i] is the position of the first significant  */
                     /* entry in row i					   */
            *last;   /* last i is the position of the last significant     */
                     /* entry in row i					   */
   
      register int   rowcount = 0; /* summes up the distances between the  */
      			           /* first and the last significant entry */
      			           /* for all rows			   */
      register short i;            /* loopindice */
      
      
      /* allocate store */
      if( ( rowptr = sdsval->rowptr = 
         (int *)malloc( nor * sizeof( int ) ) ) == NULL )
      		errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "rowptr" );
      		
      if( ( first  = sdsval->first =
          (short *)malloc( nor * sizeof( short ) ) ) == NULL )
                errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "first" );
                
      if((last  = sdsval->last = 
          (short *)malloc( nor * sizeof( short ) ) ) == NULL )
                errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "last" );
                
      /* find insignificant haeds and tails of rows in ptab */
      for( i = 0; i < nor; i++ )  {
      
      		first[i] = get_firstsigpos( ptab + i * noc, noc );
      		
      		last[i]  = get_lastsigpos( ptab + i * noc, noc );
      		
      		rowptr[i] = rowcount;
      		
      		if( last[i] != NIL ) 
      			rowcount += last[i] - first[i] + 1;
      			
      }/* for i */
      
      for( i = 0; i < nor; i++ )
      		rowptr[i] -= first[i];
    
   }/* clip_insigs */
      


/*============================================================================*/
/*============================================================================*/
/*======================				======================*/
/*======================   FUNCTIONS FOR RCS-METHOD     ======================*/
/*======================				======================*/
/*============================================================================*/
/*============================================================================*/ 

void search_eqrows( rcsval, ptab, nor, noc )

     rcstype *rcsval; /* contains the results of the RCS-Scheme */
     short   *ptab,   /* T-table or N-table                     */
              nor,    /* number of rows of ptab                 */
              noc;    /* number of columns of ptab              */

  /*  search_eqrows searches equal rows in the parsertable ptab. The results
   *  of the algorithm are returned in value *rcsval.
   *
   ***/
   
   {  short   *rowptr,                 /* rowptr[i] is the the smallest index */
   				       /* of all rows equal with row number i */
              *rowind;                 /* rowind[i] is the rowindex of row i  */
              			       /* in the optimized parse-table        */
      register short  i, j,  	       /* loop-indices                        */
      		      rowindcount = 0; /* counts the rowindices of the        */
      		      		       /* optmized parse-table                */
           
      /* allocate store */
      if( ( rowptr = rcsval->rowptr =
              (short *)malloc( nor * sizeof( short ) ) ) == NULL )
                errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "rowptr" );
                
      if( ( rowind = rcsval->rowind = 
              (short *)malloc( nor * sizeof( short ) ) ) == NULL )
                errmsg( OPTHELPFUNC, NOSPACEERR, ABORT, "rowind" );
      
      
      /* search for equal rows */
      for( i = 0; i < nor; i++ ) {
                rowptr[i] = i;
                for( j = 0; j < i; j++ )
                        if( rows_eq( ptab + i * noc, ptab + j * noc, noc ) )  {
                                rowptr[i] = j;
                                break;
                        }
                        
      }/* for i */
      
      
      for( i = 0; i < nor; i++ )
                if( rowptr[i] == i )
                        rowind[i] = rowindcount++;
                else
                        rowind[i] = rowind[ rowptr[i] ];
                        
        
      rcsval->maxrowind = rowindcount - 1;
       
   }/* search_eqrows */

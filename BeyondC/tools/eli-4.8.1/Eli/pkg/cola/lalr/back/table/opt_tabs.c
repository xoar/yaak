/*
** $Id: opt_tabs.c,v 1.4 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: opt_tabs.c,v 1.4 1997/08/29 08:38:08 mjung Exp $";

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
/* filename: opt_tabs.c                       first edit   :   8 .  6 . 89    */
/* author  : Christian Zeitel                 last  change :  10 .  7 . 90    */
/******************************************************************************/

/********************************* CONTENTS ************************************
 *									       *
 *  This module optimizes the terminaltable and the nonterminaltable after     *
 *  special optimization-methods which are given by parameter optkind. The     *
 *  different optimization methods are :				       *
 *									       *
 *   -GCS : Graph Colouring Scheme					       *
 *   -LES : Line Elemination Scheme					       *
 *   -RDS : Row Displacement Scheme					       *
 *   -SDS : Significant Distance Scheme					       *
 *   -RCS : Row Collumn Scheme						       *
 *									       *
 *  All this metods are described in					       *
 *  "Optimization of Parser Tables for Portable Compilers", P. Denker, K.      *
 *       Duerre and J. Heuft, TOPLAS 6 (4), S.564-572, 1984		       *
 *									       *
 ****************************** INCLUDE-FILES *********************************/

#include <stdio.h>

#include <string.h>

#include "error.h"

#include "optfunc.h"      /* interface to optimization-functions  */

#include "tabsopttype.h" /* typedefinition for type opt(kind)type */

/******************************** FUNCTION-MACROS *****************************/

#define  strequal( str1, str2 )   ! strcmp( str1, str2 )

/******************************** CONSTANT-MACROS *****************************/

#define  NOSORT      0

#define  SORT        1

#define  ROWFIRST    0

#define  COLFIRST    1

#define  NOMERGE     0

#define  MERGE       1

/******************************************************************************/

typedef  short  *readtype[];

void  optim_copa(pt_data, opt_data, optkind, optinfo, addinfo)

      readtype        pt_data;   /* interface between input-module */
      				 /* and optimization-module	   */
      opttype        *opt_data;  /* interface between optimization-*/
      				 /* and printing-module            */
      optkindtype     optkind;   /* contains kind of optimization  */
      
      char	      optinfo;   /* if <>0, additional information */
      				 /* about optimization is printed  */
      				 /* on file "opt.out"		   */
      char            addinfo;   /* if <>0, additional information */
      				 /* about the generation-process is*/
      				 /* printed on standardoutput      */

{  FILE  *fp_opt = NULL; /* filepointer to file to file "opt.out" */

	if(addinfo)
		printf("  C**module opt_tabs :started!\n");
		
	
	/* open file collecting optimization-results */
        if( optinfo )
		if( ( fp_opt = fopen("opt.out", "w") ) == NULL )
      	  		errmsg( OPT_TABS, FILEERR, ABORT, "opt.out" );
	

	/* select optimization for terminaltable */
        
        if( strequal( optkind.ttaboptkind, "GCSA" ) )
        	      Tmk_GCSopt( pt_data, opt_data, optinfo, 
        	                  fp_opt, addinfo, SORT );
        else if( strequal( optkind.ttaboptkind, "GCSB" ) )
        	      Tmk_GCSopt( pt_data, opt_data, optinfo, 
        	                  fp_opt, addinfo, NOSORT );
        else if( strequal( optkind.ttaboptkind, "LESA" ) )
        	      Tmk_LESopt( pt_data, opt_data, optinfo,
        	                  fp_opt, addinfo, ROWFIRST );
        else if( strequal( optkind.ttaboptkind, "LESB" ) )
        	      Tmk_LESopt( pt_data, opt_data, optinfo,
        	                  fp_opt, addinfo, COLFIRST );
        else if( strequal( optkind.ttaboptkind, "RDS" ) )
        	      Tmk_RDSopt( pt_data, opt_data, optinfo, fp_opt, addinfo );
        else if( strequal( optkind.ttaboptkind, "SDS" ) )
        	      Tmk_SDSopt( pt_data, opt_data, optinfo, fp_opt, addinfo );
        else if( strequal( optkind.ttaboptkind, "RCSA" ) )
        	      Tmk_RCSopt( pt_data, opt_data, optinfo,
        	                  fp_opt, addinfo, NOMERGE );
        else if( strequal( optkind.ttaboptkind, "RCSB" ) )
        	      Tmk_RCSopt( pt_data, opt_data, optinfo,
        	                  fp_opt, addinfo, MERGE );
        else /* not a legal optimization-method	*/
             errmsg( OPT_TABS, SELECTERR, ABORT, optkind.ttaboptkind );
             
             
	/* select optimization for nonterminaltable */
        
        if( strequal( optkind.ntaboptkind, "GCSA" ) )
        	      Nmk_GCSopt( pt_data, opt_data, optinfo,
        	                  fp_opt, addinfo, SORT );
        else if( strequal( optkind.ntaboptkind, "GCSB" ) )
        	      Nmk_GCSopt( pt_data, opt_data, optinfo,
        	                  fp_opt, addinfo, NOSORT );
        else if( strequal( optkind.ntaboptkind, "LESA" ) )
        	      Nmk_LESopt( pt_data, opt_data, optinfo,
        	                  fp_opt, addinfo, ROWFIRST );
        else if( strequal( optkind.ntaboptkind, "LESB" ) )
        	      Nmk_LESopt( pt_data, opt_data, optinfo,
        	                  fp_opt, addinfo, COLFIRST );
        else if( strequal( optkind.ntaboptkind, "RDS" ) )
        	      Nmk_RDSopt( pt_data, opt_data, optinfo, fp_opt, addinfo );
        else if( strequal( optkind.ntaboptkind, "SDS" ) )
        	      Nmk_SDSopt( pt_data, opt_data, optinfo, fp_opt, addinfo );
        else if( strequal( optkind.ntaboptkind, "RCSA" ) )
        	      Nmk_RCSopt( pt_data, opt_data, optinfo,
        	                  fp_opt, addinfo, NOMERGE );
        else if( strequal( optkind.ntaboptkind, "RCSB" ) )
        	      Nmk_RCSopt( pt_data, opt_data, optinfo,
        	                  fp_opt, addinfo, MERGE );
        else /* not a legal optimization-method	*/
             errmsg( OPT_TABS, SELECTERR, ABORT, optkind.ntaboptkind );
        
        if( optinfo )
        	fclose( fp_opt );
             
}/* optim_copa */

/*
** $Id: wrt_tabs.c,v 1.6 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: wrt_tabs.c,v 1.6 1997/08/29 08:38:08 mjung Exp $";

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
/* filename: wrt_tabs.c                       first edit   :  8 .  6 . 89     */
/* author  : Christian Zeitel                 last  change : 10 .  7 . 90     */
/******************************************************************************/

/********************************* CONTENTS ************************************
 *									       *
 *  This module selects the function which prints out the optimized parse      *
 *  tables in C-programcode. The selected function matches with the selec-     *
 *  ted optimization-method.						       *
 *									       *
 ******************************* INCLUDE-FILES ********************************/

#include <stdio.h>

#include <string.h>

#include "error.h"

#include "wrtfunc.h"     /* interface to printing functions  */

#include "tabsopttype.h" /* typedefinitions of opt(kind)type */

/******************************** FUNCTION-MACROS *****************************/

#define  strequal( str1, str2 )   ! strcmp( str1, str2 )

/*******************************  CONSTANT-MACROS *****************************/

#define NOMERGE 0

#define MERGE   1

/******************************************************************************/

typedef  short  *readtype[];

void write_copa( opt_data, optkind, pt_data, addinfo )

      opttype     *opt_data; /* interface between optimization- */
      			     /* module and printing-module      */		
      optkindtype  optkind;  /* contains kind of optimization   */
      	     
      readtype     pt_data;  /* interfacevector between input-  */
      			     /* module and optimization-module  */
      char         addinfo;  /* <>0, if additional information  */
      			     /* about the generating process is */
      			     /*printed to standardoutput        */ 
      
{   
  	FILE  *fp,     /* contains the  parsertables                     */
  	      *fp_sem; /* contains semantic information of the terminals */
  	
  	
  	
  	if( addinfo )
        	printf("  C**module wrt_tabs: started!\n");
              
        if( ( fp = fopen("ptabs.h", "w") ) == NULL )
        	errmsg( WRT_TABS, FILEERR, ABORT, "ptabs.h" );
        
        if( ( fp_sem = fopen("seminf.h", "w") ) == NULL )
        	errmsg( WRT_TABS, FILEERR, ABORT, "seminf.h" ); 	
        
        /* print out all tables not changed by optimization */

	fputs ("#ifndef PTABS_H\n#define PTABS_H\n\n", fp);
        Wrt_fixtabs( fp, fp_sem, pt_data, addinfo );
        
        fclose( fp_sem );
        
        /* select optimization for terminaltable */
        
        if( strequal( optkind.ttaboptkind, "GCSA" ) || 
            strequal( optkind.ttaboptkind, "GCSB"   ) )
        		Twrt_GCStabs( fp, pt_data, opt_data, addinfo );
        else if( strequal( optkind.ttaboptkind, "LESA" ) ||
                 strequal( optkind.ttaboptkind, "LESB"   ) )
        		Twrt_LEStabs( fp, pt_data, opt_data, addinfo ); 
        else if( strequal( optkind.ttaboptkind, "RDS" ) )
        		Twrt_RDStabs( fp, pt_data, opt_data, addinfo );
        else if( strequal( optkind.ttaboptkind, "SDS" ) )
        		Twrt_SDStabs( fp, pt_data, opt_data, addinfo );
        else if( strequal( optkind.ttaboptkind, "RCSA" ) )
        		Twrt_RCStabs( fp, pt_data, opt_data, addinfo, NOMERGE );
        else if( strequal( optkind.ttaboptkind, "RCSB" ) )
        		Twrt_RCStabs( fp, pt_data, opt_data, addinfo, MERGE );
        else
             errmsg( WRT_TABS, SELECTERR, ABORT, optkind.ttaboptkind );
             
        /* select optimization for nonterminaltable */
        
        if( strequal( optkind.ntaboptkind, "GCSA" ) || 
            strequal( optkind.ntaboptkind, "GCSB"   ) )
        		Nwrt_GCStabs( fp, pt_data, opt_data, addinfo );
        else if( strequal( optkind.ntaboptkind, "LESA" ) ||
        	 strequal( optkind.ntaboptkind, "LESB"   ) )
        		Nwrt_LEStabs( fp, pt_data, opt_data, addinfo );
        else if( strequal( optkind.ntaboptkind, "RDS" ) )
        		Nwrt_RDStabs( fp, pt_data, opt_data, addinfo );
        else if( strequal( optkind.ntaboptkind, "SDS" ) )
        		Nwrt_SDStabs( fp, pt_data, opt_data, addinfo );
        else if( strequal( optkind.ntaboptkind, "RCSA" ) )
        		Nwrt_RCStabs( fp, pt_data, opt_data, addinfo, NOMERGE );
        else if( strequal( optkind.ntaboptkind, "RCSB" ) )
        		Nwrt_RCStabs( fp, pt_data, opt_data, addinfo, MERGE );
        else
             errmsg( WRT_TABS, SELECTERR, ABORT, optkind.ntaboptkind );

	fputs("\n\n#endif\n\n", fp);
        fclose( fp );
        
}/* write_copa */          

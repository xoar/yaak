/*
** $Id: cmrsasx.c,v 1.5 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: cmrsasx.c,v 1.5 1997/08/29 08:38:08 mjung Exp $";

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
/* filename: cmrsasx.c                         first edit   :  4 . 7 . 90     */
/* author  : Christian Zeitel                  last Change  : 10 . 8 . 90     */
/******************************************************************************/

/******************************** CONTENTS *************************************
 *   									       *
 *  This tool adds the sxcodes of the terminals used by the scanner and the    *
 *  productioncodes used by the semantic analysis in property-nodes  to the    *
 *  property-lists of the definition-nodes in the COMAR-data-structure         *
 *  belonging to the corresponding  terminals or productions. 		       *
 *  									       *
 *  INPUT:  -name of the COMAR-file in argv[1].				       *
 *  ------                                                                     *
 *									       *
 *  OUTPUT: -COMAR-file "CMRSASX.out" with inserted sxcodes for terminals and  *
 *  -------  productioncodes for productions. Productions of the abstract      *
 *	     grammar are marked.     					       *
 *									       *
 ******************************* INCLUDE FILES ********************************/

#include  <stdio.h>

#include  <string.h>

#include  "comar.h"

#include  "error.h"

extern void cmrtool();

/******************************************************************************/

int	main( argc, argv )
      int   argc;
      char *argv[];
      
{ 
    FILE    *fp_comar;
    
    p_comar  Comar_root;
    
    char symbstr[80];   

    if( argc != 2 ) 
    	errmsg( CMRTOOL, CT1USERERR, ABORT, DUMMY );
    	
    if( ( fp_comar = fopen( argv[1], "r") ) == NULL )
        errmsg( CMRTOOL, FILEERR, ABORT, argv[1] );
        
    /* input old COMAR-datastructure */    
    Comar_root  = INPUT( fp_comar );
    fclose( fp_comar );
    
    /* check if filename isn't too long */
#if defined(__cplusplus) || defined(__STDC__)
    if(strlen(argv[1]) > (size_t) 76)
#else
    if(strlen(argv[1]) > 76)
#endif
	errmsg( CMRTOOL, NAMETOOLONG, ABORT, argv[1] );
    
    strcpy(symbstr, argv[1]);

    if( ( fp_comar = fopen(strcat(symbstr, ".sem"), "w" ) ) == NULL )
    	errmsg( CMRTOOL, FILEERR, ABORT, symbstr );
    	
    /* insert syntaxcodes for terminals and productioncodes */
    cmrtool( Comar_root );
    
    /* output new COMAR-datastructure */ 
    OUTPUT( fp_comar, Comar_root );
    fclose( fp_comar );

    return(0);    
}/* main */

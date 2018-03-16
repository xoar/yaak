/*
** $Id: errandio.c,v 1.4 2007/02/23 12:21:58 peter Exp $
*/
static char rcs_id[]= "$Id: errandio.c,v 1.4 2007/02/23 12:21:58 peter Exp $";

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

/***********************************************************************
 **
 **   Filename   :  errandio.c 
 **
 **   Author     :  Ursula Stellmacher
 **
 **   Date       :  12.11.88
 **
 **   Last change:  12.11.88
 **
 **
 **   Task       : contains functions for input and output and for
 **                errorhandling
 **
 **
 **********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errandio.h"


/***********************************************************************
 **
 **   Function   :  error_messsage
 **
 **   Task       :  output of an errormessage and exit(0)
 **
 **********************************************************************/

PUBLIC void error_message ( error_code, function, s1, s2 )

short error_code;
char *function, *s1 , *s2;
{
     switch ( error_code )
     {
        case FOPENERR  :
                       {
                          printf("\n");
                          printf("fileopenerror\n");
                          printf("\n");
                          printf("function : %s\n", function );
			  printf("\n");
                          printf("cannot open file %s for", s1 );
                          if ( strcmp( s2 , READ ) == 0 )
                          {
                             printf("reading\n");
                          }
                          if ( strcmp( s2 , WRITE ) == 0 )
                          {
                             printf("writing\n");
                          }
                          exit(0);
                       }

        case PGRCALLERR :
                       {
                          printf("\n");
                          printf("programcallerror\n");
                          printf("\n");
                          printf("function : %s\n", function );
                          printf("\n");
			  printf("usage : programname 'inputfile'\n");
                          exit(0);
                       }

        case LHSPROD :
		       {
			  printf("\n");
			  printf("productionname is not stored in the symboltable\n");
			  printf("\n");
			  printf("function : %s\n", function );
			  exit(0);
		       }
                       

        case LHSDEFTAB:
		       {
			  printf("\n");
			  printf("symbol of the left side is not stored as a \n");
			  printf("nonterminal in the definitiontable\n");
			  printf("\n");
			  printf("function : %s\n", function );
			  exit(0);
		       }

        case LHSSYMTAB:
		       {
			  printf("\n");
			  printf("symbol  of the left side is not stored as a \n");
			  printf("nonterminal in the symboltable\n");
			  printf("\n");
			  printf("function : %s\n", function );
			  exit(0);
                       }

        case RHSSYMTAB:
		       {
			 printf("\n"); 
		         printf("terminal or nonterminal of the right side\n"); 
			 printf("is not stored in the symboltable\n");
		         printf("\n"); 
		         printf("function : %s\n", function ); 
			 exit(0);
		       }

        case RHSOTHER:
		      {
			 printf("\n");
			 printf("other is not stored in the symboltable\n");
			 printf("\n");
			 printf("function : %s\n", function );
			 exit(0);
		      }

         case INPUTERROR:
		       {
			 printf("\n");
			 printf("inputerror by INPUT of the external COMAR data\n");
			 printf("\n");
			 printf("function : %s\n", function );
			 exit(0);
                       }


         default      :
                       {
                          exit(0);
                       }
     } /* end switch */
} /* end of error_message */


/***********************************************************************
 **
 **   Function   :  dat_open
 **
 **   Task       :  fileopening with the modus READ/WRITE
 **                 
 **   Return     :  FILE*
 **
 **********************************************************************/

PUBLIC FILE *dat_open ( dat_name, mode )

char  *dat_name;
char  *mode;

{
    FILE    *f_ptr,
            *fopen();


    if ( ( f_ptr = fopen ( dat_name , mode ) ) == (FILE*) NULL )
    {
        error_message ( FOPENERR , "dat_open", dat_name, mode );
    }
    return ( f_ptr );


} /* end of dat_open */

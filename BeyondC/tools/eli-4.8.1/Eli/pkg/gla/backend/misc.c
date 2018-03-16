static char RCSid[] = "$Id: misc.c,v 1.7 2009/09/24 17:02:28 profw Exp $";
/* Copyright, 1989, The Regents of the University of Colorado */

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

#include "dj.h"
#define MAXLINE 200

/* allocate_character_array - allocate memory for an integer array of the given size */

unsigned char *allocate_character_array( size )
int size;

    {
    unsigned char *mem;
    
    mem = (unsigned char *)malloc( size );
 
    if ( mem == NULL )
        flexfatal( "memory allocation failed in allocate_character_array()" );
 
    return ( mem );
    }


/* reallocate_character_array - increase the size of a dynamic array */

unsigned char *reallocate_character_array( array, size )
unsigned char *array;
int size;

    {        
    unsigned char *new_array;

    new_array = (unsigned char *)realloc( array, size );
 
    if ( new_array == NULL )
        flexfatal( "attempt to increase array size failed" );

    return ( new_array );                                     
    }
 
/* flexfatal - report a fatal error message and terminate
 *
 * synopsis
 *    char msg[];
 *    flexfatal( msg );
 */
 
void flexfatal( msg )
char *msg;
 
    {
    fprintf( stderr, "glagen: fatal internal error %s\n", msg );
    /* flexend( 1 );*/
    exit(1);
    }

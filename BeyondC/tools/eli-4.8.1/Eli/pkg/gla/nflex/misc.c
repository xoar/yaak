/* $Id: misc.c,v 1.6 2013/11/09 19:24:50 profw Exp $ */
/* misc - miscellaneous flex routines */

/*
 * Copyright (c) 1987, the University of California
 * 
 * The United States Government has rights in this work pursuant to
 * contract no. DE-AC03-76SF00098 between the United States Department of
 * Energy and the University of California.
 * 
 * This program may be redistributed.  Enhancements and derivative works
 * may be created provided the new works, if made available to the general
 * public, are made available for use by anyone.
 */

#include <ctype.h>
#include "flexdef.h"
#include "parse.h"
#include "main.h"
#include "misc.h"


/* action_out - write the actions from the temporary file to lex.yy.c
 *
 * synopsis
 *     action_out();
 *
 *     Copies the action file up to %% (or end-of-file) to lex.yy.c
 */

void
action_out()

    {
    }


/* allocate_array - allocate memory for an integer array of the given size */

void *allocate_array( size, element_size )
int size, element_size;

    {
    register void *mem = malloc( (unsigned) (element_size * size) );

    if ( mem == NULL )
	flexfatal( "memory allocation failed in allocate_array()" );

    return ( mem );
    }


/* bubble - bubble sort an integer array in increasing order
 *
 * synopsis
 *   int v[n], n;
 *   bubble( v, n );
 *
 * description
 *   sorts the first n elements of array v and replaces them in
 *   increasing order.
 *
 * passed
 *   v - the array to be sorted
 *   n - the number of elements of 'v' to be sorted */

void
bubble( v, n )
int v[], n;

    {
    register int i, j, k;

    for ( i = n; i > 1; --i )
	for ( j = 1; j < i; ++j )
	    if ( v[j] > v[j + 1] )	/* compare */
		{
		k = v[j];	/* exchange */
		v[j] = v[j + 1];
		v[j + 1] = k;
		}
    }


/* clower - replace upper-case letter to lower-case
 *
 * synopsis:
 *    unsigned char clower(), c;
 *    c = clower( c );
 */

unsigned char clower( c )
register unsigned char c;

    {
    return ( isupper(c) ? tolower(c) : c );
    }


/* copy_string - returns a dynamically allocated copy of a string
 *
 * synopsis
 *    unsigned char *str, *copy, *copy_string();
 *    copy = copy_string( str );
 */

unsigned char *copy_string( str )
register unsigned char *str;

    {
    register unsigned char *c;
    unsigned char *copy;

    /* find length */
    for ( c = str; *c; ++c )
	;

    copy = malloc( (unsigned) ((c - str + 1) * sizeof( unsigned char )) );

    if ( copy == NULL )
	flexfatal( "dynamic memory failure in copy_string()" );

    for ( c = copy; (*c++ = *str++); )
	;
    
    return ( copy );
    }


/* cshell - shell sort a short array in increasing order
 *
 * synopsis
 *
 *   short v[n];
 *   int n;
 *   cshell( v, n );
 *
 * description
 *   does a shell sort of the first n elements of array v.
 *
 * passed
 *   v - array to be sorted
 *   n - number of elements of v to be sorted
 */
void
cshell( v, n )
short v[];
int n;

    {
    int gap, i, j, jg;
    unsigned char k;

    for ( gap = n / 2; gap > 0; gap = gap / 2 )
	for ( i = gap; i < n; ++i )
	    for ( j = i - gap; j >= 0; j = j - gap )
		{
		jg = j + gap;

		if ( v[j] <= v[jg] )
		    break;

		k = v[j];
		v[j] = v[jg];
		v[jg] = k;
		}
    }


/* dataend - finish up a block of data declarations
 *
 * synopsis
 *    dataend();
 */
void
dataend()

    {
    }



/* dataflush - flush generated data statements
 *
 * synopsis
 *    dataflush();
 */
void
dataflush()

    {
    }

/* lerrif - report an error message formatted with one integer argument
 *
 * synopsis
 *    char msg[];
 *    int arg;
 *    lerrif( msg, arg );
 */

void
lerrif( msg, arg )
char msg[];
int arg;

    {
    char errmsg[MAXLINE];
    (void) sprintf( errmsg, msg, arg );
    flexerror( errmsg );
    }


/* lerrsf - report an error message formatted with one string argument
 *
 * synopsis
 *    char msg[]; unsigned char arg[];
 *    lerrsf( msg, arg );
 */

void
lerrsf( msg, arg )
char msg[]; unsigned char arg[];

    {
    char errmsg[MAXLINE];

    (void) sprintf( errmsg, msg, arg );
    flexerror( errmsg );
    }


/* flexerror - report an error message and terminate
 *
 * synopsis
 *    char msg[];
 *    flexerror( msg );
 */

void
flexerror( msg )
char msg[];

    {
    fprintf( stderr, "flex: %s\n", msg );
    flexend( 1 );
    }


/* flexfatal - report a fatal error message and terminate
 *
 * synopsis
 *    char msg[];
 *    flexfatal( msg );
 */

void
flexfatal( msg )
char msg[];

    {
    fprintf( stderr, "flex: fatal internal error %s\n", msg );
    flexend( 1 );
    }


/* line_directive_out - spit out a "# line" statement */

void
line_directive_out( output_file_name )
FILE *output_file_name;

    {
    }


/* mk2data - generate a data statement for a two-dimensional array
 *
 * synopsis
 *    int value;
 *    mk2data( value );
 *
 *  generates a data statement initializing the current 2-D array to "value"
 */
void
mk2data( value )
int value;

    {
    }


/* mkdata - generate a data statement
 *
 * synopsis
 *    int value;
 *    mkdata( value );
 *
 *  generates a data statement initializing the current array element to
 *  "value"
 */
void
mkdata( value )
int value;

    {
    }


/* myctoi - return the integer represented by a string of digits
 *
 * synopsis
 *    char array[];
 *    int val, myctoi();
 *    val = myctoi( array );
 *
 */

int
myctoi( array )
char array[];

    {
    int val = 0;

    (void) sscanf( array, "%d", &val );

    return ( val );
    }


/* myesc - return character corresponding to escape sequence
 *
 * synopsis
 *    unsigned char array[], c, myesc();
 *    c = myesc( array );
 *
 */

unsigned char myesc( array )
unsigned char array[];

    {
    switch ( array[1] )
	{
	case 'n': return ( '\n' );
	case 't': return ( '\t' );
	case 'f': return ( '\f' );
	case 'r': return ( '\r' );
	case 'b': return ( '\b' );

	case '0':
	    if ( isdigit(array[2]) )
		{ /* \0<octal> */
		unsigned char c, esc_char;
		register int sptr = 2;

		while ( isdigit(array[sptr]) )
		    /* don't increment inside loop control because the
		     * macro will expand it to two increments!  (Not a
		     * problem with the C version of the macro)
		     */
		    ++sptr;

		c = array[sptr];
		array[sptr] = '\0';

		esc_char = otoi( (char*)(array + 2 ));
		array[sptr] = c;

		if ( esc_char == '\0' )
		    {
		    synerr( "escape sequence for null not allowed" );
		    return ( 1 );
		    }

		return ( esc_char );
		}

	    else
		{
		synerr( "escape sequence for null not allowed" );
		return ( 1 );
		}

#ifdef NOTDEF
	case '^':
	    {
	    register unsigned char next_char = array[2];

	    if ( next_char == '?' )
		return ( 0x7f );
	    
	    else if ( next_char >= 'A' && next_char <= 'Z' )
		return ( next_char - 'A' + 1 );
    
	    else if ( next_char >= 'a' && next_char <= 'z' )
		return ( next_char - 'z' + 1 );
    
	    synerr( "illegal \\^ escape sequence" );

	    return ( 1 );
	    }
#endif
	}
    
    return ( array[1] );
    }


/* otoi - convert an octal digit string to an integer value
 *
 * synopsis:
 *    int val, otoi();
 *    char str[];
 *    val = otoi( str );
 */

int otoi( str )
char str[];

    {
#ifdef FTLSOURCE
    fortran int gctoi()
    int dummy = 1;

    return ( gctoi( str, dummy, 8 ) );
#else
    unsigned int result;

    (void) sscanf( str, "%o", &result );

    return ( result );
#endif
    }




/* reallocate_array - increase the size of a dynamic array */

void *reallocate_array( array, size, element_size )
void *array;
int size, element_size;

    {
    register void *new_array = realloc( array,
					(unsigned) (size * element_size ));

    if ( new_array == NULL )
	flexfatal( "attempt to increase array size failed" );
    
    return ( new_array );
    }


/* skelout - write out one section of the skeleton file
 *
 * synopsis
 *    skelout();
 *
 * DESCRIPTION
 *    Copies from skelfile to stdout until a line beginning with "%%" or
 *    EOF is found.
 */
void
skelout()

    {
    }


/* transition_struct_out - output a yy_trans_info structure
 *
 * synopsis
 *     int element_v, element_n;
 *     transition_struct_out( element_v, element_n );
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

void
transition_struct_out( element_v, element_n )
int element_v, element_n;

    {
    }

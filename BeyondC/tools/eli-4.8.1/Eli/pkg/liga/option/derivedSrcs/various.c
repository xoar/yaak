/* $Id: various.c,v 1.2 1999/11/24 10:50:58 cogito Exp $ */
/* $Log: various.c,v $
 * Revision 1.2  1999/11/24 10:50:58  cogito
 * option directly accesses string array from csmtbl.[ch].
 * this array has been remaned to "strng". option is
 * changed accordingly.
 *
 * Revision 1.1  1996/02/06 13:30:25  cogito
 * Initial revision
 *
 * Revision 2.5  1993/06/17  10:48:06  cogito
 * include strings.h becomes include string.h
 *
 * Revision 2.4  1991/11/08  09:51:17  cogito
 * evalpos substituted by curpos
 *
 * Revision 2.3  1991/02/21  10:59:25  cogito
 * replaced strdup() by malloc() and strcpy()
 * */
static char rcs_id[]= "$Id: various.c,v 1.2 1999/11/24 10:50:58 cogito Exp $";

/***********************************************************************\
*	various.c							*
*	various functions for the option handler			*
*									*
*	Written 06/19/90 - 02/21/91	by HaDeS			*
\***********************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "err.h"
#include "opt_liga.h"

extern  POSITION        curpos;

/*
** FUNCTION DEFINITIONS
*/

void	errormesg (msg)
char *msg;
{
	message (ERROR, msg, 0, &curpos);
} /* errormesg */

char	*getelistring (id)
int id;
{
	char	*newstr;

	newstr= (char *) malloc(strlen(strng[id])+1);
	return (strcpy(newstr, strng[id]));
} /* getelistring */

char	*str2upper (str)
char *str;
{
	char	*c;

	for (c= str; *c; c++)
		if (islower(*c))
			*c= toupper(*c);
	return (str);
} /* str2upper */

int     cmpidkw (id, kws)
int id;
keywords kws;
/* compare identifier to keywords       */
{
	int     result;
	int     i;
	char    *keystr;
	char    **cmpstr;

	result= -1;
	keystr= str2upper (getelistring (id));
	for (cmpstr= kws, i=0; (*cmpstr); cmpstr++, i++)
	if (!strcmp (keystr, (*cmpstr)))
	result= i;

	return (result);
} /* cmpidkw */


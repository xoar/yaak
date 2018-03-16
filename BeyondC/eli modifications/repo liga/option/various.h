/* $Id: various.h,v 1.1 2015/05/11 12:17:23 pfahler Exp $ */
/* $Log: various.h,v $
/* Revision 1.1  2015/05/11 12:17:23  pfahler
/* specs for liga's option file interpreter.
/*
 * Revision 1.1  1996/02/06 13:30:25  cogito
 * Initial revision
 *
 * Revision 2.1  1990/12/04  14:56:43  cogito
 * new version of option handler
 * */

/***********************************************************************\
*	various.h							*
*	Header file for various functions for the option handler	*
*									*
*	Written 06/19/90 - 10/15/90	by HaDeS			*
\***********************************************************************/

#ifndef _VARIOUS_H_INCL
#define _VARIOUS_H_INCL

/*
** FUNCTION DECLARATIONS
*/
#ifdef ELI_ARG
#undef ELI_ARG
#endif

#if defined(__STDC__) || defined(__cplusplus)
#define ELI_ARG(proto)    proto
#else
#define ELI_ARG(proto)    ()
#endif

extern	void	errormesg ELI_ARG((char *));
extern	char	*getelistring ELI_ARG((int));
extern	char	*str2upper ELI_ARG((char*));
extern	int	cmpidkw ELI_ARG((int, keywords));

#endif


/* $Id: conflicts.h,v 1.1 2015/05/11 12:17:23 pfahler Exp $ */
/* $Log: conflicts.h,v $
/* Revision 1.1  2015/05/11 12:17:23  pfahler
/* specs for liga's option file interpreter.
/*
 * Revision 1.1  1996/02/06 13:30:25  cogito
 * Initial revision
 *
 * Revision 2.1  1990/12/04  14:42:01  cogito
 * new version of option handler
 * */

/***********************************************************************\
*	conflicts.h							*
*	Header file for test function for the option handler		*
*									*
*	Written 08/08/90 - 10/15/90	by HaDeS			*
\***********************************************************************/

#ifndef CONFLICTS_H_INCL
#define CONFLICTS_H_INCL
#ifdef ELI_ARG
#undef ELI_ARG
#endif

#if defined(__STDC__) || defined(__cplusplus)
#define ELI_ARG(proto)    proto
#else
#define ELI_ARG(proto)    ()
#endif

extern	int	Conflict_Test ELI_ARG((OptCollect));

#endif


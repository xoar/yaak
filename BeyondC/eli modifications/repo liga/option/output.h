/* $Id: output.h,v 1.1 2015/05/11 12:17:23 pfahler Exp $ */
/* $Log: output.h,v $
/* Revision 1.1  2015/05/11 12:17:23  pfahler
/* specs for liga's option file interpreter.
/*
 * Revision 1.1  1996/02/06 13:30:25  cogito
 * Initial revision
 *
 * Revision 1.1  1992/03/05  13:18:26  cogito
 * Initial revision
 *
 * Revision 2.2  1991/08/26  14:23:06  cogito
 * *** empty log message ***
 *
 * Revision 2.1  90/12/04  14:55:17  cogito
 * new version of option handler
 * 
 * Revision 2.1  90/12/04  14:45:54  cogito
 * new version of option handler
 *  */

/***********************************************************************\
*	output.h							*
*	Header file for output function for the option handler		*
*									*
*	Written 07/02/90 - 11/14/90	by HaDeS			*
\***********************************************************************/

#ifndef _OUTPUT_H_INCL
#define _OUTPUT_H_INCL

#define	EXPFNAME	"expand.options"
#define	ORDFNAME	"order.options"
#define	OPTFNAME	"optim.options"
#define	BEFNAME		"backend.options"

#ifdef ELI_ARG
#undef ELI_ARG
#endif

#if defined(__STDC__) || defined(__cplusplus)
#define ELI_ARG(proto)    proto
#else
#define ELI_ARG(proto)    ()
#endif

extern	void	Output ELI_ARG((OptCollect, int));

#endif


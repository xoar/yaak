/* $Id: optlists.h,v 1.1 2015/05/11 12:17:23 pfahler Exp $ */
/* $Log: optlists.h,v $
/* Revision 1.1  2015/05/11 12:17:23  pfahler
/* specs for liga's option file interpreter.
/*
 * Revision 1.1  1996/02/06 13:30:25  cogito
 * Initial revision
 *
 * Revision 1.1  1992/11/13  12:43:32  cogito
 * Initial revision
 *
 * Revision 2.1  1990/12/04  14:44:17  cogito
 * new version of option handler
 * */

/***********************************************************************\
*	optlists.h								*
*	header file for LIGA option handler				*
*									*
*	Written 06/21/90 - 10/15/90	by HaDeS			*
\***********************************************************************/

#ifndef _LISTS_H_INCL
#define _LISTS_H_INCL

#ifdef ELI_ARG
#undef ELI_ARG
#endif

#if defined(__STDC__) || defined(__cplusplus)
#define ELI_ARG(proto)    proto
#else
#define ELI_ARG(proto)    ()
#endif

typedef int SYMB;

extern IdList nullIdList ELI_ARG((void));
extern IdList creatIdList ELI_ARG((SYMB));
extern IdList concatIdList ELI_ARG((IdList, IdList));

extern ANamesList nullNamesList ELI_ARG((void));
extern ANamesList creatNamesList ELI_ARG((SYMB, IdList));
extern ANamesList concatNamesList ELI_ARG((ANamesList, ANamesList));

extern	ExpList	creatExpOList ELI_ARG((ExpOption));
extern	ExpList	concatExpOList ELI_ARG((ExpList, ExpList));

extern	OrdList	creatOrdOList ELI_ARG((OrdOption));
extern	OrdList	concatOrdOList ELI_ARG((OrdList,OrdList));

extern	OptList	creatOptOList ELI_ARG((OptOption));
extern	OptList	concatOptOList ELI_ARG((OptList, OptList));

extern	BEList	creatBEOList ELI_ARG((BEOption));
extern	BEList	concatBEOList ELI_ARG((BEList, BEList));

#endif


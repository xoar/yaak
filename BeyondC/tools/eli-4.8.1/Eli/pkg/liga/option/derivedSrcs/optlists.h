/* $Id: optlists.h,v 1.1 1996/02/06 13:30:25 cogito Exp $ */
/* $Log: optlists.h,v $
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

extern IdList nullIdList();
extern IdList creatIdList();
extern IdList concatIdList();

extern ANamesList nullNamesList();
extern ANamesList creatNamesList();
extern ANamesList concatNamesList();

extern	ExpList	creatExpOList();
extern	ExpList	concatExpOList();

extern	OrdList	creatOrdOList();
extern	OrdList	concatOrdOList();

extern	OptList	creatOptOList();
extern	OptList	concatOptOList();

extern	BEList	creatBEOList();
extern	BEList	concatBEOList();

#endif


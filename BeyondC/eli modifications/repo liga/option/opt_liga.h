/* $Id: opt_liga.h,v 1.1 2015/05/11 12:17:23 pfahler Exp $ */

/* $Log: opt_liga.h,v $
/* Revision 1.1  2015/05/11 12:17:23  pfahler
/* specs for liga's option file interpreter.
/*
 * Revision 1.3  2001/11/05 17:23:46  cogito
 * *** empty log message ***
 *
 * Revision 1.1  1996/02/06 13:30:25  cogito
 * Initial revision
 *
 * Revision 1.4  1992/11/13  12:58:44  cogito
 * option reader now uses clp to access command line parameters
 *
 * Revision 1.3  1991/07/23  17:20:49  cogito
 * expand options: INCLUDING_FUNCTION replaced by INCLUDING ON / OFF
 * order options: new option ARRANGE FAST to cancel default ARRANGE AUTOMATICALLY
 * backend options: new option FREE_TREE (opposite of KEEP_TREE)
 *
 * Revision 1.2  91/05/15  08:32:38  cogito
 * removed unused expand options
 * 
 * Revision 1.1  91/01/15  17:55:36  cogito
 * Initial revision
 *  */

/***********************************************************************\
*	opt_liga.h							*
*	Header file for specification of the LIDO option handler	*
*									*
*	Written 06/18/90 - 07/23/91	by HaDeS			*
\***********************************************************************/

#ifndef _LIGA_H_INCL
#define _LIGA_H_INCL
typedef	int		SYMB;


#include <string.h>
#include "csm.h"
#include "option_enums.h"
#include "option_types.h"
#include "keywords.h"
#include "various.h"
#include "optlists.h"
#include "output.h"
#include "conflicts.h"

#ifdef ELI_ARG
#undef ELI_ARG
#endif

#if defined(__STDC__) || defined(__cplusplus)
#define ELI_ARG(proto)    proto
#else
#define ELI_ARG(proto)    ()
#endif


extern	char *exp_fname, *ord_fname, *opt_fname, *be_fname;


extern	ExpOption	ExpOptEnter1 ELI_ARG((int, int));
extern	ExpOption	ExpOptEnter2 ELI_ARG((int));
extern	ExpOption	ExpOptEnter3 ELI_ARG((int));

extern	OrdOption	OrdOptEnter1 ELI_ARG((int, int));
extern	OrdOption	OrdOptEnter2 ELI_ARG((int, IdList));
extern	OrdOption	OrdOptEnter3 ELI_ARG((int));
extern	OrdOption	OrdOptEnter4 ELI_ARG((void));
extern	OrdOption	OrdOptEnter5 ELI_ARG((int, int, int));
extern	OrdOption	OrdOptEnter6 ELI_ARG((int, int, int, int, int, int, int));
extern	OrdOption	OrdOptEnter7 ELI_ARG((void));

extern	OptOption	OptOptEnter1 ELI_ARG((int));
extern	OptOption	OptOptEnter2 ELI_ARG((int));
extern	OptOption	OptOptEnter3 ELI_ARG((int, ANamesList));

extern	BEOption	BEOptEnter1 ELI_ARG((int));
extern	BEOption	BEOptEnter2 ELI_ARG((int, int));

extern	OptCollect	InitOpts ELI_ARG((void));
extern	OptCollect	JoinOpts ELI_ARG((OptCombin, OptCollect));
extern	int		Mix_Options ELI_ARG((int, OptCollect));

extern	OptCombin	TransferOpts1 ELI_ARG((ExpList));
extern	OptCombin	TransferOpts2 ELI_ARG((OrdList));
extern	OptCombin	TransferOpts3 ELI_ARG((OptList));
extern	OptCombin	TransferOpts4 ELI_ARG((BEList));

extern int AttrTypeId1 ELI_ARG((int, int));
extern int AttrTypeId2 ELI_ARG((void));

#endif


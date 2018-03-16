/* $Id: opt_liga.h,v 1.3 2001/11/05 17:23:46 cogito Exp peter $ */

/* $Log: opt_liga.h,v $
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


#include <string.h>
#include "csm.h"
#include "option_enums.h"
#include "option_types.h"
#include "keywords.h"
#include "various.h"
#include "optlists.h"
#include "output.h"
#include "conflicts.h"


typedef	int		SYMB;


extern	char *exp_fname, *ord_fname, *opt_fname, *be_fname;


extern	ExpOption	ExpOptEnter1();
extern	ExpOption	ExpOptEnter2();
extern	ExpOption	ExpOptEnter3();

extern	OrdOption	OrdOptEnter1();
extern	OrdOption	OrdOptEnter2();
extern	OrdOption	OrdOptEnter3();
extern	OrdOption	OrdOptEnter4();
extern	OrdOption	OrdOptEnter5();
extern	OrdOption	OrdOptEnter6();
extern	OrdOption	OrdOptEnter7();

extern	OptOption	OptOptEnter1();
extern	OptOption	OptOptEnter2();
extern	OptOption	OptOptEnter3();

extern	BEOption	BEOptEnter1();
extern	BEOption	BEOptEnter2();

extern	OptCollect	InitOpts();
extern	OptCollect	JoinOpts();
extern	int		Mix_Options();

extern	OptCombin	TransferOpts1();
extern	OptCombin	TransferOpts2();
extern	OptCombin	TransferOpts3();
extern	OptCombin	TransferOpts4();

extern int AttrTypeId1();
extern int AttrTypeId2();

#endif


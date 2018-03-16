/* $Log: keywords.h,v $
 * Revision 1.3  2001/11/05 17:23:46  cogito
 * *** empty log message ***
 *
 * Revision 1.1  1996/02/06 13:30:25  cogito
 * Initial revision
 *
 * Revision 2.2  1991/07/23  17:21:14  cogito
 * expand options: INCLUDING_FUNCTION replaced by INCLUDING ON / OFF
 * order options: new option ARRANGE FAST to cancel default ARRANGE AUTOMATICALLY
 * backend options: new option FREE_TREE (opposite of KEEP_TREE)
 *
 * Revision 2.1  90/12/04  14:43:08  cogito
 * new version of option handler
 *  */

/***********************************************************************\
*	keywords.h							*
*	strings with keywords for LIGA option handler			*
*									*
*	Written 06/20/90 - 07/23/90	by HaDeS			*
\***********************************************************************/

#ifndef _KEYWORDS_H_INCL
#define _KEYWORDS_H_INCL

typedef	char	*keywords[];

extern	keywords	exp1kw;
extern	keywords	exp2kw;
extern	keywords	exp3kw;
extern	keywords	ord1kw;
extern	keywords	ord2kw;
extern	keywords	ord3kw;
extern	keywords	ord4kw;
extern	keywords	opt1kw;
extern	keywords	opt2kw;
extern	keywords	opt3kw;
extern	keywords	opt4kw;
extern	keywords	be1kw;
extern	keywords	be2kw;

#endif


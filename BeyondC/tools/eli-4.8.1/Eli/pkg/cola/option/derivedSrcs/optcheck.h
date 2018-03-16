/***********************************************************************************\
*										    *
*   Option-Tool for Parser Generators						    *
*   Author: M.Jung 								    *
*   										    *
*   Headerfile defining Prototypes for Value Checking                               *
\***********************************************************************************/

/* $Id: optcheck.h,v 1.1 1992/01/22 15:14:23 cogito Exp $ */

#ifndef OPTCHECK_H
#define OPTCHECK_H

#if defined(__STDC__) || defined(__cplusplus)
int testval(int, int, POSITION *);
#else
int testval();
#endif

#endif

/* (C) Copyright 1997 University of Paderborn */

/* This file is part of the Eli translator construction system.

Eli is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

Eli is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with Eli; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

/*
** $Id: error.h,v 1.6 1997/08/29 08:38:08 mjung Exp $
*/

/******************************************************************************/
/* filename: error.h                          first edit   :  29 . 6 . 89     */
/* author  : Christian Zeitel                 last change  :  14 . 9 . 90     */
/******************************************************************************/

/******************************** CONTENTS *************************************
 *									       *
 *  This is the interface between an errorreporting module of the 	       *
 *  parsergenerator-backend or tool cmrsasx and the unique errorreport-module  *
 *  error. It contains the procedure for an error-report and the macro-names   *
 *  for the different errors.						       *
 *									       *
 ******************************************************************************/



extern  void errmsg(/* short modulenumber, errtextnumber, abort;
							  char *addinfo */);

  /*   Reports an error on file stderr and returns to the calling module, if 
   *   this is possible.
   *
   *    on entry-
   *       modulenumber contains the code of the module reporting the error. 
   *       errtextnumber contains the code of the errortext, which is printed
   *       to stderr.
   *       If abort is not zero, the program is aborted with exit-code 1.
   *       addinfo contains an additional symbol to make the errormessage more
   *       specific.
   *    on exit-
   *       the errormessage is printed on file stderr. If the calling module 
   *       can't continue its execution, the whole program ist aborted with
   *       exit-code 1 ( abort was set to value not equal zero).
   *    
   ***/


/******************************************************************************/
/************               MACRO-NAMES FOR MODULES               *************/
/******************************************************************************/

#define  CMRTOOL          1

#define  BUILD_COPA       2

#define  RD_ABSPRS        3

#define  COMARPRIVDEFS    4

#define  SCANSPECS        5

#define  SEMASPECS        6

#define  RD_ADT           7

#define  WRT_TABS         8

#define  OPT_TABS         9

#define  SEMASIM         10

#define  BUILDPRS        11

#define  OPTFUNC         12

#define  WRTFUNC         13

#define  ERRPROT         14

#define  OPTHELPFUNC     15

#define  WRTHELPFUNC     16

#define  WRT_CODES       17

#define  OPT_CODES       18

#define  WRTCHELPFUNC    19

#define  OPTCHELPFUNC    20

/******************************************************************************/
/************           MACRO-NAMES FOR ERROR-MESSAGES            *************/
/******************************************************************************/

#define  FILEERR	  1

#define  CTUSERERR        2

#define  BPOPTIONERR      3

#define  NDETERR	  4

#define  SHORTSIZEERR     5

#define  OUTOFRANGEERR1   6

#define  OUTOFRANGEERR2   7

#define  BADNODEERR       8

#define  PSTOVFLERR       9

#define  NOSYMSPACEERR   10

#define  SYTOOLONGERR    11

#define  TOKENLSTERR     12

#define  SPECERR         13

#define  NOMATCHSEMERR   14

#define  SEMMISMATCHERR  15

#define  LISTTOOBIGERR   16

#define  ENTRYTOOBIGERR  17

#define  NOSPACEERR      18

#define  NOSXCODEERR     19

#define  NEGSXCODEERR    20

#define  NOEOFERR        21

#define  NOMATCHNOSEMERR 22

#define  PAUSERERR       23

#define  SELECTERR       24

#define  OPTIONERR       25

#define  PRTUSERERR      26

#define  NOSTPRODERR     27

#define  BADNUM1ERR	 32

#define  BADNUM2ERR      33

#define  BADSEQERR       34

#define  DOUBLEAPAERR    37

#define  NOAPAERR	 38

#define  NOCMRERR        39

#define  CT1USERERR      40

#define NAMETOOLONG      41

#define BKEUSERERR       42

/******************************************************************************/
/*****************     MACRONAMES FOR WARNING-MESSAGES    *********************/
/******************************************************************************/

#define  SKIPWARN        28

#define  SEPAWARN        29

#define  BRACWARN        30

#define  STOPWARN        31

#define  TSHARWARN       35

#define  NSHARWARN       36

/******************************************************************************/
/*****************      MACROS TO DIRECT ERRORHANDLER     *********************/
/******************************************************************************/

#define  ABORT     	  1

#define  CONTINUE	  0

#define  DUMMY		 ""

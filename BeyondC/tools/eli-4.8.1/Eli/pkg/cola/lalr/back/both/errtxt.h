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
** $Id: errtxt.h,v 1.6 1997/08/29 08:38:08 mjung Exp $
*/

/******************************************************************************/
/* filename: errtxt.h                         first edit   :  29 . 6 . 89     */
/* author  : Christian Zeitel                 last change  :  21 . 9 . 90     */
/******************************************************************************/

/********************************* CONTENTS ************************************
 *									       *
 *  This datafile contains two vectors and two variables:	               *
 *   -module  : contains the modulenames of the errorreporting modules	       *
 *   -errtext : contains the errormessagetexts                                 *
 *   -manmn   : contains the highest codenumber for modules	               *
 *   -maxetn  : contains the highest codenumber for errortexts		       *
 *  									       *
 ******************************************************************************/

static short  maxmn  = 20,
  	      maxetn = 42;    



static char *module[]  =  
       { 
           "error",          /*  0  */ 
	   "cmrsasx",        /*  1  */
           "build_copa",     /*  2  */
	   "rd_absprs",      /*  3  */
	   "comarprivdefs",  /*  4  */
           "scanspecs",      /*  5  */
           "semaspecs",      /*  6  */
           "rd_adt",         /*  7  */
           "wrt_tabs",       /*  8  */
           "opt_tabs",       /*  9  */
	   "semasim",        /* 10  */
	   "BUILDPRS",       /* 11  */
	   "optfunc",        /* 12  */
	   "wrtfunc",        /* 13  */
	   "errprot",        /* 14  */
	   "opthelpfunc",    /* 15  */
	   "wrthelpfunc",    /* 16  */
	   "wrt_codes",      /* 17  */
	   "opt_codes",      /* 18  */
	   "wrtchelpfunc",   /* 19  */
	   "optchelpfunc"    /* 20  */
       };



static char *errtext[]  =
{
 "received wrong errormessage", 				      /*  0  */
 "can't open file ",                                                  /*  1  */
 "usage: cmrsasx <COMARFILE><SCANSPECFILE><SEMASPECFILE>",            /*  2  */
 "usage: BUILDPRS [options] <ABSPARSERFILE>",  	                      /*  3  */
 "grammar is not LALR(1)",   					      /*  4  */
 "unexpected size of C-datatype short",			              /*  5  */
 "internal symblistsize exceeded",     			              /*  6  */
 "internal deflistsize exceeded",				      /*  7  */
 "found bad COMAR unit-node",				              /*  8  */
 "prodstring overflow",  					      /*  9  */
 "can't allocate store for symbol",				      /* 10  */
 "symbol too long",						      /* 11  */
 "tokenlistsize exceeded",					      /* 12  */
 "bad scanner-specification",				              /* 13  */
 "no match with semantic symbol",				      /* 14  */
 "inconsistent semantic-information about symbol",		      /* 15  */
 "internal listsize exceeded",				              /* 16  */
 "too high entry-codenumber",				              /* 17  */
 "can't allocate store for vector",                                   /* 18  */
 "no sxcode found for symbol", 				              /* 19  */
 "found negative syntaxcode for symbol",			      /* 20  */
 "no EOF-symbol found ",					      /* 21  */
 "no match with not semantic symbol",		                      /* 22  */
 "usage : conprs <SOURCEFILE>",				              /* 23  */
 "don't know optimization-method",				      /* 24  */
 "unknown option :", 					              /* 25  */
 "usage: errprot <LISTFILE> <SOURCEFILE> <SPECFILE>",                 /* 26  */
 "no startproduction found ",      				      /* 27  */
 "skipsymbol has other error-recovery-properties",		      /* 28  */
 "separatorsymbol is semantic or has other error-recovery-properties",/* 29  */
 "bracketsymbol is semantic or has other error-recovery-properties",  /* 30  */
 "stopsymbol has other error-recovery-properties or is semantic",     /* 31  */ 
 "bad number for N-Table-option :",				      /* 32  */
 "bad number for T-Table-option :",				      /* 33  */
 "unknown letter for option -C :",				      /* 34  */
 "number for option -t set by default",			     	      /* 35  */
 "number for option -n set by default",				      /* 36  */
 "second name defined for abstract-parser-file :",		      /* 37  */
 "no name defined for abstract-parser-file",			      /* 38  */
 "no name defined for COMAR-file",				      /* 39  */ 
 "usage: cmrsasx <COMARFILE>",                                        /* 40  */
 "name for COMAR-input-file too long",                                /* 41  */
 "usage: backend_objectfile <COMARFILE><ABSPARSERFILE>[<OPTIONFILE>]" /* 42  */
};

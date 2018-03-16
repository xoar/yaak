/* $Id: option.h,v 1.8 1999/10/20 04:56:40 tony Exp $ */
/*##############################################################################

FUNNNELWEB COPYRIGHT
====================
FunnelWeb is a literate-programming macro preprocessor.

Copyright (C) 1992 Ross N. Williams.

   Ross N. Williams
   ross@spam.adelaide.edu.au
   16 Lerwick Avenue, Hazelwood Park 5066, Australia.

This program is free software; you can redistribute it and/or modify
it under the terms of Version 2 of the GNU General Public License as
published by the Free Software Foundation.

This program is distributed WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See Version 2 of the GNU General Public License for more details.

You should have received a copy of Version 2 of the GNU General Public
License along with this program. If not, you can FTP the license from
prep.ai.mit.edu/pub/gnu/COPYING-2 or write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

Section 2a of the license requires that all changes to this file be
recorded prominently in this file. Please record all changes here.

Programmers:
   RNW  Ross N. Williams  ross@spam.adelaide.edu.au
   AMS  Tony Sloane	  asloane@comp.mq.edu.au
   WMW	William M. Waite  William.Waite@Colorado.edu

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.
   22-Jul-1992  AMS  Added field of option structure for special output
                     format option.
   26-Jul-1992  AMS  Added RCS id.
   08-Aug-1997	WMW  Added a file name to the U option
		     Add non-product files
   03-May-1998	WMW  Add A option to specify header kinds

##############################################################################*/


/******************************************************************************/
/*                                  OPTION.H                                  */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_OPTION
#define DONE_OPTION

/******************************************************************************/

#include "style.h"

#include "machin.h"
#include "help.h"

/******************************************************************************/

/* THE B7 OPTION                                                              */
/* -------------                                                              */
/* When FunnelWeb was first ported to different machines and the regression   */
/* testing was activated, a most irritating occurance was the failure of the  */
/* results of tests on different machines to compare, because of minor        */
/* differences in implementation. For example, error messages that contained  */
/* file names would differ because the directory name on different machines   */
/* was different. Another example was error messages that quoted              */
/* implementation limits. This problem was solved by creating the B7 option   */
/* which instructs FunnelWeb to suppress all output that is                   */
/* non-deterministic, machine specific, or which in any other way would cause */
/* an unncessary failure of the test suite.                                   */

/* The following symbol provides a simple replacement for filenames in error  */
/* messages.                                                                  */
#define SUPPNAME "<<Suppressed>>"
#define SUPPVAL  "<<Suppressed>>"

/******************************************************************************/

/* The following structure stores all the information that can be             */
/* communicated in one or more command lines. An important aspect of the      */
/* structure is that it is totally self contained; it does not contain any    */
/* pointers to outside structures such as command lines.                      */
/* The rather strange field names are explained as follows:                   */
/*    1) Local names must be distinct to 8 characters (for portability).      */
/*    2) All structure field names should be unique (for portability).        */
/*       Some of the older compilers use a single field structure name space. */
/*    3) The op_ is used as a prefix for entities in this whole package.      */
/*    4) The next letter is the option letter itself. It is not intended that */
/*       the command line option names be tightly bound to the internal       */
/*       identifier names -- the command line names are just convenient.      */
/*    5) The next letter gives the type: [B]oolean, [S]tring, [I]nteger.      */

typedef struct
  {
   bool  op_a_b;  /* The meaning of @A (default). */
   fn_t  op_a_s;

   bool  op_f_b;  /* The input file. */
   fn_t  op_f_s;

   bool  op_j_b;  /* The journal file. */
   fn_t  op_j_s;

   fn_t  op_i_s;  /* Include file (default). */

   bool  op_n_b;  /* Non-product files (default). */
   fn_t  op_n_s;

   bool  op_o_b;  /* Product files (default). */
   fn_t  op_o_s;

   bool  op_t_b;  /* Typeset file (default). */
   fn_t  op_t_s;

   bool  op_l_b;  /* Listing file (default). */
   fn_t  op_l_s;

   bool  op_d_b;  /* Delete output files that have not changed? */

   uword op_c_i;  /* Lines of error context in listing file. */

   bool  op_q_b;  /* Quiet mode. Console chatter suppressed if turned on. */

   bool  op_s_b;  /* Send errors to the screen with specified context. */
   uword op_s_i;

   bool  op_w_b;  /* Set maximum line length of product files. */
   uword op_w_i;

   bool  op_x_b;  /* Execute specified file in FunnelWeb shell. */
   fn_t  op_x_s;

   bool  op_k_b;  /* Interactive (keyboard) mode. */

   bool	 op_u_b;  /* UNIX-style messages in listing. */
   fn_t  op_u_s;

                  /* Dump flags:            */
   bool  op_b1_b; /* Dump input file image. */
   bool  op_b2_b; /* Dump line list.        */
   bool  op_b3_b; /* Dump token list.       */
   bool  op_b4_b; /* Dump macro table.      */
   bool  op_b5_b; /* Dump document list.    */
   bool  op_b6_b; /* Dump time summary.     */
   bool  op_b7_b; /* Don't write anything non-deterministic or machine */
                  /*    specific. This option is designed to assist in */
                  /*    regression testing.                            */
   
   bool  op_h_b;  /* Help messages. */
   hn_t  op_h_s;
  } op_t;

typedef op_t *p_op_t;

/******************************************************************************/

EXPORT void op_ini P_((p_op_t));
/* Initializes the specified options structure with default values.           */
/* This includes ALL the fields of the structure. If, for example, the        */
/* default value of op_l_b is FALSE, op_l_s will be set to the empty string.  */

EXPORT bool op_add P_((p_op_t,p_cl_t,void (*)(char *)));
/* Parses the specified command line and places the information given in the  */
/* command line into specific fields of the options structure. The options    */
/* structure should be entirely defined upon entry, as this parsing function  */
/* only ADDS information present in the command line. Call op_ini if you      */
/* don't want to initialize all the fields manually.                          */
/* The comline string should start with the leading command (e.g. "fw").      */
/* However, he leading command is ignored.                                    */
/* Returns FALSE: One or more syntax errors have been detected. One or error  */
/*                messages have been written using the funtion argument.      */
/*                *p_op unchanged.                                            */
/* Returns TRUE : No syntax errors. Comline information placed in *p_op.      */

EXPORT void op_wri P_((p_op_t,void (*)(char *)));
/* Writes a text representation of the specified options record using the     */
/* function argument.                                                         */

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                              End of OPTION.H                               */
/******************************************************************************/


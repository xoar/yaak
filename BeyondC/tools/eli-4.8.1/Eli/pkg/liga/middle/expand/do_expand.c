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
/* $Id: do_expand.c,v 4.2 1997/08/29 09:09:06 peter Exp $ */
static char rcs_id[] = "$Id: do_expand.c,v 4.2 1997/08/29 09:09:06 peter Exp $";

/***********************************************************************\
*									*
*		Implementation of LIGA expand pass			*
*									*
*	Module:		expand.c					*
*	File:		expand.c					*
*	Contents:	main function of expand pass			*
*	Author:		Hans Detlef Siewert				*
*	Creation date:	12 Dec 1990					*
*	Last change:	23 Aug 1991					*
*									*
\***********************************************************************/

#include <stdio.h>

#include "LIGA.h"

#include "err.h"

#include "option_enums.h"
#include "option_types.h"
#include "opt_input.h"

#include "expconst.h"
#include "exp_types.h"
#include "expref.h"
#include "expidl.h"
#include "exp_io.h"
#include "expclass.h"
#include "exptransfer.h"
#include "expincl.h"
#include "expchain.h"
#include "expconstit.h"
#include "expand.h"
#include "middle_mem.h"

/* * GLOBAL VARIABLES */

char *CONST_ATTR;
int EXP_PROT;
int EXP_INCL;
char *INCL_ATTR;
int IDENT_INCL;
char *CHAIN_PRE_ATTR;
char *CHAIN_POST_ATTR;

char *NULL_FUNC;
char *CREAT_FUNC;
char *CONCAT_FUNC;

FILE *InputFile;
FILE *OutputFile;
FILE *ProtocolFile;
FILE *ExpOptFile;
FILE *OptOutFile;

/* * LOCAL FUNCTIONS */

/* * GLOBAL FUNCTIONS */

#ifdef __STDC__
void
deadly(char *msg)
#else
void
deadly(msg)
   char *msg;
#endif
/* print deadly error message and terminate program			 */
{
   curpos.line = 0;
   curpos.col = 0;
   message(DEADLY, msg, 0, &curpos);
}/* deadly() */

#ifdef __STDC__
void
fatal(char *msg)
#else
void
fatal(msg)
   char *msg;
#endif
/* print fatal error message to stderr					 */
{
   curpos.line = 0;
   curpos.col = 0;
   message(FATAL, msg, 0, &curpos);
}/* fatal() */

#ifdef __STDC__
void
print_err(int row, int col, char *str, int id)
#else
void
print_err(row, col, str, id)
   int row, col;
   char *str;
   int id;
#endif
/* print error message to stderr					 */
{
   curpos.line = row;
   curpos.col = col;
   message(ERROR, str, id, &curpos);
}/* print_err() */

#ifdef __STDC__
void
print_warn(int row, int col, char *str, int id)
#else
void
print_warn(row, col, str, id)
   int row, col;
   char *str;
   int id;
#endif
/* print warning							 */
{
   curpos.line = row;
   curpos.col = col;
   message(WARNING, str, id, &curpos);
}/* print_warn() */

#ifdef __STDC__
void
print_note(int row, int col, char *str)
#else
void
print_note(row, col, str)
   int row, col;
   char *str;
#endif
/* print notes to stderr						 */
{
   curpos.line = row;
   curpos.col = col;
   message(NOTE, str, 0, &curpos);
}/* print_note() */

#ifdef __STDC__
void
do_expand(AttrEval idlstruct, FILE * ctlfile)
#else
void
do_expand(idlstruct, ctlfile)
   AttrEval idlstruct;
   FILE *ctlfile;
#endif
{
   int tf;
   ExpOptFile = ctlfile;
   IdlStruct = idlstruct;

   /* print header for protocol */
   fprintf(ProtocolFile, "=============================\n");
   fprintf(ProtocolFile, "Protocol of liga phase expand\n");
   fprintf(ProtocolFile, "=============================\n");


   /* read files for option handling */
   expand_opts = (OptCollect) middle_Malloc(__FILE__, __LINE__, 
					    sizeof(struct _optcollect));
   expand_opts->exp_opts = (ExpList) NULL;
   OptionInput(expand_opts, ExpOptFile);
   (void) fclose(ExpOptFile);

   optim_opts = (OptCollect) middle_Malloc(__FILE__, __LINE__, 
					   sizeof(struct _optcollect));
   optim_opts->exp_opts = (ExpList) NULL;
   optim_opts->ord_opts = (OrdList) NULL;
   optim_opts->opt_opts = (OptList) NULL;
   optim_opts->be_opts = (BEList) NULL;

   /* evaluate expand-options */
   eval_exp_opt();

   /* initialize reference table */
   expand_init_ref_tab();

   /* search for the root symbol of this grammar */
   find_root();

   /* calculate classes from assignments */
   calc_classes();

   /* explode abbreviated transfer rules */
   tf = unabbrev_transfers();

   /* set classes of terminal attributes */
   set_term_classes();

   /* expand all TRANSFER rules if necessary */
   if (tf)
      tf = expand_transfers();
   if (tf)
   {
      (void) fprintf(ProtocolFile,
		     "\n*** ERROR  %d transfer(s) could not be expanded\n\n",
		     tf);
      print_err(0, 0, "TRANSFER(s) could not be expanded", TF_ERRID);
   }	/* if */
   check_classes();
   find_includings();
   expand_includings();
   find_chains();
   expand_chains();
   find_constits();
   expand_constits();

   /* write options for optim pass */
   OptionOut(optim_opts, OptOutFile);
   (void) fclose(OptOutFile);

   /* print trailer for protocol */
   if (ErrorCount[ERROR] || ErrorCount[WARNING])
   {
      (void) fprintf(ProtocolFile, "Expand failed: ");
      switch (ErrorCount[ERROR])
      {
      case 0:
	 (void) fprintf(ProtocolFile,
			"no errors, ");
	 break;
      case 1:
	 (void) fprintf(ProtocolFile, "one error, ");
	 break;
      default:
	 (void) fprintf(ProtocolFile,
			"%d errors, ", ErrorCount[ERROR]);
      }	/* switch */
      switch (ErrorCount[WARNING])
      {
      case 0:
	 (void) fprintf(ProtocolFile,
			"no warnings\n");
	 break;
      case 1:
	 (void) fprintf(ProtocolFile, "one warning\n");
	 break;
      default:
	 (void) fprintf(ProtocolFile,
			"%d warnings\n", ErrorCount[WARNING]);
      }	/* switch */
   }
   fprintf(ProtocolFile,"\n\n");
   expand_finl_ref_tab();
}


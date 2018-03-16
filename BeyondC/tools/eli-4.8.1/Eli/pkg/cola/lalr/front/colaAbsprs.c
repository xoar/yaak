/*
** $Id: colaAbsprs.c,v 1.9 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: colaAbsprs.c,v 1.9 1997/08/29 08:38:08 mjung Exp $";

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

/***************************************************************************/
/* File: cola_absprs.c	First Edit: 23.08.90	  Last Edit: 23.08.90      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 20.12.90	From: Karl-Josef Prott			   */
/***************************************************************************/


#include <stdio.h>
#include <string.h>

#include "comar.h"
#include "cmrlib.h"
#include "cmrio.h"
#include "privatlib.h"

#include "grammarcomp.h"
#include "first1.h"
#include "format.h"

#include "parserlib.h"
#include "prsiface.h"
#include "absparser.h"

/* global variable for COMAR-structure defined in "cmrlib.h" */
extern	p_comar	CMR;

#define	ERRMAIL(name,code)	priv_generrstr(code, name)

Boolean	prt_first = FALSE,	/* Printing first sets ? */
	free_pos = FALSE,	/* Computing free positions ? */
	prt_gram = FALSE;	/* Printing grammar ? */

short	options = 64;	/* value for printing abstract parser */
				/* see absparser.h */

/* Maximun line length in optionfile */
#define	OPTIONSIZ	50


String	TakeOptions(argc,argv)
int	argc;
String	argv[];
{
  FILE	*input;
  char	option[OPTIONSIZ];
  String	str;

   if (argc != 3) {
      (void)fprintf(stderr, "Usage %s optionfile comarfile.\n", argv[0]);
      exit(1);
   }

  if ((input = fopen(argv[1], "r")) == NULL)
  {
    (void)fprintf(stderr, "Could not open optionfile %s.\n", argv[1]);
    exit(1);
  }

   while (fgets(option, OPTIONSIZ, input) != NULL)
    if ( option[0] != '\n' )
      {
	str = option;
	/* Skip over spaces and tabulators */
	while (*str == ' ' || *str == '\t') str++;

	/* frontend options */
	if ( strncmp(str,"ALL_STATES", 10) == 0	)
		options += 32;
	else if ( strncmp(str,"FREE_POS", 8) == 0 )
		free_pos = TRUE;
	else if ( strncmp(str,"PRT_GRAM", 8) == 0 )
		prt_gram = TRUE;
	else if ( strncmp(str,"PRT_FIRST", 9) == 0 )
		prt_first = TRUE;
      }

  return(argv[2]);
}

int main(argc, argv)
int argc;
char *argv[];
{
  String	cmrfile, file;		/* name of COMAR file */
  char		tool_info[MAX_TOOL_INFO];
  short		stat;
  FILE		*f;

  /* Scanning of all options - result stored in global variables */
  cmrfile = TakeOptions(argc,argv);


  /* input of the COMAR-data-structure */
  if ((stat = cmrlib_read(cmrfile, tool_info, &CMR)) != CMR_SUCCESS)
    {
      priv_generrstr(stat, cmrfile);
      exit(1);
    }


  /* Computing the first-sets. */
  if ( prt_first )
	file = cmrfile; 		/* printing first sets */
  else
	file = "";			/* not printing first sets */
  if ( (stat = cmrtl_first(CMR,file,FIR_AND_DEF)) !=  CMR_SUCCESS )
    {
      ERRMAIL("cmrtl_first()", stat);
      exit(1);
    }

  /* Check startproduction, proof as a reduced grammar and
   * compute a partial order on the productions.
   */
  if ( (stat = cmrtl_grammar_comp(CMR, FALSE, TRUE, TRUE)) !=  CMR_SUCCESS )
    {
      ERRMAIL("cmrtl_grammar_comp()", stat);
      exit(1);
    }


  /* Computing the abstract parser and the free positions (if free_pos). */
  if ( (stat=cmrtl_compute_absparser(CMR, cmrfile, options, free_pos))
        !=  CMR_SUCCESS )
    {
      if ( stat != ISNOTLALR1)
	{
          ERRMAIL("cmrtl_compute_absparser()", stat);
	  exit(1);
	}
    }


  /* Output of the COMAR datastructure */
  file = priv_genfilename(cmrfile, ".abs1");
  if ( (stat = cmrlib_write(file, ".abs1", CMR)) != CMR_SUCCESS )
      {
	priv_generrstr(stat, file);
        exit(1);
      }
  /* end of all if */

  /* Output of the resulting grammar in PGS notation. */
  if ( prt_gram )
    {
      file = priv_genfilename(cmrfile, ".fmt");
      if ( (f = fopen(file, "w")) == (FILE *)NULL )
        {
 	  priv_generrstr(CMR_OPNERR, file );
          exit(1);
        }
      print_grammar(CMR,f);
      (void)fclose(f);
    }  /* end of if */

#ifdef STATISTIK
{
#include "statistik.h"
statistPrintResult("STATISTIK");
}
#endif
  exit(0);
}



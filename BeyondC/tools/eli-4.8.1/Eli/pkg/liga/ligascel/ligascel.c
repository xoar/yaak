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
/* $Id: ligascel.c,v 4.1 1997/08/29 09:02:13 peter Exp $ */
/* $Log: ligascel.c,v $
 * Revision 4.1  1997/08/29 09:02:13  peter
 * GPL
 *
 * Revision 4.0  1995/08/24 13:14:45  cogito
 * *** empty log message ***
 *
 * Revision 4.0  1995/08/24  13:01:07  cogito
 * *** empty log message ***
 *
 * Revision 4.0  1995/08/24  13:00:23  cogito
 * *** empty log message ***
 *
 * Revision 1.1  1995/08/24  12:29:48  cogito
 * Initial revision
 *
 * Revision 1.1  1991/09/11  10:02:09  cogito
 * Initial revision
 *
 * Revision 1.1  91/07/12  15:49:53  tony
 * Initial revision
 *  */
static char rcs_id[]= "$Id: ligascel.c,v 4.1 1997/08/29 09:02:13 peter Exp $";

/***********************************************************************\
*									*
*		Implementation of a LIGA pass				*
*		    -- sample sceleton --				*
*									*
*	Module:		ligascel.c					*
*	File:		ligascel.c					*
*	Contents:	main function of sceleton pass			*
*	Author:		<insert name>					*
*	Creation date:	?? ??? 199?					*
*	Last change:	?? ??? 199?					*
*									*
\***********************************************************************/

#include <stdio.h>

#include "LIGA.h"

#include "err.h"

#include "option_enums.h"
#include "option_types.h"
#include "opt_input.h"

#include "ligascel.h"

/*
** GLOBAL VARIABLES
*/

AttrEval IdlStruct;

OptCollect scel_opts;

FILE	*InputFile;
FILE	*OutputFile;
FILE	*ProtocolFile;
FILE	*OptFile;

/*
** LOCAL VARIABLES
*/

char	*InputFName;
char	*OutputFName;
char	*ProtocolFName;
char	*OptFName;

/*
** LOCAL FUNCTIONS
*/

#ifdef __STDC__
void usage (char *progname)
#else
void usage (progname)
char *progname;
#endif
/* tell users how to use this program					*/
{
	(void) printf ("usage: %s [-i in][-o out][-p prot][-c ctl]\n",
		progname);
	exit (1);
} /* usage() */


/*
** GLOBAL FUNCTIONS
*/

#ifdef __STDC__
void deadly (char *msg)
#else
void deadly (msg)
char *msg;
#endif
/* print deadly error message and terminate program			*/
{
	curpos.line= 0;
	curpos.col= 0;
	message (DEADLY, msg, 0, &curpos);
} /* deadly() */

#ifdef __STDC__
int main (int argc, char *argv[])
#else
int main (argc, argv)
int argc;
char *argv[];
#endif
/* main program of expand module					*/
{
	char *progname;

	InputFName= "in";
	OutputFName= "out";
	ProtocolFName= "proto";
	OptFName= "option";

	progname= *argv;
	argv++;

	/* evaluate arguments */
	for ( ; argc>1; argc--, argv++)
	{
		if ((*argv)[0] == '-')
		{
		  switch ((*argv)[1])
		  {
			case 'i':
				argv++;
				argc--;
				InputFName= *argv;
				break;
			case 'o':
				argv++;
				argc--;
				OutputFName= *argv;
				break;
			case 'p':
				argv++;
				argc--;
				ProtocolFName= *argv;
				break;
			case 'c':
				argv++;
				argc--;
				OptFName= *argv;
				break;
			default:
				usage (progname);
				break;
		  } /* switch */
		}
		else
			usage (progname);
	} /* for */

	/* open input file */
	InputFile= fopen (InputFName, "r");
	if (!InputFile)
		deadly ("Can't read input file\n");

	/* open output file */
	OutputFile= fopen (OutputFName, "w");
	if (!OutputFile)
		deadly ("Can't create output file\n");

	/* open protocol file */
	ProtocolFile= fopen (ProtocolFName, "w");
	if (!ProtocolFile)
		deadly ("Can't create protocol file\n");

	/* open expand option file */
	OptFile= fopen (OptFName, "r");
	if (!OptFile)
		deadly ("Can't read option file\n");

	/* print header for protocol */
	(void) fprintf (ProtocolFile, "\n-------------------------------------");
	(void) fprintf (ProtocolFile, "-----------------------------------------\n");
	(void) fprintf (ProtocolFile, "\tPROTOCOL OF THE LIGA PASS ???\n");
	(void) fprintf (ProtocolFile, "-------------------------------------");
	(void) fprintf (ProtocolFile, "-----------------------------------------\n\n");

	/* read files for option handling */
	scel_opts= (OptCollect) malloc (sizeof (struct _optcollect));
	OptionInput (scel_opts, OptFile);
	(void) fclose (OptFile);

	/* read input file */
	IdlStruct= ligain (InputFile);

	/* close input file */
	(void) fclose (InputFile);

	/* perform any action */

	/* write output file */
	ligaout (OutputFile, IdlStruct);
	/* close output file */
	(void) fclose (OutputFile);

	/* print trailer for protocol */
	(void) fprintf (ProtocolFile, "\n\n-------------------------------------");
	(void) fprintf (ProtocolFile, "-----------------------------------------\n");
	(void) fprintf (ProtocolFile, "\t??? ");
	if (!ErrorCount[ERROR] && ! ErrorCount[WARNING])
	{
		(void) fprintf (ProtocolFile,
			"SUCCESSFULLY TERMINATED\n");
	} /* if */
	else
	{
	    (void) fprintf (ProtocolFile, "FAILED: ");
	    switch (ErrorCount[ERROR])
	    {
		case 0:
			(void) fprintf (ProtocolFile,
				"no ERROR messages, ");
			break;
		case 1:
			(void) fprintf (ProtocolFile, "one ERROR message, ");
			break;
		default:
			(void) fprintf (ProtocolFile,
				"%d ERROR messages, ", ErrorCount[ERROR]);
	    } /* switch */
	    switch (ErrorCount[WARNING])
	    {
		case 0:
			(void) fprintf (ProtocolFile,
				"no warnings\n");
			break;
		case 1:
			(void) fprintf (ProtocolFile, "one warning\n");
			break;
		default:
			(void) fprintf (ProtocolFile,
				"%d warnings\n", ErrorCount[WARNING]);
	    } /* switch */
	} /* else */
	(void) fprintf (ProtocolFile, "--------------------------------------");
	(void) fprintf (ProtocolFile, "----------------------------------------\n\n");
	/* close protocol file */
	(void) fclose (ProtocolFile);

	/* successful termination */
	return (ErrorCount[ERROR] || ErrorCount[WARNING]);
} /* main() */

/***********************\
* end of ligascel.c	*
\***********************/


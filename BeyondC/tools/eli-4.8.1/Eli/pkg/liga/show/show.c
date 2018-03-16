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
/***********************************************************************\
*									*
*		Implementation of a LIGA pass				*
*		    -- Interface Analyzer --				*
*									*
*	Module:		Show    					*
*	File:		show.c						*
*	Contents:	main function of sceleton pass			*
*	Author:		U. Kastens					*
*	Creation date:	26 Nov 1991					*
*	Last change:	28 Nov 1991					*
*									*
\***********************************************************************/

static char rcs_id[] = "$Id: show.c,v 4.3 1998/04/28 14:30:00 ludi Exp $";

#include <stdio.h>

#include "LIGA.h"
#include "showproc.h"
#include "map_errors.h"
#include "ptg_gen.h"

/*
 * * GLOBAL VARIABLES
 */

AttrEval IdlStruct;

FILE *InputFile;
FILE *ErrMapFile;
/*
 * * LOCAL VARIABLES
 */

char *InputFName;
char *ErrMapFName;

/*
 * * LOCAL FUNCTIONS
 */

#ifdef __STDC__
void
usage(char *progname)
#else
void
usage(progname)
   char *progname;
#endif
/* tell users how to use this program					 */
{
   (void) printf("usage: %s -i infile -e errmapfile\n",
		 progname);
   exit(1);
}/* usage() */


/*
 * * GLOBAL FUNCTIONS
 */

#ifdef __STDC__
int
main(int argc, char *argv[])
#else
int
main(argc, argv)
   int argc;
   char *argv[];
#endif
/* main program of expand module					 */
{
   char *progname;

   InputFName = "in";
   ErrMapFName = "errmap";
   progname = *argv;
   argv++;

   /* evaluate arguments */
   for (; argc > 1; argc--, argv++)
   {
      if ((*argv)[0] == '-')
      {
	 switch ((*argv)[1])
	 {
	 case 'i':
	    argv++;
	    argc--;
	    InputFName = *argv;
	    break;
	 case 'e':
	    argv++;
	    argc--;
	    ErrMapFName = *argv;
	    break;
	 default:
	    usage(progname);
	    break;
	 }	/* switch */
      } else
	 usage(progname);
   }	/* for */


   /* open ErrMapFile */
   ErrMapFile = fopen(ErrMapFName, "r");
   if (!ErrMapFile)
   {
      fprintf(stderr, "Can't read input file %s\n", ErrMapFName);
      exit(0);
   }
   ErrTabInit(ErrMapFile);

   /* open input file */
   InputFile = fopen(InputFName, "r");
   if (!InputFile)
   {
      fprintf(stderr, "Can't read input file %s\n", InputFName);
      exit(0);
   }
   /* read input file */
   IdlStruct = ligain(InputFile);

   /* close input file */
   (void) fclose(InputFile);

   /* perform any action */

   PAttrEval(IdlStruct);

   return (0);
}/* main() */

/***********************\
* end of ligascel.c	*
\***********************/

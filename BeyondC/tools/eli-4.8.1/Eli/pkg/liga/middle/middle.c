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
/* $Id: middle.c,v 4.3 1997/08/29 09:07:44 peter Exp $ */

/***********************************************************************\
*		           LIGA Middle End     		                *
*             liga phases expand, order and optim	                *
\***********************************************************************/

#include <stdio.h>
#include "LIGA.h"
#include "err.h"
#include "middle_mem.h"
#include "linemap.h"

/* for input/output */
#include "expand.h" 
    /* expand provides 
       FILE *InputFile;
       FILE *OutputFile;
       FILE *ProtocolFile;
       FILE *ExpOptFile;
       FILE *OrdOptFile;
       FILE *OptOutFile;
    */

FILE *optim_optionfile1;
FILE *optim_optionfile2;
FILE *linemapFile;
static int expandonly = 0;          /* run only the expand phase */
                                    /* option is switched on by "-g" */
/* for expand: */
#include "do_expand.h"

/* for order: */
#include "do_order.h"

/* for optim: */
#include "do_optim.h"

/* usage message: */
static
#if defined(__STDC__) || defined(__cplusplus)
void
usage(char *progname)
#else
void
usage(progname)
   char *progname;
#endif
/* tell users how to start this program	 */
{
   printf("usage: %s -i in -o out -p prot -c expopt -d ordopt -e optopt1 optopt2 [-g] -t optctl -b buprod \n",
	  progname);
   exit(1);
}/* usage() */

#if defined(__STDC__) || defined(__cplusplus)
static void 
middle_deadly(char *msg)
#else
static void 
middle_deadly(msg)
   char *msg;
#endif
/* print deadly error message and terminate program                      */
{
   curpos.line = 0;
   curpos.col = 0;
   message(DEADLY, msg, 0, &curpos);
}/* middle_deadly() */


#if defined(__STDC__) || defined(__cplusplus)
void
do_commandline(int argc, char *argv[])
#else
void
do_commandline(argc, argv)
   int argc;
   char *argv[];
#endif
{
   char *InputFName = "input_filename";
   char *OutputFName = "output_filename";
   char *ProtocolFName = "protocol_filename";
   char *linemapFName = "linemap_filename";
   char *ExpOptFName = "ExpOpt_filename";
   char *OrdOptFName = "OrdOpt_filename";
   char *OptOutFName = "OptOut_filename";
   char *OptOpt1FName = "OptOpt1_filename";
   char *BuProdFName = "BuProd_filename";
   char *OptOpt2FName = "OptOpt2_filename";
   char *progname = *argv;
   argv++;
   /* evaluate arguments */
   for (; argc > 1; argc--, argv++) {
      if ((*argv)[0] == '-') {
	 switch ((*argv)[1]) {
	 case 'i':
	    argv++;
	    argc--;
	    InputFName = *argv;
	    break;
	 case 'o':
	    argv++;
	    argc--;
	    OutputFName = *argv;
	    break;
	 case 'p':
	    argv++;
	    argc--;
	    ProtocolFName = *argv;
	    break;
	 case 'l':
	    argv++;
	    argc--;
	    linemapFName = *argv;
	    break;
	 case 'c':
	    argv++;
	    argc--;
	    ExpOptFName = *argv;
	    break;
	 case 'd':
	    argv++;
	    argc--;
	    OrdOptFName = *argv;
	    break;
	 case 'e':
	    argv++;
	    argc--;
	    OptOpt1FName = *argv;
	    argv++;
	    argc--;
	    OptOpt2FName = *argv;
	    break;
	 case 'g':
	    expandonly=1;
	    break;
	 case 't':
	    argv++;
	    argc--;
	    OptOutFName = *argv;
	    break;
	 case 'b':
	    argv++;
	    argc--;
	    BuProdFName = *argv;
	    break;
	 default:
	    usage(progname);
	    break;
	 }	/* switch */
      } else
	 usage(progname);
   }	/* for */

   /* open input file */
   InputFile = fopen(InputFName, "r");
   if (!InputFile)
      middle_deadly("Can't read input file\n");

   /* open output file */
   OutputFile = fopen(OutputFName, "w");
   if (!OutputFile)
      middle_deadly("Can't create output file\n");

   /* open protocol file */
   ProtocolFile = fopen(ProtocolFName, "w");
   if (!ProtocolFile)
      middle_deadly("Can't create protocol file\n");

   /* open linemap file */
   linemapFile = fopen(linemapFName, "r");
   if (!ProtocolFile)
      middle_deadly("Can't open linemap file\n");

   /* open expand option file */
   ExpOptFile = fopen(ExpOptFName, "r");
   if (!ExpOptFile)
      middle_deadly("Can't read option file\n");

   /* open optim option file for writing */
   OptOutFile = fopen(OptOutFName, "w");
   if (!OptOutFile)
      middle_deadly("Can't write option file\n");

   /* open order option file for reading */
   OrdOptFile = fopen(OrdOptFName, "r");
   if (!OrdOptFile)
      middle_deadly("Can't read order option file\n");

   /* open optim option file 1 for reading */
   optim_optionfile1 = fopen(OptOpt1FName, "r");
   if (!optim_optionfile1)
      middle_deadly("Can't read optim option file 1\n");

   /* open optim option file 1 for reading */
   optim_optionfile2 = fopen(OptOpt2FName, "r");
   if (!optim_optionfile2)
      middle_deadly("Can't read optim option file 2\n");

   /* open bottomup productions file */
   BuProdFile = fopen(BuProdFName, "w");
   if (!BuProdFile)
      middle_deadly("Can't create bottomup productions file\n");
}

/* main program: */

#if defined(__STDC__) || defined(__cplusplus)
int
main(int argc, char *argv[])
#else
int
main(argc, argv)
   int argc;
   char *argv[];
#endif
{
    AttrEval IdlStruct;
    /* initialize memory allocation */
    init_middle_mem();

    do_commandline(argc, argv);

    /* read input file */
    IdlStruct = ligain(InputFile);
    if (!IdlStruct)
	middle_deadly("IDL input file is empty\n");

    /* close input file */
    (void) fclose(InputFile);

    build_linemap(linemapFile);

    do_expand(IdlStruct, ExpOptFile);
    /* stop after expand if "expandonly" is set or there were errors */
    if (expandonly || ErrorCount[ERROR]) {
	ligaout(OutputFile, IdlStruct);
	exit(1);
    }
    finish_middle_mem();   /* free memory used temporarily for expand */

    do_order(IdlStruct, OrdOptFile);
    if (ErrorCount[ERROR]) {
	ligaout(OutputFile, IdlStruct);
	exit(1);
    }
    finish_middle_mem();   /* free memory used temporarily for order */

    do_optim(IdlStruct, optim_optionfile1, optim_optionfile2);

    ligaout(OutputFile, IdlStruct);
    finish_middle_mem();   /* free memory used temporarily for optim*/
    return 0;
}/* main() */

static char RCSid[] = "$Id: machin.c,v 1.9 1999/10/20 04:56:26 tony Exp $";
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

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.
   26-Jul-1992  AMS  Added RCS id.
   20-Nov-1992  AMS  Avoid problems where file name being split has a .
                     in it in the path portion.  It shouldn't be
		     recognised as the start of the extension.
   17-Mar-1993  AMS  Export fn_split for use by weaveinfo.c.

##############################################################################*/


/******************************************************************************/
/*                                    MACHIN.C                                */
/******************************************************************************/
/*                                                                            */
/* WARNING: DO NOT ADD ANY PROGRAM DEPENDENT DEFINITIONS.                     */
/*                                                                            */
/* This file contains machine-dependent, program-independent stuff that       */
/* implements the functionality promised in MACHIN.H.                         */
/*                                                                            */
/* Note: As usual, the full definitions of functions in the .H file are not   */
/*       repeated here.                                                       */
/*                                                                            */
/******************************************************************************/

#include <time.h>
#include "style.h"

#include "as.h"
#include "machin.h"

/* The Macintosh's doesn't have a command language, and so we have to prompt  */
/* for a command line. This requires a special package.                       */
#if MAC
#include <console.h>
#endif

/* Under VMS, we need RMS to get at stuff to do with filenames.               */
#if VMS
#include RMS
#endif

/******************************************************************************/
/*                           LOCAL FUNCTIONS                                  */
/******************************************************************************/

LOCAL void mconcat P_((int,char **,char *));
LOCAL void mconcat(argc,argv,result)
/* Given argc and argv, as passed to main(), this function appends all the    */
/* arguments together (separated by spaces) into the string "result".         */
/* This function assists in reconstructing the command line.                  */
/* This function is actually portable, so you shouldn't have to change it.    */
/* Note: "mconcat" stands for Multiple CONCATenation.                         */
int    argc;
char **argv;
char *result;
{
 uword i;
 strcpy(&result[0],argv[0]);
 for (i=1;i<argc;i++)
   {
    strcat(&result[0]," "    );
    strcat(&result[0],argv[i]);
   }
}

/******************************************************************************/

#if MAC | SUN | PC
EXPORT void fn_split(p_fn,p_path,p_name,p_ext)
/* Accepts a filename in p_fn and writes the path, name, and extension        */
/* components of the filename to the strings p_path, p_name, and p_ext.       */
p_fn_t p_fn;
p_fn_t p_path;
p_fn_t p_name;
p_fn_t p_ext;
{
 char *p,*q;

 /* Make sure that the input filename is a sensible length. */
#if defined(__cplusplus) || defined(__STDC__)
 as_cold(strlen(p_fn)<=(size_t)FILENAME_MAX,"fn_split: Filename is too long.");
#else
 as_cold(strlen(p_fn)<=FILENAME_MAX,"fn_split: Filename is too long.");
#endif

 /* Extract the path from the input string by searching for the last */
 /* occurrance of the special character used for directories.        */

 /* Find the last directory/filename separator. */
 p=strrchr(p_fn,FN_DELIM);
 if (p==NULL)
   {strcpy(p_path,""); p=p_fn;}
 else
   {
    memcpy(p_path,p_fn,(size_t) (p-p_fn+1));
    p_path[(size_t) (p-p_fn+1)]=EOS;
    p++;
   }

 /* Assert: p now points to the first character of the name field. */

 /* Now locate the file extension. */
 q=strrchr(p_fn,'.');
 if ((q==NULL) || (q < p))
   {strcpy(p_ext,""); q = &p_fn[strlen(p_fn)];}
 else
   {strcpy(p_ext,q);}

 /* Assert: q now points to the '.' preceding the extension field. */

 /* Now anything between p and q must be the filename proper. */
 for (;p<q;p++)
    *p_name++ = *p;
 *p_name=EOS;
}
#endif

/******************************************************************************/

#if MAC | SUN | PC
LOCAL void fn_join P_((p_fn_t,p_fn_t,p_fn_t,p_fn_t));
LOCAL void fn_join(p_fn,p_path,p_name,p_ext)
/* This function sets p_fn to the empty string and then successively appends  */
/* p_path, p_name, and p_ext. Before doing this, it checks to make sure that  */
/* there will be enough room and bombs the program if there isn't.            */
p_fn_t p_fn;
p_fn_t p_path;
p_fn_t p_name;
p_fn_t p_ext;
{
#if defined(__cplusplus) || defined(__STDC__)
 as_cold(strlen(p_path)+strlen(p_name)+strlen(p_ext) <= (size_t)FILENAME_MAX,
         "fn_join: Constructed filename is too long.");
#else
 as_cold(strlen(p_path)+strlen(p_name)+strlen(p_ext) <= FILENAME_MAX,
         "fn_join: Constructed filename is too long.");
#endif
 strcpy(p_fn,p_path);
 strcat(p_fn,p_name);
 strcat(p_fn,p_ext);
}
#endif

/******************************************************************************/
/*                              EXPORTED FUNCTIONS                            */
/******************************************************************************/

#if MAC | SUN | PC
EXPORT void fn_ins(p_cur,p_add)
p_fn_t p_cur;
p_fn_t p_add;
{
 fn_t cur_path, add_path;
 fn_t cur_name, add_name;
 fn_t cur_extn, add_extn;

 /* Split the argument file names into their component parts. */
 fn_split(p_cur,cur_path,cur_name,cur_extn);
 fn_split(p_add,add_path,add_name,add_extn);

 /* Perform the inheriting on a field by field basis. */
#if defined(__cplusplus) || defined(__STDC__)
 if (strlen(add_path) > (size_t)0) strcpy(cur_path,add_path);
 if (strlen(add_name) > (size_t)0) strcpy(cur_name,add_name);
 if (strlen(add_extn) > (size_t)0) strcpy(cur_extn,add_extn);
#else
 if (strlen(add_path) > 0) strcpy(cur_path,add_path);
 if (strlen(add_name) > 0) strcpy(cur_name,add_name);
 if (strlen(add_extn) > 0) strcpy(cur_extn,add_extn);
#endif

 /* Put the fields back together again to yield the final result. */
 fn_join(p_cur,cur_path,cur_name,cur_extn);
}
#endif

#if VMS
EXPORT void fn_ins(p_cur,p_add)
/* This VMS version of fn_ins was written with the assistance of:             */
/*    Jeremy Begg (jeremy@vsm.com.au) of VSM Software Services. Thanks!       */
/* The VMS version is messy because VMS has highly structured filenames and   */
/* highly ingrained rituals for manipulating them.                            */
p_fn_t p_cur;
p_fn_t p_add;
{
 struct FAB cur_fab;   /* FAB    for SYS$PARSE */
 struct NAM cur_nam;   /* NAM    for SYS$PARSE */
 fn_t expanded;        /* Result of  SYS$PARSE */
 long rms_status;      /* Status of  SYS$PARSE */

 /*
 printf("\nTRACE: Call of fn_ins(...).\n");
 printf("   Current spec = \"%s\".\n",p_cur);
 printf("   Add     spec = \"%s\".\n",p_add);
 */

 /* Initialize the FAB and NAM block to something sensible. */
 cur_fab = cc$rms_fab;
 cur_nam = cc$rms_nam;

 /* (fna,fns) is address and size of input file spec in FAB block. */
 cur_fab.fab$l_fna = p_add;
 cur_fab.fab$b_fns = strlen(p_add);

 /* (dna,dns) is address and size of default file spec in FAB block. */
 cur_fab.fab$l_dna = p_cur;
 cur_fab.fab$b_dns = strlen(p_cur);

 /* Connect the NAM block to the FAB block. */
 cur_fab.fab$l_nam = &cur_nam;

 /* Point the NAM block's target name fields to the target namechar array. */
 cur_nam.nam$l_esa = &expanded;
 cur_nam.nam$b_ess = FILENAME_MAX;  /* Reserve last char for NULL terminator */

 /* PWD => put the password from a DECnet Access Control String in the filespec
  * SYNCHK => check syntax only, don't search for the file on disk
  */
 cur_nam.nam$b_nop = NAM$M_PWD + NAM$M_SYNCHK;

 /* Perform the parse. */
 rms_status = sys$parse(&cur_fab);
 if (rms_status & 1)
   {
    expanded[cur_nam.nam$b_esl]=EOS; /* Terminate VMS string. */
    strcpy(p_cur,expanded);
   }
 else
   {
    printf("Note: RMS parse failed. Could be a syntax error, could be a bug!\n");
   }

 /* TRACE printf("   Result  spec = \"%s\".",p_cur); */
}
#endif

/******************************************************************************/

EXPORT void getcline(argc,argv,p_comline)
/* Given, argc and argv, writes a command line string in p_comline.           */
/* See machin.h for a thorough definition of this function.                   */
int   argc;
char **argv;
char *p_comline;
{
 int    argc2;
 char **argv2;

#if MAC
 /* On the Macintosh there is no command language and therefore no command    */
 /* line. Therefore we cannot trust the argc and argv handed to us by main()  */
 /* and have to obtain a command line from other sources.                     */
 /* The "ccommand" function comes from <console.h> of the THINK C libraries.  */
 argc2=ccommand(&argv2);
#endif

/* The other systems work like Unix. */
#if SUN | VMS | PC
argc2=argc;
argv2=argv;
#endif

 /* The command line is currently in pieces. Reassemble it. That's all!       */
 mconcat(argc2,argv2,p_comline);
}

/******************************************************************************/

EXPORT float tim_real()
{
 STAVAR bool   init=FALSE;
 STAVAR time_t base;

 /* The first time this routine is called, we establish a base real time      */
 /* from which real time differences are calculated. There are two reasons    */
 /* for doing this. The first is that difftime seems to be the only way to    */
 /* get ANSI C to hand over a calibrated arithmetic type holding the real     */
 /* time. The second is that we don't want to have to deal with large         */
 /* absolute times anyway.                                                    */
 if (!init)
   {
    /* Returns -1 if the time is not available (ANSI 7.12.2.4). */
    base=time(NULL);
    init=TRUE;
   }

 /* Return the elapsed time since the base time. */

/* Macintosh, VMS, and PC have difftime. */
#if MAC | VMS | PC
 if (base == -1)
    return 0.0;
 else
    return (float) difftime(time(NULL),base);
#endif

/* Sun does not have difftime. */
#if SUN
 return 0.0;
#endif

/* The timing functions are only used to generate performance statistics and  */
/* are not critical to FunnelWeb. There is not much harm in returning 0.0.    */
}

/******************************************************************************/

EXPORT float tim_cpu()
{
 clock_t t=clock();

/* Make sure that we have a definition for CLOCKS_PER_SEC. */
#ifndef CLOCKS_PER_SEC
#ifdef CLK_TCK
#define CLOCKS_PER_SEC CLK_TCK
#else
/* Assume one million ticks per second. */
#define CLOCKS_PER_SEC (1000000L)
#endif
#endif

 /* The clock() function returns -1 if the CPU time is not available. */
 /* Otherwise it returns the number of "clocks" since power-up.       */
 if (t == -1)
    return 0.0;
 else
    return ((float) t) / ((float) CLOCKS_PER_SEC);
}

/******************************************************************************/
/*                              End of MACHIN.C                               */
/******************************************************************************/

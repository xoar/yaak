static char RCSid[] = "$Id: command.c,v 1.16 2013/11/09 21:05:52 profw Exp $";
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
   BK   Basim Kadhim	  kadhim@cs.colorado.edu
   WMW	William M. Waite  William.Waite@Colorado.edu

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.
   22-Jul-1992  AMS  Check for option +U to output listing in special format.
   26-Jul-1992  AMS  Added support for mapping file.
   26-Jul-1992  AMS  Added RCS id.
   03-Aug-1992  AMS  Select weave function based on typesetter selection.
   12-Mar-1993  BK   Undef ARG_MAX to avoid redefinition on Linux systems.
   08-Jul-1993  BK   Make cast explicit.
   20-Nov-1995	WMW  Add typesetter HTML
   06-Aug-1997	WMW  Add non-product files
   01-May-1998	WMW  Add typesetters LATEX and LATEX2HTML
   09-Nov-2013	WMW  Corrections for a finicky C compiler

##############################################################################*/


/******************************************************************************/
/*                                COMMAND.C                                   */
/******************************************************************************/

#include <ctype.h>
#include "style.h"

#include "analyse.h"
#include "as.h"
#include "command.h"
#include "data.h"
#include "dump.h"
#include "lister.h"
#include "memory.h"
#include "mapper.h"
#include "misc.h"
#include "option.h"
#include "parser.h"
#include "scanner.h"
#include "tangle.h"
#include "weave.h"
#include "weaveinfo.h"
#include "weavehtml.h"
#include "weavel2ht.h"

/******************************************************************************/

/* Because FunnelWeb has so many options ,it is convenient to allow the user  */
/* to construct a startup file. This is its name.                             */
#define INITFILE "fwinit.fws"

/******************************************************************************/

/* Three variables hold options information in FunnelWeb.                     */
/* 'p_comopt' holds the options conveyed by the original raw command line.      */
/* 'p_defopt' holds the options that are default in the FunnelWeb shell.        */
/* 'option' is global and holds the options that have been specified for the  */
/*          current invocation of FunnelWeb proper.                           */
/* 'option' is global so here we see only 'p_comopt' and 'p_defopt'.              */
LOCVAR op_t *p_comopt;  /* Initial command line options.                         */
LOCVAR op_t *p_defopt;  /* Default shell options.                                */

/* The FunnelWeb shell interpreter has many different commands and it is      */
/* worth them sharing the same basic command line scanner. These two          */
/* variables hold the numer of arguments and a pointer to strings holding     */
/* copies of each argument.                                                   */
/* Note: The first argument is placed in arr_arg[0].                          */
#undef ARG_MAX
#define ARG_MAX 5
LOCVAR uword arg_num;
LOCVAR char *arg_arr[ARG_MAX+1]; /* Is this +1 necessary? */

/* The FunnelWeb command interpreter allows 10 substitution strings.          */
/* These strings are stored in the following array.                           */
#define NUM_SUBS (10+26)        /* 0..9 and A..Z */
LOCVAR char *subval[NUM_SUBS];

LOCVAR ulong old_war;
LOCVAR ulong old_err;
LOCVAR ulong old_sev;

/* The FunnelWeb script interpreter can echo (trace) each command before it   */
/* executes it. Whether it does is determined by this variable.               */
LOCVAR bool tracing;

/* If this variable is set to true then the interpreter will not abort if the */
/* very next command (and that one only) generates an error or severe error.  */
LOCVAR bool noabort;

/* If the following boolean is true, the interpreter skips lines until it     */
/* hits the HERE command.                                                     */
LOCVAR bool skipping;

/* The following variables count how many times DIFF is invoked and how many  */
/* times it succeeded. This allows us to output a summary at the end of the   */
/* processing of the test suite.                                              */
LOCVAR ulong difftotl = 0;
LOCVAR ulong diffsucc = 0;

/******************************************************************************/

/* Here are the prototypes for recursive or out-of-order functions.           */
LOCAL void interstr P_((char *));
LOCAL void do_set P_((char *));

/******************************************************************************/

LOCAL char *sing P_((ulong,char *,char *));
LOCAL char *sing(num,sinstr,plustr)
/* Return one or other string depending on whether first argument is singular.*/
ulong num;
char *sinstr;
char *plustr;
{
 if (num==1)
    return sinstr;
 else
    return plustr;
}

/******************************************************************************/

LOCAL uword numpos P_((ulong,ulong,ulong));
LOCAL uword numpos(a,b,c)
/* Returns the number of its arguments that are positive. */
ulong a,b,c;
{
 uword result=0;
 if (a>0) result++;
 if (b>0) result++;
 if (c>0) result++;
 return result;
}

/******************************************************************************/

LOCAL void errsum P_((ulong,ulong,ulong,ulong));
LOCAL void errsum(fat,sev,err,war)
/* Supply as arguments, the number of various kinds of diagnostics.           */
/* Places in linet1 a string describing the diagnostics.                      */
ulong fat,sev,err,war;
{
 char linet2[100];

 if (fat+sev+err+war==0)
    {strcpy(linet1,"SUCCESS: No diagnostics."); return;}

 strcpy(linet1,"There ");

 /* "Was" or "were" depending on the plurality of highest level diagnostic. */
      if (fat>0) strcat(linet1,sing(fat,"was","were"));
 else if (sev>0) strcat(linet1,sing(sev,"was","were"));
 else if (err>0) strcat(linet1,sing(err,"was","were"));
 else if (war>0) strcat(linet1,sing(war,"was","were"));
 else as_bomb("errsum: Error hierarchy failed!");

 strcat(linet1," ");

 /* Fatal errors. */
 if (fat>0)
   {
    sprintf(linet2,"%1lu Fatal error",fat); strcat(linet1,linet2);
    strcat(linet1,sing(fat,"","s"));
   }

 /* Joiner stuff. */
 if (fat>0 && numpos(sev,err,war)>=2)    strcat(linet1,", ");
 if (fat>0 && sev>0 && err==0 && war==0) strcat(linet1," and ");

 /* Severe errors. */
 if (sev>0)
   {
    sprintf(linet2,"%1lu Severe error",sev); strcat(linet1,linet2);
    strcat(linet1,sing(sev,"","s"));
   }

 /* Joiner stuff. */
 if (fat+sev>0 && err>0 && war >0) strcat(linet1,", ");
 if (fat+sev>0 && err>0 && war==0) strcat(linet1," and ");

 /* Errors. */
 if (err>0)
   {
    sprintf(linet2,"%1lu Error",err); strcat(linet1,linet2);
    strcat(linet1,sing(err,"","s"));
   }

 /* Joiner stuff. */
 if (fat+sev+err>0 && war>0) strcat(linet1," and ");

 /* Warnings. */
 if (war > 0)
   {
    sprintf(linet2,"%1lu Warning",war); strcat(linet1,linet2);
    strcat(linet1,sing(war,"","s"));
   }

 /* The final full stop! */
 strcat(linet1,".");
}

/******************************************************************************/

LOCAL void allocarg P_((void));
LOCAL void allocarg()
/* Some compilers don't allow much room for statics and so it is necessary to */
/* declare some variables as pointers and allocate them explicitly. This      */
/* function allocates the command line argument array to point to strings.    */
{
 uword i;
 for (i=0;i<=ARG_MAX;i++)
    arg_arr[i]=(char *) mm_perm(sizeof(cl_t));

 /* Also initialize the substitution strings. */
 for (i=0;i<NUM_SUBS;i++)
   {
    subval[i]=(char *) mm_perm(sizeof(cl_t));
    subval[i][0]=EOS;
   }
 p_comopt=(p_op_t) mm_perm(sizeof(op_t));
 p_defopt=(p_op_t) mm_perm(sizeof(op_t));
}

/******************************************************************************/

LOCAL void zerdia P_((void));
LOCAL void zerdia()
{
 old_war=num_war;
 old_err=num_err;
 old_sev=num_sev;
 num_sev=num_err=num_war=0;
}

LOCAL void sumdia P_((void));
LOCAL void sumdia()
{
 sum_sev+=num_sev;
 sum_err+=num_err;
 sum_war+=num_war;
}

LOCAL void restdia P_((void));
LOCAL void restdia()
{
 num_sev+=old_sev;
 num_err+=old_err;
 num_war+=old_war;
}

/******************************************************************************/

LOCAL void explode P_((char *));
LOCAL void explode(p)
/* Parses the string p into a set of non-blank sequences. Copies each         */
/* distinct run of non-blanks into successive values of arg_arr. Places the   */
/* number of runs of non-blanks into arg_num. DOESN'T generate an error if    */
/* there are too many arguments.                                              */
char *p;
{
 arg_num=0;
 while (TRUE)
   {
    char *x;

    /* Skip to the next argument. */
    while (*p==' ') p++;

    /* Exit if we have hit the end of the string. */
    if (*p==EOS) break;

    /* Exit if we are already full up with arguments. */
    if (arg_num==ARG_MAX) break;

    /* Copy the next argument. */
    x=arg_arr[arg_num];
    while (*p!=' ' && *p!=EOS) *x++ = *p++;
    *x=EOS;
    arg_num++;
   }
}

/******************************************************************************/

LOCAL void dollsub P_((char *));
LOCAL void dollsub(p_comlin)
/* Assumes that it's string argument is in a command line object. */
/* Performs dollar substitutions. */
char *p_comlin;
{
 char *p=p_comlin;
 cl_t  cl;
 char *t;

 t = &cl[0];

 /* Copy the unexpanded command line to the temporary from which we expand it */
 /* back from whence it came.                                                 */
 strcpy(t,p);

 /* Work through the unexpanded command line expanding. */
 while (*t != EOS)
   {
    /* Complain if there is not room for one more character. */
    if ((p-p_comlin) == COMLINE_MAX) goto toobig;

    /* If no dollar sign, no tricks. Just copy the character over. */
    if (*t!='$') {*p++ = *t++; continue;}

    /* We have seen a dollar sign. Move onto the next character. */
    t++;

    /* The only legal escapes are decimal digits, slash, and the dollar sign. */
    if (!isdigit(*t) && !isupper(*t) && *t!='$' && *t!='/')
      {
       wl_sj("S: Illegal dollar subtitution sequence in command line.");
       wl_sj("Legal sequences are $0..$9, $A..$Z, $/, and $$.");
       num_sev++;
       strcpy(p,t);
       return;
      }

    /* A dollar escape is easy to process. */
    if (*t=='$') {*p++ = *t++; continue;}

    /* A slash escape is easy to process. */
    if (*t=='/') {*p++ = FN_DELIM; t++; continue;}

    /* Substitutions have to be expanded. */
    if (isdigit(*t) || isupper(*t))
      {
       ubyte num;
       char *q;
       if (isdigit(*t))
           num = *t-'0';
       else
           num = 10+(*t-'A');
       as_cold(num<NUM_SUBS,"dollsub: num is too bug!");
       q=subval[num];
       if ((p-p_comlin)+(int)strlen(subval[num]) > COMLINE_MAX) goto toobig;
       while (*q!=EOS) *p++ = *q++;
       t++;
      }
   }
 *p=EOS;
 return;

 toobig:
    wl_sj("S: Expanded (i.e. after $1 etc) command line is too long.");
    num_sev++;
    strcpy(p,t);
    return;
}

/******************************************************************************/

LOCAL void fwonerun P_((void));
LOCAL void fwonerun()
/* Performs a single run of FunnelWeb proper, using the global variable       */
/* 'options' as the input command line.                                       */
{
 fn_t lisnam, nopnam, mapnam;

 /* The following clocks record the time taken by various parts of FunnelWeb.  */
 ck_t mappck;
 ck_t scanck;
 ck_t parsck;
 ck_t analck;
 ck_t dumpck;
 ck_t lstrck;
 ck_t tangck;
 ck_t weavck;
 ck_t totlck;

 /* Intialize/zero all the clocks. */
 ck_ini(&mappck);
 ck_ini(&scanck);
 ck_ini(&parsck);
 ck_ini(&analck);
 ck_ini(&dumpck);
 ck_ini(&lstrck);
 ck_ini(&tangck);
 ck_ini(&weavck);
 ck_ini(&totlck);

 /* Start the total time clock ticking. A total time clock is used to gather  */
 /* up the gaps between the invocations of the other clocks.                  */
 ck_start(&totlck);

 ck_start(&lstrck);

 /* Establish the listing file output stream. */
 strcpy(lisnam,"");             /* Start with an empty string.                */
 fn_ins(lisnam,option.op_f_s);  /* Insert input file name.                    */
 fn_ins(lisnam,".lis");         /* Insert constant extension.                 */
 fn_ins(lisnam,option.op_l_s);  /* Insert command line spec.                  */
 wf_ini(&f_l,option.op_l_b);    /* Initialize the stream.                     */
 wf_ope(&f_l,lisnam);           /* Create the file.                           */

 if (option.op_l_b && wf_err(&f_l))
   {
    sprintf(linet1,"S: Error creating listing file \"%s\".",lisnam);
    wl_sj(linet1);
    wl_sj("Aborting...");
    num_sev++;
    return;
   }

 /* Establish the non-product file list output stream. */
 strcpy(nopnam,"");             /* Start with an empty string.                */
 fn_ins(nopnam,option.op_f_s);  /* Insert input file name.                    */
 fn_ins(nopnam,".nop");         /* Insert constant extension.                 */
 fn_ins(nopnam,option.op_n_s);  /* Insert command line spec.                  */
 wf_ini(&f_n,option.op_n_b);    /* Initialize the stream.                     */
 wf_ope(&f_n,nopnam);           /* Create the file.                           */

 if (option.op_n_b && wf_err(&f_n))
   {
    sprintf(linet1,"S: Error creating non-product file list \"%s\".",nopnam);
    wl_sj(linet1);
    wl_sj("Aborting...");
    num_sev++;
    return;
   }

 /* Establish the mapping file output stream. */
 strcpy(mapnam,"");             /* Start with an empty string. */
 fn_ins(mapnam,option.op_f_s);  /* Insert input file name. */
 fn_ins(mapnam,".map");         /* Insert constant extension. */
 fn_ins(mapnam,option.op_u_s);	/* Insert command line spec. */
 wf_ini(&f_m,option.op_u_b);    /* Initialize the stream. */
 wf_ope(&f_m,mapnam);           /* Create the file. */
 if (option.op_u_b && wf_err(&f_m))
   {
    sprintf(linet1,"S: Error creating mapping file \"%s\".",mapnam);
    wl_sj(linet1);
    wl_sj("Aborting...");
    num_sev++;
    return;
   }

 wl_l("FUNNELWEB LISTING FILE");
 wl_l("======================");
 wl_l("");

 /* Initialize the lister for this run. */
 lr_ini();

 ck_stop(&lstrck);

 /* Scanner comes first. */
 ck_start(&scanck);
 scanner(&mappck,&scanck);
 ck_stop(&scanck);

 /* Dump the line and token lists if requested. The scanner supplies sensible */
 /* lists even if it encounters errors, so there is no danger here.           */
 ck_start(&dumpck);
 if (option.op_b2_b) dm_lnls(&f_l);
 if (option.op_b3_b) dm_tkls(&f_l);
 ck_stop(&dumpck);

 /* Invoke the parser if there were no serious scanner errors. */
 if (num_sev+num_err==0)
   {
    ck_start(&parsck);
    parser();
    ck_stop(&parsck);
    /* Only perform post parser dumps if the parser was run. */
    ck_start(&dumpck);
    if (option.op_b4_b) dm_matb(&f_l);
    if (option.op_b5_b) dm_dcls(&f_l);
    ck_stop(&dumpck);
   }
 else
   {
    if (option.op_b4_b)
       wl_l("Macro table dump skipped (Parser was not invoked).");
    if (option.op_b5_b)
       wl_l("Document list dump skipped (Parser was not invoked).");
   }

 /* Invoke the macro structure analyser if still no errors. */
 if (num_sev+num_err==0)
   {
    ck_start(&analck);
    analyse();
    ck_stop(&analck);
   }

 /* The scanner, parser, and analyser send errors to the lister package. */
 /* Send sorted listing to the listing file (and screen if desired).     */
 ck_start(&lstrck);
 if (option.op_u_b)
   {
    if (option.op_l_b) lr_gen_unix(&f_l,option.op_c_i);
    if (option.op_s_b) lr_gen_unix(&f_s,option.op_s_i);
    if (option.op_s_b) lr_gen_unix(&f_j,option.op_s_i);
   }
  else
   {
    if (option.op_l_b) lr_gen(&f_l,option.op_c_i);
    if (option.op_s_b) lr_gen(&f_s,option.op_s_i);
    if (option.op_s_b) lr_gen(&f_j,option.op_s_i);
   }
 ck_stop(&lstrck);

 /* If the first stages went OK, invoke tangle and weave. */
 if (num_sev+num_err==0)
   {
    if (option.op_o_b)
      {
       ck_start(&tangck);
       tangle();
       ck_stop(&tangck);
      }
    if (option.op_t_b)
      {
       ck_start(&weavck);
       if (tr_codes == TR_HTML)
	 weavehtml();
       else
       if (tr_codes == TR_LATEX || tr_codes == TR_L2HTML)
	 weavel2ht();
       else
       if (tr_codes == TR_TEXINFO)
	 weaveinfo();
       else
         weave();
       ck_stop(&weavck);
      }
    /* Leave output lines from Tangle and Weave joined, but separate them */
    /* from any further output.                                           */
    if (option.op_t_b || option.op_o_b)
       wl_sjl("");
   }
 else
   {
    /* Otherwise tell the user that back-end phases will be skipped. */
    if ( option.op_o_b ||  option.op_t_b)
      {
       if (num_sev+num_err==1)
          wr_sjl("Error caused ");
       else
          wr_sjl("Errors caused ");
      }
    if ( option.op_o_b &&  option.op_t_b) wr_sjl("tangle and weave phases");
    if ( option.op_o_b && !option.op_t_b) wr_sjl("tangle phase");
    if (!option.op_o_b &&  option.op_t_b) wr_sjl("weave phase");
    if ( option.op_o_b ||  option.op_t_b)
       {wl_sjl(" to be skipped."); wl_sjl("");}
   }

 ck_stop(&totlck);

 /* If requested write out a summary of the time taken. */
 if (option.op_b6_b)
    dm_times(&f_l,
             &mappck,&scanck,&parsck,&analck,
             &dumpck,&lstrck,&tangck,&weavck,&totlck);

 /* Write out a line summarizing the diagnostics for this run. */
 errsum(0L,num_sev,num_err,num_war); wl_sjl(linet1);

 /* Close the non-product file list file. */
 if (option.op_n_b)
   {
    if (wf_err(&f_n))
      {
       wl_sj("S: Error writing to non-product file list file. Aborting...");
       num_sev++;
       goto closelisting;
      }
    wf_clo(&f_n);
    if (wf_err(&f_n))
      {
       wl_sj("S: Error flushing and closing non-product list. Aborting...");
       num_sev++;
      }
   }
    
 /* Close the mapping file. */
 if (option.op_u_b)
   {
    if (wf_err(&f_m))
      {
       wl_sj("S: Error writing to mapping file. Aborting...");
       num_sev++;
       goto closelisting;
      }
    wf_clo(&f_m);
    if (wf_err(&f_m))
      {
       wl_sj("S: Error flushing and closing mapping file. Aborting...");
       num_sev++;
      }
   }
    
 closelisting:
 /* Close the listing file. */
 if (!option.op_l_b) goto finishoff;
 if (wf_err(&f_l))
   {
    wl_sj("S: Error writing to listing file. Aborting...");
    num_sev++;
    goto finishoff;
   }
 wf_clo(&f_l);
 if (wf_err(&f_l))
   {
    wl_sj("S: Error flushing and closing listing file. Aborting...");
    num_sev++;
   }

 finishoff:
 /* VERY IMPORTANT: Ask the memory management package to free up all the      */
 /* temporary memory (allocated using mm_temp) that has been allocated. This  */
 /* ensures that the memory allocated for this FunnelWeb run will be recycled.*/
 mm_zapt();

} /* End of fwonerun */

/******************************************************************************/

LOCAL void do_absen P_((void));
LOCAL void do_absen ()
{
 if (arg_num != 2)
   {
    wl_sj("S: The ABSENT command requires exactly one argument.");
    num_sev++;
    return;
   }
 if (fexists(arg_arr[1]))
   {
    sprintf(linet1,"S: ABSENT found \"%s\".",arg_arr[1]);
    wl_sj(linet1);
    num_sev++;
    return;
   }
}

/******************************************************************************/

LOCAL void do_cody P_((void));
LOCAL void do_cody ()
/* The CODIFY command takes an input text file and generates an output text   */
/* file containing C code to write out the input text file. The need for this */
/* command springs from the weaver. Experience with FunnelWeb showed that use */
/* of a separate header file, to be included, while apparently sensible,      */
/* caused no end of problems. In particular, problems with portably           */
/* specifying where the header file should be found. In the end, it was       */
/* decided that it would be better to write the header file out with the      */
/* weave output. As the header file is quite long, it is best to automate the */
/* process of converting the file from text to C code to write out the text.  */
/* That is what the CODIFY command does.                                      */
{
 FILE *file1;
 FILE *file2;

#define MAXHACK 1000
 char hackline[MAXHACK+1];
 uword lineno;

 if (arg_num != 3)
   {
    wl_sj("S: The CODIFY command requires exactly two arguments.");
    num_sev++;
    return;
   }

 /* Open the input file for text reading. */
 file1=fopen(arg_arr[1],"r");
 if (file1 == FOPEN_F)
   {
    wl_sj("S: Error opening the input file.");
    num_sev++;
    return;
   }
 file2=fopen(arg_arr[2],"w");
 if (file2 == FOPEN_F)
   {
    fclose(file1);
    wl_sj("S: Error creating the output file.");
    num_sev++;
    return;
   }

 lineno=0;

 /* PROCESS A SINGLE LINE PER ITERATION. */
 while (TRUE)
   {
    uword linelength;
    uword i;

    /* Read in a line of input and terminate loop if there are no more lines. */
    fgets(hackline,MAXHACK,file1);
    if (ferror(file1))
       {wl_sj("S: Error reading the input file.");num_sev++;return;}
    if (feof(file1)) break;
    lineno++;

    /* Complain if the input line is too long. */
#if defined(__cplusplus) || defined(__STDC__)
    if (strlen(hackline)>(size_t)81)
#else
    if (strlen(hackline)>81)
#endif
      {
       sprintf(linet1,"Line %lu of input file is too long.",
               (ulong) strlen(hackline));
       wl_sj(linet1);
       wl_sj("The maximum allowable length is 80 characters.");
       num_sev++;
       return;
      }

    /* Write the start-of-line string. */
    if (fputs(" WX(\"",file2) == FPUTS_F) goto write_failure;

    /* Write out the line in sanitized form. */
    linelength=strlen(hackline);
    for (i=0;i<linelength;i++)
      {
       char ch = hackline[i];
       if (ch==EOL)
          ; /* Ignore this. */
       else
       if (ch=='\"')
          {if (fputs("\\\"",file2) == FPUTS_F) goto write_failure;}
       else
       if (ch=='\\')
          {if (fputs("\\\\",file2) == FPUTS_F) goto write_failure;}
       else
          {if (fputc(ch,file2) == FPUTC_F) goto write_failure;}
      }

    /* Write the end of line string. */
    if (fputs("\");\n",file2) == FPUTS_F) goto write_failure;
   }

 if (fflush(file2) != FFLUSH_S)
    {wl_sj("S: Error flushing the output file.");num_sev++;return;}
 if (fclose(file1) == FCLOSE_F)
   {wl_sj("S: Error closing the input file.");num_sev++;return;}
 if (fclose(file2) == FCLOSE_F)
   {wl_sj("S: Error closing the output file.");num_sev++;return;}
 return;

 write_failure:
    wl_sj("S: Error writing the output file.");num_sev++;return;
}

/******************************************************************************/

LOCAL void do_comp P_((void));
LOCAL void do_comp ()
/* The compare command should have two arguments being file names. It         */
/* compares the two files and raises a fatal error if they differ.            */
{
 char *errstr;
 bool result;
 if (arg_num != 3)
   {
    wl_sj("S: COMPARE command must be given exactly two arguments.");
    num_sev++;
    return;
   }
 errstr=eq_files(arg_arr[1],arg_arr[2],&result);
 if (errstr!=NULL)
   {
    wl_sj("S: COMPARE command ran into a problem:");
    wl_sj(errstr);
    num_sev++;
    return;
   }
 if (!result)
   {
    wl_sj("S: A comparison FAILED. Two files compared were not identical!");
    sprintf(linet1,"   File1: \"%s\".",arg_arr[1]); wl_sj(linet1);
    sprintf(linet1,"   File2: \"%s\".",arg_arr[2]); wl_sj(linet1);
    wl_sj("   FunnelWeb has just FAILED a regression test.");
    wl_sj("   You should now inspect the two files to see how the result of");
    wl_sj("   this run of FunnelWeb differed from the \"correct answer\" in");
    wl_sj("   the answer directory.");
    num_sev++;
    return;
   }
}

/******************************************************************************/

LOCAL void do_defin P_((char *));
LOCAL void do_defin (p_comlin)
/* The define command associates a string with a $n. */
char *p_comlin;
{
 char *p;
 ubyte defnum;

 /* p is our scanning pointer and starts at the start of the command line. */
 p=p_comlin;

 /* Skip past the DEFINE command onto the second argument. */
 while ((*p!=' ') && (*p!=EOS)) p++;
 while (*p==' ') p++;

 /* There should be a single digit or upper case letter there. */
 if (!isdigit(*p) && !isupper(*p))
   {wl_sj("S: The first argument to DEFINE must be a decimal digit or");
    wl_sj("   upper case letter.");
    wl_sj("   Example: define 3 \"A Walrus in Spain is a Walrus in Vain.\"");
    num_sev++;return;}
 if (isdigit(*p))
    defnum = *p-'0';
 else
    defnum = 10+(*p-'A');
 as_cold(defnum<NUM_SUBS,"do_defin: num is too bug!");

 /* Move past the digit. */
 p++;

 /* Skip blanks to get to the next argument. */
 while (*p==' ') p++;

 /* Complain if there is no second argument. */
 if (*p==EOS)
   {wl_sj("S: The DEFINE command expected a second argument.");
    num_sev++; return;}

 /* Otherwise make sure that we have a double quoted string. */
 if (*p!='"' || *(p+1)==EOS || p[strlen(p)-1]!='"')
   {wl_sj("S: Second argument to DEFINE must be in double quotes.");
    num_sev++;return;}

 /* All is checked. Now it is safe to copy over the string. */
 p++;
 strcpy(subval[defnum],p);
 subval[defnum][strlen(subval[defnum])-1]=EOS;

 /* TRACE: All the definitions.
 {
  ubyte i;
  for (i=0;i<NUM_SUB;i++)
     printf("$%u=\"%s\"\n",(unsigned) i,subval[i]);
 }
 */
}

/******************************************************************************/

LOCAL void do_diff P_((void));
/* COMMAND FORMAT: diff file1 file2 logfile [abort]                           */
/* This function/command performs a proper text differences on two files.     */
/* This function is long and messy because of C's lack of nested functions.   */
/* I don't want to create global variables here, and defining subfunctions    */
/* that do not have access to the variables of this function would provoke    */
/* too wide an interface to be worth the trouble. So it's code city.          */
/* How I wish that I had FunnelWeb to help me write this function!            */
LOCAL void do_diff()
{
 bool   diffabort;        /* TRUE iff we should abort if files are different. */
 bool   is_same  = FALSE; /* True iff files are proven to be the same.        */
 FILE  *logfile;          /* File to write result of comparison.              */
 bool   badwrite = FALSE; /* TRUE if we couldn't write to the logfile.        */
 char  *p_file1;          /* Pointer to mapping of first  file to compare.    */
 char  *p_file2;          /* Pointer to mapping of second file to compare.    */
 ulong  len_file1;        /* Number of bytes in mapping of first  file.       */
 ulong  len_file2;        /* Number of bytes in mapping of second file.       */
 char  *mess1;            /* Error message from mapper for first  file.       */
 char  *mess2;            /* Error message from mapper for second file.       */
 bool  is_image;          /* TRUE iff mapped images are identical.            */
 bool   anydiff = FALSE;  /* TRUE iff any differences detected during loop.   */

 /* Check that the number of arguments is correct. */
 if (arg_num < 4 || arg_num > 5)
   {
    wl_sj("S: The DIFF command must be given either 3 or 4 arguments.");
    wl_sj("   Usage: diff f1 f2 logfile [abort]");
    num_sev++;
    return;
   }

 /* Check that the fourth argument, if present, is legal. */
 diffabort=FALSE;
 if (arg_num == 5)
    {if (strcmp(arg_arr[4],"ABORT")==0 || strcmp(arg_arr[4],"abort")==0)
       diffabort=TRUE;
    else
      {
       wl_sj(
          "S: The DIFF command's fourth argument, if present, must be ABORT.");
       wl_sj("   Usage: diff f1 f2 logfile [abort]");
       num_sev++;
       return;
      }
    }

 /* Now open the log file to append result of compare. */
 logfile=fopen(arg_arr[3],"a");
 if (logfile == FOPEN_F)
   {
    wl_sj("S: DIFF: Error opening the log file (to append result of compare).");
    num_sev++;
    return;
   }

 /* The following define simplifies writing to the log file. */
#define LOGLINE {if (fputs(linet1,logfile) == FPUTS_F) badwrite=TRUE;}
#define LOGSTR(STR) {if (fputs((STR),logfile) == FPUTS_F) badwrite=TRUE;}
#define LOGCHAR(CH) {if (fputc((CH),logfile) == FPUTC_F) badwrite=TRUE;}

 /* Write the header for this comparison to the log file. */
 sprintf(linet1,"\n\n"                          ); LOGLINE;
 sprintf(linet1,"Comparing \"%s\"\n" ,arg_arr[1]); LOGLINE;
 sprintf(linet1,"     with \"%s\".\n",arg_arr[2]); LOGLINE;

 /* Now map in the two files to be compared.                                  */
 /* Once this is done, we MUST do a mm_zapt later or memory will leak.        */
 /* We attempt to map the second file, even if the first mapping has failed   */
 /* as, if the first file is absent, there is a good chance that the second   */
 /* is absent too, and it is useful to the user to know this.                 */
 mess1=map_file(arg_arr[1],&p_file1,&len_file1);
 mess2=map_file(arg_arr[2],&p_file2,&len_file2);
 if (mess1 != NULL)
   {
    sprintf(linet1,"Error mapping \"%s\".\n",arg_arr[1]); LOGLINE;
    wr_sj("E: DIFF: "); wr_sj(linet1);
    sprintf(linet1,"         %s\n",mess1); LOGLINE; wr_sj(linet1);
    num_err++;
   }
 if (mess2 != NULL)
   {
    sprintf(linet1,"Error mapping \"%s\".\n",arg_arr[2]); LOGLINE;
    wr_sj("E: DIFF: "); wr_sj(linet1);
    sprintf(linet1,"         %s\n",mess2); LOGLINE; wr_sj(linet1);
    num_err++;
   }
 if ((mess1 != NULL) || (mess2 != NULL))
    goto frombadmap;

 /* At this point the two files to be compared are sitting in memory and we   */
 /* have a ready-for-writing log file. We are now ready to compare.           */

 /* First perform a binary image comparison as a check for later.             */
 /* We could do this later, but it is better to do this now, in case the      */
 /* complicated comparison code somehow corrupts one of the images.           */
 is_image= ((len_file1 == len_file2) &&
            (memcmp(p_file1,p_file2,(size_t) len_file1) == 0));

 /* This anonymous block performs the actual comparison. */
 {
  /* The comparison is performed by scrolling the two input files through two */
  /* fixed-length line buffers (buf1 and buf2 - see below). To avoid copying, */
  /* the buffers are made circular. Processing takes place by comparing the   */
  /* first line of each buffer. If the line is the same, the buffers are      */
  /* scrolled by one line. If they are different, then we have encountered a  */
  /* DIFFERENCES SECTION and we have to compare lines near the top of the     */
  /* buffers to find a match. When a match is found, each buffer is scrolled  */
  /* down to its match point and processing continues.                        */

/* LBUFSIZ is the number of number of lines that each buffer can hold.        */
/*         Lines are indexed from [0,LBUFSIZ-1].                              */
/*         WARNING: LBUFSIZ must be a power of two corresponding to WRAP(X).  */
/*         WARNING: Totally different input files will provoke O(LBUFSIZ^2)   */
/*                  checksum comparisons per LBUFSIZ input lines.             */
/* WRAP(X) is a macro that performs wraparound of buffer indices.             */
/* GAP     is the number of lines that have to match to end a diff section.   */
/* MAXDIST is the maximum "distance" that is tested when matching.            */
#define LBUFSIZ 64
#define WRAP(X) ((X) & 0x3F)
#define GAP     3
#define MAXDIST (LBUFSIZ-GAP)

/* The following macro compares two lines in the buffers.                     */
/* The arguments are absolute buffer indices, not relative ones.              */
/* We assume that checksums will mismatch more often than line lengths.       */
#define COMPLINE(INDA,INDB) \
   ((buf1[INDA].c_line == buf2[INDB].c_line) &&  \
    (buf1[INDA].l_line == buf2[INDB].l_line) &&  \
    (memcmp(buf1[INDA].p_line,buf2[INDB].p_line, \
                (size_t) buf1[INDA].l_line)==0))

  /* The two line buffers buf1 and buf2 (see below) don't actually store      */
  /* lines. Instead they store line structures which store pointers to the    */
  /* lines in the mapped images of the files. They also store the length of   */
  /* each line, and a checksum of the line. The checksum is useful for        */
  /* speeding up the comparisons between lines when processing a differences  */
  /* section.                                                                 */
  typedef
     struct
       {
        char *p_line; /* Pointer to first byte in the line. */
        ulong l_line; /* Number of bytes in the line.       */
        uword c_line; /* Checksum of the line.              */
       } line_t;

  char   *p_next1 = p_file1;            /* Points to next line in file1.      */
  char   *p_next2 = p_file2;            /* Points to next line in file2.      */
  char   *p_post1 = p_file1+len_file1;  /* Byte following image of file1.     */
  char   *p_post2 = p_file2+len_file2;  /* Byte following image of file2.     */
  line_t buf1[LBUFSIZ];      /* Comparison buffer for first  file.            */
  line_t buf2[LBUFSIZ];      /* Comparison buffer for second file.            */
  ulong  buf1top = 0;        /* Index of first line in first  buffer.         */
  ulong  buf2top = 0;        /* Index of first line in second buffer.         */
  ulong  buf1fil = 0;        /* Number of lines in first  buffer.             */
  ulong  buf2fil = 0;        /* Number of lines in second buffer.             */
  ulong  topnum1 = 1;        /* Line number of first line of first buffer.    */
  ulong  topnum2 = 1;        /* Line number of first line of second buffer.   */

  /* The following loop compares the line(s) at the top of the two buffers    */
  /* and processes (lines1,lines2) lines of each.                             */
  while (TRUE)
    {
     ulong lines1; /* Lines of file1 processed during this loop iteration.    */
     ulong lines2; /* Lines of file2 processed during this loop iteration.    */
     ulong d,g;    /* Used in comparison loops.                               */

     /* The first thing we do is to fill each buffer as full as possible. At  */
     /* the end of the next two lumps of code, the only reason that a file's  */
     /* is not full is that we have reached the end of the file.              */

     /* Fill the first buffer as full as possible. */
     while ((buf1fil < LBUFSIZ) && (p_next1 != p_post1))
       {
        ulong  ind   = WRAP(buf1top + buf1fil);
        ulong  len   = 0;
        uword  csum  = 0;
        char  *p_lin = p_next1;
        while (TRUE)
          {
           if (p_next1 == p_post1) break;
           len++;
           csum=(csum+*p_next1++) & 0xFFFF;
           if (*(p_next1-1) == EOL) break;
          }
        buf1[ind].p_line = p_lin;
        buf1[ind].l_line = len;
        buf1[ind].c_line = csum;
        buf1fil++;
       }

     /* Fill the second buffer as full as possible. */
     while ((buf2fil < LBUFSIZ) && (p_next2 != p_post2))
       {
        ulong  ind   = WRAP(buf2top + buf2fil);
        ulong  len   = 0;
        uword  csum  = 0;
        char  *p_lin = p_next2;
        while (TRUE)
          {
           if (p_next2 == p_post2) break;
           len++;
           csum=(csum+*p_next2++) & 0xFFFF;
           if (*(p_next2-1) == EOL) break;
          }
        buf2[ind].p_line = p_lin;
        buf2[ind].l_line = len;
        buf2[ind].c_line = csum;
        buf2fil++;
       }

     /* If the buffers are empty then we must be at the end of each file. */
     if (buf1fil==0 && buf2fil==0)
        break;

     /* Try to peel a pair of matching lines off the top of the buffer.       */
     /* If we succeed, zip down to the end of the loop and flush them.        */
     /* We can't integrate this code into the next part because the next part */
     /* requires GAP matches, whereas here we require just one.               */
     if ((buf1fil>0) && (buf2fil>0) && COMPLINE(buf1top,buf2top))
       {lines1=lines2=1; goto flushlines;}

     /* At this point, we know we have a differences section. */
     anydiff=TRUE;

     /* We now compare the top lines of the two buffers for a match. A match  */
     /* is only considered to have been found if we match GAP consecutive     */
     /* lines. The best match minimizes the DISTANCE which is the sum of the  */
     /* offsets (lines1,lines2) (in lines) from the top of each buffer where  */
     /* the match starts. Even better matches minimize abs(lines1-lines2) as  */
     /* well. All these nested loops are to ensure that we search best first. */
     for (d=1;d<=MAXDIST;d++)
       {
        /* Calculate half distance on the high side. */
        long half = (d/2)+1;
        long off;
        long sign_v;
        /* Explore up and down simultaneously from the halfway mark. */
        for (off=0;off<=half;off++)
           for (sign_v= -1;sign_v<2;sign_v+=2)
             {
              long x = half + sign_v*off;
              /* The following test allows the above loops to be sloppy. */
              if (0<=x && x<=d)
                {
                 lines1=x;
                 lines2=d-lines1;
                 /* We now know that we want to test at (lines1,lines2).  */
                 /* So compare the GAP lines starting at those positions. */
                 /* Note: lines1 and lines2, as well as being the number  */
                 /* of lines processed, are also the offset to the first  */
                 /* match line in our match gap.                          */
                 for (g=0;g<GAP;g++)
                   { /* Note: R for relative, A for absolute. */
                    ulong t1r = lines1 + g;
                    ulong t2r = lines2 + g;
                    ulong t1a,t2a;

                    /* If both files have run out at this point, it's a match!*/
                    if ((t1r>=buf1fil) && (t2r>=buf2fil)) continue;

                    /* If just one of the files has run out it's a mismatch.  */
                    if ((t1r>=buf1fil) || (t2r>=buf2fil)) goto gapfail;

                    /* We now know that we have two real lines. Compare them. */
                    /* Variables are to avoid big nested macro expansions.    */
                    t1a = WRAP(buf1top+t1r);
                    t2a = WRAP(buf2top+t2r);
                    if (!COMPLINE(t1a,t2a)) goto gapfail;
                   }
                 /* If we dropped out of the gap loop, we must have found     */
                 /* GAP consecutive matches. So we can run off and write out  */
                 /* the difference section.                                   */
                 goto writediff;

                 /* Here's where we jump if we found a mismatch during gap    */
                 /* looping. All we do is try next pair of offsets.           */
                 gapfail:;
                } /* End sloppy if. */
             } /* End for sign_v. */
       } /* End for distance loop. */

     /* If we got to here then we must have dropped out of the search loop    */
     /* which means that there must have been no match at all between the     */
     /* buffers. The only thing to do is to write out what we have as         */
     /* a differences section.                                                */
     lines1=buf1fil;
     lines2=buf2fil;

     /* Write out the differences section (lines1,lines2) to the log file. */
     writediff:
     { /* Begin writediff */
      ulong i,j;
      LOGSTR("\n");
      LOGSTR("     +-----\n");
      for (i=0;i<lines1;i++)
        {
         ulong nline = WRAP(buf1top+i);
         sprintf(linet1,"%05lu|",(ulong) topnum1+i); LOGLINE;
         for (j=0;j<buf1[nline].l_line;j++)
            LOGCHAR(*(buf1[nline].p_line+j));
        }
      LOGSTR("     +-----\n");
      for (i=0;i<lines2;i++)
        {
         ulong nline = WRAP(buf2top+i);
         sprintf(linet1,"%05lu|",(ulong) topnum2+i); LOGLINE;
         for (j=0;j<buf2[nline].l_line;j++)
            LOGCHAR(*(buf2[nline].p_line+j));
        }
      LOGSTR("     +-----\n");
     } /* End writediff. */

     /* Flush from buffer however many lines we ended up processing. */
     flushlines:
     buf1top=WRAP(buf1top+lines1); topnum1+=lines1; buf1fil-=lines1;
     buf2top=WRAP(buf2top+lines2); topnum2+=lines2; buf2fil-=lines2;

    } /* End the while loop that runs through the two files. */
 } /* End of anonymous block for doing actual comparison. */

 /* The anydiff flag tells us if the loop found any difference sections. */
 is_same=!anydiff;

 /* Target position if we couldn't map in the input files earlier. */
 frombadmap:

 /* Release the memory allocated by the mapper for the input files. */
 /* Failure to do this will result in a memory leak!                */
 mm_zapt();

 /* If the two files are identical, tell the log file. */
 if (is_same)
   LOGSTR("The two files are IDENTICAL.\n");

 /* Invalidate this test in the log file, if inconsistent (see later). */
 if (is_same != is_image)
    LOGSTR("<<CONSISTENCY FAILURE: ABOVE COMPARISON INVALID>>\n");

 /* If we had problems with the log file at any stage, kick up a fuss now. */
 if (badwrite)
   {wl_sj("S: DIFF: Error writing to log file."); num_sev++;}

 /* Close the log file. */
 if (fclose(logfile) == FCLOSE_F)
   {wl_sj("S: DIFF: Error closing the log file."); num_sev++;}

 /* The above code is quite tricky and there is a chance that it contains     */
 /* bugs. So, as a safety check we compare the results from the binary memory */
 /* image comparison performed earlier and the more complicated text          */
 /* comparison above. If they differ, then it's time to go kaboom.            */
 if (is_image && !is_same)
    as_bomb("do_diff: Image comparison succeeded, but text comparison failed.");
 if (!is_image && is_same)
    as_bomb("do_diff: Image comparison failed, but text comparison succeeded.");

 /* If files are non-same and ABORT option is turned on, set severe status. */
 if (!is_same && diffabort)
   {
    wl_sj(
     "S: DIFF: Files have not been proven identical, and ABORT option is on.");
    num_sev++;
   }

 /* Tell the console whether comparison succeeded. */
 if (is_same)
    wl_sj("The two files are IDENTICAL.");
 else
    wl_sj("The two files are DIFFERENT (see the differences file for the details).");

 /* Increment the difference summary counters. */
 difftotl++;
 if (is_same)
    diffsucc++;
}

/******************************************************************************/

LOCAL void do_dsum P_((void));
LOCAL void do_dsum ()
{
 sprintf(linet1,"Summary of Differences"); wl_sj(linet1);
 sprintf(linet1,"----------------------"); wl_sj(linet1);
 sprintf(linet1,"Identical = %lu.",(ulong)            diffsucc); wl_sj(linet1);
 sprintf(linet1,"Different = %lu.",(ulong) (difftotl-diffsucc)); wl_sj(linet1);
 sprintf(linet1,"Total     = %lu.",(ulong)            difftotl); wl_sj(linet1);
}

/******************************************************************************/

LOCAL void do_dzer P_((void));
LOCAL void do_dzer ()
/* Zaps difference counters. */
{
 difftotl = 0;
 diffsucc = 0;
}

/******************************************************************************/

LOCAL void do_eneo P_((void));
LOCAL void do_eneo ()
{
 if (arg_num != 2)
   {
    wl_sj("S: The ENEO command must be given exactly one argument.");
    num_sev++;
    return;
   }
 if (fexists(arg_arr[1]))
    if (remove(arg_arr[1]) != REMOVE_S)
      {
       sprintf(linet1,"S: ENEO failed to delete \"%s\".",arg_arr[1]);
       wl_sj(linet1);
       num_sev++;
       return;
      }
}

/******************************************************************************/

LOCAL void do_exec P_((void));
LOCAL void do_exec ()
{
 uword i;

 if (arg_num < 2)
   {
    wl_sj("S: The EXECUTE command requires at least one argument.");
    num_sev++;
    return;
   }
 if (arg_num > 10)
   {
    wl_sj("S: The EXECUTE command can have at most nine arguments.");
    num_sev++;
    return;
   }

 /* Zap all the numeric arguments. */
 for (i=0; i<10; i++)
    subval[i][0]=EOS;

 /* Copy the arguments over to the $1 $2 etc substitution variables. */
 for (i=1;i<arg_num; i++)
    strcpy(subval[i-1],arg_arr[i]);

 /* Run up a new FunnelWeb shell and interpret the file. */
 interstr(arg_arr[1]);
}

/******************************************************************************/

LOCAL void do_exist P_((void));
LOCAL void do_exist ()
{
 if (arg_num != 2)
   {
    wl_sj("S: The EXISTS command requires exactly one argument.");
    num_sev++;
    return;
   }
 if (!fexists(arg_arr[1]))
   {
    sprintf(linet1,"S: EXISTS failed to find \"%s\".",arg_arr[1]);
    wl_sj(linet1);
    num_sev++;
    return;
   }
}

/******************************************************************************/

LOCAL void do_fix P_((void));
LOCAL void do_fix ()
/* When the test suite is moved from one machine to another, it is possible   */
/* that at some stage it will be moved using a BINARY transfer rather than a  */
/* text file transfer. The result is that the test files will contain lines   */
/* terminated with a sequence of control characters that the local buffered   */
/* IO library will not convert to '\n' upon reading in. The are a few         */
/* solutions to this problem, but one of the most direct is to have a command */
/* such as this one that can convert the file over.                           */
/*                                                                            */
/* Once we have identified an end of line, it is easy to write it out as we   */
/* can just send a '\n' and the local buffered IO library will write the      */
/* right codes for us. The tricky part is deciding what an EOL is in the      */
/* input stream. Well, I could have made the control characters for the       */
/* remote EOL a parameter of this command, but instead I decided to use a     */
/* simple algorithm that should cover nearly all cases...                     */
/* ALGORITHM: Parse the input into alternating blocks of control characters   */
/* and non-control characters. Parse each block of control characters into    */
/* subblocks by parsing it from left to right and starting a new subblock the */
/* moment a character of the subblock currently being parsed appears again.   */
/* This covers at least the following cases, and probably many more:          */
/*    UNIX         LF                                                         */
/*    MSDOS     CR LF                                                         */
/*    Macintosh CR                                                            */
{
 /* Erk! But I found out the hard way, it doesn't work on a VAX!              */
 /* I'm making this do nothing on a VAX rather than generate an error as I    */
 /* want the scripts to work silently on the VAX without modification.        */
#if !VMS
 FILE *infile;     /* File variable for input file.                           */
 FILE *tmpfile;    /* File variable for temporary output file.                */
 char *p_target;   /* Name of final (target) output file.                     */
 STAVAR char *p_temp=NULL;   /* Name of temporary output file.                */

 bool  seen[256];  /* TRUE if char is in current control sequence.            */
 char  undo[256];  /* undo[0..length-1] contains current control sequence.    */
 uword length;     /* Number of control bytes in our buffer.                  */
 uword i;
 int status;

 /* Allocate the temporary file name if not already allocated. */
 if (p_temp==NULL) p_temp=(p_fn_t) mm_perm(sizeof(fn_t));

 /* We can take one or two arguments. One argument means that we should       */
 /* fix up the input file, leaving the result in the input file.              */
 if (arg_num != 2 && arg_num != 3)
   {
    wl_sj("S: The FIXEOLS command requires one or two filename arguments.");
    num_sev++;
    return;
   }

 /* Change to two arguments if the input name is the same as output name. */
 if (arg_num==3 && strcmp(arg_arr[1],arg_arr[2])==0) arg_num=2;

 /* Work out what the target name is going to be. */
 p_target=(arg_num==2) ? arg_arr[1] : arg_arr[2];

 /* Generate a temporary filename for the output file. This is tricky because */
 /* on many machines, one cannot rename across devices or directories. This   */
 /* means that the temporary file has to be created in the same directory as  */
 /* the file that we are going to rename it to later (the target file).       */
 strcpy(p_temp,p_target);
 fn_ins(p_temp,fn_temp());

 /* Open the input file for BINARY reading. */
 infile=fopen(arg_arr[1],"rb");
 if (infile == FOPEN_F)
   {
    sprintf(linet1,"S: FIXEOLS: Error opening \"%s\".",arg_arr[1]);
    wl_sj(linet1);
    num_sev++;
    return;
   }

 /* Create the output file for TEXT writing. */
 tmpfile=fopen(p_temp,"w");
 if (tmpfile == FOPEN_F)
   {
    fclose(infile);
    wl_sj("S: FIXEOLS: Error creating the temporary output file.");
    num_sev++;
    return;
   }

 /* Initialialize the control character buffer to empty. */
 for (i=0;i<256;i++) seen[i]=FALSE;
 length=0;

 while (TRUE)
   {
    /* Read in the next character from the input file. */
    char ch=getc(infile);
    if (ferror(infile))
       {wl_sj("S: FIXEOLS: Error reading the input file.");num_sev++;return;}
    if (feof(infile)) break;

    /* Does character terminate a non-empty buffer? If so, flush it. */
    if (length>0 && (isascprn(ch) || seen[ch]))
      {
       if (fputc(EOL,tmpfile) == FPUTC_F) goto write_failure;
       for (i=0;i<length;i++) seen[undo[i]]=FALSE;
       length=0;
      }

    /* Now we can approach the character cleanly and freshly. */
    if (isascprn(ch))
       {if (fputc(ch,tmpfile) == FPUTC_F) goto write_failure;}
    else
       {undo[length++]=ch; seen[ch]=TRUE;}
   }
 if (length>0)
   {if (fputc(EOL,tmpfile) == FPUTC_F) goto write_failure;}

 if (fflush(tmpfile) != FFLUSH_S)
    {wl_sj("S: FIXEOLS: Error flushing the temporary output file.");num_sev++;return;}
 if (fclose(infile) == FCLOSE_F)
   {wl_sj("S: FIXEOLS: Error closing the input file.");num_sev++;return;}
 if (fclose(tmpfile) == FCLOSE_F)
   {wl_sj("S: FIXEOLS: Error closing the temporary output file.");num_sev++;return;}

 /* If renaming to the input file, we have to delete the input file first. */
 if (arg_num==2)
   {
    status=remove(arg_arr[1]);
    if (status != REMOVE_S)
      {
       wl_sj("S: FIXEOLS: Error deleting existing input file to replace it");
       wl_sj("            with the temporary output file. Deleting temporary and aborting...");
       remove(p_temp);
       num_sev++;
       return;
      }
   }

 /* Rename the temporary file to the target output file. */
 status=rename(p_temp,p_target);

 /* Do the error checking. */
 if (status != RENAME_S)
   {
    wl_sjl("S: FIXEOLS: Error renaming temporary output file to output file.");
    sprintf(linet1,"Temporary file name was \"%s\".",p_temp);
    wl_sjl(linet1);
    sprintf(linet1,"Output    file name was \"%s\".",p_target);
    wl_sjl(linet1);
    wl_sjl("FunnelWeb will leave both files intact so you can look at them.");
    num_sev++;
    return;
   }

 return;

 write_failure:
    wl_sj("S: FIXEOLS: Error writing the output file.");num_sev++;return;
#endif
}

/******************************************************************************/

LOCAL void do_fweb P_((char *));
LOCAL void do_fweb(p_cl)
/* This function performs a single run of FunnelWeb proper. */
char *p_cl;
{
 op_t saveop;

 /* Do set can do all the work for us. However, it operates on p_defopt so we */
 /* have to do some juggling.                                                 */
 ASSIGN(saveop,*p_defopt);
 do_set(p_cl);
 ASSIGN(option,*p_defopt);
 ASSIGN(*p_defopt,saveop);
 if (num_sev>0) return;

 /* do_set ensures that the user hasn't specified any action parameters such  */
 /* as +X and +K, but it necessarily doesn't check to make sure that the user */
 /* has actually specified an input file!                                     */
 if (!option.op_f_b)
   {
    wl_sj("S: No input file specified in FW command.");
    num_sev++;
    return;
   }
 fwonerun();
}

/******************************************************************************/

LOCAL void do_help P_((void));
LOCAL void do_help()
{
 uword messno;

 if (arg_num == 1)
   {
    hel_wri(wr_sj,HL_MEN);
    return;
   }
 if (arg_num > 2)
   {
    wl_sj("S: The HELP command takes at most one argument.");
    num_sev++;
    return;
   }

 /* Translate message name to number. */

 messno=hel_num(arg_arr[1]);
 if (messno == HL_ERR)
   {
    wl_sj(
   "S: Unrecognised help message name. Try just \"help\" for a list of names.");
    num_sev++;
    return;
   }

 hel_wri(wr_sj,messno);
}

/******************************************************************************/

LOCAL void do_set(p_comlin)
/* The SET command allows the user to specify default FunnelWeb options.      */
char *p_comlin;
{
 op_t tmpopt;

 /* Experiment with temporary options, not the real thing. */
 ASSIGN(tmpopt,*p_defopt);

 /* Now execute the effect of the command line on 'p_defopt'. */
 if (!op_add(&tmpopt,p_comlin,wr_sj))
   {
    wl_s("This is a severe error (S). Aborting to FunnelWeb shell...");
    num_sev++;
    return;
   }

 /* Now make sure that the user didn't specify an option to do with the       */
 /* entire FunnelWeb run and not just this invocation of FunnelWeb proper.    */
 if (tmpopt.op_j_b)
   {
    wl_s("S: You cannot invoke FunnelWeb with +J from the FunnelWeb shell.");
    wl_s("   To create a journal file, exit FunnelWeb and reinvoke with \"fw +j\".");
    wl_s("This is a severe error. Aborting to FunnelWeb shell...");
    num_sev++;
    return;
   }
 if (tmpopt.op_x_b)
   {
    wl_s("S: You cannot invoke FunnelWeb with +X from the FunnelWeb shell.");
    wl_s("Use the interactive command EXECUTE instead.");
    wl_s("This is a severe error. Aborting to FunnelWeb shell...");
    num_sev++;
    return;
   }
 if (tmpopt.op_k_b)
   {
    wl_s("S: You cannot invoke FunnelWeb with +K from the FunnelWeb shell.");
    wl_s("This is a severe error. Aborting to FunnelWeb shell...");
    num_sev++;
    return;
   }
 if (tmpopt.op_h_b)
   {
    wl_s("S: You cannot invoke FunnelWeb with +H from the FunnelWeb shell.");
    wl_s("Use the interactive command HELP instead.");
    wl_s("This is a severe error. Aborting to FunnelWeb shell...");
    num_sev++;
    return;
   }

 /* If we get to here, the options must be OK so we can set them as default. */
 ASSIGN(*p_defopt,tmpopt);
}

/******************************************************************************/

LOCAL void do_show P_((void));
LOCAL void do_show()
/* The SHOW command writes out the current options. */
{
 if (arg_num != 1)
   {
    wl_sj("S: The SHOW command does not take arguments.");
    num_sev++;
    return;
   }
 wl_sj("Here are the FunnelWeb command line options that are");
 wl_sj("current in this FunnelWeb session:");
 op_wri(p_defopt,wr_sj);
}

/******************************************************************************/

LOCAL void do_stat P_((void));
LOCAL void do_stat ()
/* The status command checks the number of diagnostics generated by the run.  */
{
 uword i;
 char *thing;
 ulong cnum;

 if (arg_num<1 || arg_num>4)
   {
    wl_sj("S: The STATUS command requires zero to three arguments.");
    num_sev++;
    return;
   }

 /* Zero arguments just means write out status. */
 if (arg_num == 1)
   {
    sprintf(linet1,"Last command: Severes=%lu, Errors=%lu, Warnings=%lu.",
            (ulong) old_sev, (ulong) old_err, (ulong) old_war);
    wl_sj(linet1);
    sprintf(linet1,"Totals      : Severes=%lu, Errors=%lu, Warnings=%lu.",
            (ulong) sum_sev, (ulong) sum_err, (ulong) sum_war);
    wl_sj(linet1);
    return;
   }

 /* More than one argument means CHECK status. */
 for (i=1;i<arg_num;i++)
   {
    char ch=toupper(arg_arr[i][0]);
    unsigned num;
    if (ch!='W' && ch!='E' && ch!='S')
      {
       sprintf(linet1,
              "S: Argument %u of STATUS command has bad letter.",
               (unsigned) i);
       wl_sj(linet1);
       wl_sj("Arguments must be of the form ('W'|'E'|'S')<decimalnumber>.");
       num_sev++;
       return;
      }
    if (sscanf(&arg_arr[i][1],"%u",&num) != 1)
      {
       sprintf(linet1,
      "S: Argument %u of STATUS command has bad number.",
               (unsigned) i);
       wl_sj(linet1);
       wl_sj("   Arguments must be of the form ('W'|'E'|'S')<decimalnumber>.");
       num_sev++;
       return;
      }
    switch(ch)
      {
       case 'W': cnum=old_war; thing="warnings"; break;
       case 'E': cnum=old_err; thing="errors"  ; break;
       case 'S': cnum=old_sev; thing="severes" ; break;
       default : as_bomb("do_stat: case defaulted.");
      }
    if (cnum != num)
      {
       sprintf(linet1,
       "S: STATUS command detected wrong number of %s.",thing);
       wl_sj(linet1);
       sprintf(linet1, "Specifed %s=%u, Actual %s=%u.",
               thing,(unsigned) num,thing,(unsigned) cnum);
       wl_sj(linet1);
       num_sev++;
      }
   }
}

/******************************************************************************/


LOCAL void do_trace P_((void));
LOCAL void do_trace()
{
 if (arg_num != 2) goto help;
 strupper(arg_arr[1]);
 if (strcmp(arg_arr[1],"OFF") == 0) {tracing=FALSE; return;}
 if (strcmp(arg_arr[1], "ON") == 0) {tracing=TRUE ; return;}

 help:
    wl_sj("S: The TRACE command has two forms:");
    wl_sj("      TRACE OFF");
    wl_sj("      TRACE ON");
    num_sev++;
    return;
}

/******************************************************************************/

LOCAL void do_write P_((char *));
LOCAL void do_write(p)
char *p;
{
 uword len;

 /* Skip over the main command and the following blanks. */
 while (*p!=' ' && *p!=EOS) p++;
 while (*p==' ') p++;

 /* Now make sure that the remaining string is delimited by double quotes.    */
 len=strlen(p);
 if ((*p != '\"') || (p[len-1] != '\"') || len<2)
   {
    wl_sj("W: The argument to WRITE should be delimited by double quotes.");
    wl_sj(p);
    num_war++;
    return;
   }

 /* Now temporarily hack out the quotes and write out the string. */
 p[len-1]=EOS;
 wl_sj(p+1);
 p[len-1]='\"';
}

/******************************************************************************/

LOCAL void do_writu P_((char *));
LOCAL void do_writu(p)
char *p;
{
 uword len;

 /* Skip over the main command and the following blanks. */
 while (*p!=' ' && *p!=EOS) p++;
 while (*p==' ') p++;

 /* Now make sure that the remaining string is delimited by double quotes.    */
 len=strlen(p);
 if ((*p != '\"') || (p[len-1] != '\"') || len<2)
   {
    wl_sj("W: The argument to WRITEU should be delimited by double quotes.");
    wl_sj(p);
    num_war++;
    return;
   }

 /* Now temporarily hack out the quotes and write out the string. */
 p[len-1]=EOS;
 wl_sj(p+1);
 p[len-1]='\"';

 /* Now write out another line underlining the above. */
 {uword i; for (i=0;i<len-2;i++) wr_sj("-"); wl_sj("");}
}

/******************************************************************************/

LOCAL bool do_command P_((char *));
LOCAL bool do_command(p_command)
/* Execute a single FunnelWeb shell command. */
char *p_command;
{
 char *v;
 bool result=FALSE;

 zerdia();

 /* Check the command for non-printables. */
 {
  char *s=p_command;
  while (*s!=EOS)
    {
     if (!isascprn(*s))
       {
        sprintf(linet1,
                "S: Command line has non-printable at column %u.",
                (unsigned) (s-p_command)+1);
        wl_sj(linet1);
        num_sev++;
        goto finished;
       }
     s++;
    }
 }

 /* Perform substitutions. */
 dollsub(p_command); if (num_sev>0) goto finished;

 /* Ignore commands consisting entirely of blanks (or empty commands). */
 {
  char *s=p_command;
  while (*s==' ') s++;
  if (*s==EOS) goto finished;
 }

 /* Reject command lines beginning with a blank. */
 if (p_command[0]==' ')
   {
    wl_sj("S: Leading blanks are not allowed in command lines.");
    num_sev++;
    goto finished;
   }

 /* Ignore command lines commencing with the comment character. */
 if (p_command[0]=='!')
    {restdia(); goto finished;}

 /* Parse the command line into arguments. */
 explode(p_command);

 /* Complain if there is no command verb. */
 as_cold(arg_num>0,"do_command: zero arguments!");

 /* It's convenient to have v pointing to verb. */
 v=arg_arr[0];

 /* Convert the verb to upper case. */
 strupper(v);


 /* Execute the verb. */

 if (strcmp(v,"HERE")==0) skipping=FALSE;
 else if (!skipping)
 {    if (strcmp(v,"ABSENT"     )==0) do_absen();
 else if (strcmp(v,"CODIFY"     )==0) do_cody ();
 else if (strcmp(v,"COMPARE"    )==0) do_comp ();
 else if (strcmp(v,"DEFINE"     )==0) do_defin(&p_command[0]);
 else if (strcmp(v,"DIFF"       )==0) do_diff();
 else if (strcmp(v,"DIFFSUMMARY")==0) do_dsum();
 else if (strcmp(v,"DIFFZERO"   )==0) do_dzer();
 else if (strcmp(v,"ENEO"       )==0) do_eneo ();
 else if (strcmp(v,"EXECUTE"    )==0) do_exec ();
 else if (strcmp(v,"EXISTS"     )==0) do_exist();
 else if (strcmp(v,"FIXEOLS"    )==0) do_fix  ();
 else if (strcmp(v,"FW"         )==0) do_fweb (&p_command[0]);
 else if (strcmp(v,"HELP"       )==0) do_help ();
 else if (strcmp(v,"QUIT"       )==0) result=TRUE;
 else if (strcmp(v,"SET"        )==0) do_set  (&p_command[0]);
 else if (strcmp(v,"SHOW"       )==0) do_show ();
 else if (strcmp(v,"SKIPTO"     )==0) skipping=TRUE;
 else if (strcmp(v,"STATUS"     )==0) do_stat ();
 else if (strcmp(v,"TOLERATE"   )==0) noabort=TRUE;
 else if (strcmp(v,"TRACE"      )==0) do_trace();
 else if (strcmp(v,"WRITE"      )==0) do_write(&p_command[0]);
 else if (strcmp(v,"WRITEU"     )==0) do_writu(&p_command[0]);
 else
   {
    /* The following trace is likely to confuse beginners.        */
    /* sprintf(linet1,"Expanded command line=\"%s\".",p_command); */
    /* wl_sj(linet1);                                             */
    wl_sj("S: Unknown command. Type HELP for a list of commands.");
    num_sev++;
    goto finished;
   }
 }

 finished:
 sumdia();
 return result;
}

/******************************************************************************/

LOCAL void interpret P_((FILE *,char *));
LOCAL void interpret(p_file,filnam)
/* p_file must be a file opened for reading. The file's name must be supplied */
/* in filnam for error reporting reasons. The function reads each line from   */
/* the file and feeds it to the FunnelWeb interpreter command executer.       */
FILE *p_file;
char *filnam;
{
 ulong lineno=0;
 char *result;
 bool b;
 cl_t  comline;
 char *p_comline;

 p_comline = &comline[0];

 while (TRUE)
   {
    bool oldnoabort = noabort;
    noabort=FALSE;

    if (p_file == stdin || tracing)
       wr_sj("FunnelWeb>");

    result=fgets(p_comline,(int) COMLINE_MAX,p_file);
    if (feof(p_file))
      {
       sprintf(linet1,"<End of Script File \"%s\">",filnam);
      if (p_file == stdin || tracing)
          wl_sj(linet1);
       break;
      }
    if (ferror(p_file) || (result == FGETS_FE))
      {
       sprintf(linet1,"F: Error reading command file \"%s\".",filnam);
       wl_sj(linet1);
       wl_sj("Aborting...");
       sum_fat++;
       return;
      }
    if (p_file == stdin || tracing) wr_j(p_comline);
    if (p_file != stdin && tracing) wr_s(p_comline);

    lineno++;
    if (strlen(p_comline)==COMLINE_MAX)
      {
       sprintf(linet1,"F: Line %lu of command file \"%s\" is too long.",
                      (unsigned long) lineno,filnam);
       wl_sj(linet1);
       wl_sj("Aborting...");
       sum_fat++;
       return;
      }
    as_cold(p_comline[strlen(p_comline)-1]==EOL,"interpret: NO NEWLINE!");
    p_comline[strlen(p_comline)-1]=EOS;
#if defined(__cplusplus) || defined(__STDC__)
    as_cold(strlen(p_comline)<(size_t)COMLINE_MAX,
	    "interpret: Filename too long.");
#else
    as_cold(strlen(p_comline)<COMLINE_MAX,"interpret: Filename too long.");
#endif

    b=do_command(p_comline);
    if (b) break;

    if (sum_fat>0) break;
    if ((p_file != stdin) && (num_sev+num_err>0) && !oldnoabort)
      {
       wl_sj("Error caused termination of FunnelWeb shellscript.");
       break;
      }
   }
}

/******************************************************************************/

LOCAL void interstr(filnam)
/* The 'interpret' function (above) interprets each line of a file already    */
/* opened for reading. This function does a little more, opening and closing  */
/* the file before and after calling 'interpret'.                             */
char *filnam;
{
 FILE *p_file;
 fn_t fn;

 /* Set up a default of ".fws" as a file extension. */
 strcpy(&fn[0],".fws");

 /* Inherit the actual filename. */
#if defined(__cplusplus) || defined(__STDC__)
 as_cold(strlen(filnam)<=(size_t)FILENAME_MAX,"interstr: Filename blasted.");
#else
 as_cold(strlen(filnam)<=FILENAME_MAX,"interstr: Filename blasted.");
#endif
 fn_ins(&fn[0],filnam);

 p_file=fopen(fn,"r");
 if (p_file == FOPEN_F)
   {
    sprintf(linet1,"S: Error opening command file \"%s\".",fn);
    wl_sj(linet1);
    sum_sev++;
    return;
   }

 interpret(p_file,&fn[0]); if (sum_fat>0) return;

 if (fclose(p_file) == FCLOSE_F)
   {
    sprintf(linet1,"F: Error closing command file \"%s\".",fn);
    wl_sj(linet1);
    wl_sj("Aborting...");
    sum_fat++;
    return;
   }
}

/******************************************************************************/

LOCAL void chk_cline P_((void));
LOCAL void chk_cline()
/* Checks to make sure that the command line specifies exactly one action.    */
{
 uword countopt=0;

 /* Count the number of active action options are turned on. */
 if (p_comopt->op_f_b) countopt++;
 if (p_comopt->op_x_b) countopt++;
 if (p_comopt->op_k_b) countopt++;
 if (p_comopt->op_h_b) countopt++;

 if (countopt == 0)
   {
    wl_sj("Your command line does not specify an action.");
    wl_sj("Here some common ways of invoking FunnelWeb.");
    wl_sj("");
    wl_sj("   fw filename          Tangle filename.web.");
    wl_sj("   fw filename +t       Tangle and weave filename.web.");
    wl_sj("   fw +k                Enter interactive mode.");
    wl_sj("   fw +xfilename        Execute FunnelWeb shellscript filename.fws.");
    wl_sj("   fw +h                Display help information about FunnelWeb.");
    wl_sj("");
    if (countopt == 0)
       wl_sj("F: Aborting because command line does not specify an action.");
    sum_fat++;
   }
}

/******************************************************************************/

LOCAL void open_j P_((void));
LOCAL void open_j()
/* Creates and opens the journal file. Note that the journal output stream is */
/* established regardless of whether the user requested a journal file. The   */
/* only difference is that if the user did not specify a journal file, the    */
/* stream is created in error mode which means that it never actually writes. */
{
 fn_t jname;

 /* Establish the journal file output stream. */
 strcpy(jname,"");                 /* Start with an empty string.             */
 fn_ins(jname,p_comopt->op_f_s);   /* Insert input file name.                 */
 fn_ins(jname,".jrn");             /* Insert file extension.                  */
 fn_ins(jname,p_comopt->op_j_s);   /* Insert command line spec.               */
 wf_ini(&f_j,p_comopt->op_j_b);    /* Initialize the stream.                  */
 wf_ope(&f_j,jname);            /* Create the file.                           */
 if (p_comopt->op_j_b && wf_err(&f_j))
   {
    sprintf(linet1,"F: Error creating journal file \"%s\".",jname);
    wl_s(linet1);
    wl_s("Aborting...");
    sum_fat++;
    return;
   }
}

/******************************************************************************/

LOCAL void close_j P_((void));
LOCAL void close_j()
/* Closes the journal file. */
{
 if (!p_comopt->op_j_b) return;
 if (wf_err(&f_j))
   {
    wl_s("F: Error writing to journal file. Aborting...");
    sum_fat++;
    return;
   }
 wf_clo(&f_j);
 if (wf_err(&f_j))
   {
    wl_s("F: Error flushing and closing journal file. Aborting...");
    sum_fat++;
    return;
   }
}

/******************************************************************************/

LOCAL void cl_help P_((void));
LOCAL void cl_help ()
{
 uword messno;

 /* Translate message name to number. This ought to work, as the options      */
 /* package is already have supposed to have cleared this argument as OK.     */
 messno=hel_num(p_comopt->op_h_s);
 as_cold(messno!=HL_ERR,"cl_help: Unknown help argument.");

 /* Write out the message. */
 hel_wri(wr_sj,messno);
}

/******************************************************************************/

EXPORT void command(p_comline)
/* Execute the top level command line. This is the place where we do all the  */
/* "once per shell" things as opposed to the "once per run" things.           */
/* If a fatal error occurs, the correct course of action here is to increment */
/* sum_fat and return immediately. The main() function deals with delivering  */
/* the correct return status to the operating system.                         */
char *p_comline;
{
 old_war=old_err=old_sev=0;

 tracing=FALSE;
 noabort=FALSE;
 skipping=FALSE;

 /* Allocate space for command line arguments. */
 allocarg();

 /* Set up the standard output (stdout) screen (console) output stream. */
 wf_ini(&f_s,TRUE);
 wf_att(&f_s,stdout);

 /* Parse the command line and place the information in p_comopt-> */
 op_ini(p_comopt);
 if (!op_add(p_comopt,p_comline,wr_s))
   {wr_s("F: Command line error. Aborting..."); sum_fat++; goto windup;}

 /* If the user asked for some peace and quiet by setting +Q, disable the     */
 /* console stream. Note: FunnelWeb main() always issues a message using a    */
 /* printf if any diagnostics have been generated.                            */
 if (p_comopt->op_q_b) wf_ini(&f_s,FALSE);

 /* Create and open the journal file. */
 open_j(); if (sum_fat>0) goto windup;

 wl_sj("FunnelWeb Version 3.0 (May 1992)");
 wl_sj("--------------------------------");
 wl_sj("Copyright (C) Ross Williams 1992. There is ABSOLUTELY NO WARRANTY.");
 wl_sj("You are welcome to distribute this software under certain conditions.");
 if (p_comopt->op_k_b)
 wl_sj("For more information, type HELP.");
 else
 wl_sj("For more information, use the +h (help) option (e.g. \"fw +h\").");
 wl_sj("");

 /* Ensure that the user has specified at least one action. */
 chk_cline(); if (sum_fat>0) goto windup;

 /* Establish the default options for the shell run (if any).                 */
 /* Get rid of any options not to do with a single run of FunnelWeb proper.   */
 ASSIGN(*p_defopt,*p_comopt);
 p_defopt->op_j_b=FALSE;
 p_defopt->op_x_b=FALSE;
 p_defopt->op_k_b=FALSE;

 /* In the absence of everything else, command line options are run options. */
 ASSIGN(option,*p_comopt);

 /* Execute initialization file if any. */
 if (fexists(INITFILE))
    interstr(INITFILE);

 /* Execute the specified actions. */
 if (p_comopt->op_x_b) interstr(p_comopt->op_x_s);
 if (p_comopt->op_f_b) {zerdia(); fwonerun(); sumdia();}
 if (p_comopt->op_h_b) cl_help();
 if (p_comopt->op_k_b) interpret(stdin,"standard_input");

 /* If we weren't in onerun mode, give a grand summary of errors. */
 if (p_comopt->op_k_b || p_comopt->op_x_b)
    {
     wr_sj("Final diagnostics totals: ");
     errsum(sum_fat,sum_sev,sum_err,sum_war);
     wl_sj(linet1);
    }

 /* Close the journal file. */
 close_j(); if (sum_fat>0) goto windup;

 /* Check for errors on the screen stream (standard output). */
 if (p_comopt->op_s_b && wf_err(&f_s))
   {
    /* No point in trying to write a message to the screen! */
    /* But we can at least register a fatal error.          */
    sum_fat++;
   }

 windup:

 /* If the user has set +Q to turn off screen output and one or more          */
 /* diagnostics have been generated, we need to break through to warn the     */
 /* user.                                                                     */
 {
  ulong sum_all=sum_fat+sum_sev+sum_err+sum_war;
  if (p_comopt->op_q_b && sum_all>0)
     {
      errsum(sum_fat,sum_sev,sum_err,sum_war);
      fprintf(stderr,"%s\n",linet1);
     }
 }
}

/******************************************************************************/
/*                             End of COMMAND.C                               */
/******************************************************************************/

static char RCSid[] = "$Id: option.c,v 1.11 2013/11/09 21:05:52 profw Exp $";
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
   22-Jul-1992  AMS  Added support for +U option for special output.
   26-Jul-1992  AMS  Added RCS id.
   06-Aug-1997	WMW  Added a file name to the U option
		     Add non-product files
   03-May-1998	WMW  Add A option to specify header kinds
   09-Nov-2013  WMW  Corrections for a finicky C compiler

##############################################################################*/


/******************************************************************************/
/*                                  OPTION.C                                  */
/******************************************************************************/

#include <ctype.h>
#include "style.h"

#include "as.h"
#include "data.h"
#include "machin.h"
#include "misc.h"
#include "option.h"

/******************************************************************************/

LOCAL void wl_caret P_((ulong,void (*)(char *)));
LOCAL void wl_caret(n,p_outf)
/* Writes a caret at position n of an otherwise blank line. */
ulong n;
void  (*p_outf) P_((char *));
{
 as_cold(n<1000,"wl_caret: Argument is out of range.");
 while (--n > 0)
    (*p_outf)(" ");
 (*p_outf)("^\n");
}

/******************************************************************************/

EXPORT void op_ini(p_op)
p_op_t p_op;
{
 p_op->op_a_b=FALSE;
 strcpy(&p_op->op_a_s[0],"");

 p_op->op_f_b=FALSE;
 strcpy(&p_op->op_f_s[0],"");

 p_op->op_j_b=FALSE;
 strcpy(&p_op->op_j_s[0],"");

 strcpy(&p_op->op_i_s[0],"");

 p_op->op_n_b=TRUE;
 strcpy(&p_op->op_n_s[0],"");

 p_op->op_o_b=TRUE;
 strcpy(&p_op->op_o_s[0],"");

 p_op->op_t_b=FALSE;
 strcpy(&p_op->op_t_s[0],"");

 p_op->op_l_b=TRUE;
 strcpy(&p_op->op_l_s[0],"");

 p_op->op_d_b=FALSE;

 p_op->op_c_i=2;

 p_op->op_q_b=FALSE;

 p_op->op_s_b=FALSE;
 p_op->op_s_i=1;

 p_op->op_w_b=FALSE;
 p_op->op_w_i=80;

 p_op->op_x_b=FALSE;
 strcpy(&p_op->op_x_s[0],"");

 p_op->op_k_b=FALSE;

 p_op->op_u_b=FALSE;
 strcpy(&p_op->op_u_s[0],"");

 p_op->op_b1_b=FALSE;
 p_op->op_b2_b=FALSE;
 p_op->op_b3_b=FALSE;
 p_op->op_b4_b=FALSE;
 p_op->op_b5_b=FALSE;
 p_op->op_b6_b=FALSE;
 p_op->op_b7_b=FALSE;
 
 p_op->op_h_b=FALSE;
 strcpy(&p_op->op_h_s[0],"menu");
}

/******************************************************************************/

EXPORT bool op_add(p_op,p_cl,p_outf)
p_op_t p_op;
p_cl_t p_cl;
void   (*p_outf) P_((char *));
{
 op_t  op_save;                  /* Saves *p_op so it can be restored later.  */
 char *comline = (char *) p_cl;  /* Pointer to the command line to be parsed. */
 char *p;                        /* Handy parsing pointer.                    */
 bool seen_error = FALSE;        /* TRUE iff one or more errors seen.         */

#define ECHO_CL {if (!seen_error)\
                   {(*p_outf)(comline);(*p_outf)("\n"); seen_error=TRUE;}}

 /* Save the parameter option structure so that we can restore it */
 /* if an error occurs later on.                                  */
 ASSIGN(op_save,*p_op);

 /* Check to make sure that the command line is not too long. */
 /* This error should really never occur.                     */
 p=comline;
 while (*p++ != EOS)
    if ((p-comline) > COMLINE_MAX)
      {
       (*p_outf)("FunnelWeb command line syntax error.\n");
       (*p_outf)("The entire command line is too long.\n");
       sprintf(linet1,"The maximum command line length is %u characters.\n",
              (unsigned) COMLINE_MAX);
       (*p_outf)(linet1);
       goto failure;
      }

 /* Check that the command line contains only printables. */
 p=comline;
 while (*p != EOS)
   {
    if (!isascprn(*p))
      {
       (*p_outf)("FunnelWeb command line syntax error.\n");
       (*p_outf)("Command line contains one or more non-printables.\n");
       sprintf(linet1,"The first is at column %u.\n",(unsigned) (1+p-comline));
       (*p_outf)(linet1);
       goto failure;
      }
    p++;
   }

 /* Now parse each option. */
 p=comline;
 while (TRUE)
   {/* This loop processes one command line parameter (option) per iteration. */
    char *p_startopt;    /* Points to the start of the parameter.             */
    bool opsign;           /* The sign of the current option (+=TRUE).          */
    bool opsign_active;    /* TRUE => (+ or -). FALSE => (=).                   */
    char letter;         /* Letter of current option.                         */
    cl_t cl_temp;        /* Parameter string of the current option.           */
    fn_t fn_temp;        /* Parameter string of the current option.           */
    int  i;              /* Handy int used to feed sscanf.                    */

    /* Skip first parameter or rest of previous parameter after syntax error. */
    while ((*p!=' ') && (*p!=EOS)) p++;

    /* Skip blanks between parameters. */
    while (*p==' ') p++;

    /* At this point we are either at the start of a parameter or at EOS.     */
    /* Finish if we are at the EOS.                                           */
    if (*p==EOS) break;

    /* p now points to the next parameter (option). Make a note of its start. */
    p_startopt=p;

    /* This switch statement parses the sign and letter characters.           */
    switch (*p)
      {
       case '-': opsign=FALSE; opsign_active=TRUE;  p++; goto parse_letter;
       case '+': opsign=TRUE;  opsign_active=TRUE;  p++; goto parse_letter;
       case '=':             opsign_active=FALSE; p++; goto parse_letter;
          parse_letter:
          /* We have seen a sign. There should be a following letter. */
          letter = *p;
          if (!isalpha(letter))
            {
     ECHO_CL; wl_caret(p-comline,p_outf);
             (*p_outf)("FunnelWeb command line syntax error.\n");
             (*p_outf)("Option letter expected here.\n");
             continue; /* Skip to the next parameter. */
            }
          p++;
          break;
       default: /* If no sign the option is a NAME option and defaults to +F. */
          opsign=TRUE; opsign_active=TRUE; letter='F'; break;
      } /* End switch */

    /* Assert: p points to the parameter string of the option.      */
    /* Copy the parameter string into the holding variable cl_temp. */
    {char *q;
     q = &cl_temp[0];
     while ((*p!=EOS) && (*p!=' '))
        *q++ = *p++;
     *q=EOS;
    }

    /* As COMLINE_MAX can be greater than FILENAME_MAX, we have to be careful */
    /* that the user is not about to blow our filename buffer.                */
#if defined(__cplusplus) || defined(__STDC__)
    if (strlen(cl_temp) > (size_t)FILENAME_MAX)
#else
    if (strlen(cl_temp) > FILENAME_MAX)
#endif
      {
       ECHO_CL; wl_caret(p_startopt-comline,p_outf);
       (*p_outf)("FunnelWeb command line syntax error.\n");
       (*p_outf)("Option parameter string is too long.\n");
       sprintf(linet1,"The maximum option parameter length is %u characters.\n",
              (unsigned) FILENAME_MAX);
       (*p_outf)(linet1);
       continue; /* Skip to next parameter. */
      }

    /* Now that we know that the parameter is not too big, we can copy it     */
    /* into a temporary variable of filename type.                            */
    strcpy(&fn_temp[0],&cl_temp[0]);

    /* At this point p points to the character following the option that      */
    /* we have just scanned. This is either a blank or an EOS.                */
    /* The current option is held in (opsign,opsign_active,letter,fn_temp).       */
    /* Now we apply the option to the option record.                          */
    switch (toupper(letter))
      {
       case 'A':
          if (opsign_active) p_op->op_a_b=opsign;
          strcpy(&p_op->op_a_s[0],&fn_temp[0]);
          break;
       case 'F':
          if (opsign_active) p_op->op_f_b=opsign;
          strcpy(&p_op->op_f_s[0],&fn_temp[0]);
          break;
       case 'J':
          if (opsign_active) p_op->op_j_b=opsign;
          strcpy(&p_op->op_j_s[0],&fn_temp[0]);
          break;
       case 'I':
          strcpy(&p_op->op_i_s[0],&fn_temp[0]);
          break;
       case 'N':
          if (opsign_active) p_op->op_n_b=opsign;
          strcpy(&p_op->op_n_s[0],&fn_temp[0]);
          break;
       case 'O':
          if (opsign_active) p_op->op_o_b=opsign;
          strcpy(&p_op->op_o_s[0],&fn_temp[0]);
          break;
       case 'T':
          if (opsign_active) p_op->op_t_b=opsign;
          strcpy(&p_op->op_t_s[0],&fn_temp[0]);
          break;
       case 'L':
          if (opsign_active) p_op->op_l_b=opsign;
          strcpy(&p_op->op_l_s[0],&fn_temp[0]);
          break;
       case 'D':
          if (opsign_active) p_op->op_d_b=opsign;
#if defined(__cplusplus) || defined(__STDC__)
          if (strlen(fn_temp)>(size_t)0)
#else
          if (strlen(fn_temp)>0)
#endif
            {
     ECHO_CL; wl_caret(3+p_startopt-comline,p_outf);
             (*p_outf)("FunnelWeb command line syntax error.\n");
             (*p_outf)("The D option does not take an argument.\n");
            }
          break;
       case 'C':
          if ((sscanf(&fn_temp[0],"%d",&i) != 1) || (i<0) || (100<i))
            {
     ECHO_CL; wl_caret(3+p_startopt-comline,p_outf);
             (*p_outf)("FunnelWeb command line syntax error.\n");
             (*p_outf)("Numeric argument to C option invalid. It must\n");
             (*p_outf)("be an unsigned decimal integer in the range [0,100].\n");
            }
          else
             p_op->op_c_i=i;
          break;
       case 'Q':
          if (opsign_active) p_op->op_q_b=opsign;
#if defined(__cplusplus) || defined(__STDC__)
          if (strlen(fn_temp)>(size_t)0)
#else
          if (strlen(fn_temp)>0)
#endif
            {
     ECHO_CL; wl_caret(3+p_startopt-comline,p_outf);
             (*p_outf)("FunnelWeb command line syntax error.\n");
             (*p_outf)("The Q option does not take an argument.\n");
            }
          break;
       case 'S':
          if (opsign_active) p_op->op_s_b=opsign;
          if (strlen(fn_temp)==0) break;
          if ((sscanf(&fn_temp[0],"%d",&i) != 1) || (i<0) || (100<i))
            {
     ECHO_CL; wl_caret(2+p_startopt-comline,p_outf);
             (*p_outf)("FunnelWeb command line syntax error.\n");
             (*p_outf)("Numeric argument to S option invalid. It must\n");
             (*p_outf)("be an unsigned decimal integer in the range [0,100].\n");
            }
          else
             p_op->op_s_i=i;
          break;
       case 'W':
          if (opsign_active) p_op->op_w_b=opsign;
          if (strlen(fn_temp)==0) break;
          if ((sscanf(&fn_temp[0],"%d",&i) != 1) || (i<0) || (1000<i))
            {
     ECHO_CL; wl_caret(2+p_startopt-comline,p_outf);
             (*p_outf)("FunnelWeb command line syntax error.\n");
             (*p_outf)("Error: Numeric argument to W option invalid. It must\n");
             (*p_outf)("be an unsigned decimal integer in the range [0,1000].\n");
            }
          else
             p_op->op_w_i=i;
          break;
       case 'X':
          if (opsign_active) p_op->op_x_b=opsign;
          strcpy(&p_op->op_x_s[0],&fn_temp[0]);
          break;
       case 'K':
          if (opsign_active) p_op->op_k_b=opsign;
#if defined(__cplusplus) || defined(__STDC__)
          if (strlen(fn_temp)>(size_t)0)
#else
          if (strlen(fn_temp)>0)
#endif
            {
     ECHO_CL; wl_caret(3+p_startopt-comline,p_outf);
             (*p_outf)("FunnelWeb command line syntax error.\n");
             (*p_outf)("The K option does not take an argument.\n");
            }
          break;
       case 'U':
          if (opsign_active) p_op->op_u_b=opsign;
          strcpy(&p_op->op_u_s[0],&fn_temp[0]);
          break;
       case 'H':
          if (opsign_active) p_op->op_h_b=opsign;
#if defined(__cplusplus) || defined(__STDC__)
          if (strlen(&fn_temp[0]) > (size_t)0)
	  {
          if (strlen(&fn_temp[0]) > (size_t)HL_NMLEN)
#else
          if (strlen(&fn_temp[0]) > 0)
	  {
          if (strlen(&fn_temp[0]) > HL_NMLEN)
#endif
            {
     ECHO_CL; wl_caret(3+p_startopt-comline,p_outf);
             (*p_outf)("FunnelWeb command line syntax error.\n");
             (*p_outf)("The H option string argument is too long.\n");
             (*p_outf)("Try +Hmenu for a list of help message names.\n");
            }
          else
             if (hel_num(&fn_temp[0]) == HL_ERR)
            {
     ECHO_CL; wl_caret(3+p_startopt-comline,p_outf);
             (*p_outf)("FunnelWeb command line syntax error.\n");
             (*p_outf)("Unrecognised message name in argument to H option.\n");
             (*p_outf)("Try +Hmenu for a list of help message names.\n");
            }
          } else
             strcpy(&p_op->op_h_s[0],&fn_temp[0]);
          break;
       case 'B':
         {
          uword i;
          if (strlen(fn_temp)==0)
            {
     ECHO_CL; wl_caret(3+p_startopt-comline,p_outf);
             (*p_outf)("FunnelWeb command line syntax error.\n");
             (*p_outf)("The B option must be followed by one or more digits.\n");
             (*p_outf)("The digits must be in the range 1..7.\n");
             break;
            }
          for (i=0;i<strlen(fn_temp);i++)
             if (fn_temp[i]<'1' || fn_temp[i]>'7')
               {

ECHO_CL; wl_caret(2+p_startopt-comline+(1+i),p_outf);
                (*p_outf)("FunnelWeb command line syntax error.\n");
                (*p_outf)("Error: Characters in B argument must be '1'..'7'.\n");
                goto endbop;
               }
          if (opsign_active)
             for (i=0;i<strlen(fn_temp);i++)
                switch (fn_temp[i])
                  {
                   case '1': p_op->op_b1_b=opsign; break;
                   case '2': p_op->op_b2_b=opsign; break;
                   case '3': p_op->op_b3_b=opsign; break;
                   case '4': p_op->op_b4_b=opsign; break;
                   case '5': p_op->op_b5_b=opsign; break;
                   case '6': p_op->op_b6_b=opsign; break;
                   case '7': p_op->op_b7_b=opsign; break;
                   default: as_bomb("op_add: b option case defaulted.");
                  }
          endbop:
          break;
         }
       default:
  ECHO_CL; wl_caret(2+p_startopt-comline,p_outf);
          (*p_outf)("FunnelWeb command line syntax error.\n");
          (*p_outf)("Error: Unknown option letter.\n");
          (*p_outf)("Legal option letters are FIOTLCSWPXZ.\n");
          (*p_outf)("(Note: But P is not yet implemented!)\n");
          break;
      }
   } /* End while. */
 if (seen_error) goto failure;
 return TRUE;

 failure: ASSIGN(*p_op,op_save); return FALSE;
}

/******************************************************************************/

EXPORT void op_wri(p_op,p_outf)
p_op_t p_op;
void   (*p_outf) P_((char *));
{
#define STC(BOOLV) ((BOOLV)?'+':'-')
 sprintf(linet1,"   %cA\n"  , STC(p_op->op_a_b)                          );(*p_outf)(linet1);
 sprintf(linet1,"   %cB1 %cB2 %cB3 %cB4 %cB5 %cB6 %cB7\n",
 STC(p_op->op_b1_b),
 STC(p_op->op_b2_b),
 STC(p_op->op_b3_b),
 STC(p_op->op_b4_b),
 STC(p_op->op_b5_b),
 STC(p_op->op_b6_b),
 STC(p_op->op_b7_b));(*p_outf)(linet1);
 sprintf(linet1,"   +C%u\n" ,                    (unsigned) p_op->op_c_i );(*p_outf)(linet1);
 sprintf(linet1,"   %cD\n"  , STC(p_op->op_d_b)                          );(*p_outf)(linet1);
 sprintf(linet1,"   %cF%s\n", STC(p_op->op_f_b),            p_op->op_f_s );(*p_outf)(linet1);
 sprintf(linet1,"   %cH%s\n", STC(p_op->op_h_b),            p_op->op_h_s );(*p_outf)(linet1);
 sprintf(linet1,"   +I%s\n" ,                               p_op->op_i_s );(*p_outf)(linet1);
 sprintf(linet1,"   %cJ%s\n", STC(p_op->op_j_b),            p_op->op_j_s );(*p_outf)(linet1);
 sprintf(linet1,"   %cK\n"  , STC(p_op->op_k_b)                          );(*p_outf)(linet1);
 sprintf(linet1,"   %cL%s\n", STC(p_op->op_l_b),            p_op->op_l_s );(*p_outf)(linet1);
 sprintf(linet1,"   %cN%s\n", STC(p_op->op_n_b),            p_op->op_n_s );(*p_outf)(linet1);
 sprintf(linet1,"   %cO%s\n", STC(p_op->op_o_b),            p_op->op_o_s );(*p_outf)(linet1);
 sprintf(linet1,"   %cQ\n"  , STC(p_op->op_q_b)                          );(*p_outf)(linet1);
 sprintf(linet1,"   %cS%u\n", STC(p_op->op_s_b), (unsigned) p_op->op_s_i );(*p_outf)(linet1);
 sprintf(linet1,"   %cT%s\n", STC(p_op->op_t_b),            p_op->op_t_s );(*p_outf)(linet1);
 sprintf(linet1,"   %cU%s\n", STC(p_op->op_u_b),            p_op->op_u_s );(*p_outf)(linet1);
 sprintf(linet1,"   %cW%u\n", STC(p_op->op_w_b), (unsigned) p_op->op_w_i );(*p_outf)(linet1);
 sprintf(linet1,"   %cX%s\n", STC(p_op->op_x_b),            p_op->op_x_s );(*p_outf)(linet1);
}

/******************************************************************************/
/*                              End of OPTION.C                               */
/******************************************************************************/


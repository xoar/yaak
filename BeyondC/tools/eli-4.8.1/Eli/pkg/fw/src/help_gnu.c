static char RCSid[] = "$Id: help_gnu.c,v 1.5 1999/10/20 04:56:15 tony Exp $";
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

##############################################################################*/


/******************************************************************************/
/*                                 HELP_GNU.C                                 */
/******************************************************************************/
/*                                                                            */
/* REPRESENTING MESSAGES AS C CODE                                            */
/* ===============================                                            */
/* Experience has shown that it is much more reliable to code text messages   */
/* into a program than to expect the program to track down text files         */
/* containing the messages at run time. Worthwhile for smallish files (such   */
/* as these help messages) at least. For this reason, all the messages in     */
/* this module are represented by code (e.g. as in printf statements).        */
/*                                                                            */
/* There is no difficulty turning a short message into code; simply place it  */
/* in output statements. However, large messages (e.g. the GNU license) are   */
/* more tedious, and also present more of a problem if it is necessary to     */
/* change them substantially at a later date. This problem has been solved in */
/* FunnelWeb by writing a small program that reads a text file and writes out */
/* C code that writes the text file. The files involved are:                  */
/*                                                                            */
/*    help_gnu.mes - The original message.                                    */
/*    help_gnu.c   - C code to write out the original message.                */
/*                                                                            */
/* To turn help_gnu.mes into help_gnu.c, give the following command in        */
/* FunnelWeb interactive mode: codify help_gnu.txt help_gnu.c                 */
/*                                                                            */
/******************************************************************************/

#include "style.h"

#include "help_gnu.h"

/******************************************************************************/

/* This module contains many many output statements that call an output       */
/* function. To neaten up all these calls, we define a global variable to     */
/* hold a pointer to the function and simple macro to write output using      */
/* the function.                                                              */
LOCVAR void (*pf) P_((char *));

#define WX(STR) (*pf)(STR);(*pf)("\n")
#define WY(STR) (*pf)(STR)

/******************************************************************************/

EXPORT void hel_gnu (p_outf)
void (*p_outf) P_((char *));
{
 pf=p_outf;
 WY("\n");
 WY("FunnelWeb License\n");
 WY("-----------------\n");
 WY("FunnelWeb is distributed under the following license.\n");
 WY("\n");
 WY("--<Start of GNU License>--\n");
#include "help_gnu.ctx"
 WY("--<End of GNU License>--\n");
 WY("\n");
 WY("If all that scrolled off your screen too quickly, don't worry. You can\n");
 WY("capture this message (or any other FunnelWeb output) in a file by\n");
 WY("specifying the +J option when you invoke FunnelWeb. For example:\n");
 WY("\n");
 WY("       fw +hlicense +jresult.txt\n");
 WY("\n");
}

/******************************************************************************/
/*                             End of HELP_GNU.C                              */
/******************************************************************************/

static char RCSid[] = "$Id: writfile.c,v 1.5 1999/10/20 04:57:13 tony Exp $";
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
/*                                   WRITFILE.C                               */
/******************************************************************************/
/*                                                                            */
/* Implementation Notes                                                       */
/* --------------------                                                       */
/* The .H file gives most of the details of what this package does. Here we   */
/* just give some notes on how it is implemented.                             */
/*                                                                            */
/* MAGIC NUMBERS: These are placed at the head and tail of wf_t records so as */
/* to assist in the detection of uninitialized or corrupted variables.        */
/*                                                                            */
/* TEXT VS BINARY: A big problem arises in choosing whether to write binary   */
/* or text files. Binary files are far faster because they allow us to write  */
/* out large slabs of text using fwrite. The only catch is that they do not   */
/* translate EOL characters in the end of line representation of the host     */
/* environment. Text files, on the other hand are slower (because we have     */
/* only fputc and fputs) but do provide the translation. The solution we      */
/* adopt is to use binary if the host environment's representation for end of */
/* file is EOL (='\n'), but text otherwise. We can determine this by testing  */
/* the symbol UNIX_EOL defined in machin.h. If binary output is chosen,       */
/* only fwrite is called as we don't know if fwrite and fputc calls can be    */
/* mixed (it would seem not).                                                 */
/* Note: We could test the preprocessor symbol in each function. However,     */
/* the wf_att function introduces a problem as we may be attaching to a text  */
/* file in a UNIX_EOL environment (e.g. stdout). So we make the text/binary   */
/* attribute and attribute of each file, rather than the environment which we */
/* use only to direct us in how to create and tag (as binary or text) a file. */
/*                                                                            */
/******************************************************************************/

#include "style.h"

#include "as.h"
#include "machin.h"
#include "writfile.h"

/******************************************************************************/

#define MGC_HEAD (4837295L)
#define MGC_TAIL (1213839L)

/* Set the following to TRUE to bomb the package upon the first error.        */
/* This is a good idea during debugging if no output appears.                 */
#define BOMB_ON_ERROR FALSE

/******************************************************************************/

LOCAL void wf_check P_((p_wf_t));
LOCAL void wf_check(p_wf)
p_wf_t p_wf;
{
 as_cold(p_wf!=NULL,"wf_check: p_wf==NULL.");

 as_cold(p_wf->wf_mhead==MGC_HEAD,
         "wf_check: Magic header field has non-magic value.");

 as_cold(p_wf->wf_mtail==MGC_TAIL,
         "wf_check: Magic trailer field has non-magic value.");

 as_cold(p_wf->wf_isope || p_wf->wf_pfile==NULL,
         "wf_check: WF is closed but wf_pfile!=NULL.");
}

/******************************************************************************/

LOCAL void wf_errlg P_((p_wf_t, char *));
LOCAL void wf_errlg(p_wf,mess)
/* This function is called whenever an error occurs on a stream. The main     */
/* responsibility of this function is to set the error flag in the stream.    */
/* However, it can do other stuff too such as log the error to the screen.    */
p_wf_t p_wf;
char   *mess;
{
 p_wf->wf_iserr=TRUE;
#if BOMB_ON_ERROR
   if (p_wf->wf_pfile == stdout)
      fprintf(stderr,"The output file error occurred on STANDARD OUTPUT.\n");
   else
      fprintf(stderr,"The output file error occurred on an ordinary file.\n");
   as_bomb(mess);
#endif
}

/******************************************************************************/

EXPORT void wf_ini(p_wf,normal)
p_wf_t p_wf;
bool   normal;
{
 p_wf->wf_mhead = MGC_HEAD;
 p_wf->wf_iserr = !normal;
 p_wf->wf_isope = FALSE;
 p_wf->wf_istxt = FALSE;
 p_wf->wf_pfile = NULL;
 p_wf->wf_mtail = MGC_TAIL;
}

/******************************************************************************/

EXPORT void wf_att(p_wf,wf_pfile)
p_wf_t  p_wf;
FILE   *wf_pfile;
{
 wf_check(p_wf);
 if (p_wf->wf_iserr) return;
 as_cold(!p_wf->wf_isope,"wf_att: WF is already open.");

 p_wf->wf_pfile = wf_pfile;
 p_wf->wf_isope = TRUE;
 p_wf->wf_istxt = TRUE; /* Play it safe with files we didn't open. */
 wf_check(p_wf);
}

/******************************************************************************/

EXPORT void wf_ope(p_wf,p_name)
p_wf_t  p_wf;
char   *p_name;
{
 FILE *result;

 wf_check(p_wf);
 if (p_wf->wf_iserr) return;
 as_cold(!p_wf->wf_isope,"wf_ope: WF is already open.");

/* Whether we open the file as text or binary depends on whether EOL maps     */
/* to an end of line in the current environment.                              */
#if UNIX_EOL
 result=fopen(p_name,"wb"); p_wf->wf_istxt=FALSE;
#else
 result=fopen(p_name,"w"); p_wf->wf_istxt=TRUE;
#endif

 if (result == FOPEN_F)
   {
    /* TRACE printf("Output file in error is \"%s\".\n",p_name); */
    wf_errlg(p_wf,"wf_ope: Error opening output file.");
   }
 else
   {p_wf->wf_isope=TRUE; p_wf->wf_pfile=result;}
 wf_check(p_wf);
}

/******************************************************************************/

EXPORT void wf_chr(p_wf,ch)
p_wf_t p_wf;
intchar   ch;
{
 wf_check(p_wf);
 if ( p_wf->wf_iserr) return;
 as_cold(p_wf->wf_isope,"wf_chr: WF is closed.");

 if (p_wf->wf_istxt)
    {
     if (fputc((int) ch,p_wf->wf_pfile) == FPUTC_F)
        wf_errlg(p_wf,"wf_chr: Error fputc()ing to output file.");
    }
 else
   {
    if (fwrite(&ch,(size_t) 1,(size_t) 1,p_wf->wf_pfile) != 1)
        wf_errlg(p_wf,"wf_chr: Error fwrite()ing to output file.");
   }
 wf_check(p_wf);
}

/******************************************************************************/

EXPORT void wf_wr(p_wf,p_str)
p_wf_t p_wf;
char   *p_str;
{
 wf_check(p_wf);
 if ( p_wf->wf_iserr) return;
 as_cold(p_wf->wf_isope,"wf_wr: WF is closed.");

 if (p_wf->wf_istxt)
   {
    if (fputs(p_str,p_wf->wf_pfile) == FPUTS_F)
       wf_errlg(p_wf,"wf_wr: Error fputs()ing to output file.");
   }
 else
   {
    size_t len = strlen(p_str);
    if (fwrite(p_str,(size_t) 1,(size_t) len,p_wf->wf_pfile) != len)
       wf_errlg(p_wf,"wf_wr: Error fwrite()ing to output file.");
   }
 wf_check(p_wf);
}

/******************************************************************************/

EXPORT void wf_blk(p_wf,p_blk,blk_len)
p_wf_t  p_wf;
char   *p_blk;
size_t  blk_len;
{
 wf_check(p_wf);
 if ( p_wf->wf_iserr) return;
 as_cold(p_wf->wf_isope,"wf_blk: WF is closed.");

 if (p_wf->wf_istxt)
   {
    /* Amazingly, fputc seems to be the only way to write out a block of */
    /* bytes with end of line translation. Shocking, but true.           */
    /* See Section B1.4 (p.246-247) of Kernighan and Ritchie.            */
    /* Note: We can't use fputs because that requires a terminating nul. */
    char *p;
    char *p_post = p_blk+blk_len;
    for (p=p_blk; p<p_post; p++)
       if (fputc(*p,p_wf->wf_pfile) == FPUTC_F)
         {
          wf_errlg(p_wf,"wf_blk: Error fputc()ing to output file.");
          break;
         }
   }
 else
   if (fwrite(p_blk,(size_t) 1,(size_t) blk_len,p_wf->wf_pfile) != blk_len)
      wf_errlg(p_wf,"wf_blk: Error fwrite()ing to output file.");
 wf_check(p_wf);
}

/******************************************************************************/

EXPORT void wf_wl(p_wf,p_str)
p_wf_t p_wf;
char   *p_str;
{
 wf_wr(p_wf,p_str);
 wf_chr(p_wf,'\n');
}

/******************************************************************************/

EXPORT void wf_clo(p_wf)
p_wf_t p_wf;
{
 wf_check(p_wf);
 if ( p_wf->wf_iserr) return;
 as_cold(p_wf->wf_isope,"wf_clo: WF is not open.");
 if (fflush(p_wf->wf_pfile) != FFLUSH_S)
    wf_errlg(p_wf,"wf_clo: Error fflush()ing output file.");
 if (fclose(p_wf->wf_pfile) == FCLOSE_F)
    wf_errlg(p_wf,"wf_clo: Error fclose()ing output file.");
 p_wf->wf_isope=FALSE;
 p_wf->wf_pfile=NULL;
 wf_check(p_wf);
}

/******************************************************************************/

EXPORT bool wf_err(p_wf)
p_wf_t p_wf;
{
 wf_check(p_wf);
 return p_wf->wf_iserr;
}

/******************************************************************************/
/*                              End of WRITFILE.C                             */
/******************************************************************************/

static char RCSid[] = "$Id: misc.c,v 1.5 1999/10/20 04:56:36 tony Exp $";
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
/*                                    MISC.C                                  */
/******************************************************************************/

#include <ctype.h>
#include "style.h"

#include "as.h"
#include "data.h"
#include "memory.h"
#include "misc.h"
#include "writfile.h"

/******************************************************************************/

EXPORT void wr_s  (s) char *s; {wf_wr(&f_s,s);}
EXPORT void wr_j  (s) char *s; {wf_wr(&f_j,s);}
EXPORT void wr_l  (s) char *s; {wf_wr(&f_l,s);}

EXPORT void wl_s  (s) char *s; {wf_wr(&f_s,s); wf_wr(&f_s,"\n");}
EXPORT void wl_j  (s) char *s; {wf_wr(&f_j,s); wf_wr(&f_j,"\n");}
EXPORT void wl_l  (s) char *s; {wf_wr(&f_l,s); wf_wr(&f_l,"\n");}

EXPORT void wr_sj (s) char *s; {wr_s(s); wr_j(s);}
EXPORT void wl_sj (s) char *s; {wl_s(s); wl_j(s);}

EXPORT void wr_sjl(s) char *s; {wr_s(s); wr_j(s); wr_l(s);}
EXPORT void wl_sjl(s) char *s; {wl_s(s); wl_j(s); wl_l(s);}

/******************************************************************************/

EXPORT char *chabbrev(ch)
int ch;
{
 switch (ch)
   {
    case  0: return "NUL";
    case  1: return "SOH";
    case  2: return "STX";
    case  3: return "ETX";
    case  4: return "EOT";
    case  5: return "ENQ";
    case  6: return "ACK";
    case  7: return "BEL";
    case  8: return  "BS";
    case  9: return  "HT";
    case 10: return  "LF";
    case 11: return  "VT";
    case 12: return  "FF";
    case 13: return  "CR";
    case 14: return  "SO";
    case 15: return  "SI";
    case 16: return "DLE";
    case 17: return "DC1";
    case 18: return "DC2";
    case 19: return "DC3";
    case 20: return "DC4";
    case 21: return "NAK";
    case 22: return "SYN";
    case 23: return "ETB";
    case 24: return "CAN";
    case 25: return  "EM";
    case 26: return "SUB";
    case 27: return "ESC";
    case 28: return  "FS";
    case 29: return  "GS";
    case 30: return  "RS";
    case 31: return  "US";
    case 127:return "DEL";
    default: return    "";
   }
}

/******************************************************************************/

EXPORT sign signof(n)
long n;
{
 if (n<0) return -1;
 if (n>0) return  1;
 return 0;
}

/******************************************************************************/

EXPORT char * eq_files(name1,name2,p_result)
char *name1;
char *name2;
bool *p_result;
{
 FILE *file1;
 FILE *file2;

 /* The following three lines define two comparison buffers. The next part of */
 /* the two files being compared are read into these buffers and compared.    */
 /* Using the buffers allows bulk reads, which speeds things up considerably. */
#define CMPBUFSIZ 16384
 STAVAR ubyte_ *buf1 = NULL;
 STAVAR ubyte_ *buf2 = NULL;

 /* Set the default result to be FALSE (no match). */
 *p_result=FALSE;

 /* Allocate the comparison buffers if they are not already allocated. */
 if (buf1 == NULL)
   {
    buf1=(ubyte_ *) mm_perm((size_t) CMPBUFSIZ);
    buf2=(ubyte_ *) mm_perm((size_t) CMPBUFSIZ);
   }

 /* Open, for binary reading, the two files to be compared. */
 file1=fopen(name1,"rb");
 if (file1 == FOPEN_F)
    return "Error opening the first file.";
 file2=fopen(name2,"rb");
 if (file2 == FOPEN_F)
   {fclose(file1);return "Error opening the second file.";}

 while (TRUE)
   { /* Compare a chunk. */
    size_t len1;
    size_t len2;

    /* Read a chunk from each file. */
    len1=fread(buf1,(size_t) 1,(size_t) CMPBUFSIZ,file1);
    len2=fread(buf2,(size_t) 1,(size_t) CMPBUFSIZ,file2);
    if (ferror(file1))
       return "Compare: Error reading the first file.";
    if (ferror(file2))
       return "Compare: Error reading the second file.";

    /* Compare the two chunks. */
    if (len1 != len2)                                           break;
    if (len1 ==    0)                         {*p_result=TRUE;  break;}
    if (memcmp(buf1,buf2,(size_t) len1) != 0)                   break;
   }

 if (fclose(file1) == FCLOSE_F)
    {*p_result=FALSE; return "Error closing the first file.";}
 if (fclose(file2) == FCLOSE_F)
    {*p_result=FALSE; return "Error closing the second file.";}

 /* If we have reached this point, we can be sure that no errors occurred. */
 return NULL;
}

/******************************************************************************/

EXPORT bool fexists(fn)
char *fn;
{
 FILE *file;
 bool success;

 file=fopen(fn,"rb");
 if (file==NULL)
    return FALSE;

 success= (fclose(file) != FCLOSE_F);
 as_cold(success,
         "fexists: Error closing file whose existence is being tested!");

 return TRUE;
}

/******************************************************************************/

EXPORT char *fn_temp()
{
 STAVAR uword filnum=1;
 STAVAR fn_t  fn;
 do
   {
    sprintf(fn,"fwtf%04lu.tmp",(ulong) filnum);
    filnum++;
   }
 while (fexists(fn));
 return fn;
}

/******************************************************************************/

EXPORT void strupper(s)
char *s;
{
 while (*s != EOS)
   {
    *s=toupper(*s);
    s++;
   }
}

/******************************************************************************/
/*                                End of MISC.C                               */
/******************************************************************************/

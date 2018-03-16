static char RCSid[] = "$Id: lister.c,v 1.9 2009/09/10 16:49:46 profw Exp $";
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
   22-Jul-1992  AMS  Added function to perform special format output for
                     listing.
   26-Jul-1992  AMS  Added RCS id.
   09-Nov-1992  AMS  Output lr_mes calls as ERRORS rather than NOTES.
   15-Jun-1999	WMW  Changed maximum number of input lines to 65000

##############################################################################*/


/******************************************************************************/
/*                                    LISTER.C                                */
/******************************************************************************/

#include "style.h"

#include "as.h"
#include "data.h"
#include "list.h"
#include "lister.h"
#include "machin.h"
#include "misc.h"
#include "table.h"
#include "writfile.h"

/******************************************************************************/

#define LISTWIDTH     80  /* Nominal width of listing file. Can be wider.     */
#define INDENTQ        3  /* Indentation quantum for include files.           */
#define MESSMAXCH    200  /* Maximum number of characters in a message.       */
#define CTXINF       100  /* Special value that signals infinite context.     */
#define MAXLINES   65000  /* Maximum number of lines in input file.           */

/******************************************************************************/

/* The following #defines and typedef define an enumerated type for message   */
/* kinds. There are four kinds of message, and we need a type for storing     */
/* this information. mess_k_t stands for message_kind_type.                   */
/* We use #defines instead of enums as enums are not portable enough.         */
#define MESS_MES 1
#define MESS_WAR 2
#define MESS_ERR 3
#define MESS_SEV 4
typedef ubyte mess_k_t;

/* We wish to store messages in a table with message positions as keys.       */
/* However, the table package will not tolerate duplicate keys. To solve this */
/* problem, we create a new type 'unqpos_t' (unique position type) which has  */
/* not only a position but a serial number as well.                           */
typedef struct
  {
   ps_t  up_pos;
   ulong up_serial;
  } unqpos_t;

/* The following structure stores a single message. As we are storing COPIES  */
/* of the messages, we impose a maximum limit (MESSMAXCH) to their length.    */
typedef struct
  {
   mess_k_t ms_kind;
   char     ms_text[MESSMAXCH+1];
  } mess_t;

/******************************************************************************/

LOCVAR p_tb_t p_msgtab;           /* The message table storing diagnostics.   */
LOCVAR ulong  serial_next;        /* Serial number for numbering messages.    */

/******************************************************************************/

LOCAL int cmpuqpos P_((unqpos_t *,unqpos_t *));
LOCAL int cmpuqpos(p1,p2)
/* Compare two unique positions for the table package and returns [-1,0,1].   */
unqpos_t *p1;
unqpos_t *p2;
{
 long  diff;
 ubyte i;

 for (i=1; i<=3; i++)
   {
    switch (i)
      {
       case 1: diff= p1->up_pos.ps_line   - p2->up_pos.ps_line;   break;
       case 2: diff= p1->up_pos.ps_column - p2->up_pos.ps_column; break;
       case 3: diff= p1->up_serial        - p2->up_serial;  break;
       default: as_bomb("cmpuqpos: Case defaulted.");
      }
    if (diff<0)
       return -1;
    else
       if (diff>0)
          return 1;
   }
 return 0;
}

/******************************************************************************/

/* Converts a value of message kind type into a representative string. */
/* This routine unused at present.
LOCAL char *mess_let P_((mess_k_t));
LOCAL char *mess_let (mess_k)
mess_k_t mess_k;
{
 switch (mess_k)
   {
    case MESS_MES : return "M";
    case MESS_WAR : return "W";
    case MESS_ERR : return "E";
    case MESS_SEV : return "S";
    default: as_bomb("mess_let: Case defaulted.");
   }
 as_bomb("mess_let: Switch dropped out.");
 return "Failure";
}
*/

/******************************************************************************/

#define DUPMAX 200

LOCAL char *dup P_((int,uword));
LOCAL char *dup(ch,count)
/* Returns a pointer to a STAVAR string containing 'count' copies of 'ch'.    */
/* Count must be in the range [0,DUPMAX]. The pointer returned always points  */
/* to the same address which is a 'STAVAR' inside this function.              */
int   ch;
uword count;
{
 STAVAR char buffer[DUPMAX+1];

 as_cold(count<DUPMAX,"lister.dup: count>=DUPMAX");
 /* The IF in the following is just in case 'memset' is brain damaged. */
 if (count>0) memset(&buffer[0],ch,(size_t) count);
 buffer[count]=EOS;
 return &buffer[0];
}

/******************************************************************************/

LOCAL void mess_wri P_((p_wf_t,mess_t *,uword,uword));
LOCAL void mess_wri(p_wf,p_mess,indent,column)
/* Writes message p_mess to file p_wf indented by INDENTQ*indent+column.      */
p_wf_t p_wf;
mess_t *p_mess;
uword  indent;
uword  column;
{
 switch (p_mess->ms_kind)
   {
    case MESS_MES : wf_wr(p_wf,"            "); break;
    case MESS_WAR : wf_wr(p_wf,"     Warning"); break;
    case MESS_ERR : wf_wr(p_wf,"       Error"); break;
    case MESS_SEV : wf_wr(p_wf,"      Severe"); break;
    default: as_bomb("mess_let: Case defaulted.");
   }
 wf_wr(p_wf,"|.");
 wf_wr(p_wf,dup('.',indent*INDENTQ));
 wf_wr(p_wf,dup('.',column-1));
 wf_wr(p_wf,"^");
 wf_wr(p_wf,&p_mess->ms_text[0]);
 wf_wr(p_wf,"\n");
}

/******************************************************************************/

LOCAL void line_wri P_((p_wf_t,ln_t *));
LOCAL void line_wri(p_wf,p_line)
/* Writes the given line to the given output stream. */
p_wf_t  p_wf;
ln_t   *p_line;
{
 char buffer[100];

 /* The last line of the line list is the EOF marker line and to indicate     */
 /* that it is not really part of the input file, we omit it's line number.   */
 if (p_line->ln_global==ls_len(line_list))
                 /*" 12345 12345| "*/
    sprintf(buffer,"            | ");
 else
    sprintf(buffer," %5lu %5lu| ",
                   (unsigned long) p_line->ln_global,
                   (unsigned long) p_line->ln_local);
 wf_wr(p_wf,buffer);
 wf_blk(p_wf,p_line->ln_body.sc_first,(size_t)
     (p_line->ln_body.sc_last-p_line->ln_body.sc_first+1));
}

/******************************************************************************/

LOCAL void add_mess P_((ps_t *,mess_k_t,char *));
LOCAL void add_mess(p_pos,messkind,p_string)
/* Creates a message record and places the message information in the         */
/* argument into the record. Inserts the record into the message table.       */
ps_t      *p_pos;
mess_k_t   messkind;
char      *p_string;
{
 mess_t   tempmess;
 unqpos_t unqpos;

 tempmess.ms_kind=messkind;
#if defined(__cplusplus) || defined(__STDC__)
 as_cold(strlen(p_string)<=(size_t)MESSMAXCH,
         "lister.add_mess: Parameter message is too long.");
#else
 as_cold(strlen(p_string)<=MESSMAXCH,
         "lister.add_mess: Parameter message is too long.");
#endif
 strcpy(tempmess.ms_text,p_string);
 ASSIGN(unqpos.up_pos,*p_pos);
 unqpos.up_serial=serial_next++;
 tb_ins(p_msgtab,PV &unqpos,PV &tempmess);
}

/******************************************************************************/

EXPORT void lr_ini P_((void))
{
 /* Create a brand new empty message table. */
 p_msgtab=tb_cre(sizeof(unqpos_t),sizeof(mess_t),(p_kycm_t) cmpuqpos);

 /* Start the serial numbers at zero again. */
 serial_next=0;
}

/******************************************************************************/

EXPORT void lr_mes(p_pos,s)
ps_t *p_pos;
char *s;
{
 add_mess(p_pos,MESS_MES,s);
}

/******************************************************************************/

EXPORT void lr_war(p_pos,s)
ps_t *p_pos;
char *s;
{
 add_mess(p_pos,MESS_WAR,s);
 num_war++;
}

/******************************************************************************/

EXPORT void lr_err(p_pos,s)
ps_t *p_pos;
char *s;
{
 add_mess(p_pos,MESS_ERR,s);
 num_err++;
}

/******************************************************************************/

EXPORT void lr_sev(p_pos,s)
ps_t *p_pos;
char *s;
{
 add_mess(p_pos,MESS_SEV,s);
 num_sev++;
}

/******************************************************************************/

EXPORT void lr_gen(p_wf,ctx)
p_wf_t p_wf;
uword  ctx;
{
 unqpos_t next_pos; /* Position of next message.                              */
 mess_t   next_mes; /* Content  of next message.                              */
 long     prev_no;  /* Global line number of previous message.                */
 long     next_no;  /* Global line number of next     message.                */
 bool     ingap;    /* Controls issuance of gap markers in the listing.       */
 long     context=ctx; /* Signed version of the parameter.                    */

 /* A context of CTXINF signals an infinite context. */
 if (context==CTXINF) context=MAXLINES;

 /* Write listing header. */
 wf_wr(p_wf,"\nGlobal Local| Input File\n");
 wf_wr(p_wf,dup('-',12));wf_wr(p_wf,"+");
 wf_wr(p_wf,dup('-',LISTWIDTH-13));wf_wr(p_wf,"\n");

 /* Reset the line list and message table for reading. */
 ls_fir(line_list);
 tb_fir(p_msgtab);

 /* Prime the variables ingap, prev_no, next_no, next_pos, and next_mes. */
 ingap=FALSE; prev_no = -(context+1);
 if (tb_rea(p_msgtab,PV &next_pos,PV &next_mes))
    next_no=next_pos.up_pos.ps_line;
 else
    next_no=MAXLINES+context+1;

 while (TRUE)
   {/* Process a single line per iteration. */
    ln_t *p_line;

    /* Grab the next line from the line list. */
    ls_nxt(line_list,PPV &p_line);
    if (p_line==NULL) break;

    /* List the line if it is within context range of prev or next message. */
    if ((((long) p_line->ln_global) <= prev_no+context) ||
        (((long) p_line->ln_global) >= next_no-context))
       {line_wri(p_wf,p_line);ingap=FALSE;}
    else
       if (!ingap)
          {wf_wr(p_wf,".................\n");ingap=TRUE;}

    /* Issue any messages that are about this line. */
    while (next_no == p_line->ln_global)
      {
       /* Write the current message. */
       mess_wri(p_wf,&next_mes,(uword) 0,
                (uword) next_pos.up_pos.ps_column);
                
       /* Read the next message from the table. */
       prev_no=next_no;
       if (tb_rea(p_msgtab,PV &next_pos,PV &next_mes))
          next_no=next_pos.up_pos.ps_line;
       else
          next_no=MAXLINES+context+1;
      }
   } /* End while */

 /* Make sure that we have read to the end of the message table. */
 {bool result;
  result=tb_rea(p_msgtab,PV &next_pos,PV &next_mes);
  as_cold(!result,
          "lr_gen: Messages remaining in message table after listing.");
 }

 /* Write listing trailer. */
 wf_wr(p_wf,dup('-',12));wf_wr(p_wf,"+");
 wf_wr(p_wf,dup('-',LISTWIDTH-13));wf_wr(p_wf,"\n");
 wf_wl(p_wf,"");
}

EXPORT void lr_gen_unix(p_wf,ctx)
p_wf_t p_wf;
uword  ctx;
{
 unqpos_t next_pos; /* Position of next message. */
 mess_t   next_mes; /* Content  of next message. */
 long     next_no;  /* Global line number of next message. */
 char buffer[32];

 /* Reset the line and message table for reading. */
 ls_fir(line_list);
 tb_fir(p_msgtab);

 if (tb_rea(p_msgtab,PV &next_pos,PV &next_mes))
    next_no=next_pos.up_pos.ps_line;
 else
    next_no=MAXLINES+1;

 while (TRUE)
   {
    ln_t *p_line;

    ls_nxt(line_list,PPV &p_line);
    if (p_line==NULL) break;
    
    while (next_no == p_line->ln_global)
      {
       wf_wr(p_wf,"\"");
       wf_wr(p_wf,p_line->ln_filename);
       wf_wr(p_wf,"\", ");
       wf_wr(p_wf,"line ");
       sprintf(buffer,"%lu",p_line->ln_local);
       wf_wr(p_wf,buffer);
       wf_wr(p_wf,":");
       sprintf(buffer,"%lu",next_pos.up_pos.ps_column);
       wf_wr(p_wf,buffer);
       switch (next_mes.ms_kind)
         {
          case MESS_MES : wf_wr(p_wf," ERROR"); break;
	  case MESS_WAR : wf_wr(p_wf," WARNING"); break;
	  case MESS_ERR : wf_wr(p_wf," ERROR"); break;
	  case MESS_SEV : wf_wr(p_wf," DEADLY"); break;
	  default: as_bomb("lr_gen_unix: Case defaulted.");
	  }
       wf_wr(p_wf,": ");
       wf_wr(p_wf,&next_mes.ms_text[0]);
       wf_wr(p_wf,"\n");

       /* Read the next message from the table. */
       if (tb_rea(p_msgtab,PV &next_pos,PV &next_mes))
          next_no=next_pos.up_pos.ps_line;
       else
          next_no=MAXLINES+1;
      }
   }

 /* Make sure that we have read to the end of the message table. */
 {bool result;
  result=tb_rea(p_msgtab,PV &next_pos,PV &next_mes);
  as_cold(!result,
          "lr_gen_unix: Messages remaining in message table after listing.");
 }
}

/******************************************************************************/
/*                               End of LISTER.C                              */
/******************************************************************************/

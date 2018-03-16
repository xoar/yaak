static char RCSid[] = "$Id: scanner.c,v 1.17 2013/11/09 21:05:52 profw Exp $";
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
   WMW  William Waite     William.Waite@Colorado.edu

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.
   22-Jul-1992  AMS  Added code to remember the filename when we're scanning.
   26-Jul-1992  AMS  Set local line numbers.
   26-Jul-1992  AMS  Added RCS id.
   03-Aug-1992  AMS  Allow "@p typesetter = texinfo".
   18-Dec-1992  WMW  Cast the results of mm_temp to avoid pointer
                     incompatibility.
   01-Apr-1993  AMS  Removed warning about trailing spaces on lines.
   20-Nov-1995	WMW  Allow "@p typesetter = html".
   06-Aug-1997	WMW  Add non-product files
   01-May-1998	WMW  Add typesetters LATEX and LATEX2HTML
   09-Nov-2013  WMW  Corrections for a finicky C compiler

##############################################################################*/


/******************************************************************************/
/*                                   SCANNER.C                                */
/******************************************************************************/
/*                                                                            */
/* Introduction                                                               */
/* ------------                                                               */
/* The FunnelWeb scanner is a little messy because it deals with two          */
/* structures at the same time while attempting to be efficient. On the one   */
/* hand it is busy constructing the line list. This means that it has to keep */
/* an eye out for end of line characters ('\n'=EOL) so that it can add a line */
/* record whenever it sees one. On the other hand, it has to scan the input   */
/* file into a token stream consisting of text tokens and special tokens      */
/* which usually have no regard for end of lines. It is tempting to divide    */
/* these two functions up (into perhaps a LINER and a TOKENIZER). However,    */
/* the presence of the include file facility would make this messy. Also, the */
/* tokenizer has to count end of line markers so that it can generate         */
/* correctly positioned diagnostics.                                          */
/*                                                                            */
/* The long and short of it all is that the best way to do the scanning seems */
/* to be to run a liner and a tokenizer as parallel layers. The liner         */
/* extracts characters from the input file and hands them to the tokenizer.   */
/* It also keeps an eye out for newline characters, sending a line record off */
/* whenever it sees one, and counting lines. The tokenizer receives the       */
/* characters from the liner and performs the tokenize operation.             */
/*                                                                            */
/* Notes                                                                      */
/* -----                                                                      */
/* - Currently FunnelWeb recognises only two characters as whitespace.        */
/*   These are ' ' and EOL.                                                   */
/*                                                                            */
/******************************************************************************/

#include <ctype.h>
#include <limits.h>
#include "style.h"

#include "as.h"
#include "clock.h"
#include "data.h"
#include "dump.h"
#include "list.h"
#include "lister.h"
#include "machin.h"
#include "mapper.h"
#include "memory.h"
#include "misc.h"
#include "option.h"
#include "scanner.h"

/******************************************************************************/

/* The "special" character is the character that is used to introduce a       */
/* "special sequence". FunnelWeb allows the user to change this character so  */
/* as to cater for documents where the "default" character is common. This    */
/* definition defines what the default character is.                          */
#define CH_DSPE ('@')

/* FunnelWeb allows include files which are handled by the scanner by placing */
/* recursive calls to scan_file. A maximum is placed on the level of nested   */
/* includes. This acts as a good sanity check as well as catching recursive   */
/* include files which are never a sensible construct in FunnelWeb as         */
/* FunnelWeb does not provide any conditional construct.                      */
#define MAX_INCL (10)

/* FunnelWeb is very conservative about what characters it will allow in its  */
/* input and output files. Currently the only characters allowed are          */
/* printables and end of lines. When FunnelWeb does spot an illegal character */
/* it needs to be able to draw the user's attention to the character. The     */
/* best way to do this is to point to it in the listing file. However, if the */
/* character is banned, it cannot appear in the listing file! The problem is  */
/* solved by having the scanner replace all illegal characters in each mapped */
/* file by the following character. This eliminates further problems.         */
#define CENSORCH ('?')

/* Following the Unix convention, mapped in files are not terminated with an  */
/* end-of-file character. However, the presence of such a character at the    */
/* end of the mapped file simplifies scanning and so we add one. This         */
/* definition defines what the character is to be. It doesn't matter what the */
/* character is, so long as it cannot legally appear in the file. A control   */
/* character is a good choice as these are filtered out by the liner (see     */
/* above).                                                                    */
/* We undef EOF (from <stdio.h>) because it is too dangerously close to EOFCH.*/
/* (EOF wasn't redefined as that might confuse readers used to <stdio.h>.     */
/* However, we still use EOF as an acronym for End Of File.                   */
#define EOFCH (26)
/*
  Don't undefine this since we don't need to and it generates warnings with
  some ANSI C compilers because EOF is an ANSI standard library macro.
#undef EOF
*/

/* Tokens have a field for a general attribute which has meaning for some     */
/* token kinds. For other kinds, it has no meaning. This constant is used to  */
/* indicate a "don't care" value.                                             */
#define DONTCARE 0

/* A nominal maximum value for the maximum length of an input line.           */
#define INMAXINF (ULONG_MAX)

/******************************************************************************/

/* The following type is used in the suite of pragma routines for parsing.    */
typedef
   struct
     {
      ps_t  pt_ps;    /* Position of the start of this argument.              */
      char *pt_pstr;  /* Pointer to a string containing the argument.         */
      char *pt_pinl;  /* Pointer to first byte of the argument in commndline. */
     } pt_t;
typedef pt_t *p_pt_t;

/******************************************************************************/

                        /* Variables Instantiated Over The Entire Scan        */
                        /* -------------------------------------------        */
LOCVAR p_ck_t p_mapp;   /* Pointer to mapper's clock.                         */
LOCVAR p_ck_t p_scan;   /* Pointer to scanner's clock.                        */
LOCVAR ulong globalno;  /* Global line number of line being scanned.          */
LOCVAR ulong inclevel;  /* Include level of current file. Top file is zero.   */
LOCVAR bool  seenind;   /* TRUE iff we have seen an indentation pragma.       */
LOCVAR ps_t  ps_ind;    /* seenind==TRUE => ps_ind is position of pragma.     */
LOCVAR bool  seentyp;   /* TRUE iff we have seen a typesetter pragma.         */
LOCVAR ps_t  ps_typ;    /* seentyp==TRUE => ps_typ is position of pragma.     */
LOCVAR bool  seenlimo;  /* TRUE iff we have seen an out lin len limit pragma. */
LOCVAR ps_t  ps_limo;   /* seenlimo==TRUE => ps_limo is position of pragma.   */

                        /* Variables Instantiated Over The Current File       */
                        /* --------------------------------------------       */
LOCVAR ulong inln_max;  /* Maximum permitted length of an input line.         */
LOCVAR char  specialch; /* Current special (escape) character.                */
LOCVAR char  *p_eof;    /* Pointer to EOFCH byte at the end of current file.  */
LOCVAR ulong  localno;  /* Local line number of line being scanned.           */

                        /* Variables Instantiated Over The Current Line       */
                        /* --------------------------------------------       */
LOCVAR char  *p_sol;    /* Pointer to Start (first char) Of current Line.     */
LOCVAR char  *p_ch;     /* Pointer to current character in current line.      */
LOCVAR char   ch;       /* *p_ch.                                             */

/******************************************************************************/
/*                          Line Processing Layer                             */
/******************************************************************************/
/*                                                                            */
/* This mini-section contains the two routines (prepline and NEXTCH) that     */
/* take care of the line based-scanning and feed characters to the            */
/* token-based scanner routines which have the top level of control.          */
/* After mapping in a file to be read, place a call to prepline passing the   */
/* address of the first byte of the mapped file as an argument. At that       */
/* point the current position will be the first byte on the first line and    */
/* the "variables instantiated over the current line" will be well defined.   */
/* Calls to NEXTCH then move the position through the mapped file one byte at */
/* a time, stopping at the end of file at which point calls will not move the */
/* marker which will point to the EOF character.                              */
/*                                                                            */
/******************************************************************************/

LOCAL void prepline P_((char *));
LOCAL void prepline(p_line)
/* This function should be called at the end of each line to prepare the next */
/* line for scanning. The user of the liner mini-package should place a       */
/* single call to this function at the start of scanning a mapped file.       */
/* The user should then place calls to NEXTCH (which calls prepline when      */
/* necessary).                                                                */
/* This function serves two purposes:                                         */
/*    1. It looks at the next line and converts all non-printables into       */
/*       CENSORCH and issues errors for each non-printable.                   */
/*    2. It initializes the line scanning variables for the next line.        */
/* The argument is a pointer to the first byte of the next line.              */
char *p_line;
{
 char *p;  /* Scans through the line and winds up sitting on the EOL.         */

 /* Test to see if the "line" we have been given is the end of file marker.   */
 /* We have to be careful here because the byte we are using to mark the end  */
 /* of file could appear as an illegal unprintable. This is the reason for    */
 /* the test p_line==p_eof.                                                   */
 if (*p_line==EOFCH && p_line==p_eof)
   {
    /* The line we have to process is in fact the end of file marker. */
    p_sol = p_line;
    p_ch  = p_line;
    ch    = EOFCH;
    return;
   }

 /* At this point we know that we are faced with a run of bytes terminated by */
 /* an EOL character (we know this cos we put an EOL before EOF earlier on).  */
 /* We know that we have a line, so we can now bump up the line counters.     */
 globalno++;
 localno++;

 /* Run through the line checking for non-printables and issuing errors.      */
 p = p_line;
 while (*p != EOL)
    {
     /* The following test tests to see if the character is a printable in    */
     /* seven bit ascii. FunnelWeb is not currently designed to work with     */
     /* any character set other than seven-bit ascii and so we flag and       */
     /* convert all out-of-range characters here before they are exposed to   */
     /* the rest of the scanner code which assumes that each line that it is  */
     /* handed consists entirely of printables except for the EOL char on the */
     /* end and possibly an EOF char at the "Start" of a line.                */
     /* In particular, the NEXTCH macro will fail on machines with siged     */
     /* chars if non-printables are not removed. It goes into an infinite     */
     /* loop.                                                                 */
     /* Note: I don't use library function "isprint" here because on the vax  */
     /* it's definition is too loose (seems to accept characters with the top */
     /* bit set as printable).                                                */
     if (!isascprn(*p))  /* If not a printable character. */
       {
        ps_t ps;
        char c = *p;
        ubyte_ uc = *((ubyte_ *) p);
	ps.ps_filename = filename;
        ps.ps_line     = globalno;
        ps.ps_locline  = localno;
        ps.ps_column   = p-p_line+1;
        if (strlen(chabbrev(c))==0)
           sprintf(linet1,
              "Non printable character (Sym=<none>, Dec=%03u, Hex=%02X, Oct=%03o).",
              (unsigned) uc,(unsigned) uc,(unsigned) uc);
        else
           sprintf(linet1,
              "Non printable character (Sym=%s, Dec=%03u, Hex=%02X, Oct=%03o).",
                   chabbrev(c),(unsigned) uc,(unsigned) uc,(unsigned) uc);
        lr_err(&ps,linet1);
        *p=CENSORCH;
       }
     p++;
    }
 /* Assert: p_line points to the start of the current line.     */
 /* Assert: p points to the EOL at the end of the current line. */

 /* Check that the line is not too long. */
 if ((p-p_line)>inln_max)
   {
    ps_t ps;
    ps.ps_filename = filename;
    ps.ps_line     = globalno;
    ps.ps_locline  = localno;
    ps.ps_column   = inln_max+1;
    lr_err(&ps,"Input line is too long (this character is the first offender).");
    sprintf(linet1,"Currently, the maximum allowable input line length is %lu.",
                   (unsigned long) inln_max);
    lr_mes(&ps,linet1);
    lr_mes(&ps,"Note: You can change this using a pragma directive (@p).");
   }

#ifdef NOTDEF
 /* Now check for trailing spaces. */
 if ((p != p_line) && (*(p-1) == ' '))
   {
    ps_t ps;
    ps.ps_filename = filename;
    ps.ps_line     = globalno;
    ps.ps_locline  = localno;
    ps.ps_column   = p-p_line;
    lr_war(&ps,"Line has trailing spaces up to and including this space.");
   }
#endif

 /* Construct a line record and append the record to the line list. */
 /* Note that the line scrap encompasses the trailing EOL.          */
 {
  ln_t line;
  line.ln_filename	= filename;
  line.ln_global        = globalno;
  line.ln_local         = localno;
  line.ln_body.sc_first = p_line;
  line.ln_body.sc_last  = p;
  /* Note: We do not set sc_white as it is not used in lines. */
  ls_add(line_list,PV &line);
 }

 /* Finally, set the line scanning variables to the start of the line. */
 /* We can't do this earlier in case the start of the line was a       */
 /* non-printable and got substituted (ch might pick it up).           */
 p_sol =  p_line;
 p_ch  =  p_line;
 ch    = *p_line;

} /* End of prepline. */

/* NEXTCH can be called continuously after an initializing call to prepline.  */
/* After a call to NEXTCH, p_sol, p_ch, ch are all well-defined. p_sol points */
/* to the start of the current line, p_ch points to the current character,    */
/* and ch contains *p_ch. NEXTCH can be called repeatedly forever. When it    */
/* hits the EOF character, it sticks on it and returns it forever.            */
/* Note: The "ch<' '" is an optimized form of "(ch==EOL)||(ch=EOFCH)". Speed  */
/* is very important here as this macro is called in scanning tightloops.     */
/* This line of code is a little tricky so read it carefully.                 */
/* WARNING: The ch<' ' will cause an infinite loop if a character appears     */
/* that satisfies this condition without being EOF or EOL (e.g. a control     */
/* char (meant to be filtered out earlier) or a top-bit-set character on      */
/* machines with signed character type.                                       */
#define NEXTCH {if (ch<' ') {if (ch==EOL) prepline(p_ch+1);} else ch= *++p_ch;}

/******************************************************************************/
/*                           Scanner Support Routines                         */
/******************************************************************************/

LOCAL ps_t *psofch P_((void));
LOCAL ps_t *psofch()
/* Returns a pointer to an internal static ps structure holding the line and  */
/* column number of the current character ch.                                 */
{
 STAVAR ps_t chps;
 chps.ps_filename = filename;
 chps.ps_line     = globalno;
 chps.ps_locline  = localno;
 chps.ps_column   = p_ch-p_sol+1;
 return &chps;
}

/******************************************************************************/

LOCAL void grabchps P_((p_ps_t));
LOCAL void grabchps(p_ps)
/* Writes the position of the current ch into the argument position struct.   */
p_ps_t p_ps;
{
 p_ps->ps_filename = filename;
 p_ps->ps_line     = globalno;
 p_ps->ps_locline  = localno;
 p_ps->ps_column   = p_ch-p_sol+1;
}

/******************************************************************************/

LOCAL void sendspec P_((p_ps_t,tk_k_t,ubyte));
LOCAL void sendspec(p_tkps,tk_kind,tk_gen)
/* Appends a non-text token of kind tk_kind to the end of the token list.     */
/* p_ps is a pointer to a position structure giving the position of the       */
/* first character of the token. tk_gen is the general token attribute.       */
p_ps_t p_tkps;
tk_k_t tk_kind;
ubyte  tk_gen;
{
 tk_t token;
 token.tk_kind        = tk_kind;
 ASSIGN(token.tk_ps,*p_tkps);
 token.tk_sc.sc_first = NULL;
 token.tk_sc.sc_last  = NULL;
 token.tk_sc.sc_white = TRUE;
 token.tk_gen         = tk_gen;
 ls_add(token_list,PV &token);
}

/******************************************************************************/

LOCAL void sendtext P_((p_ps_t,char *,char *,bool));
LOCAL void sendtext(p_tkps,p_first,p_last,is_white)
/* Appends a text token to the end of the token list.                         */
/* IN: p_ps is a pointer to a position structure giving the position of the   */
/*     first character of the token.                                          */
/* IN: p_first and p_last point to the first and last byte of the text scrap. */
/* IN: is_white should be set to TRUE iff scrap is entirely whitespace.       */
p_ps_t p_tkps;
char  *p_first;
char  *p_last;
bool   is_white;
{
 tk_t token;

 /* Empty text scraps should never be generated. */
 as_cold(p_first<=p_last,"sendtext: Text scrap bounds are bad.");

 /* If ch=EOL then we should be scanning more text, not shipping it! */
 as_cold(ch!=EOL,"senttext: Shipping text while still more to scan.");

 /* Send the text token. */
 token.tk_kind        = TK_TEXT;
 ASSIGN(token.tk_ps,*p_tkps);
 token.tk_sc.sc_first = p_first;
 token.tk_sc.sc_last  = p_last;
 token.tk_sc.sc_white = is_white;
 token.tk_gen         = DONTCARE;
 ls_add(token_list,PV &token);
}

/******************************************************************************/

LOCAL void add_eof P_((void));
LOCAL void add_eof()
/* This function adds terminators to the line and token list.                 */
/*    1. It adds a TK_EOF token to the end of the token list.                 */
/*    2. It adds a visible <eof> line to the end of the line list.            */
/* This assists the parser by allowing it to point diagnostic messages to a   */
/* visible EOF marker rather than pointing vaguely to the end of the last     */
/* line of the input file which (by the way) may not even exist!              */
{
 STAVAR char *eofstr = "<End-Of-File>\n";
 ln_t line;
 ps_t ps;

 /* When the liner mini package encounters an end of file marker, it stops    */
 /* dead on the marker and returns EOFCH forever. scan_file() eventually gets */
 /* the message and drops out. However, in all of this, the line numbers are  */
 /* not incremented to indicate that we have moved to an EOF line. This is    */
 /* intended, as we do not want EOFs to appear in the listing for include     */
 /* files; only at the end of the main input file. Thus, here we effectively  */
 /* perform the liner function of moving from the last line of the input file */
 /* to the imaginary line containing the EOF marker. This is done by          */
 /* incrementing the line numbers. Note that the fact that these line number  */
 /* variables are incorrect from the point of detection of the final EOF to   */
 /* here doesn't matter as no tokens or diagnostics are ever added after an   */
 /* EOF is detected.                                                          */
 globalno++;
 localno++;

 /* Add a line to represent the EOF marker. */
 line.ln_filename      = filename;
 line.ln_global        = globalno;
 line.ln_local         = localno;
 line.ln_body.sc_first = eofstr;
 line.ln_body.sc_last  = eofstr+strlen(eofstr)-1;
 /* Note: We do not set sc_white as it is not used in lines. */
 ls_add(line_list,PV &line);

 /* Add a TK_EOF token to the end of the token list. */
 ps.ps_filename = filename;
 ps.ps_line     = globalno;
 ps.ps_locline  = localno;
 ps.ps_column   = 1;
 sendspec(&ps,TK_EOF,DONTCARE);
}

/******************************************************************************/
/*                              The Scanner Proper                            */
/******************************************************************************/

LOCAL void skiptoeol P_((void));
LOCAL void skiptoeol()
{
 while (ch != EOL)
    NEXTCH;
}

/******************************************************************************/

/* The incl_fil function calls this, so we have to declare it in advance. */
LOCAL void scan_file P_((char *));

LOCAL void incl_fil P_((p_ps_t));
LOCAL void incl_fil(p_ps)
/* Upon entry, the current character is the "i" of an "@i" sequence. Our task */
/* is first to see if the sequence occurred at the start of a line (the only  */
/* point at which it is legal) and issue an error if it isn't. If it is legal,*/
/* we have to read in the specified file and scan that. The included file     */
/* replaces exactly the line starting with the "@i" command and we return     */
/* to the "calling" file with the current position being the EOL character of */
/* the include line.                                                          */
p_ps_t p_ps;
{
 /* Complain if the include directive was not at the start of a line. */
 if (p_ch-1 != p_sol)
   {
    lr_err(p_ps,"Include sequence must be at the beginning of a line.");
    lr_mes(p_ps,"Include ignored.");
    skiptoeol();
    return;
   }

 /* The include command should be followed by a blank. Get the next char. */
 NEXTCH;

 /* Complain if the next character is not a blank. */
 if (ch != ' ')
   {
    ps_t ps;
    ASSIGN(ps,*p_ps);
    ps.ps_column+=2;
    lr_err(&ps,"Include sequence (@i) must be followed by a blank.");
    lr_mes(&ps,"Example include: @i macros.fwi");
    lr_mes(&ps,"Include ignored.");
    skiptoeol();
    return;
   }

 /* Complain if the include level is too high. */
 if (inclevel == MAX_INCL)
   {
    lr_err(p_ps,"This include file is nested too deeply. It's probably recursive.");
    sprintf(linet1,"The maximum level of nested includes is %u.",
                   (unsigned) MAX_INCL);
    lr_mes(p_ps,linet1);
    lr_mes(p_ps,"Include ignored.");
    skiptoeol();
    return;
   }

 {/* This construct does the work of the include.                 */
  /* Warning: The following variables MUST be declared automatic. */
  char   *p_filename;
  char   *p_tempname;
  ulong  length;
  char  *p;
  ulong xinln_max;
  char  xspecial;
  char  *xp_eof;
  ulong  xlocalno;
  char  *xp_sol;
  char  *xp_ch;
  char   xch;
  p_fn_t xfilename;

  /* We save stack space by sticking this filename in the heap. */
  p_filename=(char *)mm_temp((size_t) FILENAME_MAX+1+10); /* 10 is for paranoia. */
  p_tempname=(char *)mm_temp((size_t) FILENAME_MAX+1+10); /* 10 is for paranoia. */

  /* The rest of the line is supposed to hold a filename. Copy it. */
  NEXTCH;
  p=p_tempname;
  length=0;
  while (ch!=EOL)
    {
     if (++length > FILENAME_MAX)
       {
        lr_err(p_ps,
        "This include command's file specification is too long.");
        if (option.op_b7_b)
           sprintf(linet1,"The maximum file name length is %s characters.",
                      SUPPVAL);
        else
           sprintf(linet1,"The maximum file name length is %u characters.",
                      (unsigned) FILENAME_MAX);
        lr_mes(p_ps,linet1);
        lr_mes(p_ps,"Include ignored.");
        skiptoeol();
        return;
       }
     *p++=ch;
     NEXTCH;
    }
  *p=EOS;
  /* Note: Current position is now on the EOL at the end of the @i line. */

  /* Complain if the user has not specified a filename. */
  if (strlen(p_tempname) ==0)
    {
     lr_err(psofch(),"Expecting the name of a file to include.");
     return;
    }

  /* Perform the necessary filename inheritance.                              */
  strcpy(p_filename,"");
  fn_ins(p_filename,option.op_f_s);
  fn_ins(p_filename,".fwi");
  fn_ins(p_filename,option.op_i_s);
  fn_ins(p_filename,p_tempname);

  /* Include the included file by calling scan_file recursively. */
  /* Save and restore all variables in instantiation scope.      */
  xinln_max = inln_max;
  xspecial  = specialch;
  xp_eof    = p_eof;
  xlocalno  = localno;
  xp_sol    = p_sol;
  xp_ch     = p_ch;
  xch       = ch;
  xfilename = filename;
  inclevel++;
  scan_file(p_filename);
  inclevel--;
  filename  = xfilename;
  ch        = xch;
  p_ch      = xp_ch;
  p_sol     = xp_sol;
  localno   = xlocalno;
  p_eof     = xp_eof;
  specialch = xspecial;
  inln_max  = xinln_max;
 }
}

/******************************************************************************/

LOCAL void do_ascii P_((p_ps_t));
LOCAL void do_ascii(p_psspec)
/* Upon entry, the current character is the '^' of a @^ sequence. The task is */
/* to parse the following ascii code and generate a text token.               */
p_ps_t p_psspec;
{
 ubyte  base;             /* Base of the number we are scanning.              */
 ubyte  digits;           /* Number of digits expected.                       */
 uword  val;              /* Value of target character.                       */
 ubyte  i;                /* Looping variable.                                */
 STAVAR char alphab[256]; /* Static alphabet array to which to point scraps.  */
 STAVAR bool init=FALSE;  /* Tells if alphab has been initialized.            */

 /* Establish an array containing the ascii character set. Later on we can    */
 /* point the sc_first and sc_last pointers to particular characters.         */
 if (!init) {uword i; for (i=0;i<256;i++) alphab[i]=(char) i; init=TRUE;}

 /* Make sure that the base character is legal. */
 NEXTCH;
 switch(toupper(ch))
   {
    case 'B': base= 2; digits=8; break;
    case 'O':
    case 'Q': base= 8; digits=3; break;
    case 'D': base=10; digits=3; break;
    case 'H':
    case 'X': base=16; digits=2; break;
    default : lr_err(psofch(),"Expecting one of 'B', 'Q', 'D', 'H'.");
              lr_mes(psofch(),"(For Binary, Octal, Decimal, and Hexadecimal).");
              base=10;
              goto trouble;
   }

 /* Parse opening parenthesis. */
 NEXTCH;
 if (ch!='(')
   {lr_err(psofch(),"Expecting '('.");goto trouble;}

 val=0;
 for (i=0;i<digits;i++)
   {
    char uch;
    ubyte d;

    NEXTCH;
    uch=toupper(ch);
    if (('0'<=uch) && (uch<='9'))
       d=uch-'0';
    else
       if ('A'<=uch && uch<='F')
          d=10+uch-'A';
       else
          d=100;
    if (d>=base)
      {lr_err(psofch(),"Illegal digit."); goto trouble;}
    val = base*val + d;
   }

 /* Parse closing parenthesis. */
 NEXTCH;
 if (ch!=')')
   {lr_err(psofch(),"Expecting ')'.");goto trouble;}

 /* Make sure that the number is not too big (this is possible in decimal). */
 if (val>255)
   {
    lr_err(psofch(),"Character number is too large.");
    lr_mes(psofch(),"Character number must be in the range [0,255] (decimal).");
    goto trouble;
   }

 /* Success! Now we can parcel it up into a scrap! */
 sendtext(p_psspec,&alphab[val],&alphab[val],ch==' ' || ch==EOL);
 return;

 trouble:
 /* Jump here after a specific diagnostic to give the user a reminder of */
 /* how to specify an ascii character constant.                          */
 switch (base)
    {
     case  2:
        lr_mes(psofch(),
        "A binary character representation takes the form \"@^B(dddddddd)\".");
        lr_mes(psofch(),
        "(exactly 8 digits) where each digit d is either 0 or 1.");
        break;
     case  8:
        lr_mes(psofch(),
        "An octal character representation takes the form \"@^Q(ddd)\" (or \"@^O(ddd)\").");
        lr_mes(psofch(),
        "(exactly 3 digits) where each digit d is in the range 0..7.");
        break;
     case 10:
        lr_mes(psofch(),
        "A decimal character representation takes the form \"@^D(ddd)\".");
        lr_mes(psofch(),
        "(exactly 3 digits) where each digit d is in the range 0..9.");
        break;
     case 16:
        lr_mes(psofch(),
        "A hexadecimal character representation takes the form \"@^X(dd)\" (or \"@^H(dd)\").");
        lr_mes(psofch(),
        "(exactly 2 digits) where each digit d is in the range 0..9,A..F.");
        break;
     default: as_bomb("do_ascii: trouble base switch defaulted.");
    }
}

/******************************************************************************/

LOCAL void do_name P_((p_ps_t));
LOCAL void do_name (p_psspec)
/* Upon entry, the current character is the # of a @#. The task is to parse   */
/* it and transmit a name token.                                              */
p_ps_t p_psspec;
{
 as_cold(ch=='#',"do_name: character is wrong.");
 NEXTCH;
 if ((ch==EOL) || (ch==' '))
    {lr_err(psofch(),"Expecting a printable character."); return;}

 /* Transmit a name token. */
 sendspec(p_psspec,TK_NAME,(ubyte) ch);
}

/******************************************************************************/

LOCAL void do_pgind P_((uword,p_pt_t));
LOCAL void do_pgind(numarg,arg)
/* Parse an indentation pragma. */
uword numarg;
p_pt_t   arg;
{
 bool pragind;
 ps_t psprag;

 /* Make sure that there are exactly three arguments. */
 if (numarg != 3)  /* "indentation"  "none|blank". */
   {
    lr_err(&arg[0].pt_ps,
           "This indentation pragma has the wrong number of arguments.");
    goto help;
   }

 /* Make sure that the second argument is an "=". */
 if (0 != strcmp(arg[2].pt_pstr,"="))
   {
    lr_err(&arg[2].pt_ps,"Expecting \"=\".");
    goto help;
   }

 /* Check the third argument. */
      if (strcmp(arg[3].pt_pstr,"none" )==0) pragind=FALSE;
 else if (strcmp(arg[3].pt_pstr,"blank")==0) pragind=TRUE;
 else
   {
    lr_err(&arg[3].pt_ps,"Expecting either \"none\" or \"blank\".");
    goto help;
   }

 /* Construct a shorthand for the start of the pragma. */
 ASSIGN(psprag,arg[0].pt_ps);

 /* Make sure that the pragma does not contradict an earlier pragma. */
 if (seenind && (tgindent!=pragind))
   {
    sprintf(linet1,"This pragma is opposed by the pragma at line %lu.",
                   (unsigned long) psprag.ps_line);
    lr_mes(&ps_ind,linet1);
    sprintf(linet1,"This pragma opposes the pragma at line %lu.",
                   (unsigned long) ps_ind.ps_line);
    lr_err(&psprag,linet1);
    lr_mes(&psprag,"You can have as many indentation pragmas as you like,");
    lr_mes(&psprag,"but they all have to be the same!");
    lr_mes(&psprag,"Pragma ignored.");
    return;
   }

 /* Success: Record the pragma information. */
 seenind  = TRUE;       /* Record that we have seen a pragma. */
 tgindent = pragind;    /* Record what the pragma said.       */
 ASSIGN(ps_ind,psprag); /* Record where the pragma was.       */
 return;

 help:
    lr_mes(&arg[0].pt_ps,
           "The correct format is: \"@p indentation = none|blank\".");
    lr_mes(&arg[0].pt_ps,"Pragma ignored.");
    return;
}

/******************************************************************************/

LOCAL void do_pginl P_((uword,p_pt_t));
LOCAL void do_pginl(numarg,arg)
/* Parse a maximum input line length pragma. */
uword numarg;
p_pt_t   arg;
{
 char  *numstr;
 uword spn;

 /* Make sure that there are exactly three arguments. */
 if (numarg != 3)  /* "max..length = <num>". */
   {
    lr_err(&arg[0].pt_ps,"This pragma has the wrong number of arguments.");
    goto help;
   }

  /* Make sure that the second argument is "=". */
 if (0 != strcmp(arg[2].pt_pstr,"="))
   {lr_err(&arg[2].pt_ps,"Expecting \"=\"."); goto help;}

 /* Set up an abbreviation. */
 numstr=arg[3].pt_pstr;

 /* See if the value is "infinity". */
 if (strcmp(numstr,"infinity")==0)
   {inln_max=INMAXINF; return;}

 /* Calculate length of longest prefix containing all decimal digits. */
 /* Check that there are no illegal digits.                           */
 spn=strspn(numstr,"0123456789");
 if (spn != strlen(numstr))
   {
    ps_t ps;
    ASSIGN(ps,arg[3].pt_ps);
    ps.ps_column+=spn;
    lr_err(&ps,"Illegal digit. Value must consist entirely of decimal digits.");
    lr_mes(&ps,"You can also use the value \"infinity\".");
    lr_mes(&ps,"Pragma ignored.");
    return;
   }

 /* Check that the number is not too long. */
#if defined(__cplusplus) || defined(__STDC__)
 if (strlen(numstr)>(size_t)8)
#else
 if (strlen(numstr)>8)
#endif
   {
    lr_err(&arg[3].pt_ps,"Too many digits. The maximum is eight.");
    lr_mes(&arg[3].pt_ps,"Pragma ignored.");
    return;
   }

 /* Convert the argument into an integer. */
 {
  ulong val;
  int result;
  /* Note: Should really be %lu, but the Vax doesn't know about the %u */
  /* in sscanf and so we make do with %ld.                             */
  result=sscanf(numstr,"%ld",&val);
  as_cold(result==1,"do_pginl:sscanf failed.");
  inln_max=val;
 }
 return;

 help:
    lr_mes(&arg[0].pt_ps,
    "The correct format is: \"@p maximum_input_line_length = <num>|infinity\".");
    lr_mes(&arg[0].pt_ps,"Pragma ignored.");
    return;
}

/******************************************************************************/

LOCAL void do_pgotl P_((uword,p_pt_t));
LOCAL void do_pgotl(numarg,arg)
/* Parse a maximum product file line length pragma. */
uword numarg;
p_pt_t   arg;
{
 char  *numstr;
 uword spn;
 ulong val;
 ps_t psprag;

 /* Set up an abbreviation. */
 ASSIGN(psprag,arg[0].pt_ps);

 /* Make sure that there are exactly three arguments. */
 if (numarg != 3)  /* "max..length" "=" "value". */
   {
    lr_err(&arg[0].pt_ps,"This pragma has the wrong number of arguments.");
    goto help;
   }

  /* Make sure that the second argument is an "=". */
 if (0 != strcmp(arg[2].pt_pstr,"="))
   {lr_err(&arg[2].pt_ps,"Expecting \"=\"."); goto help;}

 /* Set up an abbreviation. */
 numstr=arg[3].pt_pstr;

 /* See if the value is "infinity". */
 if (strcmp(numstr,"infinity")==0)
   {val=TGMAXINF; goto gotvalue;}

 /* Calculate length of longest prefix containing all decimal digits. */
 /* Check that there are no illegal digits.                           */
 spn=strspn(numstr,"0123456789");
 if (spn != strlen(numstr))
   {
    ps_t ps;
    ASSIGN(ps,arg[3].pt_ps);
    ps.ps_column+=spn;
    lr_err(&ps,"Illegal digit. Value must consist entirely of decimal digits.");
    lr_mes(&ps,"You can also use the value \"infinity\".");
    lr_mes(&ps,"Pragma ignored.");
    return;
   }

 /* Check that the number is not too long. */
#if defined(__cplusplus) || defined(__STDC__)
 if (strlen(numstr)>(size_t)8)
#else
 if (strlen(numstr)>8)
#endif
   {
    lr_err(&arg[3].pt_ps,"Too many digits. The maximum is eight.");
    lr_mes(&arg[3].pt_ps,"Pragma ignored.");
    return;
   }

 /* Convert the argument into an integer. */
 {
  int result=sscanf(numstr,"%ld",&val);
  as_cold(result==1,"do_pgotl:sscanf failed.");
 }

 gotvalue:
 /* Make sure that the pragma does not contradict an earlier pragma. */
 if (seenlimo && (tglinmax!=val))
   {
    sprintf(linet1,"This pragma is opposed by the pragma at line %lu.",
                   (unsigned long) psprag.ps_line);
    lr_mes(&ps_limo,linet1);
    sprintf(linet1,"This pragma opposes the pragma at line %lu.",
                   (unsigned long) ps_limo.ps_line);
    lr_err(&psprag,linet1);
    lr_mes(&psprag,"You can have as many output line length pragmas");
    lr_mes(&psprag,"as you like, but they all have to be the same!");
    lr_mes(&psprag,"Pragma ignored.");
    return;
   }

 /* If we got this far then the pragma is just the same as an earlier one. */
 /* We don't want to set the pragma position to the later pragma so we     */
 /* return now.                                                            */
 if (seenlimo) return;

 /* Success. Set the variables. */
 tglinmax=val;
 seenlimo=TRUE;
 ASSIGN(ps_limo,psprag);
 return;

 help:
    lr_mes(&arg[0].pt_ps,
    "The correct format is: \"@p maximum_output_line_length = <num>|infinity\".");
    lr_mes(&arg[0].pt_ps,"Pragma ignored.");
    return;
}

/******************************************************************************/

LOCAL void do_pgnpg P_((uword,p_pt_t));
LOCAL void do_pgnpg(numarg,arg)
/* Parse a newpage typesetter directive. */
uword numarg;
p_pt_t   arg;
{
 /* Make sure that there is exactly one argument. */
 if (numarg > 1)  /* "new_page" */
   {
    lr_err(&arg[2].pt_ps,"The new_page directive does not take arguments.");
    lr_mes(&arg[2].pt_ps,"Directive ignored.");
    return;
   }
 sendspec(&arg[0].pt_ps,TK_NPAG,DONTCARE);
}

/******************************************************************************/

LOCAL void do_pgtoc P_((uword,p_pt_t));
LOCAL void do_pgtoc(numarg,arg)
/* Parse a table of contents typesetter directive. */
uword numarg;  /* Number of arguments to table of contents directive.         */
p_pt_t   arg;  /* Array describing arguments.                                 */
{
 /* Make sure that there is exactly one argument. */
 if (numarg > 1)  /* "table_of_contents" */
   {
    lr_err(&arg[2].pt_ps,
           "The table_of_contents directive does not take arguments.");
    lr_mes(&arg[2].pt_ps,"Directive ignored.");
    return;
   }
 sendspec(&arg[0].pt_ps,TK_TOCS,DONTCARE);
}

/******************************************************************************/

LOCAL void do_pgvsk P_((uword,p_pt_t));
LOCAL void do_pgvsk(numarg,arg)
/* Parse a vskip typesetter directive. */
uword numarg;  /* Number of arguments to indentation directive.               */
p_pt_t   arg;  /* Array describing arguments.                                 */
{
 char  *numstr;
 uword spn;

 /* Make sure that there are exactly three arguments. */
 if (numarg != 3)  /* "vskip" n "mm". */
   {
    lr_err(&arg[0].pt_ps,"This directive has the wrong number of arguments.");
    goto help;
   }

  /* Make sure that the third argument is "mm". */
 if (0 != strcmp(arg[3].pt_pstr,"mm"))
   {lr_err(&arg[3].pt_ps,"Expecting \"mm\"."); goto help;}

 /* Set up an abbreviation. */
 numstr=arg[2].pt_pstr;

 /* Calculate length of longest prefix containing all decimal digits. */
 /* Check that there are no illegal digits.                           */
 spn=strspn(numstr,"0123456789");
 if (spn != strlen(numstr))
   {
    ps_t ps;
    ASSIGN(ps,arg[2].pt_ps);
    ps.ps_column+=spn;
    lr_err(&ps,"Illegal digit.");
    lr_mes(&ps,"Value must consist entirely of decimal digits.");
    lr_mes(&ps,"Directive ignored.");
    return;
   }

 /* Check that the number is not too long. */
#if defined(__cplusplus) || defined(__STDC__)
 if (strlen(numstr)>(size_t)3)
#else
 if (strlen(numstr)>3)
#endif
   {
    lr_err(&arg[2].pt_ps,"Too many digits. The maximum is three.");
    lr_mes(&arg[2].pt_ps,"Directive ignored.");
    return;
   }

 /* Convert the argument into an integer. */
 {
  ulong val;
  int result;
  result=sscanf(numstr,"%ld",&val);
  as_cold(result==1,"do_pginl:sscanf failed.");
  if (val>255)
    {
     lr_err(&arg[2].pt_ps,"Value too large. Maximum is 255.");
     lr_mes(&arg[2].pt_ps,"Directive ignored.");
     return;
    }
  sendspec(&arg[0].pt_ps,TK_SKIP,(ubyte) val);
 }
 return;

 help:
    lr_mes(&arg[0].pt_ps,"The correct format is: \"@t vskip <num> mm\".");
    lr_mes(&arg[0].pt_ps,"Directive ignored.");
    return;
}

/******************************************************************************/

LOCAL void do_pgtit P_((uword,p_pt_t));
LOCAL void do_pgtit(numarg,arg)
/* Parse a title typesetter directive. */
uword numarg;  /* Number of arguments to title directive.                     */
p_pt_t   arg;  /* Array describing arguments.                                 */
{
 uword align;
 uword font;
 char *p_sot,*p_eot;

 /* Make sure that there are at least three arguments. */
 if (numarg < 4)  /* "title <font> <align> <text>". */
   {lr_err(&arg[0].pt_ps,"This directive has too few arguments."); goto help;}

 /* Check the font argument. */
      if (strcmp(arg[2].pt_pstr,"normalfont"    )==0) font=FT_NORM;
 else if (strcmp(arg[2].pt_pstr,"titlefont"     )==0) font=FT_TITL;
 else if (strcmp(arg[2].pt_pstr,"smalltitlefont")==0) font=FT_STIT;
 else
   {
    lr_err(&arg[2].pt_ps,
    "Expecting one of {titlefont,smalltitlefont,normalfont}.");
    lr_mes(&arg[2].pt_ps,"Directive ignored.");
    return;
   }

 /* Check the alignment argument. */
      if (strcmp(arg[3].pt_pstr,"left"  )==0) align=LR_LEFT;
 else if (strcmp(arg[3].pt_pstr,"right" )==0) align=LR_RIGH;
 else if (strcmp(arg[3].pt_pstr,"centre")==0) align=LR_CENT;
 else
   {
    lr_err(&arg[3].pt_ps,"Expecting one of {left,right,centre}.");
    if (strcmp(arg[3].pt_pstr,"center")==0)
      {
       lr_mes(&arg[3].pt_ps,"Note: Centre is spelt centRE, not centER.");
       lr_mes(&arg[3].pt_ps,"      This is my revenge for years of getting error messages");
       lr_mes(&arg[3].pt_ps,"      from TeX whenever I accidentally wrote \\centreline - Ross Williams.");
      }
    lr_mes(&arg[3].pt_ps,"Directive ignored.");
    return;
   }

 /* Now make sure that the remainder of the line is delimited by quotes. */
 p_sot=arg[4].pt_pinl;
 p_eot=p_sot+strlen(p_sot)-1;
 if (*p_sot!='"' || *p_eot!='"' || p_sot==p_eot)
   {
    lr_err(&arg[4].pt_ps,"Text argument must be delimited by double quotes.");
    lr_mes(&arg[4].pt_ps,"Directive ignored.");
    return;
   }
 p_sot++; p_eot--;

 /* Ship out a token whose fields are all fully laden. */
 {
  tk_t token;
  token.tk_kind        = TK_TITL;
  ASSIGN(token.tk_ps,arg[0].pt_ps);
  token.tk_sc.sc_first = p_sol+ (3+(p_sot-arg[1].pt_pinl));
  token.tk_sc.sc_last  = p_sol+ (3+(p_eot-arg[1].pt_pinl));
  token.tk_sc.sc_white = FALSE;
  token.tk_gen         = LRFT_PACK*font+align;
  ls_add(token_list,PV &token);
 }
 return;

 help:
    lr_mes(&arg[0].pt_ps,
    "The correct format is: \"@t title <font> <align> <text>\".");
    lr_mes(&arg[0].pt_ps,
    "   where <font>  = titlefont | smalltitlefont | normalfont.");
    lr_mes(&arg[0].pt_ps,
    "   and   <align> = left | centre | right.");
    lr_mes(&arg[0].pt_ps,
    "   and   <text>  = text delimited by double quotes.");
    lr_mes(&arg[0].pt_ps,"Directive ignored.");
    return;
}

/******************************************************************************/

LOCAL void do_pgtyp P_((uword,p_pt_t));
LOCAL void do_pgtyp(numarg,arg)
/* Parse a typesetter pragma. */
uword numarg;
p_pt_t   arg;
{
 tr_k_t pragtyp;
 ps_t   psprag;

 /* Make sure that there are exactly three arguments. */
 if (numarg != 3)  /* "typesetter" "=" "name". */
   {
    lr_err(&arg[0].pt_ps,
           "This typesetter pragma has the wrong number of arguments.");
    goto help;
   }

 /* Make sure that the second argument is "=". */
 if (0 != strcmp(arg[2].pt_pstr,"="))
   {
    lr_err(&arg[2].pt_ps,"Expecting \"=\".");
    goto help;
   }

 /* Check the third argument. */
      if (strcmp(arg[3].pt_pstr,"none")==0) pragtyp=TR_NONE;
 else if (strcmp(arg[3].pt_pstr,"tex" )==0) pragtyp=TR_TEX;
 else if (strcmp(arg[3].pt_pstr,"texinfo" )==0) pragtyp=TR_TEXINFO;
 else if (strcmp(arg[3].pt_pstr,"html" )==0) pragtyp=TR_HTML;
 else if (strcmp(arg[3].pt_pstr,"latex" )==0) pragtyp=TR_LATEX;
 else if (strcmp(arg[3].pt_pstr,"latex2html" )==0) pragtyp=TR_L2HTML;
 else
   {
    lr_err(&arg[3].pt_ps,
      "Expecting \"none\", \"tex\", \"texinfo\", \"html\" or \"latex2html\".");
    goto help;
   }

 /* Construct a shorthand for the start of the pragma. */
 ASSIGN(psprag,arg[0].pt_ps);

 /* Make sure that the pragma does not contradict an earlier pragma. */
 if (seentyp && (tr_codes != pragtyp))
   {
    sprintf(linet1,"This pragma is opposed by the pragma at line %lu.",
                   (unsigned long) psprag.ps_line);
    lr_mes(&ps_typ,linet1);
    sprintf(linet1,"This pragma opposes the pragma at line %lu.",
                   (unsigned long) ps_typ.ps_line);
    lr_err(&psprag,linet1);
    lr_mes(&psprag,"You can have as many typesetter pragmas as you like,");
    lr_mes(&psprag,"but they all have to be the same!");
    lr_mes(&psprag,"Pragma ignored.");
    return;
   }

 /* Success: Record the pragma information. */
 seentyp  = TRUE;       /* Record that we have seen a pragma. */
 tr_codes = pragtyp;    /* Record what the pragma said.       */
 ASSIGN(ps_typ,psprag); /* Record where the pragma was.       */
 return;

 help:
    lr_mes(&arg[0].pt_ps,
      "The correct format is: \"@p typesetter = none|tex|texinfo|html\".");
    lr_mes(&arg[0].pt_ps,"Pragma ignored.");
    return;
}

/******************************************************************************/

LOCAL void do_pragma P_((p_ps_t,bool));
LOCAL void do_pragma(p_ps,is_typ)
/* Upon entry, the current character is:                                      */
/* is_typ=FALSE => The P of a @p.                                             */
/* is_typ=TRUE  => The T of a @t.                                             */
/* This function processes these contructs.                                   */
p_ps_t p_ps;
bool is_typ;
{
#define MAXPARG     10         /* Maximum recorded arguments to a pragma.     */
#define PRAGMA_MAX 100         /* Maximum length of a pragma.                 */
 char  praglin[PRAGMA_MAX+1];  /* Array to hold pragma as a complete line.    */
 char  pragstr[PRAGMA_MAX+1];  /* Array to hold pragma as strings.            */
 pt_t  pragarg[MAXPARG+1];     /* Array of pragma arguments.                  */
 uword length;                 /* Helps prevent scanning overrun.             */
 char  *p,*q;                  /* Temporary.                                  */
 uword numarg,na;              /* Number of arguments seen so far.            */

 /* Complain if the pragma directive is not at the start of a line. */
 if (p_ch-1 != p_sol)
   {
    if (is_typ)
      {
       lr_err(p_ps,"Typesetter directive @t must be at the start of a line.");
       lr_mes(p_ps,"The rest of this line will be ignored.");
      }
    else
      {
       lr_err(p_ps,"Pragma sequence @p must be at the start of a line.");
       lr_mes(p_ps,"The rest of this line will be ignored.");
      }
    skiptoeol();
    goto help;
   }

 /* The include command should be followed by a blank. Get the next char. */
 NEXTCH;

 /* Complain if the next character is not a blank. */
 if (ch != ' ')
   {
    /* Note: If we position this error correctly, it gets put after the */
    /*       help message!                                              */
    if (is_typ)
       lr_err(p_ps,"Typesetter directive @t must be followed by a blank.");
    else
       lr_err(p_ps,"Pragma sequence @p must be followed by a blank.");
    skiptoeol();
    goto help;
   }

 /* Copy the rest of the line to the pragma arrays. */
 NEXTCH;
 p = &praglin[0];
 q = &pragstr[0];
 length=0;
 while (ch!=EOL)
   {
    if (++length > PRAGMA_MAX-3)  /* 3 is for "@p " or "@t " */
      {
       if (is_typ)
         {
          lr_err(p_ps,"This typestter directive line is too long.");
          sprintf(linet1,"The maximum typesetter directive line length is %u characters.",
                     (unsigned) PRAGMA_MAX);
          lr_mes(p_ps,linet1);
         }
       else
         {
          lr_err(p_ps,"This pragma line is too long.");
          sprintf(linet1,"The maximum pragma line length is %u characters.",
                     (unsigned) PRAGMA_MAX);
          lr_mes(p_ps,linet1);
         }
       skiptoeol();
       goto help;
      }
    *p++=ch;
    *q++=ch;
    NEXTCH;
   }
 *p=EOS;
 *q=EOS;
 /* Note: Current position is now on the EOL at the end of the @p line. */
 /* That is the way we want to leave it for the scanspec() routine.     */

 /* So far we have copied the body of the pragma line into two arrays. The    */
 /* next lump of code parses that line into a sequence of non-blank arguments.*/
 /* The result is an array of pt_t objects each of which contains the         */
 /* position of each argument, a pointer to the first character of each       */
 /* argument in praglin, and also a pointer to a string containing the arg.   */
 /* The string resides in the array pragstr which is the same as praglin      */
 /* except that some blanks have been replaced by EOSs so as to allow us to   */
 /* point into it to form strings. All this probably seems rather overdone    */
 /* for the analysis of a "simple" pragma, but I have found that pulling the  */
 /* different kinds of pragma lines apart separately is very messy. Far       */
 /* better to suffer here in what is at least reasonably neat code than       */
 /* later in the specific pragma routines.                                    */
 numarg=0;
 p= &praglin[0];
 q= &pragstr[0];
 while (TRUE)
   {
    /* Skip whitespace between arguments. */
    while (*p==' ') {p++;q++;}

    /* Exit if we have hit the end of the line. */
    if ((numarg==MAXPARG) || (*p==EOS)) break;

    /* We have found another argument! */
    numarg++;

    /* Record the argument. */
    ASSIGN(pragarg[numarg].pt_ps,*p_ps);
    pragarg[numarg].pt_ps.ps_column=4+(p-praglin);
    pragarg[numarg].pt_pinl=p;
    pragarg[numarg].pt_pstr=q;

    /* Skip to the end of the argument. */
    while (*p!=' ' && *p!=EOS) {p++;q++;}

    /* Drop a null in the string array to complete string rep of argument. */
    *q=EOS;
   }

 /* At this point numarg is MIN(arguments,MAXPARG), and pragargs contains an  */
 /* entry for each of the numarg arguments.                                   */

 /* It is handy to have the position of the pragma itself handy. */
 ASSIGN(pragarg[0].pt_ps,*p_ps);

 /* CHECK: Make sure that the line and string arrays square up. */
 {
  uword i;
  for (i=1;i<=numarg;i++)
    {
     uword j;
     uword t=strlen(pragarg[i].pt_pstr);
     for (j=0;j<t;j++)
       {
        as_cold(pragarg[i].pt_pstr[j]==pragarg[i].pt_pinl[j],
                "do_pragma: String and line arrays are not equal.");
        as_cold((pragarg[i].pt_pstr-pragstr)==(pragarg[i].pt_pinl-praglin),
                "do_pragma: String and line arrays are out of synch.");
       }
    }
 }

 /* Complain if there are no arguments at all. */
 if (numarg==0)
   {
    if (is_typ)
       lr_err(p_ps,"Typesetter directive @t must be followed by a keyword.");
    else
       lr_err(p_ps,"Pragma sequence @p must be followed by a keyword.");
    skiptoeol();
    goto help;
   }

 /* Branch off to specific routines based on the first argument. */
 p=pragarg[1].pt_pstr; na=numarg;
 if (is_typ)
   {
    if (0==strcmp(p,"new_page"          )) {do_pgnpg(na,pragarg);return;}
    if (0==strcmp(p,"table_of_contents" )) {do_pgtoc(na,pragarg);return;}
    if (0==strcmp(p,"title"             )) {do_pgtit(na,pragarg);return;}
    if (0==strcmp(p,"vskip"             )) {do_pgvsk(na,pragarg);return;}
   }
 else
   {
    if (0==strcmp(p,"indentation"               )) {do_pgind(na,pragarg);return;}
    if (0==strcmp(p,"maximum_input_line_length" )) {do_pginl(na,pragarg);return;}
    if (0==strcmp(p,"maximum_output_line_length")) {do_pgotl(na,pragarg);return;}
    if (0==strcmp(p,"typesetter"                )) {do_pgtyp(na,pragarg);return;}
   }

 help:
 if (is_typ)
   {
    lr_err(p_ps,"Unrecognised typesetter directive. Legal ones are:");
    lr_mes(p_ps,"   @t new_page");
    lr_mes(p_ps,"   @t table_of_contents");
    lr_mes(p_ps,"   @t title <font> <align> <string>");
    lr_mes(p_ps,"   @t vskip <num> mm");
    lr_mes(p_ps,"The blanks between arguments are important.");
    lr_mes(p_ps,"Typesetter directive ignored.");
   }
 else
   {
    lr_err(p_ps,"Unrecognised pragma. Possible legal pragmas are:");
    lr_mes(p_ps,"   @p indentation = none | blank");
    lr_mes(p_ps,"   @p maximum_input_line_length  = <num>|infinity");
    lr_mes(p_ps,"   @p maximum_output_line_length = <num>|infinity");
    lr_mes(p_ps,"   @p typesetter = none | tex | texinfo | html");
    lr_mes(p_ps,"The blanks between arguments are important.");
    lr_mes(p_ps,"Pragma ignored.");
   }
}

/******************************************************************************/

LOCAL void chksol P_((void));
LOCAL void chksol()
/* This function is called when the current character is the character after  */
/* an @. The function checks to see if the @ was at the start of a line and   */
/* issues a error message if it isn't.                                        */
{
 ps_t ps;
 grabchps(&ps);
 if (ps.ps_column != 2)
   {
    ps.ps_column--;
    sprintf(linet1,"@%c is legal only at the start of a line.",ch);
    lr_err(&ps,linet1);
   }
}

/******************************************************************************/

LOCAL void scanspec P_((void));
LOCAL void scanspec()
/* Upon entry the current character is the special character (usually '@').   */
/* The task is to scan the special sequence. Upon exit, the current character */
/* is the character following the special sequence.                           */
{
 ps_t  ps_spec;                   /* Position of start of special sequence.   */

 /* Make a note of where the special sequence starts. */
 grabchps(&ps_spec);

 /* Move onto the character following the special (escape) character. */
 NEXTCH;

 /* Now react to the character. In most cases, the special sequence is simply */
 /* a marker in the input and we can simply transmit it. The nasty special    */
 /* case sequences are left until the end of the switch statement.            */
 /* Purists will complain about how all the case options are hardwired and    */
 /* say that symbols should have been used. They once were, but were taken    */
 /* out when it was discovered that the symbols had cryptic names (because of */
 /* the portability eight-character rule) and were only used here anyway.     */
 switch (toupper(ch))
   {
    case '<': sendspec(&ps_spec,TK_ONAM,DONTCARE); break;
    case '>': sendspec(&ps_spec,TK_CNAM,DONTCARE); break;
    case '{': sendspec(&ps_spec,TK_ODEF,DONTCARE); break;
    case '}': sendspec(&ps_spec,TK_CDEF,DONTCARE); break;
    case '(': sendspec(&ps_spec,TK_OPAR,DONTCARE); break;
    case ')': sendspec(&ps_spec,TK_CPAR,DONTCARE); break;
    case ',': sendspec(&ps_spec,TK_COMA,DONTCARE); break;
    case '"': sendspec(&ps_spec,TK_QUOT,DONTCARE); break;
    case '/': sendspec(&ps_spec,TK_EMPH,DONTCARE); break;
    case 'A': sendspec(&ps_spec,TK_NSEC,1); chksol(); break;
    case 'B': sendspec(&ps_spec,TK_NSEC,2); chksol(); break;
    case 'C': sendspec(&ps_spec,TK_NSEC,3); chksol(); break;
    case 'D': sendspec(&ps_spec,TK_NSEC,4); chksol(); break;
    case 'E': sendspec(&ps_spec,TK_NSEC,5); chksol(); break;
    case '1': sendspec(&ps_spec,TK_PARM,1); break;
    case '2': sendspec(&ps_spec,TK_PARM,2); break;
    case '3': sendspec(&ps_spec,TK_PARM,3); break;
    case '4': sendspec(&ps_spec,TK_PARM,4); break;
    case '5': sendspec(&ps_spec,TK_PARM,5); break;
    case '6': sendspec(&ps_spec,TK_PARM,6); break;
    case '7': sendspec(&ps_spec,TK_PARM,7); break;
    case '8': sendspec(&ps_spec,TK_PARM,8); break;
    case '9': sendspec(&ps_spec,TK_PARM,9); break;
    case 'M': sendspec(&ps_spec,TK_MANY,DONTCARE); break;
    case 'Z': sendspec(&ps_spec,TK_ZERO,DONTCARE); break;
    case 'N': sendspec(&ps_spec,TK_NDEF,DONTCARE); chksol(); break;
    case 'O': sendspec(&ps_spec,TK_FDEF,DONTCARE); chksol(); break;
    case '$': sendspec(&ps_spec,TK_MDEF,DONTCARE); chksol(); break;
    case EOL:
       lr_err(&ps_spec,"<special><endofline> is not a legal special sequence.");
       break;
    case ' ':
       lr_err(&ps_spec,"<special><space> is not a legal special sequence.");
       break;
    case '@':
       /* @ instructs FunnelWeb to replace the special construct with the */
       /* special character. Luckily one appears just before the @ !!     */
       /* Note: FALSE is OK because space is not a legal specialch.       */
       sendtext(&ps_spec,p_ch-1,p_ch-1,FALSE);
       break;
    case '-':
       /* - instructs FunnelWeb to suppress the following end of line. */
       if (*(p_ch+1) == EOL)
          NEXTCH
       else
          lr_err(&ps_spec,
                 "Suppress EOL sequence is legal only at the end of a line.");
       break;
    case '+':
       /* + instructs FunnelWeb to insert an EOL. We can't look to the end of */
       /* the previous line to find an EOL as this might be the first line.   */
       /* Running ahead to the end of the line is expensive, and having the   */
       /* liner mini-package maintain a variable for it would be extra        */
       /* housekeeping. Instead of all this, we just point to a static.       */
       {STAVAR char stateol = EOL;
        sendtext(&ps_spec,&stateol,&stateol,TRUE);}
       break;
    case '=':
      /* = instructs FunnelWeb to change the special character to the         */
      /* character following the <special>= sequence.                         */
      NEXTCH;
      if (ch == ' ')
        {
         lr_err(&ps_spec,"You cannot set the special character to <space>!");
         lr_mes(&ps_spec,"Special sequence ignored.");
        }
      else if (ch == EOL)
        {
         lr_err(&ps_spec,
                "You cannot set the special character to <endofline>!");
         lr_mes(&ps_spec,"Special sequence ignored.");
        }
      else
         specialch=ch;
      break;
    case '!':
       /* ! instructs FunnelWeb to ignore the rest of the line (a comment). */
       skiptoeol();
       break;
    case 'I':
       /* i instructs FunnelWeb to include a file. */
       incl_fil(&ps_spec);
       break;
    case '^':
       /* ^ instructs FunnelWeb to insert a specific ascii character. */
       do_ascii(&ps_spec);
       break;
    case '#':
       /* # instructs FunnelWeb to transmit a two character name "#c". */
       do_name(&ps_spec);
       break;
    case 'P':
       /* P is used as a miscellaneous PRAGMA. */
       do_pragma(&ps_spec,FALSE);
       break;
    case 'T':
       /* T introduces a one-line typesetting directive. */
       do_pragma(&ps_spec,TRUE);
       break;
    default:
       lr_err(&ps_spec,"Unknown special sequence.");
       break;
   }

 /* The switch statment absorbs the special sequence and its effects.      */
 /* This NEXTCH places us on the character following the special sequence. */
 NEXTCH;
}

/******************************************************************************/

LOCAL void scantext P_((void));
LOCAL void scantext()
/* Upon entry, we know that the current character is not EOF and that it is   */
/* not the special character. Our task is to parse as much text as we can and */
/* ship it off as a text token. The scanner will probably spend most of its   */
/* time in the loops in this function so it is important that they be         */
/* efficient. That is why two loops are used to deal with detecting           */
/* whitespace rather than a flag.                                             */
/* Upon return, the current character is the character following the text     */
/* sequence. This is guaranteed to be the special character or an EOF.        */
{
 ps_t ps_start;        /* Position of first character of text sequence.       */
 char *p_first = p_ch; /* Pointer  to first character of text sequence.       */

 /* Grab a copy of the position of this token. */
 grabchps(&ps_start);

 /* Scan whitespace. */
 while (ch==' ' || ch==EOL)
    NEXTCH;

 /* If we hit something that ends a text token */
 /* then we can transmit a white text token.   */
 if (ch==specialch || ch==EOFCH)
    {sendtext(&ps_start,p_first,p_ch-1,TRUE); return;}

 /* Otherwise we have some more (non-white) text to scan. */
 /* We can then send a non-white text token.              */
 while (ch!=specialch && ch!=EOFCH)
    NEXTCH;
 sendtext(&ps_start,p_first,p_ch-1,FALSE);
}

/******************************************************************************/

LOCAL void scan_file(p_fname)
/* This function scans a single file. It's argument is the name of the file   */
/* to be scanned. scan_file calls the mapper to map in the file and then      */
/* scans the text of the mapped file using the liner mini-package. The result */
/* of the scan is additions to the line and token list, and diagnostics sent  */
/* to the lister package. If an include directive is encountered, this        */
/* function is called recursively.                                            */
char *p_fname;
{
 char  *p_mapped;  /* Pointer to the mapped file.                             */
 ulong  length;    /* Number of bytes in the mapped file.                     */
 char  *errstr;    /* Error string returned by mapper.                        */
 bool   addedeol;  /* Did we have to add an EOL to the end of the last line?  */

 /* Check to see if the file exists. */
 if (!fexists(p_fname))
   {
    if (inclevel==0)
      {
       /* Failure to find the main file is a severe error. */
       if (option.op_b7_b)
          sprintf(linet1,"S: Error opening input file \"%s\".",SUPPNAME);
       else
          sprintf(linet1,"S: Error opening input file \"%s\".",p_fname);
       wl_l(linet1);
       /* Although strictly speaking we should suppress this error from the   */
       /* screen stream unless option.op_s_b is set, absence of an input file */
       /* is such an important error, that we write it out anyway.            */
       /* if (option.op_s_b) */
       wl_sj(linet1);
       num_sev++;
       return;
      }
    else
      {
       /* Failure to find an include file is an ordinary error. */
       ps_t ps;
       ps.ps_filename = filename;
       ps.ps_line     = globalno;
       ps.ps_locline  = localno;
       ps.ps_column   = 4;
       lr_err(&ps,"Error opening include file.");
       if (option.op_b7_b)
          sprintf(linet1,
             "The include file's expanded name was \"%s\".",SUPPNAME);
       else
          sprintf(linet1,
             "The include file's expanded name was \"%s\".",p_fname);
       lr_mes(&ps,linet1);
       return;
      }
   }

 /* Save the file name globally */
 filename=(char *)mm_perm((size_t) FILENAME_MAX+1+10); /* 10 is for paranoia. */
 strcpy(filename, p_fname);

 /* Map the specified file into memory. We need to change from the scanner    */
 /* clock to the mapper clock to keep the time accounting correct here.       */
 ck_stop(p_scan);
 ck_start(p_mapp);
 errstr=map_file(p_fname,&p_mapped,&length);
 ck_stop(p_mapp);
 ck_start(p_scan);

 /* Abort if the mapping was not possible. */
 if (errstr != NULL)
    {if (inclevel==0)
      {
       /* Failure to map the main file is a severe error. */
       if (option.op_b7_b)
          sprintf(linet1,"S: Error reading input file \"%s\".",SUPPNAME);
       else
          sprintf(linet1,"S: Error reading input file \"%s\".",p_fname);
       wl_l(linet1); if (option.op_s_b) wl_sj(linet1);
       wl_l(errstr); if (option.op_s_b) wl_sj(errstr);
       num_sev++;
       return;
      }
    else
      {
       /* Failure to find an include file is an ordinary error. */
       ps_t ps;
       ps.ps_filename = filename;
       ps.ps_line     = globalno;
       ps.ps_locline  = localno;
       ps.ps_column   = 4;
       lr_err(&ps,"Error reading include file.");
       lr_mes(&ps,errstr);
       if (option.op_b7_b)
          sprintf(linet1,"The include file's expanded name was \"%s\".",
                  SUPPNAME);
       else
          sprintf(linet1,"The include file's expanded name was \"%s\".",
                  p_fname);
       lr_mes(&ps,linet1);
       return;
      }
    }

 /* Dump the mapped file if requested. */
 if (option.op_b1_b)
   {
    if (option.op_b7_b)
       sprintf(linet1,"Dump of mapped file \"%s\".",SUPPNAME);
    else
       sprintf(linet1,"Dump of mapped file \"%s\".",p_fname);
    wl_l(linet1);
    dm_mem(&f_l,p_mapped,length);
   }

 /* If the file is absolutely empty, we have to warn the user. Also, this is  */
 /* a special case we can do without, and so we return here if file is empty. */
 if (length==0)
   {
    ps_t ps;
    /* The empty file could be the main file or an include file.              */
    /* If the empty file is the main file, we want the diagnostic to point to */
    /*    the EOF marker which will appear as line 1.                         */
    /* If the empty file is an include file, we wish to point the diagnostic  */
    /*    to the line containing the include command. This is globalno.       */
    /* In both cases, we want the diagnostic to point to column 1.            */
    ps.ps_filename = filename;
    ps.ps_column=1;
    if (inclevel==0)
      {
       ps.ps_line=ps.ps_locline=1;
       lr_war(&ps,"Input file is empty (not a byte in syte)!");
      }
    else
      {
       ps.ps_line=globalno;
       ps.ps_locline=localno;
       lr_war(&ps,"Include file is empty (not a byte in syte)!");
      }
    return;
   }

 /* Scanning is considerably simplified if we can guarantee that we will not  */
 /* run into an EOF without first hitting an EOL. The following code takes    */
 /* care of this by tacking one on the end if necessary and also adds an      */
 /* EOF character on the end, which also simplifies the scanning. We can get  */
 /* away with all this because the mapper purposefully leaves at least two    */
 /* bytes free for us at the end of the mapped file.                          */
 addedeol=FALSE;
 if (p_mapped[length-1] != EOL)
    {p_mapped[length++]=EOL; addedeol=TRUE;}
 p_mapped[length]=EOFCH;

 /* Initialize the variables "instantiated over a single file". */
 inln_max  = 80;
 specialch = CH_DSPE;
 localno   = 0;
 p_eof     = &p_mapped[length];

 /* Crank up the line subscanner system with a call to prepline. */
 /* Then enter the main scanning loop.                           */
 /* All input consists of alternating special and text sequences */
 /* terminated by EOF.                                           */
 prepline(p_mapped);
 while (ch!=EOFCH)
    if (ch==specialch)
       scanspec();
    else
       scantext();

 /* Now that we are at the end of the scanned file and the scanning markers   */
 /* are all sitting on the end of the file, it is a good time to issue        */
 /* diagnostics about problems at the end of the file.                        */
 if (addedeol)
   {
    ps_t ps;
    /* We want the diagnostic to point to the EOF line. Hence "global+1".     */
    ps.ps_filename = filename;
    ps.ps_line     = globalno+1;
    ps.ps_locline  = localno+1;
    ps.ps_column   = 1;
    if (inclevel==0)
       lr_war(&ps,"The last line of the input file was terminated by EOF.");
    else
       lr_war(&ps,"The last line of the include file was terminated by EOF.");
    lr_mes(&ps,"An EOL was inserted at the end of the last line.");
   }
}

/******************************************************************************/

EXPORT void scanner(p_amapp,p_ascan)
/* This is the scanner's main routine and the only exported function.         */
p_ck_t p_amapp; /* Mapper's clock (stopped).  */
p_ck_t p_ascan; /* Scanner's clock (running). */
{
 /* Copy the arguments into globals where we can get at them. */
 p_mapp=p_amapp;
 p_scan=p_ascan;

 /* Apart from diagnostic messages sent to the lister, the only output of     */
 /* the scanner is two global lists holding a list of lines and a list of     */
 /* tokens. The scanner creates these lists simultaneously.                   */
 /* We have to initialize them here before we get into 'scan_file' which      */
 /* calls itself recursively if an include file command is encountered.       */
 line_list =ls_cre(sizeof(ln_t));
 token_list=ls_cre(sizeof(tk_t));

 /* Initialize all the variables instantiated throughout the entire scan.     */
 globalno  = 0;
 inclevel  = 0;
 seenind   = FALSE;
 seentyp   = FALSE;
 seenlimo  = FALSE;

 /* We also have to initialize localno in case the input file is empty and    */
 /* it never gets initialized before being sucked into being used as the      */
 /* local number for the end of file marker.                                  */
 localno=0;

 /* Initialize the global indentation flag to the default value. */
 tgindent=TRUE;

 /* Initialize the global product line length limit to the default value. */
 tglinmax=80;

 /* Initialize the global typesetter flag to the default value. */
 tr_codes=TR_NONE;

 /* Scan the top level file whose name is obtained from the command line.     */
 as_cold(option.op_f_b,"scanner: -F!!!!");

 /* Work out what the input file name should be. */
 {
  fn_t fname;
  strcpy(fname,"");              /* Start with an empty string.               */
  fn_ins(fname,".fw");
  fn_ins(fname,option.op_f_s);
  scan_file(fname);
 }

 /* The scan_file function scans the main input file and all of its included  */
 /* files, but it does not append a TK_EOF token to the end. This call does   */
 /* this and also adds a line to the line list for EOF.                       */
 add_eof();
}

/******************************************************************************/
/*                              End of SCANNER.C                              */
/******************************************************************************/

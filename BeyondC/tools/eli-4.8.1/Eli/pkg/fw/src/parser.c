static char RCSid[] = "$Id: parser.c,v 1.17 1999/10/20 04:56:43 tony Exp $";
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
   26-Jul-1992  AMS  Added version of pr_text that returns a list of tokens
                     rather than scraps.
   26-Jul-1992  AMS  Added RCS id.
   26-Jul-1992  AMS  Fixed bug due to change of text element representation
                     from scraps to tokens.
   20-Sep-1992  AMS  Fixed problem with allocation of memory for whitespace
                     preservation in macro call argument lists.
   04-May-1993  AMS  Added errors for whitespace or slashes in produce file
                     names.
   02-Jun-1993  AMS  Change index to strchr and rindex to strrchr.
   03-Jul-1993  AMS  Fixed first arguments to lr_err calls complaining about
                     output file names with whitespace or slashes in them.
   06-Aug-1997	WMW  Add non-product files
   03-May-1998	WMW  Fixed bug due to change of text element representation
		     from scraps to tokens
 
##############################################################################*/


/******************************************************************************/
/*                                    PARSER.C                                */
/******************************************************************************/

#include <setjmp.h>
#include "style.h"

#include "as.h"
#include "data.h"
#include "lister.h"
#include "machin.h"
#include "mapper.h"
#include "memory.h"
#include "misc.h"
#include "parser.h"
#include "section.h"
#include "table.h"

/******************************************************************************/

#define DUMMYINT 0                 /* It doesn't matter what this value is!!! */
#define TKPS &(p_tk->tk_ps)        /* A commonly used construct.              */

/******************************************************************************/

/* The following variables look after sections. */
LOCVAR sn_t     last_sn;   /* Hierarchical section number of last section.    */
LOCVAR ps_t     pssection; /* Position of last section.                       */
LOCVAR p_dc_t   p_secdc;   /* Pointer to current section document component.  */
LOCVAR tk_t    *p_tk;      /* Pointer to the current token (a structure).     */
LOCVAR ulong    sequence;  /* Current sequence number.                        */
LOCVAR jmp_buf  jmp_pos;   /* Setjmp() position of main parsing loop.         */

/******************************************************************************/
/*                             Comparison Functions                           */
/******************************************************************************/

LOCAL sign cm_name P_((name_t *,name_t *));
LOCAL sign cm_name(name1,name2)
/* Compares two names and returns:               */
/*    -1 if name1 < name2                        */
/*     0 if name1 = name2                        */
/*     1 if name1 > name2                        */
/* Provides a full ordering on the set of names. */
name_t *name1;
name_t *name2;
{
 return signof(strcmp(&(*name1)[0],&(*name2)[0]));
}

/******************************************************************************/

LOCAL sign eq_txst P_((p_scls_t,char *));
LOCAL sign eq_txst(p_scls,p_str)
/* The first argument is a list of text scraps.             */
/* The second argument is an ordinary string.               */
/* Returns TRUE iff the two are identical. Otherwise FALSE. */
p_scls_t  p_scls;
char     *p_str;
{
 /* To compare the scrap list with the string, we run through the scrap list */
 /* comparing the bytes its scraps yield progressively with the string.      */
 /* The two scanning groups are (p_scls,p_sc,p_ch) and p_str.                */
 sc_t *p_sc;

 ls_fir(p_scls);
 ls_nxt(p_scls,PPV &p_sc);
 while (p_sc!=NULL)
   {
    /* The loop body compares a single scrap pointed to by p_sc. */
    char *p_ch;
    for (p_ch=p_sc->sc_first; p_ch<=p_sc->sc_last; p_ch++)
      {
       if (*p_str==EOS || *p_str != *p_ch) return FALSE;
       p_str++;
      }
    ls_nxt(p_scls,PPV &p_sc);
   }
 return *p_str==EOS;
}

/******************************************************************************/
/*                               Parsing Primitives                           */
/******************************************************************************/
/* The following functions provide the basic parsing primitives used by the   */
/* main parsing routines.                                                     */
/******************************************************************************/

LOCAL void next_tk P_((bool));
LOCAL void next_tk(iseoferr)
/* This function reads the next token from the token list and places a        */
/* pointer to the token (structure) in the global variable "p_tk".           */
/* The "iseoferr" determines whether a fuss should be made if the next token  */
/* fetched is TK_EOF. If iseoferr==TRUE and the next token is TK_EOF, next_tk */
/* jumps to the main parsing loop.                                            */
bool iseoferr;
{
 ls_nxt(token_list,PPV &p_tk);
 as_cold(p_tk!=NULL,"next_tk: Attempted to read next token at EOF.");
 if (iseoferr && p_tk->tk_kind==TK_EOF)
   {
    lr_err(TKPS,"Ouch! High velocity encounter with end of file.");
    lr_mes(TKPS,"FunnelWeb expected something else when it hit the EOF.");
    longjmp(jmp_pos,DUMMYINT);    /* Jump up to the main parsing loop. */
   }
}

/******************************************************************************/

LOCAL void recover P_((void));
LOCAL void recover()
/* Parsing functions call this function at points where a syntax error has    */
/* has occurred that it is unlikely that the particular parsing function will */
/* be able to recover from on its own. In these situations, the parser        */
/* resorts to a course grained syntactic error-recovery implemented by this   */
/* function. The goal of the error recovery system is to skip tokens until    */
/* the next major outer-level-syntax structure is encountered. These are:     */
/*    - A new section (@A etc.).                                              */
/*    - A macro definition (@$ or @O).                                        */
/*    - End of file.                                                          */
/* Once one of these three is found, "recover" raises the syntax exception    */
/* which sends control to the main parsing loop which is the correct place    */
/* to deal with a new, major syntactic construct.                             */
{
 lr_mes(TKPS,"Skipping after error to the next major construct...");

 /* Skip to one of TK_NSEC,... */
 while (TRUE)
   {
    tk_k_t k = p_tk->tk_kind;
    if (k==TK_NSEC || k==TK_MDEF || k==TK_NDEF || k==TK_FDEF || k==TK_EOF)
      break;
    next_tk(FALSE);
   }

 /* Keep the user informed. */
 lr_mes(TKPS,"...skipped to here after the error.");

 /* Jump up to the main parsing loop. */
 longjmp(jmp_pos,DUMMYINT);
}

/******************************************************************************/

LOCAL void genexerr P_((tk_k_t));
LOCAL void genexerr(tk_kind)
/* Genexerr stands for GENerate EXpecting ERRor.                              */
/* Given a token kind, genexerr issues an error saying that the specified     */
/* kind of token was expected. It then invokes recover() for error recovery.  */
tk_k_t tk_kind;
{
 switch (tk_kind)
   {
    /* Note: Not all token kinds are listed here. Only those token kinds that */
    /* are passed to pr_token and check_tk by the main parsing routines are   */
    /* included here. There are some tokens that one never expects!           */
    case TK_NSEC: lr_err(TKPS,"Expecting '@*'."); break;
    case TK_ONAM: lr_err(TKPS,"Expecting '@<'."); break;
    case TK_ODEF: lr_err(TKPS,"Expecting '@{'."); break;
    case TK_CDEF: lr_err(TKPS,"Expecting '@}'."); break;
    case TK_EMPH: lr_err(TKPS,"Expecting '@/'."); break;
    case TK_CPAR: lr_err(TKPS,"Expecting '@)'."); break;
    case TK_QUOT: lr_err(TKPS,"Expecting '@\"'."); break;
    case TK_PARM: lr_err(TKPS,"Expecting one of [@1..@9]." ); break;
    case TK_TEXT: lr_err(TKPS,"Expecting a text character."); break;
    default: as_bomb("genexerr: Case defaulted.");
   }
 recover();
}

/******************************************************************************/

LOCAL void pr_token P_((tk_k_t));
LOCAL void pr_token(tk_kind)
/* Parses a single token of the specified kind.                               */
/* If the token is of the specified kind, gets the next token.                */
/* If the token is not of the specified kind, generates an "expecting" error. */
tk_k_t tk_kind;
{
 if (p_tk->tk_kind != tk_kind)
    genexerr(tk_kind);
 next_tk(TRUE);
}

/******************************************************************************/

LOCAL void check_tk P_((tk_k_t));
LOCAL void check_tk(tk_kind)
/* Same as pr_token, but only checks that the token is OK. Does not move on.  */
tk_k_t tk_kind;
{
 if (p_tk->tk_kind != tk_kind)
    genexerr(tk_kind);
}

/******************************************************************************/

LOCAL void ass_tk P_((tk_k_t));
LOCAL void ass_tk(tk_kind)
/* Aborts the program if the current token is not of the specified kind.      */
/* This function is intended to perform internal consistency checks, and      */
/* should not be considered to be part of the parsing operation.              */
tk_k_t tk_kind;
{
 as_cold(p_tk->tk_kind==tk_kind,"Parser.ass_tk: Incorrect token.");
}

/******************************************************************************/

LOCAL void ass_tks P_((tk_k_t,tk_k_t));
LOCAL void ass_tks(tk_kind1,tk_kind2)
/* Same as ass_tk except it allows a choice of two token kinds. */
tk_k_t tk_kind1;
tk_k_t tk_kind2;
{
 as_cold((p_tk->tk_kind == tk_kind1) || (p_tk->tk_kind == tk_kind2),
         "Parser.ass_tks: Token is neither of two allowables.");
}

/******************************************************************************/

LOCAL void ass_tk3 P_((tk_k_t,tk_k_t,tk_k_t));
LOCAL void ass_tk3(tk_kind1,tk_kind2,tk_kind3)
/* Same as ass_tk except it allows a choice of three token kinds. */
tk_k_t tk_kind1;
tk_k_t tk_kind2;
tk_k_t tk_kind3;
{
 as_cold((p_tk->tk_kind == tk_kind1) ||
         (p_tk->tk_kind == tk_kind2) ||
         (p_tk->tk_kind == tk_kind3),
         "Parser.ass_tk3: Token is none of the three allowables.");
}

/******************************************************************************/
/*                            Main Parsing Functions                          */
/******************************************************************************/

/* The parse expression procedure is the only procedure for which a forward   */
/* declaration is required. This is a product of the recursive definition of  */
/* a FunnelWeb expression.                                                    */
LOCAL void pr_exp P_((p_ells_t *,p_ma_t));

/******************************************************************************/

LOCAL void pr_text P_((p_scls_t *,bool *));
LOCAL void pr_text(pp_scls,p_white)
/* This function parses a sequence of zero or more text tokens (until it runs */
/* into a non-text token) and constructs a list of scraps containing the text */
/* pointed to by the tokens. In addition the function writes TRUE to its      */
/* second argument iff all of the text scraps are whitespace.                 */
p_scls_t *pp_scls;
bool     *p_white;
{
 *pp_scls=ls_cre(sizeof(sc_t));
 *p_white=TRUE;

 while (p_tk->tk_kind==TK_TEXT)
   {
    *p_white = *p_white && p_tk->tk_sc.sc_white;
    ls_add(*pp_scls,PV &p_tk->tk_sc);
    next_tk(FALSE);
   }
}

LOCAL void pr_text_tks P_((p_tkls_t *,bool *));
LOCAL void pr_text_tks(pp_tkls,p_white)
/* This function parses a sequence of zero or more text tokens (until it runs */
/* into a non-text token) and constructs a list of tokens containing the text */
/* pointed to by the tokens. In addition the function writes TRUE to its      */
/* second argument iff all of the text scraps are whitespace.                 */
p_tkls_t *pp_tkls;
bool     *p_white;
{
 *pp_tkls=ls_cre(sizeof(tk_t));
 *p_white=TRUE;

 while (p_tk->tk_kind==TK_TEXT)
   {
    *p_white = *p_white && p_tk->tk_sc.sc_white;
    ls_add(*pp_tkls,PV p_tk);
    next_tk(FALSE);
   }
}

/******************************************************************************/

LOCAL void pr_white P_((p_scls_t *));
LOCAL void pr_white(pp_scls)
/* Same as pr_text, but generates an error if the text is non-white. */
p_scls_t *pp_scls;
{
 bool iswhite;
 ps_t ps;
 ASSIGN(ps,p_tk->tk_ps);
 pr_text(pp_scls,&iswhite);
 if (!iswhite)
    lr_err(&ps,"Expecting whitespace text.");
}

/******************************************************************************/

LOCAL void pr_name P_((char *));
LOCAL void pr_name(p_name)
/* Parses a single FunnelWeb name (e.g. "@<Sloth@>" and "@#K"). */
char *p_name;   /* Really should be of type p_name_t but this caused trouble. */
{
 uword namelen = 0;

 /* Deal with the special case of a token name. */
 if (p_tk->tk_kind==TK_NAME)
   {
    p_name[0]=p_tk->tk_gen;
    p_name[1]=EOS;
    next_tk(TRUE);
    return;
   }

 ass_tk(TK_ONAM);
 next_tk(TRUE);

 while (TRUE)
    switch (p_tk->tk_kind)
      {
       case TK_TEXT:
         {
          /* Copy the text token to the name array, checking all the time. */
          char  *p;
          for (p=p_tk->tk_sc.sc_first; p<=p_tk->tk_sc.sc_last; p++)
            {
             if (*p==EOL)
               {
                lr_err(TKPS,"Names cannot cross lines.");
                recover();
               }
             namelen++;
             if (namelen>NAME_MAX)
               {
                lr_err(TKPS,"Name is too long.");
                sprintf(linet1,
                   "The maximum length of a legal name is %lu characters.",
                   (unsigned long) NAME_MAX);
                lr_mes(TKPS,linet1);
                recover();
               }
             p_name[namelen-1] = *p;
            }
          next_tk(TRUE);
          break;
         }
       case TK_CNAM:
          /* We finish successfully if we hit a close name token "@>". */
          p_name[namelen]=EOS;
          next_tk(TRUE);
          return;
       default:
          lr_err(TKPS,"Illegal character or symbol in name.");
          recover();
      } /* End switch */
}

/******************************************************************************/

LOCAL void pr_dctxt P_((void));
LOCAL void pr_dctxt()
/* Parse a major text chunk. */
{
 dc_t  dc;
 bool  dummybool;
 ps_t  pstext;

 ass_tk(TK_TEXT);

 ASSIGN(pstext,p_tk->tk_ps);
 pr_text(&dc.dc_text,&dummybool);
 ASSIGN(dc.dc_ps,pstext);
 dc.dc_kind=DC_TEXT;
 ls_add(document_list,PV &dc);
}

/******************************************************************************/

LOCAL void sendtype P_((ty_k_t));
LOCAL void sendtype(ty_kind)
/* Send a document component of kind typesetter directive with no attributes. */
ty_k_t ty_kind;
{
 dc_t dc;
 ASSIGN(dc.dc_ps,p_tk->tk_ps);
 dc.dc_kind = DC_TYPE;
 dc.dc_ty.ty_kind=ty_kind;
 ls_add(document_list,PV &dc);
}

/******************************************************************************/

LOCAL void pr_lit P_((void));
LOCAL void pr_lit()
/* Parse a string delimited by literal typeset directives e.g. @{sloth@}.     */
{
 /* Check and get past opening directive. */
 ass_tk(TK_ODEF);
 sendtype(TY_OLIT);

 /* Move past the opening directive and parse the sandwich text. */
 next_tk(TRUE);
 if (p_tk->tk_kind!=TK_TEXT)
   {
    lr_err(TKPS,"Text expected after open literal token \"@{\".");
    if (p_tk->tk_kind==TK_CDEF)
       lr_mes(TKPS,"Sorry, empty literal strings are not allowed.");
    recover();
   }
 pr_dctxt();

 /* Check and parse the closing directive. */
 pr_token(TK_CDEF);
 sendtype(TY_CLIT);
}

/******************************************************************************/

LOCAL void pr_emp P_((void));
LOCAL void pr_emp()
/* Parse a string delimited by emphasis typeset directives e.g. @/sloth@/.    */
{
 /* Check and get past opening directive. */
 ass_tk(TK_EMPH);
 sendtype(TY_OEMP);

 /* Move past the opening directive and parse the sandwich text. */
 next_tk(TRUE);
 if (p_tk->tk_kind!=TK_TEXT)
   {
    lr_err(TKPS,"Text expected after open emphasise token \"@/\".");
    if (p_tk->tk_kind==TK_EMPH)
       lr_mes(TKPS,"Sorry, empty emphasised strings are not allowed.");
    recover();
   }
 pr_dctxt();

 /* Check and parse the closing directive. */
 pr_token(TK_EMPH);
 sendtype(TY_CEMP);
}

/******************************************************************************/

LOCAL void pr_npag P_((void));
LOCAL void pr_npag()
/* Parse a newpage token. */
{
 ass_tk(TK_NPAG);
 sendtype(TY_NPAG);
 pr_token(TK_NPAG);
}

/******************************************************************************/

LOCAL void pr_tocs P_((void));
LOCAL void pr_tocs()
/* Parse a table of contents token. */
{
 ass_tk(TK_TOCS);
 sendtype(TY_TOCS);
 pr_token(TK_TOCS);
}

/******************************************************************************/

LOCAL void pr_skip P_((void));
LOCAL void pr_skip()
/* Parse a skip token. */
{
 dc_t dc;
 ass_tk(TK_SKIP);
 ASSIGN(dc.dc_ps,p_tk->tk_ps);
 dc.dc_kind = DC_TYPE;
 dc.dc_ty.ty_kind=TY_SKIP;
 dc.dc_ty.ty_mm=p_tk->tk_gen;
 ls_add(document_list,PV &dc);
 pr_token(TK_SKIP);
}

/******************************************************************************/

LOCAL void pr_titl P_((void));
LOCAL void pr_titl()
/* Parse a title token. Bascially moving bones from one grave to another.     */
{
 dc_t dc;
 ass_tk(TK_TITL);
 ASSIGN(dc.dc_ps,p_tk->tk_ps);
 dc.dc_kind        = DC_TYPE;
 dc.dc_ty.ty_kind  = TY_TITL;
 dc.dc_ty.ty_font  = p_tk->tk_gen / LRFT_PACK;
 dc.dc_ty.ty_align = p_tk->tk_gen % LRFT_PACK;
 ASSIGN(dc.dc_ty.ty_sc,p_tk->tk_sc);
 ls_add(document_list,PV &dc);
 pr_token(TK_TITL);
}

/******************************************************************************/

LOCAL void pr_sec P_((void));
LOCAL void pr_sec()
/* Parse a new section marker ("@A.. and @*") and its optional name.          */
{
 ps_t   secps;     /* Position of this new section.                           */
 ubyte  level;     /* Level number of new section.                            */
 bool   has_name;  /* Set to TRUE iff the section has a name.                 */
 name_t name;      /* Name of the section (if it has a name).                 */

 /* If called, a new section marker must have been seen. */
 ass_tk(TK_NSEC);

 /* Grab a copy of the position of the start of the section. */
 ASSIGN(secps,p_tk->tk_ps);

 /* Grab the level number of the section marker. Move to the next token. */
 level=p_tk->tk_gen;
 next_tk(TRUE);

 /* Check for a discontinuity in level. */
 if (level>sn_lev(&last_sn)+1)
   {
    if (sn_lev(&last_sn)==0)
       lr_err(&secps,"The first section in a document must be an @A section.");
    else
      {
       sprintf(linet1,"The next section (at line %lu) is too deep.",
                   (unsigned long) secps.ps_line);
       lr_mes(&pssection,linet1);
       lr_err(&secps,"This section is more than one level deeper than the last");
       sprintf(linet1,"section (at line %lu). Example: @B followed by @D is not allowed.",
                   (unsigned long) pssection.ps_line);
       lr_mes(&secps,linet1);
      }
    /* At this point we know that the section structure of the document is    */
    /* faulty and that the weaver will never be invoked. As such the          */
    /* principal concern becomes that of error recovery. The best we can do   */
    /* there is to set to the specified level regardless of how silly it is.  */
    /* This ensures that we generate section errors only relative to the      */
    /* previous section. Thus, we avoid cascades of errors, if, for example   */
    /* the user mistypes an @A at the beginning of a FunnelWeb document.      */
    /* Once an error has occurred we don't care about the actual numbers.     */
    sn_set(&last_sn,level);
   }

 /* Record the position. */
 ASSIGN(pssection,secps);

 /* Parse optional name (e.g. "@<Sloth@>"). */
 if (p_tk->tk_kind==TK_ONAM || p_tk->tk_kind==TK_NAME)
   {
    pr_name(name);
    has_name=TRUE;
   }
 else
   {
    strcpy(name,"No name given");
    has_name=FALSE;
   }

 /* Actually increment the section number at the specified level. */
 sn_inc(&last_sn,level);

 /* Place all the information we have into a document component structure     */
 /* and add it to the document list.                                          */
 {
  dc_t dc;
  ASSIGN(dc.dc_ps,secps);
  dc.dc_kind = DC_TYPE;
  dc.dc_ty.ty_kind=TY_NSEC;
  ASSIGN(dc.dc_ty.ty_sn,last_sn);
  dc.dc_ty.ty_isnam = has_name;
  strcpy(&dc.dc_ty.ty_name[0],&name[0]);
  ls_add(document_list,PV &dc);
  ls_tai(document_list,PPV &p_secdc);
 }
}

/******************************************************************************/

LOCAL void rem_name P_((char *));
LOCAL void rem_name(p_name)
/* rem_name stands for REMember NAME. rem_name accepts a pointer to a name.   */
/* It looks up the name in the global macro table, and if the name is in the  */
/* table performs no action. If the name isn't in the table, it creates a new */
/* entry for the name, filling the entry's fields with "blank" values.        */
/* The rem_name function should not be seen as recording the definition of a  */
/* macro. This is handled by the md_isdef field. Instead the rem_name macro   */
/* should be viewed as just creating the space in the table for the info.     */
char * p_name;  /* Really should be of type p_name_t but this caused trouble. */
{
 if (!tb_itb(macro_table,PV p_name))
   {
    p_ma_t p_macro=(p_ma_t) mm_temp(sizeof(ma_t));
    strcpy(&p_macro->ma_name[0],&p_name[0]);
    p_macro->ma_calls         = ls_cre(sizeof(mc_t));
    p_macro->ma_defn.md_isdef = FALSE;
    p_macro->ma_actn          = ls_cre(sizeof(p_elll_t));
    tb_ins(macro_table,PV p_name,PV &p_macro);
   }
}

/******************************************************************************/

LOCAL void chk_whex P_((p_ps_t,p_ells_t,p_scls_t *));
LOCAL void chk_whex(p_ps,p_ex,pp_white)
/* This function should really be a subfunction of pr_plist. However, C       */
/* doesn't allow nested functions so we have to put it here. This function is */
/* called after pr_plist has just parsed an opening expression followed by    */
/* @". This means that the expression should consist of whitespace crud. Our  */
/* mission here is to check that it really does contain only whitespace crud  */
/* and return a text list containing the crud. If, on the other hand, it      */
/* contains meatier items, we have to call recover().                         */
p_ps_t   p_ps;       /* Position of the start of the expression.              */
p_ells_t p_ex;       /* The expression that we have to check out.             */
p_scls_t *pp_white;  /* The place to put the resultant whitespace list.       */
{
 p_el_t p_el;

 /* If the expression is empty, we can return an empty list. */
 if (ls_len(p_ex)==0)
   {
    *pp_white=ls_cre(sizeof(sc_t));
    return;
   }

 /* If there is more than one element, there is ...trouble. */
 if (ls_len(p_ex) > 1) goto trouble;

 /* Extract the first element of the list. */
 ls_fir(p_ex); ls_nxt(p_ex,PPV &p_el);

 /* If it's not text, there is ...trouble. */
 if (p_el->el_kind != EL_TEXT) goto trouble;

 /* If the text isn't lilly white, there is ...trouble. */
 {
  p_tkls_t p_tkls = p_el->el_text;
  p_scls_t p_scls = ls_cre(sizeof(sc_t));
  p_tk_t   p_tk;
  ls_fir(p_tkls);
  while (TRUE)
    {
     ls_nxt(p_tkls,PPV &p_tk);
     if (p_tk==NULL) break;
     if (!p_tk->tk_sc.sc_white) goto trouble;
     ls_add(p_scls,PPV &p_tk->tk_sc);
    }
  /* If we got this far, we know that the expression contains a single */
  /* element and that that element is a text list and that that text   */
  /* list consists entirely of whitespace. We can now return it.       */
  *pp_white=p_scls;
  return;
 }

 /* We COULD start dissecting the expression and issuing detailed specific    */
 /* error messages. However, the general approach is cleaner and so a general */
 /* error message is used.                                                    */
 trouble:
 lr_err(       p_ps,"Everything from here...");
 lr_mes(TKPS,"...to here should be whitespace.");
 lr_mes(TKPS,"Use of @\" to delimit macro parameters is optional, but");
 lr_mes(TKPS,"if they are used, any surrounding text must be white.");
 recover();
}

/******************************************************************************/

LOCAL void pr_plist P_((p_elll_t *, p_scll_t *, p_scll_t *,p_ma_t));
LOCAL void pr_plist(pp_plist,p_before,p_after,p_curmac)
/* This function parses an optional parameter list. If the current token is   */
/* not TK_OPAR, then it is assumed that no list is present and no tokens are  */
/* consumed and empty lists are returned.                                     */
/* The three lists returned are:                                              */
/*    A list of parameters each being a pointer to a list of elements.        */
/*    A list of whitespace blocks being the space before each parameter.      */
/*    A list of whitespace blocks being the space after  each parameter.      */
/* The last parameter p_curmac should be supplied by the caller and should    */
/* contain a pointer to the macro currently being parsed.                     */
p_elll_t *pp_plist;
p_scll_t *p_before;
p_scll_t *p_after;
p_ma_t   p_curmac;
{
 /* Initialize all the result lists to empty. */
 *pp_plist = ls_cre(sizeof(p_ells_t));
 *p_before = ls_cre(sizeof(p_scls_t));
 *p_after  = ls_cre(sizeof(p_scls_t));

 /* The parameter list is optional. If it isn't there we assume a null one.   */
 if (p_tk->tk_kind!=TK_OPAR)
    return;
 next_tk(TRUE);

 /* Now parse the parameter list, one parameter during each iteration. */
 while (TRUE)
   {
    ps_t     exp_ps;
    p_ells_t p_ex;
    p_scls_t p_white;

    /* Things get a little tricky here because the double quotes around       */
    /* parameters are optional (per parameter). Thus the following calls are  */
    /* all legal (and functionally identical):                                */
    /*    @<Sloth@>@( @"walrus@" @, @"aardvark@" @)                           */
    /*    @<Sloth@>@(walrus@,       @"aardvark@" @)                           */
    /*    @<Sloth@>@(walrus@,aardvark@)                                       */

    /* Note the position of the start of this parameter slot. */
    ASSIGN(exp_ps,p_tk->tk_ps);

    /* Because we face either crud text or an expression, we parse an exp.    */
    pr_exp(&p_ex,p_curmac);

    /* Now take a look at the next token. If it is @" we know that we have    */
    /* been parsing whitespace crud. If it is @, or @) we know that we have   */
    /* been parsing the parameter expression itself.                          */
    if (p_tk->tk_kind==TK_COMA || p_tk->tk_kind==TK_CPAR)
      {
       p_scls_t p_scls = ls_cre(sizeof(sc_t));
       ls_add(*p_before,PV &p_scls);  /* Add empty whitespace to crud list.   */
       ls_add(*pp_plist,PV &p_ex);    /* Add expression to parameter list.    */
       ls_add(*p_after ,PV &p_scls);  /* Add empty whitespace to crud list.   */
      }
    else
       if (p_tk->tk_kind==TK_QUOT)
         {
          /* After parsing the expression we hit a @". This means that the    */
          /* expression just parsed SHOULD turn out to contain a single       */
          /* element consisting of a white space text list.                   */
          chk_whex(&exp_ps,p_ex,&p_white);
          ls_add(*p_before,PV &p_white);

          /* Get past the quote. */
          next_tk(TRUE);

          /* Parse the expression and add it to the parameter list. */
          pr_exp(&p_ex,p_curmac); ls_add(*pp_plist,PV &p_ex);

          /* Parse the quote to move onto the whitespace. */
          pr_token(TK_QUOT);

          /* Parse the whitespace after the parameter. */
          {p_scls_t p_white; pr_white(&p_white); ls_add(*p_after,PV &p_white);}
         }
       else
          {lr_err(TKPS,"Expecting @\" or @, or @)."); recover();}

    /* The parameter list can now end (TK_CPAR) or continue (TK_COMA). */
    if (p_tk->tk_kind==TK_COMA)
       next_tk(TRUE);
    else
       if (p_tk->tk_kind==TK_CPAR)
          {next_tk(TRUE);return;}
       else
          {lr_err(TKPS,"Expecting @, or @)."); recover();}
   } /* End while */
}

/******************************************************************************/

LOCAL void pr_invelt P_((p_el_t,p_ma_t));
LOCAL void pr_invelt(p_el,p_curmac)
/* Parses an "invocation element" which is just FunnelWebSpeak for "macro     */
/* call". Upon entry the current token must be TK_ONAM or TK_NAME which       */
/* presumably is the start of a macro call. Returns a pointer to an element   */
/* object describing the call. Does some other macro table stuff too.         */
/* p_curmac should be supplied by the caller and should be a pointer to the   */
/* macro currently being parsed.                                              */
p_el_t p_el;
p_ma_t p_curmac;
{
 name_t   name;      /* Name of the macro being invoked.                      */
 ps_t     mc_ps;     /* Position of the start of the macro invocation.        */
 mc_t     mc;        /* Macro call object that describes the invocation.      */
 p_ma_t   p_callee;  /* Pointer to the macro object of the target macro.      */
 p_elll_t parlist;   /* The parameter list of the invocation.                 */
 p_scll_t before;    /* Whitespace before each parameter in the param list.   */
 p_scll_t after;     /* Whitespace after  each parameter in the param list.   */

 /* We shouldn't have been called unless we have seen the start of a name. */
 ass_tks(TK_ONAM,TK_NAME);

 /* Note the position of the start of the invocation. */
 mc_ps=p_tk->tk_ps;

 /* Parse the invocation (name and optional parameter list). */
 pr_name(name); pr_plist(&parlist,&before,&after,p_curmac);

 /* Ensure that there is an entry for this macro name in the macro table. */
 rem_name(name);

 /* Construct a macro call object describing the call and add it to the */
 /* callee macro's call list.                                           */
 /* Note: The +1 in sequence+1 is because the sequence number is incremented  */
 /* at the end of each macro definition and we are only halfway here.         */
 mc.mc_seq  = sequence+1;
 mc.mc_ps   = mc_ps;
 mc.mc_npar = ls_len(parlist);
 tb_loo(macro_table,PV name,PV &p_callee);
 ls_add(p_callee->ma_calls,PV &mc);

 /* Write an invocation element describing the call to the parameter. */
 p_el->el_kind  = EL_INVC;
 p_el->el_p_mac = p_callee;
 p_el->el_parls = parlist;
 p_el->el_pretx = before;
 p_el->el_postx = after;
}

/******************************************************************************/

LOCAL void pr_txtelt P_((p_el_t));
LOCAL void pr_txtelt(p_el)
/* Parses a text element. Upon entry, the current token must be of type       */
/* TK_TEXT. Writes a text element into its parameter.                         */
p_el_t p_el;
{
 p_tkls_t p_tkls;
 bool     dummy;
 ass_tk(TK_TEXT);
 pr_text_tks(&p_tkls,&dummy);
 p_el->el_kind = EL_TEXT;
 p_el->el_text = p_tkls;
}

/******************************************************************************/

LOCAL void pr_parelt P_((p_el_t,p_ma_t));
LOCAL void pr_parelt(p_el,p_curmac)
/* Parses a parameter element (e.g. @5). Writes the resultant parameter       */
/* element object to the first parameter. The second parameter should be      */
/* supplied by the caller and should be a pointer to the macro being parsed.  */
p_el_t p_el;
p_ma_t p_curmac;
{
 /* We have to be sitting on a parameter token. */
 ass_tk(TK_PARM);

 /* Complain if the parameter does not exist. */
 if (p_tk->tk_gen > p_curmac->ma_defn.md_npar)
   {
    sprintf(linet1,"Macro being defined has only %lu parameter%s.",
            (unsigned long) p_curmac->ma_defn.md_npar,
            p_curmac->ma_defn.md_npar==1 ? "" : "s");
    lr_err(TKPS,linet1);
   }

 /* Write a parameter element to the function parameter. */
 p_el->el_kind  = EL_PARM;
 p_el->el_parno = p_tk->tk_gen;
 p_el->el_which = p_curmac;

 /* Move on to the token following the parameter token. */
 next_tk(TRUE);
}

/******************************************************************************/

LOCAL void pr_exp(p_ex,p_curmac)
/* Parses an expression and writes an expression list to the first parameter. */
/* The second parameter should be supplied by the user and should be a        */
/* pointer to the macro currently being parsed.                               */
p_ells_t *p_ex;
p_ma_t   p_curmac;
{
 p_ells_t ex = ls_cre(sizeof(el_t));

 while (TRUE)
   {
    el_t el;
    switch (p_tk->tk_kind)
      {
       case TK_TEXT: pr_txtelt(&el);          break;
       case TK_NAME:
       case TK_ONAM: pr_invelt(&el,p_curmac); break;
       case TK_PARM: pr_parelt(&el,p_curmac); break;
       default     : *p_ex=ex;                return;
      }
    ls_add(ex,PV &el);
   }
}

/******************************************************************************/

LOCAL void pr_formal P_((uword *,p_ps_t));
LOCAL void pr_formal(p_numpar,p_ps)
/* A FunnelWeb formal parameter list looks something like this: "@(@5@)".     */
/* This function parses a parameter list if present and returns the number of */
/* parameters in the formal parameter list. The function also returns the     */
/* position the parameter list.                                               */
uword  *p_numpar;
p_ps_t  p_ps;
{
 /* If the parameter list is absent, we default to having zero parameters and */
 /* making the position of the parameter list the position of the next token. */
 *p_numpar = 0;
 *p_ps     = p_tk->tk_ps;

 /* Parse the parameter list only if one is present. */
 if (p_tk->tk_kind==TK_OPAR)
   {
    /* Move to the parameter token and get its number and position. */
    next_tk(TRUE);
    check_tk(TK_PARM);
    *p_numpar=p_tk->tk_gen;
    *p_ps=p_tk->tk_ps;

    /* Parse the end of the formal parameter list. */
    next_tk(TRUE);
    pr_token(TK_CPAR);
   }
}

/******************************************************************************/

LOCAL void pr_number P_((bool *,bool *));
LOCAL void pr_number(p_iszer,p_isman)
/* Parses optional @Z@M after parameter list. */
bool *p_iszer;
bool *p_isman;
{
 *p_iszer=FALSE;
 *p_isman=FALSE;

 /* The following parse allows zero, one or both of @Z@M, but in order. */

 /* Grab an @Z if it is there. */
 if (p_tk->tk_kind==TK_ZERO)
   {
    next_tk(TRUE);
    *p_iszer=TRUE;
   }

 /* Grab an @M too if it is there. */
 if (p_tk->tk_kind==TK_MANY)
   {
    next_tk(TRUE);
    *p_isman=TRUE;
   }
}

/******************************************************************************/

LOCAL void pr_equals P_((bool *,p_ps_t));
LOCAL void pr_equals(isadd,p_ps)
/* Parses optional "==" or "+=". Sets *isadd==TRUE iff "+=" parsed else FALSE.*/
/* Sets *p_ps to the position of the equals.                                  */
bool   *isadd;
p_ps_t p_ps;
{
 p_scls_t p_scls;
 bool     dummy;

 /* Grab a copy of the position of the equals (even if it is not there)    . */
 ASSIGN(*p_ps,p_tk->tk_ps);

 /* If the equals isn't there, we default to FALSE. */
 *isadd=FALSE;
 if (p_tk->tk_kind!=TK_TEXT) return;

 /* Parse text tokens producing a text list. */
 pr_text(&p_scls,&dummy);

 /* Compare the text list with the assignment constant strings. */
 if (eq_txst(p_scls,"==")) {*isadd=FALSE; ls_des(p_scls); return;}
 if (eq_txst(p_scls,"+=")) {*isadd=TRUE;  ls_des(p_scls); return;}

 lr_err(p_ps,"Expecting \"==@{\" or \"+=@{\" or just \"@{\".");
 lr_mes(p_ps,"(or @Z or @M if they have not already appeared).");
 lr_mes(p_ps,"Note: FunnelWeb is intolerant of spaces at this point.");
 ls_des(p_scls);
 recover();
}

/******************************************************************************/

LOCAL bool checkdef P_((p_ma_t,bool,ulong,bool,bool,bool,
                        p_ps_t,p_ps_t,p_ps_t,p_ps_t));
LOCAL bool checkdef (p_ma,is_file,numpar,iszer,isman,isadd,
                        p_psnam,p_psfor,p_pseql,p_psnum)
/* This function performs all sorts of checks on a macro definition.          */
/* If there is anything wrong, it generates and error and calls recover().    */
/* This would be best as a local function but because C doesn't have local    */
/* functions we have to use millions of parameters instead.                   */
p_ma_t p_ma;
bool   is_file;
ulong  numpar;
bool   iszer;
bool   isman;
bool   isadd;
p_ps_t p_psnam;
p_ps_t p_psfor;
p_ps_t p_pseql;
p_ps_t p_psnum;
{
 bool semerr = FALSE;

 /* CHECK INTERNAL INCONSISTENCIES */
 /* ------------------------------ */
 /* Complain if a file macro has a parameter list. */
 if (is_file && numpar>0)
   {
    lr_err(p_psfor,"Macros attached to output files cannot be parameterized.");
    lr_mes(p_psfor,"Reason: No actual parameters would be available during");
    lr_mes(p_psfor,"        output file generation.");
    semerr=TRUE;
   }

 /* Complain if a file macro is declared additive. */
 if (is_file && isadd)
   {
    lr_err(p_pseql,"Macros attached to output files cannot be additive.");
    lr_mes(p_pseql,"Reason: Preventing this makes it easy to find output");
    lr_mes(p_pseql,"file macros later, because there will be exactly one");
    lr_mes(p_pseql,"@O declaration in the input file for each output file.");
    lr_mes(p_pseql,"To do what you are trying to do, just create an additive");
    lr_mes(p_pseql,"bridging macro, like this:");
    lr_mes(p_pseql,"   @O@<prog.c@>@{@<Bridge@>@}");
    lr_mes(p_pseql,"   @$@<Bridge@>+=@{void stringhack()...@}");
    lr_mes(p_pseql,"   @$@<Bridge@>+=@{main()...@}");
    semerr=TRUE;
   }

 /* Complain if a file macro has a name that is too long. */
#if defined(__cplusplus) || defined(__STDC__)
 if (is_file && strlen(&p_ma->ma_name[0])>(size_t)FILENAME_MAX)
#else
 if (is_file && strlen(&p_ma->ma_name[0])>FILENAME_MAX)
#endif
   {
    lr_err(p_psnam,
    "File macro's name is longer than the maximum permissible filename length.");
    sprintf(linet1,"Maximum filename length is %lu characters.",
                   (unsigned long) FILENAME_MAX);
    lr_mes(p_psnam,linet1);
    semerr=TRUE;
   }

 /* Complain if a file macro has "zero" or "many" attributes. */
 if (is_file && (iszer || isman))
   {
    lr_err(p_psnum,"Macros attached to output files cannot have @Z or @M.");
    lr_mes(p_psnum,"Reason: They are always called once to generate their");
    lr_mes(p_psnum,"output file and they cannot be called from other macros.");
    lr_mes(p_psnum,"Hence they are always called exactly once and so there");
    lr_mes(p_psnum,"can be no need for @Z or @M in their declarations.");
    semerr=TRUE;
   }

 /* COMPARE WITH EARLIER DEFINITIONS */
 /* -------------------------------- */
 /* Don't do this section if no previous definition exists. */
 if (!p_ma->ma_defn.md_isdef) goto finish;

 /* Assert: An earlier definition of this macro exists. */

 /* Old definition is a full definition, not admitting partial ones now. */
 if (!p_ma->ma_defn.md_isadd)
   {
    if (isadd)
      {
       sprintf(linet1,"A full definition of this macro appears at line %lu.",
                      (ulong) p_ma->ma_defn.md_ps.ps_line);
       lr_err(p_psnam,linet1);
       lr_mes(p_psnam,"Full and additive definitions of the same macro cannot coexist.");
      }
    else
      {
       sprintf(linet1,"This macro is already fully defined (at line %lu).",
                      (ulong) p_ma->ma_defn.md_ps.ps_line);
       lr_err(p_psnam,linet1);
      }
    semerr=TRUE;
   }

 /* Old definition is partial but new definition is full. */
 if (p_ma->ma_defn.md_isadd && !isadd)
   {
    sprintf(linet1,"An additive definition of this macro appears at line %lu.",
                   (ulong) p_ma->ma_defn.md_ps.ps_line);
    lr_err(p_psnam,linet1);
    lr_mes(p_psnam,"Full and additive definitions of the same macro cannot coexist.");
     semerr=TRUE;
   }

 /* Make sure that non-first body parts of additive macros do not have params.*/
 if (isadd && (numpar>0))
   {
    lr_err(p_psfor,"The formal parameter list of an additive macro");
    lr_mes(p_psfor,"must be placed only in the first definition part.");
    sprintf(linet1,"The first part of this macro appears at line %lu.",
                   (ulong) p_ma->ma_defn.md_ps.ps_line);
    lr_mes(p_psfor,linet1);
    semerr=TRUE;
   }

 /* Complain if number attributes are being attached to an additive. */
 if (isadd && (iszer || isman))
   {
    lr_err(p_psnum,"@Z and @M modifiers for additive macros must");
    lr_mes(p_psnum,"be placed only in the first definition part.");
    sprintf(linet1,"The first part of this macro appears at line %lu.",
                   (ulong) p_ma->ma_defn.md_ps.ps_line);
    lr_mes(p_psnum,linet1);
    semerr=TRUE;
   }

 finish:
 if (semerr)
   {
    lr_mes(p_psnam,"Macro definition ignored.");
    recover();
   }
 return TRUE;
}

/******************************************************************************/

LOCAL void pr_macro P_((void));
LOCAL void pr_macro()
/* This function parses a single macro definition. Upon entry, the current    */
/* token must be TK_MDEF, TK_NDEF or TK_FDEF.                                   */
{
 ps_t     ps_mac;   /* Position of start of the macro definition.             */
 bool     is_nonp;  /* TRUE iff definition starts with @N instead of @$.      */
 bool     is_file;  /* TRUE iff definition starts with @O instead of @$.      */
 name_t   name;     /* The macro name appearing in this definition.           */
 p_ma_t   p_ma;     /* Pointer to the macro record corresponding to 'name'.   */
 ps_t     ps_name;  /* Position of the macro name.                            */
 ps_t     ps_form;  /* Position of the formal parameter list.                 */
 ps_t     ps_equal; /* Position of the equals.                                */
 ps_t     ps_num;   /* Position of number attributes.                         */
 uword    numpar;   /* Number of parameters in formal parameter list.         */
 bool     iszer;    /* TRUE iff macro is allowed to be called zero times.     */
 bool     isman;    /* TRUE iff macro is allowed to be called more than once. */
 bool     isadd;    /* TRUE iff equals parsed here is "+=" not "==".          */
 p_ells_t ex;       /* Expression constituting this macro body part.          */
 bool     hasname;  /* TRUE iff current section already has a name.           */

 /* We should not have got in here without seeing a definition token. */
 ass_tk3(TK_MDEF,TK_NDEF,TK_FDEF);

 /* Grab a copy of the position of the start of the macro. */
 ASSIGN(ps_mac,p_tk->tk_ps);

 /* If we have seen a macro definition token then it means that the user is   */
 /* TRYING to define a macro. The macro may or may not provoke errors. In     */
 /* either case though we do not want to hassle the user with errors about    */
 /* nameless sections not containing macros if it is obvious that an attempt  */
 /* to define a macro has been made. So here we set the name flag after       */
 /* having a look at it so we can use its value later.                        */
 if (sn_lev(&last_sn)>0)
   {
    as_cold(p_secdc->dc_kind==DC_TYPE,"pr_macro: section processing error (1).");
    as_cold(p_secdc->dc_ty.ty_kind==TY_NSEC,"pr_macro: section processing error (2).");
    hasname=p_secdc->dc_ty.ty_isnam;
    p_secdc->dc_ty.ty_isnam=TRUE;
   }

 /* Record whether the macro is attached to an product file. */
 is_nonp= (p_tk->tk_kind==TK_NDEF);
 is_file= is_nonp || (p_tk->tk_kind==TK_FDEF);

 /* Parse the macro name. Record its position. Ensure that there is an entry  */
 /* in the macro table for this macro name (i.e. create one if not there).    */
 next_tk(TRUE);
 if (p_tk->tk_kind!=TK_ONAM && p_tk->tk_kind!=TK_NAME)
   {
    lr_err(TKPS,"Macro name expected (@<...@> or @#c).");
    recover();
   }
 ps_name=p_tk->tk_ps;
 pr_name (name);
 rem_name(name);
 tb_loo(macro_table,PV name,PV &p_ma);
 if (is_file)
   {
    if (strchr (name, ' ') != NULL)
      {
       /* We say whitespace here because tabs get replaced with spaces */
       lr_err(&ps_name,"Product file name contains whitespace.");
      }
    if (strchr (name, '/') != NULL)
      {
       lr_err(&ps_name,"Product file name contains a slash.");
      }
   }

 /* Parse the optional formal parameter list and the equals. */
 /* Extract positioning and other information.               */
 pr_formal(&numpar,&ps_form );
 ASSIGN(ps_num,p_tk->tk_ps);
 pr_number(&iszer, &isman);
 pr_equals(&isadd ,&ps_equal);

 /* Perform semantic checks on whether this definition is valid.              */
 checkdef(p_ma,is_file,numpar,iszer,isman,isadd,
               &ps_name,&ps_form,&ps_equal,&ps_num);

 /* If we have got this far, we know that we have parsed a valid macro        */
 /* definition except possibly for the actual expression body.                */
 /* If this is the first definition of this macro, establish its definition.  */
 if (!p_ma->ma_defn.md_isdef)
   {
    p_ma->ma_defn.md_isdef = TRUE;
    ASSIGN(p_ma->ma_defn.md_ps,ps_mac);
    p_ma->ma_defn.md_npar  = numpar;
    p_ma->ma_defn.md_isadd = isadd;
    p_ma->ma_defn.md_iszer = iszer;
    p_ma->ma_defn.md_isman = isman;
    p_ma->ma_defn.md_isfil = is_file;
    p_ma->ma_defn.md_isnop = is_nonp;
    p_ma->ma_defn.md_body  = ls_cre(sizeof(bp_t));
    if (is_file) {
      tb_ins(file_table,PV name,PV &p_ma);
      if (is_nonp) wf_wl(&f_n, name);
    }
   }

 /* Parse the body of this macro definition. */
 pr_token(TK_ODEF); pr_exp(&ex,p_ma); pr_token(TK_CDEF);

 /* We are now clear to execute the effects of the macro on our tables.       */
 /* First we bump up the sequence number.                                     */
 sequence++;

 {
  /* Construct a body part object containing the information in this          */
  /* definition and append it to the list of body parts in the macro record.  */
  bp_t bp;
  bp.bp_ex  = ex;
  bp.bp_seq = sequence;
  bp.bp_ps  = ps_name;
  ls_add(p_ma->ma_defn.md_body,PV &bp);
 }

 {
  /* Construct a document component object for this definition and append it  */
  /* to the global document component list.                                   */
  dc_t dc;
  ASSIGN(dc.dc_ps,ps_mac);
  dc.dc_kind = DC_MACR;
  dc.dc_p_ma = p_ma;
  dc.dc_part = ls_len(p_ma->ma_defn.md_body);
  ls_add(document_list,PV &dc);
 }

 /* Sections without names inherit the name of their first macro. */
 if (sn_lev(&last_sn)>0 && !hasname)
    strcpy(&p_secdc->dc_ty.ty_name[0],name);
}

/******************************************************************************/

EXPORT void parser()
/* This is the main parser function. This function contains parser            */
/* initialization as well as the main parsing loop to which control is        */
/* returned (by recover()) when an error occurs.                              */
{
 /* Create the lists and tables generated by the parser. */
 macro_table  = tb_cre (sizeof(name_t),sizeof(p_ma_t),(p_kycm_t) cm_name);
 file_table   = tb_cre (sizeof(name_t),sizeof(p_ma_t),(p_kycm_t) cm_name);
 document_list= ls_cre (sizeof(dc_t));

 /* Initialize the section number counter. */
 sequence = 0;
 sn_ini(&last_sn);
 p_secdc  = NULL;

 /* Prime the scanning of the token list. */
 ls_fir(token_list);
 next_tk(FALSE);

 /* This is where we longjmp back to after hitting a nasty syntax error.  */
 /* We don't actually have to test dummyint, as our control state is no   */
 /* different after a syntax error has occurred. Example: We try to parse */
 /* a macro but there is a syntax error. So we skip to the start of the   */
 /* next macro and then longjmp back to here ready to parse the next      */
 /* macro. Thus, there is no need to a fork test.                         */
 (void) setjmp(jmp_pos);

 /* This is the main parser loop which parses major syntactic chunks. */
 while (p_tk->tk_kind != TK_EOF)
    switch (p_tk->tk_kind)
      {
       case TK_NSEC: pr_sec  (); break;
       case TK_TEXT: pr_dctxt(); break;
       case TK_MDEF: pr_macro(); break;
       case TK_NDEF: pr_macro(); break;
       case TK_FDEF: pr_macro(); break;
       case TK_ODEF: pr_lit  (); break;
       case TK_EMPH: pr_emp  (); break;
       case TK_NPAG: pr_npag (); break;
       case TK_TOCS: pr_tocs (); break;
       case TK_SKIP: pr_skip (); break;
       case TK_TITL: pr_titl (); break;
       default:
          lr_err(TKPS,"The parser was at the top level and was expecting");
          lr_mes(TKPS,"one of: {Directive, Text, Macro definition, EOF}.");
          next_tk(FALSE);
          break;
      }

}

/******************************************************************************/
/*                              End of PARSER.C                               */
/******************************************************************************/

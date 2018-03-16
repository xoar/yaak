static char RCSid[] = "$Id: dump.c,v 1.9 1999/10/20 04:56:08 tony Exp $";
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
   26-Jul-1992  AMS  Added RCS id.
   26-Jul-1992  AMS  Fixed bug due to change of text element representation
                     from scraps to tokens.
   12-Nov-1992  AMS  Added & to fix bug revealed by gcc.
   06-Aug-1997	WMW  Add non-product files

##############################################################################*/


/******************************************************************************/
/*                                    DUMP.C                                  */
/******************************************************************************/

#include <ctype.h>
#include "style.h"

#include "as.h"
#include "clock.h"
#include "data.h"
#include "dump.h"
#include "misc.h"

/******************************************************************************/

#define DUMP_WIDTH (80)

/******************************************************************************/

/* The following advance declarations are required because of recursion. */
LOCAL void dm_ex P_((p_wf_t,p_ells_t));

/******************************************************************************/

LOCAL void centerln P_((p_wf_t,uword,int,char *));
LOCAL void centerln(p_wf,width,ch,s)
/* Writes string s in a line surrounded by character ch to specified width.   */
/* Example: centerln(*,20,'-',"sloth") would write: "------ sloth -------"    */
p_wf_t p_wf;
uword  width;
int ch;
char   *s;
{
 uword sidebar,i;
 char  linet2[100];
 /* Warning: linet2 can't be too big, or it will blow the Mac's limited       */
 /* stack space. Perhaps it should be put in the heap with a static pointer.  */

 as_cold(width>=5,"centerln: Width is too small.");
 as_cold(width<=80,"centerln: Width is too large.");
 as_cold(strlen(s) <= width-4,"centerln: Width is too narrow for string.");

 /* Construct a sidebar string. */
 sidebar=(width-strlen(s)-2)/2;
 for (i=0;i<sidebar;i++) linet2[i]=ch;
 linet2[sidebar]=EOS;

 /* Now construct the result string. */
 strcpy(linet1,linet2);
 strcat(linet1," ");
 strcat(linet1,s);
 strcat(linet1," ");
 strcat(linet1,linet2);

 /* If the sidebar division removed a character, and the line is long enough  */
 /* for the user not to notice the imbalance, tack a character on the end.    */
 if (width>40 && strlen(linet1)==width-1)
   {
    uword len=strlen(linet1);
    linet1[len]=ch;
    linet1[len+1]=EOS;
   }

 /* Write the result string to the specified stream. */
 wf_wl(p_wf,linet1);
}

/******************************************************************************/

LOCAL char * fontname P_((ubyte));
LOCAL char * fontname(font)
/* Given a font number, returns a pointer to a static string containing the   */
/* name of the font.                                                          */
ubyte font;
{
 switch (font)
   {
    case FT_NORM: return "Normal";
    case FT_TITL: return "Title";
    case FT_STIT: return "Small Title";
    default     : as_bomb("fontname: Font switch defaulted.");
   }
 /* Keep GCC warnings happy. */
 as_bomb("fontname: Dropped out of switch.");
 return "Failure";
}

/******************************************************************************/

LOCAL char * alignname P_((ubyte));
LOCAL char * alignname(align)
/* Given an alignment number, returns a pointer to a static string containing */
/* the name of the alignment.                                                 */
ubyte align;
{
 switch (align)
   {
    case LR_LEFT: return "Left";
    case LR_RIGH: return "Right";
    case LR_CENT: return "Centre";
    default     : as_bomb("alignname: Alignment switch defaulted.");
   }
 /* Keep GCC warnings happy. */
 as_bomb("alignnamename: Dropped out of switch.");
 return "Failure";
}

/******************************************************************************/

EXPORT void dm_mem(p_wf,p_mem,length)
p_wf_t  p_wf;
char   *p_mem;
ulong   length;
{
 ubyte_ *p_base = (ubyte_ *) p_mem;
 long   len     = length;

 wf_wl(p_wf,"");
 wf_wl(p_wf,"MEMORY DUMP OF MAPPED FILE");
 wf_wl(p_wf,"==========================");
 wf_wl(p_wf,"");
 wf_wr(p_wf,"+-------------------------------------------------+------------------+\n");
 wf_wr(p_wf,"| 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F | 0123456789ABCDEF |\n");
 wf_wr(p_wf,"+-------------------------------------------------+------------------+\n");

 while (len>0)
   {/* Write a single line of 16 bytes per iteration. */
    uword j;
    wf_wr(p_wf,"| ");
    for (j=0;j<16;j++)
       if (j>=len)
          wf_wr(p_wf,"   ");
       else
         {
          char s[10];
          sprintf(s,"%02X ",(unsigned int) p_base[j]);
          wf_wr(p_wf,s);
         }
    wf_wr(p_wf,"| ");
    for (j=0;j<16;j++)
       if (j>=len)
          wf_chr(p_wf,' ');
       else
        {
         char ch=p_base[j];
         /* DON'T use library function "isprint" - it is too loose. */
         /* e.g. The vax "isprint" accepts top bit characters. */
         if (!isascprn(ch)) ch='.';
         wf_chr(p_wf,ch);
        }
    wf_wr(p_wf," |\n");
    p_base+=16;
    len-=16;
   } /* End while */

 wf_wr(p_wf,"+-------------------------------------------------+------------------+\n");
 wf_wl(p_wf,"");
}

/******************************************************************************/

LOCAL void dm_byte P_((p_wf_t,ubyte));
LOCAL void dm_byte(p_wf,b)
/* Dumps a text representation of the given byte to the specified stream.     */
p_wf_t p_wf;
ubyte  b;
{
 char t[10];
 /* DON'T use library function "isprint" - it is too loose. */
 /* e.g. The vax "isprint" accepts top bit characters. */
 if (isascprn(b))
    sprintf(t,"%c",(char) b);
 else
    sprintf(t,"<%03u>",(unsigned) b);
 wf_wr(p_wf,t);
}

/******************************************************************************/

EXPORT void dm_lnls(p_wf)
p_wf_t p_wf;
{
 wf_wl(p_wf,"");
 centerln(p_wf,DUMP_WIDTH,'=',"Start of LINE LIST DUMP");
 wf_wl(p_wf,"");
           /*12345678901234567890123456789012345678901234567890123456789012345678901234567890*/
 wf_wl(p_wf,"Globl Local| Text");
 wf_wl(p_wf,"-----------+--------------------------------------------------------------------");
 ls_fir(line_list);
 while (TRUE)
   {
    ln_t *p_line;
    char *p;
    ls_nxt(line_list,PPV &p_line);
    if (p_line==NULL) break;
    sprintf(linet1,"%05lu %05lu| ",
            (ulong) p_line->ln_global,
            (ulong) p_line->ln_local);
    wf_wr(p_wf,linet1);
    for (p=p_line->ln_body.sc_first; p<=p_line->ln_body.sc_last; p++)
       dm_byte(p_wf,*((ubyte_ *)p));
    wf_wl(p_wf,"");
   }
 wf_wl(p_wf,"-----------+--------------------------------------------------------------------");
 wf_wl(p_wf,"Globl Local| Text");
 wf_wl(p_wf,"");
 centerln(p_wf,DUMP_WIDTH,'=',"End of LINE LIST DUMP");
 wf_wl(p_wf,"");
}

/******************************************************************************/

LOCAL void dm_sc P_((p_wf_t,p_sc_t));
LOCAL void dm_sc(p_wf,p_sc)
/* Dumps the specified scrap to the specified stream. */
p_wf_t p_wf;
p_sc_t p_sc;
{
 char *p;

 as_cold(p_sc->sc_first !=NULL,"dm_sc: NULL ptr1.");
 as_cold(p_sc->sc_last  !=NULL,"dm_sc: NULL ptr2.");

 if (p_sc->sc_white)
    wf_wr(p_wf,"Text scrap[White]=");
 else
    wf_wr(p_wf,"Text scrap[Grey]=");
 wf_wr(p_wf,"\"");
 for (p=p_sc->sc_first; p<=p_sc->sc_last; p++)
   {
    dm_byte(p_wf,*((ubyte_ *) p));
    if (*p=='\n')
       wf_wl(p_wf,"");
   }
 wf_wl(p_wf,"\"");
}

/******************************************************************************/

LOCAL void dm_scls P_((p_wf_t,p_scls_t));
LOCAL void dm_scls(p_wf,p_scls)
/* Dumps the specified scrap list to the specified stream. */
p_wf_t   p_wf;
p_scls_t p_scls;
{
 wf_wl(p_wf,"");
 centerln(p_wf,30,'-',"Start of Text Scrap List");
 ls_fir(p_scls);
 while (TRUE)
   {
    p_sc_t p_sc;
    ls_nxt(p_scls,PPV &p_sc);
    if (p_sc==NULL) break;
    dm_sc(p_wf,p_sc);
   }
 centerln(p_wf,30,'-',"End of Text Scrap List");
 wf_wl(p_wf,"");
}

/******************************************************************************/

EXPORT void dm_tkls(p_wf)
p_wf_t p_wf;
{
 tk_t *token;
 char *m;
 ubyte font;
 ubyte align;

 wf_wl(p_wf,"");
 centerln(p_wf,DUMP_WIDTH,'=',"Start of TOKEN LIST DUMP");
 wf_wl(p_wf,"");
 sprintf(linet1,"Summary: There are %lu tokens in the token list.",
                (ulong) ls_len(token_list));
 wf_wl(p_wf,linet1);
 wf_wl(p_wf,"");
 wf_wl(p_wf,"Line[Column]: Token Description");
 wf_wl(p_wf,"-------------------------------");
 wf_wl(p_wf,"");

 ls_fir(token_list);
 ls_nxt(token_list,PPV &token);
 while (token != NULL)
   {
    sprintf(linet1,"%04lu[%02lu]: ",
                   (ulong) token->tk_ps.ps_line,
                   (ulong) token->tk_ps.ps_column);
    wf_wr(p_wf,linet1);
    switch (token->tk_kind)
      {
       case TK_TEXT: m="Text."              ; break;
       case TK_MDEF: m="@$ Macro defn."     ; break;
       case TK_NDEF: m="@N File defn."      ; break;
       case TK_FDEF: m="@O File defn."      ; break;
       case TK_ONAM: m="@< Open name."      ; break;
       case TK_CNAM: m="@> Close name."     ; break;
       case TK_ODEF: m="@{ Open defn."      ; break;
       case TK_CDEF: m="@} Close defn."     ; break;
       case TK_OPAR: m="@( Open param."     ; break;
       case TK_CPAR: m="@} Close param."    ; break;
       case TK_COMA: m="@, Comma."          ; break;
       case TK_QUOT: m="@\" Quote."         ; break;
       case TK_PARM: m="@n Parameter."      ; break;
       case TK_ZERO: m="@Z Zero calls."     ; break;
       case TK_MANY: m="@M Many calls."     ; break;
       case TK_NAME: m="@# Name."           ; break;
       case TK_EMPH: m="@/ Emphasise."      ; break;
       case TK_NPAG: m="@t.. Newpage."      ; break;
       case TK_TOCS: m="@t.. TOC."          ; break;
       case TK_SKIP: m="@t.. Vertical skip."; break;
       case TK_TITL: m="@t.. Title."        ; break;
       case TK_EOF : m="End Of File."       ; break;
       case TK_NSEC:
          switch (token->tk_gen)
            {
             case 0: m="@* New section (Level 0)."; break;
             case 1: m="@A New section (Level 1)."; break;
             case 2: m="@B New section (Level 2)."; break;
             case 3: m="@C New section (Level 3)."; break;
             case 4: m="@D New section (Level 4)."; break;
             case 5: m="@E New section (Level 5)."; break;
             default: as_bomb("dmtkls: Level case defaulted.");
            }
          break;
       default: as_bomb("dmtkls: Token case defaulted.");
      }
    wf_wr(p_wf,m);
    wf_wr(p_wf," ");
    switch (token->tk_kind)
      {
       case TK_PARM:
          sprintf(linet1,"Parameterno=%u.",(unsigned) token->tk_gen);
          wf_wl(p_wf,linet1);
          break;
       case TK_NAME:
          wf_wr(p_wf,"Character='");
          dm_byte(p_wf,token->tk_gen);
          wf_wl(p_wf,"'.");
          break;
       case TK_TEXT:
          dm_sc(p_wf,&token->tk_sc);
          break;
       case TK_SKIP:
          sprintf(linet1,"Vertical space skipped=%lumm.",
                  (ulong) token->tk_gen);
          wf_wl(p_wf,linet1);
          break;
       case TK_TITL:
          font  = token->tk_gen / LRFT_PACK;
          align = token->tk_gen % LRFT_PACK;
          wf_wr(p_wf,"Font=");        wf_wr(p_wf,fontname(font));
          wf_wr(p_wf,", Alignment="); wf_wr(p_wf,alignname(align));
          wf_wl(p_wf,". Title text follows:");
          dm_sc(p_wf,&token->tk_sc);
          break;
       default: wf_wl(p_wf,""); break;
      }
    ls_nxt(token_list,PPV &token);
   } /* End of while loop. */

 centerln(p_wf,DUMP_WIDTH,'=',"End of TOKEN LIST DUMP");
 wf_wl(p_wf,"");
}

/******************************************************************************/

LOCAL void dm_eltx P_((p_wf_t,p_el_t));
LOCAL void dm_eltx (p_wf,p_el)
/* Dumps the specified text element to the specified stream. */
p_wf_t p_wf;
p_el_t p_el;
{
 p_tk_t p_tk;

 wf_wl(p_wf,"");
 centerln(p_wf,30,'-',"Start Text Element");

 ls_fir(p_el->el_text);
 ls_nxt(p_el->el_text,PPV &p_tk);
 while (p_tk != NULL)
   {
    dm_sc(p_wf,&p_tk->tk_sc);
    ls_nxt(p_el->el_text,PPV &p_tk);
   }
 centerln(p_wf,30,'-',"End Text Element");
 wf_wl(p_wf,"");
}

/******************************************************************************/

LOCAL void dm_elin P_((p_wf_t,p_el_t));
LOCAL void dm_elin(p_wf,p_el)
/* Dumps the specified invocation element to the specified stream. */
p_wf_t p_wf;
p_el_t p_el;
{
 ulong    parno;
 p_ells_t *pp_ex;
 p_ells_t p_ex;
 p_elll_t p_elll = p_el->el_parls;

 wf_wl(p_wf,"");
 centerln(p_wf,30,'-',"Begin Invocation Element");

 sprintf(linet1,"Invocation of macro @<%s@>",&p_el->el_p_mac->ma_name[0]);
 wf_wl(p_wf,linet1);

 if (ls_len(p_elll)==0)
    wf_wl(p_wf,"No actual parameters.");
 else
   {
    sprintf(linet1,"This invocation has %lu actual parameters.",
            (ulong) ls_len(p_elll));
    wf_wl(p_wf,linet1);
    wf_wl(p_wf,
    "Actual parameter list follows as a sequence of expressions:");
    wf_wl(p_wf,"(Text crud before and after parameter has been omitted).");
    parno=1;
    ls_fir(p_elll);
    while (TRUE)
      {
       ls_nxt(p_elll,PPV &pp_ex);
       if (pp_ex==NULL) break;
       p_ex = *pp_ex;
       sprintf(linet1,"Expression for parameter number %lu:",(ulong) parno);
       wf_wl(p_wf,linet1);
       dm_ex(p_wf,p_ex);
       parno++;
      }
   }

 centerln(p_wf,30,'-',"End Invocation Element");
 wf_wl(p_wf,"");
}

/******************************************************************************/

LOCAL void dm_elpr P_((p_wf_t,p_el_t));
LOCAL void dm_elpr(p_wf,p_el)
/* Dumps the specified parameter element to the specified stream. */
p_wf_t p_wf;
p_el_t p_el;
{
 wf_wl(p_wf,"");
 centerln(p_wf,30,'-',"Start Parameter Element");
 sprintf(linet1,"Parameter number=%lu.",(ulong) p_el->el_parno);
 wf_wl(p_wf,linet1);
 sprintf(linet1,"Parameter is of macro \"%s\".",
         &p_el->el_which->ma_name[0]);
 wf_wl(p_wf,linet1);
 centerln(p_wf,30,'-',"End Parameter Element");
 wf_wl(p_wf,"");
}

/******************************************************************************/

LOCAL void dm_ex(p_wf,p_ex)
/* Dumps the specified expression to the specified stream. */
p_wf_t   p_wf;
p_ells_t p_ex;
{
 p_el_t p_el;

 wf_wl(p_wf,"");
 centerln(p_wf,30,'-',"Start of Expression");
 ls_fir(p_ex);
 ls_nxt(p_ex,PPV &p_el);
 while (p_el != NULL)
   {
    switch (p_el->el_kind)
      {
       case EL_TEXT: dm_eltx(p_wf,p_el); break;
       case EL_INVC: dm_elin(p_wf,p_el); break;
       case EL_PARM: dm_elpr(p_wf,p_el); break;
       default     : as_bomb("dm_ex: Case defaulted.");
      }
    ls_nxt(p_ex,PPV &p_el);
   }
 centerln(p_wf,30,'-',"End of Expression");
 wf_wl(p_wf,"");
}

/******************************************************************************/

LOCAL void dm_macro P_((p_wf_t,p_ma_t));
LOCAL void dm_macro(p_wf,p_ma)
/* Dump all the information on the specified macro. */
p_wf_t p_wf;
p_ma_t p_ma;
{
 wf_wl(p_wf,"");
 centerln(p_wf,DUMP_WIDTH-20,'-',"Start of Macro Dump");

 /* A macro can't exist in the macro table without a name. */
 sprintf(linet1,"Macro Name  : \"%s\"",p_ma->ma_name); wf_wl(p_wf,linet1);

 /* Is the macro defined? */
 if (!p_ma->ma_defn.md_isdef) wf_wl(p_wf,"Defined?    : No.");
                         else wf_wl(p_wf,"Defined?    : Yes.");

 /* Defined macros carry lots more information. */
 if (p_ma->ma_defn.md_isdef)
   {
    /* Number of parameters the macro has. */
    sprintf(linet1,"Parameters  : %lu",(ulong) p_ma->ma_defn.md_npar);
    wf_wl(p_wf,linet1);

    /* Is the macro additive? */
    if (p_ma->ma_defn.md_isadd) wf_wl(p_wf,"Additive?   : Yes.");
                           else wf_wl(p_wf,"Additive?   : No.");

    /* Is the macro allowed to be called zero times? */
    if (p_ma->ma_defn.md_iszer) wf_wl(p_wf,"Zero Calls? : Yes.");
                           else wf_wl(p_wf,"Zero Calls? : No.");

    /* Is the macro allowed to be called many times? */
    if (p_ma->ma_defn.md_isman) wf_wl(p_wf,"Many Calls? : Yes.");
                           else wf_wl(p_wf,"Many Calls? : No.");

    /* Is the macro connected to an product file? */
    if (p_ma->ma_defn.md_isfil) wf_wl(p_wf,"Output File?: Yes.");
                           else wf_wl(p_wf,"Output File?: No.");

    /* Dump a list of all the calls to the macro. */
    {
     p_mc_t p_mc;
     ulong  mcnum;
     wf_wl(p_wf,"Call list   :");
     ls_fir(p_ma->ma_calls);
     ls_nxt(p_ma->ma_calls,PPV &p_mc);
     mcnum=1;
     while (p_mc != NULL)
       {
        sprintf(linet1,
 "   Call %lu: Parameters=%lu, Sequence num=%lu, Position(L,C)=(%lu,%lu).",
                (ulong) mcnum,
                (ulong) p_mc->mc_npar,
                (ulong) p_mc->mc_seq,
                (ulong) p_mc->mc_ps.ps_line,
                (ulong) p_mc->mc_ps.ps_column);
        wf_wl(p_wf,linet1);
        ls_nxt(p_ma->ma_calls,PPV &p_mc);
        mcnum++;
       }
    }

    /* Dump a list of the body parts of the macro. */
    {
     p_bp_t p_bp;
     ulong  bpnum;
     ulong  bptot = ls_len(p_ma->ma_defn.md_body);
     wf_wl(p_wf,"Macro body  :");
     wf_wl(p_wf,"");
     wf_wl(p_wf,"--Start of List of Body Parts--");
     sprintf(linet1,"This macro has %lu body part",(ulong) bptot);
     if (bptot!=1) strcat(linet1,"s");
     strcat(linet1,".");
     wf_wl(p_wf,linet1);
     bpnum=1;
     ls_fir(p_ma->ma_defn.md_body);
     ls_nxt(p_ma->ma_defn.md_body,PPV &p_bp);
     while (p_bp != NULL)
       {
        sprintf(linet1,
        "Body part %lu: Seqnum=%lu, Pos(L,C)=(%lu,%lu), Expression follows:",
                (ulong) bpnum,
                (ulong) p_bp->bp_seq,
                (ulong) p_bp->bp_ps.ps_line,
                (ulong) p_bp->bp_ps.ps_column);
        wf_wl(p_wf,linet1);
        dm_ex(p_wf,p_bp->bp_ex);
        ls_nxt(p_ma->ma_defn.md_body,PPV &p_bp);
        bpnum++;
       }
     wf_wl(p_wf,"---End of List of Body Parts---");
     wf_wl(p_wf,"");
    }

   } /* End of IF defined. */

 centerln(p_wf,DUMP_WIDTH-20,'-',"End of Macro Dump");
 wf_wl(p_wf,"");
}

/******************************************************************************/

EXPORT void dm_matb P_((p_wf_t));
EXPORT void dm_matb(p_wf)
p_wf_t p_wf;
{
 wf_wl(p_wf,"");
 centerln(p_wf,DUMP_WIDTH,'=',"Start of MACRO TABLE DUMP");
 wf_wl(p_wf,"");
 tb_fir(macro_table);
 while (TRUE)
   {
    name_t name;
    p_ma_t p_ma;
    if (!tb_rea(macro_table,PV &name[0],PV &p_ma)) break;
    dm_macro(p_wf,p_ma);
    wf_wl(p_wf,"");
   }
 wf_wl(p_wf,"");
 centerln(p_wf,DUMP_WIDTH,'=',"End of MACRO TABLE DUMP");
 wf_wl(p_wf,"");
}

/******************************************************************************/

LOCAL void dm_ty P_((p_wf_t,p_ty_t));
LOCAL void dm_ty(p_wf,p_ty)
p_wf_t p_wf;
p_ty_t p_ty;
{
 char linet2[200];
 char linet3[200];

 switch (p_ty->ty_kind)
   {
    case TY_NSEC:
       sn_str(&p_ty->ty_sn,linet2);
       strcpy(linet3,"<No name>");
       if (p_ty->ty_isnam) strcpy(linet3,&p_ty->ty_name[0]);
       sprintf(linet1,"   Section \"%s\", Section name=\"%s\".",linet2,linet3);
       wf_wl(p_wf,"");
       wf_wl(p_wf,linet1);
       break;
    case TY_OLIT: wf_wl(p_wf,"   Open  literal."    ); break;
    case TY_CLIT: wf_wl(p_wf,"   Close literal."    ); break;
    case TY_OEMP: wf_wl(p_wf,"   Open emphasise."   ); break;
    case TY_CEMP: wf_wl(p_wf,"   Close emphasise."  ); break;
    case TY_NPAG: wf_wl(p_wf,"   New page."         ); break;
    case TY_TOCS: wf_wl(p_wf,"   Table of contents."); break;
    case TY_SKIP:
       sprintf(linet1,"   Vertical skip by %lu mm.",(ulong) p_ty->ty_mm);
       wf_wl(p_wf,linet1);
       break;
    case TY_TITL:
       wf_wr(p_wf,"Font=");        wf_wr(p_wf,fontname(p_ty->ty_font));
       wf_wr(p_wf,", Alignment="); wf_wr(p_wf,alignname(p_ty->ty_align));
       wf_wl(p_wf,". Title text follows:");
       dm_sc(p_wf,&p_ty->ty_sc);
       break;
    default: as_bomb("dm_ty: Typesetter directive switch defaulted.");
   }
}

/******************************************************************************/

EXPORT void dm_dcls(p_wf)
/* Dumps a text representation of the document list to the given stream.      */
p_wf_t p_wf;
{
 wf_wl(p_wf,"");
 centerln(p_wf,DUMP_WIDTH,'=',"Start of DOCUMENT LIST DUMP");
 wf_wl(p_wf,"");

 ls_fir(document_list);
 while (TRUE)
   {
    p_dc_t p_dc;
    ls_nxt(document_list,PPV &p_dc);
    if (p_dc == NULL) break;
    wf_wl(p_wf,"");
    sprintf(linet1,"Pos(L,C)=(%lu,%lu). ",
            p_dc->dc_ps.ps_line,
            p_dc->dc_ps.ps_column);
    switch (p_dc->dc_kind)
      {
       case DC_TEXT:
          wf_wr(p_wf,"TEXT COMPONENT: "); wf_wl(p_wf,linet1);
          dm_scls(p_wf,p_dc->dc_text);
          break;

       case DC_TYPE:
          wf_wr(p_wf,"TYPESETTER DIRECTIVE COMPONENT: ");
          dm_ty(p_wf,&p_dc->dc_ty);
          break;

       case DC_MACR:
          wf_wr(p_wf,"MACRO DEFINITION COMPONENT: "); wf_wl(p_wf,linet1);
          sprintf(linet1,"Part %lu of macro @<%s@>.",
                  p_dc->dc_part,
                  &p_dc->dc_p_ma->ma_name[0]);
          wf_wl(p_wf,linet1);
          break;

       default: as_bomb("dm_scls: Case defaulted.");
      }
   }

 wf_wl(p_wf,"");
 centerln(p_wf,DUMP_WIDTH,'=',"End of DOCUMENT LIST DUMP");
 wf_wl(p_wf,"");
}

/******************************************************************************/

LOCAL void tm_for P_((p_wf_t,char *,p_ck_t,p_ck_t));
LOCAL void tm_for(p_wf,s,p_val,p_tot)
/* This rather ragged function simplifies the formatting in dm_times.         */
p_wf_t p_wf;
char   *s;
p_ck_t p_val;
p_ck_t p_tot;
{
 sprintf(linet1,"|%s| %3d%% | %8.2f | %8.2f | %3d%% |",
         s,
         (int)   ((100.0*ck_cpu(p_val))/ck_cpu(p_tot)),
         (float) ck_cpu(p_val),
         (float) ck_real(p_val),
         (int)   ((100.0*ck_real(p_val))/ck_real(p_tot))
        );
 wf_wl(p_wf,linet1);
}

/******************************************************************************/

EXPORT void dm_times(p_wf,
                     p_mapp,p_scan,p_pars,p_anal,
                     p_dump,p_lstr,p_tang,p_weav,p_totl)
p_wf_t p_wf;
p_ck_t p_mapp;
p_ck_t p_scan;
p_ck_t p_pars;
p_ck_t p_anal;
p_ck_t p_dump;
p_ck_t p_lstr;
p_ck_t p_tang;
p_ck_t p_weav;
p_ck_t p_totl;
{
 float cputot;
 float realtot;
 float cpuerr;
 float realerr;

 cputot = ck_cpu(p_mapp) + ck_cpu(p_scan) + ck_cpu(p_pars) +
          ck_cpu(p_anal) + ck_cpu(p_dump) + ck_cpu(p_lstr) +
          ck_cpu(p_tang) + ck_cpu(p_weav);

 realtot = ck_real(p_mapp) + ck_real(p_scan) + ck_real(p_pars) +
           ck_real(p_anal) + ck_real(p_dump) + ck_real(p_lstr) +
           ck_real(p_tang) + ck_real(p_weav);

 cpuerr  = ck_cpu (p_totl)-cputot;
 realerr = ck_real(p_totl)-realtot;

 wf_wl(p_wf,"");
 wf_wl(p_wf,"Summary of time used by each subsystem of Funnelweb (seconds).");
 wf_wl(p_wf,"");
 wf_wl(p_wf,    "+------------+------+----------+----------+------+");
 wf_wl(p_wf,    "| Subsystem  | CPU% | CPU Time | RealTime |  RT% |");
 wf_wl(p_wf,    "+------------+------+----------+----------+------+");
 tm_for(p_wf," Mapper     ",p_mapp,p_totl);
 tm_for(p_wf," Scanner    ",p_scan,p_totl);
 tm_for(p_wf," Parser     ",p_pars,p_totl);
 tm_for(p_wf," Analyser   ",p_anal,p_totl);
 tm_for(p_wf," Dumper     ",p_dump,p_totl);
 tm_for(p_wf," Lister     ",p_lstr,p_totl);
 tm_for(p_wf," Tangler    ",p_tang,p_totl);
 tm_for(p_wf," Weaver     ",p_weav,p_totl);
 sprintf(linet1,"|%s| %3d%% | %8.2f | %8.2f | %3d%% |",
         " Clock Err  ",
         (int)   ((100.0*cpuerr )/ck_cpu (p_totl)),
         (float)                            cpuerr,
         (float)                           realerr,
         (int)   ((100.0*realerr)/ck_real(p_totl))
        );
 wf_wl(p_wf,linet1);

 wf_wl(p_wf,    "+------------+------+----------+----------+------+");
 tm_for(p_wf," Total      ",p_totl,p_totl);
 wf_wl(p_wf,    "+------------+------+----------+----------+------+");
 wf_wl(p_wf,"");
}

/******************************************************************************/
/*                                 End of DUMP.C                              */
/******************************************************************************/

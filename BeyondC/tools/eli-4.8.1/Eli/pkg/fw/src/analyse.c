static char RCSid[] = "$Id: analyse.c,v 1.5 1999/10/20 04:55:53 tony Exp $";
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
   04-Feb-1994  AMS  Removed errors for no macro defns or output files.

##############################################################################*/


/******************************************************************************/
/*                                   ANALYSE.C                                */
/******************************************************************************/

#include "style.h"

#include "analyse.h"
#include "as.h"
#include "data.h"
#include "lister.h"
#include "misc.h"
#include "table.h"

/******************************************************************************/

LOCAL void chk_mac P_((p_ma_t));
LOCAL void chk_mac (p_ma)
p_ma_t p_ma;
{
 mc_t *call;

 /* Deal with undefined macros by flagging the first invocation. */
 if (!p_ma->ma_defn.md_isdef)
   {
    ls_loo(p_ma->ma_calls,(ulong) 1,PPV &call);
    as_cold(call!=NULL,"check_macro: No instances of \"undefined\" macro!");
    lr_err(&call->mc_ps,"Call to undefined macro.");
    return;
   }

 /* Assert: The macro has a definition. */

 /* Check that all the calls to the macro have the correct number of params. */
 ls_fir(p_ma->ma_calls);
 ls_nxt(p_ma->ma_calls,PPV &call);
 while (call!=NULL)
    {
     if (call->mc_npar != p_ma->ma_defn.md_npar)
       {
        sprintf(linet1,"Call has %lu parameter%s, but the macro",
                (ulong) call->mc_npar,
                call->mc_npar==1 ? "" : "s");
        lr_err(&(call->mc_ps),linet1);
        sprintf(linet1,"definition at line %lu specifies %lu parameter%s.",
                (ulong) p_ma->ma_defn.md_ps.ps_line,
                (ulong) p_ma->ma_defn.md_npar,
                p_ma->ma_defn.md_npar==1 ? "" : "s");
        lr_mes(&(call->mc_ps),linet1);
        if (p_ma->ma_defn.md_npar==0 && call->mc_npar==1)
          {
           lr_mes(&(call->mc_ps),"Note: If your call looks like this: @<Macro@>@(@) then you");
           lr_mes(&(call->mc_ps),"should be aware that FunnelWeb treats this as a call with");
           lr_mes(&(call->mc_ps),"a single parameter consisting of the empty string. This");
           lr_mes(&(call->mc_ps),"is a consequence of parameter delimiters @\"@\" being optional.");
          }
       }
     ls_nxt(p_ma->ma_calls,PPV &call);
    }

 /* Check that the number of calls of the macro is legal. */
 if (p_ma->ma_defn.md_isfil)
   {
    /* Flag all calls to a file macro as errors. */
    if (ls_len(p_ma->ma_calls)>0)
      {
       lr_mes(&p_ma->ma_defn.md_ps,
              "This file macro is called one or more times.");
       lr_mes(&p_ma->ma_defn.md_ps,
              "Each call has been flagged with an error message.");
      }
    ls_fir(p_ma->ma_calls);
    ls_nxt(p_ma->ma_calls,PPV &call);
    while (call!=NULL)
      {
       lr_err(&(call->mc_ps),"Calls to file macros are not allowed.");
       lr_mes(&(call->mc_ps),"Reason: It should be possible to comment out a");
       lr_mes(&(call->mc_ps),"file macro without a big fuss. Calling a file macro");
       lr_mes(&(call->mc_ps),"just tangles it up in the macro structure,");
       lr_mes(&(call->mc_ps),"making it more difficult to comment out later.");
       ls_nxt(p_ma->ma_calls,PPV &call);
      }
   }
 else
   {
    /* Non-file macros. */
    if (ls_len(p_ma->ma_calls)==0 && !p_ma->ma_defn.md_iszer)
       lr_err(&p_ma->ma_defn.md_ps,
              "This macro is never used (and has no @Z).");

    if (ls_len(p_ma->ma_calls)>1 && !p_ma->ma_defn.md_isman)
       lr_err(&p_ma->ma_defn.md_ps,
              "This macro is used more than once (and has no @M).");
   }
}

/******************************************************************************/

LOCAL void chk_rec P_((void));
LOCAL void chk_rec()
/* This macro analyses the calls between the macros in the macro              */
/* table and flags all recursive macros with an error message.                */
/*                                                                            */
/* Def: A macro is a "level 0 macro" if it does not call any macros.          */
/* Def: A macro is a "level n macro" if it calls at least one macro of level  */
/*      n-1, but does not call any macros of level n or higher.               */
/* Def: A macro is a "level infinity macro" if it directly or indirectly      */
/*      calls itself.                                                         */
/*                                                                            */
/* This function totally ignores undefined macros. This means that it can be  */
/* invoked even if problems are detected by the other checks.                 */
/*                                                                            */
/* Although the actions of this may seem rather time expensive, they may not  */
/* be. The function repeatedly runs through the macro table and each macro's  */
/* bodypart list and expression lists. However, there are not likely to be    */
/* many macros and each definition expression list is likely to be quite      */
/* short, as each macro will be mainly text.                                  */
/* Even if this stuff does take a while, it is better to detect recursion now */
/* than at tangle time!                                                       */
{
 p_ma_t p_ma;        /* General purpose pointer to macro.                     */
 name_t dummy_name;  /* Dummy name variable acts as a placeholder in calls.   */
 uword  level;       /* Level of macro currently being tagged.                */
 bool   gotone;      /* TRUE iff current loop iteration tagged >0 macros.     */

/* We need a concrete number to stand for level infinity. */
/* 30000 is a nice, large 15 bit number.                  */
#define LEVINF 30000

 /* Make sure that our idea of infinity is big enough. */
 as_cold(tb_len(macro_table)<LEVINF,"ana_rec: too many macros.");

 /* Tag all the macros as being at level infinity.                            */
 /* This could be done in the parser, but it's neater to do it here.          */
 tb_fir(macro_table);
 while (tb_rea(macro_table,PV dummy_name,PV &p_ma))
    if (p_ma->ma_defn.md_isdef)
       p_ma->ma_level=LEVINF;

 gotone=TRUE;
 /* Work from level 0 upwards identifying macros of successive levels.        */
 for (level=0; level<LEVINF && gotone; level++)
   {
    /* Identify all macros of level 'level'. */
    /* Gotone tells us if we managed to tag a macro during this iteration. */
    gotone=FALSE;

    /* Run through table tagging all macros at level 'level'. */
    tb_fir(macro_table);
    while (tb_rea(macro_table,PV dummy_name,PV &p_ma))
      {
       if (p_ma->ma_defn.md_isdef && p_ma->ma_level == LEVINF)
         {
          p_bpls_t p_bpls = p_ma->ma_defn.md_body;
          /* Run through each body part of the macro. */
          ls_fir(p_bpls);
          while (TRUE)
            {
             p_bp_t p_bp;
             ls_nxt(p_bpls,PPV &p_bp);
             if (p_bp==NULL) break;
             /* Run through the list of expression elements. */
             ls_fir(p_bp->bp_ex);
             while (TRUE)
               {
                p_el_t p_el;
                ls_nxt(p_bp->bp_ex,PPV &p_el);
                if (p_el==NULL) break;
                /* Don't tag anything that calls anything that isn't tagged. */
                if ((p_el->el_kind==EL_INVC          ) &&
                    (p_el->el_p_mac->ma_defn.md_isdef) &&

    (p_el->el_p_mac->ma_level==LEVINF))
                   goto nextmacro;
               }
            }
          /* If we got this far, then our macro must have called nothing but  */
          /* macros of levels [0,level-1]. Thus, we can tag it level 'level'. */
          p_ma->ma_level=level;
          gotone=TRUE;
         } /* End if */
       nextmacro:;
      } /* End while */
   } /* End for loop. */

 /* At this point, we have tagged all macros with their level number. Note    */
 /* that level infinity macros are discovered simply because they do not get  */
 /* tagged. The following loop flags all such recursive macros with errors.   */
 tb_fir(macro_table);
 while (tb_rea(macro_table,PV dummy_name,PV &p_ma))
    if (p_ma->ma_defn.md_isdef && p_ma->ma_level==LEVINF)
       lr_err(&p_ma->ma_defn.md_ps,"This macro has an infinite expansion.");

 /* Note: The above message is not "This macro is defined recursively",       */
 /* because this function catches not only recursive macros, but also all the */
 /* non-recursive macros that call the recursive macros!! To detect only      */
 /* the recursive macros, we really ought to use Tarjan's algorithm for the   */
 /* detection of strongly connected components. However, I don't have the     */
 /* reference handy right now and I want to finish this version of FunnelWeb  */
 /* soon, so I'll leave the installation of Tarjan's algorithm as a possible  */
 /* future enhancement. Then the error message can be changed.                */
}

/******************************************************************************/

EXPORT void analyse()
{
 name_t dummy_name;
 p_ma_t p_ma;

 /* Take a look at each macro and issue appropriate diagnostics. */
 tb_fir(macro_table);
 while (tb_rea(macro_table,PV dummy_name,PV &p_ma))
    chk_mac(p_ma);

 /* Check for recursive macros. */
 chk_rec();

 /* Run through the document list and flag any sections that still have not   */
 /* been given names.                                                         */
 ls_fir(document_list);
 while (TRUE)
   {
    p_dc_t p_dc;
    ls_nxt(document_list,PPV &p_dc);
    if (p_dc==NULL) break;
    if (p_dc->dc_kind==DC_TYPE &&
        p_dc->dc_ty.ty_kind==TY_NSEC &&
        !p_dc->dc_ty.ty_isnam)
      {
       lr_err(&p_dc->dc_ps,"This section has no name.");
       lr_mes(&p_dc->dc_ps,"You can give it one explicitly (As in @A@<Sloth@>) or implicitly by");
       lr_mes(&p_dc->dc_ps,"defining a macro (whose name will be inherited) within the section.");
      }
   }
}

/******************************************************************************/
/*                               End of ANALYSE.C                             */
/******************************************************************************/

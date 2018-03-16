static char RCSid[] = "$Id: tangle.c,v 1.12 2009/09/18 12:01:42 asloane Exp $";
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
   26-Jul-1992  AMS  When option +U is given output mapping information
                     for each text element.  Fixed bug in keeping track
		     of how many characters have been output on a line.
   26-Jul-1992  AMS  Added RCS id.
   02-Sep-1992  AMS  Fixed bug in calling ex_sc with structures instead
                     of pointers to them.  Apparently this worked anyway on
		     the sparc but crashes on the 68020.
   07-Apr-1993  AMS  Also output information about end of a region on output.

##############################################################################*/


/******************************************************************************/
/*                                   TANGLE.C                                 */
/******************************************************************************/

/* Note: In this module, "ex_" at the start of a function name means "expand" */
/*       rather than the standard meaning of "ex" of "expression.             */

/******************************************************************************/

#include "style.h"

#include "as.h"
#include "data.h"
#include "lister.h"
#include "memory.h"
#include "misc.h"
#include "table.h"
#include "tangle.h"
#include "writfile.h"

/******************************************************************************/

/* The following variable keeps track of the output line number. This is      */
/* needed to report lines that are too long.                                  */
LOCVAR ulong lineno;

/* Last line for which error message was generated.    */
LOCVAR ulong errlin;

/* Number of too-long lines seen so far in this file. */
LOCVAR ulong numlong;
/* Number of long line error messages we can tolerate per product file. */
#define LONGMESS 5

/* Note: An indentation of n means n blanks before current material.          */
/* tgindent is a global variable set by the scanner. It is TRUE if blank      */
/* indenting is required and FALSE if no indenting is required.               */
LOCVAR ulong ind_base;  /* Base indenting level of macro being expanded.      */
LOCVAR ulong ind_curr;  /* Current indenting position.                        */

LOCVAR char  *fn_targ;  /* Name of current (target) product file.             */
LOCVAR wf_t  f_o;       /* Current product file.                              */

/******************************************************************************/

/* The expression expansion function has to have a forward declaration. */
LOCAL void ex_ex P_((p_ells_t));

/******************************************************************************/

LOCAL void eolblank P_((ulong));
LOCAL void eolblank(n)
/* Writes an EOL followed by n blanks to the product file. Efficiently!       */
ulong n;
{
 /* The whole aim of this routine is to write blanks EFFICIENTLY. In          */
 /* particular avoiding any per-char procedure call overhead (e.g. calls to   */
 /* wf_chr). The best way to avoid this is to create a static array of blanks */
 /* and write out large blocks of blanks all at once.                         */
#define BLANKLEN 100             /* Number of BLANKS in blank array.          */
 STAVAR bool notinit=TRUE;       /* Has blank array been initialized?         */
 STAVAR char blanks[1+BLANKLEN]; /* EOL followed by BLANKLEN blanks.          */

 /* Set up the blank array. This only ever done once because of the static    */
 /* boolean. Note that use of an initialized static here does not make the    */
 /* code non-reentrant, as the state does not change after initialization.    */
 if (notinit)
    {blanks[0]=EOL; memset(blanks+1,' ',(size_t) BLANKLEN); notinit=FALSE;}

 /* The most common case will be a small indentation. Do this case fast. */
 if (n<=BLANKLEN)
    wf_blk(&f_o,&blanks[0],(size_t) n+1);
 else
   {
    /* We now know that n>=BLANKLEN. Write out a long line with \n at front. */
    wf_blk(&f_o,&blanks[0],BLANKLEN+1); n-=BLANKLEN;

    /* Now get into large scale blank production! */
    while (n>0)
      {
       ulong len=FW_MIN(n,BLANKLEN);
       wf_blk(&f_o,&blanks[1],(size_t) len); n-=len;
      }
   }
}

/******************************************************************************/

#define SENDLINE {wl_l(linet1); if (option.op_s_b) wl_sj(linet1);}

LOCAL void ex_sc P_((p_sc_t, p_ps_t));
LOCAL void ex_sc(p_sc, p_ps)
/* This function writes the specified scrap to the product file. It also      */
/* performs two other tasks:                                                  */
/*    If tgindent==TRUE, inserts indentation at the start of each line.       */
/*    If tglinmax>0, checks for product file lines longer than tglinmax.      */
/* Note: The speed of this routine is fairly critical.                        */
p_sc_t p_sc;
p_ps_t p_ps;
{
 char buffer[1000];

 /* Output of a scrap is straightforward if we are not inserting indentation  */
 /* or watching for lines that are too long. If neither of these tasks have   */
 /* to be performed, we can bang the scrap out directly with a wf_blk.        */

 if (!tgindent && tglinmax==TGMAXINF)
   {
     wf_blk(&f_o, p_sc->sc_first, (size_t) (p_sc->sc_last-p_sc->sc_first+1));
     if (option.op_u_b)
     {
       char *cp;
       int len;

       sprintf(buffer, "%s %lu %lu 0 %s %lu %lu", p_ps->ps_filename,
	       p_ps->ps_locline, p_ps->ps_column,
	       fn_targ, lineno, ind_curr + 1);
       wf_wr(&f_m, buffer);

       /* Need to count newlines and columns for end coord */
       for (cp = p_sc->sc_first, len = p_sc->sc_last-p_sc->sc_first+1;
	    len != 0; len--, cp++)
	   if (*cp == '\n') {
	       lineno++;
	       ind_curr = 0;
	   } else
	       ind_curr++;

       sprintf(buffer, " %lu %lu\n", lineno, ind_curr + 1);
       wf_wr(&f_m, buffer);
     }
     return;
   }

 if (option.op_u_b)
   {
     sprintf(buffer, "%s %lu %lu %lu %s %lu %lu", p_ps->ps_filename,
	     p_ps->ps_locline, p_ps->ps_column, ind_base,
	     fn_targ, lineno, ind_curr + 1);
     wf_wr(&f_m, buffer);
   }

 /* Otherwise it gets rather messy. Basically, we have to watch for end of    */
 /* lines and perform special actions there.                                  */
 /* ind_curr is the number of characters already written to the current line. */
 {
  char *p      = p_sc->sc_first;
  char *p_post = p_sc->sc_last+1;
  while (TRUE)
    {
     char *p_sot = p;  /* SOT=Start of Text. */

     /* Scan scrap until we hit either its end or an EOL. */
     while (p!=p_post && *p!=EOL) p++;

     /* Assert: p==p_post || (p_sot<=p<p_post && *p==EOL). */

     /* If we scanned any non-EOL text, write out what we scanned. */
     if (p>p_sot) {wf_blk(&f_o,p_sot,(size_t) (p-p_sot));ind_curr+=p-p_sot;}

     /* Check that what we have written so far is not too long.            */
     /* Performing this check here rather than with the EOL processing     */
     /* means that we will detect overlong final non-EOL terminated lines. */
     /* Use of errlin suppresses multiple errors on the same line.         */
     /* Note: We assume that TGMAXINF is very large.                       */
     if (ind_curr>tglinmax && lineno!=errlin)
       {
        numlong++;
        if (numlong <= LONGMESS)
          {
           if (option.op_b7_b)
              sprintf(linet1,
                      "E: Product file line is too long (line %lu of \"%s\").",
                             (ulong) lineno,SUPPNAME);
           else
              sprintf(linet1,
                      "E: Product file line is too long (line %lu of \"%s\").",
                             (ulong) lineno,fn_targ);
           SENDLINE;
           if (numlong==1)
             {
              sprintf(linet1,"   Product file line length limit is %lu characters.",
                             (ulong) tglinmax);
              SENDLINE;
              sprintf(linet1,"   Note: You can change the limit by specifying.");
              SENDLINE;
              sprintf(linet1,"      @p maximum_output_line_length = <desired length>");
              SENDLINE;
              sprintf(linet1,"   somewhere in the input file.");
              SENDLINE;
             }
           errlin=lineno;
           num_err++;
          }
        if (numlong == LONGMESS+1)
          {
           sprintf(linet1,
           "Further line-too-long warnings for file \"%s\" have been suppressed.",
              fn_targ);
           SENDLINE;
          }
       }

     /* Exit if we hit the end of the scrap. */
     if (p==p_post) break;

     /* Move past the EOL and bump up the line counter. */
     p++; lineno++;

     /* Output an EOL with indentation if desired. */
     if (tgindent)
       {
        eolblank(ind_base);
	ind_curr = ind_base;
       }
     else
       {
        wf_chr(&f_o,EOL);
        ind_curr = 0;
       }
    }
 }

 if (option.op_u_b)
   {
     sprintf(buffer, " %lu %lu\n", lineno, ind_curr + 1);
     wf_wr(&f_m, buffer);
   }
}

/******************************************************************************/

LOCAL void ex_eltx P_((p_el_t));
LOCAL void ex_eltx(p_el)
/* Writes the given text element to the product file. */
p_el_t p_el;
{
 p_tk_t p_tk;

 /* Make sure that we have actually been handed a text element. */
 as_cold(p_el->el_kind==EL_TEXT,"ex_eltx: Not a text element!");

 /* Write all the scraps in the text list to the product file. */
 ls_fir(p_el->el_text);
 while (TRUE)
   {
    ls_nxt(p_el->el_text,PPV &p_tk);
    if (p_tk==NULL) break;
    ex_sc(&p_tk->tk_sc, &p_tk->tk_ps);
   }
}

/******************************************************************************/

LOCAL void ex_elpr P_((p_el_t));
LOCAL void ex_elpr(p_el)
/* Write the expansion of the given parameter element to the product file. */
p_el_t p_el;
{
 p_ell3_t  actn = p_el->el_which->ma_actn;
 p_elll_t *pp_parls;
 p_ells_t *pp_exp;
 ulong    ind_save;

 /* Make sure that we have been handed a parameter element. */
 as_cold(p_el->el_kind==EL_PARM,"ex_elpr: Not a parameter element!");

 /* Save the current indentation base and set it to the current level. */
 ind_save=ind_base;
 ind_base=ind_curr;

 /* Get a pointer to the most recent parameter list of the target macro. */
 ls_loo(actn,ls_len(actn),PPV &pp_parls);

 /* Get the expression corresponding to the el_parno'th parameter. */
 ls_loo(*pp_parls,p_el->el_parno,PPV &pp_exp);

 /* Expand that expression. */
 ex_ex(*pp_exp);

 /* Restore the indentation base. */
 ind_base=ind_save;
}

/******************************************************************************/

LOCAL void ex_elin P_((p_el_t));
LOCAL void ex_elin(p_el)
/* Expand invocation element. */
p_el_t p_el;
{
 p_ma_t p_ma;
 p_bp_t p_bp;
 ulong  ind_save;
 p_void p_mark;

 /* Make sure that we have been handed an invocation element. */
 as_cold(p_el->el_kind==EL_INVC,"ex_elin: Not an invocation element!");

 /* Save the current indentation base and set it to the current level. */
 ind_save=ind_base;
 ind_base=ind_curr;

 /* Grab a pointer to the macro being invoked. */
 p_ma=p_el->el_p_mac;

 /* Push the actual parameter list onto the invoked macro's activation list. */
 ls_add(p_ma->ma_actn,PV &p_el->el_parls);

 /* Expand each body part expression. */
 ls_fir(p_ma->ma_defn.md_body);
 while (TRUE)
   {
    ls_nxt(p_ma->ma_defn.md_body,PPV &p_bp);
    if (p_bp==NULL) break;
    p_mark=ls_mar(p_ma->ma_defn.md_body); /* Protect againt recursion. */
    ex_ex(p_bp->bp_ex);
    ls_set(p_ma->ma_defn.md_body,p_mark);
   }

 /* Pop the activated macro's parameter list. */
 ls_lop(p_ma->ma_actn);

 /* Restore the indentation base. */
 ind_base=ind_save;
}

/******************************************************************************/

LOCAL void ex_ex(p_exp)
/* Expand the specified expression. */
p_ells_t p_exp;
{
 p_void p_mark;

 /* We need to save the current position in the expression list in case we    */
 /* are being recursively invoked (e.g. in @<X@>@(@"@<X@>@(@"sloth@"@)@"@).   */
 ls_fir(p_exp);
 while (TRUE)
   {
    p_el_t p_el;
    ls_nxt(p_exp,PPV &p_el);
    if (p_el==NULL) break;
    p_mark=ls_mar(p_exp);
    switch (p_el->el_kind)
      {
       case EL_TEXT: ex_eltx(p_el); break;
       case EL_INVC: ex_elin(p_el); break;
       case EL_PARM: ex_elpr(p_el); break;
       default     : as_bomb("ex_ex: Case defaulted.");
      }
    ls_set(p_exp,p_mark);
   }
}

/******************************************************************************/

LOCAL void ex_file P_((p_ma_t));
LOCAL void ex_file(p_ma)
/* This function accepts a pointer to a macro. It creates a product file      */
/* with the same name as the macro (inheriting any filename parts given in    */
/* the command line) and expands the macro, writing the expansion to the      */
/* product file.                                                              */
p_ma_t  p_ma;
{
 fn_t  fn_tmp;  /* Name of temporary file.                                    */
 bool  renfil;   /* Do we wish to rename product file?                        */
 bool  istarg;   /* Does a target file already exist?                         */

 /* Writing product files differs to the other output files. With non         */
 /* critical files such as the listing file that are really just logs,        */
 /* generation of half a listing file is acceptable if not desirable. However */
 /* in the case of product files, it is very bad to generate half a product   */
 /* file; far better to generate none at all. For this reason, and also       */
 /* because of the presence of the D option (which prohibits the writing      */
 /* of product files identical to existing files (to prevent MAKE             */
 /* propagations)) it is best to write a temporary file and then rename it.   */

 /* Construct the target file name.                                           */
 strcpy(fn_targ,"");                /* Start with an empty name.              */
 fn_ins(fn_targ,&option.op_o_s[0]);
 fn_ins(fn_targ,&p_ma->ma_name[0]);

 /* The temporary file has to inherit too, because the output directory may   */
 /* not be the default directory and some computers can't rename across       */
 /* directories (and we have to rename it later).                             */
 strcpy(fn_tmp,fn_targ);
 fn_ins(fn_tmp,fn_temp());

 /* Expand the macro to the temporary file. */
 wf_ini(&f_o,TRUE);
 wf_ope(&f_o,fn_tmp);
 if (wf_err(&f_o))
   {
    sprintf(linet1,"Error creating temporary product file \"%s\".",&fn_tmp[0]);
    wl_sjl(linet1);
    (void) remove(fn_tmp);
    goto severe;
   }

 /* Now expand the target macro into the file. */
 {
  el_t el;
  el.el_kind  = EL_INVC;
  el.el_p_mac = p_ma;
  el.el_parls = ls_cre(sizeof(p_ells_t));
  /* Note: We don't set el_pretx and el_postx as they are not used here. */
  ind_base = 0;
  ind_curr = 0;
  lineno   = 1;
  errlin   = 0;
  numlong  = 0;
  ex_elin(&el);
 }

 /* Make sure that there weren't any errors writing to the product file. */
 if (wf_err(&f_o))
   {
    sprintf(linet1,"S: Error writing to temporary product file \"%s\".",&fn_tmp[0]);
    wl_sjl(linet1);
    (void) remove(fn_tmp);
    goto severe;
   }

 /* Close the product file. */
 wf_clo(&f_o);
 if (wf_err(&f_o))
   {
    sprintf(linet1,"S: Error closing temporary product file \"%s\".",&fn_tmp[0]);
    wl_sjl(linet1);
    (void) remove(fn_tmp);
    goto severe;
   }

 /* The rest of the code in this function copes with the renaming. */

 /* By default, we wish to rename the temporary file. */
 renfil=TRUE;

 /* Deal with any existing file of the target name. */
 istarg=fexists(fn_targ);
 if (istarg && option.op_d_b)
   {
    /* A target already exists, and the D option is on. If the target is      */
    /* identical to the temporary, we can simply delete the temporary!        */
    char *errstr;
    bool  same;
    errstr=eq_files(fn_tmp,fn_targ,&same);
    if (errstr != NULL)
      {
       wl_sjl("S: Error comparing temporary file with previous product file.");
       wl_sjl("(A comparison was attempted because the D option was turned on.)");
       wl_sjl("Error from comparison routine was as follows (first=temp):");
       wr_sjl("   ");wl_sjl(errstr);
       sprintf(linet1,"Temporary file name was \"%s\".",&fn_tmp[0]);
       wl_sjl(linet1);
       sprintf(linet1,"Product   file name was \"%s\".",fn_targ);
       wl_sjl(linet1);
       wl_sjl("FunnelWeb will leave both files intact so you can look at them.");
       goto severe;
      }
    /* If the two files are the same, we can simply delete the temporary. */
    if (same)
      {
       int status;
       status=remove(fn_tmp);
       if (status != REMOVE_S)
 {
  sprintf(linet1,"S: Error deleting (under +D option) temporary file \"%s\".",&fn_tmp[0]);
  wl_sjl(linet1);
  goto severe;
 }
       sprintf(linet1,"Deleted identical product file \"%s\".",fn_targ);
       wl_sjl(linet1);
       renfil=FALSE;
      }
   }

 if (renfil)
   {
    int status;
    /* We need to delete any existing file of the target name. */
    if (istarg)
      {
       status=remove(fn_targ);
       if (status != REMOVE_S)
 {
  sprintf(linet1,"S: Error deleting existing product file \"%s\".",fn_targ);
  wl_sjl(linet1);
  goto severe;
 }
      }
    /* Rename the temporary file to the product file. */
    status=rename(fn_tmp,fn_targ);
    if (status != RENAME_S)
      {
       wl_sjl("S: Error renaming temporary product file to product file.");
       sprintf(linet1,"Temporary file name was \"%s\".",&fn_tmp[0]);
       wl_sjl(linet1);
       sprintf(linet1,"Product   file name was \"%s\".",fn_targ);
       wl_sjl(linet1);
       wl_sjl("FunnelWeb will leave both files intact so you can look at them.");
       goto severe;
      }
   }

 /* Tell everyone that we have written a product file. */
 /* Note that we use the macro name. The full name is usually too messy. */
 sprintf(linet1,"Tangle: Completed %s.",&p_ma->ma_name[0]);
 wl_sjl(linet1);
 return;

 /* Jump here is a nasty file error occurs. */
 severe:
 sprintf(linet1,"A problem occurred during the generation of product file \"%s\".",&fn_targ[0]);
 wl_sjl(linet1);
 wl_sjl("S: Aborting...");
 num_sev++;
 return;

}

/******************************************************************************/

EXPORT void tangle()
{
 name_t dummyname;
 p_ma_t p_ma;

 /* Possibly decrease tglinmax if W option is turned on. */
 if (option.op_w_b)
    tglinmax=FW_MIN(tglinmax,option.op_w_i);

 /* Some compilers do not allow much space for statics so we allocate fn_targ */
 /* dynamically to save static space.                                         */
 fn_targ=(char *) mm_temp(sizeof(fn_t));

 /* Generate each file contained in the file table. */
 tb_fir(file_table);
 while (num_sev==0 && tb_rea(file_table,PV dummyname,PV &p_ma))
    ex_file(p_ma);
}

/******************************************************************************/
/*                               End of TANGLE.C                              */
/******************************************************************************/


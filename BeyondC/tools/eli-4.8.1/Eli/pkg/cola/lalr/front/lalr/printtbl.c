/*
** $Id: printtbl.c,v 1.8 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: printtbl.c,v 1.8 1997/08/29 08:38:08 mjung Exp $";

/* (C) Copyright 1997 University of Paderborn */

/* This file is part of the Eli translator construction system.

Eli is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

Eli is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with Eli; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

/***************************************************************************/
/* File: printtbl.c	First Edit: 21.03.89	  Last Edit: 21.03.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change:	02.08.89	From: Karl-Josef Prott			   */
/***************************************************************************/

#include <stdio.h>
#include <string.h>

#include "comar.h"
#include "cmrlib.h"
#include "privatlib.h"
#include "name.h"

#include "format.h"		/* Declaration of print_prod() */
#include "grammarcomp.h"	/* Declaration of ORDER	       */

#include "parserlib.h"
#include "printtbl.h"

#define _CLOSURE
#ifdef _CLOSURE
#include "lr0forpurdom.h"

/* the following functions are implemented in lr0.c */
extern	SEQitemtype	CLOSURE();
extern	void	createadded();
extern	void	freeadded();
#endif


void	printSet(set,f,actlg,erclg,isERC)
BitSet	set;
FILE	*f;
short	actlg, erclg;
Boolean	isERC;
{
  char	*c, *row;
  short	i;
static	char	nextercrow[MAXROW-25];
static	char	nextrow[MAXROW-25];
static	DID	*INDEXINVERS = (DID *)NULL;

  if ( set == (BitSet)NULL )
    return;

  if ( MAXROW - erclg  <  30 )
    erclg = MAXROW - 30;

  if ( isERC  &&  *nextercrow != '\n' )
    {				/* Initialization of nextercrow[] */
      c = nextercrow;
      *c = '\n';
      for ( c++;  erclg>0;  c++, erclg-- )
        *c = ' ';
      if ( isERC )
	(void)strcpy(c,"ERC: ");
      if ( INDEXINVERS == (DID *)NULL )
        INDEXINVERS = cmrlib_INDEX_Invers(Kp_term);
    }
  else if ( *nextrow != '\n' )
    {				/* Initialization of nextrow[] */
      c = nextrow;
      *c = '\n';
      for ( c++;  erclg>0;  c++, erclg-- )
        *c = ' ';
      if ( INDEXINVERS == (DID *)NULL )
        INDEXINVERS = cmrlib_INDEX_Invers(Kp_term);
    }

  if ( isERC )
    row = nextercrow;
  else
    row = nextrow;

  if ( MAXROW - actlg  <  25 )
    {
      actlg = fprintf(f, "%s", row) - 1;
    }
  else if ( isERC )
    {
      (void)fprintf(f, "     ERC: ");
      actlg += 10;
    }

  for ( i=0; (Indextype) i<MAXTERM; i++ )
    if ( IsElemInSet(i,set) )
      {
        c = priv_deftostr(DEFTBL[INDEXINVERS[i]]);
        erclg = (short)strlen(c);
        actlg = actlg + erclg + 2;
        if ( MAXROW  <  actlg )
	  {
	    actlg = fprintf(f, "%s", row);
	    actlg += fprintf(f, "%s", c);
	  }
        else
	  (void)fprintf(f, "  %s", c);
      }  /* end of if */

  return;
}  /* end of printSet() */


short	printUnit(X,f,actlg)
p_elunit	X;
FILE		*f;
int		actlg;
{
  int	lg = 0;
  char	*c = "\0";
  char	*str;

  switch ( typeof(DEFTBL[X->did]) )
    {
      case Kp_term:
	  lg = 2;		/* offset */
	   c = "\'";
      case Kp_nterm:
	  str = priv_deftostr(DEFTBL[X->did]);
	  lg += strlen(str) + 1;
	  if ( actlg+lg > MAXROW )
	    {
	      fprintf(f, "\n %s%s%s", c, str, c);
	      return(lg);
	    }  /* end of if */
	  else
	    {
	      fprintf(f, " %s%s%s", c, str, c);
	      return(actlg+lg);
	    }  /* end of else */
      case Kp_other:
	  return(actlg);
      default:
	  UL_TAG_ERR("printUnit()",typeof(DEFTBL[X->did]));
	  if ( actlg+4 > MAXROW )
	    {
	      fprintf(f, "\n ???");
	      return(4);
	    }  /* end of if */
	  else
	    {
	      fprintf(f, " ???");
	      return(actlg+4);
	    }  /* end of else */
    }  /* end of switch */

}  /* end of printUnit() */




void	printKernel(X,f)
SEQitemtype	X;
FILE		*f;
{
  char		ROW[MAXROW+1];
  itemtype	item;
  p_prod	prod;
  SEQunit	rhstail;
  unit		un;
  char		KI, *TI;
  short		actlg, erclg;

  for ( ; !emptySEQitem(X); X=tlSEQitem(X) )
    {
      item = hdSEQitem(X);
      prod = DEFTBL[rulenoofitem(item)].Vp_prod;
      rhstail = prod->rhs;
      getfirstpos(&rhstail, (unsigned short *)&actlg);
      if ( emptySEQunit(rhstail) )
	KI = ' ';
      else
	KI = '*';
      switch ( tagofitem(item) )
	{
	  case Kshnterm: TI = "SN";	break;
	  case Kshterm : TI = "ST";	break;
	  case Kred    : TI = " R";	break;
	  default      : INT_TAG_ERR("printKernel()",tagofitem(item));
			 TI = "??";	break;
	}  /* end of switch */

      (void)sprintf(ROW," %c | %s | %3d:  %10s ->", KI, TI,
		    rulenoofitem(item), priv_deftostr(DEFTBL[prod->lhsdid])
		   );
      fprintf(f, "%s", ROW);
      erclg = actlg = (short)strlen(ROW);

      while ( rhstail != ruleposofitem(item) )
	{
	  un = headSEQunit(rhstail);
	  actlg = printUnit(un.Vp_elunit, f, actlg);
	  rhstail = tailSEQunit(rhstail);
	}  /* end of while */

      if ( actlg+2 > MAXROW )
	{
	  fprintf(f, "\n .");
	  actlg = 2;
	}
      else
	{
	  fprintf(f, " .");
	  actlg = actlg+2;
	}

      while ( !emptySEQunit(rhstail) )
	{
	  un = headSEQunit(rhstail);
	  actlg = printUnit(un.Vp_elunit, f, actlg);
	  rhstail = tailSEQunit(rhstail);
	}  /* end of while */

      if ( tagofitem(item) == Kshnterm )
	printSet(item.shnterm.erc, f, actlg, erclg, TRUE);
      else if ( tagofitem(item) == Kred )
	printSet(item.red.erc, f, actlg, erclg, TRUE);

      fprintf(f, "\n");

    }  /* end of for */

  return;
}  /* end of printKernel() */


void	printGoto(X,f)
SEQshifttype	X;
FILE		*f;
{
  short	actlg, lg;
  char	str[MAXROW];

  actlg = 0;
  while ( !emptySEQshift(X) )
    {
      if ( hdSEQshift(X).staterule < (short)UNDEF )
        sprintf(str, "(%s,SR:%d), ",
	        priv_deftostr(DEFTBL[hdSEQshift(X).symbol]),
		- hdSEQshift(X).staterule
	       );
      else
        sprintf(str, "(%s,S:%d), ",
	        priv_deftostr(DEFTBL[hdSEQshift(X).symbol]),
	        hdSEQshift(X).staterule
	       );

      lg = (short)strlen(str);
      X = tlSEQshift(X);
      if ( emptySEQshift(X) )
	str[lg-2] = '\0';

      if ( actlg+lg > MAXROW )
	{
	  fprintf(f, "\n%s", str);
	  actlg = lg;
	}
      else
	{
	  fprintf(f, "%s", str);
	  actlg = actlg+lg;
	}

    }  /* end of while */
  fprintf(f, "\n");
  return;
}  /* end of printGoto() */

void	print_Symbols(f)
FILE	*f;
{
  short		i;
  SEQdef_entry	travel;
  def_entry	symb;
  String	str;

#ifdef DEBUG_PRSLIB		/* With column INDEX */
  fprintf(f,"CMRDID | INDEX | TYPE | NAME\n");
  fprintf(f,"-------|-------|------|-----");
#endif
#ifndef DEBUG_PRSLIB		/* Without column INDEX */
  fprintf(f,"CMRDID | TYPE | NAME\n");
  fprintf(f,"-------|------|-----");
#endif
  for (i=27; i<MAXROW; i++)
    fprintf(f,"-");
  fprintf(f,"\n");

  foreachinSEQdef_entry(CMR->definitions, travel, symb)
    if ( typeof(symb) == Kp_term  ||  typeof(symb) == Kp_nterm )
      if ( *(str = priv_deftostr(symb)) != '\0' )
#ifdef DEBUG_PRSLIB		/* With column INDEX */
        fprintf(f,"%6d | %5d |   %s |  %s\n",
		  symb.IDLclassCommon->did,
		  INDEX[symb.IDLclassCommon->did],
		  (typeof(symb) == Kp_term)?  " T" : "NT",
		  priv_deftostr(symb)
	       );
#endif
#ifndef DEBUG_PRSLIB		/* Without column INDEX */
        fprintf(f,"%6d |   %s |  %s\n",
		  symb.IDLclassCommon->did,
		  (typeof(symb) == Kp_term)?  " T" : "NT",
		  priv_deftostr(symb)
	       );
#endif

  fprintf(f,"\n");
  return;
}  /* end of print_Symbols() */

void	print_Productions(f)
FILE	*f;
{
  short		i;
  p_string	ordersym;
  SEQdef_entry	travel;
  def_entry	prod;
  p_prop_val	propval;

  fprintf(f,"CMRDID | ORDER | PRODUCTIONS\n");
  fprintf(f,"-------|-------|------------");
  for (i=27; i<MAXROW; i++)
    fprintf(f,"-");
  fprintf(f,"\n");

  ordersym = cmrlib_strtopstring(CMR->symbols, ORDER);
  foreachinSEQdef_entry(CMR->definitions, travel, prod)
    if ( typeof(prod)  ==  Kp_prod )
      {
	propval = cmrlib_sidtopropval(prod.Vp_prod->prop,(SID)ordersym->sid);
#ifdef DEBUG_PRSLIB
	if ( propval  == (p_prop_val)NULL )
	  {
	fprintf(stderr, "There exists a rule without ruleorder-property.\n");
	    exit(1);
	  }
#endif
	fprintf(f,"%6d | %5d |  ", prod.Vp_prod->did,
				   propval->val.Vp_nval->val);
	print_prod(CMR, prod.Vp_prod->did, f);
      }  /* end of if */

  fprintf(f,"\n\n");
  return;
}  /* end of print_Productions() */


void	printMODIFICATIONS(f)
FILE	*f;
{
  modiftype	el;
  String	str;
  int		lg;

  while ( !emptySEQmodif(MODIFICATIONS) )
    {
      el = hdSEQmodif(MODIFICATIONS);
      lg = fprintf(f,"The %s-modification with ",el.tag? REDUCE : NOREDUCE );
      str = priv_deftostr(DEFTBL[el.term]);
      lg += strlen(str) + 11;
      if ( lg > MAXROW )
	lg = fprintf(f,"\nterminal '%s'", str) -1;
      else
	(void)fprintf(f,"terminal '%s'", str);
      lg += 19;
      if ( lg > MAXROW )
	lg = fprintf(f,"\nsolves a conflict:") -1;
      else
	(void)fprintf(f," solves a conflict:");
      if ( lg+27 > MAXROW )
	(void)fprintf(f,"\nproduction %3d, state %3d.\n",
			el.ruleno,el.stateno);
      else
	(void)fprintf(f," production %3d, state %3d.\n",
			el.ruleno,el.stateno);
      MODIFICATIONS = tlSEQmodif(MODIFICATIONS);
    }  /* end of while */
  fprintf(f,"\n");
  return;
}  /* end of printMODIFICATIONS() */


void	printCONFLICTSTATES(f)
FILE	*f;
{
  unsigned short q, i;

  /* Printing conflict-states if existing. */
  if ( CONFLICTSTATES  !=  (ARRSEQconflicttype)NULL )
    {
      fprintf(f, "CONFLICT-STATES:");
      i = 16;
      for ( q=1; q<=MAXSTATE; q++ )
	if ( !emptySEQconflict(CONFLICTSTATES[q]) )
	  {
	    if ( i > (unsigned short)(MAXROW-5) )
	      {
	        fprintf(f, "\n");
	        i = 16;
	      }  /* end of if */
	    fprintf(f, " %4d", q);
	    i += 5;
	  }  /* end of if */
      /* end of for */

      fprintf(f, "\n\n");
    }  /* end of if */

  return;
}  /* end of printCONFLICTSTATES() */


void	printConflict(str, q, f)
String		str;
unsigned short	q;
FILE		*f;
{
  SEQconflicttype	list;
  int	lg;

  if (  CONFLICTSTATES != (ARRSEQconflicttype)NULL  &&
	!emptySEQconflict( CONFLICTSTATES[q] ) )
    {
      fprintf(f,"CONFLICTS:\n");
      for ( list = CONFLICTSTATES[q];
	    !emptySEQconflict(list);
	    list = tlSEQconflict(list)
	  )
	{
	  if ( hdSEQconflict(list).red_red )
	    lg = fprintf(f,"    reduce-reduce conflict (%d:%d) with set: ",
			 hdSEQconflict(list).ruleno1,
			 hdSEQconflict(list).ruleno2
			);
	  else
	    lg = fprintf(f,"    shift-reduce conflict (%d) with set: ",
			 hdSEQconflict(list).ruleno1
			);
	  printSet(hdSEQconflict(list).set, f, lg, 14, FALSE );

	  fprintf(f, "\n");
	}  /* end of for */

      fprintf(f, "%s", str);
    }  /* end of if */
}  /* end of printConflict() */


void printGramStatist(f)
FILE		*f;
{
  symb_entry	symb;
  SEQdef_entry	travel;
  def_entry	def;
  p_other	oth = NULL;

  symb.Vp_string = cmrlib_strtopstring(CMR->symbols, GRAMNAME);
  if ( symb.IDLclassCommon != NULL )
    foreachinSEQdef_entry(OTHER_SEQ, travel, def)
    {
      if (  cmrlib_sidtoprop(def.Vp_other->prop, symb.IDLclassCommon->sid)
  	  != (p_prop)NULL  )
        {
	  oth = def.Vp_other;
 	  break;
        }
    }

  if ( oth == (p_other)NULL )
    fprintf(f, "Grammar\t\t\t : No Name\n");
  else
    fprintf(f, "Grammar\t\t\t : %s\n", priv_sidtostr(oth->sid));

  if ( CONFLICTSTATES == (ARRSEQconflicttype)NULL )
    fprintf(f, "Type\t\t\t : LALR(1)\n");
  else
    fprintf(f, "Type\t\t\t : IS NOT LALR(1)\n");

  fprintf(f, "Productions\t\t : %d\n", MAXPROD);
  fprintf(f, "Nonterminals\t\t : %d\n", MAXNTERM);
  fprintf(f, "Terminals\t\t : %d\n", MAXTERM-1);
  fprintf(f, "States\t\t\t : %d\n", MAXSTATE);

  if ( MODIFICATIONS == (SEQmodiftype)NULL )
    fprintf(f, "Successfull Modifications: NO\n\n\n");
  else
    fprintf(f, "Successfull Modifications: YES\n\n\n");

  return;
}  /* end of printGramStatist() */


void	printARRstate(X, f, opt)
ARRstatetype	X;
FILE		*f;
short		opt;
{
  unsigned short i, no;
  /* printall == FALSE: only conflict states will be printed */
  /* printall == TRUE: all states will be printed */
  Boolean	printall = TRUE;

static	char	crosses[MAXROW+2];
static	char	dashes[MAXROW+2];
static	char	*c = (char *)NULL;


  if ( MAXROW < 50 )
    {
      (void)fprintf(stderr,"Internal Error: constant MAXROW defined in");
      (void)fprintf(stderr," \"parserlib.h\" is chosen to small.\n");
    }

  if (opt == ONLY_CONFLICTS)
    {
	printall = FALSE;
	opt = AFTERLTST;
    }

  if ( opt != AFTERLR0  &&  opt != AFTERLALR  &&  opt != AFTERLTST )
    {
      (void)fprintf(stderr,
		    "Internal Error: wrong option in printARRstate()\n" );
      exit(1);
    }


  if ( c == (char *)NULL )
    {
      c = crosses;		/* Initialization of crosses[] */
      for ( i=0;  i<MAXROW;  i++,c++ )
        *c = '#';
      *c = '\n';
      c= dashes;		/* Initialization of dashes[] */
      for ( i=0;  i<MAXROW;  i++,c++ )
        *c = '-';
      *c = '\n';
    }
  if ( opt == AFTERLTST  &&  CONFLICTSTATES != (ARRSEQconflicttype)NULL )
    {
      fprintf(f,  "**************************************************\n");
      fprintf(f,  "** G R A M M A R   I S   N O T   L A L R (1) !! **\n");
      fprintf(f,  "**************************************************\n\n");
    }  /* end of if then */
  else if ( opt == AFTERLTST )
    {
      (void)fprintf(f,  "*****************************************\n");
      (void)fprintf(f,  "** G R A M M A R   I S   L A L R (1) . **\n");
      (void)fprintf(f,  "*****************************************\n\n");
    }  /* end of else if */
  else
    {
      fprintf(f,"*****************************************************\n");
      fprintf(f,"** G R A M M A R   I S   N O T   A N A L Y Z E D . **\n");
      fprintf(f,"*****************************************************\n\n");
    }

  fprintf(f, "*************************\n");
  fprintf(f, "** S T A T I S T I C S **\n");
  fprintf(f, "*************************\n");
  printGramStatist(f);

  if ( MODIFICATIONS != (SEQmodiftype)NULL )
    {
      (void)fprintf(f,  "******************************\n");
      (void)fprintf(f,  "** SUCCESSFUL MODIFICATIONS **\n");
      (void)fprintf(f,  "******************************\n\n");
      printMODIFICATIONS(f);
    }  /* end of if */


  (void)fprintf(f,  "***************************\n");
  (void)fprintf(f,  "** P R O D U C T I O N S **\n");
  (void)fprintf(f,  "***************************\n\n");
  print_Productions(f);

  (void)fprintf(f,  "*******************\n");
  (void)fprintf(f,  "** S Y M B O L S **\n");
  (void)fprintf(f,  "*******************\n\n");
  print_Symbols(f);

  if ( opt == AFTERLR0 )
    {
      (void)fprintf(f,"\n***************************************\n");
      (void)fprintf(f,  "** L R ( 0 ) - S T A T E - T A B L E **\n");
      (void)fprintf(f,  "***************************************\n\n");
    }
  else
    {
      (void)fprintf(f,"\n*******************************************\n");
      (void)fprintf(f,  "** L A L R ( 1 ) - S T A T E - T A B L E **\n");
      (void)fprintf(f,  "*******************************************\n\n");
    }

  printCONFLICTSTATES(f);

  fprintf(f,"%s", crosses);		/* one line of double-crosses */

#ifdef _CLOSURE
  createadded();
#endif

  for (no=1; no<=MAXSTATE; no++)
    if ( printall || !emptySEQconflict(CONFLICTSTATES[no]) )
    {
     fprintf(f,"STATE %4d:\t",no);
      fprintf(f,"On Error: %s\n",
	        (X[no].Errsymb == UNDEF)?
		"\"yet undefined\"" : priv_deftostr(DEFTBL[X[no].Errsymb])
	     );

      fprintf(f,"%s", dashes);		/* one line of dashes */

      printConflict(dashes,no,f);

#ifdef _CLOSURE
      {
	SEQitemtype items;

	items = CLOSURE(X[no].Kernel, FALSE);
	printKernel(items, f);
	rekdelSEQitem(items);
      }
#else
      printKernel(X[no].Kernel, f);
#endif

      fprintf(f,"%s", dashes);		/* one line of dashes */

      printGoto(X[no].Goto, f);

      fprintf(f,"%s", crosses);		/* one line of double-crosses */
    }  /* end of for */

#ifdef _CLOSURE
  freeadded();
#endif

  return;
}  /* end of printARRstate() */


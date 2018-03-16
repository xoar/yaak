/*
** $Id: privatlib.c,v 1.9 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: privatlib.c,v 1.9 1997/08/29 08:38:08 mjung Exp $";

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
/* File: privatlib.c	First Edit: 17.10.88	  Last Edit: 22.02.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 03.08.89	From: Karl-Josef Prott			   */
/***************************************************************************/

#include <stdio.h>
#include <string.h>

#include "comar.h"
#include "cmrlib.h"

#include "format.h"     /* function print_prod() */

#include "privatlib.h"

#define	CONFIG_ERR(s1,s2)	{ (void)fprintf(stderr,\
		"Configuration Error (%s) during computation of '%s'.\n", s1, s2); \
		return; }

#define	DEADLY_ERR(s1,s2)	{ (void)fprintf(stderr,\
		"Deadly Error (%s) during computation of '%s'.\n", s1, s2); \
		return; }

#if defined(__cplusplus) || defined(__STDC__)
void priv_generrstr(ERR	code, String f_name)
#else
void priv_generrstr(code, f_name)
ERR	code;
String	f_name;
#endif
{

  switch (code)
    {
	/* errorcodes of modules "cmrlib" and "cmrio" */
      case    0	: /* CMR_SUCCESS */
		  return;
      case   -1	: DEADLY_ERR("CMR_UNKERR", f_name);
      case   -2	: /* CMR_OPNERR */
		  fprintf(stderr, "Error: Can't open file '%s'\n", f_name);
		  return;
      case   -3	: /* CMR_WRTERR */
		  fprintf(stderr, "Error: Can't open file '%s' for writing\n", f_name);
		  return;
      case   -4	: /* CMR_RDERR */
		  fprintf(stderr, "Error: Can't open file '%s' for reading\n", f_name);
		  return;
      case   -5	: DEADLY_ERR("CMR_NOSUCC", f_name);

	/* errorcodes of module "contrafo" */
      case  -11	: DEADLY_ERR("TRF_CONUNK", f_name);
      case  -12	: DEADLY_ERR("TRF_WRONGTAG", f_name);
      case  -13 : DEADLY_ERR("TRF_WRONGOPT", f_name);

	/* errorcodes of module "grammarcomp" */
      case  -21	: /* ST_NOSTSYM */
		  fprintf(stderr, "Error: Grammar has no startsymbol.\n");
		  return;
      case  -22	: /* ST_AMBSTSYM */
		  fprintf(stderr, "Error: Grammar has more than one startsymbol.\n");
		  return;
      case  -23	: /* ST_AMBSTPROD */
		  fprintf(stderr, "Error: Grammar has more than one startproduction.\n");
		  return;
      case  -24	: /* ST_NOTBNFSTPROD */
		  fprintf(stderr, "Error: Startproduction must be in strict BNF.\n");
		  return;
      case  -25	: /* ST_EOFNOTERM */
		  fprintf(stderr, "Error: The determined End-Of-File symbol is not a terminal.\n");
		  return;
      case  -26	: /* ST_AMBEOF */
		  fprintf(stderr, "Error: More than one End-Of-File symbol has been determined.\n");
		  return;
      case  -27	: /* ST_EOFERR */
		  fprintf(stderr, "Error: The 'EOF'-symbol can be also found \
in other positions than the end of the startproduction.\n");
		  return;
      case  -31 : /* GR_NOTREACH */
		  fprintf(stderr, "Error: Grammar isn't reduced because of not reachable nonterminals.\n");
		  return;
      case  -32 : /* GR_NOTBNF */
		  CONFIG_ERR("GR_NOTBNF", f_name);
      case  -33 : /* GR_NODEFAULT */
		  CONFIG_ERR("GR_NODEFAULT", f_name);
      case  -34 : /* GR_NTHASNOPROD */
		  DEADLY_ERR("GR_NTHASNOPROD", f_name);
      case  -35 : /* GR_ORDER_EXIST */
		  DEADLY_ERR("GR_ORDER_EXIST", f_name);
      case  -36 : /* GR_NOTREDUCED */
		  fprintf(stderr, "Error: Grammar isn't reduced.\n");
		  return;
      case  -37 : /* GR_IDENTRULES */
                  fprintf(stderr, "Error: the grammar contains the following \
rule more than once:\n");
                  print_prod(CMR, (unsigned long)f_name, stderr);
                  return;

	/* errorcodes of module "lr0" */
      case  -41 : /* LR0_NOORDER */
		  CONFIG_ERR("LR0_NOORDER", f_name);
      case  -42 : /* LR0_GRNOTBNF */
		  CONFIG_ERR("LR0_GRNOTBNF", f_name);
      case  -43 : /* LR0_PRODNOORDER */
		  CONFIG_ERR("LR0_PRODNOORDER", f_name);
      case  -44 :  /* LR0_DEFTBLERR */
                  CONFIG_ERR("LR0_DEFTBLERR", f_name);
      case  -45 : /* LR0_NOSTART */
                  CONFIG_ERR("LR0_NOSTART", f_name);

	/* errorcodes of module "lalr" */
      case  -46 : /* LALR_AMBEPS */
                  CONFIG_ERR("LALR_AMBEPS", f_name);
      case  -49 : /* ISNOTLALR1 */
		  fprintf(stderr, "Error: Grammar is not LALR(1).\n");
		  return;

      case  -51 : /* FIR_TRANSCLOSERR */
		  fprintf(stderr, "Error: Can't evaluate first set for nonterminal '%s'.\n", f_name);
		  return;
      case  -52 : /* FIR_WRTERR */
		  fprintf(stderr, "Error: Can't write first sets to file.\n");
		  return;
      case  -53 : /* FIR_PRESENT */
                  CONFIG_ERR("FIR_PRESENT", f_name);
      case  -54 : /* FIR_NOTERMIN */
		  fprintf(stderr, "Error: Grammar isn't reduced because of nonterminals, that can't be terminalized.\n");
		  return;
      case  -56 : /* FIR_INCOMPL */
                  CONFIG_ERR("FIR_INCOMPL", f_name);
      case  -57 : /* FIR_UNK */
                  CONFIG_ERR("FIR_UNK", f_name);

      default		: {
			    static char str[20];

			    (void)sprintf(str, "%d", code);
			    DEADLY_ERR( (String)str, "priv_generrstr()" );
			  }
    }	/* of switch */
}		/* end of  priv_generrstr */


#if defined(__cplusplus) || defined(__STDC__)
String priv_genfilename(String name, String ext)
#else
String priv_genfilename(name, ext)
String	name, ext;
#endif
{
  int l1, l2;
  char *result;


  l1 = strlen(name);
  l2 = strlen(ext);
  if ( l1 > MAXNAMLEN - l2 )
    l1 = MAXNAMLEN - l2 - 1;

  if ( (result = malloc( (l1+l2+1)*sizeof(char) ))  == (char *)NULL )
    {
      INT_ALLOC_ERR("priv_genfilename()");
      exit(1);
    }

  (void)strncpy(result, name, l1+1);
  (void)strncat(result, ext, l2);

  return(result);
}		/* end of priv_genfilename() */


#if defined(__cplusplus) || defined(__STDC__)
String	priv_sidtostr(SID sid)
#else
String	priv_sidtostr(sid)
SID	sid;
#endif
{
  symb_entry	sym;

  sym = cmrlib_getsymb(CMR->symbols, sid);
  return(sym.IDLclassCommon->str);
}		/* end of priv_sidtostr() */

#if defined(__cplusplus) || defined(__STDC__)
void	priv_printdefseq(SEQdef_entry d_seq)
#else
void	priv_printdefseq(d_seq)
SEQdef_entry	d_seq;
#endif
{
  String sep = NULL; /* == FALSE */
  def_entry	def;

  for (; !emptySEQdef_entry(d_seq); removefirstSEQdef_entry(d_seq) )
    {
      retrievefirstSEQdef_entry(d_seq, def);
      fprintf(stderr, "%s%s", (sep? (sep = ", ") : " "), priv_deftostr(def));
    }
}


#if defined(__cplusplus) || defined(__STDC__)
void	priv_print_rhsdid(SEQdef_entry prods, FILE *f)
#else
void	priv_print_rhsdid(prods, f)
SEQdef_entry	prods;
FILE		*f;
#endif
{
  SEQdef_entry	travel1;
  def_entry	p, def;
  SEQunit	travel2;
  unit		u;
  int		d;

  foreachinSEQdef_entry(prods, travel1, p)
    {
      if ( typeof(p) != Kp_prod )
	UL_TAG_ERR("priv_print_rhsdid1()", typeof(p));
      else
	{
	  fprintf(f, "\t\tlhs: %d,  rhs:", p.Vp_prod->lhsdid);
	  foreachinSEQunit(p.Vp_prod->rhs, travel2, u)
	    {
	      if ( typeof(u) != Kp_elunit )
		UL_TAG_ERR("priv_print_rhsdid2()", typeof(u));
	      else
		if ( (d = u.Vp_elunit->did) > 0 )
		  {
		    def = cmrlib_getdef(CMR->definitions,d);
		    fprintf(f, " , %d(%s)", d, priv_deftostr(def));
		  }
		else
		  fprintf(f, " , %d(%s)", d, "-");
	    }
	  fprintf(f,"\n");
	}  /* of else */
    }  /* of for */
}  /* of priv_print_rhsdid() */


/*********************************************************************/
/* SECTION 5 : ADT "stack" for elemets with                          */
/*			   sizeof("elements") <= sizeof("pointer")   */
/*********************************************************************/

stacktype	STACK_GARB = NULL;

#if defined(__cplusplus) || defined(__STDC__)
stacktype push(stacktype stack, eltype el)
#else
stacktype push(stack, el)
stacktype	stack;
eltype		el;
#endif
{
  stacktype	new;

  if ( STACK_GARB )
    {
      new = STACK_GARB;
      STACK_GARB = STACK_GARB->next;
    }
  else if ( (new=(stacktype)malloc(sizeof(struct sttype))) == (stacktype)NULL )
  {
    INT_ALLOC_ERR("push()");
    exit(1);
  }
  new->val = el;
  new->next = stack;
  return(new);
}

#if defined(__cplusplus) || defined(__STDC__)
stacktype pop(stacktype	stack)
#else
stacktype pop(stack)
stacktype	stack;
#endif
{
  stacktype	result;

  result = stack->next;
  stack->next = STACK_GARB;
  STACK_GARB = stack;
  return(result);
}


#if defined(__cplusplus) || defined(__STDC__)
Boolean	isin(stacktype stack, eltype el)
#else
Boolean	isin(stack,el)
stacktype	stack;
eltype		el;
#endif
{
  for ( ; stack!=NULL; stack=stack->next )
    if ( stack->val == el )
      return(TRUE);
  return(FALSE);
}  /* end of isin() */

shstacktype	SHSTACK_GARB = NULL;

#if defined(__cplusplus) || defined(__STDC__)
shstacktype shpush(shstacktype stack, sheltype el)
#else
shstacktype shpush(stack, el)
shstacktype	stack;
sheltype	el;
#endif
{
  shstacktype	new;

  if ( SHSTACK_GARB )
    {
      new = SHSTACK_GARB;
      SHSTACK_GARB = SHSTACK_GARB->next;
    }
  else if ( (new=(shstacktype)malloc(sizeof(struct shsttype))) == (shstacktype)NULL )
  {
    INT_ALLOC_ERR("push()");
    exit(1);
  }
  new->val = el;
  new->next = stack;
  return(new);
}

#if defined(__cplusplus) || defined(__STDC__)
shstacktype shpop(shstacktype stack)
#else
shstacktype shpop(stack)
shstacktype	stack;
#endif
{
  shstacktype	result;

  result = stack->next;
  stack->next = SHSTACK_GARB;
  SHSTACK_GARB = stack;
  return(result);
}


#if defined(__cplusplus) || defined(__STDC__)
Boolean	shisin(shstacktype stack, sheltype el)
#else
Boolean	shisin(stack, el)
shstacktype stack;
sheltype el;
#endif
{
  for ( ; stack!=NULL; stack=stack->next )
    if ( stack->val == el )
      return(TRUE);
  return(FALSE);
}  /* end of isin() */


#if defined(__cplusplus) || defined(__STDC__)
queuetype qcreate(void)
#else
queuetype qcreate()
#endif
{
  queuetype	res;

  if ( (res=(queuetype)malloc(sizeof(struct _queuetype)))  == (queuetype)NULL )
  {
    INT_ALLOC_ERR("qcreate()");
    exit(1);
  }

  res->first = (stacktype)NULL;
  res->last = (stacktype)NULL;
  return(res);
}

#if defined(__cplusplus) || defined(__STDC__)
queuetype enq(queuetype	qu, eltype el)
#else
queuetype enq(qu,el)
queuetype	qu;
eltype	el;
#endif
{
  stacktype	new;

  if ( STACK_GARB )
  {
    new = STACK_GARB;
    STACK_GARB = STACK_GARB->next;
  }
  else if ( (new=(stacktype)malloc(sizeof(struct sttype))) == (stacktype)NULL )
  {
    INT_ALLOC_ERR("enq()");
    exit(1);
  }

  new->val = el;
  new->next = (stacktype)NULL;

  if ( qu->first == (stacktype)NULL )
    qu->first = qu->last = new;
  else
    qu->last = (qu->last->next = new);

  return(qu);
}

#if defined(__cplusplus) || defined(__STDC__)
queuetype	deq(queuetype qu)
#else
queuetype	deq(qu)
queuetype       qu;
#endif
{
  stacktype     tmp;

  tmp = qu->first;
  /* This isn't necessary: empty <==> qu->first==NULL
   * if ( (qu->first = qu->first->next)  ==  (stacktype)NULL )
   *   qu->last = (stacktype)NULL;
   */
  qu->first = qu->first->next;
  tmp->next = STACK_GARB;
  STACK_GARB = tmp;

  return(qu);
}

#if defined(__cplusplus) || defined(__STDC__)
shqueuetype shqcreate(void)
#else
shqueuetype shqcreate()
#endif
{
  shqueuetype	res;

  if ( (res=(shqueuetype)malloc(sizeof(struct _shqueuetype)))  == (shqueuetype)NULL )
  {
    INT_ALLOC_ERR("shqcreate()");
    exit(1);
  }

  res->first = (shstacktype)NULL;
  res->last = (shstacktype)NULL;
  return(res);
}

#if defined(__cplusplus) || defined(__STDC__)
shqueuetype shenq(shqueuetype qu, sheltype el)
#else
shqueuetype shenq(qu,el)
shqueuetype	qu;
sheltype	el;
#endif
{
  shstacktype	new;

  if ( SHSTACK_GARB )
  {
    new = SHSTACK_GARB;
    SHSTACK_GARB = SHSTACK_GARB->next;
  }
  else if ( (new=(shstacktype)malloc(sizeof(struct shsttype))) == (shstacktype)NULL )
  {
    INT_ALLOC_ERR("shenq()");
    exit(1);
  }

  new->val = el;
  new->next = (shstacktype)NULL;

  if ( qu->first == (shstacktype)NULL )
    qu->first = qu->last = new;
  else
    qu->last = (qu->last->next = new);

  return(qu);
}

#if defined(__cplusplus) || defined(__STDC__)
shqueuetype	shdeq(shqueuetype qu)
#else
shqueuetype	shdeq(qu)
shqueuetype       qu;
#endif
{
  shstacktype     tmp;

  tmp = qu->first;
  /* This isn't necessary: empty <==> qu->first==NULL
   * if ( (qu->first = qu->first->next)  ==  (stacktype)NULL )
   *   qu->last = (stacktype)NULL;
   */
  qu->first = qu->first->next;
  tmp->next = SHSTACK_GARB;
  SHSTACK_GARB = tmp;

  return(qu);
}








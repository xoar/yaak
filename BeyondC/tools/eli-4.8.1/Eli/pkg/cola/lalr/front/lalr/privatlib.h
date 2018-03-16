/*
** $Id: privatlib.h,v 1.7 1997/08/29 08:38:08 mjung Exp $
*/

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
/* File: privatlib.h	First Edit: 17.10.88	  Last Edit: 22.02.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/***************************************************************************/


#ifndef	privlib_DEF
#define privlib_DEF

#include "cmrlib.h"

/*********************************************************************/
/* TABLE OF CONTENTS :                                  	     */
/*	SECTION 1 : constant-definitions			     */
/*	SECTION 2 : variable-definitions                             */
/*	SECTION 3 : macros                                           */
/*	    3.1   : macros for general use			     */
/*	    3.2   : additions to the IDL-macros generated to "comar.idl" */
/*	SECTION 4 : "extern"-declarations of functions               */
/*					  implemented in privatlib.c */
/*	SECTION 5 : ADTs "stack" and "queue"			     */
/*	SECTION 6 : error codes	(compare priv_generrstr())	     */
/*********************************************************************/

/*********************************************************************/
/* SECTION 1 : constant-definitions                                  */
/*********************************************************************/

/* Maximal length of filenames */
#define MAXNAMLEN	80


/*********************************************************************/
/* SECTION 2  : variable-definitions                                 */
/*********************************************************************/


/*********************************************************************/
/* SECTION 3 : macros                                                */
/*********************************************************************/

/* SECTION 3.1: macros for general use				     */

#define strequal(a,b)  (!(strcmp(a,b)))

#define INT_ERR(str)	(void)fprintf(stderr,"Internal error in %s\n",str)

#define INT_TAG_ERR(str,tg)	(void)fprintf(stderr,\
		"Internal error in %s: wrong tag: %d\n",\
		str, tg)
#define UL_TAG_ERR(str,tg)	(void)fprintf(stderr,\
		"Internal error in %s: wrong tag: %lu\n",\
		str, tg)

#define INT_ALLOC_ERR(str)	(void)fprintf(stderr,\
		"Fatal error in %s: no allocation possible!\n", str)


#ifndef _P
#if defined(__STDC__) || defined(__cplusplus)
#define _P(x) x
#else
#define _P(x) ()
#endif
#endif

/* SECTION 3.2: additions to the IDL-macros generated to "comar.idl" */

#define manipulSEQsymb_entry(symbseq,formanipul,elem)  for\
	    (formanipul = &symbseq;\
	     *formanipul != NULL &&\
                ((elem.IDLinternal = (*formanipul)->value.IDLinternal)||1);\
	     formanipul = &(*formanipul)->next   )

#define manipulSEQdef_entry(defseq,formanipul,elem)  for\
	    (formanipul = &defseq;\
	     *formanipul != NULL &&\
                ((elem.IDLinternal = (*formanipul)->value.IDLinternal)||1);\
	     formanipul = &(*formanipul)->next   )

#define manipulSEQprop_entry(propseq,formanipul,elem)  for\
	    (formanipul = &propseq;\
	     *formanipul != NULL &&\
                ((elem.IDLinternal = (*formanipul)->value.IDLinternal)||1);\
	     formanipul = &(*formanipul)->next   )

#define manipulSEQunit(unitseq,formanipul,elem)  for\
	    (formanipul = &unitseq;\
	     *formanipul != NULL &&\
                ((elem.IDLinternal = (*formanipul)->value.IDLinternal)||1);\
	     formanipul = &(*formanipul)->next   )

#define manipulSEQvalue(valseq,formanipul,elem)  for\
	    (formanipul = &valseq;\
	     *formanipul != NULL &&\
                ((elem.IDLinternal = (*formanipul)->value.IDLinternal)||1);\
	     formanipul = &(*formanipul)->next   )


/* SECTION 3.3: macros using functions of "cmrlib" or "privatlib" */

#define priv_deftostr(def)	(priv_sidtostr(def.IDLclassCommon->sid))
#define priv_proptostr(prop)	(priv_sidtostr(prop.IDLclassCommon->sid))


/*********************************************************************/
/* SECTION 4 : "extern"-declarations of functions                    */
/*					  implemented in privatlib.c */
/*********************************************************************/

extern	void	priv_generrstr _P(( ERR code, String name ));

extern	String	priv_genfilename _P(( String  name, String ext ));

extern	String	priv_sidtostr _P(( SID sid ));

extern	void	priv_printdefseq _P(( SEQdef_entry d_seq ));

extern	void	priv_print_rhsdid _P(( SEQdef_entry d_seq, FILE *f ));

/*********************************************************************/
/* SECTION 5 : ADT "stack" and "queue" for elemets with              */
/*			   sizeof("elements") <= sizeof("pointer")   */
/*********************************************************************/

/* generic type of stack-elements: use cast-operator for type-conversion! */
typedef char	*eltype;

/* typedefinition for stack-variables */
typedef struct sttype
	{
	  eltype	val;
	  struct sttype	*next;
	}	*stacktype;

/* top, pop and next are not defined for empty stacks! */
#define create()	( (stacktype)NULL )
#define top(stack)	( (stack)->val )
#define empty(stack)	( (stack) == (stacktype)NULL )
#define tail(stack)	( (stack)->next )	/* pop without delete */

extern	stacktype push _P(( stacktype stack, eltype el ));
extern	stacktype pop _P(( stacktype stack ));
extern	Boolean	  isin _P(( stacktype stack, eltype el ));

/* Stack for Elements of sizeof(short). The Compiler generates awful warnings
 * if a pointer should be converted into a short... */

typedef short sheltype;

/* typedefinition for stack-variables */
typedef struct shsttype
	{
	  sheltype		val;
	  struct shsttype	*next;
	}	*shstacktype;

/* top, pop and next are not defined for empty stacks! */
#define shcreate()	( (shstacktype)NULL )
#define shtop(stack)	( (stack)->val )
#define shempty(stack)	( (stack) == (shstacktype)NULL )
#define shtail(stack)	( (stack)->next )	/* pop without delete */

extern	shstacktype shpush _P(( shstacktype stack, sheltype el ));
extern	shstacktype shpop _P(( shstacktype stack ));
extern	Boolean	  shisin _P(( shstacktype stack, sheltype el ));


/* typedefinition for queue-variables */
typedef struct _queuetype
	{
	  stacktype	first;
	  stacktype	last;
	}	*queuetype;

/* front and deq are not defined for empty queues! */
#define	qempty(queue)	((queue)->first == (stacktype)NULL)
#define	front(queue)	((queue)->first->val)

extern	queuetype qcreate _P((void));
extern	queuetype enq _P(( queuetype queue, eltype e));
extern	queuetype deq _P(( queuetype queue ));

/* typedefinition for queue-variables */
typedef struct _shqueuetype
	{
	  shstacktype	first;
	  shstacktype	last;
	}	*shqueuetype;

/* front and deq are not defined for empty queues! */
#define	shqempty(queue)	((queue)->first == (shstacktype)NULL)
#define	shfront(queue)	((queue)->first->val)

extern	shqueuetype shqcreate _P((void));
extern	shqueuetype shenq _P(( shqueuetype queue, sheltype e));
extern	shqueuetype shdeq _P(( shqueuetype queue ));

/*********************************************************************/
/* SECTION 6  : error codes 					     */
/*********************************************************************/

#define TRF_CONUNK      -11
        /* TRF_CONUNK  : there exists no connection with name 'str' in the
         *               COMAR-data-structure.
         */
#define TRF_WRONGTAG    -12
        /* TRF_WRONGTAG: error in "name.h": CONNECTTYPE must be Kp_string
         * or Kp_name
         */
#define TRF_WRONGOPT    -13
        /* wrong optioncode */

#define ST_NOSTSYM      -21
                /* No startsymbol can be determined. */
#define ST_AMBSTSYM     -22
                /* More than one startsymbol are determined. */
#define ST_AMBSTPROD    -23
                /* More than one startproduction are determined. */
#define ST_NOTBNFSTPROD -24
                /* Determined startproduction is not BNF. */
#define ST_EOFNOTERM    -25
                /* The 'EOF'-symbol determined as the last symbol of the
                 * startproduction is not a terminal.
                 */
#define ST_AMBEOF       -26
                /* More than one def_entry of the 'EOF'-symbol exists. */
#define ST_EOFERR       -27
                /* The 'EOF'-symbol can be also found in other positions
                 * than the end of the startproduction.
                 */

#define GR_NOTREACH     -31
                /* Not all nonterminals can be reached from startsymbol */
#define GR_NOTBNF       -32
                /* Grammar is not in BNF */
#define GR_NODEFAULT    -33
                /* Use cmrtl_default_for_grammar() to compute the
                 * default-productions
                 */
#define GR_NTHASNOPROD  -34
                /* There exists a nonterminal without a production */
#define GR_ORDER_EXIST  -35
                /* There exists a property with name ORDER not convenient
                 * to this application
                 */
#define GR_NOTREDUCED   -36
                /* Grammar is not reduced because of both possible
                 * conditions: GR_NOTREACH and CMRTL_NOTERMIN
                 */
#define GR_IDENTRULES   -37
                /* There are identical rules in the Grammar */



#define LR0_NOORDER     -41
#define LR0_GRNOTBNF    -42
#define LR0_PRODNOORDER -43
#define LR0_DEFTBLERR   -44
#define LR0_NOSTART     -45
#define LALR_AMBEPS     -46
#define ISNOTLALR1      -49     /* Grammar of the automaton 'automat' is */
                                /* not LALR(1) - 'automat' is nondeterm. */

#define FIR_TRANSCLOSERR -51    /* Error in computing the transitive
                                         * closure of the first-sets */
#define FIR_WRTERR      -52     /* Error in writing the first-sets */
#define FIR_PRESENT     -53     /* first-sets already computed */
#define FIR_NOTERMIN	-54	/* */
#define FIR_VERSION     -55     /* wrong value of 'version' in cmrtl_first()'*/
#define FIR_INCOMPL     -56     /* There are nonterminals for which no  */
                                /* first-set is computed.               */
#define FIR_UNK         -57     /* There are no first-sets. The name    */
                                /* FIRST (= "_FIRST1") is unknown. */

#endif		/* of privlib_DEF */

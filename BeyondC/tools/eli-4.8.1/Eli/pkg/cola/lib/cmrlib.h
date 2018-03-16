/*
** $Id: cmrlib.h,v 1.7 1997/08/29 08:38:08 mjung Exp $
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
/* File: cmrlib.h	First Edit: 10.10.88	  Last Edit: 14.02.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 10.05.89	From: Karl-Josef Prott			   */
/***************************************************************************/

/* This is a header file to a COMAR library. The types, constants and 
 * functions defined here should help working with the COMAR-data-structure.
 * Consider this library as an addition to the IDL generated routines in 
 * "comar.h" and the generated functions in "comar_func.h". Very important
 * is the use of the global variable 'CMR' needed by by a lot of functions
 * declared here. Using this library a clever person will also employ 'CMR'
 * in his own implementations to avoid a permanent copy of the COMAR-
 * structure-pointer with 'cmrlib_changeglobalcmrvar()'.
 *
 * Table of Contents:
 * 	SECTION 1 : Type-identifier, constant-definitons and the global 
 *	            variable 'CMR' for general use
 * 	SECTION 2 : Creating and initializing new COMAR components
 * 	SECTION 3 : Deleting COMAR lists and components
 * 	SECTION 4 : Fetching COMAR attributes of COMAR components
 * 	  SECT. 4.1: Fetching entries of symbol-table
 * 	  SECT. 4.2: Fetching entries of definiton-table
 * 	  SECT. 4.3: Fetching properties out of property-list
 *	SECTION 5 : Further list operations analogous to those of "comar.h"
 *	SECTION 6 : Computing general datas of COMAR-structure
 *	SECTION 7 : Global variables and their functions for faster accesses
 *		    to the COMAR-structure
 */

#ifndef  cmrlib_DEF
#define  cmrlib_DEF

#include "comar.h"

/* SECTION 1 : Type-identifier, constant-definitons and the global 
 *	       variable 'CMR' for general use
 */

/* Condition codes returned by some COMAR functions.*/
#define CMR_SUCCESS  0
#define CMR_NOSUC   -5
#define CMR_UNKERR  -1

/* define constants for two predefined COMAR symbols: */
#define S_NONAME	1
#define S_EMPTY		2

/* often used type-identifier */
typedef unsigned short	SID;	/* non-negative symbol encoding */
typedef unsigned short	DID;	/* non-negative definition encoding */
typedef short 		ERR;	/* type of functions returning errorcodes */


/* global variable for COMAR-data-structure for general use(!) */
extern	p_comar CMR; /* see also cmrlib_changeglobalcmrvar() */


/* This function sets global variable 'CMR' to 'comarvar' and returns 
 * the old value of 'CMR'. A lot of functions declared in "cmrlib.h" use
 * 'CMR' as the default COMAR-variable. So you must set 'CMR' to the 
 * right COMAR-data-structure before using them. You should also use
 * 'CMR' to avoid often use of this function. This functions allows also 
 * to manage several COMAR-structures.
 * return == the old value of 'CMR'
 */ 
extern	p_comar	cmrlib_changeglobalcmrvar(/* p_comar comarvar */);

#include "cmrinternal.h"

/* SECTION 2. Creating and initializing new COMAR components. */

/* Return new empty COMAR structure (initialized for pre-defined symbols) */
extern p_comar cmrlib_newstructure();

#ifndef MACRO
/* Insert new symbol into set of symb_entry's. Repeat call with same symbol
 * is ignored. A symb_entry can be neither deleted nor modified.
 * return == the new ( or already present ) symb_entry of type
 *           'p_string' or 'p_name'.
 */
extern p_string	cmrlib_newstring( /* String str */ );
extern p_name	cmrlib_newname( /* String str */ );


/*  Insert new term, nterm, or other into list of def_entry's. Repeat call
 *  with same SID results in a second entry. So double entries are possible!
 *  return == the new def_entry of type 'p_term', ... , 'p_prod' with an 
 *	      empty property-list.
 *         == NULL, if internal error occured.
 */
extern p_term  cmrlib_newterm( /* SID sid; */);
extern p_nterm cmrlib_newnterm( /* SID sid; */);
extern p_other cmrlib_newother( /* SID sid; */);
#endif		/* of MACRO */
extern p_prod  cmrlib_newprod(/*SID sid; DID lhs; SEQunit units;*/);

/* This global variable is needed for the macro cmrlib_newprop() invoking
 * cmrlib_propnewxy() with a dummy value. The value of DUMMYvalue may be
 * undefined, because it's never used in such cases.
 */
extern	value   DUMMYvalue;

#ifndef MACRO

/*  Insert new property identified by 'sid' into list of properties of 
 *  def_entry 'def' - except there already exists a property of type 'p_prop'
 *  with name identified by 'sid'. 
 *  return == the new or already present prop_entry of type 'p_prop' .
 */
extern p_prop     cmrlib_newprop( /* def_entry def; SID sid; */ ); 

/*  Insert new property identified by 'sid' into list of properties of 
 *  def_entry 'def' - except there already exists a property of type
 *  'p_prop_val' with name identified by 'sid'. Check with
 *  'cmrlib_sidtopropval()', whether such a propval exists.
 *  return == the new or already present prop_entry of type 'p_prop_val' .
 */
extern p_prop_val cmrlib_newpropval(/* def_entry def; SID sid; value val*/); 
#endif		/* of MACRO */


/* Geneating new def_entry beginning with String 'prefix', inserting
 * in symbol-table and definition-table.
 * return == the new def_entry of type 'p_term', 'p_nterm' or 'p_other' 
 *	     with an empty property-list.
 *        == NULL, if internal error occured.
 */
extern	p_term	cmrlib_genTerm(/* String prefix */);
extern	p_nterm	cmrlib_genNTerm(/* String prefix */);
extern	p_other	cmrlib_genOther(/* String prefix */);


/* SECTION 3 : Deleting COMAR lists and components. */

/* Deletes def_entry out of list *ptr_ofseq, but doesn't free their storage.
 * return == deleted def_entry, if one was found with index 'did'
 * return == NULL,  else ( in component IDLclassCommon of def_entry )
 */
extern	def_entry cmrlib_deldefentry(/* SEQdef_entry *ptr_ofseq, DID did */);

#ifndef MACRO
/* Deletes property out of list, but doesn't free their storage.
 * return == deleted property, if one was found with name 'sid'
 * return == NULL,  else ( = such an element not found )
 */
extern	p_prop		cmrlib_delprop(/* def_entry def, SID sid */);
extern	p_prop_val	cmrlib_delpropval(/* def_entry def, SID sid */);
#endif		/* of MACRO */

/* Traverse through all components, subtrees and sublists
 * and frees their storage.
 * return == CMR_SUCCESS, if no error occured 
 *      ( == NULL for use as NULL-pointer for the deleted variable )
 * return == CMR_NOSUC, else
 */
extern	ERR	cmrlib_rekdeldef(/* def_entry def */);
extern	ERR	cmrlib_rekdelunit(/* unit un */);
extern	ERR	cmrlib_rekdelprop(/* prop_entry prop */);
extern	ERR	cmrlib_rekdelval(/* value val */);

/* Traverse through all elements and their components, subtrees and sublists
 * and frees their storage.
 * return == CMR_SUCCESS, if no error occured
 *      ( == NULL for use as NULL-pointer for the deleted variable )
 * return == CMR_NOSUC, else
 */
extern	ERR	cmrlib_rekdelSEQdef_entry(/* SEQdef_entry d_seq */);
extern	ERR	cmrlib_rekdelSEQunit(/* SEQunit u_seq */);
extern	ERR	cmrlib_rekdelSEQprop_entry(/* SEQprop_entry p_seq */);
extern	ERR	cmrlib_rekdelSEQvalue(/* SEQvalue v_seq */);

 


/* SECTION 4 : Fetching COMAR attributes of COMAR components. */

/* SECTION 4.1: Fetching entries of symbol-table under different aspects */

/* return == the symbol with index 'sid' out of list 'seq',
 *                 if such an entry is existing
 *        == NULL, else  (stored in component IDLclassCommon of symb_entry)
 */
extern	symb_entry	cmrlib_getsymb(/* SEQsymb_entry seq, SID sid */);

/* return == a sequence collecting all symbols with a string 'str' (there
 *	     are at most two such symbols - one of type 'p_name' and one
 *	     'p_string'. An empty sequence shows, there were no such entry)
 */
extern	SEQsymb_entry	cmrlib_strtosymbs(/*SEQsymb_entry seq, String str*/);

#ifndef MACRO
/* return == symbol of type 'p_string' or 'p_name' defined by String 'str',
 *           if such an entry is existing in 'seq'
 *        == NULL, otherwise
 */
extern	p_string  cmrlib_strtopstring(/* SEQsymb_entry seq, String str */);
extern	p_name	  cmrlib_strtopname(/* SEQsymb_entry seq, String str */);

/* return == a sequence collecting all symbol-entries of 'seq' of  
 *           symbol-type 'p_string' or 'p_name'
 */
extern	SEQsymb_entry	cmrlib_getallstrings(/* SEQsymb_entry seq */);
extern	SEQsymb_entry	cmrlib_getallnames(/* SEQsymb_entry seq */);
#endif		/* of MACRO */

/* SECTION 4.2: Fetching entries of definiton-table under diff. aspects */

/* return == definit. with index 'did', if such an entry is existing in 'seq'
 *        == NULL, else  (stored in component IDLclassCommon of def_entry)
 */
extern	def_entry	cmrlib_getdef(/* SEQdef_entry seq, DID did */);

#ifndef MACRO
/* return == a sequence collecting all terminals, nonterminals, others or
 *           productions of list 'seq' belonging to symbol defined by 'sid'.
 *           (An empty sequence shows, there were no such an entry.)
 */
extern	SEQdef_entry	cmrlib_sidtodefs(/* SEQdef_entry seq, SID sid */);
extern	SEQdef_entry	cmrlib_sidtoterms(/* SEQdef_entry seq, SID sid */);
extern	SEQdef_entry	cmrlib_sidtonterms(/* SEQdef_entry seq, SID sid */);
extern	SEQdef_entry	cmrlib_sidtoothers(/* SEQdef_entry seq, SID sid */);
extern	SEQdef_entry	cmrlib_sidtoprods(/* SEQdef_entry seq, SID sid */);

/* return == a sequence collecting all terminals, nonterminals, others 
 *           or productions of list 'seq'.
 */
extern	SEQdef_entry	cmrlib_getallterms(/* SEQdef_entry seq */);
extern	SEQdef_entry	cmrlib_getallnterms(/* SEQdef_entry seq */);
extern	SEQdef_entry	cmrlib_getallothers(/* SEQdef_entry seq */);
extern	SEQdef_entry	cmrlib_getallprods(/* SEQdef_entry seq */);
#endif		/* of MACRO */

/* return == a sequence collecting all productions of 'seq' with an object
 *           defined by 'lhs' (normally a nonterminal) at the left side of
 *	     the rule
 */
extern	SEQdef_entry cmrlib_getprodswithlhs(/*SEQdef_entry seq,DID lhsdid*/);


/* SECTION 4.3: Fetching properties out of property-list */

/* return == a sequence collecting all properties of property-list 'p_seq'
 *           with name defined by 'sid' (there are at most two such 
 *	     properties - one of type 'p_prop' and one 'p_prop_val'. 
 *	     An empty sequence shows, there were no such property.)
 */
extern	SEQprop_entry cmrlib_sidtoallprops(/*SEQprop_entry p_seq,SID sid*/);

#ifndef MACRO
/* return == the property 'p_prop' or 'p_prop_val' in list 'p_seq', which 
 *           is defined by 'sid' , if such a property is existing
 *        == NULL, otherwise
 */
extern	p_prop		cmrlib_sidtoprop(/*SEQprop_entry p_seq, SID sid*/);
extern	p_prop_val	cmrlib_sidtopropval(/*SEQprop_entry p_seq,SID sid*/);

/* return == a sequence collecting all properties of list 'p_seq' of 
 *           type 'p_prop' or 'p_prop_val'.
 */
extern	SEQprop_entry	cmrlib_getallprops(/* SEQprop_entry p_seq */);
extern	SEQprop_entry	cmrlib_getallpropvals(/* SEQprop_entry p_seq */);
#endif		/* of MACRO */



/* SECTION 5: Further list operations analogous to those of "comar.h"*/

#ifndef MACRO
/* All functions of "cmrlib" returning a sequence contain the elements
 * in a reverse order to that in the lists of the COMAR-structure.
 * Normally this fact should not be important, otherwise one can use
 * the following functions to get the "right" order.
 * return == reverse of sequence 'seq'
 */
extern SEQsymb_entry	reverseSEQsymb_entry(/* SEQsymb_entry seq */);
extern SEQdef_entry	reverseSEQdef_entry(/* SEQdef_entry seq */);
extern SEQprop_entry	reverseSEQprop_entry(/* SEQprop_entry seq */);
extern SEQunit		reverseSEQunit(/* SEQunit seq */);
extern SEQvalue		reverseSEQvalue(/* SEQvalue seq */);
#endif		/* of MACRO */

/* Return of the following five functions is always the 'NULL-element':
 * a NULL stored in component IDLclassCommon of the union-result-type.
 */
extern symb_entry	NULsymb_entry();
extern def_entry	NULdef_entry();
extern prop_entry	NULprop_entry();
extern unit		NULunit();
extern value		NULvalue();

/* The following five macros can be used as a function returning the first
 * element of a sequence. Applied to an empty sequence yields a NULL stored
 * in component IDLclassCommon of the union. Don't use with macro 'typeof()'.
 */
#define headSEQsymb_entry(seq)	( (seq) ? (seq)->value : NULsymb_entry() )
#define headSEQdef_entry(seq)	( (seq) ? (seq)->value : NULdef_entry() )
#define headSEQprop_entry(seq)	( (seq) ? (seq)->value : NULprop_entry() )
#define headSEQunit(seq)	( (seq) ? (seq)->value : NULunit() )
#define headSEQvalue(seq)	( (seq) ? (seq)->value : NULvalue() )



/* SECTION 6: Computing general datas of COMAR-structure */

/* return == greatest sid of an entry in 'seq' */
extern	SID	cmrlib_getmaxsid(/* SEQsymb_entry seq */);
/* return == greatest did of an entry in 'seq' */
extern	DID	cmrlib_getmaxdid(/* SEQdef_entry seq */);

/* return == TRUE  <==> prod is a BNF-production */
extern	Boolean	cmrlib_isbnfprod(/* p_prod prod */);


/* SECTION 7 : Global variables and their functions for faster accesses
 *	       to the COMAR-structure
 */


/* Use the following variables after using cmrlib_arrangedefs() once before.
 * Think of that the elements of the above lists are not(!) copies, so that
 * you can make use of them to manipulate the entries of 'CMR'. */
extern	SEQdef_entry	TERM_SEQ;   /* global variable for all terminals   */
extern	SEQdef_entry	NTERM_SEQ;  /* global variable for all nonterminals*/
extern	SEQdef_entry	OTHER_SEQ;  /* global variable for all others      */
extern	SEQdef_entry	PROD_SEQ;   /* global variable for all productions */

/* initializing of the global variables TERM_SEQ, ... , PROD_SEQ, result:
 *	 TERM_SEQ == all terminals of the COMAR-structure 'CMR'
 *	NTERM_SEQ == all nonterminals of the COMAR-structure 'CMR'
 *	OTHER_SEQ == all others of the COMAR-structure 'CMR'
 *	 PROD_SEQ == all productions of the COMAR-structure 'CMR'
 */
extern	void	cmrlib_arrangedefs();



/* The following type-, variable- and function-defintions enable you to make
 * fast accesses to definition-table-entries of 'CMR' (in constant time).
 */

/* typedefinitions of dynamic arrays */
typedef def_entry	*ARRdef_entry;
typedef SEQdef_entry	*ARRSEQdef_entry;
typedef unsigned short	Indextype;
typedef Indextype	*ARRIndextype;

  /* MAXNTERM == The number of nonterminals in 'CMR'.
   * MAXTERM  == The number of terminals in 'CMR'.
   * MAXPROD  == The number of productions in 'CMR'.
   * MAXOTHER == The number of 'Other'-objects in 'CMR'.
   */
extern	Indextype	MAXNTERM;
extern	Indextype	MAXTERM;
extern	Indextype	MAXPROD;
extern	Indextype	MAXOTHER;


   /*  MAXDID == The greatest did of a def_entry in 'CMR'. MAXDID+1 will
   * 		 be the number of elements of arrays 'DEFTBL' and 'INDEX'.
   */
extern	DID		MAXDID;


/* INDEX can be used as a new coding of terminals, nonterminals, productions
 * and others. One has to differ four cases to describe the value of INDEX[i]:
 * let i (i=1,...,MAXDID) be a DID of a
 *    a) nonterminal <==> INDEX[i] == signific. value between 0 and MAXNTERM-1
 *    b) terminal    <==> INDEX[i] == signific. value between 0 and MAXTERM-1
 *    c) production  <==> INDEX[i] == signific. value between 0 and MAXPROD-1
 *    d) other-object<==> INDEX[i] == signific. value between 0 and MAXOTHER-1
 * INDEX restricted to one of the four groups (terminals,...) is bijective in
 * each case. For a typical use see PRODWITHLHS: using INDEX[i] instead of i
 * as index makes PRODWITHLHS really smaller (normally: MAXNTERM << MAXDID).
 */
extern	ARRIndextype	INDEX;

  /* Let i be a DID of a nonterminal and j = INDEX[i] (j will be always
   * between NULL and MAXNTERM-1: index-bounds of PRODWITHLHS). Then is:
   *
   * PRODWITHLHS[j] == sequence of all productions with lhsdid is i.
   */
extern	ARRSEQdef_entry	PRODWITHLHS;

  /* DEFTBL[i]: def_entry with did i, if an entry with did i exists
   *            NULL (stored in component IDLclassCommon), else
   * Note: DEFTBL[i] is only defined, if 0 < i <= MAXDID
   */
extern	ARRdef_entry	DEFTBL;


/* Computes the above declared variables:
 * MAX..., INDEX[1..MAXDID], PRODWITHLHS[1..MAXNTERM] and DEFTBL[1..MAXDID]
 */
void	cmrlib_compute_globarrs();

/* (tag == Kp_term)  => return == inverse function of INDEX for terminals
 * (tag == Kp_nterm) => return == inverse function of INDEX for nonterminals
 * (tag == Kp_prod)  => return == inverse function of INDEX for productions
 * (tag == Kp_other) => return == inverse function of INDEX for other-objects
 *
 * The result is an array with ( INDEX[i] == j  <==>  result[j] == i )
 * NOTE: the execution of cmrlib_compute_globarrs() and cmrlib_arrangedefs()
 *       before is a necessary condition.
 */
DID	*cmrlib_INDEX_Invers(/* short tag */);


#endif		/* of cmrlib_DEF */

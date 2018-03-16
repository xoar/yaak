/*
** $Id: cmrlib.c,v 1.8 1997/08/29 08:38:08 mjung Exp $
*/
static char rcs_id[]= "$Id: cmrlib.c,v 1.8 1997/08/29 08:38:08 mjung Exp $";

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
/* File: cmrlib.c	First Edit: 10.10.88	  Last Edit: 10.03.89      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/*									   */
/* Last Change: 10.05.89	From: Karl-Josef Prott			   */
/***************************************************************************/

/* Here You finde the implementation of the functions declared in "cmrlib.h".
 * Don't confuse, if You are missing some functions declared in the header-
 * file. You should use all functions as described in the header-file and
 * not think about incomprehensibility You will find here. To reduce code
 * several nearly identical functions are implemented by one making use of
 * file "cmrinternal.h".
 *
 * Table of Contents:
 *	SECTION 1: auxiliary function for use of global variable 'CMR'
 * 	SECTION 2: Creating and initializing new COMAR components
 * 	SECTION 3: Deleting COMAR lists and components
 * 	SECTION 4: Fetching COMAR attributes of COMAR components
 * 	  SECT. 4.1: Fetching entries of symbol-table
 * 	  SECT. 4.2: Fetching entries of definiton-table
 * 	  SECT. 4.3: Fetching properties out of property-list
 *	SECTION 5 : Further list operations analogous to those of "comar.h"
 *	SECTION 6 : Computing general datas of COMAR-structure
 *	SECTION 7 : Global variables and their functions for faster accesses
 *		    to the COMAR-structure
 */

#include <string.h>
#include <stdio.h>
/*   #include <sys/dir.h>  definition of MAXNAMLEN */
#define  MAXNAMLEN 255

#include "comar.h"
#include "comar_func.h"
#include "cmrlib.h"

#define strequal(a,b)  (!(strcmp(a,b)))

#define INT_TAG_ERR(str,tg) (void)fprintf(stderr,\
		"Internal error in %s: wrong tag: %d\n",\
		str, tg)
#define UL_TAG_ERR(str,tg) (void)fprintf(stderr,\
		"Internal error in %s: wrong tag: %lu\n",\
		str, tg)

#define INT_ALLOC_ERR(str)	(void)fprintf(stderr,\
		"Fatal error in %s: no allocation possible!\n", str)


/* SECTION 1: auxiliary function for use of global variable 'CMR' */

p_comar	CMR =(p_comar)NULL;

/* This function sets global variable 'CMR' to 'comarvar' and returns
 * the old value of 'CMR'. All functions declared in "cmrlib.h" use
 * 'CMR' as the default COMAR-variable. So you must set 'CMR' to the
 * right COMAR-data-structure before using them. You should also use
 * 'CMR' to avoid often use of this function.
 * return == the old value of 'CMR'
 */
p_comar	cmrlib_changeglobalcmrvar(comarvar)
p_comar	comarvar;
{
  p_comar help;

  help = CMR;
  CMR = comarvar;
  return(help);
}



/* SECTION 2. Creating and initializing new COMAR components. */


/* Return == new empty COMAR structure (initialized for pre-defined symbols).
 * Think of saving variable 'CMR' when using several COMAR-structures, because
 * CMR will be set by this function.
 * (see function 'cmrlib_changeglobalcmrvar()').
 */
p_comar cmrlib_newstructure()
{
  p_comar      c ;

  c = Np_comar;
  initializeSEQsymb_entry(c->symbols);
  initializeSEQdef_entry(c->definitions);

  (void)cmrlib_changeglobalcmrvar(c);
  /* initialize symbol part with pre-defined symbols */
  (void)cmrlib_newname("#");
  (void)cmrlib_newstring("");
  return(c);
}		/* cmrlib_newstructure */



/* Insert new symbol into set of symb_entry's. Repeat call with same symbol
 * is ignored. A symb_entry can be neither deleted nor modified.
 * return == the new ( or already present ) symb_entry
 */
CPsymb_entry cmrlib_symnewxy(tag,str)
int tag;
String str;
{
  SID             sid ;
  SEQsymb_entry travel;
  symb_entry     symb ;

  sid = 1;
  foreachinSEQsymb_entry(CMR->symbols,travel,symb)
  {
    if ( typeof(symb) == tag   &&  strequal(symb.IDLclassCommon->str, str) )
      return(symb.IDLclassCommon);
    if ( emptySEQsymb_entry(tailSEQsymb_entry(travel)) )
      {
	sid = symb.IDLclassCommon->sid + 1;
	break;
      }
  }

  if ( tag == Kp_string )
    symb.Vp_string = Np_string;
  else symb.Vp_name = Np_name;
  symb = Mksymb_entry(sid, str, symb);
  if ( sid == 1 )
    appendrearSEQsymb_entry(CMR->symbols, symb);
  else
    appendrearSEQsymb_entry(travel, symb);

  return(symb.IDLclassCommon);
}		/* cmrlib_symnewxy */



/*  Insert new term, nterm, or other into list of def_entry's. Repeat call
 *  with same SID results in a second entry. So double entries are possible!
 *  return == the new def_entry with an empty property-list.
 *         == NULL, if internal error occured.
 */
CPdef_entry  cmrlib_defnewxy(tag,sid)
int	tag;
SID     sid;
{
  SEQdef_entry	travel;
  def_entry	def;
  DID		did;

  did = 1;
  foreachinSEQdef_entry(CMR->definitions,travel,def)
  {
    if ( emptySEQdef_entry(tailSEQdef_entry(travel)) )
      {
	did = def.IDLclassCommon->did + 1;
	break;
      }
  }

  switch(tag)
    {
      case Kp_term : def.Vp_term = Mkp_term(); break;
      case Kp_nterm: def.Vp_nterm = Mkp_nterm(); break;
      case Kp_other: def.Vp_other = Mkp_other(); break;
      default      : ;
#ifdef DEBUG_LIB
		     INT_TAG_ERR("cmrlib_newdef",tag);
#endif
		     return(NULL);
    }
  def = Mkdef_entry(did,sid,(SEQprop_entry)NULL,def);
  if ( did == 1 )
    appendrearSEQdef_entry(CMR->definitions, def);
  else
    appendrearSEQdef_entry(travel, def);

  return(def.IDLclassCommon);
}		/* cmrlib_defnewxy */


/*  Insert new production into list of def_entry's. Repeat call with same
 *  SID results in a second entry. So double entries are possible!
 *  return == the new def_entry of type p_prod with an empty property-list.
 *         == NULL, if internal error occured.
 */
p_prod cmrlib_newprod(sid,lhs,rhs)
SID     sid;
DID	lhs;
SEQunit	rhs;
{
  SEQdef_entry	travel;
  def_entry	def;
  DID		did;

  did = 1;
  foreachinSEQdef_entry(CMR->definitions,travel,def)
  {
    if ( emptySEQdef_entry(tailSEQdef_entry(travel)) )
      {
	did = def.IDLclassCommon->did + 1;
	break;
      }
  }

  def.Vp_prod = Mkp_prod(lhs, rhs);
  def = Mkdef_entry(did, sid, (SEQprop_entry)NULL, def);
  if ( did == 1 )
    appendrearSEQdef_entry(CMR->definitions, def);
  else
    appendrearSEQdef_entry(travel, def);

  return(def.Vp_prod);
}		/* cmrlib_newprod */


/* This global variable is needed for the macro cmrlib_newprop() invoking
 * cmrlib_propnewxy() with a dummy value. The value of DUMMYvalue may be
 * undefined, because it's never used in such cases.
 */
value	DUMMYvalue;


/*  Insert new property identified by 'sid' and 'tag' into list of
 *  properties of def_entry 'def'.
 *  return == the new or already present prop_entry identified
	      by 'sid' and 'tag'.
 */
CPprop_entry     cmrlib_propnewxy(tag,def,sid,val)
int		tag;
def_entry	def;
SID		sid;
value		val;
{
  SEQprop_entry	travel;
  prop_entry	prop;

  foreachinSEQprop_entry(def.IDLclassCommon->prop, travel, prop)
    {
      if ( prop.IDLclassCommon->sid == sid  &&  typeof(prop) == tag )
	return(prop.IDLclassCommon);
    }
  /* a property of type 'tag' with name identified by 'sid' doesn't exist. */

  if ( tag == Kp_prop )
    prop.Vp_prop = Mkp_prop();
  else		/* tag == Kp_prop_val */
    prop.Vp_prop_val = Mkp_prop_val(val);
  prop = Mkprop_entry(def.IDLclassCommon->did, sid, prop);
  appendfrontSEQprop_entry(def.IDLclassCommon->prop, prop);

  return(prop.IDLclassCommon);
}		/* cmrlib_propnewxy */


char buffer[MAXNAMLEN]; /* for use in the following two functions */

/* Geneating new NonTerminal beginning with String 'prefix', inserting
 * in symbol-table and definition-table.
 *  return == the new def_entry of type 'p_nterm' with an empty property-list.
 *         == NULL, if internal error occured.
 */
p_nterm cmrlib_genNTerm(prefix)
String	prefix;
{
  static int number = 0;
  char *str;
  p_name symb;

  do
    {
      (void)sprintf(buffer, "%s%d", prefix, ++number);
    }
  while ( cmrlib_strtopname(CMR->symbols, buffer) != NULL );

  str = malloc( (unsigned)((strlen(buffer)+1) * sizeof(char)) );
  symb = cmrlib_newname(strcpy(str,buffer));
  return( cmrlib_newnterm(symb->sid) );
}		/* cmrlib_genNTerm */


/* Geneating new Terminal beginning with String 'prefix', inserting
 * in symbol-table and definition-table.
 *  return == the new def_entry of type 'p_term' with an empty property-list.
 *         == NULL, if internal error occured.
 */
p_term cmrlib_genTerm(prefix)
String	prefix;
{
  static int number = 0;
  char *str;
  p_string symb;

  do
    {
      (void)sprintf(buffer, "%s%d", prefix, ++number);
    }
  while ( cmrlib_strtopstring(CMR->symbols, buffer) != NULL );

  str = malloc( (unsigned)((strlen(buffer)+1) * sizeof(char)) );
  symb = cmrlib_newstring(strcpy(str,buffer));
  return( cmrlib_newterm(symb->sid) );
}		/* cmrlib_genTerm */


/* Geneating new Other-object beginning with String 'prefix', inserting
 * in symbol-table and definition-table.
 *  return == the new def_entry of type 'p_other' with an empty propertylist.
 *         == NULL, if internal error occured.
 */
p_other cmrlib_genOther(prefix)
String	prefix;
{
  static int number = 0;
  char *str;
  p_string symb;

  do
    {
      (void)sprintf(buffer, "%s%d", prefix, ++number);
    }
  while ( cmrlib_strtopstring(CMR->symbols, buffer) != NULL );

  str = malloc( (unsigned)((strlen(buffer)+1) * sizeof(char)) );
  symb = cmrlib_newstring(strcpy(str,buffer));
  return( cmrlib_newother(symb->sid) );
}		/* cmrlib_genOther */



/* SECTION 3 : Deleting COMAR lists and components. */

/* Deletes def_entry out of list, but doesn't free their storage.
 * return == deleted def_entry, if one was found with index 'did'
 * return == NULL, otherwise (stored in component IDLclassCommon of def_entry)
 */
def_entry	cmrlib_deldefentry(seq, did)
SEQdef_entry	*seq;
DID	did;
{
  SEQdef_entry	* link;
  def_entry	def;

  for (link = seq; *link != NULL; link = &(*link)->next)
    {
      retrievefirstSEQdef_entry(*link, def);
      if (def.IDLclassCommon->did == did)
	{
	  removefirstSEQdef_entry(*link);
	  return(def);
	}
    }

  def.IDLclassCommon = NULL;
  return(def);
}		/* cmrlib_deldefentry */


/* Deletes property out of list, but doesn't free their storage.
 * return == deleted property, if one was found with name 'sid' of type 'tag'
 * return == NULL,  else ( = such an element not found )
 */
CPprop_entry	cmrlib_propdelxy(tag, def, sid)
int		tag;
def_entry	def;
SID		sid;
{
  SEQprop_entry	* link;
  prop_entry	prop;

  if ( def.IDLclassCommon != NULL )
    for(link = &def.IDLclassCommon->prop;*link != NULL;link = &(*link)->next)
    {
      retrievefirstSEQprop_entry(*link, prop);
      if( prop.IDLclassCommon->sid == sid && typeof(prop) == tag )
	{
	  removefirstSEQprop_entry(*link);
	  return(prop.IDLclassCommon);
	}
    }

  return(NULL);
}		/* cmrlib_propdelxy */


/* Traverse through all components, subtrees and sublists
 * and frees their storage.
 * return == CMR_SUCCESS, if no error occured
 * return == CMR_NOSUC, else
 */
ERR	cmrlib_rekdeldef(def)
def_entry def;
{
  ERR	stat;

  if ( def.IDLclassCommon == NULL )
    return(CMR_SUCCESS);

  stat = cmrlib_rekdelSEQprop_entry(def.IDLclassCommon->prop);
  switch ( typeof(def) )
    {
      case Kp_term	: Dp_term(def.Vp_term);		break;
      case Kp_nterm	: Dp_nterm(def.Vp_nterm);	break;
      case Kp_other	: Dp_other(def.Vp_other);	break;
      case Kp_prod	: stat = cmrlib_rekdelSEQunit(def.Vp_prod->rhs);
			  Dp_prod(def.Vp_prod);
			  break;
      default		: ;
#ifdef DEBUG_LIB
			  INT_TAG_ERR("cmrlib_rekdeldef", typeof(def));
#endif
			  return(CMR_NOSUC);
    }
  return(stat);
}		/* of cmrlib_rekdeldef */

/* Traverse through all components, subtrees and sublists
 * and frees their storage.
 * return == CMR_SUCCESS, if no error occured
 * return == CMR_NOSUC, else
 */
ERR	cmrlib_rekdelunit(un)
unit	un;
{
  ERR	stat;

  if ( un.IDLclassCommon == NULL )
    return(CMR_SUCCESS);

  switch ( typeof(un) )
    {
      case Kp_elunit	: Dp_elunit(un.Vp_elunit);
			  break;
      case Kp_alt	: stat = cmrlib_rekdelSEQunit(un.Vp_alt->rhs1);
			  stat = cmrlib_rekdelSEQunit(un.Vp_alt->rhs2);
			  Dp_alt(un.Vp_alt);
			  break;
      case Kp_opt	: stat = cmrlib_rekdelSEQunit(un.Vp_opt->rhs);
			  Dp_opt(un.Vp_opt);
			  break;
      case Kp_plus	: stat = cmrlib_rekdelSEQunit(un.Vp_plus->rhs);
			  Dp_plus(un.Vp_plus);
			  break;
      case Kp_star	: stat = cmrlib_rekdelSEQunit(un.Vp_star->rhs);
			  Dp_star(un.Vp_star);
			  break;
      case Kp_delrep	: stat = cmrlib_rekdelSEQunit(un.Vp_delrep->rhs);
			  stat = cmrlib_rekdelSEQunit(un.Vp_delrep->sep);
			  Dp_delrep(un.Vp_delrep);
			  break;
      default		: ;
#ifdef DEBUG_LIB
			  INT_TAG_ERR("cmrlib_rekdelunit", typeof(un));
#endif
			  return(CMR_NOSUC);
    }

  return(stat);
}		/* cmrlib_rekdelunit */

/* Traverse through all components, subtrees and sublists
 * and frees their storage.
 * return == CMR_SUCCESS, if no error occured
 * return == CMR_NOSUC, else
 */
ERR	cmrlib_rekdelprop(prop)
prop_entry	prop;
{
  ERR	stat;

  if ( prop.IDLclassCommon == NULL )
    return(CMR_SUCCESS);

  switch ( typeof(prop) )
    {
      case Kp_prop	: Dp_prop(prop.Vp_prop);	break;
      case Kp_prop_val	: stat = cmrlib_rekdelval(prop.Vp_prop_val->val);
			  Dp_prop_val(prop.Vp_prop_val);
			  break;
      default		: ;
#ifdef DEBUG_LIB
			  INT_TAG_ERR("cmrlib_rekdelprop", typeof(prop));
#endif
			  return(CMR_NOSUC);
    }

  return(stat);

}		/* cmrlib_rekdelprop */

/* Traverse through all components, subtrees and sublists
 * and frees their storage.
 * return == CMR_SUCCESS, if no error occured
 * return == CMR_NOSUC, else
 */
ERR	cmrlib_rekdelval(val)
value	val;
{
  ERR	stat;

  if ( val.IDLclassCommon == NULL )
    return(CMR_SUCCESS);

  switch ( typeof(val) )
    {
      case Kp_sval	: Dp_sval(val.Vp_sval); 	break;
      case Kp_nval	: Dp_nval(val.Vp_nval); 	break;
      case Kp_dval	: Dp_dval(val.Vp_dval); 	break;
      case Kp_lval	: stat = cmrlib_rekdelSEQvalue(val.Vp_lval->list);
			  Dp_lval(val.Vp_lval);
			  break;
      default		: ;
#ifdef DEBUG_LIB
			  INT_TAG_ERR("cmrlib_rekdelval", typeof(val));
#endif
			  return(CMR_NOSUC);
    }

  return(stat);

}		/* cmrlib_rekdelval */


/* Traverse through all elements and their components, subtrees and sublists
 * and frees their storage.
 * return == CMR_SUCCESS, if no error occured
 * return == CMR_NOSUC, else
 */
ERR	cmrlib_rekdelSEQdef_entry(d_seq)
SEQdef_entry	d_seq;
{
  ERR	stat = CMR_SUCCESS;
  def_entry	def;

  while ( !emptySEQdef_entry(d_seq) )
    {
      retrievefirstSEQdef_entry(d_seq, def);
      removefirstSEQdef_entry(d_seq);
      switch ( typeof(def) )
        {
          case Kp_term	: Dp_term(def.Vp_term);		break;
          case Kp_nterm	: Dp_nterm(def.Vp_nterm);	break;
          case Kp_other	: Dp_other(def.Vp_other);	break;
          case Kp_prod	: stat = cmrlib_rekdelSEQunit(def.Vp_prod->rhs);
			  Dp_prod(def.Vp_prod);
			  break;
          default	: ;
#ifdef DEBUG_LIB
			  INT_TAG_ERR("cmrlib_rekdelSEQdef_entry", typeof(def));
#endif
			  return(CMR_NOSUC);
        }
    }

  return(stat);
}		/* cmrlib_rekdelSEQdef_entry() */

/* Traverse through all elements and their components, subtrees and sublists
 * and frees their storage.
 * return == CMR_SUCCESS, if no error occured
 * return == CMR_NOSUC, else
 */
ERR	cmrlib_rekdelSEQunit(u_seq)
SEQunit	u_seq;
{
  ERR	stat = CMR_SUCCESS;
  unit un;

  while ( !emptySEQunit(u_seq) )
    {
      retrievefirstSEQunit(u_seq, un);
      removefirstSEQunit(u_seq);
      switch ( typeof(un) )
        {
          case Kp_elunit: Dp_elunit(un.Vp_elunit);
			  break;
          case Kp_alt	: stat = cmrlib_rekdelSEQunit(un.Vp_alt->rhs1);
			  stat = cmrlib_rekdelSEQunit(un.Vp_alt->rhs2);
		 	  Dp_alt(un.Vp_alt);
		 	  break;
          case Kp_opt	: stat = cmrlib_rekdelSEQunit(un.Vp_opt->rhs);
		  	  Dp_opt(un.Vp_opt);
			  break;
          case Kp_plus	: stat = cmrlib_rekdelSEQunit(un.Vp_plus->rhs);
			  Dp_plus(un.Vp_plus);
			  break;
          case Kp_star	: stat = cmrlib_rekdelSEQunit(un.Vp_star->rhs);
			  Dp_star(un.Vp_star);
			  break;
          case Kp_delrep: stat = cmrlib_rekdelSEQunit(un.Vp_delrep->rhs);
			  stat = cmrlib_rekdelSEQunit(un.Vp_delrep->sep);
			  Dp_delrep(un.Vp_delrep);
			  break;
          default	: ;
#ifdef DEBUG_LIB
			  INT_TAG_ERR("cmrlib_rekdelSEQunit", typeof(un));
#endif
			  return(CMR_NOSUC);
        }
    }

  return(stat);

}		/* cmrlib_rekdelSEQunit */

/* Traverse through all elements and their components, subtrees and sublists
 * and frees their storage.
 * return == CMR_SUCCESS, if no error occured
 * return == CMR_NOSUC, else
 */
ERR	cmrlib_rekdelSEQprop_entry(p_seq)
SEQprop_entry	p_seq;
{
  ERR	stat = CMR_SUCCESS;
  prop_entry	prop;

  while ( !emptySEQprop_entry(p_seq) )
    {
      retrievefirstSEQprop_entry(p_seq, prop);
      removefirstSEQprop_entry(p_seq);
      switch ( typeof(prop) )
        {
          case Kp_prop	: Dp_prop(prop.Vp_prop);	break;
          case Kp_prop_val: stat = cmrlib_rekdelval(prop.Vp_prop_val->val);
			  Dp_prop_val(prop.Vp_prop_val);
			  break;
          default	: ;
#ifdef DEBUG_LIB
		INT_TAG_ERR("cmrlib_rekdelSEQprop_entry", typeof(prop));
#endif
			  return(CMR_NOSUC);
        }
    }

  return(stat);
}		/* cmrlib_rekdelSEQprop_entry() */

/* Traverse through all elements and their components, subtrees and sublists
 * and frees their storage.
 * return == CMR_SUCCESS, if no error occured
 * return == CMR_NOSUC, else
 */
ERR	cmrlib_rekdelSEQvalue(v_seq)
SEQvalue	v_seq;
{
  ERR	stat = CMR_SUCCESS;
  value	val;

  while ( !emptySEQvalue(v_seq) )
    {
      retrievefirstSEQvalue(v_seq, val);
      removefirstSEQvalue(v_seq);
      switch ( typeof(val) )
        {
           case Kp_sval	: Dp_sval(val.Vp_sval); 	break;
           case Kp_nval	: Dp_nval(val.Vp_nval); 	break;
           case Kp_dval	: Dp_dval(val.Vp_dval); 	break;
           case Kp_lval	: stat = cmrlib_rekdelSEQvalue(val.Vp_lval->list);
			  Dp_lval(val.Vp_lval);
			  break;
           default	: ;
#ifdef DEBUG_LIB
			  INT_TAG_ERR("cmrlib_rekdelSEQvalue", typeof(val));
#endif
			  return(CMR_NOSUC);
        }
    }

  return(stat);
}		/* cmrlib_rekdelSEQvalue */



/* SECTION 4 : Fetching COMAR attributes of COMAR components. */

/* SECTION 4.1: Fetching entries of symbol-table under different aspects */

/* return == the symbol with index 'sid', if such an entry is existing
 *        == NULL, else  (stored in component IDLclassCommon of symb_entry)
 */
symb_entry cmrlib_getsymb(seq, sid)
SEQsymb_entry	seq;
SID		sid;
{
  SEQsymb_entry	travel;
  symb_entry	symb;

  foreachinSEQsymb_entry(seq, travel, symb)
    {
      if ( symb.IDLclassCommon->sid == sid )
	return(symb);
    }

  symb.IDLclassCommon = NULL;
  return(symb);
}		/* cmrlib_getsymb */

/* return == a sequence collecting all symbols with a string 'str' (there
 *	     are at most two such symbols - one of type 'p_name' and one
 *	     'p_string'. An empty sequence shows, there were no such entry)
 */
SEQsymb_entry	cmrlib_strtosymbs(seq, str)
SEQsymb_entry	seq;
String	str;
{
  SEQsymb_entry	travel,	result = NULL;
  symb_entry	symb;


  foreachinSEQsymb_entry(seq, travel, symb)
    {
      if( strequal(symb.IDLclassCommon->str, str) )
	if ( result == NULL )
	  appendfrontSEQsymb_entry(result, symb);
	else
	  {
	    appendfrontSEQsymb_entry(result, symb);
	    return(result);
	  }
      else;
    }

  return(result);
}		/* cmrlib_strtosymbs */

/* return == symbol defined by string 'str' and symbol-type 'tag', if such
 *           an entry is existing
 *        == NULL, otherwise
 */
CPsymb_entry	cmrlib_symstrtoxy(seq,tag,str)
SEQsymb_entry	seq;
int	tag;
String	str;
{
  SEQsymb_entry	travel;
  symb_entry	symb;


  foreachinSEQsymb_entry(seq, travel, symb)
    {
      if ( (typeof(symb) == tag) &&
	   strequal(symb.IDLclassCommon->str, str)
         )
	  return(symb.IDLclassCommon);
    }

  return(NULL);
}		/* cmrlib_strtoxy */

/* return == a sequence collecting all symbol-entries of symbol-type 'tag'
 */
SEQsymb_entry	cmrlib_symgetallxys(seq, tag)
SEQsymb_entry	seq;
int	tag;
{
  SEQsymb_entry	result = NULL;
  SEQsymb_entry	travel;
  symb_entry	symb;

  foreachinSEQsymb_entry(seq, travel, symb)
    {
      if ( typeof(symb) == tag )
	appendfrontSEQsymb_entry(result, symb);
    }

  return(result);
}		/* cmrlib_symgetallxys */



/* SECTION 4.2: Fetching entries of definiton-table under diff. aspects */

/* return == the definition with index 'did', if such an entry is existing
 *        == NULL, else  (stored in component IDLclassCommon of def_entry)
 */
def_entry	cmrlib_getdef(seq, did)
SEQdef_entry	seq;
DID		did;
{
  SEQdef_entry	travel;
  def_entry	def;

  foreachinSEQdef_entry(seq, travel, def)
    {
      if ( def.IDLclassCommon->did == did )
	return(def);
    }

  def.IDLclassCommon = NULL;
  return(def);
}		/* cmrlib_getdef */


/* return == a sequence collecting all definition-entries of definition-type
 *           'tag' of list 'seq' belonging to symbol defined by 'sid'.
 *           (An empty sequence shows, there were no such entry.)
 */
SEQdef_entry	cmrlib_defsidtoxys(seq, tag, sid)
SEQdef_entry	seq;
int		tag;
SID		sid;
{
  SEQdef_entry	travel, result = NULL;
  def_entry	def;

  foreachinSEQdef_entry(seq, travel, def)
    {
      if ( def.IDLclassCommon->sid == sid )
	{
	  if ( typeof(def) == tag  ||  tag == Kp_all )
	    appendfrontSEQdef_entry(result, def);
	  else UL_TAG_ERR("cmrlib_defsidtoxys", typeof(def));
	}
    }
  return(result);
}		/* of cmrlib_defsidtoxys */


/* return == a sequence collecting all definition-entries of type 'tag'
 */
SEQdef_entry	cmrlib_defgetallxys(seq, tag)
SEQdef_entry	seq;
int		tag;
{
  SEQdef_entry	travel, result = NULL;
  def_entry	def;

  foreachinSEQdef_entry(seq, travel, def)
    {
      if ( typeof(def) == tag )
	appendfrontSEQdef_entry(result, def);
    }

  return(result);
}		/* of cmrlib_defgetallxys */


/* return == a sequence collecting all productions of 'seq' with an object
 *           defined by 'lhs' (normally a nonterminal) at the left side of
 *	     the rule
 */
SEQdef_entry	cmrlib_getprodswithlhs(seq, lhs)
SEQdef_entry	seq;
DID		lhs;
{
  SEQdef_entry	travel, result = NULL;
  def_entry	def;

  foreachinSEQdef_entry(seq, travel, def)
    {
      if ( typeof(def) == Kp_prod  &&  def.Vp_prod->lhsdid == lhs )
	appendfrontSEQdef_entry(result, def);
    }

  return(result);
}		/* of cmrlib_getprodswithlhs */



/* SECTION 4.3: Fetching properties out of property-list */


/* return == a sequence collecting all properties of property-list 'p_seq'
 *           with name defined by 'sid' (there are at most two such
 *	     properties - one of type 'p_prop' and one 'p_prop_val'.
 *	     An empty sequence shows, there were no such property.)
 */
SEQprop_entry	cmrlib_sidtoallprops(p_seq,sid)
SEQprop_entry	p_seq;
SID		sid;
{
  SEQprop_entry	travel, result = NULL;
  prop_entry	prop;

  foreachinSEQprop_entry(p_seq, travel, prop)
    {
      if ( prop.IDLclassCommon->sid == sid )
	appendfrontSEQprop_entry(result, prop);
    }
  return(result);
}		/* of cmrlib_sidtoallprops */


/* return == the property in list 'p_seq', which is defined by 'sid' and
 *           of property-type 'tag', if such a property is existing
 *        == NULL, otherwise
 */
CPprop_entry	cmrlib_propsidtoxys(p_seq,tag,sid)
SEQprop_entry	p_seq;
int		tag;
SID		sid;
{
  SEQprop_entry	travel;
  prop_entry	prop;

  foreachinSEQprop_entry(p_seq, travel, prop)
    {
      if ( prop.IDLclassCommon->sid == sid  &&  typeof(prop) == tag )
	return(prop.IDLclassCommon);
    }
  return(NULL);
}		/* of cmrlib_propsidtoxys */


/* return == a sequence collecting all properties of list 'p_seq' of
 *           property-type 'tag'
 */
SEQprop_entry	cmrlib_propgetallxys(p_seq,tag)
SEQprop_entry	p_seq;
int		tag;
{
  SEQprop_entry	travel, result = NULL;
  prop_entry	prop;

  foreachinSEQprop_entry(p_seq, travel, prop)
    {
      if ( typeof(prop) == tag )
	appendfrontSEQprop_entry(result, prop);
    }

  return(result);
}		/* of cmrlib_propgetallxys */


/* SECTION 5: Further list operations */

/* All functions of "cmrlib" returning a sequence contain the elements
 * in a reverse order to that in the lists of the COMAR-structure.
 * Normally this fact should not be important, otherwise one can use
 * the following functions to get the "right" order.
 */

pGenList	cmrlib_reversexy(seq)
pGenList	seq;
{
  pGenList	help, result = NULL;

  while ( seq != NULL )
    {
      help = seq;
      seq = seq->next;
      help->next = result;
      result = help;
    }

  return(result);
}		/* cmrlib_reversexy */

/* Return is always the NULL-element */
symb_entry	NULsymb_entry()
{
  symb_entry	s;
  s.IDLclassCommon = NULL;
  return(s);
}

def_entry	NULdef_entry()
{
  def_entry	d;
  d.IDLclassCommon = NULL;
  return(d);
}

prop_entry	NULprop_entry()
{
  prop_entry	p;
  p.IDLclassCommon = NULL;
  return(p);
}

unit	NULunit()
{
  unit	u;
  u.IDLclassCommon = NULL;
  return(u);
}

value	NULvalue()
{
  value	v;
  v.IDLclassCommon = NULL;
  return(v);
}


/* SECTION 6: Computing general datas of COMAR-structure */

/* return == greatest sid of an entry in 'seq' */
SID	cmrlib_getmaxsid(seq)
SEQsymb_entry	seq;
{
  SEQsymb_entry travel;
  symb_entry	symb;
  SID		maxsid = 0;

  foreachinSEQsymb_entry(seq, travel, symb)
    if ( (SID)symb.IDLclassCommon->sid > maxsid )
      maxsid = symb.IDLclassCommon->sid;
  return( maxsid );
}

/* return == greatest did of an entry in 'seq' */
DID	cmrlib_getmaxdid(seq)
SEQdef_entry	seq;
{
  SEQdef_entry travel;
  def_entry	def;
  SID		maxdid = 0;

  foreachinSEQdef_entry(seq, travel, def)
    if ( (SID)def.IDLclassCommon->did > maxdid )  /* eigentlich DID ?! */
      maxdid = def.IDLclassCommon->did;
  return( maxdid );
}


/* return == TRUE  <==> prod is a BNF-production */
Boolean	cmrlib_isbnfprod(prod)
p_prod	prod;
{
  SEQunit	travel;
  unit		un;

  foreachinSEQunit(prod->rhs, travel, un)
    if ( typeof(un) != Kp_elunit )
      return(FALSE);

  return(TRUE);

}		/* end of isbnfprod() */


/* SECTION 7 : Global variables and their functions for faster accesses
 *	       to the COMAR-structure
 */

/* Definition of the global variables declared in "cmrlib.h" */
SEQdef_entry	TERM_SEQ;   /* global variable for all terminals   */
SEQdef_entry	NTERM_SEQ;  /* global variable for all nonterminals*/
SEQdef_entry	OTHER_SEQ;  /* global variable for all others      */
SEQdef_entry	PROD_SEQ;   /* global variable for all productions */

/* initializing of the global variables TERM_SEQ, ... , PROD_SEQ, result:
 *	TERM_SEQ  == all terminals of the COMAR-structure 'CMR'

 *	NTERM_SEQ == all nonterminals of the COMAR-structure 'CMR'
 *	OTHER_SEQ == all others of the COMAR-structure 'CMR'
 *	PROD_SEQ  == all productions of the COMAR-structure 'CMR'
 */
void	cmrlib_arrangedefs()
{
  SEQdef_entry	travel;
  def_entry	def;

  while ( ! emptySEQdef_entry(TERM_SEQ) )
    removefirstSEQdef_entry(TERM_SEQ);
  while ( ! emptySEQdef_entry(NTERM_SEQ) )
    removefirstSEQdef_entry(NTERM_SEQ);
  while ( ! emptySEQdef_entry(OTHER_SEQ) )
    removefirstSEQdef_entry(OTHER_SEQ);
  while ( ! emptySEQdef_entry(PROD_SEQ) )
    removefirstSEQdef_entry(PROD_SEQ);

  foreachinSEQdef_entry(CMR->definitions, travel, def)
    switch ( typeof(def) )
      {
	case Kp_term	: appendfrontSEQdef_entry(TERM_SEQ, def);
			  break;
	case Kp_nterm	: appendfrontSEQdef_entry(NTERM_SEQ, def);
			  break;
	case Kp_other	: appendfrontSEQdef_entry(OTHER_SEQ, def);
			  break;
	case Kp_prod	: appendfrontSEQdef_entry(PROD_SEQ, def);
			  break;
#ifdef DEBUG_LIB
	default		: INT_TAG_ERR("cmrlib_arrangedefs", typeof(def));
#endif
      }
}		/* end of cmrlib_arrangedefs() */


/* Definition of the global variables declared in "cmrlib.h" */
Indextype	MAXNTERM;
Indextype	MAXTERM;
Indextype	MAXPROD;
Indextype	MAXOTHER;
DID		MAXDID;
ARRIndextype	INDEX = (ARRIndextype)NULL;
ARRSEQdef_entry	PRODWITHLHS = (ARRSEQdef_entry)NULL;
ARRdef_entry	DEFTBL = (ARRdef_entry)NULL;

/* Computes the above declared variables:
 * MAX..., INDEX[1..MAXDID], PRODWITHLHS[1..MAXNTERM] and DEFTBL[1..MAXDID]
 */
void	cmrlib_compute_globarrs()
{
  SEQdef_entry		travel;
  def_entry		def;
  DID			did;
  unsigned short	i, UNDEF;
  unsigned short	countnterm, countterm, countprod, countother;

  /* reset of old values */
  MAXNTERM = MAXTERM = MAXPROD = MAXOTHER = MAXDID = 0;
  if ( INDEX != (ARRIndextype)NULL )
  {
    free(INDEX);
    INDEX = (ARRIndextype)NULL;
  }
  if ( PRODWITHLHS != (ARRSEQdef_entry)NULL )
  {
    free(PRODWITHLHS);
    PRODWITHLHS = (ARRSEQdef_entry)NULL;
  }
  if ( DEFTBL != (ARRdef_entry)NULL )
  {
    free(DEFTBL);
    DEFTBL = (ARRdef_entry)NULL;
  }

  /* computing of MAXNTERM, ..., MAXDID */
  foreachinSEQdef_entry(CMR->definitions, travel, def)
    {
      switch ( typeof(def) )
	{
	  case Kp_nterm:  MAXNTERM++;
			  break;
	  case Kp_term :  MAXTERM++;
			  break;
	  case Kp_prod :  MAXPROD++;
			  break;
	  case Kp_other:  MAXOTHER++;
			  break;
#ifdef DEBUG_LIB
	  default: INT_TAG_ERR("cmrlib_compute_globarrs_1()",typeof(def));
#endif
	}
      if ( (DID) def.IDLclassCommon->did > MAXDID )
	MAXDID = def.IDLclassCommon->did;
    } /* end of for */

  /* Allocation of the global arrays */
  if ((INDEX = (ARRIndextype)malloc((unsigned)((MAXDID+1) * sizeof(Indextype))))
	 == NULL )
    {
      INT_ALLOC_ERR("cmrlib_compute_globarrs()");
      exit(1);
    }
  if ((PRODWITHLHS= (ARRSEQdef_entry)calloc(MAXNTERM,sizeof(SEQdef_entry)))
	 == NULL )
    {
      INT_ALLOC_ERR("cmrlib_compute_globarrs()");
      exit(1);
    }
  if ( (DEFTBL = (ARRdef_entry)calloc(MAXDID+1, sizeof(def_entry)))
	 == NULL )
    {
      INT_ALLOC_ERR("cmrlib_compute_globarrs()");
      exit(1);
    }

  /* Computing the global arrays */
  countnterm = countterm = countprod = countother = 0;
  UNDEF = MAXDID + 1;
  for (i=0; i<=MAXDID; i++)
    INDEX[i] = UNDEF;
  foreachinSEQdef_entry(CMR->definitions, travel, def)
  {
    did = def.IDLclassCommon->did;
    DEFTBL[did] = def;
    switch ( typeof(def) )
      {
	case Kp_nterm:	if ( INDEX[did] == UNDEF )
			  INDEX[did] = countnterm++;
			break;
	case Kp_prod:	INDEX[did] = countprod++;
			did = def.Vp_prod->lhsdid;
			if ( INDEX[did] == UNDEF )
			  INDEX[did] = countnterm++;
			appendfrontSEQdef_entry(PRODWITHLHS[INDEX[did]],def);
			break;
	case Kp_term:	INDEX[did] = countterm++;
			break;
	case Kp_other:	INDEX[did] = countother++;
			break;
#ifdef DEBUG_LIB
	default: INT_TAG_ERR("cmrlib_compute_globarrs_2()",typeof(def));
#endif
      }
  }
}		/* end of cmrlib_compute_globarrs() */


DID	*cmrlib_INDEX_Invers(tag)
short	tag;
{
  SEQdef_entry	travel;
  def_entry	def;
  short		no;
  DID		*result;

  switch ( tag )
    {
      case Kp_term  : no = MAXTERM;	travel = TERM_SEQ;	break;
      case Kp_nterm : no = MAXNTERM;	travel = NTERM_SEQ;	break;
      case Kp_prod  : no = MAXPROD;	travel = PROD_SEQ;	break;
      case Kp_other : no = MAXOTHER;	travel = OTHER_SEQ;	break;
      default	    : INT_TAG_ERR("cmrlib_INDEX_Invers()", tag);
	              no = 0;	        travel = NULL;		break;
    }  /* end of switch */

  if ( (result = (DID *)calloc( no, sizeof(DID) ))  ==  (DID *)NULL )
    {
      INT_ALLOC_ERR("cmrlib_INDEX_Invers()");
      exit(1);
    }

  foreachinSEQdef_entry(travel, travel, def)
    result[INDEX[def.IDLclassCommon->did]] = def.IDLclassCommon->did;

  return(result);

}  /* end of cmrlib_INDEX_Invers() */

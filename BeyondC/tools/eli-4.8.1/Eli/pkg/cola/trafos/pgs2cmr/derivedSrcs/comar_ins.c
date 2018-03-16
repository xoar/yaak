#include <string.h>
#include <stdio.h>

#include "comar.h"
#include "comarMacros.h"
#include "comar_func.h"
#include "name.h"

#include "cmrlib.h"

#include "deftbl.h"		/* definition of DefTableKey */
#include "pdl_gen.h"		/* definition of ResetDef(), ... */
#include "err.h"		/* definition of message(), ... */
#include "idn.h"
#include "MakeName.h"
#include "source.h"		/* definition of SRCFILE */
#include "termcode.h"		/* definition of NAME */
#include "csm.h"		/* definition of StringTable() */
#include "comar_ins.h"


#define	INTERNAL_ERR(no)	message(DEADLY, "Internal Error!", no , 0)


/*---------------------------------*/
/* SECTION 0: functions for output */
/*---------------------------------*/

void
#if defined (__cplusplus) || defined(__STDC__)
write_results(char *filename)
#else
write_results(filename)
char *filename;
#endif
{
  FILE *fp;

  if ((fp = fopen(filename,"w")) == NULL)
  {
    message(ERROR, "Write Error: output file can't be open!", 0 , 0);
    return;
  }
  OUTPUT(fp, CMR);
  fclose(fp);
  return;
}

/*------------------------------------------------*/
/* SECTION 1: functions for building symbol table */
/*------------------------------------------------*/

/* global variables for the COMAR symboltable indices of some properties
 * defined with ins_property_name() and used in ins_term_with_prop()
 * or ins_other_with_prop().
 */
static	SID	CODE_SID = 0, STOP_SID = 0, SEPA_SID = 0, START_SID = 0,
		BRACKET_SID = 0, SKIP_SID = 0, GRAMNAME_SID = 0,
		CONNECT_SID = 0, REDUCE_SID = 0, NOREDUCE_SID = 0;

SID
#if defined (__cplusplus) || defined(__STDC__)
	ins_property_name(proptype prop)
#else
	ins_property_name(prop)
	proptype	prop;
#endif
{
  p_string	str;

      switch ( prop )
      {
	/* Property names of terminals */
	case	P_CODE	 : if ( CODE_SID == 0 )
			     {
				str = cmrlib_newstring(CODE);
			   	CODE_SID = str->sid;
			     }
			   return(CODE_SID);
	case	P_STOP	 : if ( STOP_SID == 0 )
			     {
				str = cmrlib_newstring(STOP);
			   	STOP_SID = str->sid;
			     }
			   return(STOP_SID);
	case	P_SEPA	 : if ( SEPA_SID == 0 )
			     {
				str = cmrlib_newstring(SEPA);
			   	SEPA_SID = str->sid;
			     }
			   return(SEPA_SID);
	case	P_BRACKET: if ( BRACKET_SID == 0 )
			     {
				str = cmrlib_newstring(BRACKET);
			   	BRACKET_SID = str->sid;
			     }
			   return(BRACKET_SID);
	case	P_SKIP	 : if ( SKIP_SID == 0 )
			     {
				str = cmrlib_newstring(SKIP);
			   	SKIP_SID = str->sid;
			     }
			   return(SKIP_SID);

	/* Property names of other-objects */
	case P_CONNECT	: if ( CONNECT_SID == 0 )
			     {
				str = cmrlib_newstring(CONNECTION);
			  	CONNECT_SID = str->sid;
			     }
			  return(CONNECT_SID);
	case P_GRAMMAR	: if ( GRAMNAME_SID == 0 )
			     {
				str = cmrlib_newstring(GRAMNAME);
			  	GRAMNAME_SID = str->sid;
			     }
			  return(GRAMNAME_SID);
	case P_START	: if ( START_SID == 0 )
			     {
				str = cmrlib_newstring(START);
			  	START_SID = str->sid;
			     }
			  return(START_SID);
	case P_REDUCE	: if ( REDUCE_SID == 0 )
			     {
				str = cmrlib_newstring(REDUCE);
			  	REDUCE_SID = str->sid;
			     }
			  return(REDUCE_SID);
	case P_NOREDUCE	: if ( NOREDUCE_SID == 0 )
			     {
				str = cmrlib_newstring(NOREDUCE);
			  	NOREDUCE_SID = str->sid;
			     }
			  return(NOREDUCE_SID);
#ifdef	DEBUG
	default		: INTERNAL_ERR(1);
			  break;
#endif
      }  /* of switch */
  return(0);
}

int
#if defined (__cplusplus) || defined(__STDC__)
ins_eof(void)
#else
ins_eof()
#endif
{
  int	code = NAME,	ind = 0;

  mkidn(EOFSTRING, strlen(EOFSTRING), &code, &ind);
  return(ind);
}


SID
#if defined (__cplusplus) || defined(__STDC__)
	ins_symbol(String str, int class)

#else
	ins_symbol(str, class)
	String	str;
	int	class;
#endif
{
  symb_entry	symb;

  if ( class == Kp_string )
	symb.Vp_string = cmrlib_newstring(str);
  else /* Kp_name */
	symb.Vp_name = cmrlib_newname(str);

  return( sidOfsymb_entry(symb) );
}

/*----------------------------------------------------*/
/* SECTION 2: functions for building definition table */
/*----------------------------------------------------*/

def_entry	NoDef;	/* initialized with NULL ? */

def_entry
#if defined (__cplusplus) || defined(__STDC__)
        ins_def(DefTableKey key, int class, SID sid, DID lhs, SEQunit rhs)
#else
        ins_def(key, class, sid, lhs, rhs)
	DefTableKey key;
	int	class;
	SID	sid;
	DID	lhs;
	SEQunit	rhs;
#endif
{
    def_entry	def;

    switch (class)
    {
      case Kp_term:	def = GetDef(key, NoDef);
			if (def.Vp_term == NoDef.Vp_term)
			{
				def.Vp_term = cmrlib_newterm(sid);
				ResetDef(key, def);
			}
			break;
      case Kp_nterm:	def = GetDef(key, NoDef);
			if (def.Vp_nterm == NoDef.Vp_nterm)
			{
				def.Vp_nterm = cmrlib_newnterm(sid);
				ResetDef(key, def);
			}
			break;
      case Kp_other:	def = GetOtherDef(key, NoDef);
			if (def.Vp_other == NoDef.Vp_other)
			{
				def.Vp_other = cmrlib_newother(sid);
				ResetOtherDef(key, def);
			}
			break;
      case Kp_prod:	def.Vp_prod=cmrlib_newprod(sid, lhs, rhs);
			break;
#ifdef	DEBUG
	default:	INTERNAL_ERR(2);
			break;
#endif
    }

    return(def);
}

def_entry
#if defined (__cplusplus) || defined(__STDC__)
ins_modification(DefTableKey key, SID sid, proptype m_op)
#else
ins_modification(key, sid, m_op)
DefTableKey key;
SID	sid;
proptype m_op;
#endif
{
  def_entry def;

  switch (m_op)
    {
    case P_NOREDUCE:
      def = GetNoReduceDef(key, NoDef);
      if (def.Vp_other == NoDef.Vp_other)
	{
	  def.Vp_other = cmrlib_newother(sid);
	  ResetNoReduceDef(key, def);
	}
      break;
    case P_REDUCE:
      def = GetReduceDef(key, NoDef);
      if (def.Vp_other == NoDef.Vp_other)
	{
	  def.Vp_other = cmrlib_newother(sid);
	  ResetReduceDef(key, def);
	}
      break;

    default:	INTERNAL_ERR(4);
      break;

    }
  return(def);
}

def_entry
#if defined (__cplusplus) || defined(__STDC__)
ins_connect(DefTableKey key, SID sid)
#else
ins_connect(key, sid)
DefTableKey key;
SID	sid;
#endif
{
  def_entry def;

  def = GetConnectDef(key, NoDef);
  if (def.Vp_other == NoDef.Vp_other)
    {
      def.Vp_other = cmrlib_newother(sid);
      ResetConnectDef(key, def);
    }
  return(def);
}

SEQunit
#if defined (__cplusplus) || defined(__STDC__)
ins_nullnt(DefTableKey key, SEQunit connect)
#else
ins_nullnt(key, connect)
DefTableKey key;
SEQunit	connect;
#endif
{
  int	sym;
  def_entry	def;
  DID	nullnt;

  if ( (nullnt = GetNullNt(key, NoDid)) == NoDid )
    {
      sym = GenerateName("COLA_CONNECT");
      def = ins_def(NoKey, Kp_nterm, ins_symbol(StringTable(sym), Kp_name),
		    NoDid, nullSEQunit());
      nullnt = didOfdef_entry(def);
      ins_def(NoKey, Kp_prod, S_NONAME, nullnt, connect);
      ResetNullNt(key, nullnt);
    } /* of if */

  return(build_elunit(nullnt));
} /* of ins_nullnt() */

def_entry
#if defined (__cplusplus) || defined(__STDC__)
  ins_startrule(DID start, DID eof, int lhssym)
#else
  ins_startrule(start, eof, lhssym)
  DID	start, eof;
  int	lhssym;
#endif
{
  SEQunit	list;
  def_entry	def;

  if ( start != NoDid )
  {
    list = build_elunit(start);
    list = concatSEQunit(list, build_elunit(eof));

    def = ins_def(NoKey, Kp_nterm, ins_symbol(StringTable(lhssym), Kp_name),
		  NoDid, nullSEQunit());
    return( ins_def(NoKey, Kp_prod, S_NONAME, didOfdef_entry(def), list) );
  } /* of if */
  else return(NoDef);
}	/* of ins_startrule() */



SEQunit
#if defined (__cplusplus) || defined(__STDC__)
	build_rhs(SEQunit l1, SEQunit l2, int opr)
#else
	build_rhs(l1, l2, opr)
	SEQunit    l1, l2;
	int        opr;
#endif
{
  unit  un;

  switch ( opr )
  {
    case Kp_alt : un = p_altTounit(Mkp_alt(l1,l2));
                  break;
    case Kp_opt : un = p_optTounit(Mkp_opt(l1));
                  break;
    case Kp_star: un = p_starTounit(Mkp_star(l1));
                  break;
    case Kp_plus: un = p_plusTounit(Mkp_plus(l1));
                  break;
    case Kp_delrep: un = p_delrepTounit(Mkp_delrep(l1,l2));
                  break;
#ifdef  DEBUG
        default:  INTERNAL_ERR(3);
                  break;
#endif
  } /* of switch */

  return( creatSEQunit(un) );
}	/* of build_rhs() */


SEQunit
#if defined (__cplusplus) || defined(__STDC__)
        build_elunit(DID did)
#else
        build_elunit(did)
        DID	did;
#endif
{
  unit	un;

  un = p_elunitTounit(Mkp_elunit(did));

  return( creatSEQunit(un) );
}	/* of build_elunit() */

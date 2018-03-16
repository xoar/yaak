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

static char rcsid[] = "$Id: comar_func.c,v 1.5 1997/08/29 08:38:08 mjung Exp $";

#include <string.h>
#include <stdio.h>

#include "comar.h"
#include "comar_func.h"

String	CpString(str)
	String str;
{
	String s;

	if (str == (String)NULL)
		return((String)NULL);
	else {
		if ( (s = (String)malloc((strlen(str)+1)*sizeof(char)))
							== (String)NULL )
		{
		    fprintf(stderr, "*** FATAL: Ran out of heap storage in CpString()\n");
		    exit(1);
		}
		return( (String)strcpy(s,str) );
	}
}

p_comar	Mkp_comar (psymbols, pdefinitions)
	SEQsymb_entry psymbols;
	SEQdef_entry pdefinitions;
{
	p_comar n;

	n = Np_comar;
	n->symbols = psymbols;
	n->definitions = pdefinitions;
	return(n);
}

p_comar	Cpp_comar(old)
	p_comar old;
{
	return(Mkp_comar
		   (
			CpSEQsymb_entry(old->symbols),
			CpSEQdef_entry(old->definitions)
		   )
	      );
}

symb_entry	Cpsymb_entry(old)
	symb_entry old;
{
	symb_entry new;

	switch (typeof(old))
	  {
	    case Kp_string	: new.Vp_string = Cpp_string(old.Vp_string);
				  break;
	    case Kp_name	: new.Vp_name = Cpp_name(old.Vp_name);
				  break;
	    default		: printf("Bad class in Cpsymb_entry : %lu "
	           		         , typeof(old)
	           		        );
	  }
	return( Cpattr_symb_entry(old,new) );
}

symb_entry	Mksymb_entry(psid, pstr, n)
	Integer psid;
	String pstr;
	symb_entry n;
{
	n.IDLclassCommon->sid = psid;
	n.IDLclassCommon->str = pstr;
	return(n);
}

symb_entry	Cpattr_symb_entry (old,new)
	symb_entry old,new;
{
	new.IDLclassCommon->sid = CpInteger(old.IDLclassCommon->sid);
	new.IDLclassCommon->str = CpString(old.IDLclassCommon->str);
	return(new);
}

def_entry	Cpdef_entry(old)
	def_entry old;
{
	def_entry new;

	switch (typeof(old))
	  {
	    case Kp_term	: new.Vp_term = Cpp_term(old.Vp_term);
				  break;
	    case Kp_nterm	: new.Vp_nterm = Cpp_nterm(old.Vp_nterm);
				  break;
	    case Kp_other	: new.Vp_other = Cpp_other(old.Vp_other);
				  break;
	    case Kp_prod	: new.Vp_prod = Cpp_prod(old.Vp_prod);
				  break;
	    default		: printf("Bad class in Cpdef_entry : %lu "
	           		         , typeof(old)
	           		        );
	  }
	return( Cpattr_def_entry(old,new) );
}

def_entry	Mkdef_entry(pdid, psid, pprop, n)
	Integer pdid;
	Integer psid;
	SEQprop_entry pprop;
	def_entry n;
{
	n.IDLclassCommon->did = pdid;
	n.IDLclassCommon->sid = psid;
	n.IDLclassCommon->prop = pprop;
	return(n);
}

def_entry	Cpattr_def_entry (old,new)
	def_entry old,new;
{
	new.IDLclassCommon->did = CpInteger(old.IDLclassCommon->did);
	new.IDLclassCommon->sid = CpInteger(old.IDLclassCommon->sid);
	new.IDLclassCommon->prop = CpSEQprop_entry(old.IDLclassCommon->prop);
	return(new);
}

p_prod	Mkp_prod (plhsdid, prhs)
	Integer plhsdid;
	SEQunit prhs;
{
	p_prod n;

	n = Np_prod;
	n->lhsdid = plhsdid;
	n->rhs = prhs;
	return(n);
}

p_prod	Cpp_prod(old)
	p_prod old;
{
	return(Mkp_prod
		   (
			CpInteger(old->lhsdid),
			CpSEQunit(old->rhs)
		   )
	      );
}

unit	Cpunit(old)
	unit old;
{
	unit new;

	switch (typeof(old))
	  {
	    case Kp_alt	: new.Vp_alt = Cpp_alt(old.Vp_alt);
				  break;
	    case Kp_opt	: new.Vp_opt = Cpp_opt(old.Vp_opt);
				  break;
	    case Kp_plus	: new.Vp_plus = Cpp_plus(old.Vp_plus);
				  break;
	    case Kp_star	: new.Vp_star = Cpp_star(old.Vp_star);
				  break;
	    case Kp_delrep	: new.Vp_delrep = Cpp_delrep(old.Vp_delrep);
				  break;
	    case Kp_elunit	: new.Vp_elunit = Cpp_elunit(old.Vp_elunit);
				  break;
	    default		: printf("Bad class in Cpunit : %lu "
	           		         , typeof(old)
	           		        );
	  }
	return( Cpattr_unit(old,new) );
}

p_alt	Mkp_alt (prhs1, prhs2)
	SEQunit prhs1;
	SEQunit prhs2;
{
	p_alt n;

	n = Np_alt;
	n->rhs1 = prhs1;
	n->rhs2 = prhs2;
	return(n);
}

p_alt	Cpp_alt(old)
	p_alt old;
{
	return(Mkp_alt
		   (
			CpSEQunit(old->rhs1),
			CpSEQunit(old->rhs2)
		   )
	      );
}

p_opt	Mkp_opt (prhs)
	SEQunit prhs;
{
	p_opt n;

	n = Np_opt;
	n->rhs = prhs;
	return(n);
}

p_opt	Cpp_opt(old)
	p_opt old;
{
	return(Mkp_opt
		   (
			CpSEQunit(old->rhs)
		   )
	      );
}

p_plus	Mkp_plus (prhs)
	SEQunit prhs;
{
	p_plus n;

	n = Np_plus;
	n->rhs = prhs;
	return(n);
}

p_plus	Cpp_plus(old)
	p_plus old;
{
	return(Mkp_plus
		   (
			CpSEQunit(old->rhs)
		   )
	      );
}

p_star	Mkp_star (prhs)
	SEQunit prhs;
{
	p_star n;

	n = Np_star;
	n->rhs = prhs;
	return(n);
}

p_star	Cpp_star(old)
	p_star old;
{
	return(Mkp_star
		   (
			CpSEQunit(old->rhs)
		   )
	      );
}

p_delrep	Mkp_delrep (prhs, psep)
	SEQunit prhs;
	SEQunit psep;
{
	p_delrep n;

	n = Np_delrep;
	n->rhs = prhs;
	n->sep = psep;
	return(n);
}

p_delrep	Cpp_delrep(old)
	p_delrep old;
{
	return(Mkp_delrep
		   (
			CpSEQunit(old->rhs),
			CpSEQunit(old->sep)
		   )
	      );
}

p_elunit	Mkp_elunit (pdid)
	Integer pdid;
{
	p_elunit n;

	n = Np_elunit;
	n->did = pdid;
	return(n);
}

p_elunit	Cpp_elunit(old)
	p_elunit old;
{
	return(Mkp_elunit
		   (
			CpInteger(old->did)
		   )
	      );
}

prop_entry	Cpprop_entry(old)
	prop_entry old;
{
	prop_entry new;

	switch (typeof(old))
	  {
	    case Kp_prop	: new.Vp_prop = Cpp_prop(old.Vp_prop);
				  break;
	    case Kp_prop_val	: new.Vp_prop_val = Cpp_prop_val(old.Vp_prop_val);
				  break;
	    default		: printf("Bad class in Cpprop_entry : %lu "
	           		         , typeof(old)
	           		        );
	  }
	return( Cpattr_prop_entry(old,new) );
}

prop_entry	Mkprop_entry(pdid, psid, n)
	Integer pdid;
	Integer psid;
	prop_entry n;
{
	n.IDLclassCommon->did = pdid;
	n.IDLclassCommon->sid = psid;
	return(n);
}

prop_entry	Cpattr_prop_entry (old,new)
	prop_entry old,new;
{
	new.IDLclassCommon->did = CpInteger(old.IDLclassCommon->did);
	new.IDLclassCommon->sid = CpInteger(old.IDLclassCommon->sid);
	return(new);
}

p_prop_val	Mkp_prop_val (pval)
	value pval;
{
	p_prop_val n;

	n = Np_prop_val;
	n->val = pval;
	return(n);
}

p_prop_val	Cpp_prop_val(old)
	p_prop_val old;
{
	return(Mkp_prop_val
		   (
			Cpvalue(old->val)
		   )
	      );
}

value	Cpvalue(old)
	value old;
{
	value new;

	switch (typeof(old))
	  {
	    case Kp_sval	: new.Vp_sval = Cpp_sval(old.Vp_sval);
				  break;
	    case Kp_nval	: new.Vp_nval = Cpp_nval(old.Vp_nval);
				  break;
	    case Kp_dval	: new.Vp_dval = Cpp_dval(old.Vp_dval);
				  break;
	    case Kp_lval	: new.Vp_lval = Cpp_lval(old.Vp_lval);
				  break;
	    default		: printf("Bad class in Cpvalue : %lu "
	           		         , typeof(old)
	           		        );
	  }
	return( Cpattr_value(old,new) );
}

p_sval	Mkp_sval (psid)
	Integer psid;
{
	p_sval n;

	n = Np_sval;
	n->sid = psid;
	return(n);
}

p_sval	Cpp_sval(old)
	p_sval old;
{
	return(Mkp_sval
		   (
			CpInteger(old->sid)
		   )
	      );
}

p_nval	Mkp_nval (pval)
	Integer pval;
{
	p_nval n;

	n = Np_nval;
	n->val = pval;
	return(n);
}

p_nval	Cpp_nval(old)
	p_nval old;
{
	return(Mkp_nval
		   (
			CpInteger(old->val)
		   )
	      );
}

p_dval	Mkp_dval (pdid)
	Integer pdid;
{
	p_dval n;

	n = Np_dval;
	n->did = pdid;
	return(n);
}

p_dval	Cpp_dval(old)
	p_dval old;
{
	return(Mkp_dval
		   (
			CpInteger(old->did)
		   )
	      );
}

p_lval	Mkp_lval (plist)
	SEQvalue plist;
{
	p_lval n;

	n = Np_lval;
	n->list = plist;
	return(n);
}

p_lval	Cpp_lval(old)
	p_lval old;
{
	return(Mkp_lval
		   (
			CpSEQvalue(old->list)
		   )
	      );
}


SEQsymb_entry CpSEQsymb_entry(old)
SEQsymb_entry old;
{
	SEQsymb_entry cp;
	symb_entry  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQsymb_entry(old, first);
	first = Cpsymb_entry(first);
	cp = CpSEQsymb_entry(tailSEQsymb_entry(old));
	return(appendfrontSEQsymb_entry(cp, first));
}

SEQdef_entry CpSEQdef_entry(old)
SEQdef_entry old;
{
	SEQdef_entry cp;
	def_entry  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQdef_entry(old, first);
	first = Cpdef_entry(first);
	cp = CpSEQdef_entry(tailSEQdef_entry(old));
	return(appendfrontSEQdef_entry(cp, first));
}

SEQprop_entry CpSEQprop_entry(old)
SEQprop_entry old;
{
	SEQprop_entry cp;
	prop_entry  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQprop_entry(old, first);
	first = Cpprop_entry(first);
	cp = CpSEQprop_entry(tailSEQprop_entry(old));
	return(appendfrontSEQprop_entry(cp, first));
}

SEQunit CpSEQunit(old)
SEQunit old;
{
	SEQunit cp;
	unit  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQunit(old, first);
	first = Cpunit(first);
	cp = CpSEQunit(tailSEQunit(old));
	return(appendfrontSEQunit(cp, first));
}

SEQvalue CpSEQvalue(old)
SEQvalue old;
{
	SEQvalue cp;
	value  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQvalue(old, first);
	first = Cpvalue(first);
	cp = CpSEQvalue(tailSEQvalue(old));
	return(appendfrontSEQvalue(cp, first));
}



SEQsymb_entry AppFrontSEQsymb_entry(el, l)
symb_entry el;
SEQsymb_entry l;
{
	return(appendfrontSEQsymb_entry(l, el));
}

SEQdef_entry AppFrontSEQdef_entry(el, l)
def_entry el;
SEQdef_entry l;
{
	return(appendfrontSEQdef_entry(l, el));
}

SEQprop_entry AppFrontSEQprop_entry(el, l)
prop_entry el;
SEQprop_entry l;
{
	return(appendfrontSEQprop_entry(l, el));
}

SEQunit AppFrontSEQunit(el, l)
unit el;
SEQunit l;
{
	return(appendfrontSEQunit(l, el));
}

SEQvalue AppFrontSEQvalue(el, l)
value el;
SEQvalue l;
{
	return(appendfrontSEQvalue(l, el));
}



SEQsymb_entry creatSEQsymb_entry(el)
symb_entry el;
{
	SEQsymb_entry	l;

	initializeSEQsymb_entry(l);
	return(appendfrontSEQsymb_entry(l, el));
}

SEQdef_entry creatSEQdef_entry(el)
def_entry el;
{
	SEQdef_entry	l;

	initializeSEQdef_entry(l);
	return(appendfrontSEQdef_entry(l, el));
}

SEQprop_entry creatSEQprop_entry(el)
prop_entry el;
{
	SEQprop_entry	l;

	initializeSEQprop_entry(l);
	return(appendfrontSEQprop_entry(l, el));
}

SEQunit creatSEQunit(el)
unit el;
{
	SEQunit	l;

	initializeSEQunit(l);
	return(appendfrontSEQunit(l, el));
}

SEQvalue creatSEQvalue(el)
value el;
{
	SEQvalue	l;

	initializeSEQvalue(l);
	return(appendfrontSEQvalue(l, el));
}



SEQsymb_entry concatSEQsymb_entry(l1, l2)
SEQsymb_entry l1, l2;
{
	SEQsymb_entry	help;

	if ( l1 == (SEQsymb_entry)NULL )
		return(l2);
	if ( l2 == (SEQsymb_entry)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQsymb_entry( tailSEQsymb_entry(l1) ) )
		l1 = tailSEQsymb_entry(l1);
	l1->next = copySEQsymb_entry(l2); /* dependent on the generated C types */
	return(help);
}

SEQdef_entry concatSEQdef_entry(l1, l2)
SEQdef_entry l1, l2;
{
	SEQdef_entry	help;

	if ( l1 == (SEQdef_entry)NULL )
		return(l2);
	if ( l2 == (SEQdef_entry)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQdef_entry( tailSEQdef_entry(l1) ) )
		l1 = tailSEQdef_entry(l1);
	l1->next = copySEQdef_entry(l2); /* dependent on the generated C types */
	return(help);
}

SEQprop_entry concatSEQprop_entry(l1, l2)
SEQprop_entry l1, l2;
{
	SEQprop_entry	help;

	if ( l1 == (SEQprop_entry)NULL )
		return(l2);
	if ( l2 == (SEQprop_entry)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQprop_entry( tailSEQprop_entry(l1) ) )
		l1 = tailSEQprop_entry(l1);
	l1->next = copySEQprop_entry(l2); /* dependent on the generated C types */
	return(help);
}

SEQunit concatSEQunit(l1, l2)
SEQunit l1, l2;
{
	SEQunit	help;

	if ( l1 == (SEQunit)NULL )
		return(l2);
	if ( l2 == (SEQunit)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQunit( tailSEQunit(l1) ) )
		l1 = tailSEQunit(l1);
	l1->next = copySEQunit(l2); /* dependent on the generated C types */
	return(help);
}

SEQvalue concatSEQvalue(l1, l2)
SEQvalue l1, l2;
{
	SEQvalue	help;

	if ( l1 == (SEQvalue)NULL )
		return(l2);
	if ( l2 == (SEQvalue)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQvalue( tailSEQvalue(l1) ) )
		l1 = tailSEQvalue(l1);
	l1->next = copySEQvalue(l2); /* dependent on the generated C types */
	return(help);
}

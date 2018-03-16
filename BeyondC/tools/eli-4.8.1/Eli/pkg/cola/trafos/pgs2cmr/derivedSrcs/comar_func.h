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

#ifndef COMAR_FUNC_H
#define COMAR_FUNC_H

/* $Id: comar_func.h,v 1.6 1997/08/29 08:38:08 mjung Exp $ */

#define CpInteger(n) (n)
#define CpRational(n) (n)
#define CpBoolean(n) (n)
extern String CpString(/* String str */);

#define SEQInteger SEQint
#define SEQRational SEQfloat
#define foreachinSEQInteger(a,b,c) foreachinSEQint(a,b,c)
#define foreachinSEQRational(a,b,c) foreachinSEQfloat(a,b,c)
#define copySEQInteger(a) copySEQint(a)
#define copySEQRational(a) copySEQfloat(a)
#define initializeSEQInteger(a) initializeSEQint(a)
#define initializeSEQRational(a) initializeSEQfloat(a)
#define retrievefirstSEQInteger(a,b) retrievefirstSEQint(a,b)
#define retrievefirstSEQRational(a,b) retrievefirstSEQfloat(a,b)
#define appendrearSEQInteger(a,b) appendrearSEQint(a,b)
#define appendrearSEQRational(a,b) appendrearSEQfloat(a,b)
#define appendfrontSEQInteger(a,b) appendfrontSEQint(a,b)
#define appendfrontSEQRational(a,b) appendfrontSEQfloat(a,b)
#define emptySEQInteger(a) emptySEQint(a)
#define emptySEQRational(a) emptySEQfloat(a)
#define tailSEQInteger(a) tailSEQint(a)
#define tailSEQRational(a) tailSEQfloat(a)

extern p_comar  Mkp_comar(/* SEQsymb_entry psymbols,
                             SEQdef_entry pdefinitions
                         */);
extern p_comar  Cpp_comar(/* p_comar old */);

extern symb_entry  Cpsymb_entry(/* symb_entry old */);
#define Ksymb_entry  Kp_string:; case Kp_name
extern symb_entry  Mksymb_entry(/* Integer psid,
                                   String pstr
                                   symb_entry n
                               */);
extern symb_entry  Cpattr_symb_entry(/* symb_entry old,new */);

#define Mkp_string()  (Np_string)
#define Cpp_string(old)  (Np_string)

#define Mkp_name()  (Np_name)
#define Cpp_name(old)  (Np_name)

extern def_entry  Cpdef_entry(/* def_entry old */);
#define Kdef_entry  Kp_term:; case Kp_nterm:; case Kp_other:; case Kp_prod
extern def_entry  Mkdef_entry(/* Integer pdid,
                                 Integer psid,
                                 SEQprop_entry pprop
                                 def_entry n
                             */);
extern def_entry  Cpattr_def_entry(/* def_entry old,new */);

#define Mkp_term()  (Np_term)
#define Cpp_term(old)  (Np_term)

#define Mkp_nterm()  (Np_nterm)
#define Cpp_nterm(old)  (Np_nterm)

#define Mkp_other()  (Np_other)
#define Cpp_other(old)  (Np_other)

extern p_prod  Mkp_prod(/* Integer plhsdid,
                           SEQunit prhs
                       */);
extern p_prod  Cpp_prod(/* p_prod old */);

extern unit  Cpunit(/* unit old */);
#define Kunit  Kp_alt:; case Kp_opt:; case Kp_plus:; case Kp_star:; case Kp_delrep:; case Kp_elunit
#define  Cpattr_unit(old,new)   (new)

extern p_alt  Mkp_alt(/* SEQunit prhs1,
                         SEQunit prhs2
                     */);
extern p_alt  Cpp_alt(/* p_alt old */);

extern p_opt  Mkp_opt(/* SEQunit prhs */);
extern p_opt  Cpp_opt(/* p_opt old */);

extern p_plus  Mkp_plus(/* SEQunit prhs */);
extern p_plus  Cpp_plus(/* p_plus old */);

extern p_star  Mkp_star(/* SEQunit prhs */);
extern p_star  Cpp_star(/* p_star old */);

extern p_delrep  Mkp_delrep(/* SEQunit prhs,
                               SEQunit psep
                           */);
extern p_delrep  Cpp_delrep(/* p_delrep old */);

extern p_elunit  Mkp_elunit(/* Integer pdid */);
extern p_elunit  Cpp_elunit(/* p_elunit old */);

extern prop_entry  Cpprop_entry(/* prop_entry old */);
#define Kprop_entry  Kp_prop:; case Kp_prop_val
extern prop_entry  Mkprop_entry(/* Integer pdid,
                                   Integer psid
                                   prop_entry n
                               */);
extern prop_entry  Cpattr_prop_entry(/* prop_entry old,new */);

#define Mkp_prop()  (Np_prop)
#define Cpp_prop(old)  (Np_prop)

extern p_prop_val  Mkp_prop_val(/* value pval */);
extern p_prop_val  Cpp_prop_val(/* p_prop_val old */);

extern value  Cpvalue(/* value old */);
#define Kvalue  Kp_sval:; case Kp_nval:; case Kp_dval:; case Kp_lval
#define  Cpattr_value(old,new)   (new)

extern p_sval  Mkp_sval(/* Integer psid */);
extern p_sval  Cpp_sval(/* p_sval old */);

extern p_nval  Mkp_nval(/* Integer pval */);
extern p_nval  Cpp_nval(/* p_nval old */);

extern p_dval  Mkp_dval(/* Integer pdid */);
extern p_dval  Cpp_dval(/* p_dval old */);

extern p_lval  Mkp_lval(/* SEQvalue plist */);
extern p_lval  Cpp_lval(/* p_lval old */);

extern SEQsymb_entry	CpSEQsymb_entry(/* SEQsymb_entry old */);
extern SEQdef_entry	CpSEQdef_entry(/* SEQdef_entry old */);
extern SEQprop_entry	CpSEQprop_entry(/* SEQprop_entry old */);
extern SEQunit	CpSEQunit(/* SEQunit old */);
extern SEQvalue	CpSEQvalue(/* SEQvalue old */);


extern SEQsymb_entry	AppFrontSEQsymb_entry(/* symb_entry el, SEQsymb_entry l */);
extern SEQdef_entry	AppFrontSEQdef_entry(/* def_entry el, SEQdef_entry l */);
extern SEQprop_entry	AppFrontSEQprop_entry(/* prop_entry el, SEQprop_entry l */);
extern SEQunit	AppFrontSEQunit(/* unit el, SEQunit l */);
extern SEQvalue	AppFrontSEQvalue(/* value el, SEQvalue l */);


#define	 nullSEQsymb_entry()	((SEQsymb_entry)NULL)
#define	 nullSEQdef_entry()	((SEQdef_entry)NULL)
#define	 nullSEQprop_entry()	((SEQprop_entry)NULL)
#define	 nullSEQunit()	((SEQunit)NULL)
#define	 nullSEQvalue()	((SEQvalue)NULL)


extern SEQsymb_entry	creatSEQsymb_entry(/* symb_entry el */);
extern SEQdef_entry	creatSEQdef_entry(/* def_entry el */);
extern SEQprop_entry	creatSEQprop_entry(/* prop_entry el */);
extern SEQunit	creatSEQunit(/* unit el */);
extern SEQvalue	creatSEQvalue(/* value el */);


extern SEQsymb_entry	concatSEQsymb_entry(/* SEQsymb_entry l1, l2 */);
extern SEQdef_entry	concatSEQdef_entry(/* SEQdef_entry l1, l2 */);
extern SEQprop_entry	concatSEQprop_entry(/* SEQprop_entry l1, l2 */);
extern SEQunit	concatSEQunit(/* SEQunit l1, l2 */);
extern SEQvalue	concatSEQvalue(/* SEQvalue l1, l2 */);

#endif

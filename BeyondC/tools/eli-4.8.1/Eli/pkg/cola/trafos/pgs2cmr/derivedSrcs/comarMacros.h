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

/*
** $Id: comarMacros.h,v 1.5 1997/08/29 08:38:08 mjung Exp $
*/

#ifndef COMARMACROS_H
#define COMARMACROS_H

/* Class Attribute accessing macros */

#define sidOfsymb_entry(Asymb_entry) Asymb_entry.IDLclassCommon->sid
#define strOfsymb_entry(Asymb_entry) Asymb_entry.IDLclassCommon->str
#define didOfdef_entry(Adef_entry) Adef_entry.IDLclassCommon->did
#define sidOfdef_entry(Adef_entry) Adef_entry.IDLclassCommon->sid
#define propOfdef_entry(Adef_entry) Adef_entry.IDLclassCommon->prop
#define didOfprop_entry(Aprop_entry) Aprop_entry.IDLclassCommon->did
#define sidOfprop_entry(Aprop_entry) Aprop_entry.IDLclassCommon->sid

/* Node Attribute  accessing macros */

#define rhs2Ofp_alt(Ap_alt) Ap_alt->rhs2
#define rhs1Ofp_alt(Ap_alt) Ap_alt->rhs1
#define definitionsOfp_comar(Ap_comar) Ap_comar->definitions
#define symbolsOfp_comar(Ap_comar) Ap_comar->symbols
#define sepOfp_delrep(Ap_delrep) Ap_delrep->sep
#define rhsOfp_delrep(Ap_delrep) Ap_delrep->rhs
#define didOfp_dval(Ap_dval) Ap_dval->did
#define didOfp_elunit(Ap_elunit) Ap_elunit->did
#define listOfp_lval(Ap_lval) Ap_lval->list
#define sidOfp_name(Ap_name) Ap_name->sid
#define strOfp_name(Ap_name) Ap_name->str
#define didOfp_nterm(Ap_nterm) Ap_nterm->did
#define sidOfp_nterm(Ap_nterm) Ap_nterm->sid
#define propOfp_nterm(Ap_nterm) Ap_nterm->prop
#define valOfp_nval(Ap_nval) Ap_nval->val
#define rhsOfp_opt(Ap_opt) Ap_opt->rhs
#define didOfp_other(Ap_other) Ap_other->did
#define sidOfp_other(Ap_other) Ap_other->sid
#define propOfp_other(Ap_other) Ap_other->prop
#define rhsOfp_plus(Ap_plus) Ap_plus->rhs
#define didOfp_prod(Ap_prod) Ap_prod->did
#define sidOfp_prod(Ap_prod) Ap_prod->sid
#define propOfp_prod(Ap_prod) Ap_prod->prop
#define rhsOfp_prod(Ap_prod) Ap_prod->rhs
#define lhsdidOfp_prod(Ap_prod) Ap_prod->lhsdid
#define didOfp_prop(Ap_prop) Ap_prop->did
#define sidOfp_prop(Ap_prop) Ap_prop->sid
#define didOfp_prop_val(Ap_prop_val) Ap_prop_val->did
#define sidOfp_prop_val(Ap_prop_val) Ap_prop_val->sid
#define valOfp_prop_val(Ap_prop_val) Ap_prop_val->val
#define rhsOfp_star(Ap_star) Ap_star->rhs
#define sidOfp_string(Ap_string) Ap_string->sid
#define strOfp_string(Ap_string) Ap_string->str
#define sidOfp_sval(Ap_sval) Ap_sval->sid
#define didOfp_term(Ap_term) Ap_term->did
#define sidOfp_term(Ap_term) Ap_term->sid
#define propOfp_term(Ap_term) Ap_term->prop

/* Widening Conversion macros */

extern symb_entry IDLtempsymb_entry;
#define p_stringTosymb_entry(Ap_string) \
	(IDLtempsymb_entry.Vp_string = Ap_string, IDLtempsymb_entry)
#define p_nameTosymb_entry(Ap_name) \
	(IDLtempsymb_entry.Vp_name = Ap_name, IDLtempsymb_entry)

extern def_entry IDLtempdef_entry;
#define p_termTodef_entry(Ap_term) \
	(IDLtempdef_entry.Vp_term = Ap_term, IDLtempdef_entry)
#define p_ntermTodef_entry(Ap_nterm) \
	(IDLtempdef_entry.Vp_nterm = Ap_nterm, IDLtempdef_entry)
#define p_otherTodef_entry(Ap_other) \
	(IDLtempdef_entry.Vp_other = Ap_other, IDLtempdef_entry)
#define p_prodTodef_entry(Ap_prod) \
	(IDLtempdef_entry.Vp_prod = Ap_prod, IDLtempdef_entry)

extern unit IDLtempunit;
#define p_altTounit(Ap_alt) \
	(IDLtempunit.Vp_alt = Ap_alt, IDLtempunit)
#define p_optTounit(Ap_opt) \
	(IDLtempunit.Vp_opt = Ap_opt, IDLtempunit)
#define p_plusTounit(Ap_plus) \
	(IDLtempunit.Vp_plus = Ap_plus, IDLtempunit)
#define p_starTounit(Ap_star) \
	(IDLtempunit.Vp_star = Ap_star, IDLtempunit)
#define p_delrepTounit(Ap_delrep) \
	(IDLtempunit.Vp_delrep = Ap_delrep, IDLtempunit)
#define p_elunitTounit(Ap_elunit) \
	(IDLtempunit.Vp_elunit = Ap_elunit, IDLtempunit)

extern prop_entry IDLtempprop_entry;
#define p_propToprop_entry(Ap_prop) \
	(IDLtempprop_entry.Vp_prop = Ap_prop, IDLtempprop_entry)
#define p_prop_valToprop_entry(Ap_prop_val) \
	(IDLtempprop_entry.Vp_prop_val = Ap_prop_val, IDLtempprop_entry)

extern value IDLtempvalue;
#define p_svalTovalue(Ap_sval) \
	(IDLtempvalue.Vp_sval = Ap_sval, IDLtempvalue)
#define p_nvalTovalue(Ap_nval) \
	(IDLtempvalue.Vp_nval = Ap_nval, IDLtempvalue)
#define p_dvalTovalue(Ap_dval) \
	(IDLtempvalue.Vp_dval = Ap_dval, IDLtempvalue)
#define p_lvalTovalue(Ap_lval) \
	(IDLtempvalue.Vp_lval = Ap_lval, IDLtempvalue)


/* Narrowing Conversion macros */

#define symb_entryTop_string(Asymb_entry)	((Asymb_entry).Vp_string)
#define symb_entryTop_name(Asymb_entry)	((Asymb_entry).Vp_name)
#define def_entryTop_term(Adef_entry)	((Adef_entry).Vp_term)
#define def_entryTop_nterm(Adef_entry)	((Adef_entry).Vp_nterm)
#define def_entryTop_other(Adef_entry)	((Adef_entry).Vp_other)
#define def_entryTop_prod(Adef_entry)	((Adef_entry).Vp_prod)
#define unitTop_alt(Aunit)	((Aunit).Vp_alt)
#define unitTop_opt(Aunit)	((Aunit).Vp_opt)
#define unitTop_plus(Aunit)	((Aunit).Vp_plus)
#define unitTop_star(Aunit)	((Aunit).Vp_star)
#define unitTop_delrep(Aunit)	((Aunit).Vp_delrep)
#define unitTop_elunit(Aunit)	((Aunit).Vp_elunit)
#define prop_entryTop_prop(Aprop_entry)	((Aprop_entry).Vp_prop)
#define prop_entryTop_prop_val(Aprop_entry)	((Aprop_entry).Vp_prop_val)
#define valueTop_sval(Avalue)	((Avalue).Vp_sval)
#define valueTop_nval(Avalue)	((Avalue).Vp_nval)
#define valueTop_dval(Avalue)	((Avalue).Vp_dval)
#define valueTop_lval(Avalue)	((Avalue).Vp_lval)

#endif

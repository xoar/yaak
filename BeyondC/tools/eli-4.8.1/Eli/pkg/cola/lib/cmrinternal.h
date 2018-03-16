/*
** $Id: cmrinternal.h,v 1.4 1997/08/29 08:38:08 mjung Exp $
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
/* File: cmrinternal.h	First Edit: 17.10.88	  Last Edit: 07.12.88      */
/*									   */
/* Author: Karl-Josef Prott,	University at Paderborn, Germany	   */
/***************************************************************************/


/* This is a header file needed by library "cmrlib". Here are internal 
 * macros defined, which should not be interesting for anyone making use 
 * of "cmrlib". "cmrinternal.h" helps to implement several functions 
 * declared in "cmrlib.h" by one generic function in "cmrlib.c".
 */
#define MACRO

#define Kp_all 0

/* (forward-) declarations of functions implemented in "cmrlib.c" */
extern	CPsymb_entry	cmrlib_symnewxy();
extern	CPsymb_entry	cmrlib_symstrtoxy();
extern	SEQsymb_entry	cmrlib_symgetallxys();

extern	CPdef_entry	cmrlib_defnewxy();
extern	SEQdef_entry	cmrlib_defsidtoxys();
extern	SEQdef_entry	cmrlib_defgetallxys();

extern	CPprop_entry	cmrlib_propnewxy();
extern	CPprop_entry	cmrlib_propdelxy();
extern	CPprop_entry	cmrlib_propsidtoxys();
extern	SEQprop_entry	cmrlib_propgetallxys();

extern	pGenList	cmrlib_reversexy();


/* macros for handling with symbol-table */

#define cmrlib_newstring(str)  ( (p_string)cmrlib_symnewxy(Kp_string, str) )
#define cmrlib_newname(str)    ( (p_name)cmrlib_symnewxy(Kp_name, str) )

#define cmrlib_strtopstring(seq, str)	\
		((p_string)cmrlib_symstrtoxy(seq, Kp_string, str))
#define cmrlib_strtopname(seq, str)  	\
		( (p_name)cmrlib_symstrtoxy(seq, Kp_name, str) )

#define cmrlib_getallstrings(seq)   ( cmrlib_symgetallxys(seq, Kp_string) )
#define cmrlib_getallnames(seq)     ( cmrlib_symgetallxys(seq, Kp_name) )


/* macros for handling with definition-table */

#define cmrlib_newterm(sid)   ( (p_term)cmrlib_defnewxy(Kp_term, sid) )
#define cmrlib_newnterm(sid)  ( (p_nterm)cmrlib_defnewxy(Kp_nterm, sid) )
#define cmrlib_newother(sid)  ( (p_other)cmrlib_defnewxy(Kp_other, sid) )

#define cmrlib_sidtodefs(seq,sid)    (cmrlib_defsidtoxys(seq,Kp_all,sid))
#define cmrlib_sidtoterms(seq,sid)   (cmrlib_defsidtoxys(seq,Kp_term,sid))
#define cmrlib_sidtonterms(seq,sid)  (cmrlib_defsidtoxys(seq,Kp_nterm,sid))
#define cmrlib_sidtoothers(seq,sid)  (cmrlib_defsidtoxys(seq,Kp_other,sid))
#define cmrlib_sidtoprods(seq,sid)   (cmrlib_defsidtoxys(seq,Kp_prod,sid))

#define cmrlib_getallterms(seq)		(cmrlib_defgetallxys(seq,Kp_terms))
#define cmrlib_getallnterms(seq)	(cmrlib_defgetallxys(seq,Kp_nterms))
#define cmrlib_getallothers(seq)	(cmrlib_defgetallxys(seq,Kp_others))
#define cmrlib_getallprods(seq)		(cmrlib_defgetallxys(seq,Kp_prods))



/* macros for handling with property-list */

#define cmrlib_newprop(def,sid)	\
		( (p_prop)cmrlib_propnewxy(Kp_prop,def,sid,DUMMYvalue) )
#define cmrlib_newpropval(def,sid,val)	\
		( (p_prop_val)cmrlib_propnewxy(Kp_prop_val,def,sid,val) )

#define cmrlib_delprop(def,sid)		\
		( (p_prop)cmrlib_propdelxy(Kp_prop,def,sid) )
#define cmrlib_delpropval(def,sid)		\
		( (p_prop_val)cmrlib_propdelxy(Kp_prop_val,def,sid) )

#define cmrlib_sidtoprop(seq,sid)    \
		((p_prop)cmrlib_propsidtoxys(seq,Kp_prop,sid))
#define cmrlib_sidtopropval(seq,sid) \
		((p_prop_val)cmrlib_propsidtoxys(seq,Kp_prop_val,sid))

#define cmrlib_getallprops(seq)     (cmrlib_propgetallxys(seq,Kp_prop))
#define cmrlib_getallpropvals(seq)  (cmrlib_propgetallxys(seq,Kp_prop_val))


/* macros for list-handling analogous "comar.h"*/

#define reverseSEQsymb_entry(seq)   ( (SEQsymb_entry)cmrlib_reversexy(seq) )
#define reverseSEQdef_entry(seq)    ( (SEQdef_entry)cmrlib_reversexy(seq) )
#define reverseSEQprop_entry(seq)   ( (SEQprop_entry)cmrlib_reversexy(seq) )
#define reverseSEQunit(seq)	    ( (SEQunit)cmrlib_reversexy(seq) )
#define reverseSEQvalue(seq)	    ( (SEQvalue)cmrlib_reversexy(seq) )


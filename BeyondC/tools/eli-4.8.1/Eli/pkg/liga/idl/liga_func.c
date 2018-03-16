/* $Id: liga_func.c,v 4.1 1997/08/29 08:26:49 peter Exp $ */
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

#include <string.h>
#include <stdio.h>

#include "LIGA.h"
#include "liga_func.h"

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

AttrEval	MkAttrEval (pdefseq, pattrrules)
	SEQDef pdefseq;
	SEQAttribution pattrrules;
{
	AttrEval n;

	n = NAttrEval;
	n->defseq = pdefseq;
	n->attrrules = pattrrules;
	return(n);
}

AttrEval	CpAttrEval(old)
	AttrEval old;
{
	return(MkAttrEval
		   (
			CpSEQDef(old->defseq),
			CpSEQAttribution(old->attrrules)
		   )
	      );
}

Def	CpDef(old)
	Def old;
{
	Def new;

	switch (typeof(old))
	  {
	    case KChain	: new.VChain = CpChain(old.VChain);
				  break;
	    case KTypedef	: new.VTypedef = CpTypedef(old.VTypedef);
				  break;
	    case KSymb	: new.VSymb = CpSymb(old.VSymb);
				  break;
	    case KProd	: new.VProd = CpProd(old.VProd);
				  break;
	    default		: printf("Bad class in CpDef : %lu "
	           		         , typeof(old)
	           		        );
	  }
	return( Cpattr_Def(old,new) );
}

Def	MkDef(pdid, pdname, prow, pcol, n)
	Integer pdid;
	String pdname;
	Integer prow;
	Integer pcol;
	Def n;
{
	n.IDLclassCommon->did = pdid;
	n.IDLclassCommon->dname = pdname;
	n.IDLclassCommon->row = prow;
	n.IDLclassCommon->col = pcol;
	return(n);
}

Def	Cpattr_Def (old,new)
	Def old,new;
{
	new.IDLclassCommon->did = CpInteger(old.IDLclassCommon->did);
	new.IDLclassCommon->dname = CpString(old.IDLclassCommon->dname);
	new.IDLclassCommon->row = CpInteger(old.IDLclassCommon->row);
	new.IDLclassCommon->col = CpInteger(old.IDLclassCommon->col);
	return(new);
}

Chain	MkChain (ptypeid)
	Integer ptypeid;
{
	Chain n;

	n = NChain;
	n->typeid = ptypeid;
	return(n);
}

Chain	CpChain(old)
	Chain old;
{
	return(MkChain
		   (
			CpInteger(old->typeid)
		   )
	      );
}

Typedef	MkTypedef (pextname, plistedto)
	String pextname;
	Integer plistedto;
{
	Typedef n;

	n = NTypedef;
	n->extname = pextname;
	n->listedto = plistedto;
	return(n);
}

Typedef	CpTypedef(old)
	Typedef old;
{
	return(MkTypedef
		   (
			CpString(old->extname),
			CpInteger(old->listedto)
		   )
	      );
}

Symb	MkSymb (ptornt, pattrs)
	Integer ptornt;
	SEQAttrdef pattrs;
{
	Symb n;

	n = NSymb;
	n->tornt = ptornt;
	n->attrs = pattrs;
	return(n);
}

Symb	CpSymb(old)
	Symb old;
{
	return(MkSymb
		   (
			CpInteger(old->tornt),
			CpSEQAttrdef(old->attrs)
		   )
	      );
}

Attrdef	MkAttrdef (pdid, pname, prow, pcol, ptypeid, pclass, pprodid, pstore, pgen, ppart, pglobname)
	Integer pdid;
	String pname;
	Integer prow;
	Integer pcol;
	Integer ptypeid;
	Integer pclass;
	Integer pprodid;
	Integer pstore;
	Integer pgen;
	Integer ppart;
	String pglobname;
{
	Attrdef n;

	n = NAttrdef;
	n->did = pdid;
	n->name = pname;
	n->row = prow;
	n->col = pcol;
	n->typeid = ptypeid;
	n->class = pclass;
	n->prodid = pprodid;
	n->store = pstore;
	n->gen = pgen;
	n->part = ppart;
	n->globname = pglobname;
	return(n);
}

Attrdef	CpAttrdef(old)
	Attrdef old;
{
	return(MkAttrdef
		   (
			CpInteger(old->did),
			CpString(old->name),
			CpInteger(old->row),
			CpInteger(old->col),
			CpInteger(old->typeid),
			CpInteger(old->class),
			CpInteger(old->prodid),
			CpInteger(old->store),
			CpInteger(old->gen),
			CpInteger(old->part),
			CpString(old->globname)
		   )
	      );
}

Prod	MkProd (plhs, prhs)
	Integer plhs;
	SEQEntity prhs;
{
	Prod n;

	n = NProd;
	n->lhs = plhs;
	n->rhs = prhs;
	return(n);
}

Prod	CpProd(old)
	Prod old;
{
	return(MkProd
		   (
			CpInteger(old->lhs),
			CpSEQEntity(old->rhs)
		   )
	      );
}

Entity	CpEntity(old)
	Entity old;
{
	Entity new;

	switch (typeof(old))
	  {
	    case KUnit	: new.VUnit = CpUnit(old.VUnit);
				  break;
	    case KOpt	: new.VOpt = CpOpt(old.VOpt);
				  break;
	    case KStar	: new.VStar = CpStar(old.VStar);
				  break;
	    case KPlus	: new.VPlus = CpPlus(old.VPlus);
				  break;
	    case KDelim	: new.VDelim = CpDelim(old.VDelim);
				  break;
	    case KDelopt	: new.VDelopt = CpDelopt(old.VDelopt);
				  break;
	    default		: printf("Bad class in CpEntity : %lu "
	           		         , typeof(old)
	           		        );
	  }
	return( Cpattr_Entity(old,new) );
}

Unit	CpUnit(old)
	Unit old;
{
	Unit new;

	switch (typeof(old))
	  {
	    case KSymbol	: new.VSymbol = CpSymbol(old.VSymbol);
				  break;
	    case KLiteral	: new.VLiteral = CpLiteral(old.VLiteral);
				  break;
	    default		: printf("Bad class in CpUnit : %lu "
	           		         , typeof(old)
	           		        );
	  }
	return( Cpattr_Unit(old,new) );
}

Unit	MkUnit(prow, pcol, n)
	Integer prow;
	Integer pcol;
	Unit n;
{
	n.IDLclassCommon->row = prow;
	n.IDLclassCommon->col = pcol;
	return(n);
}

Unit	Cpattr_Unit (old,new)
	Unit old,new;
{
	new.IDLclassCommon->row = CpInteger(old.IDLclassCommon->row);
	new.IDLclassCommon->col = CpInteger(old.IDLclassCommon->col);
	return(new);
}

Symbol	MkSymbol (pdid)
	Integer pdid;
{
	Symbol n;

	n = NSymbol;
	n->did = pdid;
	return(n);
}

Symbol	CpSymbol(old)
	Symbol old;
{
	return(MkSymbol
		   (
			CpInteger(old->did)
		   )
	      );
}

Literal	MkLiteral (pstr)
	String pstr;
{
	Literal n;

	n = NLiteral;
	n->str = pstr;
	return(n);
}

Literal	CpLiteral(old)
	Literal old;
{
	return(MkLiteral
		   (
			CpString(old->str)
		   )
	      );
}

Opt	MkOpt (prhs)
	SEQUnit prhs;
{
	Opt n;

	n = NOpt;
	n->rhs = prhs;
	return(n);
}

Opt	CpOpt(old)
	Opt old;
{
	return(MkOpt
		   (
			CpSEQUnit(old->rhs)
		   )
	      );
}

Star	MkStar (prhs)
	SEQUnit prhs;
{
	Star n;

	n = NStar;
	n->rhs = prhs;
	return(n);
}

Star	CpStar(old)
	Star old;
{
	return(MkStar
		   (
			CpSEQUnit(old->rhs)
		   )
	      );
}

Plus	MkPlus (prhs)
	SEQUnit prhs;
{
	Plus n;

	n = NPlus;
	n->rhs = prhs;
	return(n);
}

Plus	CpPlus(old)
	Plus old;
{
	return(MkPlus
		   (
			CpSEQUnit(old->rhs)
		   )
	      );
}

Delim	MkDelim (prhs, pdel)
	SEQUnit prhs;
	Literal pdel;
{
	Delim n;

	n = NDelim;
	n->rhs = prhs;
	n->del = pdel;
	return(n);
}

Delim	CpDelim(old)
	Delim old;
{
	return(MkDelim
		   (
			CpSEQUnit(old->rhs),
			CpLiteral(old->del)
		   )
	      );
}

Delopt	MkDelopt (prhs, pdel)
	SEQUnit prhs;
	Literal pdel;
{
	Delopt n;

	n = NDelopt;
	n->rhs = prhs;
	n->del = pdel;
	return(n);
}

Delopt	CpDelopt(old)
	Delopt old;
{
	return(MkDelopt
		   (
			CpSEQUnit(old->rhs),
			CpLiteral(old->del)
		   )
	      );
}

Attribution	MkAttribution (pprodid, pattrrules)
	Integer pprodid;
	SEQAttrrule pattrrules;
{
	Attribution n;

	n = NAttribution;
	n->prodid = pprodid;
	n->attrrules = pattrrules;
	return(n);
}

Attribution	CpAttribution(old)
	Attribution old;
{
	return(MkAttribution
		   (
			CpInteger(old->prodid),
			CpSEQAttrrule(old->attrrules)
		   )
	      );
}

Attrrule	CpAttrrule(old)
	Attrrule old;
{
	Attrrule new;

	switch (typeof(old))
	  {
	    case KCall	: new.VCall = CpCall(old.VCall);
				  break;
	    case KVisit	: new.VVisit = CpVisit(old.VVisit);
				  break;
	    case KTransfer	: new.VTransfer = CpTransfer(old.VTransfer);
				  break;
	    case KChainStart	: new.VChainStart = CpChainStart(old.VChainStart);
				  break;
	    default		: printf("Bad class in CpAttrrule : %lu "
	           		         , typeof(old)
	           		        );
	  }
	return( Cpattr_Attrrule(old,new) );
}

ChainStart	MkChainStart (pchainid, ppregenattr, ppostgenattr, prow, pcol)
	Integer pchainid;
	String ppregenattr;
	String ppostgenattr;
	Integer prow;
	Integer pcol;
{
	ChainStart n;

	n = NChainStart;
	n->chainid = pchainid;
	n->pregenattr = ppregenattr;
	n->postgenattr = ppostgenattr;
	n->row = prow;
	n->col = pcol;
	return(n);
}

ChainStart	CpChainStart(old)
	ChainStart old;
{
	return(MkChainStart
		   (
			CpInteger(old->chainid),
			CpString(old->pregenattr),
			CpString(old->postgenattr),
			CpInteger(old->row),
			CpInteger(old->col)
		   )
	      );
}

Visit	MkVisit (psymbno, pord)
	Integer psymbno;
	Integer pord;
{
	Visit n;

	n = NVisit;
	n->symbno = psymbno;
	n->ord = pord;
	return(n);
}

Visit	CpVisit(old)
	Visit old;
{
	return(MkVisit
		   (
			CpInteger(old->symbno),
			CpInteger(old->ord)
		   )
	      );
}

Transfer	MkTransfer (psymbno, pattrs, prow, pcol)
	SEQInteger psymbno;
	SEQString pattrs;
	Integer prow;
	Integer pcol;
{
	Transfer n;

	n = NTransfer;
	n->symbno = psymbno;
	n->attrs = pattrs;
	n->row = prow;
	n->col = pcol;
	return(n);
}

Transfer	CpTransfer(old)
	Transfer old;
{
	return(MkTransfer
		   (
			CpSEQInteger(old->symbno),
			CpSEQString(old->attrs),
			CpInteger(old->row),
			CpInteger(old->col)
		   )
	      );
}

Call	MkCall (pname, pparams, prow, pcol)
	String pname;
	SEQExpr pparams;
	Integer prow;
	Integer pcol;
{
	Call n;

	n = NCall;
	n->name = pname;
	n->params = pparams;
	n->row = prow;
	n->col = pcol;
	return(n);
}

Call	CpCall(old)
	Call old;
{
	return(MkCall
		   (
			CpString(old->name),
			CpSEQExpr(old->params),
			CpInteger(old->row),
			CpInteger(old->col)
		   )
	      );
}

Expr	CpExpr(old)
	Expr old;
{
	Expr new;

	switch (typeof(old))
	  {
	    case KCall	: new.VCall = CpCall(old.VCall);
				  break;
	    case KLiteral	: new.VLiteral = CpLiteral(old.VLiteral);
				  break;
	    case KVal	: new.VVal = CpVal(old.VVal);
				  break;
	    case KName	: new.VName = CpName(old.VName);
				  break;
	    case KAttracc	: new.VAttracc = CpAttracc(old.VAttracc);
				  break;
	    case KChainacc	: new.VChainacc = CpChainacc(old.VChainacc);
				  break;
	    case KConstit	: new.VConstit = CpConstit(old.VConstit);
				  break;
	    case KIncluding	: new.VIncluding = CpIncluding(old.VIncluding);
				  break;
	    default		: printf("Bad class in CpExpr : %lu "
	           		         , typeof(old)
	           		        );
	  }
	return( Cpattr_Expr(old,new) );
}

Val	MkVal (pv, prow, pcol)
	Integer pv;
	Integer prow;
	Integer pcol;
{
	Val n;

	n = NVal;
	n->v = pv;
	n->row = prow;
	n->col = pcol;
	return(n);
}

Val	CpVal(old)
	Val old;
{
	return(MkVal
		   (
			CpInteger(old->v),
			CpInteger(old->row),
			CpInteger(old->col)
		   )
	      );
}

Name	MkName (pn, prow, pcol)
	String pn;
	Integer prow;
	Integer pcol;
{
	Name n;

	n = NName;
	n->n = pn;
	n->row = prow;
	n->col = pcol;
	return(n);
}

Name	CpName(old)
	Name old;
{
	return(MkName
		   (
			CpString(old->n),
			CpInteger(old->row),
			CpInteger(old->col)
		   )
	      );
}

Attracc	MkAttracc (psymbno, pattrid, prow, pcol)
	Integer psymbno;
	Integer pattrid;
	Integer prow;
	Integer pcol;
{
	Attracc n;

	n = NAttracc;
	n->symbno = psymbno;
	n->attrid = pattrid;
	n->row = prow;
	n->col = pcol;
	return(n);
}

Attracc	CpAttracc(old)
	Attracc old;
{
	return(MkAttracc
		   (
			CpInteger(old->symbno),
			CpInteger(old->attrid),
			CpInteger(old->row),
			CpInteger(old->col)
		   )
	      );
}

Chainacc	MkChainacc (psymbno, pchainid, prow, pcol)
	Integer psymbno;
	Integer pchainid;
	Integer prow;
	Integer pcol;
{
	Chainacc n;

	n = NChainacc;
	n->symbno = psymbno;
	n->chainid = pchainid;
	n->row = prow;
	n->col = pcol;
	return(n);
}

Chainacc	CpChainacc(old)
	Chainacc old;
{
	return(MkChainacc
		   (
			CpInteger(old->symbno),
			CpInteger(old->chainid),
			CpInteger(old->row),
			CpInteger(old->col)
		   )
	      );
}

Including	MkIncluding (pgenattr, pgenattrid, pinclattrs, prow, pcol)
	String pgenattr;
	Integer pgenattrid;
	SEQSymbattr pinclattrs;
	Integer prow;
	Integer pcol;
{
	Including n;

	n = NIncluding;
	n->genattr = pgenattr;
	n->genattrid = pgenattrid;
	n->inclattrs = pinclattrs;
	n->row = prow;
	n->col = pcol;
	return(n);
}

Including	CpIncluding(old)
	Including old;
{
	return(MkIncluding
		   (
			CpString(old->genattr),
			CpInteger(old->genattrid),
			CpSEQSymbattr(old->inclattrs),
			CpInteger(old->row),
			CpInteger(old->col)
		   )
	      );
}

Constit	MkConstit (pgenattr, psingle, psubtree, pconstattrs, prow, pcol)
	String pgenattr;
	Integer psingle;
	Integer psubtree;
	SEQSymbattr pconstattrs;
	Integer prow;
	Integer pcol;
{
	Constit n;

	n = NConstit;
	n->genattr = pgenattr;
	n->single = psingle;
	n->subtree = psubtree;
	n->constattrs = pconstattrs;
	n->row = prow;
	n->col = pcol;
	return(n);
}

Constit	CpConstit(old)
	Constit old;
{
	return(MkConstit
		   (
			CpString(old->genattr),
			CpInteger(old->single),
			CpInteger(old->subtree),
			CpSEQSymbattr(old->constattrs),
			CpInteger(old->row),
			CpInteger(old->col)
		   )
	      );
}

Symbattr	MkSymbattr (psymbdef, pattrdef)
	Integer psymbdef;
	Integer pattrdef;
{
	Symbattr n;

	n = NSymbattr;
	n->symbdef = psymbdef;
	n->attrdef = pattrdef;
	return(n);
}

Symbattr	CpSymbattr(old)
	Symbattr old;
{
	return(MkSymbattr
		   (
			CpInteger(old->symbdef),
			CpInteger(old->attrdef)
		   )
	      );
}


SEQDef CpSEQDef(old)
SEQDef old;
{
	SEQDef cp;
	Def  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQDef(old, first);
	first = CpDef(first);
	cp = CpSEQDef(tailSEQDef(old));
	return(appendfrontSEQDef(cp, first));
}

SEQAttribution CpSEQAttribution(old)
SEQAttribution old;
{
	SEQAttribution cp;
	Attribution  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQAttribution(old, first);
	first = CpAttribution(first);
	cp = CpSEQAttribution(tailSEQAttribution(old));
	return(appendfrontSEQAttribution(cp, first));
}

SEQAttrdef CpSEQAttrdef(old)
SEQAttrdef old;
{
	SEQAttrdef cp;
	Attrdef  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQAttrdef(old, first);
	first = CpAttrdef(first);
	cp = CpSEQAttrdef(tailSEQAttrdef(old));
	return(appendfrontSEQAttrdef(cp, first));
}

SEQEntity CpSEQEntity(old)
SEQEntity old;
{
	SEQEntity cp;
	Entity  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQEntity(old, first);
	first = CpEntity(first);
	cp = CpSEQEntity(tailSEQEntity(old));
	return(appendfrontSEQEntity(cp, first));
}

SEQUnit CpSEQUnit(old)
SEQUnit old;
{
	SEQUnit cp;
	Unit  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQUnit(old, first);
	first = CpUnit(first);
	cp = CpSEQUnit(tailSEQUnit(old));
	return(appendfrontSEQUnit(cp, first));
}

SEQAttrrule CpSEQAttrrule(old)
SEQAttrrule old;
{
	SEQAttrrule cp;
	Attrrule  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQAttrrule(old, first);
	first = CpAttrrule(first);
	cp = CpSEQAttrrule(tailSEQAttrrule(old));
	return(appendfrontSEQAttrrule(cp, first));
}

SEQInteger CpSEQInteger(old)
SEQInteger old;
{
	SEQInteger cp;
	Integer  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQInteger(old, first);
	first = CpInteger(first);
	cp = CpSEQInteger(tailSEQInteger(old));
	return(appendfrontSEQInteger(cp, first));
}

SEQString CpSEQString(old)
SEQString old;
{
	SEQString cp;
	String  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQString(old, first);
	first = CpString(first);
	cp = CpSEQString(tailSEQString(old));
	return(appendfrontSEQString(cp, first));
}

SEQExpr CpSEQExpr(old)
SEQExpr old;
{
	SEQExpr cp;
	Expr  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQExpr(old, first);
	first = CpExpr(first);
	cp = CpSEQExpr(tailSEQExpr(old));
	return(appendfrontSEQExpr(cp, first));
}

SEQSymbattr CpSEQSymbattr(old)
SEQSymbattr old;
{
	SEQSymbattr cp;
	Symbattr  first;

	if (old == NULL)
	  return(NULL);
	retrievefirstSEQSymbattr(old, first);
	first = CpSymbattr(first);
	cp = CpSEQSymbattr(tailSEQSymbattr(old));
	return(appendfrontSEQSymbattr(cp, first));
}



SEQDef AppFrontSEQDef(el, l)
Def el;
SEQDef l;
{
	return(appendfrontSEQDef(l, el));
}

SEQAttribution AppFrontSEQAttribution(el, l)
Attribution el;
SEQAttribution l;
{
	return(appendfrontSEQAttribution(l, el));
}

SEQAttrdef AppFrontSEQAttrdef(el, l)
Attrdef el;
SEQAttrdef l;
{
	return(appendfrontSEQAttrdef(l, el));
}

SEQEntity AppFrontSEQEntity(el, l)
Entity el;
SEQEntity l;
{
	return(appendfrontSEQEntity(l, el));
}

SEQUnit AppFrontSEQUnit(el, l)
Unit el;
SEQUnit l;
{
	return(appendfrontSEQUnit(l, el));
}

SEQAttrrule AppFrontSEQAttrrule(el, l)
Attrrule el;
SEQAttrrule l;
{
	return(appendfrontSEQAttrrule(l, el));
}

SEQInteger AppFrontSEQInteger(el, l)
Integer el;
SEQInteger l;
{
	return(appendfrontSEQInteger(l, el));
}

SEQString AppFrontSEQString(el, l)
String el;
SEQString l;
{
	return(appendfrontSEQString(l, el));
}

SEQExpr AppFrontSEQExpr(el, l)
Expr el;
SEQExpr l;
{
	return(appendfrontSEQExpr(l, el));
}

SEQSymbattr AppFrontSEQSymbattr(el, l)
Symbattr el;
SEQSymbattr l;
{
	return(appendfrontSEQSymbattr(l, el));
}



SEQDef creatSEQDef(el)
Def el;
{
	SEQDef	l;

	initializeSEQDef(l);
	return(appendfrontSEQDef(l, el));
}

SEQAttribution creatSEQAttribution(el)
Attribution el;
{
	SEQAttribution	l;

	initializeSEQAttribution(l);
	return(appendfrontSEQAttribution(l, el));
}

SEQAttrdef creatSEQAttrdef(el)
Attrdef el;
{
	SEQAttrdef	l;

	initializeSEQAttrdef(l);
	return(appendfrontSEQAttrdef(l, el));
}

SEQEntity creatSEQEntity(el)
Entity el;
{
	SEQEntity	l;

	initializeSEQEntity(l);
	return(appendfrontSEQEntity(l, el));
}

SEQUnit creatSEQUnit(el)
Unit el;
{
	SEQUnit	l;

	initializeSEQUnit(l);
	return(appendfrontSEQUnit(l, el));
}

SEQAttrrule creatSEQAttrrule(el)
Attrrule el;
{
	SEQAttrrule	l;

	initializeSEQAttrrule(l);
	return(appendfrontSEQAttrrule(l, el));
}

SEQInteger creatSEQInteger(el)
Integer el;
{
	SEQInteger	l;

	initializeSEQInteger(l);
	return(appendfrontSEQInteger(l, el));
}

SEQString creatSEQString(el)
String el;
{
	SEQString	l;

	initializeSEQString(l);
	return(appendfrontSEQString(l, el));
}

SEQExpr creatSEQExpr(el)
Expr el;
{
	SEQExpr	l;

	initializeSEQExpr(l);
	return(appendfrontSEQExpr(l, el));
}

SEQSymbattr creatSEQSymbattr(el)
Symbattr el;
{
	SEQSymbattr	l;

	initializeSEQSymbattr(l);
	return(appendfrontSEQSymbattr(l, el));
}



SEQDef concatSEQDef(l1, l2)
SEQDef l1, l2;
{
	SEQDef	help;

	if ( l1 == (SEQDef)NULL )
		return(l2);
	if ( l2 == (SEQDef)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQDef( tailSEQDef(l1) ) )
		l1 = tailSEQDef(l1);
	l1->next = copySEQDef(l2); /* dependent on the generated C types */
	return(help);
}

SEQAttribution concatSEQAttribution(l1, l2)
SEQAttribution l1, l2;
{
	SEQAttribution	help;

	if ( l1 == (SEQAttribution)NULL )
		return(l2);
	if ( l2 == (SEQAttribution)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQAttribution( tailSEQAttribution(l1) ) )
		l1 = tailSEQAttribution(l1);
	l1->next = copySEQAttribution(l2); /* dependent on the generated C types */
	return(help);
}

SEQAttrdef concatSEQAttrdef(l1, l2)
SEQAttrdef l1, l2;
{
	SEQAttrdef	help;

	if ( l1 == (SEQAttrdef)NULL )
		return(l2);
	if ( l2 == (SEQAttrdef)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQAttrdef( tailSEQAttrdef(l1) ) )
		l1 = tailSEQAttrdef(l1);
	l1->next = copySEQAttrdef(l2); /* dependent on the generated C types */
	return(help);
}

SEQEntity concatSEQEntity(l1, l2)
SEQEntity l1, l2;
{
	SEQEntity	help;

	if ( l1 == (SEQEntity)NULL )
		return(l2);
	if ( l2 == (SEQEntity)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQEntity( tailSEQEntity(l1) ) )
		l1 = tailSEQEntity(l1);
	l1->next = copySEQEntity(l2); /* dependent on the generated C types */
	return(help);
}

SEQUnit concatSEQUnit(l1, l2)
SEQUnit l1, l2;
{
	SEQUnit	help;

	if ( l1 == (SEQUnit)NULL )
		return(l2);
	if ( l2 == (SEQUnit)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQUnit( tailSEQUnit(l1) ) )
		l1 = tailSEQUnit(l1);
	l1->next = copySEQUnit(l2); /* dependent on the generated C types */
	return(help);
}

SEQAttrrule concatSEQAttrrule(l1, l2)
SEQAttrrule l1, l2;
{
	SEQAttrrule	help;

	if ( l1 == (SEQAttrrule)NULL )
		return(l2);
	if ( l2 == (SEQAttrrule)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQAttrrule( tailSEQAttrrule(l1) ) )
		l1 = tailSEQAttrrule(l1);
	l1->next = copySEQAttrrule(l2); /* dependent on the generated C types */
	return(help);
}

SEQInteger concatSEQInteger(l1, l2)
SEQInteger l1, l2;
{
	SEQInteger	help;

	if ( l1 == (SEQInteger)NULL )
		return(l2);
	if ( l2 == (SEQInteger)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQInteger( tailSEQInteger(l1) ) )
		l1 = tailSEQInteger(l1);
	l1->next = copySEQInteger(l2); /* dependent on the generated C types */
	return(help);
}

SEQString concatSEQString(l1, l2)
SEQString l1, l2;
{
	SEQString	help;

	if ( l1 == (SEQString)NULL )
		return(l2);
	if ( l2 == (SEQString)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQString( tailSEQString(l1) ) )
		l1 = tailSEQString(l1);
	l1->next = copySEQString(l2); /* dependent on the generated C types */
	return(help);
}

SEQExpr concatSEQExpr(l1, l2)
SEQExpr l1, l2;
{
	SEQExpr	help;

	if ( l1 == (SEQExpr)NULL )
		return(l2);
	if ( l2 == (SEQExpr)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQExpr( tailSEQExpr(l1) ) )
		l1 = tailSEQExpr(l1);
	l1->next = copySEQExpr(l2); /* dependent on the generated C types */
	return(help);
}

SEQSymbattr concatSEQSymbattr(l1, l2)
SEQSymbattr l1, l2;
{
	SEQSymbattr	help;

	if ( l1 == (SEQSymbattr)NULL )
		return(l2);
	if ( l2 == (SEQSymbattr)NULL )
		return(l1);
	help = l1;
	while ( !emptySEQSymbattr( tailSEQSymbattr(l1) ) )
		l1 = tailSEQSymbattr(l1);
	l1->next = copySEQSymbattr(l2); /* dependent on the generated C types */
	return(help);
}

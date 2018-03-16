/* $Id: liga_func.h,v 4.1 1997/08/29 08:26:49 peter Exp $ */
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

#ifndef LIGA_FUNC_H
#define LIGA_FUNC_H

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

extern AttrEval  MkAttrEval(/* SEQDef pdefseq,
                               SEQAttribution pattrrules
                           */);
extern AttrEval  CpAttrEval(/* AttrEval old */);

extern Def  CpDef(/* Def old */);
#define KDef  KChain:; case KTypedef:; case KSymb:; case KProd
extern Def  MkDef(/* Integer pdid,
                     String pdname,
                     Integer prow,
                     Integer pcol
                     Def n
                 */);
extern Def  Cpattr_Def(/* Def old,new */);

extern Chain  MkChain(/* Integer ptypeid */);
extern Chain  CpChain(/* Chain old */);

extern Typedef  MkTypedef(/* String pextname,
                             Integer plistedto
                         */);
extern Typedef  CpTypedef(/* Typedef old */);

extern Symb  MkSymb(/* Integer ptornt,
                       SEQAttrdef pattrs
                   */);
extern Symb  CpSymb(/* Symb old */);

extern Attrdef  MkAttrdef(/* Integer pdid,
                             String pname,
                             Integer prow,
                             Integer pcol,
                             Integer ptypeid,
                             Integer pclass,
                             Integer pprodid,
                             Integer pstore,
                             Integer pgen,
                             Integer ppart,
                             String pglobname
                         */);
extern Attrdef  CpAttrdef(/* Attrdef old */);

extern Prod  MkProd(/* Integer plhs,
                       SEQEntity prhs
                   */);
extern Prod  CpProd(/* Prod old */);

extern Entity  CpEntity(/* Entity old */);
#define KEntity  KUnit:; case KOpt:; case KStar:; case KPlus:; case KDelim:; case KDelopt
#define  Cpattr_Entity(old,new)   (new)

extern Unit  CpUnit(/* Unit old */);
#define KUnit  KSymbol:; case KLiteral
extern Unit  MkUnit(/* Integer prow,
                       Integer pcol
                       Unit n
                   */);
extern Unit  Cpattr_Unit(/* Unit old,new */);

extern Symbol  MkSymbol(/* Integer pdid */);
extern Symbol  CpSymbol(/* Symbol old */);

extern Literal  MkLiteral(/* String pstr */);
extern Literal  CpLiteral(/* Literal old */);

extern Opt  MkOpt(/* SEQUnit prhs */);
extern Opt  CpOpt(/* Opt old */);

extern Star  MkStar(/* SEQUnit prhs */);
extern Star  CpStar(/* Star old */);

extern Plus  MkPlus(/* SEQUnit prhs */);
extern Plus  CpPlus(/* Plus old */);

extern Delim  MkDelim(/* SEQUnit prhs,
                         Literal pdel
                     */);
extern Delim  CpDelim(/* Delim old */);

extern Delopt  MkDelopt(/* SEQUnit prhs,
                           Literal pdel
                       */);
extern Delopt  CpDelopt(/* Delopt old */);

extern Attribution  MkAttribution(/* Integer pprodid,
                                     SEQAttrrule pattrrules
                                 */);
extern Attribution  CpAttribution(/* Attribution old */);

extern Attrrule  CpAttrrule(/* Attrrule old */);
#define KAttrrule  KCall:; case KVisit:; case KTransfer:; case KChainStart
#define  Cpattr_Attrrule(old,new)   (new)

extern ChainStart  MkChainStart(/* Integer pchainid,
                                   String ppregenattr,
                                   String ppostgenattr,
                                   Integer prow,
                                   Integer pcol
                               */);
extern ChainStart  CpChainStart(/* ChainStart old */);

extern Visit  MkVisit(/* Integer psymbno,
                         Integer pord
                     */);
extern Visit  CpVisit(/* Visit old */);

extern Transfer  MkTransfer(/* SEQInteger psymbno,
                               SEQString pattrs,
                               Integer prow,
                               Integer pcol
                           */);
extern Transfer  CpTransfer(/* Transfer old */);

extern Call  MkCall(/* String pname,
                       SEQExpr pparams,
                       Integer prow,
                       Integer pcol
                   */);
extern Call  CpCall(/* Call old */);

extern Expr  CpExpr(/* Expr old */);
#define KExpr  KCall:; case KLiteral:; case KVal:; case KName:; case KAttracc:; case KChainacc:; case KConstit:; case KIncluding
#define  Cpattr_Expr(old,new)   (new)

extern Val  MkVal(/* Integer pv,
                     Integer prow,
                     Integer pcol
                 */);
extern Val  CpVal(/* Val old */);

extern Name  MkName(/* String pn,
                       Integer prow,
                       Integer pcol
                   */);
extern Name  CpName(/* Name old */);

extern Attracc  MkAttracc(/* Integer psymbno,
                             Integer pattrid,
                             Integer prow,
                             Integer pcol
                         */);
extern Attracc  CpAttracc(/* Attracc old */);

extern Chainacc  MkChainacc(/* Integer psymbno,
                               Integer pchainid,
                               Integer prow,
                               Integer pcol
                           */);
extern Chainacc  CpChainacc(/* Chainacc old */);

extern Including  MkIncluding(/* String pgenattr,
                                 Integer pgenattrid,
                                 SEQSymbattr pinclattrs,
                                 Integer prow,
                                 Integer pcol
                             */);
extern Including  CpIncluding(/* Including old */);

extern Constit  MkConstit(/* String pgenattr,
                             Integer psingle,
                             Integer psubtree,
                             SEQSymbattr pconstattrs,
                             Integer prow,
                             Integer pcol
                         */);
extern Constit  CpConstit(/* Constit old */);

extern Symbattr  MkSymbattr(/* Integer psymbdef,
                               Integer pattrdef
                           */);
extern Symbattr  CpSymbattr(/* Symbattr old */);

extern SEQDef	CpSEQDef(/* SEQDef old */);
extern SEQAttribution	CpSEQAttribution(/* SEQAttribution old */);
extern SEQAttrdef	CpSEQAttrdef(/* SEQAttrdef old */);
extern SEQEntity	CpSEQEntity(/* SEQEntity old */);
extern SEQUnit	CpSEQUnit(/* SEQUnit old */);
extern SEQAttrrule	CpSEQAttrrule(/* SEQAttrrule old */);
extern SEQInteger	CpSEQInteger(/* SEQInteger old */);
extern SEQString	CpSEQString(/* SEQString old */);
extern SEQExpr	CpSEQExpr(/* SEQExpr old */);
extern SEQSymbattr	CpSEQSymbattr(/* SEQSymbattr old */);


extern SEQDef	AppFrontSEQDef(/* Def el, SEQDef l */);
extern SEQAttribution	AppFrontSEQAttribution(/* Attribution el, SEQAttribution l */);
extern SEQAttrdef	AppFrontSEQAttrdef(/* Attrdef el, SEQAttrdef l */);
extern SEQEntity	AppFrontSEQEntity(/* Entity el, SEQEntity l */);
extern SEQUnit	AppFrontSEQUnit(/* Unit el, SEQUnit l */);
extern SEQAttrrule	AppFrontSEQAttrrule(/* Attrrule el, SEQAttrrule l */);
extern SEQInteger	AppFrontSEQInteger(/* Integer el, SEQInteger l */);
extern SEQString	AppFrontSEQString(/* String el, SEQString l */);
extern SEQExpr	AppFrontSEQExpr(/* Expr el, SEQExpr l */);
extern SEQSymbattr	AppFrontSEQSymbattr(/* Symbattr el, SEQSymbattr l */);


#define	 nullSEQDef()	((SEQDef)NULL)
#define	 nullSEQAttribution()	((SEQAttribution)NULL)
#define	 nullSEQAttrdef()	((SEQAttrdef)NULL)
#define	 nullSEQEntity()	((SEQEntity)NULL)
#define	 nullSEQUnit()	((SEQUnit)NULL)
#define	 nullSEQAttrrule()	((SEQAttrrule)NULL)
#define	 nullSEQInteger()	((SEQInteger)NULL)
#define	 nullSEQString()	((SEQString)NULL)
#define	 nullSEQExpr()	((SEQExpr)NULL)
#define	 nullSEQSymbattr()	((SEQSymbattr)NULL)


extern SEQDef	creatSEQDef(/* Def el */);
extern SEQAttribution	creatSEQAttribution(/* Attribution el */);
extern SEQAttrdef	creatSEQAttrdef(/* Attrdef el */);
extern SEQEntity	creatSEQEntity(/* Entity el */);
extern SEQUnit	creatSEQUnit(/* Unit el */);
extern SEQAttrrule	creatSEQAttrrule(/* Attrrule el */);
extern SEQInteger	creatSEQInteger(/* Integer el */);
extern SEQString	creatSEQString(/* String el */);
extern SEQExpr	creatSEQExpr(/* Expr el */);
extern SEQSymbattr	creatSEQSymbattr(/* Symbattr el */);


extern SEQDef	concatSEQDef(/* SEQDef l1, l2 */);
extern SEQAttribution	concatSEQAttribution(/* SEQAttribution l1, l2 */);
extern SEQAttrdef	concatSEQAttrdef(/* SEQAttrdef l1, l2 */);
extern SEQEntity	concatSEQEntity(/* SEQEntity l1, l2 */);
extern SEQUnit	concatSEQUnit(/* SEQUnit l1, l2 */);
extern SEQAttrrule	concatSEQAttrrule(/* SEQAttrrule l1, l2 */);
extern SEQInteger	concatSEQInteger(/* SEQInteger l1, l2 */);
extern SEQString	concatSEQString(/* SEQString l1, l2 */);
extern SEQExpr	concatSEQExpr(/* SEQExpr l1, l2 */);
extern SEQSymbattr	concatSEQSymbattr(/* SEQSymbattr l1, l2 */);

#endif

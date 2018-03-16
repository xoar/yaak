/* $Id: LIGAMacros.h,v 4.1 1997/08/29 08:26:49 peter Exp $ */
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
#ifndef LIGAMACROS_H
#define LIGAMACROS_H

/* Class Attribute accessing macros */

#define didOfDef(ADef) ADef.IDLclassCommon->did
#define dnameOfDef(ADef) ADef.IDLclassCommon->dname
#define rowOfDef(ADef) ADef.IDLclassCommon->row
#define colOfDef(ADef) ADef.IDLclassCommon->col
#define rowOfUnit(AUnit) AUnit.IDLclassCommon->row
#define colOfUnit(AUnit) AUnit.IDLclassCommon->col

/* Node Attribute  accessing macros */

#define attrrulesOfAttrEval(AAttrEval) AAttrEval->attrrules
#define defseqOfAttrEval(AAttrEval) AAttrEval->defseq
#define colOfAttracc(AAttracc) AAttracc->col
#define rowOfAttracc(AAttracc) AAttracc->row
#define attridOfAttracc(AAttracc) AAttracc->attrid
#define symbnoOfAttracc(AAttracc) AAttracc->symbno
#define globnameOfAttrdef(AAttrdef) AAttrdef->globname
#define partOfAttrdef(AAttrdef) AAttrdef->part
#define genOfAttrdef(AAttrdef) AAttrdef->gen
#define storeOfAttrdef(AAttrdef) AAttrdef->store
#define prodidOfAttrdef(AAttrdef) AAttrdef->prodid
#define classOfAttrdef(AAttrdef) AAttrdef->class
#define typeidOfAttrdef(AAttrdef) AAttrdef->typeid
#define colOfAttrdef(AAttrdef) AAttrdef->col
#define rowOfAttrdef(AAttrdef) AAttrdef->row
#define nameOfAttrdef(AAttrdef) AAttrdef->name
#define didOfAttrdef(AAttrdef) AAttrdef->did
#define attrrulesOfAttribution(AAttribution) AAttribution->attrrules
#define prodidOfAttribution(AAttribution) AAttribution->prodid
#define colOfCall(ACall) ACall->col
#define rowOfCall(ACall) ACall->row
#define paramsOfCall(ACall) ACall->params
#define nameOfCall(ACall) ACall->name
#define didOfChain(AChain) AChain->did
#define dnameOfChain(AChain) AChain->dname
#define rowOfChain(AChain) AChain->row
#define colOfChain(AChain) AChain->col
#define typeidOfChain(AChain) AChain->typeid
#define colOfChainStart(AChainStart) AChainStart->col
#define rowOfChainStart(AChainStart) AChainStart->row
#define postgenattrOfChainStart(AChainStart) AChainStart->postgenattr
#define pregenattrOfChainStart(AChainStart) AChainStart->pregenattr
#define chainidOfChainStart(AChainStart) AChainStart->chainid
#define colOfChainacc(AChainacc) AChainacc->col
#define rowOfChainacc(AChainacc) AChainacc->row
#define chainidOfChainacc(AChainacc) AChainacc->chainid
#define symbnoOfChainacc(AChainacc) AChainacc->symbno
#define colOfConstit(AConstit) AConstit->col
#define rowOfConstit(AConstit) AConstit->row
#define constattrsOfConstit(AConstit) AConstit->constattrs
#define subtreeOfConstit(AConstit) AConstit->subtree
#define singleOfConstit(AConstit) AConstit->single
#define genattrOfConstit(AConstit) AConstit->genattr
#define delOfDelim(ADelim) ADelim->del
#define rhsOfDelim(ADelim) ADelim->rhs
#define delOfDelopt(ADelopt) ADelopt->del
#define rhsOfDelopt(ADelopt) ADelopt->rhs
#define colOfIncluding(AIncluding) AIncluding->col
#define rowOfIncluding(AIncluding) AIncluding->row
#define inclattrsOfIncluding(AIncluding) AIncluding->inclattrs
#define genattridOfIncluding(AIncluding) AIncluding->genattrid
#define genattrOfIncluding(AIncluding) AIncluding->genattr
#define rowOfLiteral(ALiteral) ALiteral->row
#define colOfLiteral(ALiteral) ALiteral->col
#define strOfLiteral(ALiteral) ALiteral->str
#define colOfName(AName) AName->col
#define rowOfName(AName) AName->row
#define nOfName(AName) AName->n
#define rhsOfOpt(AOpt) AOpt->rhs
#define rhsOfPlus(APlus) APlus->rhs
#define didOfProd(AProd) AProd->did
#define dnameOfProd(AProd) AProd->dname
#define rowOfProd(AProd) AProd->row
#define colOfProd(AProd) AProd->col
#define rhsOfProd(AProd) AProd->rhs
#define lhsOfProd(AProd) AProd->lhs
#define rhsOfStar(AStar) AStar->rhs
#define didOfSymb(ASymb) ASymb->did
#define dnameOfSymb(ASymb) ASymb->dname
#define rowOfSymb(ASymb) ASymb->row
#define colOfSymb(ASymb) ASymb->col
#define attrsOfSymb(ASymb) ASymb->attrs
#define torntOfSymb(ASymb) ASymb->tornt
#define attrdefOfSymbattr(ASymbattr) ASymbattr->attrdef
#define symbdefOfSymbattr(ASymbattr) ASymbattr->symbdef
#define rowOfSymbol(ASymbol) ASymbol->row
#define colOfSymbol(ASymbol) ASymbol->col
#define didOfSymbol(ASymbol) ASymbol->did
#define colOfTransfer(ATransfer) ATransfer->col
#define rowOfTransfer(ATransfer) ATransfer->row
#define attrsOfTransfer(ATransfer) ATransfer->attrs
#define symbnoOfTransfer(ATransfer) ATransfer->symbno
#define didOfTypedef(ATypedef) ATypedef->did
#define dnameOfTypedef(ATypedef) ATypedef->dname
#define rowOfTypedef(ATypedef) ATypedef->row
#define colOfTypedef(ATypedef) ATypedef->col
#define listedtoOfTypedef(ATypedef) ATypedef->listedto
#define extnameOfTypedef(ATypedef) ATypedef->extname
#define colOfVal(AVal) AVal->col
#define rowOfVal(AVal) AVal->row
#define vOfVal(AVal) AVal->v
#define ordOfVisit(AVisit) AVisit->ord
#define symbnoOfVisit(AVisit) AVisit->symbno

/* Widening Conversion macros */

extern Def IDLtempDef;
#define ChainToDef(AChain) \
	(IDLtempDef.VChain = AChain, IDLtempDef)
#define TypedefToDef(ATypedef) \
	(IDLtempDef.VTypedef = ATypedef, IDLtempDef)
#define SymbToDef(ASymb) \
	(IDLtempDef.VSymb = ASymb, IDLtempDef)
#define ProdToDef(AProd) \
	(IDLtempDef.VProd = AProd, IDLtempDef)

extern Unit IDLtempUnit;
#define SymbolToUnit(ASymbol) \
	(IDLtempUnit.VSymbol = ASymbol, IDLtempUnit)
#define LiteralToUnit(ALiteral) \
	(IDLtempUnit.VLiteral = ALiteral, IDLtempUnit)

extern Entity IDLtempEntity;
#define UnitToEntity(AUnit) \
	(IDLtempEntity.VUnit = AUnit, IDLtempEntity)
#define LiteralToEntity(ALiteral) \
	(IDLtempEntity.VLiteral = ALiteral, IDLtempEntity)
#define SymbolToEntity(ASymbol) \
	(IDLtempEntity.VSymbol = ASymbol, IDLtempEntity)
#define OptToEntity(AOpt) \
	(IDLtempEntity.VOpt = AOpt, IDLtempEntity)
#define StarToEntity(AStar) \
	(IDLtempEntity.VStar = AStar, IDLtempEntity)
#define PlusToEntity(APlus) \
	(IDLtempEntity.VPlus = APlus, IDLtempEntity)
#define DelimToEntity(ADelim) \
	(IDLtempEntity.VDelim = ADelim, IDLtempEntity)
#define DeloptToEntity(ADelopt) \
	(IDLtempEntity.VDelopt = ADelopt, IDLtempEntity)

extern Attrrule IDLtempAttrrule;
#define CallToAttrrule(ACall) \
	(IDLtempAttrrule.VCall = ACall, IDLtempAttrrule)
#define VisitToAttrrule(AVisit) \
	(IDLtempAttrrule.VVisit = AVisit, IDLtempAttrrule)
#define TransferToAttrrule(ATransfer) \
	(IDLtempAttrrule.VTransfer = ATransfer, IDLtempAttrrule)
#define ChainStartToAttrrule(AChainStart) \
	(IDLtempAttrrule.VChainStart = AChainStart, IDLtempAttrrule)

extern Expr IDLtempExpr;
#define CallToExpr(ACall) \
	(IDLtempExpr.VCall = ACall, IDLtempExpr)
#define LiteralToExpr(ALiteral) \
	(IDLtempExpr.VLiteral = ALiteral, IDLtempExpr)
#define ValToExpr(AVal) \
	(IDLtempExpr.VVal = AVal, IDLtempExpr)
#define NameToExpr(AName) \
	(IDLtempExpr.VName = AName, IDLtempExpr)
#define AttraccToExpr(AAttracc) \
	(IDLtempExpr.VAttracc = AAttracc, IDLtempExpr)
#define ChainaccToExpr(AChainacc) \
	(IDLtempExpr.VChainacc = AChainacc, IDLtempExpr)
#define ConstitToExpr(AConstit) \
	(IDLtempExpr.VConstit = AConstit, IDLtempExpr)
#define IncludingToExpr(AIncluding) \
	(IDLtempExpr.VIncluding = AIncluding, IDLtempExpr)


/* Narrowing Conversion macros */

#define DefToTypedef(ADef)              (ADef.VTypedef)
#define DefToSymb(ADef)                 (ADef.VSymb)
#define DefToProd(ADef)                 (ADef.VProd)
#define DefToChain(ADef)                (ADef.VChain)
#define UnitToSymbol(AUnit)             (AUnit.VSymbol)
#define UnitToLiteral(AUnit)            (AUnit.VLiteral)
#define EntityToUnit(AEntity)           (AEntity.VUnit)
#define EntityToLiteral(AEntity)        (AEntity.VLiteral)
#define EntityToSymbol(AEntity)         (AEntity.VSymbol)
#define EntityToOpt(AEntity)            (AEntity.VOpt)
#define EntityToStar(AEntity)           (AEntity.VStar)
#define EntityToPlus(AEntity)           (AEntity.VPlus)
#define EntityToDelim(AEntity)          (AEntity.VDelim)
#define EntityToDelopt(AEntity)         (AEntity.VDelopt)
#define AttrruleToCall(AAttrrule)       (AAttrrule.VCall)
#define AttrruleToVisit(AAttrrule)      (AAttrrule.VVisit)
#define AttrruleToTransfer(AAttrrule)   (AAttrrule.VTransfer)
#define AttrruleToChainStart(AAttrrule) (AAttrrule.VChainStart)
#define ExprToCall(AExpr)               (AExpr.VCall)
#define ExprToLiteral(AExpr)            (AExpr.VLiteral)
#define ExprToVal(AExpr)                (AExpr.VVal)
#define ExprToName(AExpr)               (AExpr.VName)
#define ExprToAttracc(AExpr)            (AExpr.VAttracc)
#define ExprToChainacc(AExpr)           (AExpr.VChainacc)
#define ExprToConstit(AExpr)            (AExpr.VConstit)
#define ExprToIncluding(AExpr)          (AExpr.VIncluding)

#endif

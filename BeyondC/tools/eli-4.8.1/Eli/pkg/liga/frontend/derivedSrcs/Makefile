SHELL   = /bin/sh

CC	= gcc

OBJS	= driver.o clpintf.o clp.o csm.o obsave.o deftbl.o err.o \
	source.o pdl_gen.o DefTableKeyList.o clplib.o AlgScope.o \
	envmod.o BitSet.o PreDefId.o IdentTerm.o PreDefMod.o idn.o \
	treecon.o nodecode.o treebuild.o parser.o treestack.o \
	scanswitch.o pascalStr.o glahead.o auxNUL.o auxEOF.o \
	dflteot.o tabsize.o Cint.o p_mkstr.o str.o auxScanEOL.o \
	CchStr.o pascalCom.o Ccomment.o dfltrepar.o attrmain.o \
	visitprocs.o visitmap.o Strings.o CompRepr.o DynSpace.o \
	PExprList.o Remote.o SymbAttrList.o SymbolUses.o \
	GrammarRules.o ProdSymbolList.o RuleProdList.o Prod.o \
	MakeName.o ShieldSet.o Accumulate.o InheritRepr.o Compute.o \
	ptg_gen.o PtgCommon.o Indent.o IdlStringOut.o SymbolOcc.o \
	Attribute.o RemoteSet.o SymbAttr.o Grammar.o Inherit.o \
	Predefined.o RuleOutput.o SymbolOutput.o CheckRuleComps.o \
	RemoteOut.o DefsOut.o ReprOut.o CompOut.o obstack.o

EXE	= Lido.exe

all:	$(EXE)

$(EXE):	$(OBJS) ../../idl/IDL.a
	$(CC) -o $(EXE) $(CFLAGS) $(OBJS) ../../idl/IDL.a $(LIBS)

objects: $(OBJS) ../../idl/IDL.a

clean:
	rm -f a.out *.o *.a *~ core ERRS $(EXE)

tidy:
	rm -f core a.out *.o *~ *.a ERRS

driver.o:	driver.c err.h HEAD.h INIT.h FINL.h eliproto.h clp.h \
		Strings.h envmod.h deftbl.h BitSet.h AlgScope.h CoordCmp.h \
		ProdSymbolList.h DynSpace.h RuleProdList.h MakeName.h \
		DefTableKeyList.h Indent.h PreDefMod.h PreDefId.h \
		SymbAttrList.h PExprList.h scanswitch.h GrammarRules.h \
		RuleOutput.h source.h Grammar.h Attribute.h Inherit.h \
		SymbolOcc.h SymbolOutput.h SymbolUses.h Predefined.h \
		Compute.h ShieldSet.h RemoteSet.h Remote.h RemoteOut.h \
		CheckRuleComps.h CompRepr.h InheritRepr.h ReprOut.h \
		DefsOut.h CompOut.h IdlStringOut.h Accumulate.h ptg_gen.h \
		pdl_gen.h treecon.h VoidPtrList.h PtgCommon.h clplib.h \
		RuleProd.h ExprRepr.h args.h Prod.h \
		ProdSymbolFunctionTypes.h obstack.h \
		DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h csm.h \
		RuleProdFunctionTypes.h ptg.h PreDefId.d.h \
		ComputationRepr.h nodeptr.h VoidPtr.h \
		VoidPtrFunctionTypes.h

clpintf.o:	clpintf.c clpintf.h eliproto.h

clp.o:	clp.c clp.h clpintf.h pdl_gen.h csm.h eliproto.h clplib.h \
		DefTableKeyList.h deftbl.h CoordCmp.h err.h RuleProd.h \
		envmod.h SymbAttrList.h ExprRepr.h PExprList.h args.h \
		ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h obstack.h \
		BitSet.h DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h

csm.o:	csm.c csm.h csmtbl.h obsave.h obstack.h eliproto.h

obsave.o:	obsave.c obsave.h obstack.h eliproto.h

deftbl.o:	deftbl.c err.h deftbl.h obstack.h obsave.h eliproto.h

err.o:	err.c err.h source.h eliproto.h

source.o:	source.c source.h

pdl_gen.o:	pdl_gen.c pdl_gen.h deftbl.h CoordCmp.h err.h RuleProd.h \
		envmod.h DefTableKeyList.h SymbAttrList.h ExprRepr.h \
		PExprList.h eliproto.h args.h ProdSymbolList.h Prod.h \
		ProdSymbolFunctionTypes.h obstack.h BitSet.h \
		DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h

DefTableKeyList.o:	DefTableKeyList.c DefTableKeyList.h err.h obstack.h \
		deftbl.h DefTableKeyFunctionTypes.h eliproto.h

clplib.o:	clplib.c csm.h clplib.h obstack.h eliproto.h

AlgScope.o:	AlgScope.c AlgScope.h envmod.h deftbl.h obstack.h BitSet.h \
		eliproto.h

envmod.o:	envmod.c err.h obstack.h envmod.h obsave.h eliproto.h \
		deftbl.h BitSet.h

BitSet.o:	BitSet.c obstack.h err.h BitSet.h eliproto.h

PreDefId.o:	PreDefId.c IdentTerm.h PreDefMod.h PreDefId.h pdl_gen.h \
		PreDefId.d.h eliproto.h envmod.h deftbl.h obstack.h \
		BitSet.h CoordCmp.h err.h RuleProd.h DefTableKeyList.h \
		SymbAttrList.h ExprRepr.h PExprList.h args.h \
		ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h \
		DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h

IdentTerm.o:	IdentTerm.c termcode.h IdentTerm.h

PreDefMod.o:	PreDefMod.c idn.h PreDefMod.h eliproto.h envmod.h deftbl.h \
		obstack.h BitSet.h

idn.o:	idn.c err.h idn.h csm.h obstack.h obsave.h idntbl.h \
		eliproto.h

treecon.o:	treecon.c node.h nodecode.h attrpredef.h visitmap.h \
		treeact.h obstack.h err.h nodeptr.h HEAD.h eliproto.h clp.h \
		Strings.h envmod.h deftbl.h BitSet.h AlgScope.h CoordCmp.h \
		ProdSymbolList.h DynSpace.h RuleProdList.h MakeName.h \
		DefTableKeyList.h Indent.h PreDefMod.h PreDefId.h \
		SymbAttrList.h PExprList.h scanswitch.h GrammarRules.h \
		RuleOutput.h source.h Grammar.h Attribute.h Inherit.h \
		SymbolOcc.h SymbolOutput.h SymbolUses.h Predefined.h \
		Compute.h ShieldSet.h RemoteSet.h Remote.h RemoteOut.h \
		CheckRuleComps.h CompRepr.h InheritRepr.h ReprOut.h \
		DefsOut.h CompOut.h IdlStringOut.h Accumulate.h ptg_gen.h \
		pdl_gen.h treecon.h VoidPtrList.h PtgCommon.h clplib.h \
		RuleProd.h ExprRepr.h args.h Prod.h \
		ProdSymbolFunctionTypes.h DefTableKeyFunctionTypes.h \
		SymbAttr.h SymbAttrFunctionTypes.h PExprFunctionTypes.h \
		csm.h RuleProdFunctionTypes.h ptg.h PreDefId.d.h \
		ComputationRepr.h VoidPtr.h VoidPtrFunctionTypes.h

nodecode.o:	nodecode.c nodecode.h

treebuild.o:	treebuild.c eliproto.h pdl_gen.h source.h csm.h clp.h \
		clpintf.h deftbl.h CoordCmp.h err.h RuleProd.h envmod.h \
		DefTableKeyList.h SymbAttrList.h ExprRepr.h PExprList.h \
		args.h ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h \
		obstack.h BitSet.h DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h clplib.h

parser.o:	parser.c err.h treestack.h gsdescr.h HEAD.h reparatur.h \
		gla.h parser.h semprods.h ptabs.h eliproto.h nodeptr.h \
		parsops.h clp.h Strings.h envmod.h deftbl.h BitSet.h \
		AlgScope.h CoordCmp.h ProdSymbolList.h DynSpace.h \
		RuleProdList.h MakeName.h DefTableKeyList.h Indent.h \
		PreDefMod.h PreDefId.h SymbAttrList.h PExprList.h \
		scanswitch.h GrammarRules.h RuleOutput.h source.h Grammar.h \
		Attribute.h Inherit.h SymbolOcc.h SymbolOutput.h \
		SymbolUses.h Predefined.h Compute.h ShieldSet.h RemoteSet.h \
		Remote.h RemoteOut.h CheckRuleComps.h CompRepr.h \
		InheritRepr.h ReprOut.h DefsOut.h CompOut.h IdlStringOut.h \
		Accumulate.h ptg_gen.h pdl_gen.h treecon.h VoidPtrList.h \
		PtgCommon.h clplib.h RuleProd.h ExprRepr.h args.h Prod.h \
		ProdSymbolFunctionTypes.h obstack.h \
		DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h csm.h \
		RuleProdFunctionTypes.h ptg.h PreDefId.d.h \
		ComputationRepr.h VoidPtr.h VoidPtrFunctionTypes.h

treestack.o:	treestack.c err.h treestack.h eliproto.h nodeptr.h

scanswitch.o:	scanswitch.c scanswitch.h args.h

pascalStr.o:	pascalStr.c err.h gla.h tabsize.h eliproto.h

glahead.o:	glahead.c err.h csm.h source.h obstack.h scanops.h \
		tabsize.h ScanProc.h gla.h xtables.h xcode.h eliproto.h

auxNUL.o:	auxNUL.c source.h gla.h

auxEOF.o:	auxEOF.c 

dflteot.o:	dflteot.c 

tabsize.o:	tabsize.c 

Cint.o:	Cint.c err.h eliproto.h

p_mkstr.o:	p_mkstr.c csm.h p_mkstr.h obstack.h eliproto.h args.h

str.o:	str.c csm.h obstack.h eliproto.h

auxScanEOL.o:	auxScanEOL.c eliproto.h err.h gla.h source.h ScanProc.h

CchStr.o:	CchStr.c err.h source.h gla.h csm.h tabsize.h ScanProc.h \
		eliproto.h obstack.h

pascalCom.o:	pascalCom.c err.h gla.h source.h tabsize.h ScanProc.h \
		eliproto.h

Ccomment.o:	Ccomment.c err.h gla.h source.h tabsize.h ScanProc.h \
		eliproto.h

dfltrepar.o:	dfltrepar.c err.h reparatur.h eliproto.h

attrmain.o:	attrmain.c treestack.h visitprocs.h nodeptr.h err.h \
		eliproto.h HEAD.h node.h treecon.h clp.h Strings.h envmod.h \
		deftbl.h BitSet.h AlgScope.h CoordCmp.h ProdSymbolList.h \
		DynSpace.h RuleProdList.h MakeName.h DefTableKeyList.h \
		Indent.h PreDefMod.h PreDefId.h SymbAttrList.h PExprList.h \
		scanswitch.h GrammarRules.h RuleOutput.h source.h Grammar.h \
		Attribute.h Inherit.h SymbolOcc.h SymbolOutput.h \
		SymbolUses.h Predefined.h Compute.h ShieldSet.h RemoteSet.h \
		Remote.h RemoteOut.h CheckRuleComps.h CompRepr.h \
		InheritRepr.h ReprOut.h DefsOut.h CompOut.h IdlStringOut.h \
		Accumulate.h ptg_gen.h pdl_gen.h VoidPtrList.h PtgCommon.h \
		clplib.h RuleProd.h ExprRepr.h args.h Prod.h \
		ProdSymbolFunctionTypes.h obstack.h \
		DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h csm.h \
		RuleProdFunctionTypes.h ptg.h PreDefId.d.h \
		ComputationRepr.h VoidPtr.h VoidPtrFunctionTypes.h

visitprocs.o:	visitprocs.c HEAD.h err.h node.h visitprocs.h attrpredef.h \
		visitmap.h clp.h Strings.h envmod.h deftbl.h BitSet.h \
		AlgScope.h CoordCmp.h ProdSymbolList.h DynSpace.h \
		RuleProdList.h MakeName.h DefTableKeyList.h Indent.h \
		PreDefMod.h PreDefId.h SymbAttrList.h PExprList.h \
		scanswitch.h GrammarRules.h RuleOutput.h source.h Grammar.h \
		Attribute.h Inherit.h SymbolOcc.h SymbolOutput.h \
		SymbolUses.h Predefined.h Compute.h ShieldSet.h RemoteSet.h \
		Remote.h RemoteOut.h CheckRuleComps.h CompRepr.h \
		InheritRepr.h ReprOut.h DefsOut.h CompOut.h IdlStringOut.h \
		Accumulate.h ptg_gen.h pdl_gen.h treecon.h VoidPtrList.h \
		PtgCommon.h clplib.h eliproto.h RuleProd.h ExprRepr.h \
		args.h Prod.h ProdSymbolFunctionTypes.h obstack.h \
		DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h csm.h \
		RuleProdFunctionTypes.h ptg.h PreDefId.d.h \
		ComputationRepr.h nodeptr.h VoidPtr.h \
		VoidPtrFunctionTypes.h

visitmap.o:	visitmap.c visitprocs.h visitmap.h HEAD.h node.h treecon.h \
		eliproto.h clp.h Strings.h envmod.h deftbl.h BitSet.h \
		AlgScope.h err.h CoordCmp.h ProdSymbolList.h DynSpace.h \
		RuleProdList.h MakeName.h DefTableKeyList.h Indent.h \
		PreDefMod.h PreDefId.h SymbAttrList.h PExprList.h \
		scanswitch.h GrammarRules.h RuleOutput.h source.h Grammar.h \
		Attribute.h Inherit.h SymbolOcc.h SymbolOutput.h \
		SymbolUses.h Predefined.h Compute.h ShieldSet.h RemoteSet.h \
		Remote.h RemoteOut.h CheckRuleComps.h CompRepr.h \
		InheritRepr.h ReprOut.h DefsOut.h CompOut.h IdlStringOut.h \
		Accumulate.h ptg_gen.h pdl_gen.h VoidPtrList.h PtgCommon.h \
		clplib.h RuleProd.h ExprRepr.h args.h Prod.h \
		ProdSymbolFunctionTypes.h obstack.h \
		DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h csm.h \
		RuleProdFunctionTypes.h ptg.h PreDefId.d.h \
		ComputationRepr.h nodeptr.h VoidPtr.h \
		VoidPtrFunctionTypes.h

Strings.o:	Strings.c Strings.h csm.h obstack.h eliproto.h

CompRepr.o:	CompRepr.c CompRepr.h pdl_gen.h DynSpace.h csm.h args.h \
		ComputationRepr.h deftbl.h err.h PExprList.h Prod.h \
		eliproto.h ExprRepr.h PExprFunctionTypes.h envmod.h \
		obstack.h BitSet.h CoordCmp.h RuleProd.h DefTableKeyList.h \
		SymbAttrList.h ProdSymbolList.h ProdSymbolFunctionTypes.h \
		DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h

DynSpace.o:	DynSpace.c obstack.h DynSpace.h

PExprList.o:	PExprList.c PExprList.h err.h obstack.h ExprRepr.h \
		PExprFunctionTypes.h eliproto.h

Remote.o:	Remote.c Remote.h pdl_gen.h csm.h DefTableKeyList.h \
		SymbAttrList.h err.h deftbl.h DefTableKeyFunctionTypes.h \
		eliproto.h SymbAttr.h SymbAttrFunctionTypes.h envmod.h \
		args.h obstack.h BitSet.h CoordCmp.h RuleProd.h ExprRepr.h \
		PExprList.h ProdSymbolList.h Prod.h \
		ProdSymbolFunctionTypes.h PExprFunctionTypes.h

SymbAttrList.o:	SymbAttrList.c SymbAttrList.h err.h obstack.h SymbAttr.h \
		SymbAttrFunctionTypes.h envmod.h args.h deftbl.h BitSet.h \
		eliproto.h

SymbolUses.o:	SymbolUses.c SymbolUses.h GrammarRules.h pdl_gen.h args.h \
		envmod.h deftbl.h obstack.h BitSet.h eliproto.h \
		RuleProdList.h RuleProd.h RuleProdFunctionTypes.h err.h \
		ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h \
		CoordCmp.h DefTableKeyList.h SymbAttrList.h ExprRepr.h \
		PExprList.h DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h

GrammarRules.o:	GrammarRules.c GrammarRules.h MakeName.h pdl_gen.h \
		Strings.h DynSpace.h RuleProdList.h envmod.h RuleProd.h \
		RuleProdFunctionTypes.h args.h deftbl.h err.h \
		ProdSymbolList.h eliproto.h Prod.h \
		ProdSymbolFunctionTypes.h obstack.h BitSet.h CoordCmp.h \
		DefTableKeyList.h SymbAttrList.h ExprRepr.h PExprList.h \
		DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h csm.h

ProdSymbolList.o:	ProdSymbolList.c ProdSymbolList.h err.h obstack.h Prod.h \
		ProdSymbolFunctionTypes.h args.h deftbl.h envmod.h \
		eliproto.h BitSet.h

RuleProdList.o:	RuleProdList.c RuleProdList.h err.h obstack.h RuleProd.h \
		RuleProdFunctionTypes.h args.h deftbl.h ProdSymbolList.h \
		eliproto.h Prod.h ProdSymbolFunctionTypes.h envmod.h \
		BitSet.h

Prod.o:	Prod.c Prod.h DynSpace.h args.h deftbl.h envmod.h err.h \
		eliproto.h obstack.h BitSet.h

MakeName.o:	MakeName.c err.h csm.h idn.h termcode.h MakeName.h \
		eliproto.h obstack.h

ShieldSet.o:	ShieldSet.c ShieldSet.h pdl_gen.h args.h envmod.h \
		DefTableKeyList.h deftbl.h obstack.h BitSet.h eliproto.h \
		DefTableKeyFunctionTypes.h CoordCmp.h err.h RuleProd.h \
		SymbAttrList.h ExprRepr.h PExprList.h ProdSymbolList.h \
		Prod.h ProdSymbolFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h

Accumulate.o:	Accumulate.c Accumulate.h pdl_gen.h Strings.h Attribute.h \
		RuleProdList.h CompRepr.h PreDefId.h ComputationRepr.h \
		deftbl.h err.h PExprList.h Prod.h eliproto.h ExprRepr.h \
		PExprFunctionTypes.h args.h envmod.h obstack.h BitSet.h \
		CoordCmp.h RuleProd.h DefTableKeyList.h SymbAttrList.h \
		ProdSymbolList.h ProdSymbolFunctionTypes.h \
		DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h csm.h RuleProdFunctionTypes.h \
		PreDefId.d.h

InheritRepr.o:	InheritRepr.c InheritRepr.h Inherit.h CompRepr.h \
		GrammarRules.h Prod.h Grammar.h Attribute.h pdl_gen.h csm.h \
		Strings.h MakeName.h args.h ComputationRepr.h deftbl.h \
		err.h PExprList.h eliproto.h ExprRepr.h \
		PExprFunctionTypes.h envmod.h obstack.h BitSet.h \
		RuleProdList.h RuleProd.h RuleProdFunctionTypes.h \
		ProdSymbolList.h ProdSymbolFunctionTypes.h \
		DefTableKeyList.h DefTableKeyFunctionTypes.h CoordCmp.h \
		SymbAttrList.h SymbAttr.h SymbAttrFunctionTypes.h

Compute.o:	Compute.c Compute.h pdl_gen.h GrammarRules.h Grammar.h \
		csm.h Attribute.h MakeName.h Strings.h PreDefId.h Inherit.h \
		SymbolOcc.h args.h envmod.h err.h ptg_gen.h deftbl.h \
		obstack.h BitSet.h eliproto.h ptg.h CoordCmp.h RuleProd.h \
		DefTableKeyList.h SymbAttrList.h ExprRepr.h PExprList.h \
		ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h \
		DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h RuleProdList.h \
		RuleProdFunctionTypes.h PreDefId.d.h

ptg_gen.o:	ptg_gen.c ptg_gen.h obstack.h eliproto.h ptg.h

PtgCommon.o:	PtgCommon.c PtgCommon.h eliproto.h ptg_gen.h csm.h ptg.h \
		obstack.h

Indent.o:	Indent.c Indent.h ptg_gen.h eliproto.h ptg.h

IdlStringOut.o:	IdlStringOut.c IdlStringOut.h args.h

SymbolOcc.o:	SymbolOcc.c SymbolOcc.h pdl_gen.h csm.h args.h \
		GrammarRules.h err.h RuleProdList.h envmod.h RuleProd.h \
		RuleProdFunctionTypes.h deftbl.h ProdSymbolList.h \
		eliproto.h Prod.h ProdSymbolFunctionTypes.h obstack.h \
		BitSet.h CoordCmp.h DefTableKeyList.h SymbAttrList.h \
		ExprRepr.h PExprList.h DefTableKeyFunctionTypes.h \
		SymbAttr.h SymbAttrFunctionTypes.h PExprFunctionTypes.h

Attribute.o:	Attribute.c Attribute.h Strings.h pdl_gen.h PreDefId.h \
		csm.h DefTableKeyList.h envmod.h err.h args.h deftbl.h \
		DefTableKeyFunctionTypes.h eliproto.h obstack.h BitSet.h \
		CoordCmp.h RuleProd.h SymbAttrList.h ExprRepr.h PExprList.h \
		ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h \
		SymbAttr.h SymbAttrFunctionTypes.h PExprFunctionTypes.h \
		PreDefId.d.h

RemoteSet.o:	RemoteSet.c RemoteSet.h pdl_gen.h csm.h args.h envmod.h \
		SymbAttrList.h deftbl.h obstack.h BitSet.h eliproto.h \
		SymbAttr.h SymbAttrFunctionTypes.h CoordCmp.h err.h \
		RuleProd.h DefTableKeyList.h ExprRepr.h PExprList.h \
		ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h \
		DefTableKeyFunctionTypes.h PExprFunctionTypes.h

SymbAttr.o:	SymbAttr.c SymbAttr.h DynSpace.h envmod.h args.h deftbl.h \
		obstack.h BitSet.h eliproto.h

Grammar.o:	Grammar.c Grammar.h GrammarRules.h pdl_gen.h MakeName.h \
		err.h Strings.h deftbl.h envmod.h eliproto.h obstack.h \
		BitSet.h RuleProdList.h RuleProd.h RuleProdFunctionTypes.h \
		args.h ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h \
		CoordCmp.h DefTableKeyList.h SymbAttrList.h ExprRepr.h \
		PExprList.h DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h csm.h

Inherit.o:	Inherit.c Inherit.h GrammarRules.h Grammar.h pdl_gen.h \
		envmod.h deftbl.h obstack.h BitSet.h eliproto.h \
		RuleProdList.h RuleProd.h RuleProdFunctionTypes.h args.h \
		err.h ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h \
		CoordCmp.h DefTableKeyList.h SymbAttrList.h ExprRepr.h \
		PExprList.h DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h

Predefined.o:	Predefined.c Predefined.h pdl_gen.h Attribute.h PreDefId.h \
		args.h envmod.h deftbl.h obstack.h BitSet.h eliproto.h \
		CoordCmp.h err.h RuleProd.h DefTableKeyList.h \
		SymbAttrList.h ExprRepr.h PExprList.h ProdSymbolList.h \
		Prod.h ProdSymbolFunctionTypes.h DefTableKeyFunctionTypes.h \
		SymbAttr.h SymbAttrFunctionTypes.h PExprFunctionTypes.h \
		PreDefId.d.h

RuleOutput.o:	RuleOutput.c RuleOutput.h GrammarRules.h csm.h pdl_gen.h \
		ptg_gen.h eliproto.h ptg.h RuleProdList.h envmod.h \
		RuleProd.h RuleProdFunctionTypes.h args.h deftbl.h err.h \
		ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h obstack.h \
		BitSet.h CoordCmp.h DefTableKeyList.h SymbAttrList.h \
		ExprRepr.h PExprList.h DefTableKeyFunctionTypes.h \
		SymbAttr.h SymbAttrFunctionTypes.h PExprFunctionTypes.h

SymbolOutput.o:	SymbolOutput.c SymbolOutput.h GrammarRules.h Attribute.h \
		csm.h pdl_gen.h args.h envmod.h ptg_gen.h deftbl.h \
		obstack.h BitSet.h eliproto.h ptg.h RuleProdList.h \
		RuleProd.h RuleProdFunctionTypes.h err.h ProdSymbolList.h \
		Prod.h ProdSymbolFunctionTypes.h DefTableKeyList.h \
		DefTableKeyFunctionTypes.h CoordCmp.h SymbAttrList.h \
		ExprRepr.h PExprList.h SymbAttr.h SymbAttrFunctionTypes.h \
		PExprFunctionTypes.h

CheckRuleComps.o:	CheckRuleComps.c CheckRuleComps.h CompRepr.h GrammarRules.h \
		Grammar.h pdl_gen.h csm.h Strings.h DefTableKeyList.h \
		Predefined.h PreDefId.h Remote.h Inherit.h SymbolOcc.h \
		args.h ComputationRepr.h deftbl.h err.h PExprList.h Prod.h \
		eliproto.h ExprRepr.h PExprFunctionTypes.h envmod.h \
		obstack.h BitSet.h RuleProdList.h RuleProd.h \
		RuleProdFunctionTypes.h ProdSymbolList.h \
		ProdSymbolFunctionTypes.h CoordCmp.h SymbAttrList.h \
		DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PreDefId.d.h

RemoteOut.o:	RemoteOut.c RemoteOut.h SymbolOutput.h Remote.h pdl_gen.h \
		csm.h ptg_gen.h deftbl.h args.h eliproto.h ptg.h envmod.h \
		obstack.h BitSet.h DefTableKeyList.h SymbAttrList.h err.h \
		DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h CoordCmp.h RuleProd.h ExprRepr.h \
		PExprList.h ProdSymbolList.h Prod.h \
		ProdSymbolFunctionTypes.h PExprFunctionTypes.h

DefsOut.o:	DefsOut.c DefsOut.h GrammarRules.h Grammar.h Attribute.h \
		pdl_gen.h csm.h MakeName.h args.h envmod.h ptg_gen.h \
		deftbl.h obstack.h BitSet.h eliproto.h ptg.h RuleProdList.h \
		RuleProd.h RuleProdFunctionTypes.h err.h ProdSymbolList.h \
		Prod.h ProdSymbolFunctionTypes.h DefTableKeyList.h \
		DefTableKeyFunctionTypes.h CoordCmp.h SymbAttrList.h \
		ExprRepr.h PExprList.h SymbAttr.h SymbAttrFunctionTypes.h \
		PExprFunctionTypes.h

ReprOut.o:	ReprOut.c ReprOut.h pdl_gen.h ptg_gen.h envmod.h csm.h \
		CompRepr.h RuleProdList.h RemoteOut.h eliproto.h ptg.h \
		deftbl.h CoordCmp.h err.h RuleProd.h DefTableKeyList.h \
		SymbAttrList.h ExprRepr.h PExprList.h args.h \
		ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h obstack.h \
		BitSet.h DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h \
		ComputationRepr.h RuleProdFunctionTypes.h

CompOut.o:	CompOut.c CompOut.h pdl_gen.h ptg_gen.h envmod.h csm.h \
		CompRepr.h RuleProdList.h RemoteOut.h eliproto.h ptg.h \
		deftbl.h CoordCmp.h err.h RuleProd.h DefTableKeyList.h \
		SymbAttrList.h ExprRepr.h PExprList.h args.h \
		ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h obstack.h \
		BitSet.h DefTableKeyFunctionTypes.h SymbAttr.h \
		SymbAttrFunctionTypes.h PExprFunctionTypes.h \
		ComputationRepr.h RuleProdFunctionTypes.h

obstack.o:	obstack.c config.h obstack.h gettext.h


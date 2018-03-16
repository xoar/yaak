SHELL   = /bin/sh

CC	= gcc

OBJS	= driver.o clpintf.o clp.o csm.o obsave.o deftbl.o err.o \
	source.o pdl_gen.o VoidPtrList.o clplib.o AlgScope.o \
	envmod.o BitSet.o treecon.o nodecode.o treebuild.o parser.o \
	treestack.o scanswitch.o pascalStr.o glahead.o auxNUL.o \
	auxEOF.o dflteot.o tabsize.o idn.o Cint.o p_mkstr.o str.o \
	auxScanEOL.o CchStr.o pascalCom.o Ccomment.o dfltrepar.o \
	attrmain.o visitprocs.o visitmap.o Strings.o GrammarRules.o \
	ProdSymbolList.o RuleProdList.o Prod.o DynSpace.o \
	MakeName.o RuleOutput.o ptg_gen.o obstack.o

EXE	= LigaProd.exe

all:	$(EXE)

$(EXE):	$(OBJS)
	$(CC) -o $(EXE) $(CFLAGS) $(OBJS) $(LIBS)

objects: $(OBJS)

clean:
	rm -f a.out *.o *.a *~ core ERRS $(EXE)

tidy:
	rm -f core a.out *.o *~ *.a ERRS

driver.o:	driver.c err.h HEAD.h INIT.h FINL.h eliproto.h clp.h \
		Strings.h envmod.h deftbl.h BitSet.h AlgScope.h CoordCmp.h \
		ProdSymbolList.h DynSpace.h RuleProdList.h MakeName.h \
		scanswitch.h GrammarRules.h RuleOutput.h source.h ptg_gen.h \
		pdl_gen.h treecon.h DefTableKeyList.h VoidPtrList.h \
		clplib.h RuleProd.h args.h Prod.h ProdSymbolFunctionTypes.h \
		obstack.h VoidPtr.h VoidPtrFunctionTypes.h csm.h \
		RuleProdFunctionTypes.h ptg.h nodeptr.h

clpintf.o:	clpintf.c clpintf.h eliproto.h

clp.o:	clp.c clp.h clpintf.h pdl_gen.h csm.h eliproto.h clplib.h \
		DefTableKeyList.h deftbl.h CoordCmp.h err.h RuleProd.h \
		args.h ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h \
		envmod.h obstack.h BitSet.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h

csm.o:	csm.c csm.h csmtbl.h obsave.h obstack.h eliproto.h

obsave.o:	obsave.c obsave.h obstack.h eliproto.h

deftbl.o:	deftbl.c err.h deftbl.h obstack.h obsave.h eliproto.h

err.o:	err.c err.h source.h eliproto.h

source.o:	source.c source.h

pdl_gen.o:	pdl_gen.c pdl_gen.h deftbl.h CoordCmp.h err.h RuleProd.h \
		eliproto.h args.h ProdSymbolList.h Prod.h \
		ProdSymbolFunctionTypes.h envmod.h obstack.h BitSet.h

VoidPtrList.o:	VoidPtrList.c VoidPtrList.h err.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h eliproto.h

clplib.o:	clplib.c csm.h clplib.h obstack.h eliproto.h

AlgScope.o:	AlgScope.c AlgScope.h envmod.h deftbl.h obstack.h BitSet.h \
		eliproto.h

envmod.o:	envmod.c err.h obstack.h envmod.h obsave.h eliproto.h \
		deftbl.h BitSet.h

BitSet.o:	BitSet.c obstack.h err.h BitSet.h eliproto.h

treecon.o:	treecon.c node.h nodecode.h attrpredef.h visitmap.h \
		treeact.h obstack.h err.h nodeptr.h HEAD.h eliproto.h clp.h \
		Strings.h envmod.h deftbl.h BitSet.h AlgScope.h CoordCmp.h \
		ProdSymbolList.h DynSpace.h RuleProdList.h MakeName.h \
		scanswitch.h GrammarRules.h RuleOutput.h source.h ptg_gen.h \
		pdl_gen.h treecon.h DefTableKeyList.h VoidPtrList.h \
		clplib.h RuleProd.h args.h Prod.h ProdSymbolFunctionTypes.h \
		VoidPtr.h VoidPtrFunctionTypes.h csm.h \
		RuleProdFunctionTypes.h ptg.h

nodecode.o:	nodecode.c nodecode.h

treebuild.o:	treebuild.c eliproto.h pdl_gen.h source.h csm.h clp.h \
		clpintf.h deftbl.h CoordCmp.h err.h RuleProd.h args.h \
		ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h envmod.h \
		obstack.h BitSet.h clplib.h DefTableKeyList.h VoidPtrList.h \
		VoidPtr.h VoidPtrFunctionTypes.h

parser.o:	parser.c err.h treestack.h gsdescr.h HEAD.h reparatur.h \
		gla.h parser.h semprods.h ptabs.h eliproto.h nodeptr.h \
		parsops.h clp.h Strings.h envmod.h deftbl.h BitSet.h \
		AlgScope.h CoordCmp.h ProdSymbolList.h DynSpace.h \
		RuleProdList.h MakeName.h scanswitch.h GrammarRules.h \
		RuleOutput.h source.h ptg_gen.h pdl_gen.h treecon.h \
		DefTableKeyList.h VoidPtrList.h clplib.h RuleProd.h args.h \
		Prod.h ProdSymbolFunctionTypes.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h csm.h RuleProdFunctionTypes.h ptg.h

treestack.o:	treestack.c err.h treestack.h eliproto.h nodeptr.h

scanswitch.o:	scanswitch.c scanswitch.h args.h

pascalStr.o:	pascalStr.c err.h gla.h tabsize.h eliproto.h

glahead.o:	glahead.c err.h csm.h source.h obstack.h scanops.h \
		tabsize.h ScanProc.h gla.h xtables.h xcode.h eliproto.h

auxNUL.o:	auxNUL.c source.h gla.h

auxEOF.o:	auxEOF.c 

dflteot.o:	dflteot.c 

tabsize.o:	tabsize.c 

idn.o:	idn.c err.h idn.h csm.h obstack.h obsave.h idntbl.h \
		eliproto.h

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
		DynSpace.h RuleProdList.h MakeName.h scanswitch.h \
		GrammarRules.h RuleOutput.h source.h ptg_gen.h pdl_gen.h \
		DefTableKeyList.h VoidPtrList.h clplib.h RuleProd.h args.h \
		Prod.h ProdSymbolFunctionTypes.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h csm.h RuleProdFunctionTypes.h ptg.h

visitprocs.o:	visitprocs.c HEAD.h err.h node.h visitprocs.h attrpredef.h \
		visitmap.h clp.h Strings.h envmod.h deftbl.h BitSet.h \
		AlgScope.h CoordCmp.h ProdSymbolList.h DynSpace.h \
		RuleProdList.h MakeName.h scanswitch.h GrammarRules.h \
		RuleOutput.h source.h ptg_gen.h pdl_gen.h treecon.h \
		DefTableKeyList.h VoidPtrList.h clplib.h eliproto.h \
		RuleProd.h args.h Prod.h ProdSymbolFunctionTypes.h \
		obstack.h VoidPtr.h VoidPtrFunctionTypes.h csm.h \
		RuleProdFunctionTypes.h ptg.h nodeptr.h

visitmap.o:	visitmap.c visitprocs.h visitmap.h HEAD.h node.h treecon.h \
		eliproto.h clp.h Strings.h envmod.h deftbl.h BitSet.h \
		AlgScope.h err.h CoordCmp.h ProdSymbolList.h DynSpace.h \
		RuleProdList.h MakeName.h scanswitch.h GrammarRules.h \
		RuleOutput.h source.h ptg_gen.h pdl_gen.h DefTableKeyList.h \
		VoidPtrList.h clplib.h RuleProd.h args.h Prod.h \
		ProdSymbolFunctionTypes.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h csm.h RuleProdFunctionTypes.h ptg.h \
		nodeptr.h

Strings.o:	Strings.c Strings.h csm.h obstack.h eliproto.h

GrammarRules.o:	GrammarRules.c GrammarRules.h MakeName.h pdl_gen.h \
		Strings.h DynSpace.h RuleProdList.h envmod.h RuleProd.h \
		RuleProdFunctionTypes.h args.h deftbl.h err.h \
		ProdSymbolList.h eliproto.h Prod.h \
		ProdSymbolFunctionTypes.h obstack.h BitSet.h CoordCmp.h \
		csm.h

ProdSymbolList.o:	ProdSymbolList.c ProdSymbolList.h err.h obstack.h Prod.h \
		ProdSymbolFunctionTypes.h args.h deftbl.h envmod.h \
		eliproto.h BitSet.h

RuleProdList.o:	RuleProdList.c RuleProdList.h err.h obstack.h RuleProd.h \
		RuleProdFunctionTypes.h args.h deftbl.h ProdSymbolList.h \
		eliproto.h Prod.h ProdSymbolFunctionTypes.h envmod.h \
		BitSet.h

Prod.o:	Prod.c Prod.h DynSpace.h args.h deftbl.h envmod.h err.h \
		eliproto.h obstack.h BitSet.h

DynSpace.o:	DynSpace.c obstack.h DynSpace.h

MakeName.o:	MakeName.c err.h csm.h idn.h termcode.h MakeName.h \
		eliproto.h obstack.h

RuleOutput.o:	RuleOutput.c RuleOutput.h GrammarRules.h csm.h pdl_gen.h \
		ptg_gen.h eliproto.h ptg.h RuleProdList.h envmod.h \
		RuleProd.h RuleProdFunctionTypes.h args.h deftbl.h err.h \
		ProdSymbolList.h Prod.h ProdSymbolFunctionTypes.h obstack.h \
		BitSet.h CoordCmp.h

ptg_gen.o:	ptg_gen.c ptg_gen.h obstack.h eliproto.h ptg.h

obstack.o:	obstack.c config.h obstack.h gettext.h


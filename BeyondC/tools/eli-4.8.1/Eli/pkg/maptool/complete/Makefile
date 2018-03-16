SHELL   = /bin/sh

CC	= gcc

OBJS	= driver.o clpintf.o clp.o csm.o obsave.o deftbl.o err.o \
	source.o pdl_gen.o DefTableKeyList.o clplib.o symbol.o \
	AlgScope.o envmod.o BitSet.o ActionStack.o treecon.o \
	nodecode.o parser.o glahead.o auxNUL.o auxEOF.o dflteot.o \
	tabsize.o idn.o int.o pascalStr.o auxScanEOL.o Ccomment.o \
	pgs_gen.o treestack.o dfltrepar.o attrmain.o visitprocs.o \
	visitmap.o ptg_gen.o output.o SymbolPList.o match.o \
	oiladt2a.o map.o rules.o MakeName.o VoidPtrList.o \
	oiladt2f.o oiladt2c.o intList.o PtgCommon.o Strings.o \
	classify.o obstack.o

EXE	= maptool.exe

all:	$(EXE)

$(EXE):	$(OBJS)
	$(CC) -o $(EXE) $(CFLAGS) $(OBJS) $(LIBS)

objects: $(OBJS)

clean:
	rm -f a.out *.o *.a *~ core ERRS $(EXE)

tidy:
	rm -f core a.out *.o *~ *.a ERRS

driver.o:	driver.c err.h HEAD.h dapto.h dapto_dapto.h INIT.h FINL.h \
		eliproto.h clp.h output.h rules.h symbol.h map.h match.h \
		classify.h AlgScope.h CoordCmp.h envmod.h Strings.h \
		ActionStack.h intList.h tOilTypeSetList.h MakeName.h \
		SymbolPList.h DefTableKeyList.h VoidPtrList.h ptg_gen.h \
		pdl_gen.h treecon.h BitSet.h deftbl.h PtgCommon.h clplib.h \
		oiladt2.h csm.h DefTableKeyFunctionTypes.h \
		SymbolPFunctionTypes.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h intFunctionTypes.h ptg.h nodeptr.h

clpintf.o:	clpintf.c clp.h clpintf.h csm.h eliproto.h pdl_gen.h \
		source.h clplib.h DefTableKeyList.h deftbl.h SymbolPList.h \
		oiladt2.h rules.h intList.h CoordCmp.h \
		DefTableKeyFunctionTypes.h symbol.h SymbolPFunctionTypes.h \
		obstack.h VoidPtrList.h VoidPtr.h VoidPtrFunctionTypes.h \
		envmod.h BitSet.h intFunctionTypes.h err.h

clp.o:	clp.c clp.h clpintf.h pdl_gen.h csm.h eliproto.h clplib.h \
		DefTableKeyList.h deftbl.h SymbolPList.h oiladt2.h rules.h \
		intList.h CoordCmp.h DefTableKeyFunctionTypes.h symbol.h \
		SymbolPFunctionTypes.h obstack.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h envmod.h BitSet.h intFunctionTypes.h \
		err.h

csm.o:	csm.c csm.h csmtbl.h dapto_dapto.h csm_dapto.h obsave.h \
		obstack.h eliproto.h dapto.h

obsave.o:	obsave.c obsave.h obstack.h eliproto.h

deftbl.o:	deftbl.c err.h deftbl.h obstack.h obsave.h eliproto.h

err.o:	err.c err.h source.h dapto_dapto.h err_dapto.h eliproto.h \
		dapto.h

source.o:	source.c source.h dapto_dapto.h dapto.h eliproto.h

pdl_gen.o:	pdl_gen.c pdl_gen.h deftbl.h DefTableKeyList.h \
		SymbolPList.h oiladt2.h csm.h rules.h intList.h CoordCmp.h \
		eliproto.h DefTableKeyFunctionTypes.h symbol.h \
		SymbolPFunctionTypes.h obstack.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h envmod.h BitSet.h intFunctionTypes.h \
		err.h

DefTableKeyList.o:	DefTableKeyList.c DefTableKeyList.h err.h obstack.h \
		deftbl.h DefTableKeyFunctionTypes.h eliproto.h

clplib.o:	clplib.c csm.h clplib.h obstack.h eliproto.h

symbol.o:	symbol.c obstack.h symbol.h eliproto.h deftbl.h

AlgScope.o:	AlgScope.c AlgScope.h envmod.h deftbl.h obstack.h BitSet.h \
		eliproto.h

envmod.o:	envmod.c err.h obstack.h envmod.h obsave.h envmod_dapto.h \
		eliproto.h deftbl.h BitSet.h dapto.h

BitSet.o:	BitSet.c obstack.h err.h BitSet.h eliproto.h

ActionStack.o:	ActionStack.c obstack.h

treecon.o:	treecon.c node.h nodecode.h attrpredef.h visitmap.h \
		treeact.h obstack.h err.h nodeptr.h HEAD.h eliproto.h clp.h \
		output.h rules.h symbol.h map.h match.h classify.h \
		AlgScope.h CoordCmp.h envmod.h Strings.h ActionStack.h \
		intList.h tOilTypeSetList.h MakeName.h SymbolPList.h \
		DefTableKeyList.h VoidPtrList.h ptg_gen.h pdl_gen.h \
		treecon.h BitSet.h deftbl.h PtgCommon.h clplib.h oiladt2.h \
		csm.h DefTableKeyFunctionTypes.h SymbolPFunctionTypes.h \
		VoidPtr.h VoidPtrFunctionTypes.h intFunctionTypes.h ptg.h

nodecode.o:	nodecode.c nodecode.h

parser.o:	parser.c err.h gla.h gsdescr.h reparatur.h dapto_dapto.h \
		pgs_gen.h eliproto.h parsops.h dapto.h

glahead.o:	glahead.c err.h csm.h source.h obstack.h scanops.h \
		tabsize.h ScanProc.h gla.h dapto_dapto.h xtables.h xcode.h \
		eliproto.h dapto.h

auxNUL.o:	auxNUL.c source.h gla.h

auxEOF.o:	auxEOF.c 

dflteot.o:	dflteot.c 

tabsize.o:	tabsize.c 

idn.o:	idn.c err.h idn.h csm.h obstack.h obsave.h idntbl.h \
		eliproto.h

int.o:	int.c obstack.h csm.h err.h eliproto.h

pascalStr.o:	pascalStr.c err.h gla.h tabsize.h eliproto.h

auxScanEOL.o:	auxScanEOL.c eliproto.h err.h gla.h source.h ScanProc.h

Ccomment.o:	Ccomment.c err.h gla.h source.h tabsize.h ScanProc.h \
		eliproto.h

pgs_gen.o:	pgs_gen.c gsdescr.h treestack.h HEAD.h err.h parsops.h \
		eliproto.h nodeptr.h clp.h output.h rules.h symbol.h map.h \
		match.h classify.h AlgScope.h CoordCmp.h envmod.h Strings.h \
		ActionStack.h intList.h tOilTypeSetList.h MakeName.h \
		SymbolPList.h DefTableKeyList.h VoidPtrList.h ptg_gen.h \
		pdl_gen.h treecon.h BitSet.h deftbl.h PtgCommon.h clplib.h \
		oiladt2.h csm.h DefTableKeyFunctionTypes.h \
		SymbolPFunctionTypes.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h intFunctionTypes.h ptg.h

treestack.o:	treestack.c err.h treestack.h eliproto.h nodeptr.h

dfltrepar.o:	dfltrepar.c err.h reparatur.h eliproto.h

attrmain.o:	attrmain.c treestack.h visitprocs.h nodeptr.h HEAD.h node.h \
		treecon.h eliproto.h clp.h output.h rules.h symbol.h map.h \
		match.h classify.h AlgScope.h err.h CoordCmp.h envmod.h \
		Strings.h ActionStack.h intList.h tOilTypeSetList.h \
		MakeName.h SymbolPList.h DefTableKeyList.h VoidPtrList.h \
		ptg_gen.h pdl_gen.h BitSet.h deftbl.h PtgCommon.h clplib.h \
		oiladt2.h csm.h DefTableKeyFunctionTypes.h \
		SymbolPFunctionTypes.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h intFunctionTypes.h ptg.h

visitprocs.o:	visitprocs.c HEAD.h err.h node.h visitprocs.h attrpredef.h \
		visitmap.h clp.h output.h rules.h symbol.h map.h match.h \
		classify.h AlgScope.h CoordCmp.h envmod.h Strings.h \
		ActionStack.h intList.h tOilTypeSetList.h MakeName.h \
		SymbolPList.h DefTableKeyList.h VoidPtrList.h ptg_gen.h \
		pdl_gen.h treecon.h BitSet.h deftbl.h PtgCommon.h clplib.h \
		eliproto.h oiladt2.h csm.h DefTableKeyFunctionTypes.h \
		SymbolPFunctionTypes.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h intFunctionTypes.h ptg.h nodeptr.h

visitmap.o:	visitmap.c visitprocs.h visitmap.h HEAD.h node.h treecon.h \
		eliproto.h clp.h output.h rules.h symbol.h map.h match.h \
		classify.h AlgScope.h err.h CoordCmp.h envmod.h Strings.h \
		ActionStack.h intList.h tOilTypeSetList.h MakeName.h \
		SymbolPList.h DefTableKeyList.h VoidPtrList.h ptg_gen.h \
		pdl_gen.h BitSet.h deftbl.h PtgCommon.h clplib.h oiladt2.h \
		csm.h DefTableKeyFunctionTypes.h SymbolPFunctionTypes.h \
		obstack.h VoidPtr.h VoidPtrFunctionTypes.h \
		intFunctionTypes.h ptg.h nodeptr.h

ptg_gen.o:	ptg_gen.c ptg_gen.h obstack.h eliproto.h ptg.h

output.o:	output.c deftbl.h ptg_gen.h pdl_gen.h ActionStack.h \
		intList.h DefTableKeyList.h SymbolPList.h MakeName.h \
		rules.h match.h map.h output.h symbol.h eliproto.h ptg.h \
		oiladt2.h csm.h CoordCmp.h DefTableKeyFunctionTypes.h \
		SymbolPFunctionTypes.h obstack.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h envmod.h BitSet.h intFunctionTypes.h \
		err.h

SymbolPList.o:	SymbolPList.c SymbolPList.h err.h obstack.h symbol.h \
		SymbolPFunctionTypes.h deftbl.h eliproto.h

match.o:	match.c deftbl.h err.h csm.h oiladt2.h Strings.h match.h \
		map.h rules.h pdl_gen.h symbol.h eliproto.h obstack.h \
		VoidPtrList.h VoidPtr.h VoidPtrFunctionTypes.h envmod.h \
		SymbolPList.h BitSet.h SymbolPFunctionTypes.h intList.h \
		intFunctionTypes.h DefTableKeyList.h CoordCmp.h \
		DefTableKeyFunctionTypes.h

oiladt2a.o:	oiladt2a.c oiladt2.h tOilTypeSetList.h pdl_gen.h \
		oil_dapto.h eliproto.h VoidPtrList.h deftbl.h VoidPtr.h \
		VoidPtrFunctionTypes.h DefTableKeyList.h SymbolPList.h \
		csm.h rules.h intList.h CoordCmp.h \
		DefTableKeyFunctionTypes.h symbol.h SymbolPFunctionTypes.h \
		obstack.h envmod.h BitSet.h intFunctionTypes.h err.h \
		dapto.h

map.o:	map.c deftbl.h err.h obstack.h pdl_gen.h SymbolPList.h \
		DefTableKeyList.h intList.h map.h match.h symbol.h \
		tOilTypeSetList.h eliproto.h oiladt2.h csm.h rules.h \
		CoordCmp.h DefTableKeyFunctionTypes.h \
		SymbolPFunctionTypes.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h envmod.h BitSet.h intFunctionTypes.h

rules.o:	rules.c err.h csm.h idn.h pdl_gen.h oiladt2.h obstack.h \
		deftbl.h MakeName.h map.h symbol.h rules.h eliproto.h \
		DefTableKeyList.h SymbolPList.h intList.h CoordCmp.h \
		DefTableKeyFunctionTypes.h SymbolPFunctionTypes.h \
		VoidPtrList.h VoidPtr.h VoidPtrFunctionTypes.h envmod.h \
		BitSet.h intFunctionTypes.h

MakeName.o:	MakeName.c err.h csm.h idn.h termcode.h MakeName.h \
		eliproto.h obstack.h

VoidPtrList.o:	VoidPtrList.c VoidPtrList.h err.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h eliproto.h

oiladt2f.o:	oiladt2f.c oiladt2.h eliproto.h VoidPtrList.h deftbl.h \
		VoidPtr.h VoidPtrFunctionTypes.h

oiladt2c.o:	oiladt2c.c tOilTypeSetList.h oiladt2.h VoidPtrList.h \
		eliproto.h deftbl.h VoidPtr.h VoidPtrFunctionTypes.h

intList.o:	intList.c intList.h err.h obstack.h intFunctionTypes.h \
		eliproto.h

PtgCommon.o:	PtgCommon.c PtgCommon.h eliproto.h ptg_gen.h csm.h ptg.h \
		obstack.h

Strings.o:	Strings.c Strings.h csm.h obstack.h eliproto.h

classify.o:	classify.c pdl_gen.h DefTableKeyList.h classify.h symbol.h \
		deftbl.h SymbolPList.h oiladt2.h csm.h rules.h intList.h \
		CoordCmp.h eliproto.h DefTableKeyFunctionTypes.h \
		SymbolPFunctionTypes.h obstack.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h envmod.h BitSet.h intFunctionTypes.h \
		err.h

obstack.o:	obstack.c config.h obstack.h gettext.h


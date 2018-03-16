SHELL   = /bin/sh

CC	= gcc

OBJS	= driver.o obstack.o clpintf.o clp.o csm.o obsave.o deftbl.o err.o \
	source.o pdl_gen.o DefTableKeyList.o clplib.o ptg_gen.o \
	PrettyPrint.o PtgOutput.o PtgCommon.o AlgScope.o envmod.o \
	BitSet.o FctAlgScope.o PreDefId.o IdentTerm.o PreDefMod.o \
	idn.o treecon.o nodecode.o parser.o treestack.o glahead.o \
	auxNUL.o auxEOF.o dflteot.o tabsize.o int.o auxScanEOL.o \
	CchStr.o str.o Ccomment.o dfltrepar.o attrmain.o \
	visitprocs.o visitmap.o PatElem.o DynSpace.o PatElemList.o \
	insertKey.o cmpPatIndex.o Strings.o transInsert.o \
	cmpDefTableKey.o

EXE	= ptg.exe

all:	$(EXE)

$(EXE):	$(OBJS)
	$(CC) -o $(EXE) $(CFLAGS) $(OBJS) $(LIBS)

objects: $(OBJS)

clean:
	rm -f a.out *.o *.a *~ core ERRS $(EXE)

tidy:
	rm -f core a.out *.o *~ *.a ERRS

driver.o:	driver.c err.h HEAD.h INIT.h FINL.h eliproto.h clp.h \
		cmpDefTableKey.h cmpPatIndex.h insertKey.h transInsert.h \
		AlgScope.h FctAlgScope.h PreDefMod.h PreDefId.h CoordCmp.h \
		DynSpace.h Strings.h DefTableKeyList.h PatElemList.h \
		ptg_gen.h pdl_gen.h treecon.h BitSet.h deftbl.h envmod.h \
		VoidPtrList.h PtgCommon.h PrettyPrint.h clplib.h \
		DefTableKeyFunctionTypes.h PatElem.h PatElemFunctionTypes.h \
		ptg.h PtgOutput.h csm.h obstack.h PreDefId.d.h nodeptr.h \
		VoidPtr.h VoidPtrFunctionTypes.h

clpintf.o:	clpintf.c clp.h clpintf.h csm.h eliproto.h pdl_gen.h \
		source.h clplib.h DefTableKeyList.h deftbl.h PatElemList.h \
		ptg_gen.h Strings.h CoordCmp.h DefTableKeyFunctionTypes.h \
		PatElem.h PatElemFunctionTypes.h ptg.h PtgOutput.h \
		obstack.h err.h

clp.o:	clp.c clp.h clpintf.h pdl_gen.h csm.h eliproto.h clplib.h \
		DefTableKeyList.h deftbl.h PatElemList.h ptg_gen.h \
		Strings.h CoordCmp.h DefTableKeyFunctionTypes.h PatElem.h \
		PatElemFunctionTypes.h ptg.h PtgOutput.h obstack.h err.h

csm.o:	csm.c csm.h csmtbl.h csm_dapto.h obsave.h obstack.h \
		eliproto.h

obsave.o:	obsave.c obsave.h obstack.h eliproto.h

deftbl.o:	deftbl.c err.h deftbl.h obstack.h obsave.h eliproto.h

err.o:	err.c err.h source.h err_dapto.h eliproto.h

source.o:	source.c source.h

pdl_gen.o:	pdl_gen.c pdl_gen.h deftbl.h DefTableKeyList.h \
		PatElemList.h ptg_gen.h Strings.h CoordCmp.h eliproto.h \
		DefTableKeyFunctionTypes.h PatElem.h PatElemFunctionTypes.h \
		ptg.h PtgOutput.h csm.h obstack.h err.h

DefTableKeyList.o:	DefTableKeyList.c DefTableKeyList.h err.h obstack.h \
		deftbl.h DefTableKeyFunctionTypes.h eliproto.h

clplib.o:	clplib.c csm.h clplib.h obstack.h eliproto.h

ptg_gen.o:	ptg_gen.c ptg_gen.h obstack.h eliproto.h ptg.h PtgOutput.h

PrettyPrint.o:	PrettyPrint.c PrettyPrint.h ptg_gen.h eliproto.h ptg.h \
		PtgOutput.h

PtgOutput.o:	PtgOutput.c PtgOutput.h

PtgCommon.o:	PtgCommon.c PtgCommon.h eliproto.h ptg_gen.h csm.h ptg.h \
		PtgOutput.h obstack.h

AlgScope.o:	AlgScope.c AlgScope.h envmod.h deftbl.h obstack.h BitSet.h \
		eliproto.h

envmod.o:	envmod.c err.h obstack.h envmod.h obsave.h envmod_dapto.h \
		eliproto.h deftbl.h BitSet.h

BitSet.o:	BitSet.c obstack.h err.h BitSet.h eliproto.h

FctAlgScope.o:	FctAlgScope.c FctAlgScope.h envmod.h deftbl.h obstack.h \
		BitSet.h eliproto.h

PreDefId.o:	PreDefId.c IdentTerm.h PreDefMod.h PreDefId.h pdl_gen.h \
		PreDefId.d.h eliproto.h envmod.h deftbl.h obstack.h \
		BitSet.h DefTableKeyList.h PatElemList.h ptg_gen.h \
		Strings.h CoordCmp.h DefTableKeyFunctionTypes.h PatElem.h \
		PatElemFunctionTypes.h ptg.h PtgOutput.h csm.h err.h

IdentTerm.o:	IdentTerm.c termcode.h IdentTerm.h

PreDefMod.o:	PreDefMod.c idn.h PreDefMod.h eliproto.h envmod.h deftbl.h \
		obstack.h BitSet.h

idn.o:	idn.c err.h idn.h csm.h obstack.h obsave.h idntbl.h \
		eliproto.h

treecon.o:	treecon.c node.h nodecode.h attrpredef.h visitmap.h \
		treeact.h obstack.h err.h nodeptr.h HEAD.h eliproto.h clp.h \
		cmpDefTableKey.h cmpPatIndex.h insertKey.h transInsert.h \
		AlgScope.h FctAlgScope.h PreDefMod.h PreDefId.h CoordCmp.h \
		DynSpace.h Strings.h DefTableKeyList.h PatElemList.h \
		ptg_gen.h pdl_gen.h treecon.h BitSet.h deftbl.h envmod.h \
		VoidPtrList.h PtgCommon.h PrettyPrint.h clplib.h \
		DefTableKeyFunctionTypes.h PatElem.h PatElemFunctionTypes.h \
		ptg.h PtgOutput.h csm.h PreDefId.d.h VoidPtr.h \
		VoidPtrFunctionTypes.h

nodecode.o:	nodecode.c nodecode.h

parser.o:	parser.c err.h treestack.h gsdescr.h HEAD.h reparatur.h \
		gla.h parser.h semprods.h ptabs.h eliproto.h nodeptr.h \
		parsops.h clp.h cmpDefTableKey.h cmpPatIndex.h insertKey.h \
		transInsert.h AlgScope.h FctAlgScope.h PreDefMod.h \
		PreDefId.h CoordCmp.h DynSpace.h Strings.h \
		DefTableKeyList.h PatElemList.h ptg_gen.h pdl_gen.h \
		treecon.h BitSet.h deftbl.h envmod.h VoidPtrList.h \
		PtgCommon.h PrettyPrint.h clplib.h \
		DefTableKeyFunctionTypes.h PatElem.h PatElemFunctionTypes.h \
		ptg.h PtgOutput.h csm.h obstack.h PreDefId.d.h VoidPtr.h \
		VoidPtrFunctionTypes.h

treestack.o:	treestack.c err.h treestack.h eliproto.h nodeptr.h

glahead.o:	glahead.c err.h csm.h source.h obstack.h scanops.h \
		tabsize.h ScanProc.h gla.h xtables.h xcode.h eliproto.h

auxNUL.o:	auxNUL.c source.h gla.h

auxEOF.o:	auxEOF.c 

dflteot.o:	dflteot.c 

tabsize.o:	tabsize.c 

int.o:	int.c err.h eliproto.h

auxScanEOL.o:	auxScanEOL.c eliproto.h err.h gla.h source.h ScanProc.h

CchStr.o:	CchStr.c err.h source.h gla.h csm.h tabsize.h ScanProc.h \
		eliproto.h obstack.h

str.o:	str.c csm.h obstack.h eliproto.h

Ccomment.o:	Ccomment.c err.h gla.h source.h tabsize.h ScanProc.h \
		eliproto.h

dfltrepar.o:	dfltrepar.c err.h reparatur.h eliproto.h

attrmain.o:	attrmain.c treestack.h visitprocs.h nodeptr.h HEAD.h node.h \
		treecon.h eliproto.h clp.h cmpDefTableKey.h cmpPatIndex.h \
		insertKey.h transInsert.h AlgScope.h err.h FctAlgScope.h \
		PreDefMod.h PreDefId.h CoordCmp.h DynSpace.h Strings.h \
		DefTableKeyList.h PatElemList.h ptg_gen.h pdl_gen.h \
		BitSet.h deftbl.h envmod.h VoidPtrList.h PtgCommon.h \
		PrettyPrint.h clplib.h DefTableKeyFunctionTypes.h PatElem.h \
		PatElemFunctionTypes.h ptg.h PtgOutput.h csm.h obstack.h \
		PreDefId.d.h VoidPtr.h VoidPtrFunctionTypes.h

visitprocs.o:	visitprocs.c HEAD.h err.h node.h visitprocs.h attrpredef.h \
		visitmap.h clp.h cmpDefTableKey.h cmpPatIndex.h insertKey.h \
		transInsert.h AlgScope.h FctAlgScope.h PreDefMod.h \
		PreDefId.h CoordCmp.h DynSpace.h Strings.h \
		DefTableKeyList.h PatElemList.h ptg_gen.h pdl_gen.h \
		treecon.h BitSet.h deftbl.h envmod.h VoidPtrList.h \
		PtgCommon.h PrettyPrint.h clplib.h eliproto.h \
		DefTableKeyFunctionTypes.h PatElem.h PatElemFunctionTypes.h \
		ptg.h PtgOutput.h csm.h obstack.h PreDefId.d.h nodeptr.h \
		VoidPtr.h VoidPtrFunctionTypes.h

visitmap.o:	visitmap.c visitprocs.h visitmap.h HEAD.h node.h treecon.h \
		eliproto.h clp.h cmpDefTableKey.h cmpPatIndex.h insertKey.h \
		transInsert.h AlgScope.h err.h FctAlgScope.h PreDefMod.h \
		PreDefId.h CoordCmp.h DynSpace.h Strings.h \
		DefTableKeyList.h PatElemList.h ptg_gen.h pdl_gen.h \
		BitSet.h deftbl.h envmod.h VoidPtrList.h PtgCommon.h \
		PrettyPrint.h clplib.h DefTableKeyFunctionTypes.h PatElem.h \
		PatElemFunctionTypes.h ptg.h PtgOutput.h csm.h obstack.h \
		PreDefId.d.h nodeptr.h VoidPtr.h VoidPtrFunctionTypes.h

PatElem.o:	PatElem.c PatElem.h DynSpace.h csm.h pdl_gen.h deftbl.h \
		eliproto.h obstack.h DefTableKeyList.h PatElemList.h \
		ptg_gen.h Strings.h CoordCmp.h DefTableKeyFunctionTypes.h \
		PatElemFunctionTypes.h ptg.h PtgOutput.h err.h

DynSpace.o:	DynSpace.c obstack.h DynSpace.h

PatElemList.o:	PatElemList.c PatElemList.h err.h obstack.h PatElem.h \
		PatElemFunctionTypes.h deftbl.h eliproto.h

insertKey.o:	insertKey.c transInsert.h pdl_gen.h cmpPatIndex.h \
		DefTableKeyList.h ptg_gen.h deftbl.h \
		DefTableKeyFunctionTypes.h eliproto.h ptg.h PtgOutput.h \
		PatElemList.h Strings.h CoordCmp.h PatElem.h \
		PatElemFunctionTypes.h csm.h obstack.h err.h

cmpPatIndex.o:	cmpPatIndex.c cmpPatIndex.h pdl_gen.h deftbl.h eliproto.h \
		DefTableKeyList.h PatElemList.h ptg_gen.h Strings.h \
		CoordCmp.h DefTableKeyFunctionTypes.h PatElem.h \
		PatElemFunctionTypes.h ptg.h PtgOutput.h csm.h obstack.h \
		err.h

Strings.o:	Strings.c Strings.h csm.h obstack.h eliproto.h

transInsert.o:	transInsert.c transInsert.h pdl_gen.h cmpPatIndex.h \
		DefTableKeyList.h ptg_gen.h deftbl.h \
		DefTableKeyFunctionTypes.h eliproto.h ptg.h PtgOutput.h \
		PatElemList.h Strings.h CoordCmp.h PatElem.h \
		PatElemFunctionTypes.h csm.h obstack.h err.h

cmpDefTableKey.o:	cmpDefTableKey.c cmpDefTableKey.h deftbl.h eliproto.h


SHELL   = /bin/sh

CC	= gcc
LIBS=

OBJS	= driver.o clpintf.o clp.o csm.o obsave.o deftbl.o err.o \
	source.o pdl_gen.o VoidPtrList.o clplib.o chain.o \
	TchainList.o DynSpace.o LiteralAlgScope.o envmod.o BitSet.o \
	NonliteralAlgScope.o treecon.o nodecode.o parser.o \
	treestack.o glahead.o auxNUL.o auxEOF.o dflteot.o tabsize.o \
	mkidnwod.o idn.o int.o pascalStr.o auxScanEOL.o Ccomment.o \
	dfltrepar.o attrmain.o visitprocs.o visitmap.o comar_ins.o \
	MakeName.o classify.o wrtcomar.o obstack.o

EXE	= pgs2cmr.exe

all:	$(EXE)

$(EXE):	$(OBJS) ../../../lib/lib.a ../../../idl/IDL.a
	$(CC) -o $(EXE) $(CFLAGS) $(OBJS) ../../../lib/lib.a ../../../idl/IDL.a $(LIBS)

objects: $(OBJS) ../../../lib/lib.a ../../../idl/IDL.a

clean:
	rm -f a.out *.o *.a *~ core ERRS $(EXE)

tidy:
	rm -f core a.out *.o *~ *.a ERRS

driver.o:	driver.c err.h HEAD.h dapto.h dapto_dapto.h INIT.h FINL.h \
		eliproto.h clp.h classify.h comar.h cmrlib.h comarMacros.h \
		comar_func.h comar_ins.h csm.h TchainList.h DynSpace.h \
		LiteralAlgScope.h NonliteralAlgScope.h envmod.h Strings.h \
		MakeName.h CoordCmp.h pdl_gen.h treecon.h BitSet.h \
		DefTableKeyList.h deftbl.h VoidPtrList.h clplib.h \
		cmrinternal.h global.h VoidPtr.h VoidPtrFunctionTypes.h \
		obstack.h chain.h nodeptr.h

clpintf.o:	clpintf.c clp.h clpintf.h csm.h eliproto.h pdl_gen.h \
		source.h clplib.h DefTableKeyList.h deftbl.h cmrlib.h \
		comar.h CoordCmp.h cmrinternal.h global.h err.h \
		VoidPtrList.h VoidPtr.h VoidPtrFunctionTypes.h obstack.h

clp.o:	clp.c clp.h clpintf.h pdl_gen.h csm.h eliproto.h clplib.h \
		DefTableKeyList.h deftbl.h cmrlib.h comar.h CoordCmp.h \
		cmrinternal.h global.h err.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h obstack.h

csm.o:	csm.c csm.h csmtbl.h dapto_dapto.h csm_dapto.h obsave.h \
		obstack.h eliproto.h dapto.h

obsave.o:	obsave.c obsave.h obstack.h eliproto.h

deftbl.o:	deftbl.c err.h deftbl.h obstack.h obsave.h eliproto.h

err.o:	err.c err.h source.h dapto_dapto.h err_dapto.h eliproto.h \
		dapto.h

source.o:	source.c source.h dapto_dapto.h dapto.h eliproto.h

pdl_gen.o:	pdl_gen.c pdl_gen.h deftbl.h cmrlib.h comar.h CoordCmp.h \
		eliproto.h cmrinternal.h global.h err.h

VoidPtrList.o:	VoidPtrList.c VoidPtrList.h err.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h eliproto.h

clplib.o:	clplib.c csm.h clplib.h obstack.h eliproto.h

chain.o:	chain.c chain.h TchainList.h deftbl.h obstack.h err.h \
		eliproto.h

TchainList.o:	TchainList.c TchainList.h err.h DynSpace.h chain.h deftbl.h \
		eliproto.h

DynSpace.o:	DynSpace.c obstack.h DynSpace.h

LiteralAlgScope.o:	LiteralAlgScope.c LiteralAlgScope.h envmod.h deftbl.h \
		obstack.h BitSet.h eliproto.h

envmod.o:	envmod.c err.h obstack.h envmod.h obsave.h envmod_dapto.h \
		eliproto.h deftbl.h BitSet.h dapto.h

BitSet.o:	BitSet.c obstack.h err.h BitSet.h eliproto.h

NonliteralAlgScope.o:	NonliteralAlgScope.c NonliteralAlgScope.h envmod.h deftbl.h \
		obstack.h BitSet.h eliproto.h

treecon.o:	treecon.c node.h nodecode.h attrpredef.h visitmap.h \
		treeact.h obstack.h err.h nodeptr.h HEAD.h eliproto.h clp.h \
		classify.h comar.h cmrlib.h comarMacros.h comar_func.h \
		comar_ins.h csm.h TchainList.h DynSpace.h LiteralAlgScope.h \
		NonliteralAlgScope.h envmod.h Strings.h MakeName.h \
		CoordCmp.h pdl_gen.h treecon.h BitSet.h DefTableKeyList.h \
		deftbl.h VoidPtrList.h clplib.h cmrinternal.h global.h \
		VoidPtr.h VoidPtrFunctionTypes.h chain.h

nodecode.o:	nodecode.c nodecode.h

parser.o:	parser.c err.h treestack.h gsdescr.h HEAD.h reparatur.h \
		gla.h parser.h dapto_dapto.h semprods.h ptabs.h eliproto.h \
		nodeptr.h parsops.h clp.h classify.h comar.h cmrlib.h \
		comarMacros.h comar_func.h comar_ins.h csm.h TchainList.h \
		DynSpace.h LiteralAlgScope.h NonliteralAlgScope.h envmod.h \
		Strings.h MakeName.h CoordCmp.h pdl_gen.h treecon.h \
		BitSet.h DefTableKeyList.h deftbl.h VoidPtrList.h clplib.h \
		cmrinternal.h global.h VoidPtr.h VoidPtrFunctionTypes.h \
		obstack.h chain.h dapto.h

treestack.o:	treestack.c err.h treestack.h eliproto.h nodeptr.h

glahead.o:	glahead.c err.h csm.h source.h obstack.h scanops.h \
		tabsize.h ScanProc.h gla.h dapto_dapto.h xtables.h xcode.h \
		eliproto.h dapto.h

auxNUL.o:	auxNUL.c source.h gla.h

auxEOF.o:	auxEOF.c 

dflteot.o:	dflteot.c 

tabsize.o:	tabsize.c 

mkidnwod.o:	mkidnwod.c idn.h mkidnwod.h eliproto.h

idn.o:	idn.c err.h idn.h csm.h obstack.h obsave.h idntbl.h \
		eliproto.h

int.o:	int.c obstack.h csm.h err.h eliproto.h

pascalStr.o:	pascalStr.c err.h gla.h tabsize.h eliproto.h

auxScanEOL.o:	auxScanEOL.c eliproto.h err.h gla.h source.h ScanProc.h

Ccomment.o:	Ccomment.c err.h gla.h source.h tabsize.h ScanProc.h \
		eliproto.h

dfltrepar.o:	dfltrepar.c err.h reparatur.h eliproto.h

attrmain.o:	attrmain.c treestack.h visitprocs.h nodeptr.h HEAD.h node.h \
		treecon.h eliproto.h clp.h classify.h err.h comar.h \
		cmrlib.h comarMacros.h comar_func.h comar_ins.h csm.h \
		TchainList.h DynSpace.h LiteralAlgScope.h \
		NonliteralAlgScope.h envmod.h Strings.h MakeName.h \
		CoordCmp.h pdl_gen.h BitSet.h DefTableKeyList.h deftbl.h \
		VoidPtrList.h clplib.h cmrinternal.h global.h VoidPtr.h \
		VoidPtrFunctionTypes.h obstack.h chain.h

visitprocs.o:	visitprocs.c HEAD.h err.h node.h visitprocs.h attrpredef.h \
		visitmap.h clp.h classify.h comar.h cmrlib.h comarMacros.h \
		comar_func.h comar_ins.h csm.h TchainList.h DynSpace.h \
		LiteralAlgScope.h NonliteralAlgScope.h envmod.h Strings.h \
		MakeName.h CoordCmp.h pdl_gen.h treecon.h BitSet.h \
		DefTableKeyList.h deftbl.h VoidPtrList.h clplib.h \
		eliproto.h cmrinternal.h global.h VoidPtr.h \
		VoidPtrFunctionTypes.h obstack.h chain.h nodeptr.h

visitmap.o:	visitmap.c visitprocs.h visitmap.h HEAD.h node.h treecon.h \
		eliproto.h clp.h classify.h err.h comar.h cmrlib.h \
		comarMacros.h comar_func.h comar_ins.h csm.h TchainList.h \
		DynSpace.h LiteralAlgScope.h NonliteralAlgScope.h envmod.h \
		Strings.h MakeName.h CoordCmp.h pdl_gen.h BitSet.h \
		DefTableKeyList.h deftbl.h VoidPtrList.h clplib.h \
		cmrinternal.h global.h VoidPtr.h VoidPtrFunctionTypes.h \
		obstack.h chain.h nodeptr.h

comar_ins.o:	comar_ins.c comar.h comarMacros.h comar_func.h name.h \
		cmrlib.h deftbl.h pdl_gen.h err.h source.h termcode.h csm.h \
		comar_ins.h global.h cmrinternal.h eliproto.h CoordCmp.h \
		obstack.h

MakeName.o:	MakeName.c err.h csm.h idn.h termcode.h MakeName.h \
		eliproto.h obstack.h

classify.o:	classify.c classify.h pdl_gen.h deftbl.h eliproto.h \
		cmrlib.h comar.h CoordCmp.h cmrinternal.h global.h err.h

wrtcomar.o:	wrtcomar.c clp.h csm.h clplib.h pdl_gen.h DefTableKeyList.h \
		eliproto.h deftbl.h cmrlib.h comar.h CoordCmp.h \
		cmrinternal.h global.h err.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h obstack.h

obstack.o:	obstack.c config.h obstack.h gettext.h


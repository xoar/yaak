SHELL   = /bin/sh

CC	= gcc

OBJS	= driver.o clpintf.o clp.o csm.o obsave.o deftbl.o err.o \
	source.o pdl_gen.o KnownKey.o ptg_gen.o func.o name.o idn.o \
	envmod.o BitSet.o ElementList.o VoidPtrList.o clplib.o \
	KnownKeyAlgScope.o treecon.o nodecode.o parser.o glahead.o \
	auxNUL.o auxEOF.o dflteot.o tabsize.o Ctext.o auxScanEOL.o \
	CchStr.o str.o Ccomment.o pgs_gen.o treestack.o dfltrepar.o \
	attrmain.o visitprocs.o visitmap.o header.o type.o \
	obstack.o

EXE	= pdl.exe

all:	$(EXE)

$(EXE):	$(OBJS)
	$(CC) -o $(EXE) $(CFLAGS) $(OBJS) $(LIBS)

objects: $(OBJS)

clean:
	rm -f a.out *.o *.a *~ core ERRS $(EXE)

tidy:
	rm -f core a.out *.o *~ *.a ERRS

driver.o:	driver.c err.h HEAD.h dapto.h dapto_dapto.h INIT.h FINL.h \
		eliproto.h clp.h name.h type.h func.h header.h KnownKey.h \
		KnownKeyAlgScope.h ElementList.h envmod.h Strings.h \
		CoordCmp.h ptg_gen.h pdl_gen.h treecon.h BitSet.h \
		DefTableKeyList.h deftbl.h VoidPtrList.h clplib.h ptg.h \
		obstack.h Element.h ElementFunctionTypes.h VoidPtr.h \
		VoidPtrFunctionTypes.h csm.h nodeptr.h

clpintf.o:	clpintf.c clp.h clpintf.h csm.h eliproto.h pdl_gen.h \
		source.h clplib.h DefTableKeyList.h deftbl.h ptg_gen.h \
		func.h header.h envmod.h ElementList.h KnownKey.h \
		CoordCmp.h ptg.h obstack.h BitSet.h Element.h \
		ElementFunctionTypes.h err.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h

clp.o:	clp.c clp.h clpintf.h pdl_gen.h csm.h eliproto.h clplib.h \
		DefTableKeyList.h deftbl.h ptg_gen.h func.h header.h \
		envmod.h ElementList.h KnownKey.h CoordCmp.h ptg.h \
		obstack.h BitSet.h Element.h ElementFunctionTypes.h err.h \
		VoidPtrList.h VoidPtr.h VoidPtrFunctionTypes.h

csm.o:	csm.c csm.h csmtbl.h dapto_dapto.h csm_dapto.h obsave.h \
		obstack.h eliproto.h dapto.h

obsave.o:	obsave.c obsave.h obstack.h eliproto.h

deftbl.o:	deftbl.c err.h deftbl.h obstack.h obsave.h eliproto.h

err.o:	err.c err.h source.h dapto_dapto.h err_dapto.h eliproto.h \
		dapto.h

source.o:	source.c source.h dapto_dapto.h dapto.h eliproto.h

pdl_gen.o:	pdl_gen.c pdl_gen.h deftbl.h ptg_gen.h func.h header.h \
		envmod.h ElementList.h KnownKey.h CoordCmp.h eliproto.h \
		ptg.h obstack.h BitSet.h Element.h ElementFunctionTypes.h \
		err.h

KnownKey.o:	KnownKey.c csm.h ptg_gen.h KnownKey.h ElementList.h \
		obstack.h eliproto.h ptg.h Element.h ElementFunctionTypes.h

ptg_gen.o:	ptg_gen.c ptg_gen.h obstack.h eliproto.h ptg.h

func.o:	func.c err.h deftbl.h envmod.h ptg_gen.h func.h header.h \
		pdl_gen.h csm.h eliproto.h obstack.h BitSet.h ptg.h \
		ElementList.h KnownKey.h CoordCmp.h Element.h \
		ElementFunctionTypes.h

name.o:	name.c err.h csm.h idn.h deftbl.h envmod.h ptg_gen.h \
		header.h name.h pdl_gen.h eliproto.h obstack.h BitSet.h \
		ptg.h func.h ElementList.h KnownKey.h CoordCmp.h Element.h \
		ElementFunctionTypes.h

idn.o:	idn.c err.h idn.h csm.h obstack.h obsave.h idntbl.h \
		eliproto.h

envmod.o:	envmod.c err.h obstack.h envmod.h obsave.h envmod_dapto.h \
		eliproto.h deftbl.h BitSet.h dapto.h

BitSet.o:	BitSet.c obstack.h err.h BitSet.h eliproto.h

ElementList.o:	ElementList.c ElementList.h err.h obstack.h Element.h \
		ElementFunctionTypes.h ptg_gen.h eliproto.h ptg.h

VoidPtrList.o:	VoidPtrList.c VoidPtrList.h err.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h eliproto.h

clplib.o:	clplib.c csm.h clplib.h obstack.h eliproto.h

KnownKeyAlgScope.o:	KnownKeyAlgScope.c KnownKeyAlgScope.h envmod.h deftbl.h \
		obstack.h BitSet.h eliproto.h

treecon.o:	treecon.c node.h nodecode.h attrpredef.h visitmap.h \
		treeact.h obstack.h err.h nodeptr.h HEAD.h eliproto.h clp.h \
		name.h type.h func.h header.h KnownKey.h KnownKeyAlgScope.h \
		ElementList.h envmod.h Strings.h CoordCmp.h ptg_gen.h \
		pdl_gen.h treecon.h BitSet.h DefTableKeyList.h deftbl.h \
		VoidPtrList.h clplib.h ptg.h Element.h \
		ElementFunctionTypes.h VoidPtr.h VoidPtrFunctionTypes.h \
		csm.h

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

Ctext.o:	Ctext.c err.h source.h csm.h gla.h eliproto.h obstack.h

auxScanEOL.o:	auxScanEOL.c eliproto.h err.h gla.h source.h ScanProc.h

CchStr.o:	CchStr.c err.h source.h gla.h csm.h tabsize.h ScanProc.h \
		eliproto.h obstack.h

str.o:	str.c csm.h obstack.h eliproto.h

Ccomment.o:	Ccomment.c err.h gla.h source.h tabsize.h ScanProc.h \
		eliproto.h

pgs_gen.o:	pgs_gen.c gsdescr.h treestack.h HEAD.h err.h parsops.h \
		eliproto.h nodeptr.h clp.h name.h type.h func.h header.h \
		KnownKey.h KnownKeyAlgScope.h ElementList.h envmod.h \
		Strings.h CoordCmp.h ptg_gen.h pdl_gen.h treecon.h BitSet.h \
		DefTableKeyList.h deftbl.h VoidPtrList.h clplib.h ptg.h \
		obstack.h Element.h ElementFunctionTypes.h VoidPtr.h \
		VoidPtrFunctionTypes.h csm.h

treestack.o:	treestack.c err.h treestack.h eliproto.h nodeptr.h

dfltrepar.o:	dfltrepar.c err.h reparatur.h eliproto.h

attrmain.o:	attrmain.c treestack.h visitprocs.h nodeptr.h HEAD.h node.h \
		treecon.h eliproto.h clp.h name.h type.h func.h header.h \
		KnownKey.h KnownKeyAlgScope.h err.h ElementList.h envmod.h \
		Strings.h CoordCmp.h ptg_gen.h pdl_gen.h BitSet.h \
		DefTableKeyList.h deftbl.h VoidPtrList.h clplib.h ptg.h \
		obstack.h Element.h ElementFunctionTypes.h VoidPtr.h \
		VoidPtrFunctionTypes.h csm.h

visitprocs.o:	visitprocs.c HEAD.h err.h node.h visitprocs.h attrpredef.h \
		visitmap.h clp.h name.h type.h func.h header.h KnownKey.h \
		KnownKeyAlgScope.h ElementList.h envmod.h Strings.h \
		CoordCmp.h ptg_gen.h pdl_gen.h treecon.h BitSet.h \
		DefTableKeyList.h deftbl.h VoidPtrList.h clplib.h \
		eliproto.h ptg.h obstack.h Element.h ElementFunctionTypes.h \
		VoidPtr.h VoidPtrFunctionTypes.h csm.h nodeptr.h

visitmap.o:	visitmap.c visitprocs.h visitmap.h HEAD.h node.h treecon.h \
		eliproto.h clp.h name.h type.h func.h header.h KnownKey.h \
		KnownKeyAlgScope.h err.h ElementList.h envmod.h Strings.h \
		CoordCmp.h ptg_gen.h pdl_gen.h BitSet.h DefTableKeyList.h \
		deftbl.h VoidPtrList.h clplib.h ptg.h obstack.h Element.h \
		ElementFunctionTypes.h VoidPtr.h VoidPtrFunctionTypes.h \
		csm.h nodeptr.h

header.o:	header.c err.h deftbl.h envmod.h ptg_gen.h func.h pdl_gen.h \
		csm.h eliproto.h obstack.h BitSet.h ptg.h header.h \
		ElementList.h KnownKey.h CoordCmp.h Element.h \
		ElementFunctionTypes.h

type.o:	type.c ptg_gen.h deftbl.h envmod.h func.h pdl_gen.h type.h \
		eliproto.h ptg.h obstack.h BitSet.h header.h ElementList.h \
		KnownKey.h CoordCmp.h Element.h ElementFunctionTypes.h \
		err.h

obstack.o:	obstack.c config.h obstack.h exitfail.h gettext.h


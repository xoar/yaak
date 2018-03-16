SHELL   = /bin/sh

CC	= gcc

OBJS	= driver.o clpintf.o clp.o csm.o obsave.o deftbl.o err.o \
	source.o pdl_gen.o VoidPtrList.o clplib.o treecon.o \
	nodecode.o parser.o glahead.o auxNUL.o auxEOF.o dflteot.o \
	tabsize.o idn.o pascalStr.o auxScanEOL.o pgs_gen.o \
	treestack.o dfltrepar.o attrmain.o visitprocs.o visitmap.o \
	ptg_gen.o PtgCommon.o MakeName.o ebnf.o obstack.o

EXE	= ebnf.exe

all:	$(EXE)

$(EXE):	$(OBJS)
	$(CC) -o $(EXE) $(CFLAGS) $(OBJS) $(LIBS)

objects: $(OBJS)

clean:
	rm -f a.out *.o *.a *~ core ERRS $(EXE)

tidy:
	rm -f core a.out *.o *~ *.a ERRS

driver.o:	driver.c err.h HEAD.h INIT.h FINL.h eliproto.h clp.h \
		VoidPtrList.h DefTableKeyList.h PTGNodeList.h MakeName.h \
		ebnf.h ptg_gen.h pdl_gen.h deftbl.h treecon.h PtgCommon.h \
		clplib.h VoidPtr.h VoidPtrFunctionTypes.h ptg.h nodeptr.h \
		csm.h obstack.h

clpintf.o:	clpintf.c clp.h clpintf.h csm.h eliproto.h pdl_gen.h \
		source.h clplib.h DefTableKeyList.h deftbl.h VoidPtrList.h \
		VoidPtr.h VoidPtrFunctionTypes.h obstack.h

clp.o:	clp.c clp.h clpintf.h pdl_gen.h csm.h eliproto.h clplib.h \
		DefTableKeyList.h deftbl.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h obstack.h

csm.o:	csm.c csm.h csmtbl.h obsave.h obstack.h eliproto.h

obsave.o:	obsave.c obsave.h obstack.h eliproto.h

deftbl.o:	deftbl.c err.h deftbl.h obstack.h obsave.h eliproto.h

err.o:	err.c err.h source.h eliproto.h

source.o:	source.c source.h

pdl_gen.o:	pdl_gen.c pdl_gen.h deftbl.h eliproto.h

VoidPtrList.o:	VoidPtrList.c VoidPtrList.h err.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h eliproto.h

clplib.o:	clplib.c csm.h clplib.h obstack.h eliproto.h

treecon.o:	treecon.c node.h nodecode.h attrpredef.h visitmap.h \
		treeact.h obstack.h err.h nodeptr.h HEAD.h eliproto.h clp.h \
		VoidPtrList.h DefTableKeyList.h PTGNodeList.h MakeName.h \
		ebnf.h ptg_gen.h pdl_gen.h deftbl.h treecon.h PtgCommon.h \
		clplib.h VoidPtr.h VoidPtrFunctionTypes.h ptg.h csm.h

nodecode.o:	nodecode.c nodecode.h

parser.o:	parser.c err.h gla.h gsdescr.h reparatur.h pgs_gen.h \
		eliproto.h parsops.h

glahead.o:	glahead.c err.h csm.h source.h obstack.h scanops.h \
		tabsize.h ScanProc.h gla.h xtables.h xcode.h eliproto.h

auxNUL.o:	auxNUL.c source.h gla.h

auxEOF.o:	auxEOF.c 

dflteot.o:	dflteot.c 

tabsize.o:	tabsize.c 

idn.o:	idn.c err.h idn.h csm.h obstack.h obsave.h idntbl.h \
		eliproto.h

pascalStr.o:	pascalStr.c err.h gla.h tabsize.h eliproto.h

auxScanEOL.o:	auxScanEOL.c eliproto.h err.h gla.h source.h ScanProc.h

pgs_gen.o:	pgs_gen.c gsdescr.h treestack.h HEAD.h err.h parsops.h \
		eliproto.h nodeptr.h clp.h VoidPtrList.h DefTableKeyList.h \
		PTGNodeList.h MakeName.h ebnf.h ptg_gen.h pdl_gen.h \
		deftbl.h treecon.h PtgCommon.h clplib.h VoidPtr.h \
		VoidPtrFunctionTypes.h ptg.h csm.h obstack.h

treestack.o:	treestack.c err.h treestack.h eliproto.h nodeptr.h

dfltrepar.o:	dfltrepar.c err.h reparatur.h eliproto.h

attrmain.o:	attrmain.c treestack.h visitprocs.h nodeptr.h HEAD.h node.h \
		treecon.h eliproto.h clp.h VoidPtrList.h DefTableKeyList.h \
		PTGNodeList.h MakeName.h ebnf.h ptg_gen.h pdl_gen.h \
		deftbl.h PtgCommon.h clplib.h VoidPtr.h \
		VoidPtrFunctionTypes.h ptg.h err.h csm.h obstack.h

visitprocs.o:	visitprocs.c HEAD.h err.h node.h visitprocs.h attrpredef.h \
		visitmap.h clp.h VoidPtrList.h DefTableKeyList.h \
		PTGNodeList.h MakeName.h ebnf.h ptg_gen.h pdl_gen.h \
		deftbl.h treecon.h PtgCommon.h clplib.h eliproto.h \
		VoidPtr.h VoidPtrFunctionTypes.h ptg.h nodeptr.h csm.h \
		obstack.h

visitmap.o:	visitmap.c visitprocs.h visitmap.h HEAD.h node.h treecon.h \
		eliproto.h clp.h VoidPtrList.h DefTableKeyList.h \
		PTGNodeList.h MakeName.h ebnf.h ptg_gen.h pdl_gen.h \
		deftbl.h PtgCommon.h clplib.h VoidPtr.h \
		VoidPtrFunctionTypes.h ptg.h err.h nodeptr.h csm.h \
		obstack.h

ptg_gen.o:	ptg_gen.c ptg_gen.h obstack.h eliproto.h ptg.h

PtgCommon.o:	PtgCommon.c PtgCommon.h eliproto.h ptg_gen.h csm.h ptg.h \
		obstack.h

MakeName.o:	MakeName.c err.h csm.h idn.h termcode.h MakeName.h \
		eliproto.h obstack.h

ebnf.o:	ebnf.c ebnf.h ptg_gen.h PTGNodeList.h eliproto.h \
		VoidPtrList.h ptg.h VoidPtr.h VoidPtrFunctionTypes.h

obstack.o:	obstack.c config.h obstack.h gettext.h


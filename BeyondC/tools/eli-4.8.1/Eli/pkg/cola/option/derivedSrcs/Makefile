SHELL   = /bin/sh

CC	= gcc

OBJS	= driver.o clpintf.o clp.o csm.o obsave.o deftbl.o err.o \
	source.o pdl_gen.o VoidPtrList.o clplib.o treecon.o \
	nodecode.o parser.o treestack.o glahead.o auxNUL.o auxEOF.o \
	dflteot.o tabsize.o int.o auxScanEOL.o Ccomment.o \
	dfltrepar.o attrmain.o visitprocs.o visitmap.o optdefs.o \
	optcheck.o optcode.o ptg_gen.o obstack.o

EXE	= option.exe

all:	$(EXE)

$(EXE):	$(OBJS)
	$(CC) -o $(EXE) $(CFLAGS) $(OBJS) $(LIBS)

objects: $(OBJS)

clean:
	rm -f a.out *.o *.a *~ core ERRS $(EXE)

tidy:
	rm -f core a.out *.o *~ *.a ERRS

driver.o:	driver.c err.h HEAD.h dapto.h dapto_dapto.h INIT.h FINL.h \
		eliproto.h clp.h ptg_gen.h optdefs.h optcheck.h optcode.h \
		pdl_gen.h treecon.h DefTableKeyList.h deftbl.h \
		VoidPtrList.h clplib.h VoidPtr.h VoidPtrFunctionTypes.h \
		ptg.h nodeptr.h

clpintf.o:	clpintf.c clp.h clpintf.h csm.h eliproto.h pdl_gen.h \
		source.h clplib.h DefTableKeyList.h deftbl.h VoidPtrList.h \
		VoidPtr.h VoidPtrFunctionTypes.h obstack.h

clp.o:	clp.c clp.h clpintf.h pdl_gen.h csm.h eliproto.h clplib.h \
		DefTableKeyList.h deftbl.h VoidPtrList.h VoidPtr.h \
		VoidPtrFunctionTypes.h obstack.h

csm.o:	csm.c csm.h csmtbl.h dapto_dapto.h csm_dapto.h obsave.h \
		obstack.h eliproto.h dapto.h

obsave.o:	obsave.c obsave.h obstack.h eliproto.h

deftbl.o:	deftbl.c err.h deftbl.h obstack.h obsave.h eliproto.h

err.o:	err.c err.h source.h dapto_dapto.h err_dapto.h eliproto.h \
		dapto.h

source.o:	source.c source.h dapto_dapto.h dapto.h eliproto.h

pdl_gen.o:	pdl_gen.c pdl_gen.h deftbl.h eliproto.h

VoidPtrList.o:	VoidPtrList.c VoidPtrList.h err.h obstack.h VoidPtr.h \
		VoidPtrFunctionTypes.h eliproto.h

clplib.o:	clplib.c csm.h clplib.h obstack.h eliproto.h

treecon.o:	treecon.c node.h nodecode.h attrpredef.h visitmap.h \
		treeact.h obstack.h err.h nodeptr.h HEAD.h eliproto.h clp.h \
		ptg_gen.h optdefs.h optcheck.h optcode.h pdl_gen.h \
		treecon.h DefTableKeyList.h deftbl.h VoidPtrList.h clplib.h \
		VoidPtr.h VoidPtrFunctionTypes.h ptg.h

nodecode.o:	nodecode.c nodecode.h

parser.o:	parser.c err.h treestack.h gsdescr.h HEAD.h reparatur.h \
		gla.h parser.h dapto_dapto.h semprods.h ptabs.h eliproto.h \
		nodeptr.h parsops.h clp.h ptg_gen.h optdefs.h optcheck.h \
		optcode.h pdl_gen.h treecon.h DefTableKeyList.h deftbl.h \
		VoidPtrList.h clplib.h VoidPtr.h VoidPtrFunctionTypes.h \
		ptg.h dapto.h

treestack.o:	treestack.c err.h treestack.h eliproto.h nodeptr.h

glahead.o:	glahead.c err.h csm.h source.h obstack.h scanops.h \
		tabsize.h ScanProc.h gla.h dapto_dapto.h xtables.h xcode.h \
		eliproto.h dapto.h

auxNUL.o:	auxNUL.c source.h gla.h

auxEOF.o:	auxEOF.c 

dflteot.o:	dflteot.c 

tabsize.o:	tabsize.c 

int.o:	int.c obstack.h csm.h err.h eliproto.h

auxScanEOL.o:	auxScanEOL.c eliproto.h err.h gla.h source.h ScanProc.h

Ccomment.o:	Ccomment.c err.h gla.h source.h tabsize.h ScanProc.h \
		eliproto.h

dfltrepar.o:	dfltrepar.c err.h reparatur.h eliproto.h

attrmain.o:	attrmain.c treestack.h visitprocs.h nodeptr.h HEAD.h node.h \
		treecon.h eliproto.h clp.h ptg_gen.h err.h optdefs.h \
		optcheck.h optcode.h pdl_gen.h DefTableKeyList.h deftbl.h \
		VoidPtrList.h clplib.h VoidPtr.h VoidPtrFunctionTypes.h \
		ptg.h

visitprocs.o:	visitprocs.c HEAD.h err.h node.h visitprocs.h attrpredef.h \
		visitmap.h clp.h ptg_gen.h optdefs.h optcheck.h optcode.h \
		pdl_gen.h treecon.h DefTableKeyList.h deftbl.h \
		VoidPtrList.h clplib.h eliproto.h VoidPtr.h \
		VoidPtrFunctionTypes.h ptg.h nodeptr.h

visitmap.o:	visitmap.c visitprocs.h visitmap.h HEAD.h node.h treecon.h \
		eliproto.h clp.h ptg_gen.h err.h optdefs.h optcheck.h \
		optcode.h pdl_gen.h DefTableKeyList.h deftbl.h \
		VoidPtrList.h clplib.h VoidPtr.h VoidPtrFunctionTypes.h \
		ptg.h nodeptr.h

optdefs.o:	optdefs.c optdefs.h

optcheck.o:	optcheck.c err.h eliproto.h

optcode.o:	optcode.c optdefs.h ptg_gen.h clp.h optcode.h eliproto.h \
		ptg.h clplib.h pdl_gen.h DefTableKeyList.h deftbl.h \
		VoidPtrList.h VoidPtr.h VoidPtrFunctionTypes.h

ptg_gen.o:	ptg_gen.c ptg_gen.h obstack.h eliproto.h ptg.h

obstack.o:	obstack.c config.h obstack.h gettext.h


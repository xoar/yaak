SHELL   = /bin/sh

CC	= gcc

OBJS	= driver.o clpintf.o clp.o csm.o obsave.o deftbl.o err.o \
	source.o pdl_gen.o VoidPtrList.o clplib.o opt_liga.o \
	keywords.o various.o optlists.o treecon.o nodecode.o \
	treebuild.o parser.o treestack.o glahead.o auxNUL.o \
	auxEOF.o dflteot.o tabsize.o idn.o int.o auxScanEOL.o \
	Ccomment.o dfltrepar.o attrmain.o visitprocs.o visitmap.o \
	conflicts.o output.o obstack.o

EXE	= option.exe

all:	$(EXE)

$(EXE):	$(OBJS)
	$(CC) -o $(EXE) $(CFLAGS) $(OBJS) $(LIBS)

objects: $(OBJS)

clean:
	rm -f a.out *.o *.a *~ core ERRS $(EXE)

tidy:
	rm -f core a.out *.o *~ *.a ERRS

driver.o:	driver.c err.h HEAD.h INIT.h FINL.h eliproto.h clp.h csm.h \
		option_enums.h option_types.h keywords.h various.h \
		optlists.h output.h conflicts.h opt_liga.h pdl_gen.h \
		deftbl.h treecon.h DefTableKeyList.h VoidPtrList.h clplib.h \
		VoidPtr.h VoidPtrFunctionTypes.h obstack.h nodeptr.h

clpintf.o:	clpintf.c clplib.h clpintf.h eliproto.h

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

opt_liga.o:	opt_liga.c opt_liga.h csm.h option_enums.h option_types.h \
		keywords.h various.h optlists.h output.h conflicts.h \
		obstack.h eliproto.h

keywords.o:	keywords.c keywords.h

various.o:	various.c err.h opt_liga.h eliproto.h csm.h option_enums.h \
		option_types.h keywords.h various.h optlists.h output.h \
		conflicts.h obstack.h

optlists.o:	optlists.c opt_liga.h csm.h option_enums.h option_types.h \
		keywords.h various.h optlists.h output.h conflicts.h \
		obstack.h eliproto.h

treecon.o:	treecon.c node.h nodecode.h attrpredef.h visitmap.h \
		treeact.h obstack.h err.h nodeptr.h HEAD.h eliproto.h clp.h \
		csm.h option_enums.h option_types.h keywords.h various.h \
		optlists.h output.h conflicts.h opt_liga.h pdl_gen.h \
		deftbl.h treecon.h DefTableKeyList.h VoidPtrList.h clplib.h \
		VoidPtr.h VoidPtrFunctionTypes.h

nodecode.o:	nodecode.c nodecode.h

treebuild.o:	treebuild.c eliproto.h pdl_gen.h source.h csm.h clp.h \
		clpintf.h deftbl.h obstack.h clplib.h DefTableKeyList.h \
		VoidPtrList.h VoidPtr.h VoidPtrFunctionTypes.h

parser.o:	parser.c err.h treestack.h gsdescr.h HEAD.h reparatur.h \
		gla.h parser.h semprods.h ptabs.h eliproto.h nodeptr.h \
		parsops.h clp.h csm.h option_enums.h option_types.h \
		keywords.h various.h optlists.h output.h conflicts.h \
		opt_liga.h pdl_gen.h deftbl.h treecon.h DefTableKeyList.h \
		VoidPtrList.h clplib.h VoidPtr.h VoidPtrFunctionTypes.h \
		obstack.h

treestack.o:	treestack.c err.h treestack.h eliproto.h nodeptr.h

glahead.o:	glahead.c err.h csm.h source.h obstack.h scanops.h \
		tabsize.h ScanProc.h gla.h xtables.h xcode.h eliproto.h

auxNUL.o:	auxNUL.c source.h gla.h

auxEOF.o:	auxEOF.c 

dflteot.o:	dflteot.c 

tabsize.o:	tabsize.c 

idn.o:	idn.c err.h idn.h csm.h obstack.h obsave.h idntbl.h \
		eliproto.h

int.o:	int.c obstack.h csm.h err.h eliproto.h

auxScanEOL.o:	auxScanEOL.c eliproto.h err.h gla.h source.h ScanProc.h

Ccomment.o:	Ccomment.c err.h gla.h source.h tabsize.h ScanProc.h \
		eliproto.h

dfltrepar.o:	dfltrepar.c err.h reparatur.h eliproto.h

attrmain.o:	attrmain.c treestack.h visitprocs.h nodeptr.h err.h \
		eliproto.h HEAD.h node.h treecon.h clp.h csm.h \
		option_enums.h option_types.h keywords.h various.h \
		optlists.h output.h conflicts.h opt_liga.h pdl_gen.h \
		deftbl.h DefTableKeyList.h VoidPtrList.h clplib.h VoidPtr.h \
		VoidPtrFunctionTypes.h obstack.h

visitprocs.o:	visitprocs.c HEAD.h err.h node.h visitprocs.h attrpredef.h \
		visitmap.h clp.h csm.h option_enums.h option_types.h \
		keywords.h various.h optlists.h output.h conflicts.h \
		opt_liga.h pdl_gen.h deftbl.h treecon.h DefTableKeyList.h \
		VoidPtrList.h clplib.h eliproto.h VoidPtr.h \
		VoidPtrFunctionTypes.h obstack.h nodeptr.h

visitmap.o:	visitmap.c visitprocs.h visitmap.h HEAD.h node.h treecon.h \
		eliproto.h clp.h csm.h option_enums.h option_types.h \
		keywords.h various.h optlists.h output.h conflicts.h err.h \
		opt_liga.h pdl_gen.h deftbl.h DefTableKeyList.h \
		VoidPtrList.h clplib.h VoidPtr.h VoidPtrFunctionTypes.h \
		obstack.h nodeptr.h

conflicts.o:	conflicts.c opt_liga.h csm.h option_enums.h option_types.h \
		keywords.h various.h optlists.h output.h conflicts.h \
		obstack.h eliproto.h

output.o:	output.c opt_liga.h csm.h option_enums.h option_types.h \
		keywords.h various.h optlists.h output.h conflicts.h \
		obstack.h eliproto.h

obstack.o:	obstack.c obstack.h gettext.h


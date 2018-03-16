# $Id: Adtmk.h,v 1.6 2001/05/09 20:43:04 waite Exp $
# Abstract data type library

ADTLIB	= $(ELISYS)/pkg/Adt
ADTINCL	= -I$(ADTLIB) -I$(ELILIB)

csm.o:	$(ADTLIB)/csm.c $(ADTLIB)/csm.h $(ELILIB)/eliproto.h
	$(CC) $(CFLAGS) $(ADTINCL) -c $(ADTLIB)/csm.c

obstack.o:	$(ADTLIB)/obstack.c $(ADTLIB)/obstack.h
	$(CC) $(CFLAGS) $(ADTINCL) -c $(ADTLIB)/obstack.c

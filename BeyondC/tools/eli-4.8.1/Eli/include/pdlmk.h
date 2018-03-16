# $Id: pdlmk.h,v 1.4 2001/05/09 20:43:05 waite Exp $
# PDL definition table library

PDLLIB	= $(ELISYS)/pkg/pdl
PDLINCL	= -I$(PDLLIB)

DEFDEPS = $(PDLLIB)/deftbl.c $(PDLLIB)/deftbl.h $(INPLIB)/err.h \
	  $(ADTLIB)/obstack.h

deftbl.o:	$(DEFDEPS)
	$(CC) $(CFLAGS) $(PDLINCL) $(INPINCL) $(ADTINCL) -c \
		$(PDLLIB)/deftbl.c

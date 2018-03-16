# $Id: Inputmk.h,v 1.5 2008/04/26 14:21:19 profw Exp $
# Input library

INPLIB	= $(ELISYS)/pkg/Input
INPINCL	= -I$(INPLIB) -I$(ELILIB)

err.o:	$(INPLIB)/err.c $(INPLIB)/err.h $(INPLIB)/source.h $(ELILIB)/eliproto.h
	$(CC) $(CFLAGS) $(INPINCL) -c $(INPLIB)/err.c

source.o:	$(INPLIB)/source.c $(INPLIB)/source.h
	$(CC) $(CFLAGS) $(INPINCL) -c $(INPLIB)/source.c

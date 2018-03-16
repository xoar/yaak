# $Id: Scanmk.h,v 1.7 2008/04/26 14:21:19 profw Exp $
# Scanner library

SCNLIB	= $(ELISYS)/pkg/Scan
GLAPKG	= $(ELISYS)/pkg/gla

SCNINCL	= -I$(SCNLIB) -I$(GLAPKG) $(INPINCL) $(ADTINCL)

CchStr.o:	$(SCNLIB)/CchStr.c $(GLAPKG)/gla.h $(INPLIB)/source.h
CchStr.o:	$(INPLIB)/err.h
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/CchStr.c

Ccomment.o:	$(SCNLIB)/Ccomment.c $(GLAPKG)/gla.h $(INPLIB)/source.h
Ccomment.o:	$(INPLIB)/err.h $(GLAPKG)/tabsize.h
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/Ccomment.c

M2chStr.o:	$(SCNLIB)/M2chStr.c $(GLAPKG)/gla.h $(INPLIB)/source.h
M2chStr.o:	$(INPLIB)/err.h
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/M2chStr.c

M2int.o:	$(SCNLIB)/M2int.c
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/M2int.c

M3comment.o:	$(SCNLIB)/M3comment.c $(GLAPKG)/gla.h $(INPLIB)/source.h
M3comment.o:	$(INPLIB)/err.h $(GLAPKG)/tabsize.h
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/M3comment.c

auxEOF.o:	$(SCNLIB)/auxEOF.c
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/auxEOF.c

auxNUL.o:	$(SCNLIB)/auxNUL.c $(GLAPKG)/gla.h $(INPLIB)/source.h
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/auxNUL.c

auxNewLine.o:	$(SCNLIB)/auxNewLine.c $(GLAPKG)/gla.h $(INPLIB)/err.h
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/auxNewLine.c

auxScanEOL.o:	$(SCNLIB)/auxScanEOL.c $(GLAPKG)/gla.h $(INPLIB)/source.h
		$(INPLIB)/err.h
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/auxScanEOL.c

auxTab.o:	$(SCNLIB)/auxTab.c $(GLAPKG)/gla.h $(GLAPKG)/tabsize.h
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/auxTab.c

coordAdjust.o:	$(SCNLIB)/coordAdjust.c $(GLAPKG)/gla.h $(INPLIB)/err.h
coordAdjust.o:	$(GLAPKG)/tabsize.h
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/coordAdjust.c

dflteot.o:	$(SCNLIB)/dflteot.c
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/dflteot.c

dfltscan.o:	$(SCNLIB)/dfltscan.c
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/dfltscan.c

idn.o:	$(SCNLIB)/idn.c $(INPLIB)/err.h $(SCNLIB)/idn.h $(ADTLIB)/csm.h \
	$(ELILIB)/eliproto.h
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/idn.c

int.o:	$(SCNLIB)/int.c
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/int.c

pascalCom.o:	$(SCNLIB)/pascalCom.c $(GLAPKG)/gla.h $(INPLIB)/source.h
pascalCom.o:	$(INPLIB)/err.h $(GLAPKG)/tabsize.h
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/pascalCom.c

pascalStr.o:	$(SCNLIB)/pascalStr.c $(GLAPKG)/gla.h $(INPLIB)/err.h
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/pascalStr.c

str.o:	$(SCNLIB)/str.c $(ADTLIB)/csm.h
	$(CC) $(CFLAGS) $(SCNINCL) -c $(SCNLIB)/str.c

#!/bin/sh
# $Id: cexe.sh,v 2.2 2003/03/06 01:20:58 waite Exp $
# Copyright 1999, The Regents of the University of Colorado

# EXEC (cexe.sh) (:c) (+cc) (+cc_flags) => (:exe);

ODIN_c=$1;shift; ODIN_cc=$1;shift; ODIN_flags=$1;shift;
touch exe

if test "$ODIN_cc" != ""; then ELI_CC=$ODIN_cc; fi
CCPROG=${ELI_CC-$ODIN_CC}

${CCPROG} -o exe $ODIN_flags $ODIN_c 2>WARNINGS \
  || { mv WARNINGS ERRORS; echo "${CCPROG} failed" >>ERRORS; }

if test -x exe.exe; then mv exe.exe exe; fi

exit 0

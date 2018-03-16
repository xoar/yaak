#!/bin/sh
# $Id: burgGen.sh,v 1.7 2002/05/08 15:00:48 waite Exp $
# Copyright 1997, The Regents of the University of Colorado

# EXEC (burgGen.sh) (burg.exe) (burg.err) (:burg.cmpd :cat)
#   => (:burgGen);
# :burgGen 'Objects generated from burg specifications' => :DERIVED-DIRECTORY;

ODIN_exe=$1;shift; ODIN_err=$1;shift; ODIN_Input=$1;shift;
mkdir burgGen;

$ODIN_exe -I -p TP $ODIN_Input 1>burgGen/burg.c 2>ERROR \
  || { if test ! -s ERROR; then echo 'burg failed' >ERRORS; exit 0; fi; }
if test -s ERROR
then
        echo '(|'"$ODIN_err"'|std_err|' > ERRORS
        $ODINCACHE/PKGS/skeleton/sed.exe 's;^line \([0-9]*\):;'"$ODIN_Input"' \1 0;' \
		ERROR >> ERRORS
        echo '|)' >> ERRORS
	exit 0
fi

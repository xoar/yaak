#!/bin/sh
# $Id: do_cpp.sh,v 1.2 2002/05/08 15:00:50 waite Exp $
# Copyright 1992, The Regents of the University of Colorado

# EXEC (do_cpp.sh) (.) (:FILE :incl.all :dir_of :vir_dir) (:FILE)
#   NEEDS (:FILE :incl.all)
#   => (:do_cpp);

PKG=$1;shift; ODIN_includes=$1;shift; ODIN_atomic=$1;shift;

if test -s "$ODIN_atomic"
then
	$PKG/cpp.exe -I"$ODIN_includes" $ODIN_atomic >do_cpp 2>ERROR
else
	cp /dev/null do_cpp
	exit 0
fi

if test -s ERROR
then
  $ODINCACHE/PKGS/skeleton/sed.exe 's/:  *\([0-9]*\):/ \1 0/' ERROR > ERRORS
else :
fi

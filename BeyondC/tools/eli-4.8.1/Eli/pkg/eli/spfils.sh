#!/bin/sh
# $Id: spfils.sh,v 2.2 2002/05/08 15:00:52 waite Exp $
# Copyright 1993, The Regents of the University of Colorado

# EXEC (spfils.sh) (:specs :dir)@ (.) (:specs) spfils
#   NEEDS (:specs :incl.all)
#   => (:spfils);

ODIN_CURDIR=$1; shift; PKG=$1;shift; ODIN_specs=$1;shift; ODIN_out=$1;shift;

# This script runs in the user's directory.

ODIN_RUNDIR=`pwd`; cd $ODIN_CURDIR
$ODINCACHE/PKGS/cpp/cpp.exe $ODIN_specs \
  > $ODIN_RUNDIR/cppspfils 2> $ODIN_RUNDIR/ERROR
cd $ODIN_RUNDIR

# The result of cpp has to be cleaned up by:
# 	1) Removing all white space
# 	2) Prefixing the name of each specification file by the name of the
# 		directory containing the file introducing it

if test -s ERROR
then
  $ODINCACHE/PKGS/skeleton/sed.exe 's/:  *\([0-9]*\):/ \1 0/' ERROR > ERRORS
  exit 0
fi

$PKG/cpp_specs.exe $ODIN_CURDIR $ODINCACHE/PKGS < cppspfils \
  > $ODIN_out 2> ERRORS

exit 0

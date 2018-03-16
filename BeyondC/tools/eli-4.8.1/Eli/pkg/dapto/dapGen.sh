#!/bin/sh
# $Id: dapGen.sh,v 2.13 2009/08/05 02:03:54 profw Exp $
# Copyright 1995-1998, Anthony M. Sloane

# This file is part of the Eli translator construction system.

# Eli is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2, or (at your option) any later
# version.

# Eli is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.

# You should have received a copy of the GNU General Public License along
# with Eli; see the file COPYING.  If not, write to the Free Software
# Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

# EXEC (dapGen.sh) (:dapto.cmpd :cpp) (:dapto.cmpd :labels)
#      (dapto.exe) (dapto.err) ($ODINCACHE/PKGS/skeleton/sed.exe)
#   => (:dapGen);
#
# :dapGen 'Objects generated from a dapto specification'
#   => :DERIVED-DIRECTORY;

ODIN_RUNDIR=`pwd`;
ODIN_dapto=$1;shift; ODIN_daptolabel=$1;shift;
dapto_exe=$1;shift; dapto_err=$1;shift; SED=$1;shift;

mkdir dapGen
cd ./dapGen

label=`cat $ODIN_daptolabel`
base=`basename $label .dapto`

$dapto_exe -base $base $ODIN_dapto 1>/dev/null 2> $ODIN_RUNDIR/ERROR

cd $ODIN_RUNDIR
if test -s ERROR
then
    echo '(|'"$dapto_err"'|std_err|' > ERRORS
    echo '(|'"$ODIN_dapto"'|line_err|' >> ERRORS
    $SED 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
	ERROR >> ERRORS
    echo '|)' >> ERRORS
    echo '|)' >> ERRORS
else :
fi


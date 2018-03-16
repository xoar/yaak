#!/bin/sh
# $Id: clp_gen.sh,v 2.14 2010/03/03 22:58:07 profw Exp $
# Copyright, 1990, The University of Colorado
# Copyright, 1995-1999, Anthony M. Sloane

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

# EXEC (clp_gen.sh) (clp.exe) (:clp.cmpd :cpp) (clp.err)
#      ($ODINCACHE/PKGS/skeleton/sed.exe)
#   => (:clp_gen);
# 
# :clp_gen 'Objects generated from CLP specifications' => :DERIVED-DIRECTORY;

ODIN_exe=$1;shift; ODIN_cmpd=$1;shift; ODIN_err=$1;shift;
SED=$1;shift;

mkdir clp_gen;

# put the clp comment indicator '%' in front of cpp control lines
$SED -e '/^#/s/^/%/' "$ODIN_cmpd" > INFILE

# run the clp compiler
($ODIN_exe INFILE || echo 'CLP compiler failed') >ERROR 2>&1

if test -s ERROR
then
    echo '(|'"$ODIN_err"'|std_err|' > ERRORS
    echo '(|'"$ODIN_cmpd"'|line_err|' >> ERRORS
    $SED \
        's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' ERROR >>ERRORS
    echo '|)' >> ERRORS
    echo '|)' >> ERRORS
    exit 0
else :
fi

# generated components
mv clp.c clp.h clp_gen


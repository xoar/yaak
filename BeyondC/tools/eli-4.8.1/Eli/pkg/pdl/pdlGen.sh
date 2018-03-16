#!/bin/sh
# $Id: pdlGen.sh,v 2.9 2010/02/26 17:50:58 profw Exp $
# Copyright 1992, The Regents of the University of Colorado

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

# EXEC (pdlGen.sh) (pdl.exe) (:pdl.cmpd :cpp) (lib.pdl) (pdl.err)
#      ($ODINCACHE/PKGS/skeleton/sed.exe)
#   => (:pdlGen);

ODIN_Exe=$1;shift; ODIN_Input=$1;shift; ODIN_Lib=$1;shift; ODIN_Err=$1;shift;
ODIN_Sed=$1;shift;
mkdir pdlGen;

cat $ODIN_Input > INFILE
echo '$LIBRARY' >> INFILE
cat $ODIN_Lib >> INFILE

$ODIN_Exe INFILE 1>/dev/null 2>ERROR
mv pdl_gen.c pdlGen
mv pdl_gen.h pdlGen
if test -f pdl_gen.init; then mv pdl_gen.init pdlGen; fi

if test -s ERROR
then
        echo '(|'"$ODIN_Err"'|std_err|' > ERRORS
        echo '(|'"$ODIN_Input"'|line_err|' >> ERRORS
        $ODIN_Sed 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		ERROR >> ERRORS
        echo '|)' >> ERRORS
        echo '|)' >> ERRORS
	exit 0
fi

echo '#include "pdl_gen.h"' > pdlGen/pdl_gen.head

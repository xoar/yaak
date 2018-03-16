#!/bin/sh
# $Id: oil_gen.sh,v 2.7 2002/05/08 15:01:01 waite Exp $
# Copyright 1990, The Regents of the University of Colorado

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

# EXEC (oil_gen.sh) (oil.exe) (:oil.cmpd :cpp) (oil.err)
#   => (:oil_gen);

ODIN_exe=$1;shift; ODIN_Input=$1;shift; ODIN_Err=$1;shift;
mkdir oil_gen;

$ODIN_exe $ODIN_Input 1>/dev/null 2>ERROR
if test -s ERROR
then
        echo '(|'"$ODIN_Err"'|std_err|' > ERRORS
        echo '(|'"$ODIN_Input"'|line_err|' >> ERRORS
        $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		ERROR >> ERRORS
        echo '|)' >> ERRORS
        echo '|)' >> ERRORS
	exit 0
fi

cp OilDecls.c OilDecls.h OilDecls.pdl oil_gen

echo '#include "oiladt2.h"' > oil_gen/oil.head

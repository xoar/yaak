#!/bin/sh
# $Id: tpGen.sh,v 1.6 2002/05/08 15:01:07 waite Exp $
# Copyright 1998, The Regents of the University of Colorado

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

# EXEC (tpGen.sh) (.) (:tp.cmpd :cpp) (+monitor)
#   NEED (tp.exe) (tp.err) (tp.INIT.phi) (tpnode.h) (tp.dapto) (tp.tcl)
#   => (:tpGen);

PKG=$1;shift;
ODIN_Input=$1;shift; ODIN_mon=$1;shift;
mkdir tpGen;

$PKG/tp.exe $ODIN_Input 1>/dev/null 2>ERROR
mv tp_gen.burg tpGen
mv tp_gen.h tpGen

if test -s ERROR
then
        echo '(|'"$PKG/tp.err"'|std_err|' > ERRORS
        echo '(|'"$ODIN_Input"'|line_err|' >> ERRORS
        $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		ERROR >> ERRORS
        echo '|)' >> ERRORS
        echo '|)' >> ERRORS
	exit 0
fi

cp $PKG/tp.INIT.phi $PKG/tpnode.h $PKG/tp.dapto $PKG/tp.tcl tpGen
echo '#include "tp_gen.h"' > tpGen/tp.HEAD.phi

if test "$ODIN_mon" != ''
then cp $PKG/tp.dapto $PKG/tp.tcl tpGen
else :
fi

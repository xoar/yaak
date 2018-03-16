#!/bin/sh
# $Id: showFe.sh,v 2.5 1997/08/29 08:13:57 peter Exp $
# Copyright, 1990, The University of Paderborn

# This file is part of the Eli translator construction system.
# 
# Eli is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2, or (at your option) any later
# version.
# 
# Eli is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
# 
# You should have received a copy of the GNU General Public License along
# with Eli; see the file COPYING.  If not, write to the Free Software
# Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  

PKG=$1;shift; ODIN_e94=$1;shift; ODIN_e95=$1;shift;  mkdir showFeDir;

# showFe[.none] 'Gives information about .lido specs after the initial analysis' :
#         USER
#                : (:level_4_specs:lido.cmpd :cpp)
#                : (:level_4_specs:lido.cmpd :cpp_tab)

"$ODINCACHE/PKGS/liga/ligaFe.exe" "$ODIN_e94" 1> ERRS 2>&1

if test ! -s liga.out
then
        echo '".", line 0:0 DEADLY: no input for step showFe' >> ERRS 
        exit 0
fi

"$ODINCACHE/PKGS/liga/ligaShow.exe" \
	-i liga.out \
	-e "$ODIN_e95" 1> ERRS2  2>&1

if test -s ERRS2
then
	cat ERRS2 >> ERRS
fi

if test -s core
then
        echo '".", line 0:0 DEADLY: Tool LIGA Show failed' >> ERRS
fi

## Producing no errors, but only warnings
if test -s ERRS
then
        echo '(|'"$ODINCACHE/PKGS/liga/Info/front.err"'|std_err|' > WARNINGS
        echo '(|'"$ODIN_e94"'|line_err|' >> WARNINGS
        $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		ERRS >> WARNINGS
        echo '|)' >> WARNINGS
        echo '|)' >> WARNINGS
fi

mv attrs.info symbols.info visit.info showFeDir

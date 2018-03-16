#!/bin/sh
# $Id: showMe.sh,v 2.4 1997/08/29 08:13:57 peter Exp $
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

PKG=$1;shift; ODIN_e96=$1;shift; ODIN_e97=$1;shift; ODIN_e98=$1;shift; ODIN_e99=$1;shift; ODIN_e100=$1;shift; ODIN_e101=$1;shift;  mkdir showMeDir;

# EXEC (showMe.sh) (.) (:level_4_specs :lido.cmpd :cpp) 
#                      (:level_4_specs :lido.cmpd :cpp_tab) 
#                      (:level_4_specs :ligaFe) (:level_4_specs :exp_option) 
#                      (:level_4_specs :ord_option) (:level_4_specs :optUoption)
#  => (:showMeDir);

"$ODINCACHE/PKGS/liga/ligaMe.exe" \
        -i "$ODIN_e98" \
        -c "$ODIN_e99" \
        -d "$ODIN_e100" \
        -t optEoption \
        -e "$ODIN_e101" optEoption \
	-l "$ODIN_e97" \
        -o MeIdl \
        -p MeInfo          > /dev/null 2> ERROR


if test ! -s MeIdl
then
        echo '".", line 0:0 DEADLY: no input for step showMe' >> ERROR
else
	"$ODINCACHE/PKGS/liga/ligaShow.exe" \
		-i MeIdl \
	        -e "$ODIN_e97" 1> ERRS2  2>&1

	if test -s ERRS2
	then
        	cat ERRS2 >> ERROR
	fi
	if test -s core
	then
        	echo '".", line 0:0 DEADLY: Tool LIGA Show failed' >> ERROR
	fi
fi

## delete Notes
if test -s ERROR
then
        $ODINCACHE/PKGS/skeleton/sed.exe '/NOTE/d' ERROR > ERRS
fi

## Producing no errors, but only warnings
if test -s ERRS
then
        echo '(|'"$ODINCACHE/PKGS/liga/Info/middle.err"'|std_err|' > WARNINGS
        echo '(|'"$ODIN_e96"'|line_err|' >> WARNINGS
        $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		ERRS >> WARNINGS
        echo '|)' >> WARNINGS
        echo '|)' >> WARNINGS
fi

if test -s MeIdl
then	mv attrs.info symbols.info visit.info showMeDir
fi







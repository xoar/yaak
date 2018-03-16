#!/bin/sh
# $Id: ptg_gen.sh,v 2.6 1997/08/28 15:16:12 cogito Exp $
# Copyright (C) 1997 University of Paderborn
# 
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

PKG=$1;shift; ODIN_e52=$1;shift;  mkdir ptg_gen;

#ptg_gen[.none] "Objects generated from PTG specifications"* :
#	USER
#		: (:ptg.cmpd :cpp)

"$ODINCACHE/PKGS/ptg/ptg.exe" "$ODIN_e52" 1>ERROR 2>&1

if test -s core
then
	echo '"INFILE", line 0:0 FATAL: Tool PTG failed.' >> ERROR
fi

if test -s ERROR
then
	$ODINCACHE/PKGS/skeleton/sed.exe -n -f "$ODINCACHE/PKGS/ptg/mess_sort" ERROR
fi

if test -s WARN
then
        echo '(|'"$ODINCACHE/PKGS/ptg/ptg.err"'|std_err|' > WARNINGS
        echo '(|'"$ODIN_e52"'|line_err|' >> WARNINGS
        $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		WARN >> WARNINGS
        echo '|)' >> WARNINGS
        echo '|)' >> WARNINGS
else :
fi

if test -s ERRS
then
        echo '(|'"$ODINCACHE/PKGS/ptg/ptg.err"'|std_err|' > ERRORS
        echo '(|'"$ODIN_e52"'|line_err|' >> ERRORS
        $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		ERRS >> ERRORS
        echo '|)' >> ERRORS
        echo '|)' >> ERRORS
else :
fi

if test -f ptg_gen.h
then
	mv ptg_gen.h ptg_gen/ptg_gen.h
fi

if test -s ptg_gen.c
then
	mv ptg_gen.c ptg_gen/ptg_gen.c
fi	

#!/bin/sh
# $Id: colaOpt.sh,v 2.3 1997/08/29 09:43:29 mjung Exp $
# 
# (C) Copyright 1997 University of Paderborn
# 
# /* This file is part of the Eli translator construction system.
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
# 

PKG=$1;shift; ODIN_e128=$1;shift;
SED=$ODINCACHE/PKGS/skeleton/sed.exe

# EXEC (colaOpt.sh) (.) (:cola.cmpd :cpp)
#   => (:colaLalrOpt) (:colaBackOpt) (:colaErrOff);
#         :colaLalrOpt 'cola analyzer options' => :FILE;
#         :colaBackOpt 'cola backend options' => :FILE;
#         :colaErrOff 'macro to stop the table driven parser after the first syntax error' 
#		=> :FILE;

if test -s "$ODIN_e128"
then cp "$ODIN_e128"  opt
else echo '# no options' > opt 
fi

"$ODINCACHE/PKGS/cola/colaOption.exe" -table  opt 1>ERROR 2>&1
if test -s core
then
    echo '".", line 0:0 DEADLY: Tool COLA option failed' >> ERROR
fi

if test -s ERROR
then
  $SED -n -f $ODINCACHE/PKGS/cola/Info/mess_sort ERROR
fi

if test -s ERRS
then
    echo '(|'"$ODINCACHE/PKGS/cola/Info/option.err"'|std_err|' > ERRORS
    echo '(|'"$ODIN_e128"'|line_err|' >> ERRORS
    $SED 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		ERRS >> ERRORS
    echo '|)' >> ERRORS
    echo '|)' >> ERRORS
else
    mv table.opt	colaBackOpt
    mv table.2.opt	colaErrOff
    mv frontend.opt	colaLalrOpt
fi

if test -s WARN
then
    echo '(|'"$ODINCACHE/PKGS/cola/Info/option.err"'|std_err|' > WARNINGS
    echo '(|'"$ODIN_e128"'|line_err|' >> WARNINGS
    $SED 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
		WARN >> WARNINGS
    echo '|)' >> WARNINGS
    echo '|)' >> WARNINGS
else :
fi

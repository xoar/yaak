#!/bin/sh
# $Id: colaFe.sh,v 2.4 1997/08/29 09:43:29 mjung Exp $
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

ODIN_pgram=$1;shift; ODIN_bupgram=$1;shift;

# EXEC (colaFe.sh) (:Pgram) (:BuPgram)
#   => (:colaCmrIn) (:colaCmrBuIn);
# 	:colaCmrIn 'EBNF-COMAR data structure without bottomup constraints'
# 	  => :FILE;
# 	:colaCmrBuIn 'EBNF-COMAR data structure with bottomup constraints'
# 	  => :FILE;

"$ODINCACHE/PKGS/cola/colaPgs2cm.exe" -cmr colaCmrIn "$ODIN_pgram" \
    1> ERROR 2>&1

if test -s $ODIN_bupgram
then
    "$ODINCACHE/PKGS/cola/colaPgs2cm.exe" -cmr colaCmrBuIn "$ODIN_bupgram" \
	1> tmp 2>&1
else
    cp /dev/null colaCmrBuIn
fi

if test -s core
then
   echo 'DEADLY: COLA Frontend failed' >> ERROR
fi

if test -s ERROR
then
  echo '(|'"$ODINCACHE/PKGS/cola/Info/cola.err"'|std_err|' > ERRORS
  $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
        ERROR >> ERRORS
  echo '|)' >> ERRORS
else :
fi

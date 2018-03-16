#! /bin/sh
# $Id: mapBuGen.sh,v 2.5 2005/06/08 15:18:24 profw Exp $
# Copyright 1997, The Regents of the University of Colorado

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

# EXEC (mapBuGen.sh) (maptool.exe) (:mapIn :cpp)
#      (:LIST :extract=:MeBottomUp :cat) (maptool.err)
#   => (:mapBuPgram);
# :mapBuPgram 'Parsing grammar with bottomup constraints' => :FILE;

ODIN_maptool=$1;shift; ODIN_mapIn=$1;shift; ODIN_BottomUp=$1;shift;
ODIN_err=$1;shift;

echo '$BOTTOMUP' | cat $ODIN_mapIn - $ODIN_BottomUp > input

$ODIN_maptool input > /dev/null 2> ERROR

if test -s ERROR
then
  echo '(|'"$ODIN_err"'|std_err|'     > ERRORS
  echo '(|'"$ODIN_mapIn"'|line_err|' >> ERRORS
  $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
	ERROR >> ERRORS
  echo '|)' >> ERRORS
  echo '|)' >> ERRORS
  exit 0
fi

cp pgram mapBuPgram

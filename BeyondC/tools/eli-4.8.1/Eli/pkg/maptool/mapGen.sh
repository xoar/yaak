#! /bin/sh
# $Id: mapGen.sh,v 2.12 2012/04/10 22:16:09 profw Exp $
# Copyright 1994, The Regents of the University of Colorado

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


# EXEC (mapGen.sh) (maptool.exe) (:lido.cmpd :names) (:mapIn :cpp) (+parser)
#      (maptool.err) (treedef.h) (treestack.c)
#   => (:mapConSyn) (:mapAbsSyn) (:mapAbsTree) (:mapFe) (:mapBe) (:mapPgram);
#:mapConSyn 'Complete concrete syntax' => :FILE;
#:mapAbsSyn 'Complete abstract syntax' => :FILE;
#:mapAbsTree 'Complete abstract tree' => :FILE;
#:mapFe 'Concrete syntax and grammar symbols' => :DERIVED-DIRECTORY;
#:mapBe 'Abstract grammar' => :DERIVED-DIRECTORY;
#:mapPgram 'Parsing grammar without bottomup constraints' => :FILE;

ODIN_maptool=$1;shift; ODIN_lido=$1;shift; ODIN_in=$1;shift;
ODIN_parser=$1;shift; ODIN_err=$1;shift; ODIN_treedef=$1;shift;
ODIN_treestack=$1;shift;
mkdir mapFe; mkdir mapBe;

SED=$ODINCACHE/PKGS/skeleton/sed.exe
$ODIN_maptool $ODIN_in > /dev/null 2> ERROR

if test -s ERROR
then
  echo '(|'"$ODIN_err"'|std_err|'  > ERRORS
  echo '(|'"$ODIN_in"'|line_err|' >> ERRORS
  $SED 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
	ERROR >> ERRORS
  echo '|)' >> ERRORS
  echo '|)' >> ERRORS
  exit 0
fi

cp consyntax mapConSyn
cp absyntax mapAbsSyn
cp abstree mapAbsTree

cp abstree mapBe/abstree.lido

echo "$ODINCACHE/PKGS/Input/err.specs" > mapBe/treestack.specs

if test -s "$ODIN_lido"
then
	cp pgram mapPgram
else
	$SED -n -e '/^<\$START_SYMBOL>: /p' pgram \
		> mapPgram
	cat consyntax >> mapPgram
fi

if test "$ODIN_parser" != 'none'
then
  cp symbols mapFe/map.symbols
  cp $ODIN_treedef   mapBe/treestack.h
  cp $ODIN_treestack mapBe/treestack.c
else
  echo '#define _COORDSTACK' | cat - $ODIN_treedef   > mapBe/treestack.h
  echo '#define _COORDSTACK' | cat - $ODIN_treestack > mapBe/treestack.c
fi

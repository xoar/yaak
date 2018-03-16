#! /bin/sh
# $Id: pgram.sh,v 2.5 2010/03/17 22:48:35 profw Exp $
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

# EXEC (pgram.sh) (:coding.cmpd :cpp) (:perrOut :list :cat)
#                 (:LIST :extract=:mapPgram :ls)
#                 (:LIST :extract=:mapBuPgram :ls)
#		  ($ODINCACHE/PKGS/skeleton/sed.exe)
#   NEEDS (:LIST :extract=:mapPgram) (:LIST :extract=:mapBuPgram)
#   => (:Pgram) (:BuPgram);
# :Pgram 'Complete parsing grammar without bottomup constraints' => :FILE;
# :BuPgram 'Complete parsing grammar with bottomup constraints' => :FILE;

ODIN_coding=$1;shift; ODIN_perrGen=$1;shift;
ODIN_mapPgram=$1;shift; ODIN_mapBuPgram=$1;shift;
SED=$1;shift;

echo '$CODE' > Pgram

$SED -e '/^#/d' "$ODIN_coding" >> Pgram

cat "$ODIN_perrGen" >> Pgram

echo '$GRAMMAR' >> Pgram

if test -s "$ODIN_mapBuPgram"
then
    cp Pgram BuPgram
    for f in `cat $ODIN_mapBuPgram`
    do
	$SED -e '/^#/d' $f >> BuPgram
    done
else
    cp /dev/null BuPgram
fi

for f in `cat $ODIN_mapPgram`
do
    $SED -e '/^#/d' $f >> Pgram
done


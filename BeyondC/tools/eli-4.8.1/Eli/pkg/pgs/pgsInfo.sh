#! /bin/sh
# $Id: pgsInfo.sh,v 2.10 2005/05/13 20:25:57 profw Exp $
# Copyright 1989, The Regents of the University of Colorado

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

# EXEC (pgsInfo.sh) (:Pgram) (:BuPgram) (+pgsOpt)
#      (eingabe.exe) (analyse.exe)
#   => (:pgsInfo);

ODIN_Pgram=$1;shift; ODIN_BuPgram=$1;shift; ODIN_pgsOpt=$1;shift;
ODIN_eingabe=$1;shift; ODIN_analyse=$1;shift;

SED=$ODINCACHE/PKGS/skeleton/sed.exe

if test '' = "$ODIN_pgsOpt"
then echo 'SN' > Optionen
else echo "$ODIN_pgsOpt" > Optionen
fi


if test -s "$ODIN_BuPgram"
then
  input=$ODIN_BuPgram
  cp $ODIN_BuPgram Eindat
else
  input=$ODIN_Pgram
  cp $ODIN_Pgram Eindat
fi

$ODIN_eingabe

mv Putout pgsInfo

$ODIN_analyse

cat Putout >>pgsInfo

#! /bin/sh
# $Id: perrGen.sh,v 2.5 2010/03/17 22:48:34 profw Exp $
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

# EXEC (perrGen.sh) (perr.exe) (:perr.cmpd :cpp) (perr.err)
#      ($ODINCACHE/PKGS/skeleton/sed.exe)
#   => (:perrGen);

ODIN_exe=$1;shift; ODIN_e124=$1;shift; ODIN_err=$1;shift;
SED=$1;shift;

$ODIN_exe $ODIN_e124 > ERROR 2>&1
mv perr perrGen

if test -s ERROR
then
  echo '(|'"$ODIN_err"'|std_err|' > ERRORS
  echo '(|'"$ODIN_e124"'|line_err|' >> ERRORS
  $SED 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' \
	ERROR >> ERRORS
  echo '|)' >> ERRORS
  echo '|)' >> ERRORS
else :
fi

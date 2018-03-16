#!/bin/sh
# $Id: idem.sh,v 2.9 2002/07/31 23:45:43 waite Exp $
# Copyright 2002, The Regents of the University of Colorado

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

# EXEC (idem.sh) (Idem.exe) (:idem.cmpd :union :cpp) (+prefix)
#   => (:idem);

ODIN_pgm=$1;shift; ODIN_Input=$1;shift; ODIN_prefix=$1;shift;
touch idem

if test "$ODIN_prefix" != ''
then prefix="$ODIN_prefix"
else prefix="Idem"
fi

$ODIN_pgm -p $prefix $ODIN_Input >/dev/null 2>ERROR ||\
  ( grep $ODIN_pgm ERROR >/dev/null 2>%1 &&\
    echo "Could not execute $ODIN_pgm" > ERRORS; exit 0 )

if test -s ERROR
then
  echo '(|'"$ODIN_Input"'|line_err|' > ERRORS
  $ODINCACHE/PKGS/skeleton/sed.exe -e \
    's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' ERROR >> ERRORS
  echo '|)' >> ERRORS
fi

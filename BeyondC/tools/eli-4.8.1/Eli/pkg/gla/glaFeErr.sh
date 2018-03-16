#! /bin/sh
# $Id: glaFeErr.sh,v 2.3 2002/05/08 15:00:54 waite Exp $
# Copyright 1999, The Regents of the University of Colorado

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

# EXEC (glaFeErr.sh) (+hookvalue) (:scan_spec :list :cpp) glaFeErr
#   => (:glaFeErr);

ODIN_hook=$1;shift; ODIN_in=$1;shift; ODIN_flexin=$1;shift;

SED=$ODINCACHE/PKGS/skeleton/sed.exe

cat -n $ODIN_flexin \
  | $SED -n -e "s,^ *\([0-9][0-9]*\).*sourceLine=\([0-9][0-9]*\).*,s;^[^ ]* \1;$ODIN_in \2;,p" \
  > script

echo "(|$ODIN_in|line_err|" > glaFeErr
$SED -f script $ODIN_hook >> glaFeErr
echo "|)" >> glaFeErr

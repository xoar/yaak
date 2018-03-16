#! /bin/sh
# $Id: mapBnf.sh,v 2.6 2005/06/08 15:19:27 profw Exp $
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

# EXEC (mapBnf.sh) (ebnf.exe) (:con.cmpd :cpp) (maptool.err)
#   => (:mapBnf);

ODIN_ebnf=$1;shift; ODIN_con=$1;shift; ODIN_err=$1;shift;
touch bnf

if $ODIN_ebnf $ODIN_con 1>bnf 2>ERROR
then :
else
  echo '(|'"$ODIN_err"'|std_err|'   > ERRORS
  echo '(|'"$ODIN_con"'|line_err|' >> ERRORS
  $ODINCACHE/PKGS/skeleton/sed.exe 's/^"\([^"]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/' ERROR >> ERRORS
  echo '|)' >> ERRORS
  echo '|)' >> ERRORS
fi

sort -u bnf > mapBnf

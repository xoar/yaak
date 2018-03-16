#! /bin/sh
# $Id: pgsGenErr.sh,v 2.1 2006/11/29 22:25:02 profw Exp $
# Copyright 2006, The Regents of the University of Colorado

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

# EXEC (pgsGenErr.sh) (+hookvalue) (:FILE) (:pgsConflict)
#   => (:pgsGenErr);

SED=$ODINCACHE/PKGS/skeleton/sed.exe 

cat -n $3 \
  | $SED -n -e "s;^ *\([0-9]*\)[^*]*\*\*\* [^-]*-reduce .*$;$3 \1 1 \
;p" \
  > pgsGenErr

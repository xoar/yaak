#!/bin/sh
# $Id: includes.sh,v 2.7 2012/06/11 19:35:52 profw Exp $
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

# EXEC (includes.sh) (:level_9_specs :pasted)
#      (:genlib :extract=:h :pasted)
#      (:phiGenHeaders :pasted)
#   => (:includes);

ODIN_userincls=$1;shift; ODIN_libincls=$1;shift; ODIN_phiincls=$1;shift;

cat $ODIN_userincls $ODIN_libincls $ODIN_phiincls \
  | "$ODINCACHE/PKGS/skeleton/cat-n.exe" \
  | sort -k 3 -k 1n,1 \
  | uniq -f 2 \
  | $ODINCACHE/PKGS/skeleton/sed.exe -e 's/^[0-9]*	\([^	]*\)	\(.*\)$/\1@\2/' \
  > dothlist

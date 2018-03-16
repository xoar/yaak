#!/bin/sh
# $Id: etaIncl.sh,v 1.2 1997/08/28 15:39:39 mjung Exp $
# Copyright 1996, Universitaet-GH Paderborn
# 
# This file is part of the Eli translator construction system.
# 
# Eli is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2, or (at your option) any later
# version.
# 
# Eli is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
# 
# You should have received a copy of the GNU General Public License along
# with Eli; see the file COPYING.  If not, write to the Free Software
# Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

etaincludes=$1

cat $etaincludes \
  | "$ODINCACHE/PKGS/skeleton/cat-n.exe" \
  | sort -k3 -k 1n,1 \
  | uniq -f 2 \
  | $ODINCACHE/PKGS/skeleton/sed.exe -e 's/^[0-9]*	\([^	]*\)	\(.*\)$/\1@\2/' \
  > etaIncl

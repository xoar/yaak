#! /bin/sh
# $Id: codeGen.sh,v 2.6 2008/11/11 10:10:57 asloane Exp $
# Copyright 1997, The Regents of the University of Colorado

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

# EXEC (codeGen.sh) (:symbols.cmpd :cpp)
#   => (:codeGen);

ODIN_symbols=$1;shift;
mkdir codeGen;

SED=$ODINCACHE/PKGS/skeleton/sed.exe

$SED -e '/^#/d' -e '/^$/d' $ODIN_symbols \
  | tee symbols \
  | $SED -f $ODINCACHE/PKGS/maptool/lex_code.sed \
  | awk '($0 != "EOF") { printf "%s\t\t%d\n", $0, NR+1 }' \
  | tee codeGen/code.lex_code \
  | $SED -n -e '/^[^$]/s/^/#define /p' \
  > codeGen/termcode.h

echo 'EOF=1.' > codeGen/code.coding
awk '($0 != "EOF") { printf "%s=%d.\n", $0, NR+1 }' symbols >> codeGen/code.coding

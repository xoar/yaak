#!/bin/sh
# $Id: csmidnProd.sh,v 2.3 2002/05/08 15:00:47 waite Exp $
# Copyright 1991, The Regents of the University of Colorado

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

PKG=$1;shift; ODIN_e172=$1;shift; ODIN_fold=$1;shift;  mkdir csmidnProd;

#csmidnProd[.none] "Identifier and string table ADTs"* :
#	USER
#		: (:.compound +typekey=str :extract :.cat)
#		+ fold

$PKG/transl.exe /dev/null < $ODIN_e172 > symbols

if test '' != "$ODIN_fold"
then "$PKG/adtinit.exe" -f -s symbols
else "$PKG/adtinit.exe" -s symbols
fi

mv csmtbl.h csmidnProd
mv idntbl.h csmidnProd

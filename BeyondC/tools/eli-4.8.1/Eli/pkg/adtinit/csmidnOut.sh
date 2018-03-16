#!/bin/sh
# $Id: csmidnOut.sh,v 1.2 1997/08/28 18:25:20 waite Exp $
# Copyright 1992, The Regents of the University of Colorado

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

ODIN_RUNDIR=`pwd`;
PKG=$1;shift; ODIN_e156=$1;shift; ODIN_e157=$1;shift;

#csmidnOut(.none) "Results of identifier and string table generation"* :
#	USER
#		: (:.compound +typekey=str :extract :names)
#		: (:csmidnProd :name)

cp "$ODIN_e157" csmidnOut

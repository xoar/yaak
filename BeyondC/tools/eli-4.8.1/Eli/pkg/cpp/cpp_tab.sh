#!/bin/sh
# $Id: cpp_tab.sh,v 2.2 1997/08/28 18:25:38 waite Exp $
# Copyright 1989, The Regents of the University of Colorado

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
PKG=$1;shift; ODIN_cpp=$1;shift;

#cpp_tab "Table summarizing file and line offset information"* :
#	USER
#		: cpp

"$ODINCACHE/PKGS/skeleton/err_tab.exe" "$ODIN_cpp" cpp_tab

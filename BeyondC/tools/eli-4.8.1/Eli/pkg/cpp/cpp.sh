#!/bin/sh
# $Id: cpp.sh,v 2.3 2002/05/08 15:00:50 waite Exp $
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
PKG=$1;shift; ODIN_e168=$1;shift;

#cpp "Result of applying the C pre-processor to a set of files"* :
#	USER
#		: (:.compound ::do_cpp)

if test -s $ODIN_e168
then
  cat `cat $ODIN_e168` >cpp
else
  cat /dev/null > cpp
fi


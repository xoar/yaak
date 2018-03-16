#!/bin/sh
# $Id: info_data.sh,v 2.6 2009/08/16 15:47:10 profw Exp $
# Copyright 1990, The Regents of the University of Colorado

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

# EXEC (info_data.sh) (texinfo/makeinfo.exe) (:tnf)
#   => (:info_data);

ODIN_makeinfo=$1;shift; ODIN_tnf=$1;shift;
mkdir info_data;

cd ./info_data

$ODIN_makeinfo $ODIN_tnf -o `basename $ODIN_tnf .tnf` >/dev/null 2>../Report

if test -s ../Report
then
	grep 'Warning' ../Report >WARNINGS
	grep -v 'Warning' ../Report >ERRORS
fi

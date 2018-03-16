#!/bin/sh
# $Id: fwOut.sh,v 2.5 1997/08/30 17:57:15 waite Exp $
# Copyright (c) 1992, The Regents of the University of Colorado
# Copyright 1995, Anthony M. Sloane

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

# EXEC (fwOut.sh) (:fw.cmpd :names) (:fw.cmpd :fwProd :name) 
#  => (:fwOut);
#
# :fwOut 'Results of FunnelWeb processing' => :FILE;

ODIN_names=$1;shift; ODIN_specname=$1;shift;

if test -s $ODIN_names
then 
	cp $ODIN_specname fwOut
else 
	cp /dev/null fwOut 
fi

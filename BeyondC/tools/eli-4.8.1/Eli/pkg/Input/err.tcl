# $Id: err.tcl,v 1.1 2010/09/22 02:31:34 profw Exp $
# Copyright 2010 The Regents of the University of Colorado
# err.tcl
# Monitoring support for coordinates.

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

set n(CoordPtr,desc) "Source text coordinates"

proc n_CoordPtr_open {text coord} {
    n_say "$text"
    if {$coord == 0} {
	n_say "\n  NoPosition\n"
    } else {
	set coord [n_hextodec $coord]
	set r [n_send get_coordinate_info $coord]
	n_say "\n  $r"
	n_say "\n"
    }
}

proc n_CoordPtr_say {coord} {
    n_say "CoordPtr:0x[n_dectohex $coord]"
}

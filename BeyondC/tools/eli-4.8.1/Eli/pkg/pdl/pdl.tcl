# $Id: pdl.tcl,v 1.2 1999/10/29 03:21:21 tony Exp $
# Copyright (c) 1999 Anthony M.Sloane 
# pdl.tcl
# Monitoring support for PDL.

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

set n(DefTableKey,desc) "Definition table key"

proc n_DefTableKey_open {text key} {
    n_say "$text\n"
    if {$key == 0} {
        n_say "  NoKey\n"
    } else {
        set key [n_hextodec $key]
        set p [n_send get_properties $key]
        if {[llength $p] == 0} {
            n_say "  No properties\n"
        } else {
            foreach {name type val} $p {
                n_say "  $name = "
                n_say_val $type $val
                n_say "\n"
            }
        }
    }
}

proc n_DefTableKey_say {key} {
    n_say "DefTableKey:0x[n_dectohex $key]"
}


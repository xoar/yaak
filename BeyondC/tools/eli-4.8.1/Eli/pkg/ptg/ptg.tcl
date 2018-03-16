# $Id: ptg.tcl,v 1.1 1999/11/08 09:08:33 mjung Exp $
# Copyright (c) 1999 Anthony M.Sloane 
# ptg.tcl
# Monitoring support for PTG.

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

set n(PTGNode,desc) "Pattern-based text generator tree node"

proc n_PTGNode_open {text node} {
    global n
    set f "/tmp/ptg$n(pid)"
    n_PTGNode_say $node
    set node [n_hextodec $node]
    n_send output_ptg_text $node $f
    n_say " represents:\n"
    set fd [open $f "r"]
    n_say [read $fd]
    n_say "\n"
    close $fd
    file delete $f
}

proc n_PTGNode_say {node} {
    n_say "PTGNode:0x[n_dectohex $node]"
}


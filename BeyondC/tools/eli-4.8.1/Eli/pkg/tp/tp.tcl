# $Id: tp.tcl,v 1.2 2008/10/03 15:56:40 profw Exp $
# Copyright (c) 1999 The Regents of the University of Colorado
# tp.tcl
# Monitoring support for tree parsing.

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

set n(TPNode,desc) "Tree parser node descriptor"

proc n_TPNode_say {node} {
  n_say "TPNode:0x[n_dectohex $node]"
}

proc n_TPNode_open {text node} {
  n_say "$text\n"
  if {$node != 0} {
    set node [n_hextodec $node]
    set r [n_send get_tp_node $node]
    n_say "  Node name = "
    n_say [lindex $r 0]
    set n [lindex $r 1]
    if {$n > 0} {
      n_say "\n  "
      n_TPNode_say [lindex $r 2]
    }
    if {$n > 1} {
      n_say "\n  "
      n_TPNode_say [lindex $r 3]
    }
    n_say "\n"
  }
}

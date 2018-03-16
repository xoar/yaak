# $Id: envmod.tcl,v 1.6 2007/08/12 21:17:02 profw Exp $
# Copyright (c) 1999 Anthony M.Sloane 
# envmod.tcl
# Monitoring support for envmod.

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

set n(Environment,desc) "Identifier scoping environment"

proc n_Environment_open {text env} {
    n_say "$text"
    if {$env == 0} {
	n_say "\n  NoEnv\n"
    } else {
	set inh 0
	set env [n_hextodec $env]
	set r [n_send get_scope_info $env]
	if {[lindex $r 0] != 0} {
	    n_say " (parent: "
	    n_Environment_say [lindex $r 0]
	    n_say ")"
	}
	n_say "\n"
	if {[lindex $r 1] != 0} {
	    set inh [lindex $r 1]
	}
	set r [lreplace $r 0 1]
	set c 0
	foreach {i j} $r {
	    n_say "  "
	    n_say_val DefTableKey $j
	    set s [n_send get_string $i]
	    if {[string compare "{*** Illegal string table index ***}" $s] == 0} {
		n_say " int:$i\n"
	    } else {
		n_say " $s\n"
	    }
	    incr c
	}
	if {$c == 0} {
	    n_say "  No bindings\n"
	}
	if {$inh != 0} {
	    n_say "  Inherits from"
	    set r [n_send get_inheritance_info $inh]
	    set c 0
	    foreach {i} $r {
		n_say "\n    "
		n_Environment_say $i
		incr c
	    }
	    if {$c == 0} {
		n_say " nothing\n"
	    }
	    n_say "\n"
	}
    }
}

proc n_Environment_say {env} {
    n_say "Environment:0x[n_dectohex $env]"
}

set n(Binding,desc) "Identifier binding"

proc n_Binding_open {text bind} {
    n_say "$text"
    if {$bind == 0} {
	n_say "\n  NoBinding\n"
    } else {
	set bind [n_hextodec $bind]
	set r [n_send get_binding_info $bind]
	n_say "\n  IdnOf = "
	set s [n_send get_string [lindex $r 0]]
	if {[string compare "{*** Illegal string table index ***}" $s] == 0} {
	    n_say " int:[lindex $p 0]"
	} else {
	    n_say " $s"
	}
	n_say "\n  KeyOf = "
	n_say_val DefTableKey [lindex $r 1]
	n_say "\n  EnvOf = "
	n_Environment_say [lindex $r 2]
	n_say "\n"
    }
}

proc n_Binding_say {bind} {
    n_say "Binding:0x[n_dectohex $bind]"
}

set n(Inherits,desc) "Inheritance specification"

proc n_Inherits_open {text cl} {
    n_say "$text"
    if {$cl == 0} {
	n_say "\n  No Inherits\n"
    } else {
	set cl [n_hextodec $cl]
	set r [n_send get_inheritance_info $cl]
	n_Environment_say [lindex $r 0]
	n_say " inherits from\n"
	set r [lreplace $r 0 0]
	set c 0
	foreach {i} $r {
	    n_say "    "
	    n_Inherits_say $i
	    n_say "\n"
	    incr c
	}
	if {$c == 0} {
	    n_say "    Nothing\n"
	}
	n_say "\n"
    }
}

proc n_Inherits_say {cl} {
    n_say "Inherits:0x[n_dectohex $cl]"
}

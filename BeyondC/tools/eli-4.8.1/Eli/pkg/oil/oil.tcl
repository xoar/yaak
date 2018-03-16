# $Id: oil.tcl,v 1.5 2007/07/09 10:24:22 profw Exp $
# Copyright (c) 1999 The Regents of the University of Colorado
# oil.tcl
# Monitoring support for oil.

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

set n(tOilType,desc) "Oil type descriptor"

proc n_tOilType_open {text type} {
    n_say "$text\n"
    if {$type == 0} {
        n_say "  OilInvalidType\n"
    } else {
        set type [n_hextodec $type]
        set p [n_send get_oil_type $type]
        n_say "  Type name = "
        n_say_val DefTableKey [lindex $p 0]
        n_say "\n"
        n_say "  Coercions = "
        n_tOilCoercionSeq_say [lindex $p 1]
        n_say "\n"
    }
}

proc n_tOilType_say {ty} {
    n_say "tOilType:0x[n_dectohex $ty]"
}

set n(tOilOp,desc) "Oil operator descriptor"

proc n_tOilOp_open {text op} {
    n_say "$text\n"
    if {$op == 0} {
        n_say "  OilInvalidOp\n"
    } else {
        set op [n_hextodec $op]
        set p [n_send get_oil_op $op]
        n_say "  Operator name = "
        n_say_val DefTableKey [lindex $p 0]
        set p [lreplace $p 0 0]
        set c [lindex $p 0]
        set p [lreplace $p 0 0]
        set r [lindex $p 0]
        set p [lreplace $p 0 0]
        n_say "\n  Prototype = ("
        set i 0
        foreach {a} $p {
            if {$i != 0} { n_say "," }
            n_tOilType_say $a
            incr i
        }
        n_say ")"
        if {[string compare $r ""] != 0} {
            n_say ": "
            n_tOilType_say $r
        }
        n_say "\n  Cost = int:$c\n"
        set p [n_send get_identifications $op]
	n_say "  Identifies:\n"
	foreach {a} $p {
	    n_say "    "
	    n_tOilOp_say $a
	    n_say "\n"
	}
    }
}

proc n_tOilOp_say {op} {
    n_say "tOilOp:0x[n_dectohex $op]"
}

set n(tOilTypeSet,desc) "Oil type set descriptor"

proc n_tOilTypeSet_open {text ts} {
    n_say "$text\n"
    if {$ts == 0} {
        n_say "  OilEmptyTypeSet\n"
    } else {
        set ts [n_hextodec $ts]
        set p [n_send get_oil_type_set $ts]
        foreach {t c} $p {
            n_say "  Type = "
            n_tOilType_say $t
            n_say ", Cost = int:$c\n"
        }
    }
}

proc n_tOilTypeSet_say {ts} {
    n_say "tOilTypeSet:0x[n_dectohex $ts]"
}

proc n_tOilSetSig_open {text ts} {
    n_say "$text\n"
    if {$ts == 0} {
        n_say "  OilEmptySetSig\n"
    } else {
        set ts [n_hextodec $ts]
        set p [n_send get_oil_set_sig $ts]
        foreach {t} $p {
	    n_say "    "
            n_tOilTypeSet_say $t
	    n_say "\n"
        }
    }
}

proc n_tOilSetSig_say {ts} {
    n_say "tOilSetSig:0x[n_dectohex $ts]"
}

proc n_tOilArgSig_open {text ts} {
    n_say "$text\n"
    if {$ts == 0} {
        n_say "  OilEmptyArgSig\n"
    } else {
        set ts [n_hextodec $ts]
        set p [n_send get_oil_arg_sig $ts]
        foreach {t} $p {
	    n_say "    "
            n_tOilType_say $t
	    n_say "\n"
        }
    }
}

proc n_tOilArgSig_say {ts} {
    n_say "tOilArgSig:0x[n_dectohex $ts]"
}

proc n_tOilCoercionSeq_open {text ts} {
    n_say "$text\n"
    if {$ts == 0} {
        n_say "  OilEmptyCoercionSeq\n"
    } else {
        set ts [n_hextodec $ts]
        set p [n_send get_oil_coercion_seq $ts]
        foreach {t c} $p {
	    n_say "    "
            n_tOilType_say $t
            n_say ", Cost = int:$c\n"
        }
    }
}

proc n_tOilCoercionSeq_say {ts} {
    n_say "tOilCoercionSeq:0x[n_dectohex $ts]"
}


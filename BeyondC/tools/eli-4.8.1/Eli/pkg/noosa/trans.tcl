# $Id: trans.tcl,v 2.11 1999/11/02 04:09:50 tony Exp $
# Copyright (c) 1995-1999 Anthony M. Sloane
# trans.tcl
# Transcript window support for Noosa

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

proc n_create_trans {} {
    global n
    frame .trans
    text .trans.t -height $n(transHeight) -width $n(width) \
        -xscrollcommand ".trans.x set" -yscrollcommand ".trans.y set" \
        -exportselection yes -cursor left_ptr -wrap none
    .trans.t tag configure value -underline yes -foreground $n(valueColour)
    scrollbar .trans.x -orient horiz -command ".trans.t xview"
    scrollbar .trans.y -orient vert -command ".trans.t yview"
    pack .trans.y -side right -fill y
    pack .trans.x -side bottom -fill x
    pack .trans.t -side left -fill both -expand yes
    pack .trans -side bottom -fill both -expand yes

    bind .trans.t <Button-2> "tk_popup .m.exec.m1 %X %Y"
    bind .trans.t <Control-Button-1>  "tk_popup .m.exec.m1 %X %Y"
    bind .trans.t <Button-3> "tk_popup .m.exam.m1 %X %Y"
    bind .trans.t <Alt-Button-1> "tk_popup .m.exam.m1 %X %Y"

    bind .trans.t <FocusIn> "set n(window) .trans"
    bind .trans.t <Control-s> \
	"set n(.trans.search,dir) \"-forwards\"; n_searchFile .trans .trans.t"
    bind .trans.t <Control-r> \
	"set n(.trans.search,dir) \"-backwards\"; n_searchFile .trans .trans.t"

    set n(values) 0

    set n(.trans,file) untitled
}

proc n_value {p l {t ""}} {
    global n
    if {[string compare $t ""] == 0} {
	set t [.trans.t get "$p" "$p wordend"]
    }
    if {[llength [info procs n_${t}_open]] == 0} {
	return [.trans.t index "$p wordend"]
    }
    set r [.trans.t index "$p + $l chars"]
    if {[string compare $t "Coord"] == 0} {
	set i [.trans.t get $p $r]
	set v $i
    } else {
	set q [.trans.t index "$p wordend + 1c"]
	set i [.trans.t get $p $r]
	set v [.trans.t get $q $r]
    }
    if [info exists n($t,desc)] {
	set d $n($t,desc)
    } else {
	set d $t
    }
    set vn $n(values)
    .trans.t tag add "v$vn" $p $r
    .trans.t tag add value $p $r
    .trans.t tag bind "v$vn" <Button-1> "
        n_${t}_open $i $v
    "
    .trans.t tag bind "v$vn" <Any-Enter> "
        set n(msg) \"$d $v\"
    "
    .trans.t tag bind "v$vn" <Any-Leave> "
        set n(msg) \"\"
    "
    incr n(values)
    return $r
}

proc n_say {args} {
    global n
    scan [.trans.t index end] "%d.%d" s x
    set o [.trans.t index "end - 1c"]
    foreach arg $args {
	.trans.t insert end $arg
    }
    while 1 {
	# Coordinates: nn,nn or nn,nn-nn,nn
	set p [.trans.t search -regexp -count l \
		{[0-9]+,[0-9]+(\-[0-9]+,[0-9]+)?} $o end]
	if {[string compare $p ""] != 0} {
	    set o [n_value $p $l Coord]
	    continue
	}
	# Values of the form type:0xnnnn (n hex)
	set p [.trans.t search -nocase -regexp -count l \
		{[a-z]+:0x[0-9A-F]+} $o end]
	if {[string compare $p ""] != 0} {
	    set o [n_value $p $l]
            continue
	}
	# Values of the form type:nnnn (n dec)
	set p [.trans.t search -nocase -regexp -count l \
		{[a-z]+:[0-9]+} $o end]
	if {[string compare $p ""] == 0} {
	    break
	} else {
	    set o [n_value $p $l]
	}
    }
    .trans.t mark set insert end
    scan [.trans.t index end] "%d.%d" e x
    if {$e - $s <= $n(transHeight)} {
	.trans.t see $e.0
    } {
	.trans.t see $s.0
    }
    update
    return
}

proc n_say_val {type val} {
    if {[llength [info procs n_${type}_say]] == 0} {
        n_say "$type:$val"
    } else {
        n_${type}_say $val
    }
}

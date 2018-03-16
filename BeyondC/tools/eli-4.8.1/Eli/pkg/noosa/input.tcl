# $Id: input.tcl,v 2.15 2013/07/30 20:51:14 profw Exp $
# Copyright (c) 1995-1999 Anthony M. Sloane
# input.tcl
# Input window support for Noosa

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

proc n_create_input {} {
    global n

    frame .input
    text .input.t -height $n(inputHeight) -width $n(width) \
        -xscrollcommand ".input.x set" -yscrollcommand ".input.y set" \
        -exportselection yes -cursor left_ptr -wrap none
    scrollbar .input.x -orient horiz -command ".input.t xview"
    scrollbar .input.y -orient vert -command ".input.t yview"
    pack .input.y -side right -fill y
    pack .input.x -side bottom -fill x
    pack .input.t -side left -fill both -expand yes
    pack .input -side top -fill both -expand yes
    set n(b1) 0
    bind .input.t <Button-2> "tk_popup .m.exec.m1 %X %Y"
    bind .input.t <Control-Button-1>  "tk_popup .m.exec.m1 %X %Y"
    bind .input.t <Button-3> "tk_popup .m.exam.m1 %X %Y"
    bind .input.t <Alt-Button-1> "tk_popup .m.exam.m1 %X %Y"
    bind .input.x <Button-1> {set n(b1) 1}
    bind .input.x <ButtonRelease-1> {set n(b1) 0}
    bind . <B1-Motion> {
	if $n(b1) {
	    set y [expr [winfo pointery .]-[winfo rooty .input.t]]
	    scan [.input.t dlineinfo 1.0] "%%*d %%*d %%*d %%d %%*d" h
	    set s [expr $n(inputHeight)+$n(transHeight)]
	    set l [expr $y/$h-1]
	    set tl [expr $s-$l]
	    .input.t configure -height $l
	    set n(inputHeight) $l
	    .trans.t configure -height $tl
	    set n(transHeight) $tl
	}
    }

    bind .input.t <FocusIn> "set n(window) .input"
    bind .input.t <Control-s> \
	"set n(.input.search,dir) \"-forwards\"; n_searchFile .input .input.t"
    bind .input.t <Control-r> \
	"set n(.input.search,dir) \"-backwards\"; n_searchFile .input .input.t"

    set n(.input,file) untitled
    set n(changed) 1
}

# n_source_changed
# Called when we see a source_changed event.
#   w: text window for displaying files
#   filename: name of file changed to
#   init: whether this should count as a new examination of the file,
#     as opposed to a return to a previous examination.
#   curline, curcol: current cumulative line number and local column
#   line, col: new local (in current file) line number and local column

proc n_source_changed {w filename init curline curcol line col} {
    global n

    if {$n(changed) && $init} {
        set c [expr $curcol-1]
        n_finit_signals
        set file [open "|expand $filename" r]
        set contents [read $file]
        close $file
        n_init_signals
        $w insert $curline.$c $contents
	if {[$w get insert-1c] != "\n"} {
	  $w insert insert "\n"
	}
        focus $w
        update
        n_token_init
        n_phrase_init
    }
}

proc n_input_mod {w filename init curline curcol line col} {
    global n nn

    set n(changed) 0
    
    if {![info exists n(infile)]} {
        set n(infile) $filename
        set n(infile,mtime) [file mtime $filename]
        set n(changed) 1
        set n(hinstalled) 0
    }
    if {[file mtime $filename] > $n(infile,mtime)} {
        set n(infile,mtime) [file mtime $filename]
        set n(changed) 1
    }
    if {$n(changed) && [info exists nn]} {
        unset nn
    }

    # Install or remove other handlers
    if {$n(changed) && !$n(hinstalled)} {
        n_eventset 1
    }
    if {!$n(changed) && $n(hinstalled)} {
        n_eventset 0
    }

    # Remove input mod handler    
    n_remove source_changed $n(input_mod,ids)
    unset n(input_mod,ids)

    # Display first one if it's changed, install handler for others
    if $n(changed) {
        .input.t delete 1.0 end
        .input.t mark set insert end
        if {![info exists n(source_changed,id)]} {
            n_source_changed .input.t "$filename" $init $curline $curcol \
                $line $col
            set n(source_changed,id) \
                [n_handle 0 Input_source_changed source_changed {
                    n_source_changed .input.t "$filename" $init $curline \
                        $curcol $line $col
                } 1]
        }
    } else {
        if [info exists n(source_changed,id)] {
            n_remove source_changed $n(source_changed,id)
            unset n(source_changed,id)
        }
    }
}


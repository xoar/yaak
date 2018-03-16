# $Id: cmd.tcl,v 2.38 2013/12/05 21:34:43 profw Exp $ 
# Copyright (c) 1995-1999 Anthony M.Sloane 
# cmd.tcl 
# Command window support for Noosa.  
# Includes implementations of standard commands. 

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

# Utility procedures

proc n_chkarg {arg re} {
    if [regexp $re $arg] {
	return 1
    } {
	return 0
    }
}

proc n_center_win {w} {
    wm withdraw $w
    update idletasks
    set x [expr [winfo screenwidth $w]/2 - [winfo reqwidth $w]/2 \
	    - [winfo vrootx [winfo parent $w]]]
    set y [expr [winfo screenheight $w]/2 - [winfo reqheight $w]/2 \
	    - [winfo vrooty [winfo parent $w]]]
    wm geom $w +$x+$y
    wm deiconify $w
}

# Cont

proc n_contcmd {} {
    n_save_handler
    n_cont
}

# Coorddesc

proc n_coorddesccmd {} {
    global n

    scan [.input.t index insert] "%d.%d" line col
    incr col
    set s ""
    foreach {s l c lo co} $n(breaks) {
	if {$l < $line} {
	    set l [expr $line+$lo]
	    set c $col
	    break
        } elseif {($l == $line) && ($c <= $col)} {
	    set l [expr $line+$lo]
	    set c [expr $col+$co]
	    break
	}
    }
    if {[string compare $s ""] != 0} {
	n_say "\n$line,$col is $s:$l,$c\n"
    }
}

set n(Coord,desc) "Source text coordinate"

proc n_Coord_open {text value} {
    if {[scan $value "%d,%d-%d,%d" sl sc el ec] == 4} {
	n_hl $sl [expr $sc-1] $el [expr $ec-1]
	return
    }
    # Single coordinate
    if {[scan $value "%d,%d" l c] == 2} {
	n_hl $l [expr $c-1] $l $c
	return
    }
}

proc n_hl {sl sc el ec} {
    if {[string compare [.input.t tag ranges sel] ""] != 0} {
	.input.t tag remove sel 1.0 end
    }
    .input.t tag add sel $sl.$sc $el.$ec
    .input.t mark set insert $sl.$sc
    .input.t see insert
}

# Freq

proc n_freqcmd {} {
    global n
    if $n(Freq) {
	set n(current) {}
	set n(freqnames) {}
        foreach event $n(events) {
            set eventname [lindex $event 0]
            if [lindex $event 3] {
                lappend n(freqs) [list $eventname \
                    [n_handle 0 Freq_$eventname $eventname "
                        global n
                        set e \"$eventname \$n(current)\"
 	                if {\[lsearch -exact \$n(freqnames) \$e\] == -1} {
                            set n(freqs,\$e) 1
			    lappend n(freqnames) \$e
                        } {
                            incr n(freqs,\$e)
                        }
                    " 1]]
            }
        }
        lappend n(freqs) \
	    [list finit [n_handle 0 Freq_finit finit {
                global n
	    } 1]] \
            [list stopped [n_handle 0 Freq_stopped stopped "
                global n
	        if {!\$error} {
                    set pairs {}
	            foreach name \$n(freqnames) {
		        lappend pairs \[list \$name \$n(freqs,\$name)\]
	            }
                    n_freq \$pairs
	        }
            " 1]] \
            [list enter [n_handle 0 Freq_enter enter {
                global n
                set n(current) [linsert $n(current) 0 $name]
           } 1]] \
            [list leave [n_handle 0 Freq_leave leave {
                global n
                set n(current) [lreplace $n(current) 0 0]
            } 1]]
    } {
        foreach p $n(freqs) {
	    n_remove [lindex $p 0] [lindex $p 1]
        }
        set n(freqs) {}
    }
}

proc n_freqzerocmd {} {
    global n
    if {[string compare $n(status) "dead"] != 0} {
	if [info exists n(freqname)] {
	    foreach e $n(freqnames) {
		set n(freqs,$e) 0
	    }
        }
    }
}

proc n_freq {pairs} {
    set total 0
    set pairs [lsort $pairs]
    set ev ""
    set etotal 0
    set count 0
    n_say "\nEvent frequency profile:\n"
    foreach pair $pairs {
        set lev $ev
        set ev [lindex [lindex $pair 0] 0]
        set callstack [lrange [lindex $pair 0] 1 end]
        set num [lindex $pair 1]
        if {[string compare $ev $lev] != 0} {
            if {($count > 1) && ($etotal != 0)} {
                n_say [format "%8d total\n" $etotal]
            }
            set etotal 0
            set count 0
            n_say " $ev:\n"
        }
        n_say [format "%8d %s\n" $num $callstack]
        incr count 
        incr etotal $num
        incr total $num
    }
    if {($count > 1) && ($etotal != 0)} {
        n_say [format "%8d total\n" $etotal]
    }
    n_say [format "%8d total events.\n" $total]
}

# Handlers

proc n_handlerscmd {} {
    global n

    toplevel .h -class NoosaHand
    wm title .h "Noosa Handlers"

    frame .h.m -relief raised -borderwidth 1

    set m .h.m.file.m
    menubutton .h.m.file -menu $m -text "File" -underline 0
    menu $m -tearoff 1
    $m add command -label "Load..." -underline 0 -command n_fload_handler
    $m add command -label "Save" -underline 0 -command "n_fsave_handler Save"
    $m add command -label "Save As..." -underline 5 \
	-command "n_fsave_handler SaveAs"
    $m add separator
    $m add command -label "Close" -underline 0 -command {
        n_save_handler
        destroy .h
    }

    set m .h.m.hand.m
    menubutton .h.m.hand -menu $m -text "Handlers" -underline 0
    menu $m -tearoff 1
    $m add command -label "New" -underline 0 -command n_new_handler
    $m add command -label "Rename" -underline 0 -command n_rename_handler
    $m add command -label "Clear" -underline 1 -command n_clear_handler
    $m add command -label "Delete" -underline 1 -command {
        n_del_handler
        n_clear_handler
    }

    set m .h.m.help.m
    menubutton .h.m.help -menu $m -text "Help" -underline 0
    menu $m -tearoff 1
    n_help_setup .h $m

    pack .h.m.file -side left
    pack .h.m.hand -side left
    pack .h.m.help -side right
    pack .h.m -side top -fill x

    frame .h.l
    listbox .h.l.e -height 8 -selectmode browse -exportselection no \
	-yscrollcommand ".h.l.ey set" 
    scrollbar .h.l.ey -orient vert -command ".h.l.e yview"
    listbox .h.l.h -height 8 -selectmode browse -exportselection no \
	-yscrollcommand ".h.l.hy set"
    scrollbar .h.l.hy -orient vert -command ".h.l.h yview"
    listbox .h.l.p -height 8 -selectmode browse -exportselection no \
	-yscrollcommand ".h.l.py set"
    scrollbar .h.l.py -orient vert -command ".h.l.p yview"
    pack .h.l.e -side left -expand yes -fill x
    pack .h.l.ey -side left -fill y
    pack .h.l.h -side left -expand yes -fill x
    pack .h.l.hy -side left -fill y
    pack .h.l.p -side left -expand yes -fill x
    pack .h.l.py -side left -fill y
    pack .h.l -side top -fill x

    set n(hmsg) ""
    message .h.g -textvariable n(hmsg) -aspect 10000 -relief ridge \
	-borderwidth 1
    pack .h.g -side top -fill x

    frame .h.h -relief raised -borderwidth 1
    frame .h.h.l -width 10
    frame .h.h.r -width 10
    label .h.h.nl -text "Handler name: "
    entry .h.h.n -width 20
    label .h.h.el -text "Enabled"
    radiobutton .h.h.e -variable n(henabled) -value 1
    label .h.h.dl -text "Disabled"
    radiobutton .h.h.d -variable n(henabled) -value 0

    text .h.t -yscrollcommand ".h.y set" -height $n(handHeight) \
	-exportselection yes -cursor left_ptr -wrap word
    scrollbar .h.y -orient vert -command ".h.t yview"

    pack .h.h.l -side left
    pack .h.h.nl -side left
    pack .h.h.n -side left -pady 5
    pack .h.h.r -side right
    pack .h.h.d -side right
    pack .h.h.dl -side right
    pack .h.h.e -side right
    pack .h.h.el -side right
    pack .h.h -side top -fill x 
    .h.h.e select

    pack .h.y -side right -fill y
    pack .h.t -side left -fill x -expand true

    n_center_win .h

    if {! [info exists n(hnum)]} {
	set n(hnum) 0
    }
    foreach ev $n(events) {
	set en [lindex $ev 0]
	if {! [info exists n(hnames,$en)]} {
	    set n(hnames,$en) {}
	}
        if {[llength $n(hnames,$en)] == 0} {
            .h.l.e insert end $en
        } {
            .h.l.e insert end "$en  *"
        }
    }
    .h.l.h delete 0 end
    .h.l.h selection clear 0 end
    .h.l.p delete 0 end
    .h.l.p selection clear 0 end
    n_clear_handler
    bind .h.l.e <Button-1> {
	n_save_handler
    }
    bind .h.l.e <ButtonRelease-1> {
        n_hevent_click
    }
    bind .h.l.h <Button-1> {
	n_save_handler
    }
    bind .h.l.h <ButtonRelease-1> {
	set cs [.h.l.h curselection]
        if {[string compare $cs ""] != 0} {
	    n_clear_handler
	    .h.t insert end $n(hands,[n_get_curhandler])
            .h.h.n insert end [n_get_curhandler]
            if {$n(hid,[n_get_curhandler]) == -1} {
                .h.h.d select
            } {
                .h.h.e select
            }
	}
    }
    bind .h.l.p <ButtonRelease-1> {
	set ev [lindex $n(events) [.h.l.e curselection]]
	set as [lindex $ev 2]
	set n(hmsg) \
	    "Parameter: [lindex $as [expr [.h.l.p curselection] * 2 + 1]]"
    }
    bind .h.h.e <ButtonRelease-1> {
	set cs [.h.l.h curselection]
        if {[string compare $cs ""] != 0} {
            set hn [n_get_curhandler]
            .h.l.h delete $cs
            .h.l.h insert $cs "$hn  +"
            .h.l.h selection set $cs
        }
    }
    bind .h.h.d <ButtonRelease-1> {
	set cs [.h.l.h curselection]
        if {[string compare $cs ""] != 0} {
            set hn [n_get_curhandler]
            .h.l.h delete $cs
            .h.l.h insert $cs "$hn"
            .h.l.h selection set $cs
        }
    }
    focus .h.t
}

proc n_hevent_click {} {
    global n

    set ev [lindex $n(events) [.h.l.e curselection]]
    set en [lindex $ev 0]
    set n(hmsg) "Event type: [lindex $ev 1]"
    .h.l.h delete 0 end
    .h.l.h selection clear 0 end
    foreach hn $n(hnames,$en) {
        if {$n(hid,$hn) == -1} {
            .h.l.h insert end $hn
        } {
            .h.l.h insert end "$hn  +"
        }
    }
    .h.l.p delete 0 end
    .h.l.p selection clear 0 end
    foreach {attr doc} [lindex $ev 2] {
        .h.l.p insert end $attr
    }
}

proc n_new_handler { {inspt end}} {
    global n

    set cs [.h.l.e curselection]
    if {[string compare $cs ""] == 0} {
	set n(hmsg) "Please select an event in the left list first"
    } else {
        set ev [lindex $n(events) $cs]
        set en [lindex $ev 0]
        incr n(hnum)
        if {[string compare [.h.h.n get] ""] == 0} {
            set hn "Handler$n(hnum)"
            .h.h.n insert end $hn
        } {
            set hn [.h.h.n get]
        }
        if [info exists n(hid,$hn)] {
            set n(hmsg) "A handler with that name already exists"
            incr n(hnum) -1
        } {
            .h.l.h selection clear 0 end
            .h.l.h insert $inspt $hn
            .h.l.h selection set $inspt
            lappend n(hnames,$en) $hn
            .h.l.e delete $cs
            .h.l.e insert $cs "$en  *"
            .h.l.e selection set $cs
            set n(hands,$hn) ""
            set n(hid,$hn) -1
            n_save_handler
        }
    }
}

proc n_save_handler {} {
    global n

    if {![winfo exists .h]} {
        return
    }

    set cs [.h.l.h curselection]
    if {[winfo exists .h] && ([string compare $cs ""] != 0)} {
	set ev [lindex $n(events) [.h.l.e curselection]]
	set en [lindex $ev 0]
	set hn [n_get_curhandler]
	if {$n(hid,$hn) != -1} {
	    n_remove $en $n(hid,$hn)
            set n(hid,$hn) -1
	}
	set n(hands,$hn) [.h.t get 1.0 "end - 1c"]
        if $n(henabled) {
            .h.l.h delete $cs
            if [catch {set n(hid,$hn) [n_handle 0 $hn $en $n(hands,$hn) 1]} \
		    result] {
                global errorInfo
                .h.h.d select
                .h.l.h insert $cs $hn
                .h.l.h selection set $cs
                set savedInfo $errorInfo
                error $result $savedInfo
            } {
                .h.l.h insert $cs "$hn  +"
                .h.l.h selection set $cs
            }
        }
    }
}

proc n_clear_handler {} {
    .h.t delete 1.0 end
    .h.h.n delete 0 end
}

proc n_del_handler {} {
    global n

    set c [.h.l.h curselection]
    if {[string compare $c ""] == 0} {
	set n(hmsg) "Please select a handler in the middle list first"
    } else {
        set cs [.h.l.e curselection]
	set ev [lindex $n(events) $cs]
	set en [lindex $ev 0]
	set hn [n_get_curhandler]
	if {$n(hid,$hn) != -1} {
	    n_remove $en $n(hid,$hn)
	}
	unset n(hands,$hn)
	unset n(hid,$hn)
	.h.l.h delete $c
	set p [lsearch -exact $n(hnames,$en) $hn]
	set n(hnames,$en) [lreplace $n(hnames,$en) $p $p]
        if {[llength $n(hnames,$en)] == 0} {
            .h.l.e delete $cs
            .h.l.e insert $cs $en
            .h.l.e selection set $cs
        }
    }
}

proc n_rename_handler {} {
    global n

    set inspt [.h.l.h curselection]
    if {[string compare $inspt ""] == 0} {
	set n(hmsg) "Please select a handler in the middle list first"
    } elseif {[string compare [.h.h.n get] ""] == 0} {
        set n(hmsg) "Please type a new name for the handler in the entry box"
    } elseif {[string compare [.h.h.n get] [n_get_curhandler]] == 0} {
        set n(hmsg) "New and old handler names must be different"
    } else {
        n_del_handler
        n_new_handler $inspt
    }
}

proc n_get_curhandler {} {
    return [string trimright [.h.l.h get [.h.l.h curselection]] " +"]
}

proc n_fsave_handler {mode} {
    global n

    n_save_handler
    if {[string compare $mode "SaveAs"] == 0} {
        set n(hfile) [tk_getSaveFile -title "Save As..."]
        if {[string length $n(hfile)] == 0} {
            return
        }
    } else {
        if {![info exists n(hfile)]} {
            n_fsave_handler "SaveAs"
            return
        }
    } 
    set fileID [open $n(hfile) w]
    set i 0

    foreach ev $n(events) {
        set en [lindex $ev 0]
        if {[llength $n(hnames,$en)] != 0} {
            foreach hn $n(hnames,$en) {
                if {$n(hid,$hn) == -1} {
                    set enabled 0
                } {
                    set enabled 1
                }
                puts $fileID \
		    "n_install_handler {$en $i $hn $enabled {$n(hands,$hn)}}"
            }
        }
	incr i
    }
    close $fileID
    set n(hmsg) "Saved $n(hfile)"
}

proc n_fload_handler {} {
    global n

    set n(hfile) [tk_getOpenFile -title "Load Handlers..."]
    if {[string length $n(hfile)] == 0} {
        return
    }
    source $n(hfile)
    set n(hmsg) "Loaded $n(hfile)"
}

proc n_install_handler {handler} {
    global n

    set en [lindex $handler 0]
    set i [lindex $handler 1]
    set hn [lindex $handler 2]
    set enabled [lindex $handler 3]
    set body [lindex $handler 4]

    if [winfo exists .h] {
        .h.l.e selection clear 0 end
    	.h.l.e selection set $i
    	n_hevent_click
    	n_clear_handler
    	.h.h.n insert end $hn
    	if {$enabled == 0} {
            .h.h.d select
    	} {
            .h.h.e select
    	}
    	.h.t insert end $body
    	n_new_handler
    } {
        if {![info exists n(hid,$hn)]} {
            lappend n(hnames,$en) $hn
	    set n(hands,$hn) $body
            set n(hid,$hn) [n_handle 0 $hn $en $n(hands,$hn) 1]
        }
    }
}

# Help

proc n_helpcmd {ow item} {
    global n
    if {[info exists n(count)]} {
	incr n(count)
    } else {
	set n(count) 0
    }
    set w .d$n(count)
    toplevel $w -class NoosaHelp
    wm title $w "Noosa Help"

    frame $w.m -relief raised -borderwidth 1

    set m $w.m.win.w
    menubutton $w.m.win -menu $m -text "Help" -underline 0
    menu $m -tearoff 1
    $m add command -label "Close" -underline 0 -command "destroy $w"
    pack $w.m.win -side left
    pack $w.m -side top -fill x

    text $w.t -yscrollcommand "$w.y set" -exportselection yes \
	-cursor left_ptr -wrap word
    scrollbar $w.y -orient vert -command "$w.t yview"
    pack $w.y -side right -fill y
    pack $w.t -side left -fill both -expand yes

    bind $w <Return> "destroy $w"

    $w.t insert end $n(help,$ow,$item)

    n_center_win $w
}

proc n_help_setup {w m} {
    global n

    foreach i [lsort [array names n "help,$w,*"]] {
        scan $i "help,$w,%\[a-zA-Z \]" s
        $m add command -label $s -underline 0 -command "n_helpcmd $w \{$s\}"
    }
}

# Kill

proc n_killcmd {} {
    n_kill
}

# Node

proc n_nodecmd {w} {
    global n

    set here [.input.t index insert]
    scan $here "%d.%d" l c

    incr c
    if {[string compare $w .tb] == 0} {
        n_tree_see .tb.c.c .tb[n_tbtree_view_coord .tb.c.c $l $c]
    } else {
        set tags [.input.t tag names $here] 
        set index [lsearch -glob $tags ${w}Node:*]
        if {$index == -1} {
    	    n_say "\nNo tree nodes represent $l,$c\n"
	} else { 
	    n_tree_see $w.c.c [lindex $tags $index]
	}
    }
}

set n(Node,desc) "Tree node"

proc n_Node_open {text {num ""}} {
    global n nn

    foreach w [winfo children .] {
        if {[string match .lr* $w] || [string match .tv* $w]} {
            n_tree_see_clear $w.c.c
            catch {n_tree_see $w.c.c $w$text}
        }
    }
    if [winfo exists .lr] {
        n_tree_see_clear .lr.c.c
	n_tree_see .lr.c.c .lr$text
    }
    if [winfo exists .tb] {
	if {[string compare $num ""] != 0} {
	    n_tbtree_view_node .tb.c.c $num
	}
        n_tree_see_clear .tb.c.c
	n_tree_see .tb.c.c .tb$text
    }
}

set n(NODEPTR,desc) "Tree node pointer"

proc n_NODEPTR_open {text root} {
    global nn
    if [info exists nn(tree,$root,num)] {
        n_Node_open Node:$nn(tree,$root,num) $nn(tree,$root,num)
    }
    if {![winfo exists .tv$root]} {
        n_lrtree_show .tv$root $root
    }
}

# Phrase

proc n_phrasecmd {} {
    scan [.input.t index insert] "%d.%d" l c
    incr c
    n_say "\nPhrases recognised involving $l,$c: [n_find_phrases $l $c]"
}
    
# Postscript

proc n_pscmd {w all} {
    set fn [tk_getSaveFile -title "Save as Postscript" -initialfile tree.ps]
    if {[string compare $fn ""] == 0} {
        return
    }
    if $all {
        scan [$w.c.c bbox all] "%*d %*d %d %d" maxx maxy
        set args "-x 0 -width $maxx -y 0 -height $maxy"
    } else {
        set args ""
    }
    eval $w.c.c postscript -file $fn $args
}

# Quit

proc n_quitcmd {} {
    if [n_spec_kill] {
        exit 0
    }
}

# Run

proc n_runcmd {} {
    global n

    n_save_handler
    set n(tnum) 0
    if $n(eventinit) {
	n_eventinit
	set n(eventinit) 0
    }
    set code [catch {n_run} msg]
    if {$code == 1} {
	n_say "Run: $msg\n"
    }
}

# String

proc n_stringcmd {} {
    if {[catch "selection get" arg] != 0} {
        n_say "\nPlease select the index of a string\n"
    } {
 	if [n_chkarg $arg {^[0-9]+$}] {
	    n_say "\nString at index $arg: "
	    set s [n_send get_string $arg]
	    n_say [format "\'%s\'\n" $s]
	} {
	    n_say "\nPlease select a string index\n"
	}
    }
}

proc n_stringscmd {} {
    set strs [n_send get_all_strings]
    if {[llength $strs] == 0} {
        n_say "\nString table is empty\n"
    } {
	n_say "\nString table:\n"
        foreach {i j} $strs {
            n_say [format "%4d '%s'\n" $i $j]
        }
    }
}

# Time

proc n_timecmd {} {
    global n
    if $n(Time) {
        lappend n(times) \
            [list init [n_handle 0 Time_init init {
                n_time_init $n_time
            } 1]] \
            [list stopped [n_handle 0 Time_stopped stopped {
	        if {!$error} {
                    n_time_stopped $n_time
	        }
            } 1]] \
            [list enter [n_handle 0 Time_enter enter {
                n_time_enter $name $n_time
            } 1]] \
            [list leave [n_handle 0 Time_leave leave {
                n_time_leave $name $n_time
            } 1]]
    } {
        foreach p $n(times) {
	    n_remove [lindex $p 0] [lindex $p 1]
        }
        set n(times) {}
    }
}

proc n_timezerocmd {} {
    global n
    foreach name [array names n] {
	if [string match "times,*" $name] {
	    unset n($name)
	}
    }
}

proc n_time_init {time} {
    global n
    set n(starttime) $time
    set n(cstack) {}
    set n(tstack) [list $time]
    set n(sections) {}
    n_timezerocmd
    return
}

proc n_time_enter {section time} {
    global n
    upvar #0 n(cstack) cstack
    upvar #0 n(tstack) tstack
    set delta [expr $time-[lindex $tstack 0]]
    if [info exists n(times,$cstack)] {
        incr n(times,$cstack) $delta
    } {
        set n(times,$cstack) $delta
        lappend n(sections) $cstack
    }
    set cstack [linsert $cstack 0 $section]
    set tstack [linsert $tstack 0 $time]
    return
}

proc n_time_leave {section time} {
    global n
    upvar #0 n(cstack) cstack
    upvar #0 n(tstack) tstack
    if {[string compare [lindex $cstack 0] $section] != 0} {
        n_say "\nError: illegal non-nested section leave $section"
	return
    }
    set delta [expr $time-[lindex $tstack 0]]
    if [info exists n(times,$cstack)] {
        incr n(times,$cstack) $delta
    } {
        set n(times,$cstack) $delta
        lappend n(sections) $cstack
    }
    set cstack [lreplace $cstack 0 0]
    set tstack [lreplace $tstack 0 1 $time]
    return
}

proc n_time_stopped {time} {
    global n
    n_say "\nTime profile:\n"
    set totaltime [expr $time-$n(starttime)]
    if {$totaltime != 0} {
        foreach section [lsort $n(sections)] {
            set t $n(times,$section)
            set s [expr $t/1000000.0]
            n_say [format "%6.2fs %6.2f%% %s\n" $s \
                [expr $t*100.0/$totaltime] $section]
        }
    }
    n_say [format "Total CPU time: %5.2fs\n" [expr $totaltime/1000000.0]]
    return
}

# Token

proc n_tokencmd {} {
    if {[string compare [.input.t tag ranges sel] ""] == 0} {
        set s [.input.t index insert]
        set e $s
    } {
	set s [.input.t index sel.first]
	set e [.input.t index sel.last]
    }
    scan $s "%d.%d" sl sc
    incr sc
    if {[string compare $s $e] == 0} {
        n_say "\nTokens recognised at $sl,$sc: "
	n_say [n_find_tokens $sl $sc $sl $sc]
    } {
        scan $e "%d.%d" el ec
        incr ec
        n_say "\nTokens recognised in $sl,$sc-$el,$ec: "
	n_say [n_find_tokens $sl $sc $el $ec]
    }
}

# Trace

proc n_tracecmd {} {
    global n
    if $n(Trace) {
        n_trace_on
    } {
        n_trace_off
    }
}

proc n_traceset {} {
    global n

    if {[string compare $n(tracere) ""] == 0} {
        set n(tracere) ".*"
    }
    if $n(Trace) {
        n_trace_off
        n_trace_on
    }
}

proc n_traceexpcmd {} {
    global n

    if [winfo exists .trace] {
        raise .trace
        return
    }

    toplevel .trace
    wm title .trace "Set Event Filter..."
    n_center_win .trace

    frame .trace.t -relief raised
    label .trace.t.l -text "Regular Exp: "
    entry .trace.t.e -relief sunken -textvar n(tracere)
    bind .trace.t.e <Return> {n_traceset; destroy .trace}
    frame .trace.b -relief groove -bd 1
    button .trace.b.b1  -text "Set" -command n_traceset
    button .trace.b.b2 -text "Clear" -command {
        .trace.t.e delete 0 end
        set n(tracere) ""
    }  
    button .trace.b.b3 -text "Close" -command "destroy .trace"

    pack .trace.t.l -side left
    pack .trace.t.e -side right -fill both -expand true
    pack .trace.t -side top -fill both -pady 5
    pack .trace.b.b1  -side left -expand true -anchor w -pady 5
    pack .trace.b.b2  -side left -expand true -anchor c -pady 5
    pack .trace.b.b3  -side right -expand true -anchor e -pady 5
    pack .trace.b -side bottom -fill both
 
    focus .trace.t.e
}

proc n_trace_on {} {
    global n
    foreach e $n(events) {
        set nm [lindex $e 0]
 	set res ""
	foreach {attr doc} [lindex $e 2] {
	    set res "$res $attr=\\\"\$$attr\\\""
	}
	lappend n(traces) [list $nm \
	    [n_handle 0 Trace_$nm $nm "
                global n
		if \{\[regexp \{$n(tracere)\} \{$nm$res\}\]\} \{
		    n_say \"$nm$res\\n\"
		\}
	    " 1]]
    }
}

proc n_trace_off {} {
    global n
    foreach p $n(traces) {
	n_remove [lindex $p 0] [lindex $p 1]
    }
    set n(traces) {}
}

# Tree

proc n_treecmd {} {
    global n nn

    if [info exists n(tree,id)] {
	n_remove tree $n(tree,id)
	unset n(tree,id)
    }
    if {($n(Tree,Full) == 0) && [winfo exists .lr]} {
        destroy .lr
    }
    if {($n(Tree,Src) == 0) && [winfo exists .lr0]} {
	destroy .lr0
    }
    if {$n(Tree,Comp) == 0} {
        for {set i 1} {$i < $n(tnum)} {incr i 1} {
            if [winfo exists .lr$i] {
	        destroy .lr$i
            }
        }
    }
    if {($n(Tree,Incr) == 0) && [winfo exists .tb]} {
	destroy .tb
    }

    set n(tree,id) \
	[n_handle 0 Tree tree "
            global n nn t
            n_tree_setup
	    if {$n(Tree,Full)} {
                set nn(tree,\$root,parent) \$parent
                if {\$n(tnum) == 0} {
   		    set n(lrdone) 0
		    if {(!\[winfo exists .lr\] || \$n(changed))} {
                        set nn(toproot) \$root
                        n_lrtree_show .lr \$root
			set n(lrdone) 1
		    }
		} elseif {(\$n(tnum) > 0) && \$n(lrdone)} {
                    n_lrtree_show .lr \$nn(toproot)
                }
            }
	    if {($n(Tree,Src) && (\$n(tnum) == 0)) ||
                    ($n(Tree,Comp) && (\$n(tnum) > 0))} {
                if {!\[winfo exists .lr\$n(tnum)\] || \$n(changed)} {
                    n_lrtree_show .lr\$n(tnum) \$root
                }
            }
	    if {$n(Tree,Incr)} {
                if {!\[winfo exists .tb\] || \$n(changed)} {
                    if {\$n(tnum) == 0} {
                        unset t
                        set nn(toproot) \$root
                        n_tbtree_show \$root
                    }
                }
                if {\[winfo exists .tb\] && (\$n(tnum) > 0) && \$n(changed)} {
                    n_tbtree_attach \$root \$parent \$desc
                }
            }
            incr n(tnum)
        " 1]
}

proc n_tree_setup {} {
    global n nn

    if {![info exists nn(tree,num)]} {
	set nn(tree,num) 0
    }

    if {$n(setuptree)} {
	set n(setuptree) 0
	set n(attr,-1,name) "Computed"
	set n(attr,-1,lhs) "Unknown"
	set n(attr,-1,rhs) "Unknown"
	set n(attr,-1,label) "$n(attr,-1,lhs)\n$n(attr,-1,name)"

	set prods [n_send get_abs_prods]
	set prod 0
	foreach p $prods {
	    set n(attr,$prod,name) [lindex $p 0]
	    set n(attr,$prod,lhs) [lindex $p 1]
	    set n(attr,$prod,rhs) [lindex $p 2]
	    set n(attr,$prod,label) "$n(attr,$prod,lhs)\n$n(attr,$prod,name)"
	    incr prod
	}
    }
}

proc n_tbtree_view_coord {w l c} {
    global n nn t

    foreach node [n_send find_nodes $nn(toproot) $l $c] {
        if {!$t(tree,$node,open) && ($nn(tree,$node,nch) > 0)} {
	    n_tbtree_expand $w $nn($w,$node,id) 0
	}
    }
    return Node:$nn(tree,$node,num)
}

proc n_tbtree_view_node {w num} {
    global n nn t

    set node $nn(tree,$num,node)
    if {[info exists t(tree,$node,open)] && $t(tree,$node,open)} {
	return
    }
    set ps {}
    for {set p $nn(tree,$node,parent)} {$p != -1} {set p $nn(tree,$p,parent)} {
	set ps [concat $p $ps]
    }
    foreach p $ps {
	if {![info exists t(tree,$p,open)] || !$t(tree,$p,open)} {
	    n_tbtree_expand $w $nn($w,$p,id) 0
	}
    }
}

proc n_tbtree_show {root} {
    global n nn t

    set w .tb.c.c
    if [winfo exists .tb] {
	wm deiconify .tb
	raise .tb
    } {
        toplevel .tb -class NoosaIncrTree
	wm title .tb "Noosa Tree (Incremental)"

	frame .tb.m -relief raised -borderwidth 1

	set m .tb.m.tree.m
	menubutton .tb.m.tree -menu $m -text "Tree" -underline 0
	menu $m -tearoff 1
	$m add command -label "Node" -underline 0 \
            -command "n_nodecmd .tb"
	$m add command -label "Save tree as Postscript" -underline 5 \
            -command "n_pscmd .tb 1"
	$m add command -label "Save window as Postscript" -underline 5 \
            -command "n_pscmd .tb 0"
	$m add separator
	$m add command -label "Close" -underline 0 \
	    -command "destroy .tb"

	set m .tb.m.help.m
	menubutton .tb.m.help -menu $m -text "Help" -underline 0
	menu $m -tearoff 1
        n_help_setup .tb $m

	pack .tb.m.tree -side left
	pack .tb.m.help -side right
	pack .tb.m -side top -fill x

        frame .tb.c -borderwidth 1 -relief sunken
        canvas .tb.c.c \
	    -scrollregion [list 0 0 5000 5000] \
	    -xscrollcommand ".tb.c.x set" \
	    -yscrollcommand ".tb.c.y set"
        scrollbar .tb.c.x -orient horizontal -relief sunken \
	    -command ".tb.c.c xview"
        scrollbar .tb.c.y -orient vertical -relief sunken \
	    -command ".tb.c.c yview"

	pack .tb.c.y -side right -fill y
	pack .tb.c.x -side bottom -fill x
	pack .tb.c.c -side left -fill both -expand yes
	pack .tb.c -side top -fill both -expand yes

	set n(b2) 0
	bind $w <Button-2> {
	    if {!$n(b2)} {
		%W scan mark %x %y
	    }
	}
	bind $w <Control-Button-1> {
	    if {!$n(b2)} {
		%W scan mark %x %y
	    }
	}
	bind $w <B2-Motion> {
	    if {!$n(b2)} {
		%W scan dragto %x %y
	    }
	}
	bind $w <Control-B1-Motion> {
	    if {!$n(b2)} {
		%W scan dragto %x %y
	    }
	}
	bind $w <ButtonRelease-2> {set n(b2) 0}
	bind $w <Control-ButtonRelease-1> {set n(b2) 0}

	$w bind open <Button-1> {
	    set n(tid) [%W find closest [%W canvasx %x] [%W canvasy %y]]
	    n_tbtree_contract %W $n(tid)
	}
	$w bind closed <Button-1> {
	    set n(tid) [%W find closest [%W canvasx %x] [%W canvasy %y]]
	    n_tbtree_expand %W $n(tid) 1
	}
	$w bind closed <Button-2> {
	    set n(tid) [%W find closest [%W canvasx %x] [%W canvasy %y]]
	    n_tbtree_expand %W $n(tid) 0
	    set n(b2) 1
	}
	$w bind closed <Control-Button-1> {
	    set n(tid) [%W find closest [%W canvasx %x] [%W canvasy %y]]
	    n_tbtree_expand %W $n(tid) 0
	    set n(b2) 1
	}
	$w bind closed <B2-Motion> {break}
	$w bind closed <Control-B1-Motion> {break}
    }

    $w delete all
    set nn(tree,$root,parent) -1
    set t(tree,$root,open) 0
    n_tbtree_draw $w 15 15 {} {} $root
    n_tree_see $w .tbNode:1
}

proc n_tbtree_attach {root parent desc} {
    global n nn t

    if {[info exists nn(tree,$parent,ch)]} {
        set ch $nn(tree,$parent,ch)
        set el [expr $desc - 1]
        set nn(tree,$parent,ch) [lreplace $ch $el $el $root]
        if {[info exists t(tree,$parent,open)] && $t(tree,$parent,open) == 1} {
            set it p$parent$desc
            scan [.tb.c.c coords $it] "%d.0 %d.0" x y
            .tb.c.c delete $it
            set l $nn(tree,$parent,$desc)
            set mid [n_tbtree_draw .tb.c.c [expr $x-20] [expr $y-5] \
                         [lindex $l 0] [lindex $l 1] $root]
            set nch $nn(tree,$parent,nch)
            if {($nch > 1) && ($nch == $desc)} {
                set nn(tree,$mid,line) $nn(tree,$nn(tree,$parent,lastch),line)
                unset nn(tree,$nn(tree,$parent,lastch),line)
                set nn(tree,$parent,lastch) $mid
            }
        }
    }
}

proc n_tbtree_draw {w x y atags ntags node {desc 0}} {
    global n nn

    if {$node == 0} {
        set nn(tree,$node,prod) -1
        set nn(tree,$node,nch) 0
        set nn(tree,$node,ch) {}
        set nch 0
        set num [incr nn(tree,num)]
    } else {
        if {![info exists nn(tree,$node,prod)]} {
            set ch [n_send get_node $node]
            set nn(tree,$node,prod) [lindex $ch 0]
            set nn(tree,$node,ch) [lrange $ch 1 end]
            set nn(tree,$node,nch) [llength $nn(tree,$node,ch)]
        }
        set nn(tree,$node,atags) $atags
        set nn(tree,$node,ntags) $ntags
        set nch $nn(tree,$node,nch)
        if {[info exists nn(tree,$node,num)]} {
            set num $nn(tree,$node,num)
        } else {
            set num [incr nn(tree,num)]
            set nn(tree,$node,num) $num
            set nn(tree,$num,node) $node
        }
    }

    if {($node == 0) && ($desc != 0)} {
        set ctag p$nn(tree,$node,parent)$desc
    } {
        set ctag ""
    }

    set tag .tbNode:$num

    set x1 [expr $x+5]
    set y1 [expr $y+5]
    set x2 [expr $x+10]
    set y2 [expr $y+10]

    set f "$n(treeFont) $n(treeFontSize)"
    set prod $nn(tree,$node,prod)
    set id1 [$w create text [expr $x1+15] $y1 -anchor w \
 	         -tags [concat $tag $atags $ctag] \
	         -text "$n(attr,$prod,lhs)" -font $f]
    scan [$w bbox $id1] "%*d %*d %d %*d" x3
    set id2 [$w create text $x3 $y1 -anchor w \
  	         -tags [concat $tag $atags $ctag] \
	         -text "($n(attr,$prod,name))" -font $f]
    set f "$n(treeFont) [expr $n(treeFontSize) * 8 / 10]"
    $w create text [expr $x-2] $y -anchor e -text $num \
	-tags [concat n$id1 $atags $ctag] -font $f
    if {$nch == 0} {
	set mid [$w create line $x $y1 $x2 $y1 -width 3 \
		    -tags [concat $atags $ntags $ctag]]
    } else {
	set mid [$w create rectangle $x $y $x2 $y2 -fill black \
		    -tag [concat closed $atags $ntags]]
	set nn(tree,$mid,rnode) $node
    }
    set nn($w,$node,id) $mid

    if {$node != 0} {
        set nn($w,$node,sid) $id1
        set nn($w,$node,rid) $id2
        n_tree_bind $w $num $node $prod $tag $id1 $id2
    }

    return $mid
}

proc n_tbtree_expand {w id rec {shift 1}} {
    global n nn t

    set node $nn(tree,$id,rnode)
    scan [$w coords $id] "%f %f %*f %*f" x y
    set x [expr round($x)]
    set y [expr round($y)]
    scan [$w cget -scrollregion] "%*d %*d %d %d" maxx maxy

    if {($x > $maxx) || ($y > $maxy)} {
	set maxx [expr $maxx*2]
	set maxy [expr $maxy*2]
	$w configure -scrollregion [list 0 0 $maxx $maxy]
    }

    $w dtag $id closed
    $w addtag open withtag $id
    $w itemconfigure $id -fill white
    
    set nch $nn(tree,$node,nch)
    set t(tree,$node,open) 1
    set dy $nch
    if {$rec && $shift} {
        set chs $nn(tree,$node,ch)
        while {[llength $chs] > 0} {
            set c [lindex $chs 0]
            set chs [lrange $chs 1 end]
            if {![info exists nn(tree,$c,prod)]} {
                set ch [n_send get_node $c]
                set nn(tree,$c,prod) [lindex $ch 0]
                set nn(tree,$c,ch) [lrange $ch 1 end]
                set nn(tree,$c,nch) [llength $nn(tree,$c,ch)]
            }
            if {$nn(tree,$c,nch) > 0} {
                set chs [concat $chs $nn(tree,$c,ch)]
                incr dy $nn(tree,$c,nch)
            }
        }
    }
    set dy [expr 20*$dy]

    if $shift {
        foreach b [$w find enclosed 0 [expr $y+10] $maxx $maxy] {
            $w move $b 0 $dy
            if [info exists nn(tree,$b,line)] {
                scan [$w coords $nn(tree,$b,line)] "%f %f %f %f" a1 b1 \
                    a2 b2
                if {$b1 <= [expr $y+5]} {
                    $w coords $nn(tree,$b,line) $a1 $b1 $a2 [expr $b2+$dy]
                }
            }
        }
    }

    incr x 20
    set dy $y
    set atags [concat Desc:$id $nn(tree,$node,atags)] 
    set ntags [concat Ndesc:$id $nn(tree,$node,ntags)] 

    set desc 1

    foreach child $nn(tree,$node,ch) {
	set nn(tree,$child,parent) $node
	set t(tree,$child,open) 0

	incr dy 20
	set ldy $dy

        if {$child == 0} {
            set nn(tree,$node,$desc) [list $atags $ntags]
        }

	set mid [n_tbtree_draw $w $x $dy $atags $ntags $child $desc]
	if {$rec && ($nn(tree,$child,nch) > 0)} {
	    set dy [n_tbtree_expand $w $mid 1 0]
	}
        incr desc
    }

    if {$nn(tree,$node,nch) > 1} {
	incr x 5
	set lid [$w create line $x [expr $y+25] $x [expr $ldy+5] \
		    -tag [concat line $atags]]
	$w lower $lid
	set nn(tree,$mid,line) $lid
        set nn(tree,$node,lastch) $mid
    }

    return $dy
}

proc n_tbtree_contract {w id} {
    global nn t

    set node $nn(tree,$id,rnode)
    scan [$w coords $id] "%f %f %*f %*f" x y
    set x [expr round($x)]
    set y [expr round($y)]
    scan [$w cget -scrollregion] "%*d %*d %d %d" maxx maxy

    $w dtag $id open
    $w addtag closed withtag $id
    $w itemconfigure $id -fill black

    set desc [$w find withtag Ndesc:$id]
    set t(tree,$node,open) 0
    foreach d $desc {
	if [info exists nn(tree,$d,rnode)] {
	    set t(tree,$nn(tree,$d,rnode),open) 0
	}
    }

    $w delete highlight
    set dy [expr [llength $desc]*20]
    $w delete Desc:$id 

    foreach b [$w find enclosed 0 [expr $y+10] $maxx $maxy] {
 	$w move $b 0 -$dy
	if [info exists nn(tree,$b,line)] {
	    scan [$w coords $nn(tree,$b,line)] "%f %f %f %f" a1 b1 a2 b2
	    if {$b1 <= [expr $y+5]} {
		$w coords $nn(tree,$b,line) $a1 $b1 $a2 [expr $b2-$dy]
	    }
	}
    }
}
proc n_lrtree_show {v root} {
    global n nn

    if [winfo exists $v] {
	wm deiconify $v
	raise $v
    } {
	if {[string compare $v .lr] == 0} {
            set class NoosaFullTree
            set title "Noosa Tree (Source and Computed)"
        } elseif {[string compare $v .lr0] == 0} {
            set class NoosaSrcTree
            set title "Noosa Tree (Source)"
        } else {
            set class NoosaCompTree
            set title "Noosa Tree (Computed)"
        }
        toplevel $v -class $class
	wm title $v $title

	frame $v.m -relief raised -borderwidth 1

	set m $v.m.tree.m
	menubutton $v.m.tree -menu $m -text "Tree" -underline 0
	menu $m -tearoff 0
	$m add command -label "Node" -underline 0 \
            -command "n_nodecmd $v"
	$m add command -label "Save tree as Postscript" -underline 5 \
            -command "n_pscmd $v 1"
	$m add command -label "Save window as Postscript" -underline 5 \
            -command "n_pscmd $v 0"
	$m add separator
	$m add command -label "Close" -underline 0 \
	    -command "destroy $v"

	set m $v.m.help.m
	menubutton $v.m.help -menu $m -text "Help" -underline 0
	menu $m -tearoff 0
        n_help_setup .lr $m

	pack $v.m.tree -side left
	pack $v.m.help -side right
	pack $v.m -side top -fill x

# Commented out because canvas text items do not scale currently
#	set n(attr,zoom) 1.0
#	set n(attr,zf) 1.0
#	frame $v.s
#	label $v.s.l -text "Zoom: "
#	scale $v.s.s -from 0.1 -to 1.0 -orient horiz -showvalue false \
#	    -resolution 0.01 -command n_lrtree_zoom -variable n(attr,zf)
#	pack $v.s.l -side left
#	pack $v.s.s -side left -fill x -expand yes
#	pack $v.s -side top -fill x

        frame $v.c -borderwidth 1 -relief sunken
        canvas $v.c.c \
	    -scrollregion [list 0 0 5000 5000] \
	    -xscrollcommand "$v.c.x set" \
	    -yscrollcommand "$v.c.y set"
        scrollbar $v.c.x -orient horizontal -relief sunken \
	    -command "$v.c.c xview"
        scrollbar $v.c.y -orient vertical -relief sunken \
	    -command "$v.c.c yview"
    }

    $v.c.c create text 0 0 -text ""
    set f "$n(treeFont) $n(treeFontSize)"
    set size [eval n_lrtree_build {$f} [n_send get_all_nodes $root]]
    scan $size "%d %d" w h
    $v.c.c configure -scrollregion [list 0 0 $w $h]
    pack $v.c.y -side right -fill y
    pack $v.c.x -side bottom -fill x
    pack $v.c.c -side left -fill both -expand yes
    pack $v.c -side top -fill both -expand yes

    bind $v.c.c <Button-2> "$v.c.c scan mark %x %y"
    bind $v.c.c <Control-Button-1> "$v.c.c scan mark %x %y"
    bind $v.c.c <B2-Motion> "$v.c.c scan dragto %x %y"
    bind $v.c.c <Control-B1-Motion> "$v.c.c scan dragto %x %y"

    $v.c.c delete all
    n_lrtree_draw $v
    n_tree_see $v.c.c ${v}Node:$nn(tree,$root,num)
}

#proc n_lrtree_zoom {zf} {
#    global n
#
#    set sf [expr $zf / $n(attr,zoom)]    
#    .lr$n(tnum).c.c scale all 0 0 $sf $sf
#    set n(attr,zoom) $zf
#}

proc n_lrtree_drawnode {v parent node prod x y} {
    global n nn

    set w $v.c.c
    if {[info exists nn(tree,$node,num)]} {
	set num $nn(tree,$node,num)
    } else {
	set num [incr nn(tree,num)]
	set nn(tree,$node,num) $num
	set nn(tree,$num,node) $node
    }
    if ![info exists nn(tree,$node,parent)] {
        set nn(tree,$node,parent) $parent
    }

    set tag ${v}Node:$num

    set f "$n(treeFont) $n(treeFontSize)"
    set id1 [$w create text $x $y -anchor s \
                 -text $n(attr,$prod,lhs) -font $f -tag $tag]
    set id2 [$w create text $x $y -anchor n \
                 -text "($n(attr,$prod,name))" -font $f -tag $tag]
    scan [$w bbox $id1] "%d %d %d %d" minx miny maxx maxy
    set f "$n(treeFont) [expr $n(treeFontSize) * 8 / 10]"
    $w create text $minx $miny -anchor e -text $num -tag n$id1 -font $f
    if {$node != 0} {
        set nn($w,$node,sid) $id1
        set nn($w,$node,rid) $id2
        n_tree_bind $w $num $node $prod $tag $id1 $id2
    }
}

proc n_lrtree_lineto {v fx fy tx ty} {
    global n

    set w $v.c.c
    $w create line $fx $fy $tx $ty
}

proc n_tree_bind {w num node prod tag id1 id2} {
    global n nn

    if {![info exists n(attr,$node,scount)]} {
	set n(attr,$node,scount) 0
	set n(attr,$node,rcount) 0
	set n(attr,$node,hids) {}
    }
    if {$n(attr,$node,scount) > 0} {
	n_tree_setmark $node 0
    }
    if {$n(attr,$node,rcount) > 0} {
	n_tree_setmark $node 1
    }

    scan [n_send get_node_coords $node] "%d %d %d %d" sl sc el ec
    set msc [expr $sc-1]
    set mec [expr $ec-1]
    if {! [string match "LST*" $n(attr,$prod,lhs)]} {
        .input.t tag add $tag $sl.$msc $el.$mec
        .input.t tag lower $tag
    }

    if {![info exists nn(tree,$num,bind)]} {
        if {($sl == $el) && ($sc == $ec)} {
            set nn(tree,$num,hl) "
                n_hl $sl $msc $el $ec
            "
            set s [format "%s Node:%d %s: %s" $sl,$sc $num \
                       $n(attr,$prod,name) \
                       "$n(attr,$prod,lhs) ::=$n(attr,$prod,rhs)"]
        } else {
            set nn(tree,$num,hl) "
                n_hl $sl $msc $el $mec
            "
            set s [format "%s-%s Node:%d %s: %s" $sl,$sc $el,$ec $num \
                       $n(attr,$prod,name) \
                       "$n(attr,$prod,lhs) ::=$n(attr,$prod,rhs)"]
        }
        set nn(tree,$num,bind) "
            n_say \{$s\n\}
        "
    }
    set n(attr,$tag,hl) $nn(tree,$num,hl)

    $w bind $id1 <Button-3> \
        "n_tree_symb_menu $w $node $n(attr,$prod,lhs) %X %Y $num \
         \"Attributes of symbol $n(attr,$prod,lhs) (node $num)\""
    $w bind $id2 <Button-3> \
        "n_tree_rule_menu $w $node %X %Y $num \
        \"Attributes and terminals of rule $n(attr,$prod,name) (node $num)\""
    $w bind $id1 <Button-1> "$nn(tree,$num,bind); n_tree_see $w $tag"
    $w bind $id2 <Button-1> "$nn(tree,$num,bind); n_tree_see $w $tag"
}

proc n_tree_set {w node attr type value} {
    global nn
    n_say "Node:$nn(tree,$node,num) $attr = "
    n_say_val $type $value
    n_say "\n"
}

proc n_tree_mark {w node israttr on} {
    global n nn

    if $israttr {
        set id $nn($w,$node,rid)
    } else {
        set id $nn($w,$node,sid)
    }
    set f "$n(treeFont) $n(treeFontSize)"
    if $on {
        set font "$f underline"
        $w itemconfigure $id -fill $n(nodeColour) -font $font
    } else {
        $w itemconfigure $id -fill black -font $f
    }
}

proc n_tree_setmark {node isrule} {
    global n nn t

    if [winfo exists .lr] {
        n_tree_mark .lr.c.c $node $isrule 1
    }
    foreach v [winfo children .] {
        if {[string match .lr* $v] || [string match .tv* $v]} {
            n_tree_mark $v.c.c $node $isrule 1
        }
    }
    if [winfo exists .tb] {
        set parent $nn(tree,$node,parent)
        if {$parent == -1 || [info exists t(tree,$parent,open)] &&
	      $t(tree,$parent,open)} {
            n_tree_mark .tb.c.c $node $isrule 1
        }   
    } 
}

proc n_tree_clearmark {node isrule} {
    global n

    if [winfo exists .lr] {
        n_tree_mark .lr.c.c $node $isrule 0
    }
    for {set i 0} {$i < $n(tnum)} {incr i 1} {
        set v .lr$i
        if [winfo exists $v] {
            n_tree_mark $v.c.c $node $isrule 0
        }
    }
    if [winfo exists .tb] {
        n_tree_mark .tb.c.c $node $isrule 0
    }
}

proc n_tree_break {w node val attr uattr type kind {symb ""}} {
    global n nn

    set event "attr_$type"
    if $kind {
        upvar n(attr,$node,rcount) count
        upvar n(attrs,$node,$attr,rid) id
        if {$kind == 2} {
            set event "term_$type"
        }
    } else {
        upvar n(attr,$node,scount) count
        upvar n(attrs,$node,$attr,sid) id
    }

    if [info exists id] {
        n_remove $event $id
        unset id
        incr count -1
    }

    if {[string compare $val "stop"] == 0} {
	set b "n_break"
    } else {
	set b ""
    }
    switch $val {
	stop -
	show {
	    incr count
	    if {$count == 1} {
		n_tree_setmark $node $kind
	    }
            set namefilter ""
            switch $kind {
                0 {set aname "$symb.$uattr"; set cond "(\$is_symb == 1) &&"}
                1 {set aname ".$uattr"; set cond "(\$is_symb == 0) &&"}
                2 {set aname "$uattr"; set cond "";
                    set namefilter "regsub -all {\[\]\[\]} \$name \"\" name;"}
            }
	    set id \
 	        [n_handle 0 "evaluation of Node:$nn(tree,$node,num) $aname" \
		     $event "
              $namefilter
	      if \"$cond ($node == \$root) && (\\\"$attr\\\" == \\\"\$name\\\")\" \{
                  n_tree_set $w $node \{$aname\} $type \$value
                  $b
	      \}
	        " 1]
        }
	ignore {
	    if {$count == 0} {
		n_tree_clearmark $node $kind
	    }
	}
    }
}

proc n_tree_item_reset {} {
    global n
    set n(items) 0
}

proc n_tree_item {mn l c} {
    global n
    upvar $mn m
    if {$n(items) == 10} {
        set mc $m.c
        menu $mc -tearoff 1
        $m add cascade -label "More..." -menu $mc
        set m $mc
        set n(items) 1
    } else {
        incr n(items)
    }
    $m add cascade -label $l -menu $c
}

proc n_tree_symb_menu {w node symb x y num label} {
    global n

    set rm .mn$node
    set m $rm
    if {![winfo exists $m]} {
	eval menu $m -tearoff 1
        set attrs [n_send get_symb_attrs $node]
        $m add command -label $label
        if {[llength $attrs] == 0} {
            $m add command -label "None"
        } else {
            n_tree_item_reset
            foreach attr $attrs {
                set a [lindex $attr 0]
                set t [lindex $attr 1]
                set n(sattrs,$node,$a) ignore
                eval menu $m.a$a -tearoff 0
                $m.a$a add radiobutton -label "Show" \
                    -variable n(sattrs,$node,$a) -value show \
                    -command "n_tree_break $w $node \$n(sattrs,$node,$a) $a $a $t 0 $symb"
                $m.a$a add radiobutton -label "Show, stop" \
                    -variable n(sattrs,$node,$a) -value stop \
                    -command "n_tree_break $w $node \$n(sattrs,$node,$a) $a $a $t 0 $symb"
                $m.a$a add radiobutton -label "Ignore" \
                    -variable n(sattrs,$node,$a) -value ignore \
                    -command "n_tree_break $w $node \$n(sattrs,$node,$a) $a $a $t 0 $symb"
                n_tree_item m "$a : $t" $m.a$a
            }
        }
    }
    tk_popup $rm $x $y
}

proc n_tree_rule_menu {w node x y num label} {
    global n

    set rm .mr$node
    set m $rm
    if {![winfo exists $m]} {
	eval menu $m -tearoff 1
        set attrs [n_send get_rule_attrs $node]
        set terms [n_send get_rule_terms $node]
        $m add command -label $label
        if {[llength $attrs]+[llength $terms] == 0} {
            $m add command -label "None"
        } else {
            n_tree_item_reset
            foreach attr $attrs {
                set a [lindex $attr 0]
                set t [lindex $attr 1]
                set n(rattrs,$node,$a) ignore
                eval menu $m.a$a -tearoff 0
                $m.a$a add radiobutton -label "Show" \
                    -variable n(rattrs,$node,$a) -value show \
                    -command "n_tree_break $w $node \$n(rattrs,$node,$a) $a $a $t 1"
                $m.a$a add radiobutton -label "Show, stop" \
                    -variable n(rattrs,$node,$a) -value stop \
                    -command "n_tree_break $w $node \$n(rattrs,$node,$a) $a $a $t 1"
                $m.a$a add radiobutton -label "Ignore" \
                    -variable n(rattrs,$node,$a) -value ignore \
                    -command "n_tree_break $w $node \$n(rattrs,$node,$a) $a $a $t 1"
                n_tree_item m ".$a : $t" $m.a$a
            }
            foreach term $terms {
                set a [lindex $term 0]
                regsub -all {[][]} $a "" at
                set t [lindex $term 1]
                set n(rterms,$node,$at) ignore
                eval menu $m.t$at -tearoff 0
                $m.t$at add radiobutton -label "Show" \
                    -variable n(rterms,$node,$at) -value show \
                    -command "n_tree_break $w $node \$n(rterms,$node,$at) $at \{$a\} $t 2"
                $m.t$at add radiobutton -label "Show, stop" \
                    -variable n(rterms,$node,$at) -value stop \
                    -command "n_tree_break $w $node \$n(rterms,$node,$at) $at \{$a\} $t 2"
                $m.t$at add radiobutton -label "Ignore" \
                    -variable n(rterms,$node,$at) -value ignore \
                    -command "n_tree_break $w $node \$n(rterms,$node,$at) $at \{$a\} $t 2"
                n_tree_item m "$a : $t" $m.t$at
            }
        }
    }
    tk_popup $rm $x $y
}

proc n_tree_see_clear {w} {
    $w delete highlight
}

proc n_tree_see {w tag} {
    global n

    scan [$w cget -scrollregion] "%*d %*d %d %d" cmaxx cmaxy
    scan [$w coords $tag] "%f %f" x y
    set xr [expr $x/$cmaxx]
    set yr [expr $y/$cmaxy]
    scan [$w xview] "%f %f" minx maxx
    scan [$w yview] "%f %f" miny maxy
    set wd [winfo width $w]

    if {($xr < $minx) || ($xr > $maxx)} {
	$w xview moveto [expr ($x-($wd/2))/$cmaxx]
    }
    if {($yr < $miny) || ($yr > $maxy)} {
	$w yview moveto [expr ($y-20)/$cmaxy]
    }
    n_tree_see_clear $w
    eval $w create rectangle [$w bbox $tag] -tags {highlight} -width 1 \
        -outline $n(nodeColour)
    eval $n(attr,$tag,hl)
    $w focus $tag
}

# Command initialisation

proc n_cmdinit {} {
    global n

    # Specs
    set n(specs) 0
    set n(files) ""

    # Trace
    set n(tracere) ".*"

    # Tree count
    set n(tnum) 0
}

proc n_eventinit {} {
    global n

    # Process events
    n_handle 0 Process_init init {
	global n
	set n(status) "running"
	set n(pid) $pid
        set n(input_mod,ids) [n_handle 0 Mod_check source_changed {
            n_input_mod .input.t "$filename" $init $curline $curcol $line $col
        } 1]
    } 1
    n_handle 0 Process_exit exit {
	global n
	set n(status) "dead"
    } 1
    n_handle 0 Process_stopped stopped {
	n_stopped $locale
    } 1

    # Coord
    n_handle 0 Coord_init init {
        global n
        set n(breaks) {}
    } 1
    n_handle 0 Coord_source_changed source_changed {
        global n
        lappend n(breaks) $filename $curline $curcol [expr $line-$curline] \
            [expr $col-$curcol]
    } 1

    # Message (not a command)
    n_handle 0 Message_message message {
	n_say [format "%6s %s %s\n" $line,$col $severity $text]
    } 1
}

proc n_eventset {mode} {
    global n

    if {$mode == 1} {
        # Install handlers
        # Phrase
        lappend n(tree,ids) [n_handle 1 Phrase_finit tree 1]
        lappend n(finit,ids) [n_handle 1 Phrase_finit finit 1]
        lappend n(production,ids) [n_handle 1 Phrase_production production 1]

        # Token
        lappend n(tree,ids) [n_handle 1 Token_finit tree 1]
        lappend n(finit,ids) [n_handle 1 Token_finit finit 1]
        lappend n(token,ids) [n_handle 1 Token_token token 1]

        set n(hinstalled) 1
    } else {
        # Remove handlers
        foreach event {tree finit production token} {
            foreach id $n($event,ids) {
                n_remove $event $id
            }
            set n($event,ids) {}
        }
        set n(hinstalled) 0
    }
}

# $Id: noosa.tcl,v 1.40 2013/03/13 02:38:04 profw Exp $ 
# Copyright (c) 1994-1999 Anthony M.Sloane 
# noosa.tcl 
# Startup file for noosa

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

# Make sure we can find the rest of noosa
set auto_path [list $n(lib) $tk_library [info library]]

# Turn on profiling if requested
if $n(profile) {
    package require profile
}

# Fix up some Delete bindings (we don't like the defaults)
bind Entry <Delete> {
    tkEntryBackspace %W
}
bind Entry <Meta-Delete> {
    %W delete [string wordstart [%W get] [expr [%W index insert] - 1]] \
        insert
}
bind Text <Delete> {
    if {[%W tag nextrange sel 1.0 end] != ""} {
        %W delete sel.first sel.last
    } elseif [%W compare insert != 1.0] {
        %W delete insert-1c
        %W see insert
    }
}
bind Text <Meta-Delete> {
    %W delete {insert -1c wordstart} insert
}

# Default values
set n(aspects) {}
set n(events) {}
set nn(dummy) ""
set t(dummy) ""

# Set general options
option clear
option add Noosa*Scale*Width 12 startupFile
option add Noosa*Scrollbar*Width 12 startupFile
option add Noosa*Dialog.msg.wrapLength 7i startupFile
option add Noosa*selectBackground red startupFile
option add Noosa*selectForeground yellow startupFile

# Set defaults for Noosa-specific options
option add Noosa.width 80 startupFile
option add Noosa.inputHeight 15 startupFile
option add Noosa.transHeight 15 startupFile
option add Noosa.handHeight 20 startupFile
option add Noosa.fileWidth 80 startupFile
option add Noosa.fileHeight 30 startupFile
option add Noosa.treeWidth 400 startupFile
option add Noosa.treeHeight 300 startupFile
option add Noosa.treeFont TkFixedFont startupFile
option add Noosa.treeFontSize 10 startupFile
option add Noosa.valueColour blue startupFile
option add Noosa.nodeColour red startupFile

# Setup global array of options
foreach o [list width inputHeight transHeight handHeight \
           fileWidth fileHeight treeWidth treeHeight treeFont treeFontSize \
	   valueColour nodeColour \
           treeFullWidth treeFullHeight treeSrcWidth \
	   treeSrcHeight treeCompWidth treeCompHeight \
           treeIncrWidth treeIncrHeight] {
    set n($o) [option get . $o {}]
}
foreach o [list treeFullHeight treeSrcHeight treeCompHeight treeIncrHeight] {
    if {[string compare $n($o) ""] == 0} {
        set n($o) $n(treeHeight)
    }
}
foreach o [list treeFullWidth treeSrcWidth treeCompWidth treeIncrWidth ] {
    if {[string compare $n($o) ""] == 0} {
        set n($o) $n(treeWidth)
    }
}

# Convert user-level options to window-specific options 
option add *NoosaFile.t.t.width $n(fileWidth)
option add *NoosaFile.t.t.height $n(fileHeight)

option add *NoosaFullTree.c.c.width $n(treeFullWidth)
option add *NoosaFullTree.c.c.height $n(treeFullHeight)
option add *NoosaSrcTree.c.c.width $n(treeSrcWidth)
option add *NoosaSrcTree.c.c.height $n(treeSrcHeight)
option add *NoosaCompTree.c.c.width $n(treeCompWidth)
option add *NoosaCompTree.c.c.height $n(treeCompHeight)
option add *NoosaIncrTree.c.c.width $n(treeIncrWidth)
option add *NoosaIncrTree.c.c.height $n(treeIncrHeight)

# Setup window properties
wm title . "Noosa"
wm sizefrom . program
wm geometry . [option get . geometry {}]
selection clear

# Utility procedure to return the number of lines in a text window
proc n_text_height {w} {
    scan [$w dlineinfo 0.0] "%*d %*d %*d %d %*d" lh
    return [expr [winfo height $w] / $lh]
}

# Menu bar and menus
frame .m -relief raised -borderwidth 1

set m .m.noosa.m
menubutton .m.noosa -menu $m -text "Noosa" -underline 0
menu $m -tearoff 1

$m add command -label "Clear transcript" -underline 0 \
    -command ".trans.t delete 1.0 end"
$m add separator

set n(window) .input
$m add command -label "Search..." -underline 1 \
    -command {n_newSearch $n(window) $n(window).t}
$m add command -label "Forward search" -underline 0 -accelerator "^S" \
    -command {set n($n(window).search,dir) "-forwards"; \
              n_searchFile $n(window) $n(window).t} 
$m add command -label "Backward search" -underline 0 -accelerator "^R" \
    -command {set n($n(window).search,dir) "-backwards"; \
              n_searchFile $n(window) $n(window).t}

$m add separator
$m add command -label "Save" -underline 0 \
    -command {n_saveFile $n(window).t Save $n(window)}
$m add command -label "Save As..." -underline 5 \
    -command {n_saveFile $n(window).t SaveAs $n(window)}
$m add separator
$m add command -label "Quit" -underline 0 -command n_quitcmd

set m .m.exec.m
menubutton .m.exec -menu $m -text "Execution" -underline 0
menu $m -tearoff 1
$m add command -label "Run" -underline 0 -command n_runcmd \
    -accelerator "Alt-R"
$m add command -label "Continue" -underline 0 -command n_contcmd \
    -accelerator "Alt-C"
$m add command -label "Kill" -underline 0 -command n_killcmd \
    -accelerator "Alt-K"
set m .m.exec.m1
menu $m -tearoff 0
$m add command -label "Run" -underline 0 -command n_runcmd \
    -accelerator "Alt-R"
$m add command -label "Continue" -underline 0 -command n_contcmd \
    -accelerator "Alt-C"
$m add command -label "Kill" -underline 0 -command n_killcmd \
    -accelerator "Alt-K"
bind . <Alt-r> n_runcmd
bind . <Alt-c> n_contcmd
bind . <Alt-k> n_killcmd

set m .m.exam.m
menubutton .m.exam -menu $m -text "Examine" -underline 1
menu $m -tearoff 1
$m add command -label "Token" -underline 0 -command n_tokencmd
$m add command -label "Phrase" -underline 0 -command n_phrasecmd
$m add command -label "String" -underline 0 -command n_stringcmd
$m add command -label "Strings" -underline 2 -command n_stringscmd
$m add command -label "Describe coord" -underline 0 -command n_coorddesccmd
set m .m.exam.m1
menu $m -tearoff 0
$m add command -label "Token" -underline 0 -command n_tokencmd
$m add command -label "Phrase" -underline 0 -command n_phrasecmd
$m add command -label "String" -underline 0 -command n_stringcmd
$m add command -label "Strings" -underline 2 -command n_stringscmd
$m add command -label "Describe coord" -underline 0 -command n_coorddesccmd

set m .m.prof.m
menubutton .m.prof -menu $m -text "Profile" -underline 0
menu $m -tearoff 1
set n(Freq) 0
$m add checkbutton -label "Frequency profile" -underline 0 -variable n(Freq) \
    -command n_freqcmd -onvalue 1 -offvalue 0
$m add command -label "Zero frequencies" -underline 0 -command n_freqzerocmd
set n(Time) 0
$m add checkbutton -label "Time profile" -underline 0 -variable n(Time) \
    -command n_timecmd -onvalue 1 -offvalue 0
$m add command -label "Reset times" -underline 0 -command n_timezerocmd
set n(Trace) 0
$m add checkbutton -label "Event trace" -underline 0 -variable n(Trace) \
    -command n_tracecmd -onvalue 1 -offvalue 0
$m add command -label "Set event filter..." -underline 0 \
    -command n_traceexpcmd

set m .m.win.m
menubutton .m.win -menu $m -text "Windows" -underline 0
menu $m -tearoff 1
$m add cascade -label "Trees" -underline 0 -menu $m.trees
$m add command -label "Handlers" -underline 0 \
    -command  {if ![winfo exists .h] {n_handlerscmd}}
$m add command -label "Files" -underline 0 -command n_filescmd

set s $m.trees
menu $s -tearoff 1
set n(Tree,Full) 0
set n(Tree,Src) 0
set n(Tree,Comp) 0
set n(Tree,Incr) 0
$s add checkbutton -label "Just Source" -variable n(Tree,Src) \
    -command n_treecmd -underline 5
$s add checkbutton -label "Separate Computed" -variable n(Tree,Comp) \
    -command n_treecmd -underline 9
$s add checkbutton -label "Source and Computed" -variable n(Tree,Full) \
    -command n_treecmd -underline 1
$s add checkbutton -label "Incremental" -variable n(Tree,Incr) \
    -command n_treecmd -underline 0

set m .m.help.m
menubutton .m.help -menu $m -text "Help" -underline 0
menu $m -tearoff 1
n_help_setup . $m

pack .m.noosa .m.exec .m.exam .m.prof .m.win -side left
pack .m.help -side right
pack .m -side top -fill x

# Program entry window
set n(prog) [format "%*s" 200 ""]
entry .p -textvariable n(prog)
pack .p -side top -fill x

# Status display window
set n(smsg) ""
message .s -textvariable n(smsg) -aspect 10000 
pack .s -side top -fill x

# Link display window
set n(msg) ""
message .g -textvariable n(msg) -aspect 10000 
pack .g -side bottom -anchor w

# Main sub-windows
n_create_input
n_create_trans

# Initialise process, help and commands, set flag for initialisation
# of events and tree setup, build main help menu
n_processinit
n_cmdinit
set n(eventinit) 1
set n(setuptree) 1
n_helpinit
n_help_setup . .m.help.m

# Code to update menu items when status or db changes 

proc n_setitem {menu item {status {}} {prov {}} {val 1}} {
    global n
    if $val {
	if {($status == {}) || ([lsearch -exact $status $n(status)] != -1)} {
	    foreach p $prov {
		if {! [n_provided $p]} {
		    $menu entryconfigure $item -state disabled
		    return
		}
	    }
	    $menu entryconfigure $item -state normal
	    return
	}
    }
    $menu entryconfigure $item -state disabled
}

trace variable n(status) w n_setcmds
proc n_setcmds {name1 name2 op} {
    global n nn
    switch $n(status) {
	NULL -
        dead {
	    set n(smsg) "Status: not running"
        }
        stopped {
	    set n(smsg) "Status: stopped at $n(where)"
        }
        running {
	    set n(smsg) "Status: running"
        }
        default {
	    n_say "Error: status is \"$n(status)\" in n_setcmds\n"
	}
    }
    n_setitem .m.exec.m Run {dead stopped}
    n_setitem .m.exec.m Continue {stopped}
    n_setitem .m.exec.m Kill {stopped running}
    n_setitem .m.exam.m Phrase {stopped} {parser}
    n_setitem .m.exec.m1 Run {dead stopped}
    n_setitem .m.exec.m1 Continue {stopped}
    n_setitem .m.exec.m1 Kill {stopped running}
    n_setitem .m.exam.m1 Phrase {stopped} {parser}
    n_setitem .m.exam.m String {stopped} {string}
    n_setitem .m.exam.m Strings {stopped} {string}
    n_setitem .m.exam.m Token {} {lexical source}
    n_setitem .m.exam.m "Describe coord" {} {source}
    n_setitem .m.exam.m1 String {stopped} {string}
    n_setitem .m.exam.m1 Strings {stopped} {string}
    n_setitem .m.exam.m1 Token {} {lexical source}
    n_setitem .m.exam.m1 "Describe coord" {} {source}
    n_setitem .m.win.m "Trees" {} {attribution}
}

proc new_aspect {a} {
    global n
    lappend n(aspects) $a
}

proc new_event {e} {
    global n
    lappend n(events) $e
}

trace variable n(db) w n_setdb
proc n_setdb {name1 name2 op} {
    global n np
    source $n(db)
    set n(events) [lsort $n(events)]
    foreach e $n(events) {
	set s [list n_ename n_time]
	foreach {name doc} [lindex $e 2] {
	    lappend s $name
	}
        namespace eval "n_[lindex $e 0]" {}
	eval n_event_params [lindex $e 0] $s
    }
    set n(aspects) [lsort $n(aspects)]
    set n(hnames) {}
    trace vdelete n(db) w n_setdb
    n_setcmds "" "" ""
}

# Load monitoring support
source [lindex $argv 0]

# Set n(prog) and n(db) from args
set n(db) [lindex $argv 1]
set n(prog) [lrange $argv 2 end]

# Read user customisation files
if [file exists ~/.noosarc] {
    if {[catch {source ~/.noosarc} msg] != 0} {
        error "error in ~/.noosarc: $msg $errorInfo"
        exit 1
    }
}
if [file exists .noosarc] {
    if {[catch {source .noosarc} msg] != 0} {
        error "error in ./.noosarc: $msg $errorInfo"
        exit 1
    }
}

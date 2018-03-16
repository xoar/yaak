# $Id: process.tcl,v 1.33 2012/06/10 13:01:06 profw Exp $
# Copyright (c) 1994-1999 Anthony M. Sloane
# process.tcl
# Process control procedures for noosa

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

# exit
# Redefinition of exit to kill process if it exists

rename exit exit.old
proc exit {{exitstatus 0}} {
    n_killall
    exit.old $exitstatus
}

# n_break
# Called from event handlers to cause breakpoints

proc n_break {} {
    global n
    upvar n_ename ename
    n_stopped "handler \"[n_handlername]\" for event \"$ename\""
}

# n_cont
# Continue execution

proc n_cont {} {
    global n
    if {[catch "n_cont_child $n(pid)" msg] != 0} {
	n_say "$msg\n"
	set n(status) "dead"
    } {
	set n(status) "running"
    }
    return
}

# n_kill
# Kill the current process being debugged (if any)

proc n_kill {} {
    global n
    if {$n(pid) != -1} {
        if {[string compare $n(status) "dead"] != 0} {
	    if {[catch "n_kill_child $n(pid)" msg] != 0} {
		n_say "$msg\n"
		set n(status) "dead"
	    }
	    while {[string compare $n(status) "dead"] != 0 } {
	        tkwait variable n(status)
	    }
	}
	set n(pid) -1
    }
    return
}

# n_killall
# Kill everything, process being debugged and immediate child.
# These will be different if the child is a source-level debugger.

proc n_killall {} {
    global n
    n_kill
    if {$n(childpid) != -1} {
	catch "n_kill_child $n(childpid)"
	n_wait_child $n(childpid)
	set n(childpid) -1
    }
    n_finit_signals
}

# n_provided
# Is a monitoring aspect provided by the program?

proc n_provided {name} {
    global n
    return [expr "[lsearch $n(aspects) $name] != -1"]
}

# n_run
# Run a program prog with argument args in the background

proc n_run args {
    global n nn env
    n_killall
    if {[llength $args] != 0} {
        set n(prog) [join $args]
    } else {
	if {$n(prog) == ""} {
           error "must specify program and args"
	}
    }
    scan $n(prog) "%s " progname
    if [string match "*/*" $progname] {
        if {![file exists $progname] || \
            ![file executable $progname] || \
            [file isdirectory $progname]} {
            error "can't find $progname to execute"
        }
    } {
        set found 0
        foreach p [split $env(PATH) ":"] {
            if {[file exists $p/$progname] && \
                [file executable $p/$progname] && \
                ![file isdirectory $p/$progname]} {
                set found 1
                break
            }
        }
        if {!$found} {
            error "can't find $progname to execute"
        }
    }
    set nn(dummy) ""
    n_init_signals
    set l [eval exec $n(prog) </dev/tty >&/dev/tty &]
    set n(childpid) [lindex $l 0]
    return
}

# n_send
# Send a message to the child and collect response

proc n_send {args} {
    global n
    
    if {[string compare $n(status) "dead"] == 0} {
        error "The program must be running for that operation to be completed."
    }

    set n(retstat) -1
    n_sendb $n(pid) [join $args]
    if {$n(retstat) == 0} {
	return $n(result)
    } elseif {$n(retstat) == 1} {
	error $n(error) "n_send $args"
    } {
	error "bad return status $n(retstat) in n_send" "n_send $args"
    }
}

# n_stopped
# Called when the child stops
# n(where) must be assigned before n(status)

proc n_stopped {locale {stat ""}} {
    global n
    if {$stat == ""} {
        set n(where) "$locale"
    } {
	set n(where) "$locale $stat"
    }
    set n(status) stopped
    return
}

# n_processinit

proc n_processinit {} {
    global n env

    set n(status) "dead"
    set n(where) ""
    set n(handlers) {}
    set n(id) 0
    set n(pid) -1
    set n(childpid) -1
}


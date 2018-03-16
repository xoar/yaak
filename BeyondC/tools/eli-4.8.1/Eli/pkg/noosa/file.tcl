# $Id: file.tcl,v 2.5 1999/10/20 08:41:28 tony Exp $
# Copyright (c) 1997-1999 Anthony M. Sloane
# spec.tcl
# File window support for Noosa.

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

proc n_filescmd {} {
    global n

    set w ".f$n(specs)"
    incr n(specs)
    toplevel $w -class NoosaFile
    wm title $w ""
    set n($w,file) ""

    wm iconname $w "Specs"

    # Create the menu bar at the top of the window
    frame $w.m -relief raised -borderwidth 1
    set m $w.m.file.m
    set fileButton [menubutton $w.m.file -menu $m -text "File" -underline 0]
    set fileMenu [menu $m -tearoff 1]
    set m $w.m.help.m
    set helpButton [menubutton $w.m.help -menu $m -text "Help" -underline 0]
    set helpMenu [menu $m -tearoff 1]
    foreach i {"General" "File menu"} {
	$m add command -label $i -underline 0 \
	    -command "n_helpcmd .f \{$i\}"
    }
    pack $fileButton -side left
    pack $helpButton -side right
    pack $w.m -side top -fill x

    # Create the message window at the bottom of the screen
    set n($w,msg) ""
    message $w.g -aspect 10000 -textvariable n($w,msg)
    pack $w.g -side bottom -fill both

    # Create text widget at the bottom of the window with scroll bars
    # to the left and below 
    frame $w.t -relief raised -borderwidth 2
    pack $w.t -side bottom -fill both -expand true
    set fileText [text $w.t.t -height $n(fileHeight) -width $n(fileWidth) \
            -wrap none -yscrollcommand "$w.t.yscroll set" \
	    -xscrollcommand "$w.t.xscroll set"]
    set Yscroll [scrollbar $w.t.yscroll -orient vertical \
	    -command "$fileText yview" ]
    set Xscroll [scrollbar $w.t.xscroll -orient horizontal \
	    -command "$fileText xview" ]
    pack $Xscroll -side bottom -fill x
    pack $Yscroll -side right -fill y
    pack $fileText -side left -fill both -expand true

    # Center the window on the screen
    n_center_win $w

    # New file option
    $fileMenu add command -label "New" -underline 0 \
	-command "n_newFile $w $fileText"

    # Open file option
    $fileMenu add command -label "Open..." -underline 0 \
	-command "n_openFile $w $fileText " 
 
    # Search 
    $fileMenu add separator
    $fileMenu add command -label "Search..." -underline 1 -state disabled \
	-command "n_newSearch $w $fileText" 
    $fileMenu add command -label "Forward search" -underline 0 \
        -accelerator "^S" -state disabled \
	-command "set n($w.search,dir) \"-forwards\"; \
                  n_searchFile $w $fileText"
    $fileMenu add command -label "Backward search" -underline 0 \
        -accelerator "^R" -state disabled \
	-command "set n($w.search,dir) \"-backwards\"; \
                  n_searchFile $w $fileText"

    # Save and Save As options in the File Menu
    $fileMenu add separator
    $fileMenu add command -label "Save" -underline 0 -state disabled \
	    -command "n_saveFile $fileText Save $w "
    $fileMenu add command -label "Save As..." -underline 5 -state disabled \
	    -command "n_saveFile $fileText SaveAs $w "

    # Close
    $fileMenu add separator
    $fileMenu add command -label "Close" -underline 0 \
	    -command "n_closeWindow $fileText $w"

    # start with text window disabled
    $fileText configure -state disabled

    bind $fileText <Control-s> \
	"set n($w.search,dir) \"-forwards\"; n_searchFile $w $fileText"
    bind $fileText <Control-r> \
	"set n($w.search,dir) \"-backwards\"; n_searchFile $w $fileText" 

    return $w
}

proc n_updateMenu {w} {
    set m $w.m.file.m
    $m entryconfigure "Search..." -state normal
    $m entryconfigure "Forward search" -state normal
    $m entryconfigure "Backward search" -state normal
    $m entryconfigure "Save" -state normal
    $m entryconfigure "Save As..." -state normal
}

proc n_newFile {w textWindow} {
    global n

    set currentfile [n_getName $w]
    if {$currentfile != ""}  {
	if {![n_modified $textWindow $currentfile]} {
	    $textWindow delete 1.0 end
	} else {
	    if {![n_querySave $textWindow $currentfile $w]} {
		return 0
	    }
	}		 
	set n(files) [n_ldelete $n(files) $currentfile]
    }	
    $textWindow configure -state normal
    wm iconname $w untitled
    wm title $w untitled
    set n($w,file) untitled
    if [info exists n($w,dcode)] {
        unset $n($w,dcode)
    }
    focus $textWindow
    n_updateMenu $w
    set n($w,msg) "New file untitled"
    return 1
}

proc n_openFile {w textWindow} {
    global n

    set filename [tk_getOpenFile -title "Open File..."]

    if {[string compare $filename ""] == 0} {
	return
    } elseif {[lsearch $n(files) $filename ] == -1} {
	if {![n_showFile $w $textWindow $filename]} {
            return
        }
    } else {
	set n($w,msg) "$filename is already open"
	return
    }
    $textWindow mark set insert 1.0
    focus $textWindow
    n_updateMenu $w
    set n($w,msg) "Opened $filename"
}

proc n_showFile {w textWindow newfile {dcode {}}} {
    global n

    set currentfile [n_getName $w]
    if {$currentfile != ""}  {
	if {![n_modified $textWindow $currentfile]} {
	    $textWindow delete 1.0 end
	} else {
	    if {![n_querySave $textWindow $currentfile $w]} {
		return 0
	    }
	}		 
	set n(files) [n_ldelete $n(files) $currentfile]
    } else {
	$textWindow configure -state normal
    }	
    n_displayFile $textWindow $newfile
    wm iconname $w [file tail $newfile]
    wm title $w $newfile
    n_updateMenu $w
    set n($w,file) $newfile
    set n(files) [linsert $n(files) 0 $newfile]
    if [info exists n($w,dcode)] {
        unset $n($w,dcode)
    }
    if {$dcode != {}} {
        set n($w,dcode) $dcode
    }
    return 1
}

proc n_ldelete {list value} {
    set ix [lsearch $list $value]
    if {$ix >= 0} {
	return [lreplace $list $ix $ix]
    } else {
	return $list
    }
}

proc n_querySave {textWindow filename w} {
    set answer [tk_messageBox -icon question \
	    -message "\"$filename\" has been modified.\n\
	    Do you want to save it first? " -type yesnocancel ]
    switch -exact $answer {
	no {
	    $textWindow delete 1.0 end
	}
	yes {
	    n_saveFile $textWindow $filename $w
	    $textWindow delete 1.0 end
	}
	cancel {
	    return 0
	}
    }
    return 1
}

proc n_displayFile {textWindow file} {
    set fileID [open $file]
    $textWindow insert end [read -nonewline $fileID]
    close $fileID
}

proc n_closeWindow {textWindow w} {
    global n

    set filename [n_getName $w]
    if {$filename != ""} {
	if [n_modified $textWindow $filename] {
	    if {![n_querySave $textWindow $filename $w]} {
		return 0
	    }
            set filename [n_getName $w]
	}
	set n(files) [n_ldelete $n(files) $filename]
    }
    if [info exists n($w,dcode)] {
        eval $n($w,dcode)
    }
    destroy $w
    return 1
}

proc n_getName {w} {
    global n

    return $n($w,file)
}

proc n_saveFile {textWindow mode w} {
    global n

    set new 0
    if [string match .f* $w] {
        set default ""
    } else {
	set default [string trimleft $w "."].log
    }
	
    if {[string compare $mode "SaveAs"] == 0} {
	set new 1
	set filename [tk_getSaveFile -title "Save As..." -initialfile $default]
        set oldname [n_getName $w]
    } else {
        set filename [n_getName $w]
        if {[string compare $filename "untitled"] == 0} {
	    n_saveFile $textWindow "SaveAs" $w
	    return
        }
    }

    if {$filename != ""} {
	set fileID [open $filename "w"]
	puts -nonewline $fileID [$textWindow get 1.0 end]   
	close $fileID
	if $new {
    	    set n(files) [linsert [n_ldelete $n(files) $oldname] 0 $filename]
            if [string match .f* $w] {
	        wm iconname $w [file tail $filename]
	        wm title $w $filename
            }
            set n($w,file) $filename
        }
	set n($w,msg) "$filename saved"
    }
}

proc n_modified {textWindow filename} {
    set modified 1
    if [file exists $filename] {
	set fileID [open $filename]
	if {[string compare [$textWindow get 1.0 end] [read $fileID]] == 0} {
	    set modified 0
    	}
    	close $fileID
    } else {
	if [regexp "^\n?$" [$textWindow get 1.0 end]] {
	    set modified 0
	}
    }
    return $modified
}

proc n_newSearch {w textWindow} {
    global n

    set search [toplevel $w.search]
    wm title $search "Search..."
    n_center_win $search

    # intialize array n($search,dir), n($search,type), and n($search)
    if {![info exists n($search,dir)]} {
	 set n($search,dir) "-forwards"
    }
    if {![info exists n($search,type)]} {
	 set n($search,type) "-exact"
    }
    if {![info exists n($search)]} {
	set n($search) ""
	set n($search,last) ""
    } else {
	set n($search,last) $n($search)
    }

    set s_top [frame $search.top -relief raised ]
    
    set s_l [label $s_top.l -text "Search for: "] 
    set s_e [entry $s_top.e -relief sunken -textvar n($search)]

    set s_mid [frame $s_top.mid ]
    set s_c1 [checkbutton $s_mid.c1 -text "Regular Expression" \
	  -variable n($search,type) -offvalue "-exact" -onvalue "-regexp"]
    set s_c2 [checkbutton $s_mid.c2 -text "Search Backwards" \
	  -variable n($search,dir) -offvalue "-forwards" -onvalue "-backwards"]
    
    set s_bot [frame $search.bot -relief groove -bd 1 ]

    set s_b1 [button $s_bot.b1  -text "Search" \
	-command "n_searchFile $w $textWindow " ]
    set s_b2 [button $s_bot.b2  -text "Clear" \
	-command "$s_e delete 0 end; set n($search) \"\" " ]
    set s_b3 [button $s_bot.b3  -text "Close" \
	-command "destroy $search" ]

    pack $s_c2 $s_c1 -side right -expand true
    pack $s_mid -side bottom -fill both -expand true  -pady 5
    pack $s_l -side left
    pack $s_e -side right -fill both -expand true
    pack $s_top -side top -fill both -pady 5
    pack $s_b1  -side left -expand true -anchor w -pady 5
    pack $s_b3  -side right -expand true -anchor e -pady 5
    pack $s_b2  -side left -expand true -anchor c -pady 5
    pack $s_bot -side bottom -fill both 

    bind $s_e <Return> "n_searchFile $w $textWindow "
    focus $s_e
}

proc n_searchFile {w textWindow } {
    global n

    set n($w,msg) ""

    if {[info exists n($w.search)] && ([string length $n($w.search)] != 0)} {
    	set search $n($w.search)
    } else {
	n_newSearch $w $textWindow
	return
    }

    set dir $n($w.search,dir)
    set type $n($w.search,type)

    if {[info exists n($w.search,l_index)] && \
	    ([string compare $n($w.search,last) $search] == 0)} {
	if {$n($w.search,l_index) == [$textWindow index insert]} {
	    if {[string compare $dir "-forwards"] == 0} {
	        set index "$n($w.search,l_index) + $n($w.search,l_size) chars"
	    } else {	
	        set index $n($w.search,l_index)
	    }
	} else {
	    set index [$textWindow index insert]
	}
    } else {
	set index [$textWindow index insert]
    }

    set sel [$textWindow search $dir $type -count size -- $search $index]

    if {[string compare $sel ""] == 0} {
        if [string match .f* $textWindow] {
	    set n($w,msg) "\"$search\" not found"
        } else {
            set n(msg) "\"$search\" not found"
        }
    } else {
	set n($w.search,last) $search
 	set n($w.search,l_index) $sel 
 	set n($w.search,l_size) $size
	set n($w.search,l_dir) $dir
        $textWindow tag delete sel
        $textWindow tag remove sel 1.0 end
	$textWindow tag add sel $sel "$sel + $size chars"
	$textWindow see $sel 
	$textWindow mark set insert $sel
    } 
}

proc n_spec_kill {} {
    global n

    for {set i [expr $n(specs) - 1]} {$i > -1 } {incr i -1} {
	if [winfo exists .f$i]  {
            if {![n_closeWindow .f$i.t.t .f$i]} {
                return 0
            }
	}
    }
    return 1
}


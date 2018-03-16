# $Id: info.tcl,v 1.13 2002/08/27 15:01:09 waite Exp $

proc NodeDisplay {infofile infonode} {
  global errmsg NodeBody
  wm title . "TclInfo: ($infofile)$infonode"
  set errmsg "Move to a menu item or note by clicking on the text"
  .tx.t configure -state normal
  .tx.t delete 1.0 end
  .tx.t insert end $NodeBody
  .tx.t mark set insert 1.0
  .tx.t configure -state disabled
  if {[winfo exists .t.edit.eg]} {
    destroy .t.edit.eg
  }
}

proc SelectMenuOrNote {} {
  .tx.t mark set insert current
  set low [.tx.t index {current linestart}]
  set high [.tx.t index {current lineend}]
  if [c_NodeMenu [.tx.t get $low $high]] {return 1}
  if [.tx.t compare 1.0 < $low] then {
    set low [.tx.t index "$low -1 lines"]
  }
  if [.tx.t compare $high < end] then {
    set high [.tx.t index "$high +1 lines"]
  }
  return [c_NodeNote [.tx.t get $low $high] \
	             [.tx.t get $low {current -1 chars}]]
}

proc GotoButton {pattern} {
  if [expr [string length $pattern] == 0] then {
    global errmsg
    set errmsg "No destination node has been specified"
    return
  }
  c_GotoNode $pattern
}

proc SearchButton {pattern} {
  if [expr [string length $pattern] == 0] then {
    global errmsg
    set errmsg "No search string has been specified"
    return
  }
  set pos [.tx.t index insert]
  set dot [string first . $pos]
  set ll [expr $dot - 1]
  set fc [expr $dot + 1]
  if [c_SearchNode $pattern [string range $pos 0 $ll] [string range $pos $fc end]] {
    .tx.t mark set insert sel.last
    .tx.t yview -pickplace insert
  }
}

proc NewEgFiles {} {
  global EgFiles
  set EgFiles {}
}

proc EgFile {label value} {
  global EgFiles
  lappend EgFiles "[list $label $value]"
}

proc DoEdit {{egindex 0}} {
  global EgFiles
  c_EditButton [lindex [lindex $EgFiles $egindex] 1]
}

proc ShowEgFiles {} {
  global EgFiles
  if {[winfo exists .t.edit.eg]} {
    wm geometry .t.edit.eg "+[winfo rootx .t.edit]+[winfo rooty .t.edit]"
    raise .t.edit.eg
  } {
    toplevel .t.edit.eg
    wm geometry .t.edit.eg "+[winfo rootx .t.edit]+[winfo rooty .t.edit]"

    frame .t.edit.eg.f
    set maxlen 0
    foreach egfile $EgFiles {
      set tmp [string length [lindex $egfile 0]]
      if { $tmp > $maxlen } {
        set maxlen $tmp
      }
    }
    listbox .t.edit.eg.f.l -yscrollcommand ".t.edit.eg.f.s set" \
      -exportselection no -width $maxlen
    foreach egfile $EgFiles {
      .t.edit.eg.f.l insert end [lindex $egfile 0]
    }
    bind .t.edit.eg.f.l <Button-1> {DoEdit [.t.edit.eg.f.l index @%x,%y]}
    scrollbar .t.edit.eg.f.s -orient vert -command ".t.edit.eg.f.l yview"
    pack .t.edit.eg.f.l -side left
    pack .t.edit.eg.f.s -side right -fill y
    pack .t.edit.eg.f

    button .t.edit.eg.c -text "Cancel" -width 8 -command {destroy .t.edit.eg}
    pack .t.edit.eg.c
  }
}

proc control {} {
  frame .t
  button .t.quit -text "Quit" -width 6 -command {destroy .}
  button .t.dir  -text "Dir"  -width 6 -command {c_GotoNode {(dir)Top}}
  button .t.prev -text "<="   -width 6 -command {c_GotoNode $PrevNodeName}
  button .t.next -text "=>"   -width 6 -command {c_GotoNode $NextNodeName}
  button .t.goup -text "Up"   -width 6 -command {c_GotoNode $UpNodeName}
  button .t.undo -text "Back" -width 6 -command {c_BackButton}
  button .t.edit -text "Edit" -width 6 -command {DoEdit}
  bind .t.edit <Button-3> {ShowEgFiles}
  button .t.exec -text "Run"  -width 6 -command {c_ExecButton}
  pack .t.quit .t.dir .t.prev .t.next .t.goup .t.undo .t.edit .t.exec \
    -side left
  pack .t -anchor w

  frame .m
  button .m.goto -text "Goto Node" -command {
    GotoButton [.m.input get]
  }
  button .m.search -text "Search" -command {
    SearchButton [.m.input get]
  }
  message .m.m -aspect 10000 -text "Node/String:"
  entry .m.input -width 30 -borderwidth 1 -relief sunken
  pack .m.goto .m.search .m.m .m.input \
    -side left 
  pack .m -anchor n

  frame .b
  button .b.complain -text "Complain..." -command {complain}
  button .b.options -text "Options..." -command {options}
  button .b.print -text "Print Node" -command {
    print {Do you really want to print this node?} c_PrintNodeButton
  }
  button .b.pman -text "Print Manual" -command {
    global ManualMessage
    print $ManualMessage c_PrintManualButton
  }
  pack .b.complain .b.options .b.print .b.pman \
    -side left
  pack .b -anchor n

  global errmsg
  message .i -aspect 10000 -justify left -textvariable errmsg
  pack .i -anchor n

  frame .tx -borderwidth 1 -relief raised
  scrollbar .tx.s -relief sunken -command ".tx.t yview"
  pack .tx.s -side right -fill y
  text .tx.t -height 40 -width 80 -yscrollcommand ".tx.s set" \
    -borderwidth 1 -relief raised -state disabled -exportselection yes
  set bg [lindex [.tx.t configure -background] 4]
  set fg [lindex [.tx.t configure -foreground] 4]
  .tx.t tag configure sel -foreground $bg -background $fg
  bind .tx.t <Any-KeyPress> {
    if {"%A" != ""} {
      global errmsg
      set errmsg "No key binding for '%K'."
    }
  }
  bind .tx.t <ButtonRelease-1> {
    set r [lindex [.tx.t tag ranges sel] 0]    
    if {[lindex $r 0] == [lindex $r 1]} {
      SelectMenuOrNote
    }
    focus .tx.t
  }
  bind . <ButtonRelease-1> {
    if {"%W" != ".m.input"} {
      focus .tx.t
    }
  }
  bind .tx.t b {.t.undo invoke}
  bind .tx.t d {.t.dir  invoke}
  bind .tx.t e {.t.edit invoke}
  bind .tx.t n {.t.next invoke}
  bind .tx.t p {.t.prev invoke}
  bind .tx.t q {.t.quit invoke}
  bind .tx.t r {.t.exec invoke}
  bind .tx.t u {.t.goup invoke}
  bind .tx.t <Key-space> {
    set h [lindex [.tx.t configure -height] 4]
    .tx.t yview "[.tx.t index @0,0]+ $h lines"
  }
  bind .tx.t <Key-Delete> {
    set h [lindex [.tx.t configure -height] 4]
    .tx.t yview "[.tx.t index @0,0]- $h lines"
  }
  pack .tx.t -expand 1 -fill both
  pack .tx -expand 1 -fill both
  focus .tx.t
}

proc complain {} {
  global ComplaintSubj

  toplevel .x
  wm title .x "Complainer"

  frame .x.b
  button .x.b.send -text "Send" -width 8 -command {
    c_SendComplaint $ComplaintSubj [.x.c.t get 1.0 end]
    focus .tx.t
    destroy .x
  }
  button .x.b.quit -text "Cancel" -width 8 -command {
    focus .tx.t
    destroy .x
  }
  pack .x.b.send .x.b.quit -side left -fill x 
  pack .x.b -side bottom

  frame .x.c -borderwidth 1 -relief sunken
  scrollbar .x.c.s -relief sunken -command ".x.c.t yview"
  pack .x.c.s -side right -fill y
  text .x.c.t -height 10 -width 80 -yscrollcommand {.x.c.s set} \
    -borderwidth 1 -relief sunken
  pack .x.c.t -expand 1 -fill both
  pack .x.c -side bottom -expand 1 -fill both

  message .x.msg -justify center -aspect 1000 \
    -text "Please set the subject and type your complaint\
into the window below.\n\
When done, click 'Send' to send the message\
or 'Cancel' to return to browsing without sending."
  pack .x.msg -expand 1 -fill x

  frame .x.s
  message .x.s.m -text "Subject:" -aspect 10000
  if {! [info exists ComplaintSubj]} {
      set ComplaintSubj "Eli complaint"
  }
  entry .x.s.e -textvariable ComplaintSubj -width 50
  pack .x.s.m .x.s.e -side left
  pack .x.s
  focus .x.s.e
}

proc options {} {
  toplevel .x
  wm title .x "Options"
  global OptionValue OptionDesc

  frame .x.u
  frame .x.u.t
  button .x.u.t.do -text "Done" -command {c_ResetOptions; destroy .x}
  pack .x.u.t.do -side right 

  message .x.u.t.msg -aspect 1000 \
    -text "Set the options and click 'Done' when finished.  Click on an \
           option name to see a description of the option."
  pack .x.u.t.msg
  pack .x.u.t

  set msg ""
  message .x.u.desc -textvariable desc -aspect 10000 -borderwidth 1 \
    -relief sunken
  pack .x.u.desc -side top -fill x 

  pack .x.u

  proc describe option {
      global OptionDesc desc
      set desc "$option: $OptionDesc($option)"
  }

  frame .x.b

  frame .x.b.editor
  message .x.b.editor.m -text "EDITOR" -aspect 10000
  bind .x.b.editor.m <Button-1> {describe EDITOR}
  entry .x.b.editor.e -borderwidth 1 -relief sunken -width 50 \
    -textvariable OptionValue(EDITOR)
  .x.b.editor.e icursor end
  pack .x.b.editor.m -side left -anchor e
  pack .x.b.editor.e -side right
  pack .x.b.editor -anchor e

  frame .x.b.wineditor
  message .x.b.wineditor.m -text "WINEDITOR" -aspect 10000
  bind .x.b.wineditor.m <Button-1> {describe WINEDITOR}
  entry .x.b.wineditor.e -borderwidth 1 -relief sunken -width 50 \
    -textvariable OptionValue(WINEDITOR)
  .x.b.wineditor.e icursor end
  pack .x.b.wineditor.m -side left -anchor e
  pack .x.b.wineditor.e -side right
  pack .x.b.wineditor -anchor e

  frame .x.b.winrunner
  message .x.b.winrunner.m -text "WINRUNNER" -aspect 10000
  bind .x.b.winrunner.m <Button-1> {describe WINRUNNER}
  entry .x.b.winrunner.e -borderwidth 1 -relief sunken -width 50 \
    -textvariable OptionValue(WINRUNNER)
  .x.b.winrunner.e icursor end
  pack .x.b.winrunner.m -side left -anchor e
  pack .x.b.winrunner.e -side right
  pack .x.b.winrunner -anchor e

  frame .x.b.printer
  message .x.b.printer.m -text "PRINTER" -aspect 10000
  bind .x.b.printer.m <Button-1> {describe PRINTER}
  entry .x.b.printer.e -borderwidth 1 -relief sunken -width 50 \
    -textvariable OptionValue(PRINTER)
  .x.b.printer.e icursor end
  pack .x.b.printer.m -side left -anchor e
  pack .x.b.printer.e -side right
  pack .x.b.printer -anchor e

  frame .x.b.se
  message .x.b.se.m -text "SEARCHINSENSITIVE" -aspect 10000
  bind .x.b.se.m <Button-1> {describe SEARCHINSENSITIVE}
  checkbutton .x.b.se.b -onvalue yes -offvalue no \
    -variable OptionValue(SEARCHINSENSITIVE) \
    -textvariable OptionValue(SEARCHINSENSITIVE) 
  pack .x.b.se.m .x.b.se.b -side left
  pack .x.b.se -anchor w

  pack .x.b -side left
}

proc DoPrint cmd {
  destroy .x
  global errmsg
  if [$cmd] {
    global OptionValue
    set errmsg "Output sent to the printer named \"$OptionValue(PRINTER)\""
  }
}

proc print {warning cmd} {
  toplevel .x
  wm title .x "Printer"

  frame .x.m
  message .x.m.msg -aspect 10000 -text $warning
  pack .x.m.msg
  pack .x.m -padx 1c -pady 0.5c

  frame .x.pr
  button .x.pr.ok -text "Print" -width 12 -borderwidth 3 -command "
    DoPrint $cmd
  "
  button .x.pr.ca -text "Cancel" -width 12 -borderwidth 0.6 -command {
    destroy .x
  }
  pack .x.pr.ok .x.pr.ca -side left -padx 5 -pady 5
  pack .x.pr -padx 1c -pady 0.5c
}

option clear
wm geometry . [option get . geometry TclInfo]
control

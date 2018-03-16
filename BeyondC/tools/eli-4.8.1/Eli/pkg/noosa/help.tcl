# $Id: help.tcl,v 2.10 1999/10/20 08:39:20 tony Exp $
# Copyright (c) 1996-1999 Anthony M. Sloane
# help.tcl
# Help information for Noosa.

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

proc n_helpinit {} {
    global n

    set n(help,.,About\ Noosa) "
* Noosa is a domain-level execution monitoring system for the Eli\
compiler construction system.  Using Noosa you can examine the\
behaviour of Eli-generated programs in terms of the specifications\
used to generate them.\n
* Noosa was written primarily by Tony Sloane at the University\
of Colorado, Boulder, James Cook University and Macquarie University.\
Marianne Brown at JCU wrote the file window code.  Tony Vanderlinden\
coded many improvements including the multiple tree displays and the\
current handlers window.\n
"

    set n(help,.,General) "
* The name of the program to be monitored and command-line arguments\
(if any) are entered into the entry field just under the menu bar.\
If you have invoked Noosa from Eli the program name should be set\
correctly but you may want to specify additional arguments or change\
them during monitoring.\n
* The two main text windows contain the input text of the processor\
and a transcript of monitoring output, respectively.  The transcript\
will also display any messages that your program generates using the\
Eli message reporting facility.  The default configuration makes the\
input window and the transcript window the same size.  You can adjust\
the size by dragging the middle horizontal scroll bar up or down.\n
* The text windows can be saved to files using the Save and Save As\
items in the Noosa menu.  There are also menu items that enable searching\
within these windows.\n
* Within the text windows the mouse buttons are used to select text\
(left, B1), display the Execution menu (middle, B2) and display the\
Examine menu (right, B3).\n
* The left button (B1) selects text in the standard fashion via single\
clicks (select a position), double clicks (select a word), triple\
clicks (select a line), or dragging (select an arbitrary text\
region).\n
* For users of machines with only one mouse button, B2 can be simulated\
with Control-B1 and B3 can be simulated with Alt-B1.\n
* Most menus in Noosa can be torn off.  Just invoke the dashed-line\
item at the top of the menu.  The menu will then become a separate window\
that you can leave on the screen until it is no longer needed.\n
* Menus in Noosa can be invoked with the mouse in the usual way or\
using keyboard traversal.  To pop up a menu whose title has the letter\
'x' underlined, type Alt-x.  Once the menu is displayed, items can be\
invoked by typing the letter that is underlined in their name. E.g.\
you can quit Noosa by typing Alt-n q.  The Execution menu also has\
specific keyboard shortcuts.  E.g., Run can be invoked by typing Alt-R.\n
* Much of the appearance of Noosa can be customised using X resources.\
E.g., the colour of highlighting and selection can be adjusted to user\
preference.  See the reference manual for details.\n
"

    set n(help,.,Browsing\ values) "
* The transcript window is the lower of the two text windows in the\
main Noosa window and is used to display output from monitoring and\
Noosa messages.\n
* Within the transcript window, some forms of text are special in that\
they can be \"opened\" by double clicking B1 on them.  Text to which\
this applies will be underlined and, if on a colour machine, will be a\
different colour (default: blue).  When you move the mouse onto\
text of this kind, a description of it will be displayed at the bottom\
of the main Noosa window.\n
The following forms of \"openable\" text are currently supported (where\
nn is a sequence of digits):\n
  1. Coordinates of the form nn,nn or nn,nn-nn,nn\n
  2. Values displayed as type:nn\n
* When a coordinate is opened, the corresponding region of text in the\
input window will be highlighted.  The first form indicates a single\
coordinate while the second indicates a range.\n
* When a value is opened, the behaviour depends on the type of value.\
The following types are currently supported with the described effects\
when the value is opened:\n
 + Node           -- abstract tree node nn will be selected in any abstract
                     tree windows you have open.\n
 + NODEPTR        -- A tree node pointer.  If that node is visible
                     in a tree display it will be selected.  Also,
                     if the tree fragment rooted at that node has not already
                     been displayed in a separate window it will be.\n
 + PTGNode        -- The PTGNode will be passed to PTGOutFile, the output
                     collected and displayed in the transcript window.
                     Note that the output shown may not be the same as will
                     be produced by your processor using this PTGNode.  The
                     difference may occur due to side-effects of functions
                     called during printing, or redefinition of output macros.\n
 * Environment    -- The key-identifier pairs in the environment will be
                     displayed one per line.  If the environment is nested
                     within another, the parent will also be listed.\n
 * DefTableKey    -- The properties of the definition table key will be 
                     displayed one per line with their values and their
                     types.\n
 * tOilType and tOilTypeSet
                  -- These types are used for operator identification.
                     Clicking on an OIL type shows the type name (a
                     definition table key).  Clicking on an OIL type set
                     shows the elements of the set and their associated
                     costs.\n
"

    set n(help,.,Noosa\ menu) "
* Clear transcript deletes the current contents of the transcript window.\n
* The Search item brings up a dialog in which you can specify a search\
string or regular expression, and specify the search direction.  The\
search is performed in whichever of the input or transcript window has\
the focus when the search is initiated.  The Forward search and Backward\
search items are shortcuts to repeat or reverse a search that has already\
been specified in the dialog.  They can also be executed from the keyboard\
using Ctrl-S and Ctrl-R.\n
* The Save and Save As items can be used to save the contents of either the\
input window or the transcript window in the file previously saved to (Save)\
or in a different file (Save As).  Like the search items, these items save\
the window that has the focus when the item is invoked.\n
* Quit causes the monitoring session to be terminated and Noosa to\
exit.
"

    set n(help,.,Execution\ menu) "
* Run causes a new invocation of the program being monitored to be\
created.  Any existing invocation is killed first.  Alt-R is a keyboard\
shortcut for this command.\n
* Cont is used to continue execution of the program being monitored\
after it has stopped for some reason.  Typical reasons are reaching a\
breakpoint or reaching the end of execution either due to normal\
program termination or a runtime signal.  Alt-C is a keyboard shortcut\
for this command.\n
* Kill causes the program being monitored to terminate.  A new invocation\
can be created using the Run command.  Alt-K is a keyboard shortcut for\
this command.
"

    set n(help,.,Examine\ menu) "
* Not all items in this menu will be available for all programs at all\
times.  Some items depend on the execution status of the program;\
others depend on the capabilities of the program.  E.g., the Phrase\
item can't be used on a program that doesn't contain an Eli-generated\
parser.\n
* Token allows examination of the token stream produced by the lexical\
analyzer.  To display the token (if any) recognized at a particular\
input location select the location in the input window using B1 and\
execute Token.  If a range of locations is selected then all the\
tokens (if any) in that range are displayed.  For each token, the\
following is displayed: coordinate range, token name (for non-literals\
only), internal code, intrinsic value, lexeme and length in\
characters.\n
* Phrase allows examination of the phrase structure of the input text\
as determined by the processor.  To display the concrete grammar\
productions used to determine the phrase structure affecting a\
location, just select the location in the input window and execute\
Phrase.\n
* String allows specific entries in the string table to be examined.\
First, select the index of the entry you want to see.  (E.g., it might\
have been displayed by Token as the value of a token.)  Then executing\
String will show you the value that has been stored in the string\
table at that index.\n
* Strings is similar to String except that it displays the entire\
string table.\n
* The input text of a processor can come from a variety of operating\
system files (e.g., due to #include-like directives).  The Describe\
coord item lets you find out the source coordinate of input text.\
Select locations in the input window and execute Describe coord to\
find out where they come from.\n
"

    set n(help,.,Profile\ menu) "
* The Frequency profile item enables event frequency profiling to be\
toggled.  If frequency profiling is on, each time the monitored\
program stops, Noosa will print a summary of the number of events\
received since the beginning of the execution if no stops have\
occurred).  Each event occurrence is labelled with the program modules\
that were active when the event occurred.\n
* Zero frequencies resets the event frequencies collected by Noosa to\
zero.  If further event frequency profiling is done reported frequencies\
will only summarise events from this point on.\n
* The Time profile item toggles time profiling.  If time profiling is\
on, measurements are made of the amount of time spent in each module\
of the program being monitored.  Each time the monitored program\
stops, Noosa will print a summary of the timing information since the\
beginning of the execution.  Timings are grouped according to the\
modules active when each module was entered.  Note that the\
granularity of timing is fairly large so meaningful numbers may not be\
produced.  If you need accurate timings, use a real profiler.\n
* Occasionally it is useful to reset timing information collected by\
Noosa in the middle of program execution.  For example, you might only\
be interested in timings after a particular execution point has been\
reached.  The timings can be reset using the Reset times item.\n
* The Event trace item enables a tracing display of the events\
generated by the program being monitored by Noosa.  When tracing is\
on, the events and their parameters will be displayed in the\
transcript window as they occur.  Initially, tracing is off.\n
* The Set event filter item is used to set the regular expression used\
to filter the events displayed during tracing.  The default regular\
expression is \".*\".  When this item is invoked, a dialog box appears\
in which you can alter the current regular expression.\n
"

    set n(help,.,Windows\ menu) "
* The Trees item controls the display of the tree computed by the processor's\
parser (if attribution is present in the specifications) and any other trees\
computed by the attribution.  By default no trees are displayed.\n
The first three options draw trees in a traditional tree manner with\
the root at the top and children under their parents. The Incremental\
option draws the root at the left and children to the right of their\
parents.  The former style always uses a nice layout but always draws\
the whole the tree (but see below); the latter initially just draws\
the root of the tree but allows nodes to be selectively expanded.\n
The Just Source option causes the source tree built by your\
processor's parser to be displayed.  The Separate Computed option\
will cause each computed tree to be displayed in a separate window as\
soon as they are complete.  This option is most suitable if you have a\
few largish computed trees.  The Source and Computed option shows the\
entire tree (including computed trees joined at the appropriate\
places) so it is more suitable if you have many smaller computed\
trees.  Finally, the Incremental display allows access to the entire\
tree that has been computed so far.\n
* All of the tree windows allow you to determine the input text and\
abstract productions associated with tree nodes (see their Help menus\
for details).  Also, you can select attributes of nodes in order to\
examine their values as execution proceeds.\n
* Note that the abstract tree windows will not be displayed as soon as\
you enable them.  They will appear the next time the program is run to\
the point of creating the relevant tree.\n
* The Handlers item creates a window through which handlers can be placed\
on events that will be generated during execution by the program being\
monitored.  The handler code will then be executed every time the program\
generates an event of the appropriate type.  A list of existing handlers is\
displayed and each of these may be edited, enabled, disabled or deleted.\
For more information, see the Help menu in the Handlers window.\n
* The Files item creates a window through which you can edit or\
create arbitrary files, in particular your specification files.  This\
facility allows you to fix bugs or change the input to your processor\
while you are monitoring.\n
"

    set n(help,treecommon) "
* B1 on a tree node will cause the source text corresponding to that\
node to be highlighted in the source window, and the coordinate range\
of the text and the abstract production applied at that node to be\
displayed.\n
* B3 on a tree symbol pops up a menu listing the attributes of that\
symbol instance and their types.  Each attribute has a pull-right menu\
that contains three (exclusive) items: Show, Show stop, and Ignore.  The\
default is Ignore meaning that the value of the attribute will be\
ignored by Noosa.  If you set the selected item to Show,  the value\
of the attribute will be displayed in the transcript window when you\
it is next evaluated.  If Show stop is selected, the value will be\
displayed and program execution will stop.  It can be continued using\
Continue from the Execution menu.\n
* B3 on a rule name pops up a menu listing the attributes and terminals\
of that rule instance.  Each of these has a pull-right menu that is used\
in the same way as the symbol attribute menus described earlier.\n
* If a symbol (rule) has any attributes for which Show or Show stop is\
is selected the symbol (rule) name will be underlined and highlighted\
on colour displays.\n
"

    set n(help,.lr,General) "
* This form of abstract tree window is used to graphically display\
a tree that is being operated on by the processor.  Alternatively, there\
is the Incremental form of tree display that lets you selectively browse\
the tree rather than displaying it all at once.\n
* In addition to the scrollbars for separate horizontal and vertical\
scrolling, easier scrolling can be obtained by holding B2 down and\
dragging.
$n(help,treecommon)"

    set n(help,.tb,General) "
* This form of abstract tree window is used to browse the abstract\
syntax tree that is operated on by the program being monitored. \
The tree is displayed in a compact textual form where nodes can be\
individually opened and closed.  There are other kinds of tree window\
that display the whole tree in a more traditional fashion.\n
* In addition to the scrollbars for separate horizontal and vertical\
scrolling, easier scrolling can be obtained by holding B2 down and\
dragging.\n
* Subtrees can be selectively displayed using the squares located\
to the left of nodes with children.  A black (white) square indicates\
a subtree that is closed (open).  Closed subtrees can be completely\
expanded by clicking B1 on their square, or expanded one level by\
clicking B2 on their square.  Open subtrees can be completely closed\
by clicking B1 on their square.
$n(help,treecommon)"

    set n(help,.lr,Tree\ menu) "
* In a tree display the Node item can be used to browse the tree.\
First, select a source text location in the input window.  Then invoke\
the Node command.  The tree window will then scroll to display the node\
furthest from the root whose input text contains the selected location.\
Note: more than one node might qualify for selection by this command\
(particularly if computed trees are present).  The leftmost-deepest one\
is chosen.\n
* In all tree displays there are Tree menu commands to save to a file\
the contents of the window as PostScript.  A choice can be made between\
saving the whole tree or just the visible portion.\n
* The Close item causes the tree window to be removed from the screen.\n
"

    set n(help,.tb,Tree\ menu) $n(help,.lr,Tree\ menu)

    set n(help,.h,General) "
* The Handlers window is used to manage handlers for domain-specific\
program events.  As the program executes, any installed handlers will\
be executed when their corresponding events are generated.\n
* The window has six main parts.  Across the top are three listboxes\
that display events, handlers, and event parameters, respectively. \
Below the listboxes is a one-line message area, an entry field for\
the handler name, and a radio box to enable or disable the handler. \
The rest of the window is used for displaying and editing the code\
of the current handler.\n
* The leftmost listbox contains a sorted list of the event types that\
might be generated by the program currently being monitored.  Selecting an\
event type displays a description in the message area.  Also, the\
parameters of that event type (if any) are listed in the rightmost\
listbox.  Selecting the name of a parameter displays a description\
of the parameter in the message area.\n
* The middle listbox contains the names of handlers that are currently\
known to the system.  See the help on the Handlers menu for details about\
creating new handlers or deleting handlers.\n
"

    set n(help,.h,File\ menu) "
* Load allows previously saved handlers to be loaded into the current\
Noosa session.  A dialog box allows you to select which file to load.\n
* Save and Save As allow the current handlers to be saved to a file.\
For Save the name of the most recently loaded file is used (if any).\
Save As always asks for the filename via a file selection dialog.\n
* Close causes the Handlers window to be removed from the screen.\n
"

    set n(help,.h,Handlers\ menu) "
* New causes a new handler to be created and added to the handler list.\
It's name will be whatever is in the handler name field.  The code window\
is left unchanged in case you want to reuse the previous handler code.\n
* Rename changes the name of the currently selected handler (if any)\
to the name in the handler name entry.\n
* Clear clears the handler code window.\n
* Delete completely deletes the currently selected handler.\n
* The code for a handler should be entered into the text window.  Any\
valid Tcl code can be used.  This code can include access to event\
parameters (if any).  For example, if an event has a parameter called\
\"line\" then the value for an instance can be accessed in the handler\
code using \$line.\n
* The handler code executes in a Tcl interpreter that is running in\
the program being monitored.  Hence you can do anything you can\
normally do in Tcl.\n
* Handlers can also execute commands within Noosa.  The most useful\
command of this kind is n_say which displays its arguments in the Noosa\
transcript window. E.g., a handler of the form:\n
         n_say \"line was \$line\\n\"\n
causes the value of the line parameter of each of the relevant events\
to be displayed with a message in the transcript window.\n
* Handlers can also cause program execution to stop when an event is\
generated. If a handler executes 'n_break' then execution will stop\
after all of the handlers for the current event have been executed. \
E.g., the following handler will cause execution to stop when the\
line parameter of the event is equal to 3:\n
         if {\$line == 3} { n_break }\n
* After a handler has caused execution to stop, the program can be\
restarted using the Continue or Run items in the Execution menu.\n
"

    set n(help,.h,Autoloading\ handlers) "
* Sometimes it is useful to be able to automatically load handlers\
at the beginning of a Noosa session.  This can be achieved by placing\
code in the .noosarc file in the current directory.  Alternatively,\
you can place the code in ~/.noosarc if you want the handlers loaded in\
every Noosa session regardless of directory.\n
* To autoload the handlers in file \"useful.hnd\" the following line can\
be used in your .noosarc file:\n
        source useful.hnd\n
useful.hnd should previously have been produced by the Save or Save As items\
in the File menu of the Handlers window.  If useful.hnd does not reside in\
the directory in which Noosa is invoked, a full path name can be used. \
Also, ~ is expanded to your home directory.\n
"

    set n(help,.f,General) "
* A file window can be used to view and/or edit files while you are\
monitoring your processor.  For example, you might use it to fix bugs\
in your specifications or to change the input to your processor for\
the next test run.\n
* Files can be opened or searched using the File menu.  The text window\
displays the text of the file and the bottom line of the window is\
used to display messages.\n
"

    set n(help,.f,File\ menu) "
* The New item clears the window in preparation for creating a new file,\
while the Open item creates a dialog in which you can select the file\
to edit/view.\n
* Once you have loaded a file, the Search item brings up a dialog in\
which you can specify a search string or regular expression, and\
specify the search direction.  The Forward search and Backward search\
items are shortcuts to repeat or reverse a search that has already\
been specified in the dialog.  They can also be executed from the\
keyboard using Ctrl-S and Ctrl-R.\n
* The Save and Save As items can be used to save the contents of the\
window in the file loaded (Save) or in another file (Save As).\n
* The Close item removes the file window from the display, taking care\
to make sure that changes have been saved.\n
"

}


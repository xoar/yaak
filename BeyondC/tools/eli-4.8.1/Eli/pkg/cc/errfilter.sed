# Error formats:
# cc:  "fred.c", line 9: an error message
# gcc: fred.c:9: an error message
# CC:  xx Error(s) detected
# CC:  xx Warning(s) detected
# Remove extra gcc messages,e.g.:
# gcc2.4.5:	/^In file included from .*:$/d
# gcc2.5.7:	/^In file included from .*,$/,/from .*:[0-9][0-9]*:$/d
# cc: SC3.0 15 Dec 1993: identifier redeclared
# cc: SC* license messages for SPARCompiler

/(W) File is empty/d
/Empty compilation - nothing to compile/d
/^In file included from .*:$/d
/^In file included from .*,$/,/from .*:[0-9][0-9]*:$/d
/^Compilation aborted/d
/^compilation terminated/d
/: At top level/d
/: At global scope/d
/: In function /d
/: In member function /d
/: In constructor /d
/: (Each undeclared identifier/d
/: for each function/d
/: acomp failed/d
/recover from earlier errors, terminating/d
/^[0-9\ ]*Error(s) detected/d
/^[0-9\ ]*Warning(s) detected/d
/^\	current : function/d
/^\	previous: function/d
/SPARCompiler/d
/^[ 	]*$/d
s;^cc: ;;
s;^cpp: ;;
s/^\([^:]*\): *\([0-9]*\):/\1 \2 0/
s/^"\([^"]*\)". line \([0-9]*\):/\1 \2 0/
s/^\([^ ]*\) \([^ ]*\) 0\([0-9]*\):/\1 \2 \3/
s;^\.\/;;
/.arning: /{
	s;.arning: ;;w WARN1
	d
}
/(W)/{
	s;(W) ;;w WARN1
	d
}

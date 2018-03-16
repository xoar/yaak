dnl aclocal.m4,v 4.8 1997/08/14 13:48:15 mjung Exp
dnl
dnl Configuration Macros.
dnl 
dnl These macros extend capabilities of Autoconf or replace existing
dnl macros in order to remove some problems.
dnl 
dnl If you call 'autoconf' in another directory than this, specify
dnl this directory with the -l option.

dnl ############################################################################
dnl Macro for Creating a Logfile Message
dnl
dnl Macro-Name:		ELI_MSG_LOG
dnl
dnl Arguments:		$1:	Message to log, without "
dnl
dnl Preconditions:	none
dnl
dnl Postconditions:	message had been appended to logfile
dnl
dnl Comments:		none

AC_DEFUN(ELI_MSG_LOG, 
[
echo "  $1" 1>&AC_FD_CC
])

dnl ############################################################################
dnl Macro for adding a switch to a linker commandline for Solaris:
dnl For each -L option under Solaris a equal -R option is required because
dnl Solaris does not search dynamic libraries in the Pathes that were specified
dnl with -L automatically.
dnl
dnl Macro-Name:		ELI_LIB_SOLARIS
dnl
dnl Arguments:		Name of environment-variable that should be changed.
dnl
dnl Postconditions:	
dnl
dnl Comments:		Library-Path-Specification must be attached to the
dnl			-L-Option without a separating space.

AC_DEFUN(ELI_LIB_SOLARIS,
[
dnl First check, if under Solaris.

if test "`(uname) 2>/dev/null`" = SunOS && uname -r | grep '^5' >/dev/null; then
	eli_lib_solaris=''
	for option in ${$1}; do
		if echo $option | grep '^-L' >/dev/null; then
			eli_lib_solaris_more=`echo $option | sed 's/^-L//'`
			if test "$eli_lib_solaris" = ""; then
				eli_lib_solaris=$eli_lib_solaris_more
			else
				eli_lib_solaris="$eli_lib_solaris:$eli_lib_solaris_more"
			fi
		fi
	done
	if test "$eli_lib_solaris" != ""; then
		$1=${$1}" -R $eli_lib_solaris"
	fi
fi
])
 
dnl ############################################################################
dnl Subroutine to find an X include-directory and an according library-directory.
dnl This is largely taken from AC_PATH_X_DIRECT with minor details replaced.
dnl
dnl Macro-Name:		ELI_PATH_X_ADD
dnl
dnl Arguments:		$1:	Header-file to find.
dnl			$2:	Library to find.
dnl			[$3]:	Further directory to scan.
dnl
dnl Preconditions:	AC_PATH_X
dnl
dnl Postconditions:	$eli_x_add_inc = Path of Include or "NO"
dnl			$eli_x_add_lib = Path of Library or "NO"
dnl
dnl Comments:		First tries to find in the previously determined X Pathes.
dnl			If that fails, some other common configuration pathes
dnl			are scanned.


AC_DEFUN(ELI_PATH_X_ADD, 
[eli_x_add_inc=NO
eli_x_add_lib=NO
if test "$3" != "no"; then
  if test -n "$3"; then
     eli_x_add_inc_opt="$3 $3/include"
  else
     eli_x_add_inc_opt=
  fi

  # Look for the header file $1 in a standard set of common directories.
  for eli_dir in              \
    $eli_x_add_inc_opt        \
    $x_includes               \
    /usr/X11R6/include        \
    /usr/X11R5/include        \
    /usr/X11R4/include        \
                              \
    /usr/include/X11R6        \
    /usr/include/X11R5        \
    /usr/include/X11R4        \
                              \
    /usr/local/X11R6/include  \
    /usr/local/X11R5/include  \
    /usr/local/X11R4/include  \
                              \
    /usr/local/include/X11R6  \
    /usr/local/include/X11R5  \
    /usr/local/include/X11R4  \
                              \
    /usr/X11/include          \
    /usr/include/X11          \
    /usr/local/X11/include    \
    /usr/local/include/X11    \
                              \
    /usr/X386/include         \
    /usr/x386/include         \
    /usr/XFree86/include/X11  \
                              \
    /usr/include              \
    /usr/local/include        \
    /usr/unsupported/include  \
    /usr/athena/include       \
    /usr/local/x11r5/include  \
    /usr/lpp/Xamples/include  \
                              \
    /usr/openwin/include      \
    /usr/openwin/share/include \
    ; \
  do
    if test -r "$eli_dir/$1"; then
      eli_x_add_inc=$eli_dir
      break
    fi
  done

  if test "$eli_x_add_inc" != NO; then
    # Check for library $2.
    
    # First see if replacing the include by lib works.
    for eli_dir in `echo "$eli_x_add_inc" | sed s/include/lib/` \
      /usr/X11R6/lib        \
      /usr/X11R5/lib        \
      /usr/X11R4/lib        \
                            \
      /usr/lib/X11R6        \
      /usr/lib/X11R5        \
      /usr/lib/X11R4        \
                            \
      /usr/local/X11R6/lib  \
      /usr/local/X11R5/lib  \
      /usr/local/X11R4/lib  \
                            \
      /usr/local/lib/X11R6  \
      /usr/local/lib/X11R5  \
      /usr/local/lib/X11R4  \
                            \
      /usr/X11/lib          \
      /usr/lib/X11          \
      /usr/local/X11/lib    \
      /usr/local/lib/X11    \
                            \
      /usr/X386/lib         \
      /usr/x386/lib         \
      /usr/XFree86/lib/X11  \
                            \
      /usr/lib              \
      /usr/local/lib        \
      /usr/unsupported/lib  \
      /usr/athena/lib       \
      /usr/local/x11r5/lib  \
      /usr/lpp/Xamples/lib  \
                            \
      /usr/openwin/lib      \
      /usr/openwin/share/lib \
      /usr/lib/* \
      ; \
    do
      if test -d $eli_dir; then
       if test "`ls $eli_dir/lib$2.* 2> /dev/null`" != ""; then
         eli_x_add_lib=$eli_dir
         break
       fi
      fi
    done
  fi
fi])

dnl ############################################################################
dnl Check for extra libraries that must be used, if X should be used.
dnl Find additional X libraries, magic flags, etc. I included an own 
dnl version here, because the original find libraries SM and ICE on
dnl linux and these libraries are neither needed, nor existant.

AC_DEFUN(AC_PATH_XTRA1,
[AC_REQUIRE([AC_PATH_X])dnl
if test "$no_x" != yes; then
  if test -n "$x_includes"; then
    X_CFLAGS="$X_CFLAGS -I$x_includes"
  fi

  # It would be nice to have a more robust check for the -R ld option than
  # just checking for Solaris.
  # It would also be nice to do this for all -L options, not just this one.
  if test -n "$x_libraries"; then
    X_LIBS="$X_LIBS -L$x_libraries"
    if test "`(uname) 2>/dev/null`" = SunOS &&
      uname -r | grep '^5' >/dev/null; then
      X_LIBS="$X_LIBS -R $x_libraries"
    fi
  fi

  # Check for system-dependent libraries X programs must link with.

  if test "$ISC" = yes; then
    X_EXTRA_LIBS="$X_EXTRA_LIBS -lnsl_s -linet"
  else
    # Martyn.Johnson@cl.cam.ac.uk says this is needed for Ultrix, if the X
    # libraries were built with DECnet support.  And karl@cs.umb.edu says
    # the Alpha needs dnet_stub (dnet does not exist).
    AC_CHECK_LIB(dnet, dnet_ntoa, [X_EXTRA_LIBS="$X_EXTRA_LIBS -ldnet"], [
      AC_CHECK_LIB(dnet_stub, dnet_ntoa, [X_EXTRA_LIBS="$X_EXTRA_LIBS -ldnet_stub"])])

    # msh@cis.ufl.edu says -lnsl (and -lsocket) are needed for his 386/AT,
    # to get the SysV transport functions.
    # Not sure which flavor of 386 UNIX this is, but it seems harmless to
    # check for it.
    AC_CHECK_LIB(nsl, t_accept, [X_EXTRA_LIBS="$X_EXTRA_LIBS -lnsl"])

    # lieder@skyler.mavd.honeywell.com says without -lsocket,
    # socket/setsockopt and other routines are undefined under SCO ODT 2.0.
    # But -lsocket is broken on IRIX, according to simon@lia.di.epfl.ch.
    if test "`(uname) 2>/dev/null`" != IRIX; then
      AC_CHECK_LIB(socket, socket, [X_EXTRA_LIBS="$X_EXTRA_LIBS -lsocket"])
    fi
  fi
fi

AC_SUBST(X_CFLAGS)dnl
AC_SUBST(X_PRE_LIBS)dnl
AC_SUBST(X_LIBS)dnl
AC_SUBST(X_EXTRA_LIBS)dnl
])

dnl ############################################################################
dnl Find XView
dnl
dnl Macro-Name:		ELI_PATH_XVIEW
dnl
dnl Arguments:		none
dnl
dnl Preconditions:	AC_PATH_XTRA1, AC_PATH_X
dnl
dnl Postconditions:	X_CFLAGS modified to include xview-include-path
dnl			X_LIBS modified to include xview-library-path
dnl                     Output variable HAVE_XVIEW replaced by "yes" or "no"
dnl			Shell-Variable eli_no_xview set to "yes" or empty or "disabled"
dnl
dnl Comments:		Uses ELI_PATH_X_ADD to find Xview-Pathes.
dnl                     Includes a commandline-option '--with-XView' that
dnl			can be given a pathname where Xview can be found.

AC_DEFUN(ELI_PATH_XVIEW, [
AC_MSG_CHECKING([for XView])
HAVE_XVIEW=no

if test "$with_XView" != "no"; then
	ELI_PATH_X_ADD(xview/textsw.h,xview, $with_XView)
	
	if test -d "$eli_x_add_inc" && test -d "$eli_x_add_lib"
	then
   		if test "$eli_x_add_inc" != "$x_includes"; then
	      		X_CFLAGS="$X_CFLAGS -I$eli_x_add_inc"

      			# Bug in xview include files on Solaris. 
			# They are using SVR4 instead of __SVR4
      			if test "`(uname) 2>/dev/null`" = SunOS && 
		   		uname -r | grep '^5' >/dev/null; then
        			X_CFLAGS="$X_CFLAGS -DSVR4"
      			fi
   		fi
   		if test "$eli_x_add_lib" != "$x_libraries"; then
      			X_LIBS="$X_LIBS -L$eli_x_add_lib"
      			if test "`(uname) 2>/dev/null`" = SunOS &&
        	   	   uname -r | grep '^5' >/dev/null; then
	        		X_LIBS="$X_LIBS -R $eli_x_add_lib"
      			fi
   		fi
   		HAVE_XVIEW=yes
   		AC_MSG_RESULT([yes])
   		eli_no_xview=
	else
   		AC_MSG_RESULT([no])
   		eli_no_xview=yes
	fi
else
	AC_MSG_RESULT([disabled])
	eli_no_xview=disabled
fi

AC_SUBST(HAVE_XVIEW)dnl
])

dnl ############################################################################
dnl Find Athena Widgets
dnl
dnl Macro-Name:		ELI_LIB_XAW
dnl
dnl Arguments:		none
dnl
dnl Preconditions:	AC_PATH_XTRA1, AC_PATH_X
dnl
dnl Postconditions:	X_CFLAGS modified to include xaw-include-path
dnl			X_LIBS modified to include xaw-library-path
dnl                     Output variable HAVE_XAW replaced by "yes" or "no"
dnl			Shell-Variable eli_no_xaw set to "yes" or empty or "disabled"
dnl
dnl Comments:		Uses ELI_PATH_X_ADD to find Xaw-Pathes.
dnl                     Includes a commandline-option '--with-Xaw' that
dnl			can be given a pathname where Xaw can be found.

AC_DEFUN(ELI_LIB_XAW, [
AC_MSG_CHECKING([if Athena Widgets exist])

HAVE_XAW=no

if test "$with_Xaw" != "no"; then
	ELI_PATH_X_ADD(X11/Xaw/Text.h,Xaw,$with_Xaw)

	if test -d "$eli_x_add_inc" && test -d "$eli_x_add_lib"
	then
   		if test "$eli_x_add_inc" != "$x_includes"; then
      			X_CFLAGS="$X_CFLAGS -I$eli_x_add_inc"
   		fi
   		if test "$eli_x_add_lib" != "$x_libraries"; then
      			X_LIBS="$X_LIBS -L$eli_x_add_lib"
      			if test "`(uname) 2>/dev/null`" = SunOS &&
        		   uname -r | grep '^5' >/dev/null; then
        			X_LIBS="$X_LIBS -R $eli_x_add_lib"
      			fi
   		fi

   		HAVE_XAW=yes
   		AC_MSG_RESULT([yes])
   		eli_no_xaw=

   		eli_save_LDFLAGS="$LDFLAGS"
   		LDFLAGS="$LDFLAGS -L$x_libraries"

   		# SM needs ICE to (dynamically) link under SunOS 4.x (so we have to
   		# check for ICE first), but we must link in the order -lSM -lICE or
   		# we get undefined symbols.  So assume we have SM if we have ICE.
   		# These have to be linked with before -lX11, unlike the other
   		# libraries we check for below, so use a different variable.
   		#  --interran@uluru.Stanford.EDU, kb@cs.umb.edu.
   		AC_CHECK_LIB(ICE, IceConnectionNumber,
     			[X_PRE_LIBS="$X_PRE_LIBS -lSM -lICE"])
   		LDFLAGS="$eli_save_LDFLAGS"
	else
   		AC_MSG_RESULT([no])
   		eli_no_xaw=yes
	fi
else
	AC_MSG_RESULT([disabled])
	eli_no_xaw=disabled	
fi

AC_SUBST(HAVE_XAW)dnl
])

dnl ############################################################################
dnl Macro-Name:		ELI_ERR_CHECK
dnl
dnl Arguments:		none
dnl
dnl Preconditions:	none
dnl
dnl Postconditions:     eli_no_errlib = yes, if strerror() and sys_errlist[] not found
dnl			set #define USE_ERRLIST 0, if the strerror() function is found
dnl                                             1, if the sys_errlist[] array is found
dnl 			set #define ERR_PROTO 1, if strerror()/sys_errlist[] is prototyped in string.h or errno.h 
dnl

AC_DEFUN(ELI_ERR_CHECK,
[
eli_no_errlib=no

func_strerr=
func_syserrlist=
AC_CHECK_FUNC(strerror, func_strerr=yes,
  [AC_CHECK_FUNC(sys_errlist, func_syserrlist=yes, eli_no_errlib=yes )])

if test "$eli_no_errlib" != yes; then
  AC_DEFINE(ERR_PROTO, 1)
  if test "$func_strerr" = yes; then
    AC_DEFINE(USE_ERRLIST, 0)
  else
    AC_DEFINE(USE_ERRLIST, 1)
  fi
fi
])

dnl ############################################################################
dnl Macro-Name:		ELI_PATH_CURSES
dnl
dnl Arguments:		none
dnl
dnl Preconditions:	none
dnl
dnl Postconditions:	Replaces CFLAGS_CURSES by Options to give to the C-Compiler to
dnl			use curses header files.
dnl			Replaces LIB_CURSES by Options to give to the Linker to 
dnl			use a curses-library.


AC_DEFUN(ELI_PATH_CURSES,
[
LIB_CURSES=
CFLAGS_CURSES=
eli_no_curses=

# Since curses often uses termcap or terminfo, try to find it first.
AC_CHECK_LIB(termcap, tgetent, LIB_CURSES='-ltermcap')

# If it is not found, we expect that termcap functions have been built in the
# ncurses or curses-library.


AC_MSG_CHECKING([if curses is available])

if test "$with_curses" != "no"; then
# Build List of directories to search in

# Default Directories.
	eli_curses_lib_dirs="/usr/lib /usr/local/lib /usr/lib64"
	if test "$LD_LIBRARY_PATH" != ''
	then eli_curses_lib_dirs="$eli_curses_lib_dirs `echo $LD_LIBRARY_PATH | tr ':=' '  '`"
	fi

# But begin with directory specified by user in Option.
	eli_curses_lib_dirs="$with_curses/lib $eli_curses_lib_dirs"

# At the end, append some more directories
	eli_curses_lib_dirs="$eli_curses_lib_dirs $HOME/lib /usr/lib/ncurses /usr/lib/curses /usr/lib/* /lib/* /usr/local/lib/curses /usr/local/lib/ncurses /usr/ccs/lib"
	if test "$prefix" != 'NONE' && test "$prefix" != '/usr/local'
	then eli_curses_lib_dirs="$eli_curses_lib_dirs $prefix/lib"
	fi

# Now search in all these directories.
	eli_curses_lib_dir=
	eli_ncurses_lib_dir=

	for eli_dir in $eli_curses_lib_dirs; do
		if test -d $eli_dir; then
			if test "`ls $eli_dir/libcurses.* 2> /dev/null`" != ""; then
				ELI_MSG_LOG([curses library found in $eli_curses_lib_dir])
				eli_curses_lib_dir=$eli_dir
			fi 
			if test "`ls $eli_dir/libncurses.* 2> /dev/null`" != ""; then
				ELI_MSG_LOG([ncurses library found in $eli_ncurses_lib_dir])
				eli_ncurses_lib_dir=$eli_dir
			fi
			if test "$eli_curses_lib_dir" != "" && test "$eli_ncurses_lib_dir" != ""
			then
				break
			fi
		fi
	done


	if test "$eli_ncurses_lib_dir" = "" && test "$eli_curses_lib_dir" = ""; then
		AC_MSG_RESULT([curses library not found])
		eli_no_curses=yes
	else
# Build List of directories to search for include
		eli_curses_inc_dirs="/usr/include /usr/local/include"
		if test "$prefix" != 'NONE' && test "$prefix" != '/usr/local'
		then eli_curses_inc_dirs="$prefix/include $eli_curses_inc_dirs"
		fi
# But begin with directory specified by user in Option.
		eli_curses_inc_dirs="$with_curses/include $eli_curses_inc_dirs"

# At the end, append some more directories
		eli_curses_inc_dirs="$eli_curses_inc_dirs $HOME/include /usr/include/curses /usr/local/include/curses /usr/include/ncurses /usr/local/include/ncurses"
# Now search in all these directories.
	        eli_curses_inc_dir=
	        eli_ncurses_inc_dir=
	        for eli_dir in $eli_curses_inc_dirs; do
			if test -d $eli_dir; then
				if test -r $eli_dir/curses.h; then
					ELI_MSG_LOG([curses include found in $eli_curses_inc_dir])
					eli_curses_inc_dir=$eli_dir
				fi 
				if test -r $eli_dir/ncurses.h; then
					ELI_MSG_LOG([curses library found in $eli_ncurses_inc_dir])
					eli_ncurses_inc_dir=$eli_dir
				fi
				if (test "$eli_curses_lib_dir" != "" && test "$eli_curses_inc_dir" != "") \
                                 || (test "$eli_ncurses_lib_dir" != "" && test "$eli_ncurses_inc_dir" != "");
				then
					break
				fi
			fi
		done
	fi

	if test "$eli_no_curses" != "yes"; then
		if test "$eli_ncurses_lib_dir" != "" && test "$eli_ncurses_inc_dir" != ""; then
			LIB_CURSES="-lncurses $LIB_CURSES"
			CFLAGS_CURSES="-I$eli_ncurses_inc_dir"
			AC_MSG_RESULT([ncurses:  library $eli_ncurses_lib_dir  include $eli_ncurses_inc_dir])
			AC_DEFINE(USE_NCURSES, 1)
		else
			if test "$eli_curses_lib_dir" != "" && test "$eli_curses_inc_dir" != ""; then
				LIB_CURSES="-lcurses $LIB_CURSES"
				CFLAGS_CURSES="-I$eli_curses_inc_dir"
				AC_MSG_RESULT([library $eli_curses_lib_dir  include $eli_curses_inc_dir])
				AC_DEFINE(USE_NCURSES, 0)
			else
				if test "$eli_curses_inc_dir" = "" && test "$eli_ncurses_inc_dir" = ""; then
					AC_MSG_RESULT([no include file found])
				else
					AC_MSG_RESULT([wrong include file found])
				fi
				eli_no_curses=yes
			fi
		fi
	fi
fi

AC_SUBST(LIB_CURSES)
AC_SUBST(CFLAGS_CURSES)
])



dnl ############################################################################
dnl Macro-Name:		ELI_PATH_TCLTK
dnl
dnl Arguments:		$1: 	Possible Options for Tcl/Tk Version.
dnl				Format: Spaces-separated List of Versions like:
dnl				7.5:4.1 7.6:4.2
dnl
dnl Preconditions:	none
dnl
dnl Postconditions:	Replaces CFLAGS_TCL by Options to give to the C-Compiler to
dnl			use Tcl/Tk.
dnl			Replaces LIBS_TCL by Options to give to the Linker to 
dnl			use Tcl/Tk-Library.
dnl
dnl			Method:	(1) Try to find tclConfig.sh and tkConfig.sh in
dnl				    a number of common directories including 
dnl				    a directory that can be specified in option
dnl				    --with-tcltk.
dnl				(2) Sources these two files.
dnl				(3) Checks that the version in one of the 
dnl				    acceptable versions.
dnl				(4) Does some consistency-checks.
dnl				(5) Searches include-files in ../include

AC_DEFUN(ELI_PATH_TCLTK,
[
CFLAGS_TCL=
LIBS_TCL=
eli_no_tcltk=

AC_MSG_CHECKING([if Tcl/Tk is available])

if test "$with_tcltk" != "no"; then
# Build List of directories to search Configuration Scripts 'tclConfig.sh' and
# 'tkConfig.sh' in.

# Default Directories.
	eli_tcltk_dirs="$HOME /usr /usr/local"
	if test "$prefix" != '/usr/local' && test "$prefix" != "NONE"
	then eli_tcltk_dirs="$prefix $eli_tcltk_dirs"
	fi

# Tcl-Version-Number Directories
	for eli_tcltk_ver in $1; do
		eli_tcl_ver=`echo $eli_tcltk_ver | sed 's,:.*$,,'`
		eli_tk_ver=`echo $eli_tcltk_ver | sed 's,^.*:,,'`
		eli_tcltk_dirs="$eli_tcltk_dirs $HOME/tcl$eli_tcl_ver $HOME/tcl-$eli_tcl_ver /usr/tcl$eli_tcl_ver /usr/lib/tcl$eli_tcl_ver /usr/tcl-$eli_tcl_ver /usr/local/tcl$eli_tcl_ver /usr/local/tcl-$eli_tcl_ver $HOME/tk$eli_tk_ver $HOME/tk-$eli_tk_ver /usr/tk$eli_tk_ver /usr/lib/tk$eli_tk_ver /usr/tk-$eli_tk_ver /usr/local/tk$eli_tk_ver /usr/local/tk-$eli_tk_ver"
	done

# But begin with directory specified by user in Option.
	if test "$with_tcltk" != "yes"
        then eli_tcltk_dirs="$with_tcltk $eli_tcltk_dirs"
        fi

# At the end, append some more directories
	eli_tcltk_dirs="$eli_tcltk_dirs $HOME/tcl /usr/lib64 /usr/tcl /usr/local/tcl"

# Now search in all these directories, if the file tclConfig.sh and tkConfig.sh
# can be found there or in a lib subdirectory.

	eli_tcl_dir=
	eli_tk_dir=
	for eli_dir in $eli_tcltk_dirs; do
		if test -d $eli_dir; then
			ELI_MSG_LOG([looking for Tcl/Tk library in $eli_dir])
			if test -r $eli_dir/tclConfig.sh; then
		   		eli_tcl_dir=$eli_dir
		   		eli_tcl_base=$eli_dir
			else
		   	        if test -r $eli_dir/lib/tclConfig.sh; then
					eli_tcl_dir=$eli_dir/lib
					eli_tcl_base=$eli_dir
		                fi
			fi
			if test -r $eli_dir/tkConfig.sh; then
			        eli_tk_dir=$eli_dir
			        eli_tk_base=$eli_dir
			else
			        if test -r $eli_dir/lib/tkConfig.sh; then
					eli_tk_dir=$eli_dir/lib
					eli_tk_base=$eli_dir
 			        fi
			fi
			if test "$eli_tcl_dir" != "" && test "$eli_tk_dir" != ""
			then
				break
			fi
		fi
	done

	if test "$eli_tcl_dir" = ""; then
		AC_MSG_RESULT([Tcl library not found])
		eli_no_tcltk=yes
	fi
	if test "$eli_tk_dir" = ""; then
		AC_MSG_RESULT([Tk library not found])
		eli_no_tcltk=yes
	fi

	if test "$eli_no_tcltk" != "yes"; then
# Both Configuration files could be found.		
# Source them to extract necessary information
		ELI_MSG_LOG([TCL Configuration found in $eli_tcl_dir])
		ELI_MSG_LOG([TK Configuration found in $eli_tk_dir])
		
		. $eli_tcl_dir/tclConfig.sh
		. $eli_tk_dir/tkConfig.sh

# Check for Tcl/Tk Version.

		: ${TCL_VERSION=none}					
		: ${TK_VERSION=none}
		if (echo "$1" | grep "$TCL_VERSION:$TK_VERSION") >/dev/null; then
			:
		else
			AC_MSG_RESULT([wrong version found])
			eli_no_tcltk=yes
		fi
	fi

	if test "$eli_no_tcltk" != "yes"; then
# Tk Configuration also seems to be good. Assemble the Library Line.
# It should consist of everything specified in 
# $TCL_LIB_SPEC $TCL_LIBS $TK_LIB_SPEC $TK_LIBS.
# Since TK is configured to use tcl, everything specified in 
# $TCL_LIBS is also mentioned in $TK_LIBS.
		LIBS_TCL="$TK_LIB_SPEC $TCL_LIB_SPEC $TK_LIBS"
		ELI_LIB_SOLARIS(LIBS_TCL)

# Now search for the include-files. We will check the pathes
		eli_tcl_dirs="$eli_tcl_dir/include $eli_tcl_dir/include/tcl $eli_tcl_dir/include/tcl$TCL_VERSION $eli_tcl_dir/include/tcl-$TCL_VERSION /usr/local/include/tcl$TCL_VERSION /usr/local/include/tk$TK_VERSION /usr/local/include /usr/include/tcl$TCL_VERSION /usr/include/tk$TK_VERSION /usr/include"
                if test "$eli_tcl_dir" != "$eli_tcl_base"
                then
        		eli_tcl_dirs="$eli_tcl_base/include $eli_tcl_dirs"
                fi

		eli_tcl_incldir=
		for eli_tcl_includes in $eli_tcl_dirs; do
			ELI_MSG_LOG([looking for tcl.h in $eli_tcl_includes])
			if test -r $eli_tcl_includes/tcl.h; then
				eli_tcl_incldir=$eli_tcl_includes
				break;
			fi
		done

		if test "$eli_tcl_incldir" = ""; then
			AC_MSG_RESULT([Tcl include files not found])
			eli_no_tcltk=yes
		else
			ELI_MSG_LOG([tcl.h found in $eli_tcl_incldir])
		fi

		eli_tk_dirs="$eli_tcl_incldir $eli_tk_dir/include $eli_tk_dir/include/tk $eli_tk_dir/include/tk$TK_VERSION $eli_tk_dir/include/tk-$TK_VERSION /usr/local/include/tcl$TCL_VERSION /usr/local/include/tk$TK_VERSION /usr/local/include /usr/include/tcl$TCL_VERSION /usr/include/tk$TK_VERSION /usr/include"
                if test "$eli_tk_dir" != "$eli_tk_base"
                then
        		eli_tk_dirs="$eli_tk_base/include $eli_tk_dirs"
                fi
		
		eli_tk_incldir=
		for eli_tk_includes in $eli_tk_dirs; do
			ELI_MSG_LOG([looking for tk.h in $eli_tk_includes])
			if test -r $eli_tk_includes/tk.h; then
				eli_tk_incldir=$eli_tk_includes
				break;
			fi
		done

		if test "$eli_tk_incldir" = ""; then
			AC_MSG_RESULT([Tk include files not found])
			eli_no_tcltk=yes
		else
			ELI_MSG_LOG([tk.h found in $eli_tk_incldir])
		fi
	fi

	if test "$eli_no_tcltk" != "yes"; then
		if test "$eli_tcl_incldir" = "$eli_tk_incldir"; then
			CFLAGS_TCL="-I$eli_tcl_incldir"
		else	CFLAGS_TCL="-I$eli_tcl_incldir -I$eli_tk_incldir"
		fi
dnl Allow use of interp->errorLine until we no longer support Tcl versions
dnl earlier than 8.6.  At that time, replace interp->errorLine by
dnl Tcl_GetErrorLine(interp)
		CFLAGS_TCL=$CFLAGS_TCL' -DUSE_INTERP_ERRORLINE'
		AC_MSG_RESULT([found Tcl$TCL_VERSION, Tk$TK_VERSION])
	fi
else
	AC_MSG_RESULT([disabled])
	eli_no_tcltk=yes
fi

AC_SUBST(CFLAGS_TCL)dnl
AC_SUBST(LIBS_TCL)dnl
])

dnl ###########################################################################
dnl Macro for finding the word count program (wc).
dnl
dnl Macro-Name:		ELI_PROG_WC
dnl
dnl Arguments:		none
dnl
dnl Preconditions:	User can specify a processor in environment variable
dnl			WCPROG.
dnl
dnl Postconditions:	substitutes WCPROG

AC_DEFUN(ELI_PROG_WC,
[
AC_PATH_PROG(WCPROG, "wc", "junk")
if test "$WCPROG" = "junk"; then
	AC_MSG_ERROR([wc was not found in your path])
fi
if test "`echo 'foo and bar' | $WCPROG -l`" -ne 1; then
	AC_MSG_ERROR([wc doesn't work as expected])
fi
AC_SUBST(WCPROG)dnl
])

dnl ############################################################################
dnl Macro for checking, if hard links are usable.
dnl Please note that the Andrew File System is known to fail.
dnl
dnl Macro-Name:		ELI_CHECK_LN
dnl
dnl Arguments:		none
dnl
dnl Preconditions:	none
dnl
dnl Postconditions:	Substitutes LINK with 'ln' or 'cp'.
dnl
dnl Comments:		none

AC_DEFUN(ELI_CHECK_LN, 
[
AC_CHECK_PROG(LINK, ln, ln, cp)

if test "$LINK" = "ln"; then
   AC_MSG_CHECKING([whether ln works])
   rm -f conftest.a
   echo GNUS AND GNATS > conftest.a
   rm -f conftest.b
   if $LINK conftest.a conftest.b 2>/dev/null ; then
      rm -f conftest.a
      if test -s conftest.b; then
        rm -f conftest.*
        mkdir conftest.a
        echo GNUS AND GNATS > conftest.b
        if $LINK conftest.b conftest.a/conftest.b 2>/dev/null; then
           rm -f conftest.b
           if test -s conftest.a/conftest.b; then
              AC_MSG_RESULT([yes])
           else
              AC_MSG_RESULT([no])
	      ELI_MSG_LOG([ln does not work accros directories])
              LINK=cp
           fi
        else
           AC_MSG_RESULT([no])
	   ELI_MSG_LOG([executing ln across directories yields error])
           LINK=cp
        fi
        rm -f conftest.a/*
        rmdir conftest.a
      else
        AC_MSG_RESULT([no])
        ELI_MSG_LOG([ln executes, but does nothing])
        LINK=cp
      fi
      rm -f conftest.*
   else
      AC_MSG_RESULT([no])
      ELI_MSG_LOG([executing ln yields error])
      LINK=cp
   fi
fi
])

dnl ############################################################################
dnl Macro for checking, if symbolic links are usable.
dnl Some non-Unix environments (e.g. cygnus for Windows NT) support symlinks only
dnl partially.
dnl
dnl Macro-Name:		ELI_CHECK_SYMLINK
dnl
dnl Arguments:		none
dnl
dnl Postconditions:	Sets eli_no_symlink to yes, if symlinks are unusable.
dnl
dnl Comments:		Performs the following checks.
dnl			- Symlink to nonexisting file. Writing into the symlink
dnl			  must create the file.
dnl			- Symlinks a directory. Writing into the directory.

AC_DEFUN(ELI_CHECK_SYMLINK, 
[
AC_MSG_CHECKING(whether ln -s works)
rm -f conftest.*

# First check. See if symlink to nonexisting file works.
eli_no_symlink=

if ln -s conftest.a conftest.b 2>/dev/null; then
   echo GNUS > conftest.b
   if test -s conftest.a; then    # First test passed.
      :
   else
      AC_MSG_RESULT([no])
      ELI_MSG_LOG([symlink to nonexistent file did not work.])
      eli_no_symlink=yes
   fi
else
   AC_MSG_RESULT([no])
   ELI_MSG_LOG([symlink to nonexistent file yields error.])
   eli_no_symlink=yes
fi
rm -f conftest.*

if test "$eli_no_symlink" = ""; then
# Second, try to symlink a directory.

   mkdir conftest.a
   if ln -s conftest.a conftest.b 2>/dev/null; then
      echo GNUS > conftest.b/gnu
      if test -s conftest.a/gnu; then
         :
      else
         AC_MSG_RESULT([no])
	 ELI_MSG_LOG([symlinking a directory did not work])
         eli_no_symlink=yes
      fi
   else
      AC_MSG_RESULT([no])
      ELI_MSG_LOG([symlinking a directory yields error.])
      eli_no_symlink=yes
   fi
   rm -rf conftest.a
   rm -rf conftest.b
fi

if test "$eli_no_symlink" = ""; then
	AC_MSG_RESULT([yes])
fi
])

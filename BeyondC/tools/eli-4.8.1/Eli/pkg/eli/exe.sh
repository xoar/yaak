#!/bin/sh
# $Id: exe.sh,v 2.12 2007/07/24 16:29:21 profw Exp $
# Copyright 1995, The Regents of the University of Colorado

# EXEC (exe.sh) (.) (:objects :dir_of :vir_dir)
#     (:libsflags)
#     (:library_flags)
#     (:dotafiles :dir_of :vir_dir)
#     (:dotafiles :labels)
#     (+debug) (+prof) (+cc) (+cc_flags)
#   NEEDS (:objects) (:level_9_specs :extract=:a)
#   => (:exe);

ODIN_RUNDIR=`pwd`
PKG=$1;shift; ODIN_objects=$1;shift;
ODIN_libsflags=$1;shift; ODIN_library_flags=$1;shift;
ODIN_e34=$1;shift; ODIN_e35=$1;shift;
ODIN_debug=$1;shift; ODIN_prof=$1;shift;
ODIN_cc=$1;shift; ODIN_flags=$1;shift;

SED=$ODINCACHE/PKGS/skeleton/sed.exe

if test -s $ODIN_e34
then
	for f in `cat $ODIN_e35`
	do libs="$libs "$ODIN_e34"/$f"
	done
fi

libs="$libs "`cat $ODIN_libsflags`
libs="$libs "`cat $ODIN_library_flags`

libpath=`echo $libs | $SED -e '
    s/.*/>&</
    s/-L\([^ <]*\)/<\1>/g
    s/>[^<]*</:/g
    s/:\(.*\):/\1/
    s/^://'`
if test "$libpath" != ''
then 
  if test "$LD_LIBRARY_PATH" != ''
  then LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$libpath
  else LD_LIBRARY_PATH=$libpath
  fi
  export LD_LIBRARY_PATH
fi

flags=""
if test "$ODIN_debug" != ""; then flags="$flags $ODIN_CC_DEBUGF"; fi
if test "$ODIN_prof" != "";  then flags="$flags -pg";  fi
if test "$ODIN_flags" != ""; then flags="$flags `cat $ODIN_flags`"; fi
flags="$flags $ODIN_CC_FLAGS"

if test "$ODIN_cc" != ""; then ELI_CC=$ODIN_cc; fi
CCPROG=${ELI_CC-$ODIN_CC}

cd $ODIN_objects

${CCPROG} -o $ODIN_RUNDIR/exe $flags *.o $libs 1>$ODIN_RUNDIR/ERROR 2>&1
compstat=$?

cd $ODIN_RUNDIR

if test -x exe.exe; then mv exe.exe mvtmp; mv mvtmp exe; fi

if test -s ERROR
then
  if grep '^[^:]*: In function' ERROR > /dev/null && \
     grep '^/'                  ERROR > /dev/null
  then
    $SED -e 's;/bin/ld: ;;
        /^[^:]*: In function/d
        /^[^:]*: ld returned/d
        /^[^.]*\.c\.c\.o:/s;^[^.]*\.c\.c\.o:;;
        s;^\([^:]*\):\([^:]*\):;\1 \2 0;' ERROR \
      | $ODINCACHE/PKGS/skeleton/cat-n.exe \
      | sort -k 2,2 -k 3n,4 -k 1n,1 \
      | $ODINCACHE/PKGS/skeleton/line_err.exe \
      > ERRORS
  else
    $SED -e 's;/bin/ld: ;;
	s/^:/ /
        /^ld: fatal:/d
        /^[^:]*: ld returned/d
            s;^;. 0 0 ;' ERROR >ERRORS
  fi
  rm ERROR
elif test $compstat -ne 0
then echo ". 0 0 Loader failed with status $compstat" > ERRORS
else :
fi

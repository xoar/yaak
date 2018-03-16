#!/bin/sh
# $Id: so.sh,v 2.1 2013/03/31 00:52:32 profw Exp $
# Copyright 2012, The Regents of the University of Colorado

# EXEC (so.sh) (:objects :dir_of :vir_dir)
#     (+debug) (+cc) (+cc_flags)
#   NEEDS (:objects)
#   => (:so);

ODIN_RUNDIR=`pwd`
ODIN_objects=$1;shift;
ODIN_debug=$1;shift; ODIN_cc=$1;shift; ODIN_flags=$1;shift;

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
if test "$ODIN_flags" != ""; then flags="$flags `cat $ODIN_flags`"; fi
flags="$flags $ODIN_CC_FLAGS"

if test "$ODIN_cc" != ""; then ELI_CC=$ODIN_cc; fi
CCPROG=${ELI_CC-$ODIN_CC}

cd $ODIN_objects

${CCPROG} -shared -fPIC -o $ODIN_RUNDIR/so $flags *.o 1>$ODIN_RUNDIR/ERROR 2>&1
compstat=$?

cd $ODIN_RUNDIR

if test $compstat -ne 0
then echo ". 0 0 Loader failed with status $compstat" > ERRORS
else :
fi

#!/bin/sh

ODIN_exe=$1;shift; ODIN_data=$1;shift; ODIN_flags=$1;shift;

flags=""
if [ "$ODIN_flags" != "" ] ; then flags="$flags `cat $ODIN_flags`"; fi

if [ "$ODIN_data" = "" ] ; then
   echo "At least one +prof_data parameter must be specified." >ERRORS;
   exit 0; fi
data=`cat $ODIN_data`

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}gprof $flags `basename $ODIN_exe` $data; fi

gprof $flags $ODIN_exe $data >profile 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo 'prof failed' >>ERRORS; }

exit 0

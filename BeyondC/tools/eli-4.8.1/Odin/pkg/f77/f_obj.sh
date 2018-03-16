#!/bin/sh

ODIN_f=$1;shift; ODIN_debug=$1;shift; ODIN_prof=$1;shift;
ODIN_home=$1;shift; ODIN_f77=$1;shift; ODIN_flags=$1;shift;

if [ "$ODIN_home" != "" ] ; then
   PATH="$ODIN_home:$PATH"; export PATH; fi

compiler=f77
if [ "$ODIN_f77" != "" ] ; then compiler=$ODIN_f77; fi

flags=""
if [ "$ODIN_flags" != "" ] ; then flags="`cat $ODIN_flags` $flags"; fi
if [ "$ODIN_debug" != "" ] ; then flags="-g $flags"; fi
if [ "$ODIN_prof" != "" ] ; then flags="-pg $flags"; fi

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}$compiler $flags -c `basename $ODIN_f`; fi

$compiler $flags -c $ODIN_f 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo 'f77 failed' >>ERRORS; }

input=`basename $ODIN_f .f`
if [ -f $input.o ] ; then mv $input.o o; fi

exit 0

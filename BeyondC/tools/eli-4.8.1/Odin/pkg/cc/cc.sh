#!/bin/sh

ODIN_c=$1;shift; ODIN_dir=$1;shift; ODIN_incsp=$1;shift;
ODIN_home=$1;shift; ODIN_gnu=$1;shift; ODIN_debug=$1;shift;
ODIN_prof=$1;shift; ODIN_optimize=$1;shift; ODIN_define=$1;shift;
ODIN_cc=$1;shift; ODIN_flags=$1;shift;

if [ "$ODIN_CC_HOME" != "" ] ; then
   PATH="$ODIN_CC_HOME:$PATH"; export PATH; fi
if [ "$ODIN_home" != "" ] ; then
   PATH="$ODIN_home:$PATH"; export PATH; fi

compiler=$ODIN_CC
if [ "$ODIN_cc" != "" ] ; then compiler=$ODIN_cc; fi
if [ "$ODIN_gnu" != "" ] ; then compiler='gcc'; fi

flags=""
if [ "$ODIN_debug" != "" ] ; then flags="$flags $ODIN_CC_DEBUGF"; fi
if [ "$ODIN_prof" != "" ] ; then flags="$flags -pg"; fi
if [ "$ODIN_optimize" != "" ] ; then flags="$flags -O$ODIN_optimize"; fi
if [ "$ODIN_define" != "" ] ; then
   for def in `cat $ODIN_define`; do
      flags="$flags -D$def"; done; fi
flags="$flags -I$ODIN_dir"
if [ "$ODIN_incsp" != "" ] ; then
   for sp in `cat $ODIN_incsp`; do
      flags="$flags -I$sp"; done; fi
if [ "$ODIN_flags" != "" ] ; then flags="$flags `cat $ODIN_flags`"; fi
flags="$flags $ODIN_CC_FLAGS"

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}$compiler -c $flags `basename $ODIN_c`; fi

$compiler -c $flags $ODIN_c 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo "$compiler failed" >>ERRORS; }

input=`basename $ODIN_c .c`
if [ -f $input.o ] ; then mv $input.o o; fi

exit 0

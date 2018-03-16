#!/bin/sh

ODIN_cpp=$1;shift; ODIN_FILE=$1;shift; ODIN_dir=$1;shift;
ODIN_incsp=$1;shift; ODIN_define=$1;shift;

flags=""
if [ "$ODIN_define" != "" ] ; then
   for def in `cat $ODIN_define`; do
      flags="$flags -D$def"; done; fi
flags="$flags -I$ODIN_dir"
if [ "$ODIN_incsp" != "" ] ; then
   for sp in `cat $ODIN_incsp`; do
      flags="$flags -I$sp"; done; fi
flags="$flags $ODIN_CPP_FLAGS"

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}$ODIN_CPP $flags `basename $ODIN_FILE`; fi

$ODIN_CPP $flags $ODIN_FILE >$ODIN_cpp 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo "$ODIN_CPP failed" >>ERRORS; }

exit 0

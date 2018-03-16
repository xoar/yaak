#!/bin/sh

ODIN_c=$1;shift; ODIN_dir=$1;shift; ODIN_incsp=$1;shift;
ODIN_define=$1;shift; ODIN_flags=$1;shift; ODIN_ignore=$1;shift;

flags="$ODIN_LINT_PASS1_FLAG"
if [ "$ODIN_define" != "" ] ; then
   for def in `cat $ODIN_define`; do
      flags="$flags -D$def"; done; fi
flags="$flags -I$ODIN_dir"
if [ "$ODIN_incsp" != "" ] ; then
   for sp in `cat $ODIN_incsp`; do
      flags="$flags -I$sp"; done; fi
if [ "$ODIN_flags" != "" ] ; then
   flags="$flags `cat $ODIN_flags`"; fi
flags="$flags $ODIN_LINT_FLAGS"

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}lint $flags `basename $ODIN_c`; fi

lint $flags $ODIN_c >lint1.log 2>ERRORS \
 || cat lint1.log >>ERRORS

input=`basename $ODIN_c .c`
if [ -r $input.ln ] ; then mv $input.ln ln; fi

egrep -v 'possible pointer alignment' lint1.log >tmp; mv tmp lint1.log
if [ "$ODIN_ignore" != "" ] ; then
   egrep -v -f $ODIN_ignore lint1.log >tmp; mv tmp lint1.log; fi

exit 0

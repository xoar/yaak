#!/bin/sh

ODIN_lnlist=$1;shift; ODIN_loglist=$1;shift; ODIN_lnstubs=$1;shift;
ODIN_ln=$1;shift; ODIN_flags=$1;shift; ODIN_ignore=$1;shift;
ODIN_gignore=$1;shift

if [ "$ODIN_flags" != "" ] ; then lintflags=`cat $ODIN_flags`; fi
lintflags="$lintflags $ODIN_LINT_FLAGS"

inputs="`cat $ODIN_lnlist`"
if [ "$ODIN_lnstubs" != "" ] ; then inputs="$inputs `cat $ODIN_lnstubs`"; fi
if [ "$ODIN_ln" != "" ] ; then inputs="$inputs `cat $ODIN_ln`"; fi

cat /dev/null `cat $ODIN_loglist` >lint

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}lint $lintflags $inputs; fi

lint $lintflags $inputs >>lint 2>ERRORS \
 || echo 'lint failed' >>ERRORS

if [ "$ODIN_ignore" != "" ] ; then
   egrep -v -f $ODIN_ignore lint >tmp; mv tmp lint; fi

if [ "$ODIN_gignore" != "" ] ; then
   egrep -v -f $ODIN_gignore lint >tmp; mv tmp lint; fi

exit 0

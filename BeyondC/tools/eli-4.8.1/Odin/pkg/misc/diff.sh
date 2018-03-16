#!/bin/sh

ODIN_FILE=$1;shift; ODIN_other=$1;shift;

if [ "$ODIN_other" = "" ] ; then
   echo 'No comparison file specified' >>ERRORS
   exit 0; fi

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}diff `basename $ODIN_FILE` `basename $ODIN_other`; fi

diff $ODIN_FILE $ODIN_other 2>diff
cat diff >>ERRORS

exit 0

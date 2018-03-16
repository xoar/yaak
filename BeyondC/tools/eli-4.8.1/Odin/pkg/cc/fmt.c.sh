#!/bin/sh

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}indent `basename $1`; fi

# indent is brain-damaged. always returns non-zero status
(indent $1 fmt) 2>>ERRORS

exit 0

#!/bin/sh

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}tbl `basename $1`; fi

tbl <$1 >tbl 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo 'tbl failed' >>ERRORS; }

exit 0

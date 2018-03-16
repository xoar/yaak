#!/bin/sh

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}eqn `basename $2`; fi

eqn <$2 >$1 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo 'eqn failed' >ERRORS; }

exit 0

#!/bin/sh

ln -s $1 o
objs=`ls o/*`

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}ar qcv out.a $objs; fi

ar qcv a $objs >STDOUT 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo 'ar failed' >>ERRORS; }

if [ "$ODIN_RANLIB" != "" ] ; then
   if [ "$ODINVERBOSE" != "" ] ; then
      echo ${ODINRBSHOST}$ODIN_RANLIB out.a; fi
   $ODIN_RANLIB a >>STDOUT 2>>WARNINGS \
    || { mv WARNINGS ERRORS; echo 'ranlib failed' >>ERRORS; }; fi

cat STDOUT
exit 0

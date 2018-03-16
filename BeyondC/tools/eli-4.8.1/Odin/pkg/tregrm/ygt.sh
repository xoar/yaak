#!/bin/sh

ODIN_ygi=$1;shift; ODIN_yaccid=$1;shift; ODIN_tregrm=$1;shift

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}`basename $ODIN_tregrm` `basename $ODIN_ygi`; fi

$ODIN_tregrm <$ODIN_ygi >ygi.log 2>WARNINGS \
 || { mv WARNINGS ERRORS
      echo 'tregrm.exe failed' >>ERRORS; }

if [ "$ODIN_yaccid" != "" ] ; then
   yy=$ODIN_yaccid
   YY=`echo $yy | tr '[a-z]' '[A-Z]'`; fi

if [ -f LEX_TAB ] ; then
   if [ "$ODIN_yaccid" != "" ] ; then
      sed -e "s/yy/$yy/g" -e "s/YY/$YY/g" <LEX_TAB >tmp
      mv tmp LEX_TAB; fi
   mv LEX_TAB tok.h; fi
if [ -f GRM_TAB ] ; then mv GRM_TAB y; fi
if [ -f NOD_TAB ] ; then
   if [ "$ODIN_yaccid" != "" ] ; then
      sed -e "s/yy/$yy/g" -e "s/YY/$YY/g" <NOD_TAB >tmp
      mv tmp NOD_TAB; fi
   mv NOD_TAB nod.h; fi

exit 0

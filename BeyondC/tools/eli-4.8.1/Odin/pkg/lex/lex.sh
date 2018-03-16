#!/bin/sh

ODIN_l=$1;shift; ODIN_yaccid=$1;shift;

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}lex `basename $ODIN_l`; fi

lex $ODIN_l 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo 'lex failed' >>ERRORS; }

if [ -f lex.yy.c ] ; then
   sed -e 's/"stdio.h"/<stdio.h>/' <lex.yy.c >c
#  mv c tmp.c; sed '/^# line /d; /yypvt/d; /yyerrlab/d' <tmp.c >c
   if [ "$ODIN_yaccid" != "" ] ; then
      yy=$ODIN_yaccid
      YY=`echo $yy | tr '[a-z]' '[A-Z]'`
      sed -e "s/yy/$yy/g" -e "s/YY/$YY/g" <c >tmp.c
      mv tmp.c c; fi; fi

exit 0

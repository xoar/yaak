#!/bin/sh

ODIN_y=$1;shift; ODIN_yaccid=$1;shift; ODIN_conflictok=$1;shift;
ODIN_sys5=$1;shift; ODIN_gnu=$1;shift; ODIN_yacc=$1;shift; ODIN_flags=$1;shift;

compiler=$ODIN_YACC
if [ "$ODIN_gnu" != "" ] ; then compiler='bison'; fi
if [ "$ODIN_yacc" != "" ] ; then compiler=$ODIN_yacc; fi

flags=$ODIN_YACC_FLAGS
if [ "$ODIN_flags" != "" ] ; then flags="`cat $ODIN_flags` $flags"; fi
if [ "$ODIN_gnu" != "" ] ; then flags="$flags -y"; fi

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}$compiler $flags `basename $ODIN_y`; fi

$compiler $flags $ODIN_y 2>WARNINGS

if [ $? != 0 ] ; then
   mv WARNINGS ERRORS
   echo 'yacc failed' >>ERRORS
elif [ "$ODIN_conflictok" = "" ] ; then
   egrep 'conflicts' WARNINGS >ERRORS; fi

if [ -f y.tab.c ] ; then
   if [ "$ODIN_yaccid" != "" ] ; then
      yy=$ODIN_yaccid
      YY=`echo $yy | tr '[a-z]' '[A-Z]'`
      sed -e "s/yy/$yy/g" -e "s/YY/$YY/g" <y.tab.c >tmp.c
      mv tmp.c y.tab.c; fi
   if [ "$ODIN_sys5" != "" -o "$ODIN_SYS5" != "" ] ; then
      sed -e '/^extern char \*malloc()/s/char/void/' <y.tab.c >tmp.c
      mv tmp.c y.tab.c; fi
#   sed '/yypvt/d; /yyerrlab/d' <y.tab.c >c
   mv y.tab.c c; fi

if [ -f y.tab.h ] ; then mv y.tab.h h; fi
if [ -f y.output ] ; then mv y.output yacc.log; fi

exit 0

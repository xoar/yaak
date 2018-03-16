#!/bin/sh

ODIN_o=$1;shift; ODIN_lib=$1;shift; ODIN_home=$1;shift;
ODIN_gnu=$1;shift; ODIN_purify=$1;shift; ODIN_debug=$1;shift;
ODIN_prof=$1;shift; ODIN_eprof=$1;shift; ODIN_cc=$1;shift; ODIN_flags=$1;shift;

if [ "$ODIN_CC_HOME" != "" ] ; then
   PATH="$ODIN_CC_HOME:$PATH"; export PATH; fi
if [ "$ODIN_home" != "" ] ; then
   PATH="$ODIN_home:$PATH"; export PATH; fi

compiler=$ODIN_CC
if [ "$ODIN_cc" != "" ] ; then compiler=$ODIN_cc; fi
if [ "$ODIN_gnu" != "" ] ; then compiler='gcc'; fi
if [ "$ODIN_purify" != "" ] ; then
   compiler="purify `cat $ODIN_purify` $compiler"; fi
   
flags=""
if [ "$ODIN_debug" != "" ] ; then flags="$flags $ODIN_CC_DEBUGF"; fi
if [ "$ODIN_prof" != "" ] ; then flags="$flags -pg"; fi
if [ "$ODIN_flags" != "" ] ; then flags="$flags `cat $ODIN_flags`"; fi
flags="$flags $ODIN_CC_FLAGS"

libs=""
if [ "$ODIN_lib" != "" ] ; then libs=`cat $ODIN_lib`; fi

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}$compiler $flags $objs $libs; fi

exe=`pwd`/exe
(cd $ODIN_o; $compiler $flags * $libs -o $exe) >MESSAGES 2>WARNINGS \
 || { cat MESSAGES WARNINGS >ERRORS; rm MESSAGES WARNINGS;
      echo "$compiler failed" >>ERRORS; }
if [ -f MESSAGES ] ; then cat MESSAGES; fi

if [ "$ODIN_purify" != "" ] ; then
   cd $ODIN_o
   for file in *; do
      if [ ! -h $file ] ; then
         rm -f $file; fi; done; fi

if [ -x exe.exe ] ; then mv exe.exe mvtmp; mv mvtmp exe; fi

exit 0

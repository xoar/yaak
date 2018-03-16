#!/bin/sh

ODIN_o=$1;shift; ODIN_lib=$1;shift;
ODIN_home=$1;shift; ODIN_gnu=$1;shift; ODIN_purify=$1;shift;
ODIN_atac=$1;shift; ODIN_debug=$1;shift; ODIN_prof=$1;shift;
ODIN_eprof=$1;shift; ODIN_flags=$1;shift;

export PATH
if [ "$ODIN_CC_HOME" != "" ] ; then PATH="$ODIN_CC_HOME:$PATH"; fi
if [ "$ODIN_home" != "" ] ; then PATH="$ODIN_home:$PATH"; fi

compiler=$ODIN_CC
if [ "$ODIN_gnu" != "" ] ; then compiler='gcc'; fi
if [ "$ODIN_atac" != "" ] ; then
   PATH=$ATACHOME/bin:$PATH
   ATAC_CC=$compiler; export ATAC_CC; compiler=atacCC; fi
if [ "$ODIN_purify" != "" ] ; then
   compiler="purify `cat $ODIN_purify` $compiler"; fi
   
flags=""
if [ "$ODIN_debug" != "" ] ; then flags="$flags $ODIN_CC_DEBUGF"; fi
if [ "$ODIN_prof" != "" ] ; then flags="$flags -pg"; fi
if [ "$ODIN_flags" != "" ] ; then flags="$flags `cat $ODIN_flags`"; fi
flags="$flags $ODIN_CC_FLAGS"

ln -s $ODIN_o o
objs=`ls o/*`

libs=""
if [ "$ODIN_lib" != "" ] ; then libs=`cat $ODIN_lib`; fi

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}$compiler $flags $objs $libs; fi

$compiler $flags $objs $libs -o exe >MESSAGES 2>WARNINGS \
 || { cat MESSAGES WARNINGS >ERRORS; rm MESSAGES WARNINGS;
      echo "$compiler failed" >>ERRORS; }
if [ -f MESSAGES ] ; then cat MESSAGES; fi

if [ "ODIN_purify" != "" ] ; then
   for file in `ls o`; do
      if [ ! -h o/$file ] ; then
         rm -f o/$file; fi; done; fi

exit 0

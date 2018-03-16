#!/bin/sh

ODIN_o=$1;shift; ODIN_lib=$1;shift; ODIN_ptr=$1;shift;
ODIN_define=$1;shift; ODIN_incsp=$1;shift; ODIN_gnu=$1;shift;
ODIN_purify=$1;shift; ODIN_debug=$1;shift; ODIN_prof=$1;shift;
ODIN_eprof=$1;shift; ODIN_cxx=$1;shift; ODIN_flags=$1;shift;

if [ "$ODIN_CXX_HOME" != "" ] ; then
   PATH="$ODIN_CXX_HOME:$PATH"; export PATH; fi

if [ "$ODIN_CXX_LD_LIBRARY_PATH" != "" ] ; then
   LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ODIN_CXX_LD_LIBRARY_PATH;
   export LD_LIBRARY_PATH; fi

compiler=$ODIN_CXX
if [ "$ODIN_cxx" != "" ] ; then compiler=$ODIN_cxx; fi
if [ "$ODIN_gnu" != "" ] ; then compiler='g++'; fi
if [ "$ODIN_purify" != "" ] ; then compiler="purify `cat $ODIN_purify` $compiler"; fi

flags=""
if [ "$ODIN_CXX_PTR" = "1" -a "$ODIN_gnu" = "" ] ; then
   flags="$flags -ptr$ODIN_ptr"; fi
if [ "$ODIN_define" != "" ] ; then
   for def in `cat $ODIN_define`; do
      flags="$flags -D$def"; done; fi
if [ "$ODIN_incsp" != "" ] ; then
   for sp in `cat $ODIN_incsp`; do
      flags="$flags -I$sp"; done; fi
if [ "$ODIN_debug" != "" ] ; then flags="$flags $ODIN_CXX_LD_DEBUGF"; fi
if [ "$ODIN_prof" != "" ] ; then flags="$flags -pg"; fi
if [ "$ODIN_flags" != "" ] ; then flags="$flags `cat $ODIN_flags`"; fi
flags="$flags $ODIN_CXX_FLAGS"

ln -s $ODIN_o o
objs=`ls o/*`

libs=""
if [ "$ODIN_lib" != "" ] ; then libs=`cat $ODIN_lib`; fi

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}$compiler $flags $objs $libs; fi

exe=`pwd`/exe
(cd $ODIN_o; $compiler $flags * $libs -o $exe) >MESSAGES 2>WARNINGS || {
   cat MESSAGES WARNINGS >ERRORS; rm MESSAGES WARNINGS;
   if [ ! -s ERRORS ] ; then 
      echo "$compiler failed" >>ERRORS; fi;
   if [ "$ODIN_CXX_IGNORE_ERR" != "" ] ; then
      if egrep -s -e "$ODIN_CXX_IGNORE_ERR" ERRORS; then
	 mv ERRORS WARNINGS; fi; fi; }
if [ -f MESSAGES ] ; then cat MESSAGES; rm MESSAGES; fi

if [ "$ODIN_purify" != "" ] ; then
   cd $ODIN_o
   for file in *; do
      if [ ! -h $file ] ; then
         rm -f $file; fi; done; fi

if [ -x exe.exe ] ; then mv exe.exe exe; fi

exit 0

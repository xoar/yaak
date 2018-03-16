#! /bin/sh

ODIN_source=$1;shift; ODIN_ptr=$1;shift;
ODIN_dir=$1;shift; ODIN_incsp=$1;shift; ODIN_gnu=$1;shift;
ODIN_debug=$1;shift; ODIN_prof=$1;shift; ODIN_optimize=$1;shift;
ODIN_define=$1;shift; ODIN_cxx=$1;shift; ODIN_flags=$1;shift;
ODIN_abort=$1;shift;

if [ "$ODIN_CXX_HOME" != "" ] ; then
   PATH="$ODIN_CXX_HOME:$PATH"; export PATH; fi

if [ "$ODIN_CXX_LD_LIBRARY_PATH" != "" ] ; then
   LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ODIN_CXX_LD_LIBRARY_PATH;
   export LD_LIBRARY_PATH; fi

compiler=$ODIN_CXX
if [ "$ODIN_cxx" != "" ] ; then compiler=$ODIN_cxx; fi
if [ "$ODIN_gnu" != "" ] ; then compiler='g++'; fi

flags=""
if [ "$ODIN_CXX_PTR" = "1" -a "$ODIN_gnu" = "" ] ; then
   flags="$flags -ptr$ODIN_ptr"; fi
if [ "$ODIN_debug" != "" ] ; then flags="$flags $ODIN_CXX_DEBUGF"; fi
if [ "$ODIN_prof" != "" ] ; then flags="$flags -pg"; fi
if [ "$ODIN_optimize" != "" ] ; then flags="$flags -O$ODIN_optimize"; fi
if [ "$ODIN_define" != "" ] ; then
   for def in `cat $ODIN_define`; do
      flags="$flags -D$def"; done; fi
flags="$flags -I$ODIN_dir"
if [ "$ODIN_incsp" != "" ] ; then
   for sp in `cat $ODIN_incsp`; do
      flags="$flags -I$sp"; done; fi
if [ "$ODIN_flags" != "" ] ; then flags="$flags `cat $ODIN_flags`"; fi
flags="$flags $ODIN_CXX_FLAGS"

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}$compiler -c $flags `basename $ODIN_source`; fi

$compiler -c $flags $ODIN_source 2>MSGS \
 || {  if egrep -s -f $ODIN_abort MSGS; then
         cat MSGS
         exit 1; fi
       mv MSGS ERRORS  
       echo "$compiler failed." >>ERRORS
       exit 0; }

egrep 'arning' MSGS | egrep -v '& before array or function: ignored' >>WARNINGS
egrep -v 'arning' MSGS

input=`expr $ODIN_source : '.*/\([^/]*\)[.][^./]*'`
if [ -f $input.o ] ; then mv $input.o o; fi

exit 0

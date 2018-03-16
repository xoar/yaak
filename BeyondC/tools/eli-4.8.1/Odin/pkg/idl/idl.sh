#!/bin/sh

ODIN_idl=$1;shift; ODIN_dir=$1;shift; ODIN_incsp=$1;shift; ODIN_flags=$1;shift;

if [ "$ODIN_IDL_HOME" != "" ] ; then
   PATH="$ODIN_IDL_HOME:$PATH"; export PATH; fi

flags="-I$ODIN_dir"
if [ "$ODIN_incsp" != "" ] ; then
   for sp in `cat $ODIN_incsp`; do
      flags="$flags -I$sp"; done; fi
if [ "$ODIN_flags" != "" ] ; then flags="$flags `cat $ODIN_flags`"; fi
flags="$flags $ODIN_IDL_FLAGS"

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}$ODIN_IDL $flags `basename $ODIN_idl`; fi

$ODIN_IDL $flags $ODIN_idl 2>WARNINGS \
 || { mv WARNINGS ERRORS; echo "$ODIN_IDL failed" >>ERRORS; }

input=`basename $ODIN_idl .idl`
if [ -f ${input}_cstub.c ] ; then mv ${input}_cstub.c cstub.c; fi
if [ -f ${input}_sstub.c ] ; then mv ${input}_sstub.c sstub.c; fi
if [ -f ${input}C.C ] ; then mv ${input}C.C client.C; fi
if [ -f ${input}E.C ] ; then mv ${input}E.C epv.C; fi

mkdir idl_h_dir
mv *.[hH] idl_h_dir

exit 0

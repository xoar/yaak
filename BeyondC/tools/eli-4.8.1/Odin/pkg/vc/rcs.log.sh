#!/bin/sh

ODIN_v=$1;shift;
ODIN_date=$1;shift; ODIN_rev=$1;shift; ODIN_state=$1;shift; ODIN_who=$1;shift

file=`basename $ODIN_v`
case $file in *,v);; *) 
   file=$file,v;; esac
ln -s $ODIN_v $file

flag=""
if [ "$ODIN_date" != "" ] ; then flag="$flag -d`cat $ODIN_date`"; fi
if [ "$ODIN_rev" != "" ] ; then flag="$flag -r`cat $ODIN_rev`"; fi
if [ "$ODIN_state" != "" ] ; then flag="$flag -s`cat $ODIN_state`"; fi
if [ "$ODIN_who" != "" ] ; then flag="$flag -w`cat $ODIN_who`"; fi

if [ "$ODINVERBOSE" != "" ] ; then
   echo ${ODINRBSHOST}rlog $flag `basename $file`; fi

rlog $flag $file >rcs 2>ERRORS
status=$?
if [ $status != 0 -a $status != 1 ] ; then
   cat ERRORS; echo 'rlog failed'; exit 1; fi

exit 0

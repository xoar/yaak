#!/bin/sh

ODIN_OBJECT=$1;shift; ODIN_dest=$1;shift;

if [ "$ODIN_dest" = "" ] ; then
   echo ":copy must have a +copy_dest parameter" >ERRORS
   exit 0; fi

if [ -d $ODIN_OBJECT ] ; then
   if [ "$ODINVERBOSE" != "" ] ; then
      echo "${ODINRBSHOST}** Copying up-to-date value into $ODIN_dest"; fi
   if [ -d $ODIN_dest ] ; then
      object=`basename $ODIN_dest`
      ln -s $ODIN_OBJECT $object
      ODIN_OBJECT=$object
      ODIN_dest=`expr $ODIN_dest : '\(.*\)/[^/]*'`; fi
   cp -RL $ODIN_OBJECT $ODIN_dest || exit 1
   chmod -f -R +w $ODIN_dest
   exit 0; fi

if [ -d $ODIN_dest ] ; then
   echo "Directory already exists at destination of copy: $ODIN_dest" >ERRORS
   exit 0; fi

cmp -s $ODIN_OBJECT $ODIN_dest && {
   if [ "$ODINVERBOSE" != "" ] ; then
      echo "${ODINRBSHOST}** Verified up-to-date: $ODIN_dest"; fi
   exit 0; }

rm -f $ODIN_dest
cp $ODIN_OBJECT $ODIN_dest || exit 1
if [ "$ODINVERBOSE" != "" ] ; then
   echo "${ODINRBSHOST}** Copied up-to-date value into: $ODIN_dest"; fi

exit 0

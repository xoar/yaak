#!/bin/sh

ODIN_FILE=$1;shift; ODIN_default=$1;shift;

if [ "$ODIN_default" = "" ] ; then
   echo 'No default file specified' >>ERRORS
   exit 0; fi

if [ -f $ODIN_FILE ] ; then
   echo $ODIN_FILE >boot_name
else
   echo $ODIN_default >boot_name; fi

exit 0

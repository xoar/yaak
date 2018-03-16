#!/bin/sh

rshcmd=rsh
if [ `uname` = HP-UX ] ; then rshcmd=remsh; fi

cmdargs="$2/PKGS/odin/rbs.exe $3 $4"

ct=${CLEARTOOLHOME-/usr/atria/bin}
if [ -f $ct/cleartool ] ; then
   view=`$ct/cleartool pwv -s`
   if [ "$view" != '** NONE **' ] ; then
      cmdargs="$2/PKGS/odin/rbs-local.sh $ct $view $2 $3 $4"
      fi; fi

if [ "$ODINVERBOSE" != "" ] ; then
   echo $rshcmd $1 -n $cmdargs; fi

$rshcmd $1 -n $cmdargs






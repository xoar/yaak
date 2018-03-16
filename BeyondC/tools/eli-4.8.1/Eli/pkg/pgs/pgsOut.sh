#!/bin/sh
# $Id: pgsOut.sh,v 2.1 2009/05/04 15:31:13 profw Exp $
# Copyright 2009, The Regents of the University of Colorado

# EXEC (pgsOut.sh) (:pgsGen :name) (:pgsInfo :name) (+parser)
#   => (:pgsOut) (:pgsData);

ODIN_pgs=$1;shift; ODIN_info=$1;shift; ODIN_parser=$1;shift;

if test '' = "$ODIN_parser" -o 'pgs' = "$ODIN_parser"
then
  cp $ODIN_pgs pgsOut
  cp $ODIN_info pgsData
else
  cp /dev/null pgsOut
  cp /dev/null pgsData
fi

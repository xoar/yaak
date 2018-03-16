#!/bin/sh
# $Id: colaOut.sh,v 2.1 2009/05/04 15:30:26 profw Exp $
# Copyright 2009, The Regents of the University of Colorado

# EXEC (colaOut.sh) (:colaBe :name) (:colaInfo :name) (+parser)
#   => (:colaOut) (:colaData);

ODIN_cola=$1;shift; ODIN_info=$1;shift; ODIN_parser=$1;shift;

if test 'cola' = "$ODIN_parser"
then
  cp $ODIN_cola colaOut
  cp $ODIN_info colaData
else
  cp /dev/null colaOut
  cp /dev/null colaData
fi

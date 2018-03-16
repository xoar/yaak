#!/bin/sh
# $Id: burgOut.sh,v 1.1 1997/12/01 22:00:11 waite Exp $
# Copyright 1997, The Regents of the University of Colorado

#EXEC (burgOut.sh) (.) (:burg.cmpd :names) (:burgGen :name)
#  => (:burgOut);

PKG=$1;shift; ODIN_e154=$1;shift; ODIN_e155=$1;shift;

if test -s "$ODIN_e154"
then cp $ODIN_e155 burgOut
else cp /dev/null burgOut 
fi

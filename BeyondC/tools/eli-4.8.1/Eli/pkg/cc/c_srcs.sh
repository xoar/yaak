#!/bin/sh
# $Id: c_srcs.sh,v 2.3 2007/04/01 19:45:11 profw Exp $
# Copyright 1998, The Regents of the University of Colorado

# EXEC (c_srcs.sh) (:c) (+incls) => (:c_srcs);

ODIN_c=$1;shift; ODIN_incls=$1;shift;

echo $ODIN_c | cat - $ODIN_incls > c_srcs

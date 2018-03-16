#!/bin/sh
# $Id: cxx_srcs.sh,v 2.1 2007/04/01 19:49:05 profw Exp $
# Copyright 1998, The Regents of the University of Colorado

# EXEC (cxx_srcs.sh) (:cxx) (+incls) => (:cxx_srcs);

ODIN_c=$1;shift; ODIN_incls=$1;shift;

echo $ODIN_c | cat - $ODIN_incls > cxx_srcs

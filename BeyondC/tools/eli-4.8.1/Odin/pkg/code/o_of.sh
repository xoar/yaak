#!/bin/sh

ODIN_src=$1;shift; ODIN_o=$1;shift;

$ODIN_PASTE $ODIN_src $ODIN_o \
 | sed 's,^.*/\([^/]*\)[.][^.]*[ 	]\(.*\)$,%\1.o == \2,' >o_of 2>ERRORS

exit 0

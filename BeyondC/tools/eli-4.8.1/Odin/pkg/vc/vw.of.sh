#!/bin/sh

$ODIN_PASTE $1 $2 | sed 's,^\(.\),/\1,' | sed 's,^.*/\([^/]*\)[ 	]\(.*\)$,%\1 == \2,' >vw.of 2>ERRORS

exit 0

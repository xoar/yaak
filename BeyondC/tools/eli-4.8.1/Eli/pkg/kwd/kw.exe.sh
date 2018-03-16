#!/bin/sh
# $Id: kw.exe.sh,v 1.2 2002/05/08 15:00:58 waite Exp $
# Copyright 1992, The Regents of the University of Colorado

# EXEC (kw.exe.sh) (.) (:backend_data) (:flex_binary) (:accept_binary)
#      (:lastdfa_binary)
#   NEEDS (kwd.c) (match.c) (match.h)
#   => (:kw.exe);

PKG=$1;shift; ODIN_backend_data=$1;shift; ODIN_flex_binary=$1;shift;
ODIN_accept_binary=$1;shift; ODIN_lastdfa_binary=$1;shift;

$ODINCACHE/PKGS/gla/gla_be.exe $ODIN_backend_data $ODIN_lastdfa_binary \
	$ODIN_accept_binary $ODIN_flex_binary 1>/dev/null 2>ERROR
if test -s ERROR
then
	# default error handling, for now
	cp ERROR ERRORS
	exit 0
fi

CCPROG=${ELI_CC-$ODIN_CC}

$CCPROG -o kw.exe -I. -I"$PKG" \
		-I"$ODINCACHE/PKGS/Input" \
		-I"$ODINCACHE/PKGS/Adt" \
		-I"$ODINCACHE/PKGS/gla" \
		-I"$ODINCACHE/PKGS/eli" \
		$PKG/kwd.c \
		$PKG/match.c \
		$ODINCACHE/PKGS/Input/source.c \
		$ODINCACHE/PKGS/Input/err.c \
		$ODINCACHE/PKGS/Adt/obstack.c \
		$ODINCACHE/PKGS/Adt/obsave.c \
		$ODINCACHE/PKGS/Adt/csm.c \
		$ODINCACHE/PKGS/gla/tabsize.c \
		$ODINCACHE/PKGS/Scan/auxEOF.c \
		$ODINCACHE/PKGS/Scan/auxNUL.c \
		$ODINCACHE/PKGS/Scan/dflteot.c \
	>/dev/null 2>ERROR

if test -s ERROR
then
	# Error formats:
	# cc:  "fred.c", line 9: an error message
	# gcc: fred.c:9: an error message
	# Remove extra gcc messages
	$ODINCACHE/PKGS/skeleton/sed.exe -e '/^In file included from /d
		/: At top level/d
		/: In function /d
		/: (Each undeclared identifier/d
		/: for each function/d
		/^[^:]*:$/d
		s/^\([^:]*\): *\([0-9]*\):/\1 \2 0/
		s/^"\([^"]*\)". line \([0-9]*\):/\1 \2 0/
		s;^\.\/;;
		/arning/{
			s;.arning: ;;w WARNINGS
			d
		}' ERROR >ERRORS
else :
fi

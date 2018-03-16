#!/bin/sh
# $Id: err_filter.sh,v 2.7 2006/06/29 10:49:02 pfahler Exp $
# Copyright 1991, The Regents of the University of Colorado

# This file is part of the Eli translator construction system.

# Eli is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2, or (at your option) any later
# version.

# Eli is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.

# You should have received a copy of the GNU General Public License along
# with Eli; see the file COPYING.  If not, write to the Free Software
# Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

ODIN_resolved_errors=$1;shift;
touch filtered
touch errfiles

if test ! -s "$ODIN_resolved_errors"; then exit 0; fi

SED=$ODINCACHE/PKGS/skeleton/sed.exe

$SED -e '/^$/d
		/Summary of[ a-z]* error messages for/d
		/^Unknown input macro/s/^\(.*\) in <\(.*\)>/\2 0 0 \1/
		/does not exist/s/^[^<]*<\([^>]*\)>.*/. 0 0 \1 missing/
#		/^--- <.*> .* ---$/s/^--- <\(.*\)> \(.*\) ---$/. 0 0 \1 \2/
		/^---.*:\.cmd_ref.*---$/{
			s/^.*\(<.*\) :\.cmd_ref>.*/\1>/
			h
			d
		}
		/^---.*---$/d
		/syntax error at token/d
		/^Syntax error in macro/{
			G
			s/^\(.*\) <\(..*\)>.*<\(.*\)>/\3 0 0 \1 <\2>/
		}
		/^"[^ "]*", line [0-9]*:[0-9]* /{
			s/^"\([^ "]*\)", line \([0-9]*\):\([0-9]*\)/\1 \2 \3/
		}
		/^[^./]/{
			s/^/. 0 0 /
			w FRONT
			d
		}
		/^[^ ][^ ]* [0-9][0-9]* [0-9][0-9]* /!{
			s/^/. 0 0 /
			w FRONT
			d
		}' "$ODIN_resolved_errors" \
	| "$ODINCACHE/PKGS/skeleton/cat-n.exe" \
	| sort -k 2,2 -k 3n,3 -k 4n,4 -k 1n,1 \
	| $SED -e 's/^[0-9 	]*//' \
	| uniq \
	| tee FMSG \
	| $SED -e 's/ .*//' \
	| uniq \
	| $SED -e 's/\([+=]\)/\\\1/g' \
	> errfiles

cat FRONT FMSG >> filtered

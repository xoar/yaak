#!/bin/sh
# $Id: colaLalr.sh,v 2.4 1997/08/29 09:43:29 mjung Exp $
# 
# (C) Copyright 1997 University of Paderborn
# 
# /* This file is part of the Eli translator construction system.
# 
# Eli is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2, or (at your option) any later
# version.
# 
# Eli is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
# 
# You should have received a copy of the GNU General Public License along
# with Eli; see the file COPYING.  If not, write to the Free Software
# Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
# 

ODIN_colaCmrIn=$1;shift; ODIN_colaCmrBuIn=$1;shift; ODIN_colaLalrOpt=$1;shift;


# EXEC (colaLalr.sh) (.) (:colaCmrIn) (:colaCmrBuIn) (:colaLalrOpt)
#   => (:colaCmr) (:colaAbs) (:colaErrTerms) (:colaInfo);
# 	:colaCmr 'The COMAR datastructure of the abstract parser' => :FILE;
# 	:colaAbs 'The state table of the abstract parser' => :FILE;
# 	:colaErrTerms 'C code for producing (... expected)-messages' => :FILE;
#	:colaInfo 'result of LALR(1)-analysis, conflict states/all states'? => :FILE;

if test -s "$ODIN_colaCmrBuIn"
then
    cp "$ODIN_colaCmrBuIn" bnf
else
    cp "$ODIN_colaCmrIn" bnf
fi

$ODINCACHE/PKGS/cola/colaAbsprs.exe $ODIN_colaLalrOpt bnf 1> ERRORS 2>&1
mv bnf.abs1 colaCmr
mv bnf.abs2 colaAbs
mv State2Terms.c colaErrTerms

if test -s core
then
   echo '".", line 0:0 DEADLY: COLA analyzer failed' >> ERRORS
fi

if test -s ERRORS
then
	cp ERRORS colaInfo
else
    if test -s bnf.info
    then
	mv bnf.info bnf.info.save

	if test -s "$ODIN_colaCmrBuIn"
	then
	    rm bnf
	    cp "$ODIN_colaCmrIn" bnf
	    "$ODINCACHE/PKGS/cola/colaAbsprs.exe" \
		"$ODIN_colaLalrOpt" bnf 1> ERRORS 2>&1
	    if test -s bnf.info
	    then
		mv bnf.info.save colaInfo
	    else
		echo ". 0 0 You have bottomup constraints in your attribute grammar that cause your concrete syntax to not be parsable."
	    fi
	else
	    mv bnf.info.save colaInfo
	fi
    else
	echo "Grammar is LALR(1)." > colaInfo
    fi
fi

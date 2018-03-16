#!/bin/sh
# $Id: lit_out.sh,v 2.4 1999/06/24 21:06:40 waite Exp $
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

# EXEC (lit_out.sh) (:delit.cmpd :names) (:lex_code.cmpd :names) (:lit_gen :name)
#   => (:lit_out);

ODIN_HAVELIT=$1;shift; ODIN_LEXCODE=$1;shift; ODIN_LITGEN=$1;shift;

if test -s "$ODIN_HAVELIT"
then cp "$ODIN_LITGEN" lit_out
else cp "$ODIN_LEXCODE" lit_out
fi

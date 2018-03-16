#!/bin/sh
# $Id: kwd_out.sh,v 2.3 1998/08/10 16:59:14 waite Exp $
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

# EXEC (kwd_out.sh) (:lex_code.cmpd :ls) (:LIST :extract=:kwd :names)
#      (:kwd_gen :name)
#   NEEDS (:lex_code.cmpd)
#   => (:kwd_out);

ODIN_lex_code_cmpd=$1;shift; ODIN_kwdfiles=$1;shift; ODIN_kwd_gen_name=$1;shift;
ODIN_RUNDIR=`pwd`;

if test -s $ODIN_kwdfiles && test -s $ODIN_lex_code_cmpd
then cp $ODIN_kwd_gen_name kwd_out
else cp /dev/null kwd_out
fi

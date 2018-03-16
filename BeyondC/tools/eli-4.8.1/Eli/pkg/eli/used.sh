#!/bin/sh
# $Id: used.sh,v 2.8 2002/05/08 15:00:52 waite Exp $
# Copyright 1992, The Regents of the University of Colorado

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

# EXEC (used.sh) (loaded.exe) (main.reqsym)
#     (:all_c
#       +incl=(:includes) :map=(:c +incls=(:incl.all) :lookup=:c_srcs)
#       :union :map=:o :ls)
#     (:all_c :names)
#     (:genlib :extract=:c
#       +incl=(:includes) :map=(:c +incls=(:incl.all) :lookup=:c_srcs)
#       :union :map=:o :ls)
#     (:genlib :extract=:c :names)
#     (:LIST :extract=:reqsym :cat)
#     (:genlib :extract=:reqsym :cat)
#     (+debug) (+prof) (+nomain) (+monitor)
#     (+cc)
#   NEEDS
#     (:all_c
#       +incl=(:includes) :map=(:c +incls=(:incl.all) :lookup=:c_srcs)
#       :union :map=:o)
#     (:genlib :extract=:c
#       +incl=(:includes) :map=(:c +incls=(:incl.all) :lookup=:c_srcs)
#       :union :map=:o)
#   => (:used_sources) (:used_objects);

ODIN_loaded=$1;shift; ODIN_main_reqsym=$1;shift;
ODIN_user_o_files=$1;shift; ODIN_user_c_files=$1;shift;
ODIN_library_o_files=$1;shift; ODIN_library_c_files=$1;shift;
ODIN_required_symbols=$1;shift; ODIN_gen_required_symbols=$1;shift;
ODIN_debug=$1;shift; ODIN_prof=$1;shift;
ODIN_nomain=$1;shift; ODIN_monitor=$1;shift;
ODIN_cc=$1;shift;

if test -s "$ODIN_required_symbols"
then reqsym=$ODIN_required_symbols
else reqsym=/dev/null
fi

if test -s "$ODIN_gen_required_symbols"
then greqsym=$ODIN_gen_required_symbols
else greqsym=/dev/null
fi

echo '#include <stdio.h>
void _f_o_o_()
{' > symbols.c

if test '' != "$ODIN_nomain"
then
    cat $reqsym $greqsym >> symbols.c
    nomain="-n"
else
    cat $ODIN_main_reqsym $reqsym $greqsym >> symbols.c
    nomain=""
fi

echo '}' >> symbols.c

if test "$ODIN_cc" != ""; then ELI_CC=$ODIN_cc; fi
CCPROG=${ELI_CC-$ODIN_CC}
${CCPROG} -c symbols.c

$ODIN_loaded $nomain \
      symbols.o \
      $ODIN_library_o_files $ODIN_library_c_files \
      $ODIN_user_o_files $ODIN_user_c_files \
   >symbols 2>ERRORS
mv source used_sources
mv object used_objects

exit 0

#! /bin/sh
# $Id: UserPgram.sh,v 2.2 1997/08/28 18:27:04 waite Exp $
# Copyright 1997, The Regents of the University of Colorado

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

ODIN_Pgram=$1;shift; ODIN_BuPgram=$1;shift;

# EXEC (UserPgram.sh) (:level_6_specs +incl=(:etaIncl) :Pgram)
#                     (:level_6_specs +incl=(:etaIncl) :BuPgram)
#   => (:pgram);
# :pgram 'Complete parsing grammar'? => :FILE;

if test -s $ODIN_BuPgram
then
    cp $ODIN_BuPgram pgram
else
    cp $ODIN_Pgram pgram
fi

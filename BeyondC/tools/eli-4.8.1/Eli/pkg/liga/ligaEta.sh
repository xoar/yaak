#! /bin/sh
# $Id: ligaEta.sh,v 1.1 2002/05/02 14:46:35 cogito Exp $
# Copyright, 2002, The University of Paderborn

# This file is part of the Eli translator construction system.
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

#EXEC (ligaEta.sh) (:lido) (+incl)
#  => (:lidoEta) (:lidoEta_tab);


ODIN_lido=$1;shift; ODIN_incl=$1;shift;

if test "$ODIN_incl" != '' 
then
  if grep lido.eta.h $ODIN_incl >/dev/null 2>&1
  then
    echo '#include "lido.eta.h"' | cat - $ODIN_lido > lidoEta
    echo "1 -1 $ODIN_lido" > lidoEta_tab
  else
    cp $ODIN_lido lidoEta
    echo "1 0 $ODIN_lido" > lidoEta_tab
  fi
else
  cp $ODIN_lido lidoEta
  echo "1 0 $ODIN_lido" > lidoEta_tab
fi

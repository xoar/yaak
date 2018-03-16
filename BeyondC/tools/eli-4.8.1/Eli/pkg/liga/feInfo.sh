#!/bin/sh
# $Id: 
# Copyright, 2008, The University of Paderborn

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

PKG=$1;shift; ODIN_e94=$1;shift; ODIN_e95=$1;shift;  mkdir feInfoDir;

# feInfo[.none] 'Gives information about .lido specs after the initial analysis' :
#         USER
#                : (:level_4_specs:lido.cmpd :cpp)

"$ODINCACHE/PKGS/liga/ligaFe.exe" "$ODIN_e94" 1> ERRS 2>&1
cp $ODIN_e94 feInfoDir/compoundLido

echo "Liga Frontend Protocol Information" > feInfoDir/feInfo
echo "----------------------------------" >> feInfoDir/feInfo
echo "The following protocol provides information about" >> feInfoDir/feInfo
echo "the compound liga input specification:" >> feInfoDir/feInfo
echo "" >> feInfoDir/feInfo
echo "  - tree and class symbols, their attributes and their inheritance relation" >> feInfoDir/feInfo
echo "  - rule attributes" >> feInfoDir/feInfo
echo "  - remote access constructs INCLUDING, CONSTITUENT, and CONSTITUENTS" >> feInfoDir/feInfo
echo "  - inheritance of computations" >> feInfoDir/feInfo
echo "  " >> feInfoDir/feInfo
echo "You can find a copy of the compound liga input specification" >> feInfoDir/feInfo
echo "in file $ODIN_e94" >> feInfoDir/feInfo
echo "  " >> feInfoDir/feInfo
echo "Both frontend information and the compound lido specification can" >> feInfoDir/feInfo
echo "also be obtained from a virtual directory by deriving" >> feInfoDir/feInfo
echo "  " >> feInfoDir/feInfo
echo "   <yourspec>:feInfo:viewlist" >> feInfoDir/feInfo

echo "  " >> feInfoDir/feInfo
echo "  " >> feInfoDir/feInfo
echo "Symbol and rule information" >> feInfoDir/feInfo
echo "---------------------------" >> feInfoDir/feInfo
cat $ODIN_e94.symb >> feInfoDir/feInfo
echo "  " >> feInfoDir/feInfo

echo "Remote access information" >> feInfoDir/feInfo
echo "-------------------------" >> feInfoDir/feInfo
cat $ODIN_e94.remote  >> feInfoDir/feInfo
echo "  " >> feInfoDir/feInfo

echo "Inheritance of computations" >> feInfoDir/feInfo
echo "---------------------------" >> feInfoDir/feInfo
cat $ODIN_e94.inhcmp  >> feInfoDir/feInfo
echo "  " >> feInfoDir/feInfo



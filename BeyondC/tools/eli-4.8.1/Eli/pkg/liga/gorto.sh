#!/bin/sh
# $Id: gorto.sh,v 2.5 2001/10/25 14:34:04 cogito Exp $

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

PKG=$1;shift; ODIN_lido=$1;shift; ODIN_MeIdl=$1;shift; ODIN_option=$1;shift;
ODIN_dir=`dirname $ODIN_lido`

#EXEC (gorto.sh) (.) (:level_4_specs :lido.cmpd :cpp) 
#		     (:level_4_specs +RunGorto :MeIdl) 
#                    (:level_4_specs :ord_option)
#  => (:gorto);
#    :gorto 'Graphical dependence analysis possibly with output of arrange options'? => :EXECUTABLE;

cat <<END > gorto
#!/bin/sh

if ( test -n "$DISPLAY" )
then
    xrdb -merge $PKG/Frames/Gorto.ad
    $PKG/ligaGorto.exe  \
	-input $ODIN_MeIdl  \
	-output /dev/null  \
	-lido $ODIN_lido -ctrl \
	$ODIN_option -lcl \
	$ODIN_dir/options 1> /dev/null 2> $ODIN_dir/ERROR
else
    echo FATAL: GORTO works only under X11! > ERROR
    exit 0
fi

if test -s $ODIN_dir/ERROR
then
    cat $ODIN_dir/ERROR
fi

if test ! -s $ODIN_dir/options
then
    exit 0
fi

if test ! -w .
then
    echo "****"
    echo "Because your current directory is not writable, the results of your"
    echo "Gorto session cannot be moved in your current directory. You will"
    echo "find the Liga options in file $ODIN_dir/options."
    echo "****"
    exit 0
fi

if test -s GORTO.ctl
then
    mv GORTO.ctl GORTO.bak
    echo "****"
    echo "The file \"GORTO.ctl\" in your current working directory"
    echo "has been overwritten with the results of GORTO and will be used"
    echo "now for further derivations, if it is part of your specifications."
    echo "The previous content of \"GORTO.ctl\" has been saved in \"GORTO.bak\""
    echo "****"
else
    echo "****"
    echo "In your current working directory you will find a file"
    echo "\"GORTO.ctl\" containing LIGA options for further derivations."
    echo " You should add this file to your specifications!"
    echo "****"
fi

mv $ODIN_dir/options GORTO.ctl
exit 0
END


chmod +x gorto
exit 0

#! /bin/sh -f

sed 's/$/!:redo/' $1 >redo
cat $1 >>redo

exit 0


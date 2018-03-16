#! /bin/sh -f

sed -n 's/^--- <\(.*\)> generated errors ---$/\1 !:redo/p' $1 >redo_errs
sed -n 's/^** Summary of error messages for \(.*\)/\1/p' $1 >>redo_errs

exit 0


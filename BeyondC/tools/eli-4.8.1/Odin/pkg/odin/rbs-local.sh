#!/bin/sh

$1/cleartool setview $2 << EOF
$3/PKGS/odin/rbs.exe $4 $5
EOF



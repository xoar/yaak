#!/bin/sh

cat << EOF
   !:quit
   OdinExpr
      HostFile
	+ ParameterType
	+ ParameterType = String
	+ ParameterType = (OdinExpr)
	+ (OdinExpr)
	: FileType
	/ Key
	% Key
   OdinExpr > OdinExpr
   OdinExpr >
   OdinExpr < OdinExpr
   OdinExpr <
   OdinExpr !HostCommand
   OdinExpr !
   OdinExpr !:test
   !HostCommand
   !:test
   Variable =
   Variable = Value
   Variable = !Value
EOF

exit 0

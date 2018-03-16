# $Id: line_err.awk,v 1.4 1998/09/16 22:02:34 waite Exp $
# Copyright 1992, The Regents of the University of Colorado

# Add line_err hooks to a file with standard error reporting
#    On entry-
#       stdin is a text file with lines in the form:
#             seq file line column text
#          seq=irrelevant integer
#          file=Odin file name or "."
#          line=Decimal line number or "0"
#          column=Decimal column number or "0"
#
#          The file is sorted by (file line column)
#    On exit-
#       stdout is a text file with lines grouped by file as follows:
#
#             . 0 0 text
#             ...
#             (|file1|line_err|file1 line1 column1 text1
#             file1 line2 column2 text2
#             ...
#             file1 linen columnn textn
#             |)
#             ...

	{ line = ""
	  if ($2 != file) {
	    if (file != "." && file != "") line = "|)\n"
	    file = $2
	    if (file != ".") line = line "(|" $2 "|line_err|"
	  }
	  line = line $2
	  for (i = 3; i <= NF; i++) line = line " " $(i)
	  print line
	}

END	{if (file != "." && file != "") print "|)"}

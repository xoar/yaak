/* This file is part of the Eli translator construction system.

Eli is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

Eli is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with Eli; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */
/* $Id: new_line.c,v 4.1 1997/08/29 07:55:18 peter Exp $ */

/* newline.c 
   provides a function new_line used in the PTG specs to insert a new 
   line into the output. This new line looks different depending on 
   the context for which it is produced: 
   a) ordinary EOL ("\n") for .c and .h file output
   b) a backslash followed by EOL ("\\")  for use in generated cpp-macros
   The context switch is done by calling either 
   "ord_new_line" or 
   "cpp_new_line"
*/

#include <stdio.h>
char *new_line_look = "\n";

#if defined(__STDC__) || defined(__cplusplus)
void ord_new_line(FILE * f)                    /* an ordinary newline */
#else
void ord_new_line(f)
FILE * f;
#endif
{ new_line_look="\n";
}

#if defined(__STDC__) || defined(__cplusplus) /* a newline for a cpp */
					      /* macro */
void cpp_new_line(FILE * f)
#else
void cpp_new_line(f)
FILE * f;
#endif
{ new_line_look="\\\n";
}

#if defined(__STDC__) || defined(__cplusplus)
void new_line(FILE * f)
#else
void new_line(f)
FILE * f;
#endif
{ fprintf(f,"%s",new_line_look);
}







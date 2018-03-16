/* $Id: style.h,v 1.17 1999/10/20 04:56:52 tony Exp $ */
/*##############################################################################

FUNNNELWEB COPYRIGHT
====================
FunnelWeb is a literate-programming macro preprocessor.

Copyright (C) 1992 Ross N. Williams.

   Ross N. Williams
   ross@spam.adelaide.edu.au
   16 Lerwick Avenue, Hazelwood Park 5066, Australia.

This program is free software; you can redistribute it and/or modify
it under the terms of Version 2 of the GNU General Public License as
published by the Free Software Foundation.

This program is distributed WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See Version 2 of the GNU General Public License for more details.

You should have received a copy of Version 2 of the GNU General Public
License along with this program. If not, you can FTP the license from
prep.ai.mit.edu/pub/gnu/COPYING-2 or write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

Section 2a of the license requires that all changes to this file be
recorded prominently in this file. Please record all changes here.

Programmers:
   RNW  Ross N. Williams  ross@spam.adelaide.edu.au
   AMS  Tony Sloane	  asloane@comp.mq.edu.au
   BK   Basim Kadhim      kadhim@cs.colorado.edu
   MJ   Matthias Jung     mjung@uni-paderborn.de

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.
   26-Jul-1992  AMS  Added RCS id.
   22-Jan-1993  BK   Don't define ulong on AIX because it is already defined.
   03-Feb-1993  BK   Changes for Linux.
   27-Oct-1993  BK   Undefine MIN and MAX if they are already defined.
   28-Oct-1993  BK   Fix bungled ifdef of MIN and MAX.
   31-Aug-1994  AMS  Rename MIN and MAX to FW_MIN and FW_MAX because quite a
                     few systems define MIN and MAX and it's a pain to ensure
		     that this file only gets included after other defns.
   28-Mar-1996  MJ   Add cpp conditionals for compilation under SGI/IRIX

##############################################################################*/


/******************************************************************************/
/*                                    STYLE.H                                 */
/******************************************************************************/
/*                                                                            */
/* WARNING: DO NOT ADD ANY MACHINE OR PROGRAM DEPENDENT DEFINITIONS.          */
/*                                                                            */
/* This style.h file contains program-independent, machine-independent        */
/* definitions that assist C programming in general. Nothing in this file     */
/* should require modification if this file is moved to a new machine or used */
/* in a new computer program. However, it may use abstracted second-order     */
/* definitions from the machine-dependent, program independent module         */
/* "environ".                                                                 */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_STYLE
#define DONE_STYLE

/******************************************************************************/

/* System File Inclusions                                                     */
/* ----------------------                                                     */
/* In order to support a readable programming style, symbols such as TRUE and */
/* NULL are essential. However, environments differ as to whether and where   */
/* these symbols are defined. This can lead to multiple definition errors     */
/* where (say) this style.h file is included in a .C file before <stdlib.h>.  */
/* I did a quick survey of all the .C FunnelWeb modules and found the         */
/* following:                                                                 */
/*                                                                            */
/*    Total files     = 54                                                    */
/*    Number .C files = 22                                                    */
/*    Number .H files = 32                                                    */
/*    Used <stdlib.h> = 19                                                    */
/*    Used <stdio.h>  = 16                                                    */
/*    Used <string.h> = 12                                                    */
/*    Used <ctype.h>  =  6                                                    */
/*    Used <stddef.h> =  4                                                    */
/*    Used <limits.h> =  2                                                    */
/*    Used <setjmp.h> =  1                                                    */
/*                                                                            */
/* Most of these inclusions were in the .C files.                             */
/* It therefore seemed sensible to include some very commonly used system     */
/* header files here and header files that cause problems if not included     */
/* before style.h (<stddef.h>).                                               */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/******************************************************************************/

/* Although this file is machine independent, it still needs some generic     */
/* definitions whose values vary from machine to machine (see above).         */
#include "environ.h"

/******************************************************************************/

/* The following types provide a clear and consistent collection of names for */
/* C's arithmetic types. Each name describes only the portable range that the */
/* underlying type supports. As in C, there are no guarantees about the       */
/* MAXIMUM size of each underlying type and these types can provide no        */
/* guarantees either. In the normal case, they translate to the most speed    */
/* efficient type that will support the specified range. However, to support  */
/* the situations where space efficiency is required, types ending in         */
/* underscores have been defined that strive to conserve memory.              */
/* Note: The signedness of a type does not change when an _ is added.         */
/*                                                                            */
/* The following terminology may be a touch vaxcentric, but it works for me.  */
/*    A BYTE is an  8 bit quantity.                                           */
/*    A WORD is a  16 bit quantity.                                           */
/*    A LONG is a  32 bit quantity.                                           */
#if defined(linux) || defined(__SVR4) || defined(__svr4__) || defined(__alpha) || defined(sgi)
#include <sys/types.h>
#endif

typedef unsigned        ubyte  ; /* Unsigned, [0,255].                        */
typedef unsigned char   ubyte_ ; /* Unsigned, [0,255].         Space first.   */
typedef int             word   ; /* Signed  , [-32767,+32767].                */
typedef short           word_  ; /* Signed  , [-32767,+32767]. Space first.   */
typedef unsigned        uword  ; /* Unsigned, [0,65535].                      */
typedef unsigned short  uword_ ; /* Unsigned, [0,+65535].      Space first.   */
#if !defined(_AIX) && !defined(linux) && !defined(__SVR4) && !defined(__svr4__) && !defined(__alpha) && !defined(sgi)
typedef unsigned long   ulong  ; /* Unsigned, [0,(2^32)-1].                   */
#endif

typedef unsigned        bool   ; /* Unsigned, [0,1].                          */
typedef unsigned char   bool_  ; /* Unsigned, [0,1].           Space first.   */

typedef int             sign   ; /* Signed  , [-1,0,1].                       */

/******************************************************************************/

/* C overloads the attribute keyword "static" horribly giving it meaning on   */
/* both the scoping and lifetime dimensions.  This section gives definitions  */
/* that clarify its use. If these macros are used, there should be no need    */
/* for the keyword "static" in programs using this style file.                */

/* The following macros assist in making the scope of functions clearer. In   */
/* deciding on the names of these macros, I chose from the following lists:   */
/*    file    scope: PRIVATE, LOCAL, HIDDEN.                                  */
/*    program scope: EXPORT, PUBLIC, GLOBAL.                                  */
/* In the end I chose LOCAL and EXPORT. Note: I didn't want to allow more     */
/* than one form as that would have created too much confusion.               */
#define LOCAL  static
#define EXPORT

/* It is desirable to use separate keywords for variables. This makes it      */
/* easier to search for them without stopping at every function. There are    */
/* four classes of variable that we wish to tag, along the two dimensions     */
/* scope:(local,global) and lifetime:(permanent,temporary). In C, all         */
/* variables declared outside of functions have permanent lifetime and so     */
/* the following two names (which should be used only to tag variables not    */
/* declared within a function) have been designed to emphasise the scope      */
/* dimension which is the principal concern for these variables.              */
#define LOCVAR static
#define GLOVAR

/* Variables local to functions always have local scope and so the dimension  */
/* to emphasise is the lifetime. Automatic variables are the most common in   */
/* C and it would be messy to declare them all using a keyword. Far better    */
/* just to tag static local variables, emphasising their lifetime (STAtic).   */
#define STAVAR static

/******************************************************************************/

/* The following definitions are useful for dealing with void.                */
/* The typedefed definition "p_void" should always be used instead of         */
/* "void *" so as to improve portability.                                     */
/* The definition of "void" and "p_void" come from environ.h                  */
typedef p_void *p_p_void;
#define PV     (p_void)
#define PPV    (p_p_void)

/******************************************************************************/

/* The following symbols are more mnemonic than character escape sequences.   */
#define EOS '\0'
#define EOL '\n'

/******************************************************************************/

/* The ANSI library functions use many different techniques for returning     */
/* status information. For example, fopen returns NULL upon failure, but      */
/* fclose returns EOF upon failure. The result is that it is hard to          */
/* proofread calls to these routines without constantly referring to the      */
/* library manual. To avoid this problem, we define symbols with helpful      */
/* names for the different values returned. This makes the code obvious.      */

/* 07-Feb-1992: During porting I ran into a problem here with FPUTS_S. I had  */
/* defined it to be zero, as stated in the THINK C V4 ANSI library guide.     */
/* However, it turned out that fputs() returns EOF (-1) on failure and the    */
/* value that it returns on success is non negative! (See ANSI (7.9.7.4)).    */
/* Caught by an overspecification by the THINK C people! The lesson is that   */
/* it is very important to make sure that each function's status check symbol */
/* is defined on the "right" side (success or failure) - that is, the side    */
/* for which a single value for that status is guaranteed portably.           */
/* The following values have all been checked for this.                       */

/* Note: _F=Failure, _S=Success, _FE=Failure or End of File.                  */

#define FOPEN_F  (NULL)
#define FSEEK_S     (0)
#define FTELL_F   (-1L)
#define FGETC_FE  (EOF)
#define FGETS_FE (NULL)
#define FPUTC_F   (EOF)
#define FPUTS_F   (EOF)
#define FFLUSH_S    (0)
#define FCLOSE_F  (EOF)
#define REMOVE_S    (0)
#define RENAME_S    (0)
#define MALLOC_F (NULL)

/******************************************************************************/

/* The following macro functions are handy. However, be sure not to hand them */
/* an argument with a non-idempotent side effect!!! (e.g. FW_MAX(a++,b)).     */
#define FW_MIN(A,B) ((A)<(B) ? (A) : (B))
#define FW_MAX(A,B) ((A)>(B) ? (A) : (B))

/******************************************************************************/

/* Some environments don't define some stuff we need so we do it here.        */
/* Cautiously!                                                                */

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE (-1)
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS (0)
#endif

/******************************************************************************/

/* The standard library macro/function "isprint" can be too loose in some     */
/* circumstances on some machines and it is convenient to define a macro      */
/* that provides a more strict 7-bit ASCII definition of "printable".         */
#define isascprn(ch) ((' '<=ch) && (ch<='~'))

/******************************************************************************/

/* Some compilers (GCC at least) complain about characters as a type in a     */
/* function argument. The following typedef is a quick hack that lets me say  */
/* that I really wanted the function argument to be a character, while        */
/* actually supplying an integer.                                             */
typedef int intchar;

/******************************************************************************/
/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                                End of STYLE.H                              */
/******************************************************************************/


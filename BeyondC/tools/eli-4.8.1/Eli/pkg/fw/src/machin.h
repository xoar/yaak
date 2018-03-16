/* $Id: machin.h,v 1.12 2013/11/11 09:41:24 pfahler Exp $ */
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
   WMW  William Waite	  William.Waite@Colorado.edu
   BK   Basim Kadhim      kadhim@cs.colorado.edu

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.
   26-Jul-1992  AMS  Added RCS id.
   22-Nov-1992  AMS  Tailored prototypes for memcpy, memset and memcmp
                     to keep gcc happy.
   18-Dec-1992  WMW  Add a check for the macro version of toupper.
   12-Jan-1993  BK   Replace declarations with system header includes.
   13-Jan-1993  BK   Fix FILENAME_MAX so that it is long enough for HPUX.
   17-Mar-1993  AMS  Export fn_split for use by weaveinfo.c.
   25-Jan-1994  AMS  Added alignment setting for ALPHA.

##############################################################################*/


/******************************************************************************/
/*                                    MACHIN.H                                */
/******************************************************************************/
/*                                                                            */
/* WARNING: DO NOT ADD ANY PROGRAM DEPENDENT DEFINITIONS.                     */
/*                                                                            */
/* This module (machin.h and machin.c) contains definitions and objects       */
/* whose values depends directly on the compilation and execution             */
/* environment, but are otherwise independent from any particular computer    */
/* program.                                                                   */
/*                                                                            */
/* The only difference between the purpose of this module and the "environ"   */
/* module is that the "environ" module contains the "essentials" whereas this */
/* module contains extra machine specific definitions and objects that will   */
/* not be required by most user modules.                                      */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_FWMACHIN
#define DONE_FWMACHIN

/******************************************************************************/

#include <time.h>
#include "style.h"

/******************************************************************************/

/* Machine Alignment Constraints                                              */
/* -----------------------------                                              */
/* Some machines require that objects of particular lengths be aligned in     */
/* memory. For example, the 68000 will trap any attempt to access a word      */
/* (16 bits or an int in THINK C) at an odd address. It is important that C   */
/* programs that deal with memory at a low level be aware of such             */
/* constraints. As the constraints are always at a power of two, we defined   */
/* ALIGN_POWER to be the minimum power of two at which it is both safe and    */
/* efficient to operate.                                                      */

/* The Macintosh requires words and longs to be aligned on word boundaries.   */
/* The PC is not fussy about alignment, but operates more efficiently at word */
/* boundaries.                                                                */
#if MAC | PC
#define ALIGN_POWER (1L)
#endif

/* The VMS VAX doesn't care about alignment, but operates more efficiently on */
/* longword boundaries.                                                       */
#if VMS
#define ALIGN_POWER (2L)
#endif

/* For Eli purposes, we want to be SUN for everything, except for the 	      */
/* alignment on alpha's.  Hence this wierd construct.			      */
/* This saves us going around and defining symbols for all the archs that Eli */
/* supports.								      */
/* The Sun requires objects to be aligned on longword boundaries (=2^2).      */
/* The ALPHA is more strict. 						      */
#if SUN
#if __alpha
#define ALIGN_POWER (3L)
#else
#define ALIGN_POWER (2L)
#endif
#endif

/******************************************************************************/

/* Filenames                                                                  */
/* ---------                                                                  */
/* The length and structure of filenames varies from machine to machine. The  */
/* differences addressed here are:                                            */
/*    1) The character used to separate directory specs from filenames.       */
/*    2) The maximum length of a filename.                                    */

/* FN_DELIM must contain the character that separates directory specs from    */
/* filenames. Notice that in the VMS case, it is "]", not "."                 */

#if MAC
#define FN_DELIM ':'
#endif

#if SUN
#define FN_DELIM '/'
#endif

#if VAX
#define FN_DELIM ']'
#endif

#if PC
#define FN_DELIM '\\'
#endif

/* The rest of this section shouldn't have to be changed, unless you          */
/* encounter a funny with your system's definition of FILENAME_MAX.           */

/* FILENAME_MAX tells the maximum number of characters allowed in a filename  */
/* on the target machine. This symbol is supposed to be defined in stdio.h    */
/* (ANSI S7.9.1) so we don't want to override that. However, if it isn't, we  */
/* need to define a safe default length.                                      */
#ifdef hpux
#undef FILENAME_MAX
#endif

#ifndef FILENAME_MAX
#define FILENAME_MAX 300
#endif

/* Some VAX compilers define FILENAME_MAX to be 39, which is the maximum      */
/* length of the NAME part of a VMS filename. This is not appropriate, so we  */
/* override it.                                                               */
#if VMS
#undef FILENAME_MAX
#define FILENAME_MAX 255        /* Should really be NAM$C_MAXRSS              */
#endif

/* Now we can use the constant to define a filename type.                     */
/* Note: For a while I defined "typedef fn_t *p_fn_t". However, this is a     */
/* pointer to an array rather than (char *) and it caused no end of problems. */
typedef char fn_t[FILENAME_MAX+1];
typedef char *p_fn_t;

/******************************************************************************/

/* Command Lines                                                              */
/* -------------                                                              */
/* The maximum length of command line varies from machine to machine and we   */
/* define symbols to reflect this. The reason why we don't just set this to a */
/* high value and forget about it is that FunnelWeb sometimes places          */
/* command line variables on the stack, and some machines (e.g. MAC under     */
/* THINK-C don't provide much stack space. So we have to minimize this        */
/* variable on those machines.                                                */

/* We choose a small maximum command line on the Macintosh so as to avoid     */
/* chewing up stack space when command lines have to be pushed.               */
#if MAC
#define COMLINE_MAX 300
#endif

/* On the Sun, 1024 is a normal command line and 2048 is safe. */
#if SUN
#define COMLINE_MAX 2048
#endif

/* On the VMS, 1024 is usually adequate. */
#if VMS
#define COMLINE_MAX 1024
#endif

/* On a PC, we assume this is enough. */
#if PC
#define COMLINE_MAX 300
#endif

/* Make sure that the value is not too low. */
/* The value 300 is guaranteed by the command interpreter. */
#if COMLINE_MAX < 300
   #error COMLINE_MAX must be at least 300.
#endif

/* Now define a type for command lines.                                       */
/* Note: For a while I defined "typedef cl_t *p_cl_t". However, this is a     */
/* pointer to an array rather than (char *) and it caused no end of problems. */
typedef char cl_t[COMLINE_MAX+1];
typedef char *p_cl_t;

/******************************************************************************/

/* Line Termination                                                           */
/* ----------------                                                           */

/* FunnelWeb has special-case code to make reading input files faster on      */
/* machines where the format of text files corresponds to the internal C      */
/* text stream model. The UNIX_EOL #define should be activated if and only    */
/* the host environment has text files consisting of a stream of bytes with   */
/* a single LF (ASCII,decimal-10,hex-0A) character being used to terminate    */
/* each line, and no special character to indicate end of file.               */
/* This is the same format as is used in the Unix operating system.           */
/* If you are in doubt about this, play it safe and define your environment   */
/* to be non-Unix, as non-Unix will work on ALL systems (including Unix).     */

#if MAC | VMS | PC
/* These systems do NOT use Unix EOLs. */
#define UNIX_EOL 0
#endif

#if SUN
/* This should really be 1 on a SUN, but I haven't got around to debugging    */
/* FunnelWeb with UNIX_EOL==1.                                                */
#define UNIX_EOL 0
#endif

/******************************************************************************/

/* MIssing Prototypes                                                         */
/* ----------------                                                           */
/* Compilers that are fussy about prototypes sometimes complain about calls   */
/* to the standard libraries. These declarations solve this problem.          */

#include <stdio.h>

/* toupper is a macro accepting only lower case letters in some systems.
 * FunnelWeb assumes that toupper is a function that accepts ANY character.
 * This redefines a macro to accept any character, or deals with a routine.
 */
#ifdef toupper
#undef toupper
#define toupper(c) (islower(c) ? ((c)-'a'+'A') : c)
#else
/* int     toupper P_((int)); this comes from ctype.h */
#endif

#ifdef __STDC__
#include <string.h>
#else
#include <memory.h>
#endif

#include <time.h>

/******************************************************************************/

EXPORT void fn_split P_((p_fn_t,p_fn_t,p_fn_t,p_fn_t));

EXPORT void fn_ins P_((p_fn_t,char *));
/* - The name stands for FileName INSert.                                     */
/* - The first argument must be a pointer to an object of type fn_t           */
/*   (containing an ordinary C character string).                             */
/* - The second argument must be a pointer to an ordinary C character string. */
/* - Both arguments must contain a full, partial, or empty filename spec.     */
/* - We will refer to the arguments as f1 and f2.                             */
/* - If there is a syntax error in either spec, fn_ins does nothing.          */
/* - Otherwise, it:                                                           */
/*      1. Analyses the two filename specifications into filename field .     */
/*      2. Replaces each field in f1 by the corresponding field in f2, but    */
/*         only if the corresponding field in f2 is non-empty.                */
/*      3. Optionally [concession to VMS] it may then replace blank fields    */
/*         in the resulting file spec in f1 by fields from the current        */
/*         global "default" directory spec.                                   */
/* The structure and fields of filenames will vary from machine to machine    */
/* and so this is not important. However, every implementation must structure */
/* the filename so that it will at least RECOGNISE a file extension           */
/* (e.g. ".lis") field.                                                       */

/******************************************************************************/

EXPORT void getcline P_((int,char **,char *));
/* Operating system environments vary a lot in the way in which their command */
/* language interfaces are set up. The approach taken in FunnelWeb is to      */
/* define a "standard" Unix-like command line syntax and then insist that     */
/* other environments deliver such a command line as a single string.         */
/* This function getcline must extract such a standard command line from its  */
/* environment and copy it as a single string of not more than COMLINE_MAX    */
/* characters into its third argument. A description of the "standard"        */
/* command line can be found in the options package.                          */
/* The first  argument is given to getcline and is argc from main().          */
/* The second argument is given to getcline and is argv from main().          */
/* These two arguments are given in case getcline needs them to assemble the  */
/* command line (as opposed to calling e.g. VMS CLI routines).                */
/* The third argument is the string into which the result should be placed.   */

/******************************************************************************/

EXPORT float tim_real P_((void));
/* Returns the number of seconds between the present and an unspecified, but  */
/* statically fixed time in the past.                                         */
/* Returns 0.0 if this information is unavailable                             */

EXPORT float tim_cpu P_((void));
/* Returns the number of CPU seconds consumed between the present and an      */
/* unspecified, but statically fixed time in the past.                        */
/* Returns 0.0 if this information is unavailable                             */

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                                End of MACHIN.H                             */
/******************************************************************************/

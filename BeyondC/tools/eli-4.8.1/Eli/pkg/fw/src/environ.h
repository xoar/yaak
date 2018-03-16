/* $Id: environ.h,v 1.5 1999/10/20 04:56:11 tony Exp $ */
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

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.
   26-Jul-1992  AMS  Added RCS id.

##############################################################################*/


/******************************************************************************/
/*                                   ENVIRON.H                                */
/******************************************************************************/
/*                                                                            */
/* WARNING: DO NOT ADD ANY PROGRAM-DEPENDENT DEFINITIONS.                     */
/*                                                                            */
/* This header file environ.h contains definitions and objects whose values   */
/* depends directly on the compilation and execution environment, but are     */
/* otherwise independent of any particular computer program.                  */
/*                                                                            */
/* This is one of two machine-dependent, program-independent modules. The     */
/* other module is machin (machin.h,machin.c). This "environ" module contains */
/* definitions and objects that are considered essential. The "machin" module */
/* contains less essential definitions. Motivation for the division came from */
/* the fact that style.h (used by almost every module) includes environ.h     */
/* (this file), and from the need for the stuff in style.h by some            */
/* environment-dependent definitions.                                         */
/*                                                                            */
/* There seems to be two ways to organize a module such as this one. The      */
/* first is to have a different version of this module for each target        */
/* environment. The second is to have a single file that uses #defines and    */
/* #ifs to select between code for each target environment. I have chosen the */
/* latter method as this allows many different environments to share the same */
/* definitions.                                                               */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_ENVIRON
#define DONE_ENVIRON

/******************************************************************************/

/* Select An Environment                                                      */
/* ---------------------                                                      */
/* Choose the environment in which the program will be compiled and executed. */
/* This may be the only change you need to make to get FunnelWeb to compile.  */
/*                                                                            */
/* If your exact environment is not listed, try one that is close.            */
/* If problems arise, an attempt should be made to solve them                 */
/* without creating a new environment definition.  However, if this is not    */
/* possible, define a new environment below and "implement" it by going       */
/* through environ.h and machin.h and machin.c and adding appropriate         */
/* definitions.                                                               */
/*                                                                            */
/* The following table lists real/defined environment pairs under which       */
/* FunnelWeb is known to compile cleanly.                                     */
/*                                                                            */
/* Symbol = Processor  Machine       OS            Compiler                   */
/* ------   ---------  -------       --            --------                   */
/*    MAC = 68000      Macintosh-SE  Mac           THINK-C V4.0.5             */
/*    SUN = SPARC      SUN ELC       Unix(SunOS)   GNUC                       */
/*    VMS = VAX        VAXStation    VMS           VAXC                       */
/*     PC = 386        IBM PC Clone  MSDOS5.0      Borland C++                */
/*                                                                            */
/* Set exactly one of the following environments to 1, the others to 0.       */

#define MAC 0
#define SUN 1
#define VMS 0
#define PC  0

/* Ensure that exactly one environment has been selected.                     */
#if MAC+SUN+VMS+PC != 1
   #error Error: You must choose exactly one machine in ENVIRON.H.
#endif

/******************************************************************************/

/* Establish Presence or Absence of __STDC__                                  */
/* -----------------------------------------                                  */
/* The __STDC__ symbol is very useful for determining if the compiler is      */
/* ANSI. However, some "nearly ANSI" compilers don't set this symbol, and     */
/* experience shows that things turn out better if it is set.                 */
/* This section decides if __STDC__ should be defined.                        */

/* The Macintosh THINK C compiler seems to be ANSI standard but, strangely    */
/* does not define the standard preprocessor symbol __STDC__ that indicates   */
/* this. Instead it defines THINK_C. Here, we execute the link manually.      */
/* For more information see the THINK C User's Manual, Chapter 57: "Language  */
/* Reference", Section 12.10, p.442.                                          */
#ifdef THINK_C
#define __STDC__ 1
#endif

/* The problem seems to exist with VAX C too. */
#if VMS
#define __STDC__ 1
#endif

/******************************************************************************/

/* Switch From Definedness to Boolean Symbols                                 */
/* ------------------------------------------                                 */
/* Use of the definedness of a preprocessor symbol to detect a condition is   */
/* convenient if it is desired that only one condition be tested at a time.   */
/* However, if we want to OR conditions, it is more convenient to use defined */
/* symbols that are either 0 or 1. This section contains ifdefs that do this. */

#ifdef __STDC__
#define STDC 1
#else
#define STDC 0
#endif

/* Note: If THINK_C is predefined, it is predefined to be 1. */
#ifndef THINK_C
#define THINK_C 0
#endif

/******************************************************************************/

/* Void                                                                       */
/* ----                                                                       */
/* Define void if necessary and define pointer to void.                       */
/* This idea from the book "Portable C", p.41.                                */
/* If necessary, add a boolean condition to cover your environment.           */
/* Note: The "| SUN" is a last minute desperate hack.                         */
#if STDC | SUN
typedef void   *p_void;
#else
typedef int       void;
typedef char   *p_void;
#endif

/* The following function is here solely to act as a first tripping point for */
/* environments with no "void" so that the users trying to port this code     */
/* will look here first instead of starting to delete voids in the program.   */
extern void test_void();

/******************************************************************************/

/* Const                                                                      */
/* -----                                                                      */
/* It's useful to be able to specify that certain objects are constants.      */
/* Unfortunately, the "const" construct is only available in ANSI C and so we */
/* have to have a macro so as to cope with non-ANSI compilers.                */
/* Note: THINK-C is nearly ANSI, but does not support "const".                */
#if STDC & !THINK_C
#define CONST const
#else
#define CONST
#endif

/******************************************************************************/

/* Prototypes                                                                 */
/* ----------                                                                 */
/* Define a macro to wrap around prototype parameter lists so as to support   */
/* compilers with and without prototypes.                                     */
/* This idea came from the book "Portable C", S3.1, p.32.                     */
#if STDC
#define P_(A) A
#else
#define P_(A) ()
#endif

/******************************************************************************/

/* Structure Assignments                                                      */
/* ---------------------                                                      */
/* Structure assignments are not supported on some of the older compilers and */
/* so we use a macro to perform such operations.                              */
/* This idea came from the book "Portable C", S8.2.2, p.184.                  */
#if STDC
#define ASSIGN(a,b) ((a)=(b))
#else
#define ASSIGN(a,b) (memcpy((char *)&(a),(char *)&(b),sizeof(a)))
#endif

/******************************************************************************/

/* VMS EXIT STATUS */
/* --------------- */
/* The VAX C compiler I used doesn't seem to be ANSI. This means that the    */
/* exit symbols aren't set up properly. Furthermore, the sensible defaults   */
/* in the style.h file don't work for VMS. The upshot is that we have to do  */
/* a special case. Note: The top bit set in a VMS exit status means suppress */
/* diagnostic message. Even status means failure. Odd means success.         */
#if VMS
#undef  EXIT_SUCCESS
#undef  EXIT_FAILURE
#define EXIT_SUCCESS 1
#define EXIT_FAILURE (0x10000002)
#endif

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                                End of ENVIRON.H                            */
/******************************************************************************/

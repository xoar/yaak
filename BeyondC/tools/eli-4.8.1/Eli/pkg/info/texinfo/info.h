#ifndef INFO_H
#define INFO_H
/* $Id: info.h,v 1.23 1998/02/11 16:43:12 waite Exp $

   info.h

   Copyright (C) 1987 Free Software Foundation, Inc.

   This file is part of GNU Info.

   GNU Info is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.  No author or distributor accepts
   responsibility to anyone for the consequences of using it or for
   whether it serves any particular purpose or works at all, unless he
   says so in writing.  Refer to the GNU Emacs General Public License
   for full details.

   Everyone is granted permission to copy, modify and redistribute
   GNU Info, but only under the conditions described in the GNU Emacs
   General Public License.   A copy of this license is supposed to
   have been given to you along with GNU Emacs so you can know your
   rights and responsibilities.  It should be in a file named COPYING.
   Among other things, the copyright notice and this notice must be
   preserved on all copies.  
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <signal.h>
#include <pwd.h>
#include <string.h>

#include "eliproto.h"

#ifdef sequent
#define strchr(s,c) index(s,c)
#define strrchr(s,c) rindex(s,c)
#endif

#include <stdlib.h>

#if defined(STDC_HEADERS) || defined(__GNU_LIBRARY__)
#define index strchr
#else

#ifdef __alpha
#include <unistd.h>
#include <sys/types.h>
#endif

#if defined(USG) || defined(hpux)
#include <memory.h>
#endif

#ifdef SYSV
struct passwd *getpwnam ();
#include <fcntl.h>

#ifdef sgi
#include <unistd.h>
#endif

#else
#include <sys/file.h>
#endif

#endif

/* Miscellaneous */

typedef int boolean;
#define true 1
#define false 0
#ifndef NULL
#define NULL char *0x0
#endif
#define UNIX

#define barf(msg) fprintf(stderr, "%s\n", msg)
#define FILE_EXISTS(f) (access((f),R_OK)==0)

/* Configurable things */

#define FILENAME_LEN 256
#define FOOTNOTE_HEADER "*Note"
#define MAX_INDIRECT_FILES 100	/* should be done in a different way. */
#define MENU_HEADER "\n* Menu:"
#define MENU_ID "\n* "
#define NODE_ID "Node:"
#define NODENAME_LEN 256
#define PROJECT_NAME "GNU Info"
#define STRING_SIZE 256
#define TAG_TABLE_BEG_STRING "\nTag Table:\n"
#define TAG_TABLE_END_STRING "\037\nEnd Tag Table"
#define nodeend_sequence "\n\037"

/* Characters */

#define control_character_threshold 0x020 /* smaller than this is control */
#define meta_character_threshold 0x07f	/* larger than this is Meta. */
#define control_character_bit 0x40	/* 0x000000, must be off. */
#define meta_character_bit 0x080/* x0000000, must be on. */

#define info_separator_char '\037'
#define start_of_node_string "\037"

#ifdef CTRL
#undef CTRL
#endif

#define CTRL(c) ((c) & (~control_character_bit))
#define META(c) ((c) | meta_character_bit)

#define UNMETA(c) ((c) & (~meta_character_bit))
#define UNCTRL(c) to_upper(((c)|control_character_bit))

#ifndef to_upper
#define to_upper(c) (((c) < 'a' || (c) > 'z') ? c : c-32)
#define to_lower(c) (((c) < 'A' || (c) > 'Z') ? c : c+32)
#endif

#define CTRL_P(c) ((c) < control_character_threshold)
#define META_P(c) ((c) > meta_character_threshold)

#define NEWLINE '\n'
#define RETURN CTRL('M')
#define DELETE 0x07f
#define TAB '\t'
#define ABORT_CHAR CTRL('G')
#define PAGE CTRL('L')
#define SPACE 0x020
#define ESC CTRL('[')
#define control_display_prefix '^'

/* Types */

typedef struct nodeinfo
{
  char *filename;
  char *nodename;
  size_t pagetop;
  size_t nodetop;
  size_t datatop;
  struct nodeinfo *next;
} NODEINFO;

typedef struct indirectinfo
{
  char *filename;
  int first_byte;
} INDIRECT_INFO;

typedef int Function ();

typedef struct
{
  int left, top, right, bottom;
  int ch, cv;
} IWINDOW;

typedef struct _wind_list
{
  int left, top, right, bottom;
  int ch, cv;
  struct _wind_list *next_window;
} IWINDOW_LIST;

typedef struct {
  char *name, *value, *desc;
} OPTION;

typedef struct {
  int index;
  char *value;
} INIT_OPTION;

typedef struct completion_entry
{
  char *identifier;
  char *data;
  struct completion_entry *next;
} COMP_ENTRY;

/* Option indexes. */
/* These must be consistent with the option array in option.c
   and choice ones should be after all general ones (see option_sw.c). */

#define EDITOR			0
#define WINEDITOR		1
#define WINRUNNER		2
#define PRINTER 	        3
/* Start of toggle options */
#define SEARCHINSENSITIVE	4

/* The default options. */
/* The defaults for WINEDITOR and WINRUNNER must be decided by each	*/
/* info browser individually using the INIT_OPTION structure.		*/

#ifndef DEFAULT_EDITOR
#define DEFAULT_EDITOR		"vi"
#endif
#ifndef DEFAULT_PRINTER
#define DEFAULT_PRINTER		"postscript"
#endif
#ifndef DEFAULT_SEARCHINSENSITIVE
#define DEFAULT_SEARCHINSENSITIVE	"yes"
#endif

/* Output from a run command goes here */
#ifndef SCRIPTOUTPUT
#define SCRIPTOUTPUT	"scriptout"
#endif

/* Manuals have this at the end of their names */
#ifndef PRINTEXTENSION
#define PRINTEXTENSION	".ps"
#endif

/* Terminal error codes */

#define NO_ERROR 0
#define GENERIC_ERROR 1
#define NO_TERMINAL_DESCRIPTOR 2
#define OUT_OF_MEMORY 3
#define BAD_TERMINAL 4

#define FERROR(msg)	fprintf (stderr, msg); exit (GENERIC_ERROR)

/* For complaining */

#ifndef MAIL
#define MAIL		"mail"
#endif
#ifndef MAINTAINER
#define MAINTAINER	"elibugs@cs.colorado.edu"
#endif

/* Used for formatting options list */

#define INDENT 20

extern void display_error ELI_ARG((char *));
extern boolean confirm ELI_ARG((char *));
extern void eat_argument ELI_ARG((int, int, char **, char *));
extern void info ELI_ARG((int, char **));

#endif

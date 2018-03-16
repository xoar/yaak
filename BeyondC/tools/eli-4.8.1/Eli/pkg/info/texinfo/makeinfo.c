char rcsid[] = "$Id: makeinfo.c,v 1.41 2013/11/14 04:03:35 profw Exp $";

/* Makeinfo -- convert texinfo format files into info files

   Copyright (C) 1987, 1991 Free Software Foundation, Inc.

   This file is part of GNU Info.

   Makeinfo is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.  No author or distributor accepts
   responsibility to anyone for the consequences of using it or for
   whether it serves any particular purpose or works at all, unless he
   says so in writing.  Refer to the GNU Emacs General Public License
   for full details.

   Everyone is granted permission to copy, modify and redistribute
   Makeinfo, but only under the conditions described in the GNU Emacs
   General Public License.   A copy of this license is supposed to
   have been given to you along with GNU Emacs so you can know your
   rights and responsibilities.  It should be in a file named COPYING.
   Among other things, the copyright notice and this notice must be
   preserved on all copies.  */

/* This is Makeinfo version 1.43.  If you change the version number of
   Makeinfo, please change it here and at the lines reading:

    int major_version = 1;
    int minor_version = 43;

   in the code below. */

/* You can change some of the behaviour of Makeinfo by changing the
   following defines: */

/* Define INDENT_PARAGRAPHS_IN_TABLE if you want the paragraphs which
   appear within an @table, @ftable, or @itemize environment to have
   standard paragraph indentation.  Without this, such paragraphs have
   no starting indentation. */
/* #define INDENT_PARAGRAPHS_IN_TABLE */

/* Define DEFAULT_INDENTATION_INCREMENT as an integer which is the amount
   that @example should increase indentation by.  This incrmement is used
   for all insertions which indent the enclosed text. */
#define DEFAULT_INDENTATION_INCREMENT 5

/* Define PARAGRAPH_START_INDENT to be the amount of indentation that
   the first lines of paragraphs receive by default, where no other
   value has been specified.  Users can change this value on the command
   line, with the +paragraph-indent option, or within the texinfo file,
   with the @paragraphindent command. */
#define PARAGRAPH_START_INDENT 3

/* Define DEFAULT_PARAGRAPH_SPACING as the number of blank lines that you
   wish to appear between paragraphs.  A value of 1 creates a single blank
   line between paragraphs.  Paragraphs are defined by 2 or more consecutive
   newlines in the input file (i.e., one or more blank lines). */
#define DEFAULT_PARAGRAPH_SPACING 1

/* **************************************************************** */
/*								    */
/*			Include File Declarations       	    */
/*								    */
/* **************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/stat.h>
#include <ctype.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>

#include <memory.h>

#define DONTCARE 0

#ifdef sequent
#define strchr(s,c) index(s,c)
#define strrchr(s,c) rindex(s,c)
#endif

#if defined (VMS)
#include <perror.h>
#endif

#include <time.h>
#include <fcntl.h>
#include <sys/file.h>

#include "getopt.h"
#include "../../../config.h"
#include "eliproto.h"

/* Forward declarations. */
void *xmalloc (), *xrealloc ();
void write_tag_table();

/* Non-zero means that we are currently hacking the insides of an
   insertion which would use a fixed width font. */
static int in_fixed_width_font = 0;

/* Non-zero means that start_paragraph () MUST be called before we pay
   any attention to close_paragraph () calls. */
int must_start_paragraph = 0;

/* Some systems don't declare this function in pwd.h. */
struct passwd *getpwnam ();


/* **************************************************************** */
/*								    */
/*			      Global Defines  			    */
/*								    */
/* **************************************************************** */

/* Error levels */
#define NO_ERROR 0
#define SYNTAX	 2
#define FATAL	 4

/* How to allocate permanent storage for STRING. */
#define savestring(x) \
  ((char *)strcpy ((char *)xmalloc (1 + ((x) ? strlen (x) : 0)), \
		   (x) ? (x) : ""))

/* C's standard macros don't check to make sure that the characters being
   changed are within range.  So I have to check explicitly. */

/* GNU Library doesn't have toupper().  Until GNU gets this fixed, I will
   have to do it. */
#ifndef toupper
#define toupper(c) ((c) - 32)
#endif

#define coerce_to_upper(c) ((islower(c) ? toupper(c) : (c)))
#define coerce_to_lower(c) ((isupper(c) ? tolower(c) : (c)))

#define control_character_bit 0x40 /* %01000000, must be off. */
#define meta_character_bit 0x080/* %10000000, must be on.  */
#define CTL(c) ((c) & (~control_character_bit))
#define UNCTL(c) coerce_to_upper(((c)|control_character_bit))
#define META(c) ((c) | (meta_character_bit))
#define UNMETA(c) ((c) & (~meta_character_bit))

#define whitespace(c) (((c) == '\t') || ((c) == ' '))
#define sentence_ender(c) ((c) == '.' || (c) == '?' || (c) == '!')
#define cr_or_whitespace(c) (((c) == '\t') || ((c) == ' ') || ((c) == '\n'))

#ifndef isletter
#define isletter(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))
#endif

#ifndef isupper
#define isupper(c) ((c) >= 'A' && (c) <= 'Z')
#endif

#ifndef isdigit
#define isdigit(c)  ((c) >= '0' && (c) <= '9')
#endif

#ifndef digit_value
#define digit_value(c) ((c) - '0')
#endif

#define member(c, s) (strchr (s, c) != (char *)0)

#define COMMAND_PREFIX '@'

/* Stuff for splitting large files. */
#define SPLIT_SIZE_THRESHOLD 70000	/* What's good enough for Stallman... */
#define DEFAULT_SPLIT_SIZE 50000/* Is probably good enough for me. */
int splitting = 1;		/* Always true for now. */

typedef int FUNCTION ();	/* So I can say FUNCTION *foo; */

#define SHELL "/bin/sh"		/* A sensible default */


/* **************************************************************** */
/*								    */
/*			    Global Variables			    */
/*								    */
/* **************************************************************** */

/* Global pointer to argv[0]. */
char *progname;

/* The current input file state. */
char *input_filename;
char *input_text;
int size_of_input_text;
int input_text_offset;
int line_number;

#define curchar() input_text[input_text_offset]

#define command_char(c) ((!whitespace(c)) && \
			 ((c) != '\n') && \
			 ((c) != '{') && \
			 ((c) != '}'))

#define skip_whitespace() while (input_text_offset != size_of_input_text \
				 && whitespace(curchar()))\
  input_text_offset++

/* Return non-zero if STRING is the text at input_text + input_text_offset,
   else zero. */
#define looking_at(string) \
  (strncmp (input_text + input_text_offset, string, strlen (string)) == 0)

char exec_string[4000];

/* And writing to the output. */

/* The output file name. */
char *output_filename = (char *)0;
char *pretty_output_filename;

/* Name of the output file that the user elected to pass on the command line.
   Such a name overrides any name found with the @setfilename command. */
char *command_output_filename = (char *)0;

/* Current output stream. */
FILE *output_stream;

/* Position in the output file. */
int output_position;

/* Position of the tag table. */
int tag_table_pos;

/* Output paragraph buffer. */
unsigned char *output_paragraph;

/* Offset into OUTPUT_PARAGRAPH. */
int output_paragraph_offset;

/* The output paragraph "cursor" horizontal position. */
int output_column = 0;

/* Non-zero means output_paragraph contains text. */
int paragraph_is_open = 0;

#define INITIAL_PARAGRAPH_SPACE 5000
int paragraph_buffer_len = INITIAL_PARAGRAPH_SPACE;

/* Filling.. */
/* Non-zero indicates that filling will take place on long lines. */
int filling_enabled = 1;

/* Non-zero means that words are not to be split, even in long lines.  This
   gets changed for cm_w (). */
int non_splitting_words = 0;

/* Non-zero indicates that filling a line also indents the new line. */
int indented_fill = 0;

/* The column at which long lines are broken. */
int fill_column = 72;

/* The amount of indentation to apply at the start of each line. */
int current_indent = 0;

/* The amount of indentation to add at the starts of paragraphs.
   0 means don't change existing indentation at paragraph starts.
   > 0 is amount to indent new paragraphs by.
   < 0 means indent to column zero by removing indentation if necessary.

   This is normally zero, but some people prefer paragraph starts to be
   somewhat more indented than paragraph bodies.  A pretty value for
   this is 3. */
int paragraph_start_indent = PARAGRAPH_START_INDENT;

/* Non-zero means that the use of paragraph_start_indent is inhibited.
   @example uses this to line up the left columns of the example text.
   A negative value for this variable is incremented each time it is used.
   @noindent uses this to inhibit indentation for a single paragraph.  */
int inhibit_paragraph_indentation = 0;

/* Indentation that is pending insertion.  We have this for hacking lines
   which look blank, but contain whitespace.  We want to treat those as
   blank lines. */
int pending_indent = 0;

/* The amount that indentation increases/decreases by. */
int default_indentation_increment = DEFAULT_INDENTATION_INCREMENT;

/* Non-zero indicates that indentation is temporarily turned off. */
int no_indent = 1;

/* Non-zero means forcing output text to be flushright. */
int force_flush_right = 0;

/* Non-zero means that the footnote style for this document was set on
   the command line, which overrides any other settings. */
int footnote_style_preset = 0;

/* Non-zero means that we automatically number footnotes that have no
   specified marker. */
int number_footnotes = 1;

/* The current footnote number in this node.  Each time a new node is
   started this is reset to 1. */
int current_footnote_number = 1;

/* Whether we have had an @egfiles command in the current node or not. */
int have_had_run = 0;
int have_had_egfiles = 0;

/* Command name in the process of being hacked. */
char *command;

/* The index in our internal command table of the currently
   executing command. */
int command_index;

/* A stack of file information records.  If a new file is read in with
   "@input", we remember the old input file state on this stack. */
typedef struct fstack
{
  struct fstack *next;
  char *filename;
  char *text;
  int size;
  int offset;
  int line_number;
} FSTACK;

FSTACK *filestack = (FSTACK *) 0;

/* Stuff for nodes. */
/* The current nodes node name. */
char *current_node = (char *)0;

/* The current nodes section level. */
int current_section = 0;

/* The filename of the current input file.  This is never freed. */
char *node_filename = (char *)0;

/* What we remember for each node. */
typedef struct tentry
{
  struct tentry *next_ent;
  char *node;		/* name of this node. */
  char *prev;		/* name of "Prev:" for this node. */
  char *next;		/* name of "Next:" for this node. */
  char *up;		/* name of "Up:" for this node.   */
  int position;		/* output file position of this node. */
  int line_no;		/* defining line in source file. */
  char *filename;	/* The file that this node was found in. */
  int touched;		/* non-zero means this node has been referenced. */
  int flags;		/* Room for growth.  Right now, contains 1 bit. */
} TAG_ENTRY;

/* If node-a has a "Next" for node-b, but node-b has no "Prev" for node-a,
   we turn on this flag bit in node-b's tag entry.  This means that when
   it is time to validate node-b, we don't report an additional error
   if there was no "Prev" field. */
#define PREV_ERROR 0x1
#define NEXT_ERROR 0x2
#define UP_ERROR   0x4
#define NO_WARN	   0x8
#define IS_TOP 	   0x10

TAG_ENTRY *tag_table = (TAG_ENTRY *) 0;

#define HAVE_MACROS
#if defined (HAVE_MACROS)
/* Macro definitions for user-defined commands. */
typedef struct {
  char *name;			/* Name of the macro. */
  char *definition;		/* Definition text. */
  char *filename;		/* File where this macro is defined. */
  int lineno;			/* Line number within FILENAME. */
} MACRO_DEF;

void add_macro (), execute_macro ();
MACRO_DEF *find_macro (), *delete_macro ();
#endif /* HAVE_MACROS */

/* Menu reference, *note reference, and validation hacking. */

/* The various references that we know about. */
enum reftype
{
  menu_reference, followed_reference
};

/* A structure to remember references with.  A reference to a node is
   either an entry in a menu, or a cross-reference made with [px]ref. */
typedef struct node_ref
{
  struct node_ref *next;
  char *node;			/* Name of node referred to. */
  char *containing_node;	/* Name of node containing this reference. */
  int line_no;			/* Line number where the reference occurs. */
  int section;			/* Section level where the reference occurs. */
  char *filename;		/* Name of file where the reference occurs. */
  enum reftype type;		/* Type of reference, either menu or note. */
} NODE_REF;

/* The linked list of such structures. */
NODE_REF *node_references = (NODE_REF *) 0;

/* Flag which tells us whether to examine menu lines or not. */
int in_menu = 0;

/* Flags controlling the operation of the program. */

/* Default is to notify users of bad choices. */
int print_warnings = 1;

/* Default is to check node references. */
int validating = 1;

/* Non-zero means do not output "Node: Foo" for node separations. */
int no_headers = 0;

/* Number of errors that we tolerate on a given fileset. */
int max_error_level = 100;

/* Maximum number of references to a single node before complaining. */
int reference_warning_limit = 1000;

/* Non-zero means print out information about what is going on when it
   is going on. */
int verbose_mode = 0;

/* The list of commands that we hack in texinfo.  Each one
   has an associated function.  When the command is encountered in the
   text, the associated function is called with START as the argument.
   If the function expects arguments in braces, it remembers itself on
   the stack.  When the corresponding close brace is encountered, the
   function is called with END as the argument. */

#define START 0
#define END 1

typedef struct brace_element
{
  struct brace_element *next;
  FUNCTION *proc;
  int pos, line;
} BRACE_ELEMENT;

BRACE_ELEMENT *brace_stack = (BRACE_ELEMENT *) 0;

/* Forward declarations. */

int
cm_tex (), cm_asterisk (), cm_dots (), cm_bullet (),
cm_TeX (), cm_copyright (), cm_code (), cm_samp (), cm_file (), cm_kbd (),
cm_key (), cm_ctrl (), cm_var (), cm_dfn (), cm_emph (), cm_strong (),
cm_cite (), cm_italic (), cm_bold (), cm_roman (), cm_title (), cm_w (),
cm_refill (), cm_titlefont ();

int
cm_chapter (), cm_unnumbered (), cm_appendix (), cm_top (),
cm_section (), cm_unnumberedsec (), cm_appendixsec (),
cm_subsection (), cm_unnumberedsubsec (), cm_appendixsubsec (),
cm_subsubsection (), cm_unnumberedsubsubsec (), cm_appendixsubsubsec (),
cm_heading (), cm_chapheading (), cm_subheading (), cm_subsubheading (),
cm_majorheading ();

/* All @defxxx commands map to cm_defun (). */
int cm_defun ();

int
  cm_node (), cm_menu (), cm_xref (), cm_ftable (), cm_vtable (), cm_pxref (),
  cm_inforef (), cm_quotation (), cm_display (), cm_smalldisplay (),
  cm_itemize (), cm_enumerate (), cm_table (), cm_itemx (), cm_noindent (),
  cm_setfilename (), cm_comment (), cm_br (), cm_sp (), cm_page (),
  cm_group (), cm_need (), cm_center (), cm_include (), cm_bye (),
  cm_item (), cm_end (), cm_infoinclude (), cm_ifinfo (), cm_ifnottex (),
  cm_kindex (), cm_cindex (), cm_findex (), cm_pindex (), cm_vindex (),
  cm_tindex (), cm_asis (), cm_synindex (), cm_settitle (),
  cm_setchapternewpage (), cm_printindex (), cm_minus (), cm_footnote (),
  cm_force_abbreviated_whitespace (), cm_example (), cm_smallexample (),
  cm_lisp (), cm_format (), cm_exdent (), cm_defindex (), cm_defcodeindex (),
  cm_sc (), cm_result (), cm_expansion (), cm_equiv (), cm_print (),
  cm_error (), cm_point (), cm_smallbook (), cm_headings (), cm_today (),
  cm_flushleft (),  cm_flushright (), cm_smalllisp (), cm_finalout (),
  cm_math (), cm_cartouche (), cm_ignore_sentence_ender ();

/* Conditionals. */
int cm_set (), cm_clear (), cm_ifset (), cm_ifclear ();

#if defined (HAVE_MACROS)
/* Define a user-defined command which is simple substitution. */
int cm_macro (), cm_unmacro ();
#endif /* HAVE_MACROS */

/* Options. */
int cm_paragraphindent (), cm_footnotestyle ();

/* Examples */
int cm_eg(), cm_egfiles(), cm_run();

/* Internals. */
int cm_obsolete ();
int validate (char*, int, char*);
int misplaced_brace ();
int insert_self ();
int do_nothing ();
int command_name_condition ();
int set_paragraph_indent (char*);
int set_footnote_style (char*);
int self_delimiting (int);
int search_forward (char*, int);

void push_node_filename ();
void pop_node_filename ();
void add_char (int);
void close_insertion_paragraph ();
void close_paragraph ();
void close_paragraph_with_lines (int);
void convert (char*);
void define_user_command (char*, FUNCTION, int);
void do_flush_right_indentation ();
void execute_string();
void flush_output ();
void free_node_references ();
void free_pending_notes ();
void gen_defindex (int);
void handle_variable (int);
void ignore_blank_line ();
void indent (int);
void init_indices ();
void init_insertion_stack ();
void init_internals ();
void init_paragraph ();
void init_tag_table ();
void insert (int);
void normalize_node_name (char*);
void output_pending_notes ();
void pop_insertion ();
void print_version_info ();
void read_command ();
void reader_loop ();
void remember_brace_1 (FUNCTION*, int);
void split_file (char*, int);
void start_paragraph ();
void usage ();
void validate_file (char*, TAG_ENTRY *);
void validate_other_references ( register NODE_REF *);

typedef struct
{
  char *name;
  FUNCTION *proc;
  int argument_in_braces;
} COMMAND;

/* Stuff for defining commands on the fly. */
COMMAND **user_command_array = (COMMAND **) 0;
int user_command_array_len = 0;

#define NO_BRACE_ARGS 0
#define BRACE_ARGS 1

static COMMAND CommandTable[] = {
  { "!", cm_ignore_sentence_ender, NO_BRACE_ARGS },
  { "'", insert_self, NO_BRACE_ARGS },
  { "*", cm_asterisk, NO_BRACE_ARGS },
  { ".", cm_ignore_sentence_ender, NO_BRACE_ARGS },
  { ":", cm_force_abbreviated_whitespace, NO_BRACE_ARGS },
  { "?", cm_ignore_sentence_ender, NO_BRACE_ARGS },
  { "@", insert_self, NO_BRACE_ARGS },
  { " ", insert_self, NO_BRACE_ARGS },
  { "\n", insert_self, NO_BRACE_ARGS },
  { "TeX", cm_TeX, BRACE_ARGS },
  { "`", insert_self, NO_BRACE_ARGS },
  { "appendix", cm_appendix, NO_BRACE_ARGS },
  { "appendixsection", cm_appendixsec, NO_BRACE_ARGS },
  { "appendixsec", cm_appendixsec, NO_BRACE_ARGS },
  { "appendixsubsec", cm_appendixsubsec, NO_BRACE_ARGS },
  { "appendixsubsubsec", cm_appendixsubsubsec, NO_BRACE_ARGS },
  { "asis", cm_asis, BRACE_ARGS },
  { "b", cm_bold, BRACE_ARGS },
  { "br", cm_br, NO_BRACE_ARGS },
  { "bullet", cm_bullet, BRACE_ARGS },
  { "bye", cm_bye, NO_BRACE_ARGS },
  { "c", cm_comment, NO_BRACE_ARGS },
  { "cartouche", cm_cartouche, NO_BRACE_ARGS },
  { "center", cm_center, NO_BRACE_ARGS },
  { "chapheading", cm_chapheading, NO_BRACE_ARGS },
  { "chapter", cm_chapter, NO_BRACE_ARGS },
  { "cindex", cm_cindex, NO_BRACE_ARGS },
  { "cite", cm_cite, BRACE_ARGS },
  { "clear", cm_clear, NO_BRACE_ARGS },
  { "code", cm_code, BRACE_ARGS },
  { "comment", cm_comment, NO_BRACE_ARGS },
  { "contents", do_nothing, NO_BRACE_ARGS },
  { "copyright", cm_copyright, BRACE_ARGS },
  { "ctrl", cm_ctrl, BRACE_ARGS },
  { "defcodeindex", cm_defcodeindex, NO_BRACE_ARGS },
  { "defindex", cm_defindex, NO_BRACE_ARGS },
  { "dfn", cm_dfn, BRACE_ARGS },

/* The `def' commands. */
  { "deffn", cm_defun, NO_BRACE_ARGS },
  { "deffnx", cm_defun, NO_BRACE_ARGS },
  { "defun", cm_defun, NO_BRACE_ARGS },
  { "defunx", cm_defun, NO_BRACE_ARGS },
  { "defmac", cm_defun, NO_BRACE_ARGS },
  { "defmacx", cm_defun, NO_BRACE_ARGS },
  { "defspec", cm_defun, NO_BRACE_ARGS },
  { "defspecx", cm_defun, NO_BRACE_ARGS },
  { "defvr", cm_defun, NO_BRACE_ARGS },
  { "defvrx", cm_defun, NO_BRACE_ARGS },
  { "defvar", cm_defun, NO_BRACE_ARGS },
  { "defvarx", cm_defun, NO_BRACE_ARGS },
  { "defopt", cm_defun, NO_BRACE_ARGS },
  { "defoptx", cm_defun, NO_BRACE_ARGS },
  { "deftypefn", cm_defun, NO_BRACE_ARGS },
  { "deftypefnx", cm_defun, NO_BRACE_ARGS },
  { "deftypefun", cm_defun, NO_BRACE_ARGS },
  { "deftypefunx", cm_defun, NO_BRACE_ARGS },
  { "deftypevr", cm_defun, NO_BRACE_ARGS },
  { "deftypevrx", cm_defun, NO_BRACE_ARGS },
  { "deftypevar", cm_defun, NO_BRACE_ARGS },
  { "deftypevarx", cm_defun, NO_BRACE_ARGS },
  { "defcv", cm_defun, NO_BRACE_ARGS },
  { "defcvx", cm_defun, NO_BRACE_ARGS },
  { "defivar", cm_defun, NO_BRACE_ARGS },
  { "defivarx", cm_defun, NO_BRACE_ARGS },
  { "defop", cm_defun, NO_BRACE_ARGS },
  { "defopx", cm_defun, NO_BRACE_ARGS },
  { "defmethod", cm_defun, NO_BRACE_ARGS },
  { "defmethodx", cm_defun, NO_BRACE_ARGS },
  { "deftypemethod", cm_defun, NO_BRACE_ARGS },
  { "deftypemethodx", cm_defun, NO_BRACE_ARGS },
  { "deftp", cm_defun, NO_BRACE_ARGS },
  { "deftpx", cm_defun, NO_BRACE_ARGS },
/* The end of the `def' commands. */

  { "display", cm_display, NO_BRACE_ARGS },
  { "dots", cm_dots, BRACE_ARGS },
  { "dmn", do_nothing, BRACE_ARGS },
  { "eg", cm_eg, NO_BRACE_ARGS },
  { "egfiles", cm_egfiles, NO_BRACE_ARGS },
  { "emph", cm_emph, BRACE_ARGS },
  { "end", cm_end, NO_BRACE_ARGS },
  { "enumerate", cm_enumerate, NO_BRACE_ARGS },
  { "equiv", cm_equiv, BRACE_ARGS },
  { "error", cm_error, BRACE_ARGS },
  { "example", cm_example, NO_BRACE_ARGS },
  { "exdent", cm_exdent, NO_BRACE_ARGS },
  { "expansion", cm_expansion, BRACE_ARGS },
  { "file", cm_file, BRACE_ARGS },
  { "findex", cm_findex, NO_BRACE_ARGS },
  { "finalout", do_nothing, NO_BRACE_ARGS },
  { "flushleft", cm_flushleft, NO_BRACE_ARGS },
  { "flushright", cm_flushright, NO_BRACE_ARGS },
  { "format", cm_format, NO_BRACE_ARGS },
  { "ftable", cm_ftable, NO_BRACE_ARGS },
  { "group", cm_group, NO_BRACE_ARGS },
  { "heading", cm_heading, NO_BRACE_ARGS },
  { "headings", cm_headings, NO_BRACE_ARGS },
  { "i", cm_italic, BRACE_ARGS },
  { "iappendix", cm_appendix, NO_BRACE_ARGS },
  { "iappendixsection", cm_appendixsec, NO_BRACE_ARGS },
  { "iappendixsec", cm_appendixsec, NO_BRACE_ARGS },
  { "iappendixsubsec", cm_appendixsubsec, NO_BRACE_ARGS },
  { "iappendixsubsubsec", cm_appendixsubsubsec, NO_BRACE_ARGS },
  { "ichapter", cm_chapter, NO_BRACE_ARGS },
  { "ifclear", cm_ifclear, NO_BRACE_ARGS },
  { "ifinfo", cm_ifinfo, NO_BRACE_ARGS },
  { "ifnotinfo", command_name_condition, NO_BRACE_ARGS },
  { "ifnottex", cm_ifnottex, NO_BRACE_ARGS },
  { "ifset", cm_ifset, NO_BRACE_ARGS },
  { "iftex", command_name_condition, NO_BRACE_ARGS },
  { "ignore", command_name_condition, NO_BRACE_ARGS },
  { "include", cm_include, NO_BRACE_ARGS },
  { "inforef", cm_inforef, BRACE_ARGS },
  { "input", cm_include, NO_BRACE_ARGS },
  { "isection", cm_section, NO_BRACE_ARGS },
  { "isubsection", cm_subsection, NO_BRACE_ARGS },
  { "isubsubsection", cm_subsubsection, NO_BRACE_ARGS },
  { "item", cm_item, NO_BRACE_ARGS },
  { "itemize", cm_itemize, NO_BRACE_ARGS },
  { "itemx", cm_itemx, NO_BRACE_ARGS },
  { "iunnumbered", cm_unnumbered, NO_BRACE_ARGS },
  { "iunnumberedsec", cm_unnumberedsec, NO_BRACE_ARGS },
  { "iunnumberedsubsec", cm_unnumberedsubsec, NO_BRACE_ARGS },
  { "iunnumberedsubsubsec", cm_unnumberedsubsubsec, NO_BRACE_ARGS },
  { "kbd", cm_kbd, BRACE_ARGS },
  { "key", cm_key, BRACE_ARGS },
  { "kindex", cm_kindex, NO_BRACE_ARGS },
  { "lisp", cm_lisp, NO_BRACE_ARGS },
  { "macro", cm_macro, NO_BRACE_ARGS },
  { "majorheading", cm_majorheading, NO_BRACE_ARGS },
  { "math", cm_math, BRACE_ARGS },
  { "menu", cm_menu, NO_BRACE_ARGS },
  { "minus", cm_minus, BRACE_ARGS },
  { "need", cm_need, NO_BRACE_ARGS },
  { "node", cm_node, NO_BRACE_ARGS },
  { "nodetitle", cm_subsubsection, NO_BRACE_ARGS },
  { "noindent", cm_noindent, NO_BRACE_ARGS },
  { "nwnode", cm_node, NO_BRACE_ARGS },
  { "page", do_nothing, NO_BRACE_ARGS },
  { "pindex", cm_pindex, NO_BRACE_ARGS },
  { "point", cm_point, BRACE_ARGS },
  { "print", cm_print, BRACE_ARGS },
  { "printindex", cm_printindex, NO_BRACE_ARGS },
  { "pxref", cm_pxref, BRACE_ARGS },
  { "quotation", cm_quotation, NO_BRACE_ARGS },
  { "r", cm_roman, BRACE_ARGS },
  { "ref", cm_xref, BRACE_ARGS },
  { "refill", cm_refill, NO_BRACE_ARGS },
  { "result", cm_result, BRACE_ARGS },
  { "run", cm_run, NO_BRACE_ARGS },
  { "samp", cm_samp, BRACE_ARGS },
  { "sc", cm_sc, BRACE_ARGS },
  { "section", cm_section, NO_BRACE_ARGS },
  { "set", cm_set, NO_BRACE_ARGS },
  { "setchapternewpage", cm_setchapternewpage, NO_BRACE_ARGS },
  { "setfilename", cm_setfilename, NO_BRACE_ARGS },
  { "settitle", cm_settitle, NO_BRACE_ARGS },
  { "shortcontents", do_nothing, NO_BRACE_ARGS },
  { "smallbook", cm_smallbook, NO_BRACE_ARGS },
  { "smalldisplay", cm_smalldisplay, NO_BRACE_ARGS },
  { "smallexample", cm_smallexample, NO_BRACE_ARGS },
  { "smalllisp", cm_smalllisp, NO_BRACE_ARGS },
  { "sp", cm_sp, NO_BRACE_ARGS },
  { "strong", cm_strong, BRACE_ARGS },
  { "subheading", cm_subheading, NO_BRACE_ARGS },
  { "subsection", cm_subsection, NO_BRACE_ARGS },
  { "subsubheading", cm_subsubheading, NO_BRACE_ARGS },
  { "subsubsection", cm_subsubsection, NO_BRACE_ARGS },
  { "summarycontents", do_nothing, NO_BRACE_ARGS },
  { "syncodeindex", cm_synindex, NO_BRACE_ARGS },
  { "synindex", cm_synindex, NO_BRACE_ARGS },
  { "t", cm_title, BRACE_ARGS },
  { "table", cm_table, NO_BRACE_ARGS },
  { "tex", command_name_condition, NO_BRACE_ARGS },
  { "tindex", cm_tindex, NO_BRACE_ARGS },
  { "titlefont", cm_titlefont, BRACE_ARGS },
  { "titlepage", command_name_condition, NO_BRACE_ARGS },
  { "titlespec", command_name_condition, NO_BRACE_ARGS },
  { "today", cm_today, BRACE_ARGS },
  { "top", cm_top, NO_BRACE_ARGS  },
  { "unmacro", cm_unmacro, NO_BRACE_ARGS },
  { "unnumbered", cm_unnumbered, NO_BRACE_ARGS },
  { "unnumberedsec", cm_unnumberedsec, NO_BRACE_ARGS },
  { "unnumberedsubsec", cm_unnumberedsubsec, NO_BRACE_ARGS },
  { "unnumberedsubsubsec", cm_unnumberedsubsubsec, NO_BRACE_ARGS },
  { "var", cm_var, BRACE_ARGS },
  { "vindex", cm_vindex, NO_BRACE_ARGS },
  { "vtable", cm_vtable, NO_BRACE_ARGS },
  { "w", cm_w, BRACE_ARGS },
  { "xref", cm_xref, BRACE_ARGS },
  { "{", insert_self, NO_BRACE_ARGS },
  { "}", insert_self, NO_BRACE_ARGS },

  /* Some obsoleted commands. */
  { "infotop", cm_obsolete, NO_BRACE_ARGS },
  { "infounnumbered", cm_obsolete, NO_BRACE_ARGS },
  { "infounnumberedsec", cm_obsolete, NO_BRACE_ARGS },
  { "infounnumberedsubsec", cm_obsolete, NO_BRACE_ARGS },
  { "infounnumberedsubsubsec", cm_obsolete, NO_BRACE_ARGS },
  { "infoappendix", cm_obsolete, NO_BRACE_ARGS },
  { "infoappendixsec", cm_obsolete, NO_BRACE_ARGS },
  { "infoappendixsubsec", cm_obsolete, NO_BRACE_ARGS },
  { "infoappendixsubsubsec", cm_obsolete, NO_BRACE_ARGS },
  { "infochapter", cm_obsolete, NO_BRACE_ARGS },
  { "infosection", cm_obsolete, NO_BRACE_ARGS },
  { "infosubsection", cm_obsolete, NO_BRACE_ARGS },
  { "infosubsubsection", cm_obsolete, NO_BRACE_ARGS },

  /* Now @include does what this was supposed to. */
  { "infoinclude", cm_infoinclude, NO_BRACE_ARGS },
  { "footnote", cm_footnote, NO_BRACE_ARGS}, /* self-arg eater */
  { "footnotestyle", cm_footnotestyle, NO_BRACE_ARGS },
  { "paragraphindent", cm_paragraphindent, NO_BRACE_ARGS },

  {(char *) 0, (FUNCTION *) 0}, NO_BRACE_ARGS};

int major_version = 1;
int minor_version = 43;

struct option long_options[] =
{
  { "error-limit", 1, 0, 'e' },			/* formerly -el */
  { "fill-column", 1, 0, 'f' },			/* formerly -fc */
  { "footnote-style", 1, 0, 's' },		/* formerly -ft */
  { "no-headers", 0, &no_headers, 1 },		/* Do not output Node: foo */
  { "no-pointer-validate", 0, &validating, 0 }, /* formerly -nv */
  { "no-split", 0, &splitting, 0 },		/* formerly -ns */
  { "no-validate", 0, &validating, 0 },		/* formerly -nv */
  { "no-warn", 0, &print_warnings, 0 },		/* formerly -nw */
  { "number-footnotes", 0, &number_footnotes, 1 },
  { "no-number-footnotes", 0, &number_footnotes, 0 },
  { "output", 1, 0, 'o' },
  { "paragraph-indent", 1, 0, 'p' },		/* formerly -pi */
  { "reference-limit", 1, 0, 'r' },		/* formerly -rl */
  { "verbose", 0, &verbose_mode, 1 },		/* formerly -verbose */
  { "version", 0, 0, 'V' },
  {(char *)0, 0, 0, 0}
};

/* **************************************************************** */
/*								    */
/*			Main ()  Start of code  		    */
/*					        		    */
/* **************************************************************** */

/* For each file mentioned in the command line, process it, turning
   texinfo commands into wonderfully formatted output text. */
int
main (argc, argv)
     int argc;
     char **argv;
{
  extern int errors_printed;
  char *filename_part ();
  int c, ind;

  /* The name of this program is the last filename in argv[0]. */
  progname = filename_part (argv[0]);

  /* Parse argument flags from the input line. */
  while ((c = getopt_long (argc, argv, "f:o:p:e:r:s:V", long_options, &ind))
	 != EOF)
    {
      if (c == 0 && long_options[ind].flag == 0)
	c = long_options[ind].val;

      switch (c)
	{
	  /* User specified fill_column? */
	case 'f':
	  if (sscanf (optarg, "%d", &fill_column) != 1)
	    usage ();
	  break;

	  /* User specified output file? */
	case 'o':
	  command_output_filename = savestring (optarg);
	  break;

	  /* User specified paragraph indent (paragraph_start_index)? */
	case 'p':
	  if (set_paragraph_indent (optarg) < 0)
	    usage ();
	  break;

	  /* User specified error level? */
	case 'e':
	  if (sscanf (optarg, "%d", &max_error_level) != 1)
	    usage ();
	  break;

	  /* User specified reference warning limit? */
	case 'r':
	  if (sscanf (optarg, "%d", &reference_warning_limit) != 1)
	    usage ();
	  break;

	  /* User specified footnote style? */
	case 's':
	  if (set_footnote_style (optarg) < 0)
	    usage ();
	  footnote_style_preset = 1;
	  break;

	  /* User requested version info? */
	case 'V':
	  print_version_info ();
	  exit (NO_ERROR);
	  break;

	case '?':
	  usage ();
	}
    }

  if (optind == argc)
    usage ();
  else if (verbose_mode)
    print_version_info ();

  /* Remaining arguments are file names of texinfo files.
     Convert them, one by one. */
  while (optind != argc)
    convert (argv[optind++]);

  if (errors_printed) return SYNTAX; else return NO_ERROR;
}

/* Display the version info of this invocation of Makeinfo. */
void
print_version_info ()
{
  (void)fprintf (stderr, "This is GNU Makeinfo version %d.%d.\n",
	   major_version, minor_version);
}

/* **************************************************************** */
/*								    */
/*			Generic Utilities			    */
/*								    */
/* **************************************************************** */

void
memory_error(callers_name, bytes_wanted)
     char *callers_name;
     int bytes_wanted;
{
  (void)fprintf(stderr,
    "Virtual memory exhausted in %s ()!  Needed %d bytes.\n",
	   callers_name, bytes_wanted);
  abort ();
}

/* Just like malloc, but kills the program in case of fatal error. */
void *
xmalloc (nbytes)
     int nbytes;
{
  void *temp = (void *) malloc((size_t)nbytes);

  if (nbytes && temp == (void *)0)
    memory_error("xmalloc", nbytes);

  return (temp);
}

/* Like realloc (), but barfs if there isn't enough memory. */
void *
xrealloc (pointer, nbytes)
     char *pointer;
     int nbytes;
{
  void *temp;

  if (!pointer)
    temp = (void *)xmalloc (nbytes);
  else
    temp = (void *)realloc (pointer, nbytes);

  if (nbytes && !temp)
    memory_error("xrealloc", nbytes);

  return (temp);
}

/* Tell the user how to use this program. */
void
usage ()
{
  (void)fprintf (stderr, "Usage: %s [options] texinfo-file...\n\
\n\
This program accepts as input files of texinfo commands and text\n\
and outputs a file suitable for reading with GNU Info.\n\
\n\
The options are:\n\
`+no-validate' to suppress node cross reference validation.\n\
`+no-warn' to suppress warning messages (errors are still output).\n\
`+no-split' to suppress the splitting of large files.\n\
`+no-headers' to suppress the output of Node: Foo headers.\n\
`+verbose' to print information about what is being done.\n\
`+version' to print the version number of Makeinfo.\n\
`+paragraph-indent NUM' to set the paragraph indent to NUM (default %d).\n\
`+fill-column NUM' to set the filling column to NUM (default %d).\n\
`+error-limit NUM' to set the error limit to NUM (default %d).\n\
`+reference-limit NUM' to set the reference warning limit to NUM (default %d).\n\
`+footnote-style STYLE' to set the footnote style to STYLE.  STYLE should\n\
  either be `separate' to place footnotes in their own node, or\n\
  `end', to place the footnotes at the end of the node in which they are\n\
   defined (the default).\n\n",
	   progname, paragraph_start_indent,
	   fill_column, max_error_level, reference_warning_limit);
  exit (FATAL);
}

/* **************************************************************** */
/*								    */
/*			Manipulating Lists      		    */
/*					        		    */
/* **************************************************************** */

typedef struct generic_list
{
  struct generic_list *next;
}            GENERIC_LIST;

/* Reverse the chain of structures in LIST.  Output the new head
   of the chain.  You should always assign the output value of this
   function to something, or you will lose the chain. */
GENERIC_LIST *
reverse_list (list)
     register GENERIC_LIST *list;
{
  register GENERIC_LIST *next;
  register GENERIC_LIST *prev = (GENERIC_LIST *) 0;

  while (list)
    {
      next = list->next;
      list->next = prev;
      prev = list;
      list = next;
    }
  return (prev);
}

void
init_brace_stack ()
{
  brace_stack = (BRACE_ELEMENT *) 0;
}

extern void line_error();

void
remember_brace (proc)
     FUNCTION *proc;
{
  if (curchar () != '{') {
    line_error();
    (void)fprintf(stderr, "@%s expected `{..}'.\n", command);
  } else input_text_offset++;
  remember_brace_1 (proc, output_paragraph_offset);
}

/* Remember the current output position here.  Save PROC
   along with it so you can call it later. */
void
remember_brace_1 (proc, position)
     FUNCTION *proc;
     int position;
{
  BRACE_ELEMENT *new = (BRACE_ELEMENT *) xmalloc (sizeof (BRACE_ELEMENT));
  new->next = brace_stack;
  new->proc = proc;
  new->pos = position;
  new->line = line_number;
  brace_stack = new;
}

/* Pop the top of the brace stack, and call the associated function
   with the args END and POS. */
void
pop_and_call_brace ()
{
  BRACE_ELEMENT *temp;
  FUNCTION *proc;
  int pos;

  if (brace_stack == (BRACE_ELEMENT *) 0) {
    line_error();
    (void)fprintf(stderr, "Unmatched close brace.\n");
  }

  pos = brace_stack->pos;
  proc = brace_stack->proc;
  temp = brace_stack->next;
  free((char *)brace_stack);
  brace_stack = temp;

  (*proc) (END, pos, output_paragraph_offset);
}

/* Return the string which invokes PROC; a pointer to a function. */
char *
find_proc_name (proc)
     FUNCTION *proc;
{
  register int i;

  for (i = 0; CommandTable[i].name; i++)
    if (proc == CommandTable[i].proc)
      return (CommandTable[i].name);
  return ("NO_NAME!");
}

/* You call discard_braces () when you shouldn't have any braces on the stack.
   I used to think that this happens for commands that don't take arguments
   in braces, but that was wrong because of things like @code{foo @@}.  So now
   I only detect it at the beginning of nodes. */
void
discard_braces ()
{
  int temp_line_number = line_number;
  char *proc_name;

  if (!brace_stack) return;

  while (brace_stack) {
    line_number = brace_stack->line;
    proc_name = find_proc_name (brace_stack->proc);
    line_error();
    (void)fprintf(stderr, "@%s missing close brace.\n", proc_name);
    line_number = temp_line_number;
    pop_and_call_brace ();
  }
}


/* **************************************************************** */
/*								    */
/*			Pushing and Popping Files       	    */
/*								    */
/* **************************************************************** */

/* Find and load the file named FILENAME.  Return a pointer to
   the loaded file, or NULL if it can't be loaded. */
char *
find_and_load (filename)
     char *filename;
{
  struct stat fileinfo;
  int file, count = 0;
  char *result = (char *) 0;

  if (stat (filename, &fileinfo) != 0)
    goto error_exit;

  file = open (filename, O_RDONLY);
  if (file < 0)
    goto error_exit;

  /* Load the file. */
  result = (char *)xmalloc((int)fileinfo.st_size);

  /* VMS stat lies about the st_size value.  The actual number of
     readable bytes is always less than this value.  The arcane
     mysteries of VMS/RMS are too much to probe, so this hack
    suffices to make things work. */
#if defined (VMS)
  while ((n = read (file, result+count, fileinfo.st_size)) > 0)
    count += n;
  if (n == -1)
#else
#ifdef __CYGWIN__
  /* The size of a Windows text file is longer than the string read
     because the CR characters preceding LF characters are stripped
     off during the read.  We need to keep track of the actual number
     for later operations. */
    count = read (file, result, (int)fileinfo.st_size);
    if (count == -1)
#else
    count = fileinfo.st_size;
    if (read (file, result, (int)fileinfo.st_size) != fileinfo.st_size)
#endif
#endif
  error_exit:
    {
      if (result)
	free (result);
      if (file != -1)
	(void)close (file);
      return ((char *) 0);
    }
  (void)close (file);

  /* Set the globals to the new file. */
  input_text = result;
#ifdef __CYGWIN__
  size_of_input_text = count;
#else
  size_of_input_text = fileinfo.st_size;
#endif
  input_filename = savestring (filename);
  node_filename = savestring (filename);
  input_text_offset = 0;
  line_number = 1;
  return (result);
}

/* Save the state of the current input file. */
void
pushfile ()
{
  FSTACK *newstack = (FSTACK *) xmalloc (sizeof (FSTACK));
  newstack->filename = input_filename;
  newstack->text = input_text;
  newstack->size = size_of_input_text;
  newstack->offset = input_text_offset;
  newstack->line_number = line_number;
  newstack->next = filestack;

  filestack = newstack;
  push_node_filename ();
}

/* Make the current file globals be what is on top of the file stack. */
void
popfile ()
{
  extern int executing_string;
  FSTACK *temp = filestack;

  if (!filestack)
    abort ();			/* My fault.  I wonder what I did? */

  /* Make sure that commands with braces have been satisfied. */
  if (!executing_string)
    discard_braces ();

  /* Get the top of the stack into the globals. */
  input_filename = filestack->filename;
  input_text = filestack->text;
  size_of_input_text = filestack->size;
  input_text_offset = filestack->offset;
  line_number = filestack->line_number;

  /* Pop the stack. */
  filestack = filestack->next;
  free((char *)temp);
  pop_node_filename ();
}

/* Flush all open files on the file stack. */
void
flush_file_stack ()
{
  while (filestack)
    {
      free (input_filename);
      free (input_text);
      popfile ();
    }
}

int node_filename_stack_index = 0;
int node_filename_stack_size = 0;
char **node_filename_stack = (char **)0;

void
push_node_filename ()
{
  if (node_filename_stack_index + 1 > node_filename_stack_size)
    {
      if (!node_filename_stack)
	node_filename_stack =
	  (char **)xmalloc ((node_filename_stack_size += 10)
			    * sizeof (char *));
      else
	node_filename_stack =
	  (char **)xrealloc((char *)node_filename_stack,
			     (node_filename_stack_size + 10)
			     * sizeof (char *));
    }

  node_filename_stack[node_filename_stack_index] = node_filename;
  node_filename_stack_index++;
}

void
pop_node_filename ()
{
  node_filename = node_filename_stack[--node_filename_stack_index];
}

/* Return just the simple part of the filename; i.e. the
   filename without the path information, or extensions.
   This conses up a new string. */
char *
filename_part (filename)
     char *filename;
{
  register int i = strlen (filename) - 1;

  while (i && filename[i] != '/')
    i--;
  if (filename[i] == '/')
    i++;

#if defined (REMOVE_OUTPUT_EXTENSIONS)
  result = savestring (&filename[i]);

  /* See if there is an extension to remove.  If so, remove it. */
  if (strrchr (result, '.'))
    *(strrchr (result, '.')) = '\0';
  return (result);
#else
  return (savestring (&filename[i]));
#endif /* REMOVE_OUTPUT_EXTENSIONS */
}

/* Return the pathname part of filename.  This can be NULL. */
char *
pathname_part (filename)
     char *filename;
{
  char *expand_filename ();
  char *result = (char *) 0;
  register int i;

  filename = expand_filename (filename, "");

  i = strlen (filename) - 1;

  while (i && filename[i] != '/')
    i--;
  if (filename[i] == '/')
    i++;

  if (i)
    {
      result = (char *)xmalloc (1 + i);
      (void)strncpy (result, filename, i);
      result[i] = '\0';
    }
  free (filename);
  return (result);
}

/* Return the expansion of FILENAME. */
char *
expand_filename (filename, input_name)
     char *filename, *input_name;
{
  char *full_pathname ();
  filename = full_pathname (filename);

  if (filename[0] == '.')
    return (filename);

  if (filename[0] != '/' && input_name[0] == '/')
    {
      /* Make it so that relative names work. */
      char *result;
      int i = strlen (input_name) - 1;

      result = (char *)xmalloc (1 + strlen (input_name) + strlen (filename));
      (void)strcpy (result, input_name);

      while (result[i] != '/' && i)
	i--;

      if (result[i] == '/')
	i++;

      (void)strcpy (&result[i], filename);
      free (filename);
      return (result);
    }
  return (filename);
}

/* Return the full path to FILENAME. */
char *
full_pathname (filename)
     char *filename;
{
  int initial_character;

  if (filename && (initial_character = *filename))
    {
      if (initial_character == '/')
	return (savestring (filename));
      if (initial_character != '~')
	{
	  return (savestring (filename));
	}
      else
	{
	  if (filename[1] == '/')
	    {
	      /* Return the concatenation of HOME and the rest of the string. */
	      char *temp_home;
	      char *temp_name;

	      temp_home = (char *) getenv ("HOME");
	      temp_name = (char *)xmalloc (strlen (&filename[2])
					   + 1
					   + temp_home ? strlen (temp_home)
					   : 0);
	      if (temp_home)
		(void)strcpy (temp_name, temp_home);

	      (void)strcat (temp_name, &filename[2]);
	      return (temp_name);
	    }
	  else
	    {
	      struct passwd *user_entry;
	      int i, c;
	      char *username = (char *)xmalloc (257);
	      char *temp_name;

	      for (i = 1; (c = filename[i]); i++)
		{
		  if (c == '/')
		    break;
		  else
		    username[i - 1] = c;
		}
	      if (c)
		username[i - 1] = '\0';

	      user_entry = getpwnam (username);

	      if (!user_entry)
		return (savestring (filename));

	      temp_name = (char *)xmalloc (1 + strlen (user_entry->pw_dir)
					   + strlen (&filename[i]));
	      (void)strcpy (temp_name, user_entry->pw_dir);
	      (void)strcat (temp_name, &filename[i]);
	      return (temp_name);
	    }
	}
    }
  else
    {
      return (savestring (filename));
    }
}

/* **************************************************************** */
/*								    */
/*			Error Handling				    */
/*								    */
/* **************************************************************** */

/* Number of errors encountered. */
int errors_printed = 0;

/* Remember that an error has been printed.  If this is the first
   error printed, then tell them which program is printing them.
   If more than max_error_level have been printed, then exit the
   program. */
void
remember_error()
{
  errors_printed++;
  if (max_error_level && (errors_printed > max_error_level))
    {
      (void)fprintf (stderr, "Too many errors!  Gave up.\n");
      flush_file_stack ();
      cm_bye ();
      exit (1);
    }
}

/* Print the last error gotten from the file system. */
void
fs_error(filename)
     char *filename;
{
  remember_error();
  perror(filename);
}

void
line_error()
{
  remember_error();
  (void)fprintf (stderr, "%s:%d: ", input_filename, line_number);
}

void
warning()
{
  (void)fprintf (stderr, "%s:%d: Warning: ", input_filename, line_number);
}


/* **************************************************************** */
/*								    */
/*			Hacking Tokens and Strings		    */
/*								    */
/* **************************************************************** */

/* Return the next token as a string pointer.  We cons the
   string. */
char *
read_token ()
{
  int i, character;
  char *result;

  /* Hack special case.  If the first character to be read is
     self-delimiting, then that is the command itself. */

  character = curchar ();
  if (self_delimiting (character))
    {
      input_text_offset++;
      result = savestring (" ");
      *result = character;
      return (result);
    }

  for (i = 0; ((input_text_offset != size_of_input_text)
	       && (character = curchar ())
	       && command_char (character));
       i++, input_text_offset++);
  result = (char *)xmalloc (i + 1);
  memcpy (result, &input_text[input_text_offset - i], i);
  result[i] = '\0';
  return (result);
}

/* Return non-zero if CHARACTER is self-delimiting. */
int
self_delimiting (character)
     int character;
{
  return (member (character, "{}:.@*'`,!?; \n"));
}

/* Clear whitespace from the front and end of string. */
void
canon_white (string)
     char *string;
{
  int len = strlen (string);
  int x;
  char *s;

  if (!len)
    return;

  for (x = 0; x < len; x++)
    if (!whitespace (string[x]))
      break;

  if (x > 0) {
    for (s=string+x,x=0; s[x]; x++)
      string[x] = s[x];
    string[x] = '\0';
  }

  len = strlen (string);
  if (len)
    len--;
  while (len > -1 && cr_or_whitespace (string[len]))
    len--;
  string[len + 1] = '\0';
}

/* Bash STRING, replacing all whitespace with just one space. */
void
fix_whitespace (string)
     char *string;
{
  char *temp = (char *)xmalloc (strlen (string) + 1);
  int string_index = 0;
  int temp_index = 0;
  int c;

  canon_white (string);

  while (string[string_index])
    {
      c = temp[temp_index++] = string[string_index++];

      if (c == ' ' || c == '\n' || c == '\t')
	{
	  temp[temp_index - 1] = ' ';
	  while ((c = string[string_index]) && (c == ' ' ||
						c == '\t' ||
						c == '\n'))
	    string_index++;
	}
    }
  temp[temp_index] = '\0';
  (void)strcpy (string, temp);
  free (temp);
}

/* Discard text until the desired string is found.  The string is
   included in the discarded text. */
void
discard_until (string)
     char *string;
{
  int temp = search_forward (string, input_text_offset);

  int tt = (temp < 0) ? size_of_input_text : temp + strlen (string);
  int from = input_text_offset;

  /* Find out what line we are on. */
  while (from != tt)
    if (input_text[from++] == '\n')
      line_number++;

  if (temp < 0) {
    input_text_offset = size_of_input_text - strlen (string);

    if (strcmp (string, "\n") != 0) {
      line_error();
      (void)fprintf(stderr, "Expected `%s'.\n", string);
      return;
    }
  } else input_text_offset = temp;

  input_text_offset += strlen (string);
}

/* Read characters from the file until we are at MATCH.
   Place the characters read into STRING.
   On exit input_text_offset is after the match string.
   Return the offset where the string starts. */
int
get_until (match, string)
     char *match, **string;
{
  int len, current_point, x, new_point, tem;

  current_point = x = input_text_offset;
  new_point = search_forward (match, input_text_offset);

  if (new_point < 0)
    new_point = size_of_input_text;
  len = new_point - current_point;

  /* Keep track of which line number we are at. */
  tem = new_point + (strlen (match) - 1);
  while (x != tem)
    if (input_text[x++] == '\n')
      line_number++;

  *string = (char *)xmalloc (len + 1);

  memcpy (*string, &input_text[current_point], len);
  (*string)[len] = '\0';

  /* Now leave input_text_offset in a consistent state. */
  input_text_offset = tem;

  if (input_text_offset > size_of_input_text)
    input_text_offset = size_of_input_text;

  return (new_point);
}

/* Read characters from the file until we are at MATCH or end of line.
   Place the characters read into STRING.  */
void
get_until_in_line (match, string)
     char *match, **string;
{
  int real_bottom, temp;

  real_bottom = size_of_input_text;
  temp = search_forward ("\n", input_text_offset);

  if (temp < 0)
    temp = size_of_input_text;

  size_of_input_text = temp;
  (void)get_until (match, string);
  size_of_input_text = real_bottom;
}

void
get_rest_of_line (string)
     char **string;
{
  (void)get_until ("\n", string);
  canon_white (*string);

  if (curchar () == '\n')	/* as opposed to the end of the file... */
    {
      line_number++;
      input_text_offset++;
    }
}

/* Backup the input pointer to the previous character, keeping track
   of the current line number. */
void
backup_input_pointer ()
{
  if (input_text_offset)
    {
      input_text_offset--;
      if (curchar () == '\n')
	line_number--;
    }
}

/* Read characters from the file until we are at MATCH or closing brace.
   Place the characters read into STRING.  */
void
get_until_in_braces (match, string)
     char *match, **string;
{
  int i, brace = 0;
  int match_len = strlen (match);
  char *temp;

  for (i = input_text_offset; i < size_of_input_text; i++)
    {
      if (input_text[i] == '{')
	brace++;
      else if (input_text[i] == '}')
	brace--;
      else if (input_text[i] == '\n')
	line_number++;

      if (brace < 0 ||
	  (brace == 0 && strncmp (input_text + i, match, match_len) == 0))
	break;
    }

  match_len = i - input_text_offset;
  temp = (char *)xmalloc (2 + match_len);
  (void)strncpy (temp, input_text + input_text_offset, match_len);
  temp[match_len] = '\0';
  input_text_offset = i;
  *string = temp;
}

/* Add STRING to output_paragraph. */
void
add_word (string)
     char *string;
{
  while (*string)
    add_char (*string++);
}

void
add_word_args (format, arg1, arg2, arg3, arg4)
     char *format, *arg1, *arg2; int arg3, arg4;
{
  char buffer[1000];
  (void)sprintf (buffer, format, arg1, arg2, arg3, arg4);
  add_word (buffer);
}

/* **************************************************************** */
/*								    */
/*			Converting the File     		    */
/*								    */
/* **************************************************************** */

/* Convert the file named by NAME.  The output is saved on the file
   named as the argument to the @setfilename command. */
static char *suffixes[] = {
  "",
  ".texinfo",
  ".texi",
  ".txinfo",
  (char *)0
};

void
convert (name)
     char *name;
{
  char *real_output_filename, *expand_filename (), *filename_part ();
  char *filename = (char *)xmalloc (strlen (name) + 50);
  register int i;

  init_tag_table ();
  init_indices ();
  init_internals ();
  init_paragraph ();

  /* Try to load the file specified by NAME.  If the file isn't found, and
     there is no suffix in NAME, then try NAME.texinfo, and NAME.texi. */
  for (i = 0; suffixes[i]; i++)
    {
      (void)strcpy (filename, name);
      (void)strcat (filename, suffixes[i]);

      if (find_and_load (filename))
	break;

      if (!suffixes[i][0] && strrchr (filename, '.'))
	{
	  fs_error(filename);
	  free (filename);
	  return;
	}
    }

  if (!suffixes[i])
    {
      fs_error(name);
      free (filename);
      return;
    }

  input_filename = filename;

  /* Search this file looking for the special string which starts conversion.
     Once found, we may truly begin. */

  input_text_offset = search_forward ("@setfilename", 0);

  if (input_text_offset < 0) {
    if (!command_output_filename) {
      remember_error();
      (void)fprintf(stderr, "No `@setfilename' found in `%s'.\n", name);
      goto finished;
    }
  } else input_text_offset += strlen ("@setfilename");

  real_output_filename = (char *)0;

  if (!command_output_filename)
    (void)get_until ("\n", &output_filename);
  else
    {
      discard_until ("\n");
      real_output_filename = output_filename = command_output_filename;
      command_output_filename = (char *)0;
    }

  canon_white (output_filename);
  (void)printf ("Making info file `%s' from `%s'.\n", output_filename, name);

  if (verbose_mode)
    (void)fprintf (stderr, "  The input file contains %d characters.\n",
	     size_of_input_text);

  if (real_output_filename &&
      strcmp (real_output_filename, "-") == 0)
    {
      output_stream = stdout;
    }
  else
    {
      if (!real_output_filename)
	real_output_filename = expand_filename (output_filename, name);

      output_stream = fopen (real_output_filename, "w");
    }

  if (!output_stream)
    {
      fs_error(real_output_filename);
      goto finished;
    }

  /* Make the displayable filename from output_filename.  Only the base
     portion of the filename need be displayed. */
  pretty_output_filename = filename_part (output_filename);

  /* For this file only, count the number of newlines from the top of
     the file to here.  This way, we keep track of line numbers for
     error reporting.  Line_number starts at 1, since the user isn't
     zero-based. */
  {
    int temp = 0;
    line_number = 1;
    while (temp != input_text_offset)
      if (input_text[temp++] == '\n')
	line_number++;
  }

  add_word_args ("This is Info file %s, produced by %s-%d.%d from ",
		 output_filename, "Makeinfo", major_version, minor_version);
  add_word_args ("the input file %s.\n", input_filename, "", 0, 0);
  close_paragraph ();

  reader_loop ();

finished:
  close_paragraph ();
  flush_file_stack ();
  if (output_stream)
    {
      output_pending_notes ();
      free_pending_notes ();
      if (tag_table)
	{
	  tag_table = (TAG_ENTRY *)reverse_list((GENERIC_LIST *)tag_table);
	  write_tag_table ();
	}

      if (output_stream != stdout)
	(void)fclose (output_stream);

      /* If validating, then validate the entire file right now. */
      if (validating)
	validate_file (real_output_filename, tag_table);

      /* This used to test  && !errors_printed.
	 But some files might have legit warnings.  So split anyway.  */
      if (splitting)
	split_file (real_output_filename, 0);
    }
}

void
free_and_clear (pointer)
     char **pointer;
{ if (*pointer) { free (*pointer); *pointer = (char *) 0; } }

 /* Initialize some state. */
void
init_internals ()
{
  free_and_clear (&current_node);
  free_and_clear (&output_filename);
  free_and_clear (&command);
  free_and_clear (&input_filename);
  free_node_references ();
  init_insertion_stack ();
  init_brace_stack ();
  command_index = 0;
  in_menu = 0;
}

void
init_paragraph ()
{
  free_and_clear ((char **)(&output_paragraph));
  output_paragraph = (unsigned char *)xmalloc (paragraph_buffer_len);
  output_position = 0;
  output_paragraph[0] = '\0';
  output_paragraph_offset = 0;
  output_column = 0;
  paragraph_is_open = 0;
  current_indent = 0;
}

/* Okay, we are ready to start the conversion.  Call the reader on
   some text, and fill the text as it is output.  Handle commands by
   remembering things like open braces and the current file position on a
   stack, and when the corresponding close brace is found, you can call
   the function with the proper arguments. */
void
reader_loop ()
{
  int character;
  int done = 0;
  int dash_count = 0;

  while (!done)
    {
      if (input_text_offset >= size_of_input_text)
	{
	  if (filestack)
	    {
	      free (input_filename);
	      free (input_text);
	      popfile ();
	    }
	  else
	    break;
	}

      character = curchar ();

      if (!in_fixed_width_font &&
	  (character == '\'' || character == '`') &&
	  input_text[input_text_offset + 1] == character)
	{
	  input_text_offset++;
	  character = '"';
	}

      if (character == '-')
	{
	  dash_count++;
	  if (dash_count == 3 && !in_fixed_width_font)
	    {
	      input_text_offset++;
	      continue;
	    }
	}
      else
	{
	  dash_count = 0;
	}

      /* If this is a whitespace character, then check to see if the line
	 is blank.  If so, advance to the carriage return. */
      if (whitespace (character))
	{
	  register int i = input_text_offset + 1;

	  while (i < size_of_input_text && whitespace (input_text[i]))
	    i++;

	  if (i == size_of_input_text || input_text[i] == '\n')
	    {
	      if (i == size_of_input_text)
		i--;

	      input_text_offset = i;
	      character = curchar ();
	    }
	}

      if (character == '\n')
	{
	  line_number++;
	  if (in_menu && input_text_offset + 1 < size_of_input_text)
	    {
	      char *glean_node_from_menu (), *tem;

	      /* Note that the value of TEM is discarded, since it is
		 gauranteed to be NULL when glean_node_from_menu () is
		 called with a non-zero argument. */
	      tem = glean_node_from_menu (1);
	    }
	}

      switch (character)
	{
	case COMMAND_PREFIX:
	  read_command ();
	  if (strcmp (command, "bye") == 0)
	    {
	      done = 1;
	      continue;
	    }
	  break;

	case '{':

	  /* Special case.  I'm not supposed to see this character by itself.
	     If I do, it means there is a syntax error in the input text.
	     Report the error here, but remember this brace on the stack so
	     you can ignore its partner. */

	  line_error();
          (void)fprintf(stderr, "Misplaced `{'.\n");
	  remember_brace (misplaced_brace);

	  /* Don't advance input_text_offset since this happens in
	     remember_brace ().
	     input_text_offset++;
           */
	  break;

	case '}':
	  pop_and_call_brace ();
	  input_text_offset++;
	  break;

	default:
	  add_char (character);
	  input_text_offset++;
	}
    }
}

/* Find the command corresponding to STRING.  If the command
   is found, return a pointer to the data structure.  Otherwise
   return (0). */
COMMAND *
get_command_entry (string)
     char *string;
{
  register int i;

  for (i = 0; CommandTable[i].name; i++)
    if (strcmp (CommandTable[i].name, string) == 0)
      return (&CommandTable[i]);

  /* This command is not in our predefined command table.  Perhaps
     it is a user defined command. */
  for (i = 0; i < user_command_array_len; i++)
    if (user_command_array[i] &&
	(strcmp (user_command_array[i]->name, string) == 0))
      return (user_command_array[i]);

  /* Nope, we never heard of this command. */
  return ((COMMAND *)0);
}

/* input_text_offset is right at the command prefix character.
   Read the next token to determine what to do. */
void
read_command ()
{
  COMMAND *entry;
  input_text_offset++;
  free_and_clear (&command);
  command = read_token ();

#if defined (HAVE_MACROS)
  /* Check to see if this command is a macro.  If so, execute it here. */
  {
    MACRO_DEF *def;

    def = find_macro (command);

    if (def)
      {
	execute_macro (def);
	return;
      }
  }
#endif /* HAVE_MACROS */

  entry = get_command_entry (command);

  if (! entry ) {
    line_error();
    (void)fprintf(stderr, "Unknown info command `%s'.\n", command);
    return;
  }

  if (entry->argument_in_braces)
    remember_brace (entry->proc);

  (*(entry->proc)) (START);
}

int
get_char_len (character)
     int character;
{
  /* Return the printed length of the character. */
  int len;

  switch (character)
    {
    case '\t':
      len = (output_column + 8) & 0xf7;
      if (len > fill_column)
	len = fill_column - output_column;
      else
	len = len - output_column;
      break;

    case '\n':
      len = fill_column - output_column;
      break;

    default:
      if (character < ' ')
	len = 2;
      else
	len = 1;
    }
  return (len);
}

int last_char_was_newline = 1;
int last_inserted_character = 0;

/* Non-zero means that a newline character has already been
   inserted, so close_paragraph () should insert one less. */
int line_already_broken = 0;

/* Add the character to the current paragraph.  If filling_enabled is
   non-zero, then do filling as well. */
void
add_char (character)
     int character;
{
  /* If we are avoiding outputting headers, and we are currently
     in a menu, then simply return. */
  if (no_headers && in_menu)
    return;

  /* If we are adding a character now, then we don't have to
     ignore close_paragraph () calls any more. */
  if (must_start_paragraph && character != '\n')
    {
      must_start_paragraph = 0;
      line_already_broken = 0;	/* The line is no longer broken. */
      if (current_indent > output_column)
	{
	  indent (current_indent - output_column);
	  output_column = current_indent;
	}
    }

  if (non_splitting_words && member (character, " \t\n"))
    character = ' ' | 0x80;

  switch (character)
    {
    case '\n':
      if (!filling_enabled)
	{
	  insert ('\n');

	  if (force_flush_right)
	    {
	      close_paragraph ();
	      /* Hack to force single blank lines out in this mode. */
	      flush_output ();
	    }

	  output_column = 0;

	  if (!no_indent && paragraph_is_open)
	    indent (output_column = current_indent);
	  break;
	}
      else
	{
	  if (sentence_ender (last_inserted_character))
	    {
	      insert (' ');
	      output_column++;
	      last_inserted_character = character;
	    }
	}

      if (last_char_was_newline)
	{
	  close_paragraph ();
	  pending_indent = 0;
	}
      else
	{
	  last_char_was_newline = 1;
	  insert (' ');
	  output_column++;
	}
      break;

    default:
      {
	int len = get_char_len (character);

	if ((character == ' ') && (last_char_was_newline))
	  {
	    if (!paragraph_is_open)
	      {
		pending_indent++;
		return;
	      }
	  }

	if (!paragraph_is_open)
	  {
	    start_paragraph ();

	    /* If the paragraph is supposed to be indented a certain way,
	       then discard all of the pending whitespace.  Otherwise, we
	       let the whitespace stay. */
	    if (!paragraph_start_indent)
	      indent (pending_indent);
	    pending_indent = 0;
	  }

	if ((output_column += len) >= fill_column)
	  {
	    if (filling_enabled)
	      {
		int temp = output_paragraph_offset;
		while (--temp > 0 && output_paragraph[temp] != '\n')
		  {
		    /* If we have found a space, we have the place to break
		       the line. */
		    if (output_paragraph[temp] == ' ')
		      {
			output_paragraph[temp++] = '\n';

			/* We have correctly broken the line where we want
			   to.  What we don't want is spaces following where
			   we have decided to break the line.  We get rid of
			   them. */
			{
			  int t1 = temp;
			  while (t1 < output_paragraph_offset
				 && whitespace (output_paragraph[t1]))
			    t1++;

			  if (t1 != temp)
			    {
			      (void)strncpy ((char *) &output_paragraph[temp],
				       (char *) &output_paragraph[t1],
				       (output_paragraph_offset - t1));
			      output_paragraph_offset -= (t1 - temp);
			    }
			}

			/* Filled, but now indent if that is right. */
			if (indented_fill && current_indent)
			  {
			    int buffer_len = ((output_paragraph_offset - temp)
					      + current_indent);
			    char *temp_buffer = (char *)xmalloc (buffer_len);
			    int indentation = 0;

			    /* We have to shift any markers that are in
			       front of the wrap point. */
			    {
			      register BRACE_ELEMENT *stack = brace_stack;

			      while (stack)
				{
				  if (stack->pos > temp)
				    stack->pos += current_indent;
				  stack = stack->next;
				}
			    }

			    while (current_indent > 0 &&
				   indentation != current_indent)
			      temp_buffer[indentation++] = ' ';

			    (void)strncpy ((char *) &temp_buffer[current_indent],
				     (char *) &output_paragraph[temp],
				     buffer_len - current_indent);

			    if (output_paragraph_offset + buffer_len
				>= paragraph_buffer_len)
			      {
				unsigned char *tt;
				tt = (unsigned char *)xrealloc
				  ((char *)output_paragraph,
				   (paragraph_buffer_len += buffer_len));
				output_paragraph = tt;
			      }
			    (void)strncpy ((char *) &output_paragraph[temp],
				     temp_buffer, buffer_len);
			    output_paragraph_offset += current_indent;
			    free (temp_buffer);
			  }
			output_column = 0;
			while (temp < output_paragraph_offset)
			  output_column +=
			    get_char_len((char)output_paragraph[temp++]);
			output_column += len;
			break;
		      }
		  }
	      }
	  }
	insert (character);
	line_already_broken = 0;
	last_char_was_newline = 0;
	last_inserted_character = character;
      }
    }
}

/* Insert CHARACTER into OUTPUT_PARAGRAPH. */
void
insert (character)
     int character;
{
  output_paragraph[output_paragraph_offset++] = character;
  if (output_paragraph_offset == paragraph_buffer_len)
    {
      output_paragraph =
	(unsigned char *)xrealloc((char *)output_paragraph,
          (paragraph_buffer_len += 100));
    }
}

/* Remove upto COUNT characters of whitespace from the
   the current output line.  If COUNT is less than zero,
   then remove until none left. */
void
kill_self_indent (count)
     int count;
{
  /* Handle infinite case first. */
  if (count < 0)
    {
      output_column = 0;
      while (output_paragraph_offset)
	{
	  if (whitespace (output_paragraph[output_paragraph_offset - 1]))
	    output_paragraph_offset--;
	  else
	    break;
	}
    }
  else
    {
      while (output_paragraph_offset && count--)
	if (whitespace (output_paragraph[output_paragraph_offset - 1]))
	  output_paragraph_offset--;
	else
	  break;
    }
}

void
flush_output ()
{
  register int i;

  if (!output_paragraph_offset)
    return;

  for (i = 0; i < output_paragraph_offset; i++)
    {
      if (output_paragraph[i] == (unsigned char)(' ' | 0x80) ||
	  output_paragraph[i] == (unsigned char)('\t' | 0x80) ||
	  output_paragraph[i] == (unsigned char)('\n' | 0x80) ||
	  sentence_ender (UNMETA (output_paragraph[i])))
	output_paragraph[i] &= 0x7f;
    }

  (void)fwrite ((char *)output_paragraph, 1, output_paragraph_offset, output_stream);
  output_position += output_paragraph_offset;
  output_paragraph_offset = 0;
}

/* How to close a paragraph controlling the number of lines between
   this one and the last one. */

/* Paragraph spacing is controlled by this variable.  It is the number of
   blank lines that you wish to appear between paragraphs.  A value of
   1 creates a single blank line between paragraphs. */
int paragraph_spacing = DEFAULT_PARAGRAPH_SPACING;

/* Close the current paragraph, leaving no blank lines between them. */
void
close_single_paragraph ()
{
  close_paragraph_with_lines (0);
}

/* Close a paragraph after an insertion has ended. */
int insertion_paragraph_closed = 0;

void
close_insertion_paragraph ()
{
  if (!insertion_paragraph_closed)
    {
      /* Close the current paragraph, breaking the line. */
      close_single_paragraph ();

      /* Start a new paragraph here, inserting whatever indention is correct
	 for the now current insertion level (one above the one that we are
	 ending). */
      start_paragraph ();

      /* Tell close_paragraph () that the previous line has already been
	 broken, so it should insert one less newline. */
      line_already_broken = 1;

      /* Let functions such as add_char () know that we have already found a
	 newline. */
      ignore_blank_line ();
    }

  insertion_paragraph_closed = 1;
}

void
close_paragraph_with_lines (lines)
     int lines;
{
  int old_spacing = paragraph_spacing;
  paragraph_spacing = lines;
  close_paragraph ();
  paragraph_spacing = old_spacing;
}

/* Close the currently open paragraph. */
void
close_paragraph ()
{
  register int i;

  /* The insertion paragraph is no longer closed. */
  insertion_paragraph_closed = 0;

  if (paragraph_is_open && !must_start_paragraph)
    {
      register int tindex, c;

      tindex = output_paragraph_offset;

      /* Back up to last non-newline/space character, forcing all such
	 subsequent characters to be newlines.  This isn't strictly
	 necessary, but a couple of functions use the presence of a newline
	 to make decisions. */
      for (tindex = output_paragraph_offset - 1; tindex >= 0; --tindex)
	{
	  c = output_paragraph[tindex];

	  if (c == ' '|| c == '\n')
	    output_paragraph[tindex] = '\n';
	  else
	    break;
	}

      /* All trailing whitespace is ignored. */
      output_paragraph_offset = ++tindex;

      /* Break the line if that is appropriate. */
      if (paragraph_spacing >= 0)
	insert ('\n');

      /* Add as many blank lines as is specified in PARAGRAPH_SPACING. */
      if (!force_flush_right)
	{
	  for (i = 0; i < (paragraph_spacing - line_already_broken); i++)
	    insert ('\n');
	}

      /* If we are doing flush right indentation, then do it now
	 on the paragraph (really a single line). */
      if (force_flush_right)
	do_flush_right_indentation ();

      flush_output ();
      paragraph_is_open = 0;
      no_indent = 0;
      output_column = 0;
    }
  ignore_blank_line ();
}

/* Make the last line just read look as if it were only a newline. */
void
ignore_blank_line ()
{
  last_inserted_character = '\n';
  last_char_was_newline = 1;
}

/* Align the end of the text in output_paragraph with fill_column. */
void
do_flush_right_indentation ()
{
  char *temp;
  int temp_len;

  kill_self_indent (-1);

  if (output_paragraph[0] != '\n')
    {
      output_paragraph[output_paragraph_offset] = '\0';

      if (output_paragraph_offset < fill_column)
	{
	  register int i;

	  if (fill_column >= paragraph_buffer_len)
	    output_paragraph =
	      (unsigned char *)xrealloc((char *)output_paragraph,
			(paragraph_buffer_len += fill_column));

	  temp_len = strlen ((char *)output_paragraph);
	  temp = (char *)xmalloc (temp_len + 1);
	  memcpy (temp, (char *)output_paragraph, temp_len);

	  for (i = 0; i < fill_column - output_paragraph_offset; i++)
	    output_paragraph[i] = ' ';

	  memcpy ((char *)output_paragraph + i, temp, temp_len);
	  free (temp);
	  output_paragraph_offset = fill_column;
	}
    }
}

/* Begin a new paragraph. */
void
start_paragraph ()
{
  /* First close existing one. */
  if (paragraph_is_open)
    close_paragraph ();

  /* In either case, the insertion paragraph is no longer closed. */
  insertion_paragraph_closed = 0;

  /* However, the paragraph is open! */
  paragraph_is_open = 1;

  /* If we MUST_START_PARAGRAPH, that simply means that start_paragraph ()
     had to be called before we would allow any other paragraph operations
     to have an effect. */
  if (!must_start_paragraph)
    {
      int amount_to_indent = 0;

      /* If doing indentation, then insert the appropriate amount. */
      if (!no_indent)
	{
	  if (inhibit_paragraph_indentation)
	    {
	      amount_to_indent = current_indent;
	      if (inhibit_paragraph_indentation < 0)
		inhibit_paragraph_indentation++;
	    }
	  else if (paragraph_start_indent < 0)
	    amount_to_indent = current_indent;
	  else
	    amount_to_indent = current_indent + paragraph_start_indent;

	  if (amount_to_indent >= output_column)
	    {
	      amount_to_indent -= output_column;
	      indent (amount_to_indent);
	      output_column += amount_to_indent;
	    }
	}
    }
  else
    must_start_paragraph = 0;
}

/* Insert the indentation specified by AMOUNT. */
void
indent (amount)
     int amount;
{
  while (--amount >= 0)
    insert (' ');
}

/* Whoops, Unix doesn't have stricmp, or strnicmp. */

/* Case independent string compare. */
int
#ifdef PROTO_OK
stricmp (const char *string1, const char *string2)
#else
stricmp (string1, string2)
     char *string1, *string2;
#endif
{
  char ch1, ch2;

  for (;;)
    {
      ch1 = *string1++;
      ch2 = *string2++;
      if (!(ch1 | ch2))
	return (0);

      ch1 = coerce_to_upper (ch1);
      ch2 = coerce_to_upper (ch2);

      if (ch1 != ch2)
	return (1);
    }
}

/* Compare at most COUNT characters from string1 to string2.  Case
   doesn't matter. */
int
#ifdef PROTO_OK
strnicmp (const char *string1, const char *string2, size_t count)
#else
strnicmp (string1, string2, count)
     char *string1, *string2;
#endif
{
  char ch1, ch2;

  while (count)
    {
      ch1 = *string1++;
      ch2 = *string2++;
      if (coerce_to_upper (ch1) == coerce_to_upper (ch2))
	count--;
      else
	break;
    }
  return (count);
}

/* Search forward for STRING in input_text.
   FROM says where where to start. */
int
search_forward (string, from)
     char *string;
     int from;
{
  int len = strlen (string);

  while (from < size_of_input_text)
    {
      if (strnicmp (input_text + from, string, len) == 0)
	return (from);
      from++;
    }
  return (-1);
}

enum insertion_type { menu, quotation, lisp, smalllisp, example,
  smallexample, display, smalldisplay, itemize, format, enumerate,
  cartouche, table,
  ftable, vtable, group, ifinfo, ifnottex, flushleft, flushright, ifset,
  ifclear, deffn, defun, defmac, defspec, defvr, defvar, defopt, deftypefn,
  deftypefun, deftypevr, deftypevar, defcv, defivar, defop, defmethod,
  deftypemethod, deftp, egfiles, run, bad_type };

char *insertion_type_names[] = { "menu", "quotation", "lisp",
  "smalllisp", "example", "smallexample", "display", "smalldisplay", "itemize",
  "format", "enumerate", "cartouche", "table", "ftable", "vtable", "group",
  "ifinfo", "ifnottex", "flushleft", "flushright", "ifset", "ifclear", "deffn",
  "defun", "defmac", "defspec", "defvr", "defvar", "defopt",
  "deftypefn", "deftypefun", "deftypevr", "deftypevar", "defcv",
  "defivar", "defop", "defmethod", "deftypemethod", "deftp",
  "egfiles", "run", "bad_type" };

int insertion_level = 0;
typedef struct istack_elt
{
  struct istack_elt *next;
  char *item_function;
  int line_number;
  int filling_enabled;
  int indented_fill;
  enum insertion_type insertion;
  int inhibited;
} INSERTION_ELT;

INSERTION_ELT *insertion_stack = (INSERTION_ELT *) 0;

void
init_insertion_stack ()
{
  insertion_stack = (INSERTION_ELT *) 0;
}

/* Return the type of the current insertion. */
enum insertion_type
current_insertion_type ()
{
  if (!insertion_level)
    return (bad_type);
  else
    return (insertion_stack->insertion);
}

/* Return a pointer to the string which is the function
   to wrap around items. */
char *
current_item_function ()
{
  if (!insertion_level)
    return ((char *) 0);
  else
    return (insertion_stack->item_function);
}

char *
get_item_function ()
{
  char *item_function;
  get_rest_of_line (&item_function);
  backup_input_pointer ();
  canon_white (item_function);
  return (item_function);
}

 /* Push the state of the current insertion on the stack. */
void
push_insertion (type, item_function)
     enum insertion_type type;
     char *item_function;
{
  INSERTION_ELT *new = (INSERTION_ELT *) xmalloc (sizeof (INSERTION_ELT));

  new->item_function = item_function;
  new->filling_enabled = filling_enabled;
  new->indented_fill = indented_fill;
  new->insertion = type;
  new->line_number = line_number;
  new->inhibited = inhibit_paragraph_indentation;
  new->next = insertion_stack;
  insertion_stack = new;
  insertion_level++;
}

 /* Pop the value on top of the insertion stack into the
    global variables. */
void
pop_insertion ()
{
  INSERTION_ELT *temp = insertion_stack;

  if (temp == (INSERTION_ELT *) 0)
    return;

  inhibit_paragraph_indentation = temp->inhibited;
  filling_enabled = temp->filling_enabled;
  indented_fill = temp->indented_fill;
  free_and_clear (&(temp->item_function));
  insertion_stack = insertion_stack->next;
  free((char *)temp);
  insertion_level--;
}

 /* Return a pointer to the print name of this
    enumerated type. */
char *
insertion_type_pname (type)
     enum insertion_type type;
{
  if ((int) type < (int) bad_type)
    return (insertion_type_names[(int) type]);
  else
    return ("Broken-Type in insertion_type_pname");
}

/* Return the insertion_type associated with NAME.
   If the type is not one of the known ones, return BAD_TYPE. */
enum insertion_type
find_type_from_name (name)
     char *name;
{
  int index = 0;
  while (index < (int) bad_type)
    {
      if (stricmp (name, insertion_type_names[index]) == 0)
	return (enum insertion_type) index;
      index++;
    }
  return (bad_type);
}

int
do_nothing ()
{
  return DONTCARE;
}

int
defun_insertion (type)
     enum insertion_type type;
{
  return
    ((type == deffn)
     || (type == defun)
     || (type == defmac)
     || (type == defspec)
     || (type == defvr)
     || (type == defvar)
     || (type == defopt)
     || (type == deftypefn)
     || (type == deftypefun)
     || (type == deftypevr)
     || (type == deftypevar)
     || (type == defcv)
     || (type == defivar)
     || (type == defop)
     || (type == defmethod)
     || (type == deftypemethod)
     || (type == deftp));
}

/* MAX_NS is the maximum nesting level for enumerations.  I picked 100
   which seemed reasonable.  This doesn't control the number of items,
   just the number of nested lists. */
#define max_stack_depth 100
#define ENUM_DIGITS 1
#define ENUM_ALPHA  2
typedef struct {
  int enumtype;
  int enumval;
} DIGIT_ALPHA;

DIGIT_ALPHA enumstack[max_stack_depth];
int enumstack_offset = 0;
int current_enumval = 1;
int current_enumtype = ENUM_DIGITS;
char *enumeration_arg = (char *)0;

void
start_enumerating (at, type)
     int at, type;
{
  if ((enumstack_offset + 1) == max_stack_depth) {
    line_error();
    (void)fprintf(stderr, "Enumeration stack overflow.\n");
    return;
  }
  enumstack[enumstack_offset].enumtype = current_enumtype;
  enumstack[enumstack_offset].enumval = current_enumval;
  enumstack_offset++;
  current_enumval = at;
  current_enumtype = type;
}

void
stop_enumerating ()
{
  --enumstack_offset;
  if (enumstack_offset < 0)
    enumstack_offset = 0;

  current_enumval = enumstack[enumstack_offset].enumval;
  current_enumtype = enumstack[enumstack_offset].enumtype;
}

/* Place a letter or digits into the output stream. */
void
enumerate_item ()
{
  char temp[10];

  if (current_enumtype == ENUM_ALPHA)
    {
      if (current_enumval == ('z' + 1) || current_enumval == ('Z' + 1)) {
	current_enumval = ((current_enumval - 1) == 'z' ? 'a' : 'A');
	if (print_warnings) {
          warning();
          (void)fprintf(stderr, "Lettering overflow, restarting at %c.\n",
            current_enumval);
	}
      }
      (void)sprintf (temp, "%c. ", current_enumval);
    }
  else
    (void)sprintf (temp, "%d. ", current_enumval);

  indent (output_column += (current_indent - strlen (temp)));
  add_word (temp);
  current_enumval++;
}

/* This is where the work for all the "insertion" style
   commands is done.  A huge switch statement handles the
   various setups, and generic code is on both sides. */
void
begin_insertion (type)
     enum insertion_type type;
{
  int no_discard = 0;
  char *cp;
  static char *libdir = (char *)0, *shellname = SHELL;

  if (defun_insertion (type))
    {
      push_insertion (type, savestring (""));
      no_discard++;
    }
  else
    push_insertion (type, get_item_function ());

  switch (type)
    {
    default: break;
    case menu:
      close_paragraph ();

      filling_enabled = no_indent = 0;
      inhibit_paragraph_indentation = 1;

      if (!no_headers)
	add_word ("* Menu:\n");

      in_menu++;
      no_discard++;
      break;

      /* I think @quotation is meant to do filling.
	 If you don't want filling, then use @example. */
    case quotation:
      close_single_paragraph ();
      last_char_was_newline = no_indent = 0;
      indented_fill = filling_enabled = 1;
      inhibit_paragraph_indentation = 1;
      current_indent += default_indentation_increment;
      break;

    case display:
    case smalldisplay:
    case example:
    case smallexample:
    case lisp:
    case smalllisp:
      /* Just like @example, but no indentation. */
    case format:

      close_single_paragraph ();
      inhibit_paragraph_indentation = 1;
      in_fixed_width_font++;
      filling_enabled = 0;
      last_char_was_newline = 0;

      if (type != format)
	current_indent += default_indentation_increment;

      break;

    case table:
    case ftable:
    case vtable:
    case itemize:
      close_single_paragraph ();
      current_indent += default_indentation_increment;
      filling_enabled = indented_fill = 1;
#if defined (INDENT_PARAGRAPHS_IN_TABLE)
      inhibit_paragraph_indentation = 0;
#else
      inhibit_paragraph_indentation = 1;
#endif /* !INDENT_PARAGRAPHS_IN_TABLE */

      /* Make things work for losers who forget the itemize syntax. */
      if (type == itemize)
	{
	  if (!(*insertion_stack->item_function))
	    {
	      free (insertion_stack->item_function);
	      insertion_stack->item_function = savestring ("@bullet");
	    }
	}
      break;

    case enumerate:
      close_single_paragraph ();
      inhibit_paragraph_indentation = no_indent = 0;
      current_indent += default_indentation_increment;
      filling_enabled = indented_fill = 1;

      if (isdigit (*enumeration_arg))
	start_enumerating (atoi (enumeration_arg), ENUM_DIGITS);
      else
	start_enumerating (*enumeration_arg, ENUM_ALPHA);
      break;

      /* Does nothing special in makeinfo. */
    case group:
      close_single_paragraph ();
      break;

      /* Insertions that are no-ops in info, but do something in TeX. */
    case ifinfo:
    case ifnottex:
    case ifset:
    case ifclear:
    case cartouche:
      break;

    case deffn:
    case defun:
    case defmac:
    case defspec:
    case defvr:
    case defvar:
    case defopt:
    case deftypefn:
    case deftypefun:
    case deftypevr:
    case deftypevar:
    case defcv:
    case defivar:
    case defop:
    case defmethod:
    case deftypemethod:
    case deftp:
      inhibit_paragraph_indentation = 1;
      filling_enabled = indented_fill = 1;
      current_indent += default_indentation_increment;
      no_indent = 0;
      break;

    case flushleft:
      close_single_paragraph ();
      inhibit_paragraph_indentation = 1;
      filling_enabled = indented_fill = no_indent = 0;
      break;

    case flushright:
      close_single_paragraph ();
      filling_enabled = indented_fill = no_indent = 0;
      inhibit_paragraph_indentation = 1;
      force_flush_right++;
      break;

    case run:
      inhibit_paragraph_indentation = 1;
      filling_enabled = indented_fill = 0;
      if (!have_had_egfiles) add_word("\n\037\n\037\n");
      add_word( "\n\037\n" );
      if ((cp = insertion_stack->item_function) && (*cp != '\0')) {
	free_and_clear( &shellname );
	shellname = savestring( cp );
      }
      add_word_args( "#!%s\n", shellname, "", 0, 0 );
      break;

    case egfiles:
      inhibit_paragraph_indentation = 1;
      filling_enabled = indented_fill = 0;
      add_word( "\n\037\n" );
      if (!(cp = insertion_stack->item_function) || (*cp == '\0')) {
	/* not specified so it tries to default */
	if (!libdir) {
	  line_error();
          (void)fprintf(stderr, "No default library directory in @egfiles.\n");
	  return;
	}
      } else {
	free_and_clear( &libdir );
	libdir = savestring( cp );
      }
      add_word_args( "%s\n", libdir, "", 0, 0 );
      break;
    }

  if (!no_discard)
    discard_until ("\n");
}

/* Try to end the insertion with the specified TYPE.
   TYPE, with a value of bad_type,  gets translated to match
   the value currently on top of the stack.
   Otherwise, if TYPE doesn't match the top of the insertion stack,
   give error. */
void
end_insertion (type)
     enum insertion_type type;
{
  enum insertion_type temp_type;

  if (!insertion_level)
    return;

  temp_type = current_insertion_type ();

  if (type == bad_type)
    type = temp_type;

  if (type != temp_type) {
    line_error();
    (void)fprintf(stderr, "Expected `%s', but saw `%s'.\n",
	 insertion_type_pname (temp_type), insertion_type_pname (type));
    return;
  }

  pop_insertion ();

  switch (type)
    {
      /* "Insertions which have no effect on paragraph formatting. */
    case ifinfo:
    case ifnottex:
    case ifset:
    case ifclear:
      break;

    case menu:
      in_menu--;		/* No longer hacking menus. */
      close_insertion_paragraph ();
      break;

    case enumerate:
      stop_enumerating ();
      close_insertion_paragraph ();
      current_indent -= default_indentation_increment;
      break;

    case flushleft:
    case group:
    case cartouche:
      close_insertion_paragraph ();
      break;

    case format:
    case display:
    case smalldisplay:
    case example:
    case smallexample:
    case lisp:
    case smalllisp:
    case quotation:

      /* @quotation is the only one of the above without a fixed width
	 font. */
      if (type != quotation)
	in_fixed_width_font--;

      /* @format is the only fixed_width insertion without a change
	 in indentation. */
      if (type != format)
	current_indent -= default_indentation_increment;

      /* The ending of one of these insertions always marks the
	 start of a new paragraph. */
      close_insertion_paragraph ();
      break;

    case table:
    case ftable:
    case vtable:
    case itemize:
      current_indent -= default_indentation_increment;
      break;

    case flushright:
      force_flush_right--;
      close_insertion_paragraph ();
      break;

    case egfiles:
    case run:
      add_word("\037");
      return;	/* so we don't get paragraph break */

      /* Handle the @defun style insertions with a default clause. */
    default:
      current_indent -= default_indentation_increment;
      close_insertion_paragraph ();
      break;
    }
}

/* Insertions cannot cross certain boundaries, such as node beginnings.  In
   code that creates such boundaries, you should call discard_insertions ()
   before doing anything else.  It prints the errors for you, and cleans up
   the insertion stack. */
void
discard_insertions ()
{
  int real_line_number = line_number;
  while (insertion_stack) {
    if (insertion_stack->insertion == ifinfo ||
	insertion_stack->insertion == ifnottex ||
	insertion_stack->insertion == ifset ||
	insertion_stack->insertion == ifclear ||
	insertion_stack->insertion == cartouche)
      break;
    { char *offender = (char *)insertion_type_pname(insertion_stack->insertion);

      line_number = insertion_stack->line_number;
      line_error();
      (void)fprintf(stderr, "This `%s' doesn't have a matching `%cend %s'.\n",
        offender, COMMAND_PREFIX, offender);
      pop_insertion ();
    }
  }
  line_number = real_line_number;
}

/* The actual commands themselves. */

/* Commands which insert themselves. */
int
insert_self ()
{
  add_word (command);
  return DONTCARE;
}

/* Force line break */
int
cm_asterisk ()
{
  /* Force a line break in the output. */
  insert ('\n');
  indent (output_column = current_indent);
  return DONTCARE;
}

/* Insert ellipsis. */
int
cm_dots (arg)
     int arg;
{
  if (arg == START)
    add_word ("...");
  return DONTCARE;
}

int
cm_bullet (arg)
     int arg;
{
  if (arg == START)
    add_char ('*');
  return DONTCARE;
}

int
cm_minus (arg)
     int arg;
{
  if (arg == START)
    add_char ('-');
  return DONTCARE;
}

/* Insert "TeX". */
int
cm_TeX (arg)
     int arg;
{
  if (arg == START)
    add_word ("TeX");
  return DONTCARE;
}

int
cm_copyright (arg)
     int arg;
{
  if (arg == START)
    add_word ("(C)");
  return DONTCARE;
}

int
cm_today (arg)
     int arg;
{
  static char * months [12] =
    { "January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December" };
  if (arg == START)
    {
      char Buffer[20];
      extern time_t time();

      time_t timer = time((time_t *)0);
      struct tm * ts = (localtime (&timer));
      (void)sprintf(Buffer, "%d %s %d",
	ts->tm_mday, months[ts->tm_mon], ts->tm_year + 1900);
      add_word(Buffer);
    }
  return DONTCARE;
}

int
cm_code (arg)
     int arg;
{
  extern int printing_index;

  if (printing_index)
    return  DONTCARE;

  if (arg == START)
    {
      in_fixed_width_font++;
      add_char ('`');
    }
  else
    {
      add_word ("'");
      in_fixed_width_font--;
    }
  return DONTCARE;
}

int
cm_samp (arg)
     int arg;
{
  cm_code (arg);
  return DONTCARE;
}

int
cm_file (arg)
     int arg;
{
  cm_code (arg);
  return DONTCARE;
}

int
cm_kbd (arg)
     int arg;
{
  cm_code (arg);
  return DONTCARE;
}

int
cm_key (arg)
     int arg;
{
  return DONTCARE;
}

/* Convert the character at position into CTL. */
int
cm_ctrl (arg, position)
     int arg, position;
{
  if (arg == END)
    output_paragraph[position - 1] = CTL (output_paragraph[position]);
  return DONTCARE;
}

/* Small Caps in makeinfo just does all caps. */
int
cm_sc (arg, start_pos, end_pos)
     int arg, start_pos, end_pos;
{
  if (arg == END)
    {
      while (start_pos < end_pos)
	{
	  output_paragraph[start_pos] =
	    coerce_to_upper (output_paragraph[start_pos]);
	  start_pos++;
	}
    }
  return DONTCARE;
}

/* @var in makeinfo just uppercases the text. */
int
cm_var (arg, start_pos, end_pos)
     int arg, start_pos, end_pos;
{
  if (arg == END)
    {
      while (start_pos < end_pos)
	{
	  output_paragraph[start_pos] =
	    coerce_to_upper (output_paragraph[start_pos]);
	  start_pos++;
	}
    }
  return DONTCARE;
}

int
cm_dfn (arg, position)
     int arg, position;
{
  add_char ('"');
  return DONTCARE;
}

int
cm_emph (arg)
     int arg;
{
  add_char ('*');
  return DONTCARE;
}

int
cm_strong (arg, position)
     int arg, position;
{
  cm_emph (arg);
  return DONTCARE;
}

int
cm_cite (arg, position)
     int arg, position;
{
  if (arg == START)
    add_word ("`");
  else
    add_word ("'");
  return DONTCARE;
}

/* Current text is italicized. */
int
cm_italic (arg, start, end)
     int arg, start, end;
{
  return DONTCARE;
}

/* Current text is highlighted. */
int
cm_bold (arg, start, end)
     int arg, start, end;
{
  cm_italic (arg, start, end);
  return DONTCARE;
}

/* Current text is in roman font. */
int
cm_roman (arg, start, end)
     int arg, start, end;
{
  return DONTCARE;
}

/* Current text is in roman font. */
int
cm_titlefont (arg, start, end)
     int arg, start, end;
{
  return DONTCARE;
}

/* Italicize titles. */
int
cm_title (arg, start, end)
     int arg, start, end;
{
  cm_italic (arg, start, end);
  return DONTCARE;
}

/* @refill is a NOP. */
int
cm_refill ()
{
  return DONTCARE;
}

/* Prevent the argument from being split across two lines. */
int
cm_w (arg, start, end)
     int arg, start, end;
{
  if (arg == START)
    non_splitting_words++;
  else
    non_splitting_words--;
  return DONTCARE;
}


/* Explain that this command is obsolete, thus the user shouldn't
   do anything with it. */
int
cm_obsolete (arg, start, end)
     int arg, start, end;
{
  if (arg == START && print_warnings) {
    warning();
    (void)fprintf(stderr, "The command `@%s' is obsolete.\n", command);
  }
  return DONTCARE;
}

/* Insert the text following input_text_offset up to the end of the line
   in a new, separate paragraph.  Directly underneath it, insert a
   line of WITH_CHAR, the same length of the inserted text. */
void
insert_and_underscore (with_char)
     int with_char;
{
  int len, i, old_no_indent;
  char *temp;

  close_paragraph ();
  filling_enabled =  indented_fill = 0;
  old_no_indent = no_indent;
  no_indent = 1;
  get_rest_of_line (&temp);

  len = output_position;
  (void)sprintf(exec_string, "%s\n@bye\n", temp);
  execute_string();
  free (temp);

  len = ((output_position + output_paragraph_offset) - 1) - len;
  for (i = 0; i < len; i++)
    add_char (with_char);
  insert ('\n');
  close_paragraph ();
  filling_enabled = 1;
  no_indent = old_no_indent;
}

/* The remainder of the text on this line is a chapter heading. */
int
cm_chapter ()
{
  insert_and_underscore ('*');
  return DONTCARE;
}

/* The remainder of the text on this line is a section heading. */
int
cm_section ()
{
  insert_and_underscore ('=');
  return DONTCARE;
}

/* The remainder of the text on this line is a subsection heading. */
int
cm_subsection ()
{
  insert_and_underscore ('-');
  return DONTCARE;
}

/* The remainder of the text on this line is a subsubsection heading. */
int
cm_subsubsection ()
{
  insert_and_underscore ('.');
  return DONTCARE;
}

/* Here is a structure which associates sectioning commands with
   an integer, hopefully to reflect the `depth' of the current
   section. */
struct {
  char *name;
  int level;
} section_alist[] = {
  { "unnumberedsubsubsec", 5 },
  { "unnumberedsubsec", 4 },
  { "unnumberedsec", 3 },
  { "unnumbered", 2 },
  { "appendixsubsubsec", 5 },
  { "appendixsubsec", 4 },
  { "appendixsec", 3 },
  { "appendixsection", 3 },
  { "appendix", 2 },
  { "subsubsec", 5 },
  { "subsubsection", 5 },
  { "subsection", 4 },
  { "section", 3 },
  { "chapter", 2 },
  { "top", 1 },

  { (char *)0, 0 }
};

/* Return an integer which identifies the type section present in TEXT. */
int
what_section (text)
     char *text;
{
  register int i, j;
  char *t;

 find_section_command:
  for (j = 0; text[j] && cr_or_whitespace (text[j]); j++);
  if (text[j] != '@')
    return (-1);

  text = text + j + 1;

  /* We skip @comment commands. */
  if ((strncmp (text, "comment", strlen ("comment")) == 0) ||
      (strncmp (text, "c ", strlen ("c ")) == 0))
    {
      while (*text++ != '\n');
      goto find_section_command;
    }

  /* Handle italicized sectioning commands. */
  if (*text == 'i')
    text++;

  for (j = 0; text[j] && !cr_or_whitespace (text[j]); j++);

  for (i = 0; (t = section_alist[i].name); i++)
    {
      if (j == strlen (t) && strncmp (t, text, j) == 0)
	return (section_alist[i].level);
    }
  return (-1);
}

/* Treat this just like @unnumbered.  The only difference is
   in node defaulting. */
int
cm_top ()
{
  static int top_encountered = 0;
  cm_unnumbered ();

  /* It is an error to have more than one @top. */
  if (top_encountered)
    {
      TAG_ENTRY *tag = tag_table;

      line_error();
      (void)fprintf(stderr, "There already is a node having @top as a section.\n");

      while (tag != (TAG_ENTRY *)0)
	{
	  if ((tag->flags & IS_TOP))
	    {
	      int old_line_number = line_number;
	      line_number = tag->line_no;
	      line_error();
              (void)fprintf(stderr, "Here is the @top node.\n");
	      line_number = old_line_number;
	      return  DONTCARE;
	    }
	  tag = tag->next_ent;
	}
    }
  else
    {
      top_encountered = 1;

      /* The most recently defined node is the top node. */
      if (tag_table)
	tag_table->flags |= IS_TOP;

      /* Now set the logical hierarchical level of the Top node. */
      {
	int orig_offset = input_text_offset;

	input_text_offset = search_forward ("\n@node", orig_offset);

	if (input_text_offset > 0)
	  {
	    int this_section;

	    /* Move to the end of this line, and find out what the
	       sectioning command is here. */
	    while (input_text[input_text_offset] != '\n')
	      input_text_offset++;

	    if (input_text_offset < size_of_input_text)
	      input_text_offset++;

	    this_section = what_section (input_text + input_text_offset);

	    /* If we found a sectioning command, then give the top section
	       a level of this section - 1. */
	    if (this_section != -1)
	      {
		register int i;

		for (i = 0; section_alist[i].name; i++)
		  if (strcmp (section_alist[i].name, "Top") == 0)
		    {
		      section_alist[i].level = this_section - 1;
		      break;
		    }
	      }
	  }
	input_text_offset = orig_offset;
      }
    }
  return DONTCARE;
}

/* The remainder of the text on this line is an unnumbered heading. */
int
cm_unnumbered ()
{
  cm_chapter ();
  return DONTCARE;
}

/* The remainder of the text on this line is an unnumbered section heading. */
int
cm_unnumberedsec ()
{
  cm_section ();
  return DONTCARE;
}

/* The remainder of the text on this line is an unnumbered
   subsection heading. */
int
cm_unnumberedsubsec ()
{
  cm_subsection ();
  return DONTCARE;
}

/* The remainder of the text on this line is an unnumbered
   subsubsection heading. */
int
cm_unnumberedsubsubsec ()
{
  cm_subsubsection ();
  return DONTCARE;
}

/* The remainder of the text on this line is an appendix heading. */
int
cm_appendix ()
{
  cm_chapter ();
  return DONTCARE;
}

/* The remainder of the text on this line is an appendix section heading. */
int
cm_appendixsec ()
{
  cm_section ();
  return DONTCARE;
}

/* The remainder of the text on this line is an appendix subsection heading. */
int
cm_appendixsubsec ()
{
  cm_subsection ();
  return DONTCARE;
}

/* The remainder of the text on this line is an appendix
   subsubsection heading. */
int
cm_appendixsubsubsec ()
{
  cm_subsubsection ();
  return DONTCARE;
}

/* Compatibility functions substitute for chapter, section, etc. */
int
cm_majorheading ()
{
  cm_chapheading ();
  return DONTCARE;
}

int
cm_chapheading ()
{
  cm_chapter ();
  return DONTCARE;
}

int
cm_heading ()
{
  cm_section ();
  return DONTCARE;
}

int
cm_subheading ()
{
  cm_subsection ();
  return DONTCARE;
}

int
cm_subsubheading ()
{
  cm_subsubsection ();
  return DONTCARE;
}


/* **************************************************************** */
/*								    */
/*		   Adding nodes, and making tags		    */
/*								    */
/* **************************************************************** */

/* Start a new tag table. */
void
init_tag_table ()
{
  while (tag_table != (TAG_ENTRY *) 0)
    {
      TAG_ENTRY *temp = tag_table;
      free (temp->node);
      free (temp->prev);
      free (temp->next);
      free (temp->up);
      tag_table = tag_table->next_ent;
      free((char *)temp);
    }
}

/* Write out the contents of the existing tag table.
   INDIRECT_P says how to format the output. */
void
write_tag_table_internal (indirect_p)
     int indirect_p;
{
  TAG_ENTRY *node = tag_table;
  int old_indent = no_indent;

  no_indent = 1;
  filling_enabled = 0;
  must_start_paragraph = 0;
  close_paragraph ();

  tag_table_pos = output_position + 1;

  if (!indirect_p)
    {
      no_indent = 1;
      insert ('\n');
    }

  add_word_args ("\037\nTag Table:\n%s",
    indirect_p ? "(Indirect)\n" : "", "", 0, 0);

  while (node != (TAG_ENTRY *) 0)
    {
      add_word_args ("%s: %s\177%d\n", "Node", node->node, node->position, 0);
      node = node->next_ent;
    }

  add_word ("\037\nEnd Tag Table\n");
  flush_output ();
  no_indent = old_indent;
}

void
write_tag_table ()
{
  write_tag_table_internal (0);	/* Not indirect. */
}

void
write_tag_table_indirect ()
{
  write_tag_table_internal (1);
}

char *
get_node_token ()
{
  char *string;

  get_until_in_line (",", &string);

  if (curchar () == ',')
    input_text_offset++;

  canon_white (string);

  /* Allow things like @@nodename. */
  normalize_node_name (string);

  return (string);
}

/* Given a node name in STRING, remove double @ signs, replacing them
   with just one. */
void
normalize_node_name (string)
     char *string;
{
  register int i, l = strlen (string);

  for (i = 0; i < l; i++)
    {
      if (string[i] == '@' && string[i + 1] == '@')
	{
	  (void)strncpy (string + i, string + i + 1, l - i);
	  l--;
	}
    }
}

/* Look up NAME in the tag table, and return the associated
   tag_entry.  If the node is not in the table return NULL. */
TAG_ENTRY *
find_node (name)
     char *name;
{
  TAG_ENTRY *tag = tag_table;

  while (tag != (TAG_ENTRY *) 0)
    {
      if (stricmp (tag->node, name) == 0)
	return (tag);
      tag = tag->next_ent;
    }
  return ((TAG_ENTRY *) 0);
}

/* Remember NODE and associates. */
void
remember_node (node, prev, next, up, position, line_no, no_warn)
     char *node, *prev, *next, *up;
     int position, line_no, no_warn;
{
  /* Check for existence of this tag already. */
  if (validating) {
    register TAG_ENTRY *tag = find_node (node);

    if (tag) {
      line_error();
      (void)fprintf(stderr,
        "Node `%s' multiply defined (%d is first definition).\n",
        node, tag->line_no);
      return;
    }
  }

  /* First, make this the current node. */
  current_node = node;

  /* Now add it to the list. */
  {
    TAG_ENTRY *new = (TAG_ENTRY *) xmalloc (sizeof (TAG_ENTRY));
    new->node = node;
    new->prev = prev;
    new->next = next;
    new->up = up;
    new->position = position;
    new->line_no = line_no;
    new->filename = node_filename;
    new->touched = 0;		/* not yet referenced. */
    new->flags = 0;
    if (no_warn)
      new->flags |= NO_WARN;
    new->next_ent = tag_table;
    tag_table = new;
  }
}


/* The order is: nodename, nextnode, prevnode, upnode, eg.
   The next, prev, and up fields can be defaulted.
   You must follow a node command which has those fields
   defaulted with a sectioning command (e.g. @chapter) giving
   the "level" of that node.  It is an error not to do so.
   The defaults come from the menu in this nodes parent. */
int
cm_node ()
{
  char *node, *prev, *next, *up, *eg;
  int new_node_pos, defaulting, this_section, no_warn = 0;
  extern int already_outputting_pending_notes;

  if (strcmp (command, "nwnode") == 0)
    no_warn = 1;

  /* Get rid of unmatched brace arguments from previous commands. */
  discard_braces ();

  /* There also might be insertions left lying around that haven't been
     ended yet.  Do that also. */
  discard_insertions ();

  if (!already_outputting_pending_notes)
    {
      close_paragraph ();
      output_pending_notes ();
      free_pending_notes ();
    }

  filling_enabled = indented_fill = 0;
  new_node_pos = output_position + 1;
  current_footnote_number = 1;

  node = get_node_token ();
  next = get_node_token ();
  prev = get_node_token ();
  up = get_node_token ();
  eg = get_node_token ();

  no_indent = 1;
  if (!no_headers)
    add_word_args ("\037\nFile: %s,  Node: %s",
      pretty_output_filename, node, 0, 0);

  /* Check for defaulting of this node's next, prev, and up fields. */
  defaulting = ((strlen (next) == 0) &&
		(strlen (prev) == 0) &&
		(strlen (up) == 0));

  this_section = what_section (input_text + input_text_offset);

  /* If we are defaulting, then look at the immediately following
     sectioning command (error if none) to determine the node's
     level.  Find the node that contains the menu mentioning this node
     that is one level up (error if not found).  That node is the "Up"
     of this node.  Default the "Next" and "Prev" from the menu. */
  if (defaulting)
    {
      NODE_REF *last_ref = (NODE_REF *)0;
      NODE_REF *ref = node_references;

      if (this_section < 0)
	{
	  char *polite_section_name = "top";
	  int i;

	  for (i = 0; section_alist[i].name; i++)
	    if (section_alist[i].level == current_section + 1)
	      {
		polite_section_name = section_alist[i].name;
		break;
	      }

	  line_error();
          (void)fprintf(stderr,
            "Node `%s' requires a sectioning command (e.g. @%s).\n",
	     node, polite_section_name);
	}
      else
	{
	  if (stricmp (node, "Top") == 0)
	    {
	      /* Default the NEXT pointer to be the first menu item in
		 this node, if there is a menu in this node. */
	      {
		int orig_offset, orig_size;
		char *glean_node_from_menu ();

		orig_offset = input_text_offset;
		orig_size = search_forward ("\n@node ", orig_offset);

		if (orig_size < 0)
		  orig_size = size_of_input_text;

		input_text_offset = search_forward ("\n@menu", orig_offset);
		if (input_text_offset > -1)
		  {
		    input_text_offset =
		      search_forward ("\n* ", input_text_offset);

		    if (input_text_offset > -1)
		      next = glean_node_from_menu (0);

		    if (next)
		      {
			prev = savestring ("(DIR)");
			up = savestring ("(DIR)");
		      }
		  }
		input_text_offset = orig_offset;
	      }
	    }

	  while (ref)
	    {
	      if (ref->section == (this_section - 1) &&
		  ref->type == menu_reference &&
		  stricmp (ref->node, node) == 0)
		{
		  char *containing_node = ref->containing_node;

		  free (up);
		  up = savestring (containing_node);

		  if (last_ref &&
		      strcmp
		      (last_ref->containing_node, containing_node) == 0)
		    {
		      free (next);
		      next = savestring (last_ref->node);
		    }

		  while ((ref->section == this_section - 1) &&
			 (ref->next) &&
			 (ref->next->type != menu_reference))
		    ref = ref->next;

		  if (ref->next &&
		      strcmp
		      (ref->next->containing_node, containing_node) == 0)
		    {
		      free (prev);
		      prev = savestring (ref->next->node);
		    }
		  else if (!ref->next &&
			   stricmp (ref->containing_node, "Top") == 0)
		    {
		      free (prev);
		      prev = savestring (ref->containing_node);
		    }
		  break;
		}
	      last_ref = ref;
	      ref = ref->next;
	    }
	}
    }

  if (!no_headers)
    {
      if (*next)
	add_word_args (",  Next: %s", next, "", 0, 0);

      if (*prev)
	add_word_args (",  Prev: %s", prev, "", 0, 0);

      if (*up)
	add_word_args (",  Up: %s", up, "", 0, 0);

      if (*eg)
	add_word_args (",  Eg: %s", eg, "", 0, 0);
    }

  insert ('\n');
  close_paragraph ();
  no_indent = 0;

  if (!*node) {
    line_error();
    (void)fprintf(stderr, "No node name specified for `@%s' command.\n",
      command);
    free (node);
    free (next);
    free (prev);
    free (up);
    free (eg);
  } else {
    if (!*next) { free (next); next = (char *)0; }
    if (!*prev) { free (prev); prev = (char *)0; }
    if (!*up) { free (up); up = (char *)0; }
    remember_node (node, prev, next, up, new_node_pos, line_number, no_warn);
  }

  /* Change the section only if there was a sectioning command. */
  if (this_section >= 0)
    current_section = this_section;

  filling_enabled = 1;
  have_had_run = 0;
  have_had_egfiles = 0;
  return DONTCARE;
}

/* Validation of an info file.
   Scan through the list of tag entrys touching the Prev, Next, and Up
   elements of each.  It is an error not to be able to touch one of them,
   except in the case of external node references, such as "(DIR)".

   If the Prev is different from the Up,
   then the Prev node must have a Next pointing at this node.

   Every node except Top must have an Up.
   The Up node must contain some sort of reference, other than a Next,
   to this node.

   If the Next is different from the Next of the Up,
   then the Next node must have a Prev pointing at this node. */
void
validate_file (filename, tag_table)
     char *filename;
     TAG_ENTRY *tag_table;
{
  char *old_input_filename = input_filename;
  TAG_ENTRY *tags = tag_table;

  while (tags != (TAG_ENTRY *) 0)
    {
      register TAG_ENTRY *temp_tag;

      input_filename = tags->filename;
      line_number = tags->line_no;

      /* If this node has a Next, then make sure that the Next exists. */
      if (tags->next)
	{
	  (void)validate (tags->next, tags->line_no, "Next");

	  /* If the Next node exists, and there is no Up, then make
	     sure that the Prev of the Next points back. */
	  if ((temp_tag = find_node (tags->next)))
	    {
	      char *prev = temp_tag->prev;
	      if (!prev || (stricmp (prev, tags->node) != 0)) {
		line_error();
                (void)fprintf(stderr,
                  "Node `%s''s Next field not pointed back to.\n", tags->node);
		line_number = temp_tag->line_no;
		input_filename = temp_tag->filename;
		line_error();
                (void)fprintf(stderr,
                  "This node (`%s') is the one with the bad `Prev'.\n",
		  temp_tag->node);
		input_filename = tags->filename;
		line_number = tags->line_no;
		temp_tag->flags |= PREV_ERROR;
              }
	    }
	}

      /* Validate the Prev field if there is one, and we haven't already
	 complained about it in some way.  You don't have to have a Prev
	 field at this stage. */
      if (!(tags->flags & PREV_ERROR) && tags->prev)
	{
	  int valid = validate (tags->prev, tags->line_no, "Prev");

	  if (!valid) tags->flags |= PREV_ERROR;
	  else {
	    /* If the Prev field is not the same as the Up field,
	then the node pointed to by the Prev field must have
	a Next field which points to this node. */
	    if (tags->up && (stricmp (tags->prev, tags->up) != 0)) {
              temp_tag = find_node (tags->prev);
              if (!temp_tag->next ||
		  (stricmp (temp_tag->next, tags->node) != 0)) {
		line_error();
                (void)fprintf(stderr,
                  "Node `%s''s Prev field not pointed back to.\n", tags->node);
		line_number = temp_tag->line_no;
		input_filename = temp_tag->filename;
		line_error();
                (void)fprintf(stderr,
                  "This node (`%s') is the one with the bad `Next'.\n",
                  temp_tag->node);
		input_filename = tags->filename;
		line_number = tags->line_no;
		temp_tag->flags |= NEXT_ERROR;
              }
            }
	  }
	}

      if (!tags->up && (stricmp (tags->node, "Top") != 0)) {
	line_error();
        (void)fprintf(stderr,
          "Node `%s' is missing an \"Up\" field.\n", tags->node);
      } else if (tags->up) {
	  int valid = validate (tags->up, tags->line_no, "Up");

	  /* If node X has Up: Y, then warn if Y fails to have a menu item
	     or note pointing at X, if Y isn't of the form "(Y)". */
	  if (valid && *tags->up != '(')
	    {
	      NODE_REF *nref, *tref, *list;
	      NODE_REF *find_node_reference ();

	      tref = (NODE_REF *) 0;
	      list = node_references;

	      for (;;)
		{
		  if (!(nref = find_node_reference (tags->node, list)))
		    break;

		  if (stricmp (nref->containing_node, tags->up) == 0)
		    {
		      if (nref->type != menu_reference)
			{
			  tref = nref;
			  list = nref->next;
			}
		      else
			break;
		    }
		  list = nref->next;
		}

	      if (!nref)
		{
		  temp_tag = find_node (tags->up);
		  line_number = temp_tag->line_no;
		  filename = temp_tag->filename;
		  if (!tref) {
		    line_error();
                    (void)fprintf(stderr,
"`%s' has an Up field of `%s', but `%s' has no menu item for `%s'.\n",
                      tags->node, tags->up, tags->up, tags->node);
                  }
		  line_number = tags->line_no;
		  filename = tags->filename;
		}
	    }
	}
      tags = tags->next_ent;
    }

  validate_other_references (node_references);
  /* We have told the user about the references which didn't exist.
     Now tell him about the nodes which aren't referenced. */

  tags = tag_table;
  while (tags != (TAG_ENTRY *) 0)
    {
      /* Special hack.  If the node in question appears to have
         been referenced more than REFERENCE_WARNING_LIMIT times,
         give a warning. */
      if (tags->touched > reference_warning_limit)
	{
	  input_filename = tags->filename;
	  line_number = tags->line_no;
          if (print_warnings) {
	    warning();
            (void)fprintf(stderr, "Node `%s' has been referenced %d times.\n",
	      tags->node, tags->touched);
          }
	}

      if (tags->touched == 0)
	{
	  input_filename = tags->filename;
	  line_number = tags->line_no;

	  /* Notice that the node "Top" is special, and doesn't have to
	     be referenced. */
	  if (stricmp (tags->node, "Top") != 0 && print_warnings) {
	    warning();
            (void)fprintf(stderr, "Unreferenced node `%s'.\n", tags->node);
          }
	}
      tags = tags->next_ent;
    }
  input_filename = old_input_filename;
}

/* Return 1 if tag correctly validated, or 0 if not. */
int
validate (tag, line, label)
     char *tag;
     int line;
     char *label;
{
  TAG_ENTRY *result;

  /* If there isn't a tag to verify, or if the tag is in another file,
     then it must be okay. */
  if (!tag || !*tag || *tag == '(')
    return (1);

  /* Otherwise, the tag must exist. */
  result = find_node (tag);

  if (!result) {
    line_number = line;
    line_error();
    (void)fprintf(stderr,
"Validation error.  `%s' field points to node `%s', which doesn't exist.\n",
      label, tag);
    return 0;
  }
  result->touched++;
  return (1);
}

/* Split large output files into a series of smaller files.  Each file
   is pointed to in the tag table, which then gets written out as the
   original file.  The new files have the same name as the original file
   with a "-num" attached.  SIZE is the largest number of bytes to allow
   in any single split file. */
void
split_file (filename, size)
     char *filename;
     int size;
{
  char *root_filename, *root_pathname;
  char *the_file, *filename_part ();
  struct stat fileinfo;
  char *the_header;
  int header_size;

  /* Can only do this to files with tag tables. */
  if (!tag_table)
    return;

  if (size == 0)
    size = DEFAULT_SPLIT_SIZE;

  if ((stat (filename, &fileinfo) != 0) ||
      (fileinfo.st_size < SPLIT_SIZE_THRESHOLD))
    return;

  the_file = find_and_load (filename);
  if (!the_file)
    return;

  root_filename = filename_part (filename);
  root_pathname = pathname_part (filename);

  if (!root_pathname)
    root_pathname = savestring ("");

  /* Start splitting the file.  Walk along the tag table
     outputting sections of the file.  When we have written
     all of the nodes in the tag table, make the top-level
     pointer file, which contains indirect pointers and
     tags for the nodes. */
  {
    int which_file = 1;
    TAG_ENTRY *tags = tag_table;
    char *indirect_info = (char *)0;

    /* Remember the `header' of this file.  The first tag in the file is
       the bottom of the header; the top of the file is the start. */
    the_header = (char *)xmalloc (1 + (header_size = (tags->position - 2)));
    memcpy (the_header, the_file, header_size);

    while (tags)
      {
	int file_top, file_bot, limit;

	/* Have to include the Control-_. */
	file_top = file_bot = tags->position - 2;
	limit = file_top + size;

	/* If the rest of this file is only one node, then
	   that is the entire subfile. */
	if (!tags->next_ent)
	  {
/*
	    int i = tags->position + 1;
	    char last_char = the_file[i];

	    while (i < fileinfo.st_size)
	      {
		if ((the_file[i] == '\037') &&
		    ((last_char == '\n') ||
		     (last_char == '\014')))
		  break;
		else
		  last_char = the_file[i];
		i++;
	      }
	    file_bot = i;
*/
	    file_bot = tag_table_pos;
	    tags = tags->next_ent;
	    goto write_region;
	  }

	/* Otherwise, find the largest number of nodes that can fit in
	   this subfile. */
	for (; tags; tags = tags->next_ent)
	  {
	    if (!tags->next_ent)
	      {
		/* This entry is the last node.  Search forward for the end
	           of this node, and that is the end of this file. */
/*
		int i = tags->position + 1;
		char last_char = the_file[i];

		while (i < fileinfo.st_size)
		  {
		    if ((the_file[i] == '\037') &&
			((last_char == '\n') ||
			 (last_char == '\014')))
		      break;
		    else
		      last_char = the_file[i];
		    i++;
		  }
		file_bot = i;
*/
		file_bot = tag_table_pos;

		if (file_bot < limit)
		  {
		    tags = tags->next_ent;
		    goto write_region;
		  }
		else
		  {
		    /* Here we want to write out everything before the last
		       node, and then write the last node out in a file
		       by itself. */
		    file_bot = tags->position;
		    goto write_region;
		  }
	      }

	    if (tags->next_ent->position > limit)
	      {
		if ((tags->position) - 2 == file_top)
		  tags = tags->next_ent;
		file_bot = tags->position;
	      write_region:
		{
		  int fd;
		  char *split_file = (char *)
		    xmalloc (10
			     + strlen (root_pathname)
			     + strlen (root_filename));
		  (void)sprintf (split_file,
		       "%s%s-%d", root_pathname, root_filename, which_file);

		  if (((fd = open (split_file, O_WRONLY | O_TRUNC | O_CREAT, 0666)) < 0)
		      || (write (fd, the_header, header_size) != header_size)
		      || (write (fd, the_file + file_top, file_bot - file_top)
			  != (file_bot - file_top))
		      || ((close (fd)) < 0))
		    {
		      perror (split_file);
		      (void)close (fd);
		      exit (FATAL);
		    }

		  if (!indirect_info)
		    {
		      indirect_info = the_file + file_top;
		      (void)sprintf (indirect_info, "\037\nIndirect:\n");
		      indirect_info += strlen (indirect_info);
		    }

		  (void)sprintf (indirect_info, "%s-%d: %d\n",
			   root_filename, which_file, file_top);

		  free (split_file);
		  indirect_info += strlen (indirect_info);
		  which_file++;
		  break;
		}
	      }
	  }
      }

    /* We have sucessfully created the subfiles.  Now write out the
       original again.  We must use `output_stream', or
       write_tag_table_indirect () won't know where to place the output. */
    output_stream = fopen (filename, "w");
    if (!output_stream)
      {
	perror (filename);
	exit (FATAL);
      }

    {
      int distance = indirect_info - the_file;
      (void)fwrite (the_file, 1, distance, output_stream);

      /* Inhibit newlines. */
      paragraph_is_open = 0;

      write_tag_table_indirect ();
      (void)fclose (output_stream);
      free (the_header);
      free (the_file);
    }
  }
}

/* Some menu hacking.  This is used to remember menu references while
   reading the input file.  After the output file has been written, if
   validation is on, then we use the contents of NODE_REFERENCES as a
   list of nodes to validate. */
char *
reftype_type_string (type)
     enum reftype type;
{
  switch (type)
    {
    case menu_reference:
      return ("Menu");
    case followed_reference:
      return ("Followed-Reference");
    default:
      return ("Internal-bad-reference-type");
    }
}

/* Remember this node name for later validation use. */
void
remember_node_reference (node, line, type)
     char *node;
     int line;
     enum reftype type;
{
  NODE_REF *temp = (NODE_REF *) xmalloc (sizeof (NODE_REF));

  temp->next = node_references;
  temp->node = savestring (node);
  temp->line_no = line;
  temp->section = current_section;
  temp->type = type;
  temp->containing_node = savestring (current_node);
  temp->filename = node_filename;

  node_references = temp;
}

void
validate_other_references (ref_list)
     register NODE_REF *ref_list;
{
  char *old_input_filename = input_filename;

  while (ref_list != (NODE_REF *) 0)
    {
      input_filename = ref_list->filename;
      (void)validate (ref_list->node, ref_list->line_no,
		reftype_type_string (ref_list->type));
      ref_list = ref_list->next;
    }
  input_filename = old_input_filename;
}

/* Find NODE in REF_LIST. */
NODE_REF *
find_node_reference (node, ref_list)
     char *node;
     register NODE_REF *ref_list;
{
  while (ref_list)
    {
      if (stricmp (node, ref_list->node) == 0)
	break;
      ref_list = ref_list->next;
    }
  return (ref_list);
}

void
free_node_references ()
{
  register NODE_REF *list, *temp;

  list = node_references;

  while (list)
    {
      temp = list;
      free (list->node);
      free (list->containing_node);
      list = list->next;
      free((char *)temp);
    }
  node_references = (NODE_REF *) 0;
}

  /* This function gets called at the start of every line while inside of
     a menu.  It checks to see if the line starts with "* ", and if so,
     remembers the node reference that this menu refers to.
     input_text_offset is at the \n just before the line start. */
#define menu_starter "* "
char *
glean_node_from_menu (remember_reference)
     int remember_reference;
{
  int i, orig_offset = input_text_offset;
  char *nodename;

  if (strncmp (&input_text[input_text_offset + 1],
	       menu_starter,
	       strlen (menu_starter)) != 0)
    return ((char *)0);
  else
    input_text_offset += strlen (menu_starter) + 1;

  get_until_in_line (":", &nodename);
  if (curchar () == ':')
    input_text_offset++;
  canon_white (nodename);

  if (curchar () == ':')
    goto save_node;

  free (nodename);
  get_rest_of_line (&nodename);

  /* Special hack: If the nodename follows the menu item name,
     then we have to read the rest of the line in order to find
     out what the nodename is.  But we still have to read the
     line later, in order to process any formatting commands that
     might be present.  So un-count the carriage return that has just
     been counted. */
  line_number--;

  canon_white (nodename);
#if defined(__cplusplus) || defined(__STDC__)
  for (i = 0; (size_t)i < strlen (nodename); i++)
#else
  for (i = 0; i < strlen (nodename); i++)
#endif
    {
      if (nodename[i] == '\t' ||
	  nodename[i] == '.' ||
	  nodename[i] == ',')
	{
	  nodename[i] = '\0';
	  break;
	}
    }
save_node:
  input_text_offset = orig_offset;
  normalize_node_name (nodename);
  i = strlen (nodename);
  if (i && nodename[i - 1] == ':')
    nodename[i - 1] = '\0';

  if (remember_reference)
    {
      remember_node_reference (nodename, line_number, menu_reference);
      free (nodename);
      return ((char *)0);
    }
  else
    return (nodename);
}

int
cm_menu ()
{
  begin_insertion (menu);
  return DONTCARE;
}


/* **************************************************************** */
/*								    */
/*			Cross Reference Hacking			    */
/*								    */
/* **************************************************************** */

char *
get_xref_token ()
{
  char *string;

  get_until_in_braces (",", &string);
  if (curchar () == ',')
    input_text_offset++;
  fix_whitespace (string);
  return (string);
}

int px_ref_flag = 0;		/* Controls initial output string. */

/* Make a cross reference. */
int
cm_xref (arg)
{
  if (arg == START)
    {
      char *arg1, *arg2, *arg3, *arg4, *arg5;

      arg1 = get_xref_token ();
      arg2 = get_xref_token ();
      arg3 = get_xref_token ();
      arg4 = get_xref_token ();
      arg5 = get_xref_token ();

      add_word_args ("%s", px_ref_flag ? "*note " : "*Note ", "", 0, 0);

      if (*arg5 || *arg4)
	{
	  char *node_name;

	  if (!*arg2)
	    {
	      if (*arg3)
		node_name = arg3;
	      else
		node_name = arg1;
	    }
	  else
	    node_name = arg2;

	  (void)sprintf(exec_string, "%s: (%s)%s@bye\n", node_name, arg4, arg1);
          execute_string();
	  return DONTCARE;
	}
      else
	remember_node_reference (arg1, line_number, followed_reference);

      if (*arg3)
	{
	  if (!*arg2) {
	    (void)sprintf(exec_string, "%s: %s@bye\n", arg3, arg1);
            execute_string();
          } else {
	    (void)sprintf(exec_string, "%s: %s@bye\n", arg2, arg1);
            execute_string();
          }
	  return DONTCARE;
	}

      if (*arg2) {
	(void)sprintf(exec_string, "%s: %s@bye\n", arg2, arg1);
        execute_string();
      } else {
	(void)sprintf(exec_string, "%s::@bye\n", arg1);
        execute_string();
      }
    }
  else
    {

      /* Check to make sure that the next non-whitespace character is either
         a period or a comma. input_text_offset is pointing at the "}" which
         ended the xref or pxref command. */
      int temp = input_text_offset + 1;

      if (output_paragraph[output_paragraph_offset - 2] == ':' &&
	  output_paragraph[output_paragraph_offset - 1] == ':')
	return DONTCARE;
      while (temp < size_of_input_text) {
	if (cr_or_whitespace (input_text[temp])) temp++;
	else {
	  if (input_text[temp] != '.' &&
              input_text[temp] != ',' &&
              input_text[temp] != '\t') {
            line_error();
            (void)fprintf(stderr,
              "Cross-reference must be terminated with a period or a comma.\n");
          }
          return DONTCARE;
	}
      }
    }
  return DONTCARE;
}

int
cm_pxref (arg)
     int arg;
{
  if (arg == START)
    {
      px_ref_flag++;
      cm_xref (arg);
      px_ref_flag--;
    }
  else
    add_char ('.');
  return DONTCARE;
}

int
cm_inforef (arg)
     int arg;
{
  if (arg == START)
    {
      char *node, *pname, *file;

      node = get_xref_token ();
      pname = get_xref_token ();
      file = get_xref_token ();

      (void)sprintf(exec_string, "*note %s: (%s)%s@bye\n", pname, file, node);
      execute_string();
    }
  return DONTCARE;
}

/* **************************************************************** */
/*								    */
/*			Insertion Command Stubs			    */
/*								    */
/* **************************************************************** */

int
cm_quotation ()
{
  begin_insertion (quotation);
  return DONTCARE;
}

int
cm_example ()
{
  begin_insertion (example);
  return DONTCARE;
}

int
cm_smallexample ()
{
  begin_insertion (smallexample);
  return DONTCARE;
}

int
cm_lisp ()
{
  begin_insertion (lisp);
  return DONTCARE;
}

int
cm_smalllisp ()
{
  begin_insertion (smalllisp);
  return DONTCARE;
}

/* @cartouche/@end cartouche draws box with rounded corners in
   TeX output.  Right now, just a NOP insertion. */
int
cm_cartouche ()
{
  begin_insertion (cartouche);
  return DONTCARE;
}

int
cm_format ()
{
  begin_insertion (format);
  return DONTCARE;
}

int
cm_display ()
{
  begin_insertion (display);
  return DONTCARE;
}

int
cm_smalldisplay ()
{
  begin_insertion (smalldisplay);
  return DONTCARE;
}

int
cm_itemize ()
{
  begin_insertion (itemize);
  return DONTCARE;
}

int
cm_enumerate ()
{
  get_until_in_line (".", &enumeration_arg);
  canon_white (enumeration_arg);

  if (!*enumeration_arg) {
    free (enumeration_arg);
    enumeration_arg = savestring ("1");
  }

  if (!isdigit (*enumeration_arg) && !isletter (*enumeration_arg)) {
    if (print_warnings) {
      warning();
      (void)fprintf(stderr, "%s requires a letter or a digit.\n",
        insertion_type_pname (enumerate));
    }
    enumeration_arg = savestring ("1");
  }
  begin_insertion (enumerate);
  return DONTCARE;
}

int
cm_table ()
{
  begin_insertion (table);
  return DONTCARE;
}

int
cm_ftable ()
{
  begin_insertion (ftable);
  return DONTCARE;
}

int
cm_vtable ()
{
  begin_insertion (vtable);
  return DONTCARE;
}

int
cm_group ()
{
  begin_insertion (group);
  return DONTCARE;
}

int
cm_ifinfo ()
{
  begin_insertion (ifinfo);
  return DONTCARE;
}

int
cm_ifnottex ()
{
  begin_insertion (ifnottex);
  return DONTCARE;
}

/* Begin an insertion where the lines are not filled or indented. */
int
cm_flushleft ()
{
  begin_insertion (flushleft);
  return DONTCARE;
}

/* Begin an insertion where the lines are not filled, and each line is
   forced to the right-hand side of the page. */
int
cm_flushright ()
{
  begin_insertion (flushright);
  return DONTCARE;
}


/* **************************************************************** */
/*								    */
/*			  Conditional Handling			    */
/*								    */
/* **************************************************************** */

/* A structure which contains `defined' variables. */
typedef struct _defines {
  struct _defines *next;
  char *name;
} DEFINE;

/* The linked list of `set' defines. */
DEFINE *defines = (DEFINE *)0;

/* Add NAME to the list of `set' defines. */
void
set (name)
     char *name;
{
  DEFINE *temp;

  for (temp = defines; temp; temp = temp->next)
    if (strcmp (name, temp->name) == 0)
      return;

  temp = (DEFINE *)xmalloc (sizeof (DEFINE));
  temp->next = defines;
  temp->name = savestring (name);
  defines = temp;
}

/* Remove NAME from the list of `set' defines. */
void
clear (name)
     char *name;
{
  register DEFINE *temp, *last;

  last = (DEFINE *)0;
  temp = defines;

  while (temp)
    {
      if (strcmp (temp->name, name) == 0)
	{
	  if (last)
	    last->next = temp->next;
	  else
	    defines = temp->next;

	  free (temp->name);
	  free((char *)temp);
	  break;
	}
      last = temp;
      temp = temp->next;
    }
}

/* Return non-zero if NAME is present in the list of `set' defines. */
int
set_p (name)
     char *name;
{
  register DEFINE *temp;

  for (temp = defines; temp; temp = temp->next)
    if (strcmp (temp->name, name) == 0)
      return (1);

  return (0);
}

/* Conditionally parse based on the current command name. */
int
command_name_condition ()
{
  char discarder[128];

  (void)sprintf (discarder, "\n@end %s", command);
  discard_until (discarder);
  discard_until ("\n");
  return DONTCARE;
}

#define SET	1
#define CLEAR	2
#define IFSET	3
#define IFCLEAR	4

/* Create a variable whose name is the rest of the line. */
int
cm_set ()
{
  handle_variable (SET);
  return DONTCARE;
}

/* Remove a variable whose name is the rest of the line. */
int
cm_clear ()
{
  handle_variable (CLEAR);
  return DONTCARE;
}

int
cm_ifset ()
{
  handle_variable (IFSET);
  return DONTCARE;
}

int
cm_ifclear ()
{
  handle_variable (IFCLEAR);
  return DONTCARE;
}

/* Set, clear, or conditionalize based on ACTION. */
void
handle_variable (action)
     int action;
{
  char *name;

  get_rest_of_line (&name);
  backup_input_pointer ();
  canon_white (name);

  if (!*name) {
    line_error();
    (void)fprintf(stderr, "@%s requires a name.\n", command);
  } else
    {
      switch (action)
	{
	case SET:
	  set (name);
	  break;

	case CLEAR:
	  clear (name);
	  break;

	case IFSET:
	  if (!set_p (name))
	    {
	      discard_until ("\n@end ifset");
	      discard_until ("\n");
	    }
	  else
	    begin_insertion (ifset);
	  break;

	case IFCLEAR:
	  if (set_p (name))
	    {
	      discard_until ("\n@end ifclear");
	      discard_until ("\n");
	    }
	  else
	    begin_insertion (ifclear);
	  break;
	}
    }
  free (name);
}

/* **************************************************************** */
/*								    */
/*			@itemx, @item				    */
/*								    */
/* **************************************************************** */

/* Non-zero means a string is in execution, as opposed to a file. */
int executing_string = 0;

/* Execute the string produced by formatting the ARGs with FORMAT.  This
   is like submitting a new file with @include. */
void
execute_string()
{
  pushfile ();
  input_text_offset = 0;
  input_text = exec_string;
  input_filename = savestring (input_filename);
  size_of_input_text = strlen (exec_string);

  executing_string++;
  reader_loop ();

  popfile ();
  executing_string--;

  free_and_clear (&command);
  command = savestring ("not bye");
}

int itemx_flag = 0;

int
cm_itemx ()
{
  itemx_flag++;
  cm_item ();
  itemx_flag--;
  return DONTCARE;
}

int
cm_item ()
{
  char *rest_of_line, *item_func;

  /* Can only hack "@item" while inside of an insertion. */
  if (insertion_level)
    {
      INSERTION_ELT *stack = insertion_stack;

      get_rest_of_line (&rest_of_line);
      canon_white (rest_of_line);
      item_func = current_item_function ();

      /* Okay, do the right thing depending on which insertion function
	 is active. */

    switch_top:
      switch (stack->insertion)
	{
	default: break;
	case ifinfo:
	case ifnottex:
	case ifset:
	case ifclear:
	case cartouche:
	  stack = stack->next;
	  if (!stack)
	    goto no_insertion;
	  else
	    goto switch_top;
	  break;

	case menu:
	case quotation:
	case example:
	case smallexample:
	case lisp:
	case smalllisp:
	case format:
	case display:
	case smalldisplay:
	case group:
	  line_error();
          (void)fprintf(stderr,
            "The `@%s' command is meaningless within a `@%s' block.\n",
            command, insertion_type_pname (current_insertion_type ()));
	  break;

	case itemize:
	case enumerate:
	  if (itemx_flag) {
	    line_error();
            (void)fprintf(stderr,
              "@itemx is not meaningful inside of a `%s' block.\n",
              insertion_type_pname (current_insertion_type ()));
	  } else {
	    start_paragraph ();
	    kill_self_indent (-1);
	    filling_enabled = indented_fill = 1;

	    if (current_insertion_type () == itemize) {
		  indent (output_column = current_indent - 2);

		  /* I need some way to determine whether this command
		     takes braces or not.  I believe the user can type
		     either "@bullet" or "@bullet{}".  Of course, they
		     can also type "o" or "#" or whatever else they want. */
		  if (item_func && *item_func) {
		    if (*item_func == '@')
                      if (item_func[strlen (item_func) - 1] != '}') {
			(void)sprintf(exec_string, "%s{}@bye\n", item_func);
                        execute_string();
                      } else {
			(void)sprintf(exec_string, "%s@bye\n", item_func);
                        execute_string();
                      }
		    else {
                      (void)sprintf(exec_string, "%s@bye\n", item_func);
                      execute_string();
                    }
		  }
		  insert (' ');
		  output_column++;
		}
	      else
		enumerate_item ();

	      /* Special hack.  This makes close paragraph ignore you until
		 the start_paragraph () function has been called. */
	      must_start_paragraph = 1;
	    }
	  break;

	case table:
	case ftable:
	case vtable:
	  {
	    /* Get rid of extra characters. */
	    kill_self_indent (-1);

	    /* close_paragraph () almost does what we want.  The problem
	       is when paragraph_is_open, and last_char_was_newline, and
	       the last newline has been turned into a space, because
	       filling_enabled. I handle it here. */
	    if (last_char_was_newline && filling_enabled && paragraph_is_open)
	      insert ('\n');
	    close_paragraph ();

#if defined (INDENT_PARAGRAPHS_IN_TABLE)
	    /* Indent on a new line, but back up one indentation level. */
	    /* force existing indentation. */
	    {
	      int t;

	      t = inhibit_paragraph_indentation;
	      inhibit_paragraph_indentation = 1;
	      add_char ('i');
	      inhibit_paragraph_indentation = t;
	    }
#else /* !INDENT_PARAGRAPHS_IN_TABLE */
	    add_char ('i');
#endif /* !INDENT_PARAGRAPHS_IN_TABLE */

	    output_paragraph_offset--;
	    kill_self_indent (default_indentation_increment + 1);

	    /* Add item's argument to the line. */
	    filling_enabled = 0;
	    if (!item_func && !(*item_func)) {
	      (void)sprintf(exec_string, "%s@bye\n", rest_of_line);
              execute_string();
            } else {
	      (void)sprintf(exec_string, "%s{%s}@bye\n", item_func, rest_of_line);
              execute_string();
            }

	    if (current_insertion_type () == ftable) {
	      (void)sprintf(exec_string, "@findex %s\n@bye\n", rest_of_line);
              execute_string();
            }

	    if (current_insertion_type () == vtable) {
	      (void)sprintf(exec_string, "@vindex %s\n@bye\n", rest_of_line);
              execute_string();
            }

	    /* Start a new line, and let start_paragraph ()
	       do the indenting of it for you. */
	    close_single_paragraph ();
	    indented_fill = filling_enabled = 1;
	  }
	}
      free (rest_of_line);
    } else {
no_insertion:
      line_error();
      (void)fprintf(stderr,
        "@%s found outside of an insertion block.\n", command);
    }
  return DONTCARE;
}


/* **************************************************************** */
/*								    */
/*			Defun and Friends       		    */
/*								    */
/* **************************************************************** */

#define DEFUN_SELF_DELIMITING(c)					\
  (((c) == '(')								\
   || ((c) == ')')							\
   || ((c) == '[')							\
   || ((c) == ']'))

struct token_accumulator
{
  unsigned int length;
  unsigned int index;
  char **tokens;
};

void
initialize_token_accumulator (accumulator)
     struct token_accumulator *accumulator;
{
  (accumulator->length) = 0;
  (accumulator->index) = 0;
  (accumulator->tokens) = NULL;
}

void
accumulate_token (accumulator, token)
     struct token_accumulator *accumulator;
     char *token;
{
  if ((accumulator->index) >= (accumulator->length))
    {
      (accumulator->length) += 10;
      (accumulator->tokens) = (char **) xrealloc
	((char *)accumulator->tokens,
        (int)(accumulator->length * sizeof (char *)));
    }
  accumulator->tokens[accumulator->index] = token;
  accumulator->index += 1;
}

char *
copy_substring (start, end)
     char *start;
     char *end;
{
  char *result, *scan, *scan_result;

  result = (char *) xmalloc ((end - start) + 1);
  scan_result = result;
  scan = start;

  while (scan < end)
    *scan_result++ = *scan++;

  *scan_result = '\0';
  return (result);
}

/* Given `string' pointing at an open brace, skip forward and return a
   pointer to just past the matching close brace. */
int
scan_group_in_string (string_pointer)
     char **string_pointer;
{
  register int c;
  register char *scan_string;
  register unsigned int level = 1;

  scan_string = (*string_pointer) + 1;

  while (1)
    {
      if (level == 0)
	{
	  (*string_pointer) = scan_string;
	  return (1);
	}
      c = (*scan_string++);
      if (c == '\0') {
	/* Tweak line_number to compensate for fact that
	   we gobbled the whole line before coming here. */
	line_number -= 1;
	line_error();
        (void)fprintf(stderr, "Missing `}' in @def arg.\n");
	line_number += 1;
	(*string_pointer) = (scan_string - 1);
	return (0);
      }
      if (c == '{') level += 1;
      if (c == '}') level -= 1;
    }
}

/* Return a list of tokens from the contents of `string'.
   Commands and brace-delimited groups count as single tokens.
   Contiguous whitespace characters are converted to a token
   consisting of a single space. */
char **
args_from_string (string)
     char *string;
{
  struct token_accumulator accumulator;
  register char *scan_string = string;
  char *token_start, *token_end;

  initialize_token_accumulator (&accumulator);

  while ((*scan_string) != '\0')
    {
      /* Replace arbitrary whitespace by a single space. */
      if (whitespace (*scan_string))
	{
	  scan_string += 1;
	  while (whitespace (*scan_string))
	    scan_string += 1;
	  accumulate_token ((&accumulator), (savestring (" ")));
	  continue;
	}

      /* Commands count as single tokens. */
      if ((*scan_string) == COMMAND_PREFIX)
	{
	  token_start = scan_string;
	  scan_string += 1;
	  if (self_delimiting (*scan_string))
	    scan_string += 1;
	  else
	    {
	      register int c;
	      while (1)
		{
		  c = *scan_string++;

 		  if ((c == '\0') || (c == '{') || (whitespace (c)))
		    {
		      scan_string -= 1;
		      break;
		    }
		}

	      if (*scan_string == '{')
		{
		  char *s = scan_string;
		  (void) scan_group_in_string (&s);
		  scan_string = s;
		}
	    }
	  token_end = scan_string;
	}

      /* Parentheses and brackets are self-delimiting. */
      else if (DEFUN_SELF_DELIMITING (*scan_string))
	{
	  token_start = scan_string;
	  scan_string += 1;
	  token_end = scan_string;
	}

      /* Open brace introduces a group that is a single token. */
      else if (*scan_string == '{')
	{
	  char *s = scan_string;
	  int balanced = scan_group_in_string (&s);

	  token_start = scan_string + 1;
	  scan_string = s;
	  token_end = balanced ? (scan_string - 1) : scan_string;
	}

      /* Otherwise a token is delimited by whitespace, parentheses,
	 brackets, or braces.  A token is also ended by a command. */
      else
	{
	  token_start = scan_string;

	  while (1)
	    {
	      register int c;

	      c = *scan_string++;

	      if (!c ||
		  (whitespace (c) || DEFUN_SELF_DELIMITING (c) ||
		   c == '{' || c == '}'))
		{
		  scan_string--;
		  break;
		}

	      /* If we encounter a command imbedded within a token,
		 then end the token. */
	      if (c == COMMAND_PREFIX)
		{
		  scan_string--;
		  break;
		}
	    }
	  token_end = scan_string;
	}

      accumulate_token
	(&accumulator, copy_substring (token_start, token_end));
    }
  accumulate_token (&accumulator, (char *)0);
  return (accumulator.tokens);
}

void
process_defun_args (defun_args, auto_var_p)
     char **defun_args;
     int auto_var_p;
{
  int pending_space = 0;

  while (1)
    {
      char *defun_arg = *defun_args++;

      if (defun_arg == NULL)
	break;

      if (defun_arg[0] == ' ')
	{
	  pending_space = 1;
	  continue;
	}

      if (pending_space)
	{
	  add_char (' ');
	  pending_space = 0;
	}

      if (DEFUN_SELF_DELIMITING (defun_arg[0]))
	add_char (defun_arg[0]);
      else if (defun_arg[0] == '&')
	add_word (defun_arg);
      else if (defun_arg[0] == COMMAND_PREFIX) {
	(void)sprintf(exec_string, "%s@bye\n", defun_arg);
        execute_string();
      } else if (auto_var_p) {
	(void)sprintf(exec_string, "@var{%s}@bye\n", defun_arg);
        execute_string();
      }
      else
	add_word (defun_arg);
    }
}

char *
next_nonwhite_defun_arg (arg_pointer)
     char ***arg_pointer;
{
  char **scan = (*arg_pointer);
  char *arg = (*scan++);

  if ((arg != 0) && (*arg == ' '))
    arg = *scan++;

  if (arg == 0)
    scan -= 1;

  *arg_pointer = scan;

  return ((arg == 0) ? "" : arg);
}

/* Make the defun type insertion.
   TYPE says which insertion this is.
   X_P says not to start a new insertion if non-zero. */
void
defun_internal (type, x_p)
     enum insertion_type type;
     int x_p;
{
  enum insertion_type base_type;
  char **defun_args, **scan_args;
  char *category, *defined_name, *type_name, *type_name2;

  {
    char *line;
    get_rest_of_line (&line);
    defun_args = (args_from_string (line));
    free (line);
  }

  scan_args = defun_args;

  switch (type)
    {
    case defun:
      category = "Function";
      base_type = deffn;
      break;
    case defmac:
      category = "Macro";
      base_type = deffn;
      break;
    case defspec:
      category = "Special Form";
      base_type = deffn;
      break;
    case defvar:
      category = "Variable";
      base_type = defvr;
      break;
    case defopt:
      category = "User Option";
      base_type = defvr;
      break;
    case deftypefun:
      category = "Function";
      base_type = deftypefn;
      break;
    case deftypevar:
      category = "Variable";
      base_type = deftypevr;
      break;
    case defivar:
      category = "Instance Variable";
      base_type = defcv;
      break;
    case defmethod:
      category = "Method";
      base_type = defop;
      break;
    case deftypemethod:
      category = "Method";
      base_type = deftypemethod;
      break;
    default:
      category = next_nonwhite_defun_arg (&scan_args);
      base_type = type;
      break;
    }

  if ((base_type == deftypefn)
      || (base_type == deftypevr)
      || (base_type == defcv)
      || (base_type == defop)
      || (base_type == deftypemethod))
    type_name = next_nonwhite_defun_arg (&scan_args);

  if (base_type == deftypemethod)
    type_name2 = next_nonwhite_defun_arg (&scan_args);

  defined_name = next_nonwhite_defun_arg (&scan_args);

  /* This hack exists solely for the purposes of formatting the texinfo
     manual.  I couldn't think of a better way.  The token might be
     a simple @@ followed immediately by more text.  If this is the case,
     then the next defun arg is part of this one, and we should concatenate
     them. */
  if (*scan_args && **scan_args && !whitespace (**scan_args) &&
      (strcmp (defined_name, "@@") == 0))
    {
      char *tem = (char *)xmalloc (3 + strlen (scan_args[0]));

      (void)sprintf (tem, "@@%s", scan_args[0]);

      free (scan_args[0]);
      scan_args[0] = tem;
      scan_args++;
      defined_name = tem;
    }

  if (!x_p)
    begin_insertion (type);

  /* Write the definition header line.
     This should start at the normal indentation.  */
  current_indent -= default_indentation_increment;
  start_paragraph ();

  switch (base_type)
    {
    default: break;
    case deffn:
    case defvr:
    case deftp:
      (void)sprintf(exec_string, " -- %s: %s@bye\n", category, defined_name);
      execute_string();
      break;
    case deftypefn:
    case deftypevr:
      (void)sprintf(exec_string, " -- %s: %s %s@bye\n", category, type_name, defined_name);
      execute_string();
      break;
    case defcv:
      (void)sprintf(exec_string, " -- %s of %s: %s@bye\n", category, type_name, defined_name);
      execute_string();
      break;
    case defop:
      (void)sprintf(exec_string, " -- %s on %s: %s@bye\n", category, type_name, defined_name);
      execute_string();
      break;
    case deftypemethod:
      (void)sprintf(exec_string, " -- %s on %s: %s %s@bye\n", category, type_name, type_name2,
		      defined_name);
      execute_string();
      break;
    }
  current_indent += default_indentation_increment;

  /* Now process the function arguments, if any.
     If these carry onto the next line, they should be indented by two
     increments to distinguish them from the body of the definition,
     which is indented by one increment.  */
  current_indent += default_indentation_increment;

  switch (base_type)
    {
    default: break;
    case deffn:
    case defop:
      process_defun_args (scan_args, 1);
      break;
    case deftp:
    case deftypefn:
    case deftypemethod:
      process_defun_args (scan_args, 0);
      break;
    }
  current_indent -= default_indentation_increment;
  close_single_paragraph ();

  /* Make an entry in the appropriate index. */
  switch (base_type)
    {
    default: break;
    case deffn:
    case deftypefn:
      (void)sprintf(exec_string, "@findex %s\n@bye\n", defined_name);
      execute_string();
      break;
    case defvr:
    case deftypevr:
    case defcv:
      (void)sprintf(exec_string, "@vindex %s\n@bye\n", defined_name);
      execute_string();
      break;
    case defop:
    case deftypemethod:
      (void)sprintf(exec_string, "@findex %s on %s\n@bye\n", defined_name, type_name);
      execute_string();
      break;
    case deftp:
      (void)sprintf(exec_string, "@tindex %s\n@bye\n", defined_name);
      execute_string();
      break;
    }

  /* Deallocate the token list. */
  scan_args = defun_args;
  while (1)
    {
      char * arg = (*scan_args++);
      if (arg == NULL)
	break;
      free (arg);
    }
  free((char *)defun_args);
}

/* Add an entry for a function, macro, special form, variable, or option.
   If the name of the calling command ends in `x', then this is an extra
   entry included in the body of an insertion of the same type. */
int
cm_defun ()
{
  int x_p;
  enum insertion_type type;
  char *temp = savestring (command);

  x_p = (command[strlen (command) - 1] == 'x');

  if (x_p)
    temp[strlen (temp) - 1] = '\0';

  type = find_type_from_name (temp);
  free (temp);

  /* If we are adding to an already existing insertion, then make sure
     that we are already in an insertion of type TYPE. */
  if (x_p && (!insertion_level || insertion_stack->insertion != type)) {
    line_error();
    (void)fprintf(stderr,
      "Must be in a `%s' insertion in order to use `%s'x.\n",
      command, command);
    discard_until ("\n");
    return DONTCARE;
  }

  defun_internal (type, x_p);
  return DONTCARE;
}

/* End existing insertion block. */
int
cm_end ()
{
  char *temp;
  enum insertion_type type;

  if (!insertion_level) {
    line_error();
    (void)fprintf(stderr, "Unmatched `@%s'.\n", command);
    return DONTCARE;
  }

  get_rest_of_line (&temp);
  canon_white (temp);

  if (strlen (temp) == 0) {
    line_error();
    (void)fprintf(stderr, "`@%s' needs something after it.\n", command);
  }

  type = find_type_from_name (temp);

  if (type == bad_type) {
    line_error();
    (void)fprintf(stderr, "Bad argument to `%s', `%s', using `%s'.\n",
      command, temp, insertion_type_pname (current_insertion_type ()));
    return DONTCARE;
  }
  end_insertion (type);
  free (temp);
  return DONTCARE;
}


/* **************************************************************** */
/*								    */
/*			Other Random Commands		   	    */
/*								    */
/* **************************************************************** */

/* This says to inhibit the indentation of the next paragraph, but
   not of following paragraphs.  */
int
cm_noindent ()
{
  if (!inhibit_paragraph_indentation)
    inhibit_paragraph_indentation = -1;
  return DONTCARE;
}

/* I don't know exactly what to do with this.  Should I allow
   someone to switch filenames in the middle of output?  Since the
   file could be partially written, this doesn't seem to make sense.
   Another option: ignore it, since they don't *really* want to
   switch files.  Finally, complain, or at least warn. */
int
cm_setfilename ()
{
  char *filename;
  get_rest_of_line (&filename);
  /* warning ("`@%s %s' encountered and ignored", command, filename); */
  free (filename);
  return DONTCARE;
}

int
cm_comment ()
{
  discard_until ("\n");
  return DONTCARE;
}

/* @br can be immediately followed by `{}', so we have to read those here.
   It should simply close the paragraph. */
int
cm_br ()
{
  if (looking_at ("{}"))
    input_text_offset += 2;

  if (curchar () == '\n')
    {
      input_text_offset++;
      line_number++;
    }

  close_paragraph ();
  return DONTCARE;
}

 /* Insert the number of blank lines passed as argument. */
int
cm_sp ()
{
  int lines;
  char *line;

  get_rest_of_line (&line);

  (void)sscanf (line, "%d", &lines);
  while (lines--)
    add_char ('\n');
  free (line);
  return DONTCARE;
}

int
cm_settitle ()
{
  discard_until ("\n");
  return DONTCARE;
}

int
cm_need ()
{
  discard_until ("\n");
  return DONTCARE;
}

int
cm_headings ()
{
  discard_until ("\n");
  return DONTCARE;
}

/* Start a new line with just this text on it.
   Then center the line of text.
   This always ends the current paragraph. */
int
cm_center ()
{
  char *line;
  int start, length;

  close_paragraph ();
  filling_enabled = indented_fill = 0;

  get_rest_of_line (&line);

  start = output_paragraph_offset;
  (void)sprintf(exec_string, "%s@bye\n", line);
  execute_string();
  length = output_paragraph_offset - start;
  free (line);

  if (length < fill_column)
    {
      int i;

      line = (char *)xmalloc (1 + length);
      (void)strncpy (line, ((char *)output_paragraph) + start, length);
      line[length] = '\0';

      i = (fill_column - length) / 2;
      output_paragraph_offset = start;
      while (i--)
	insert (' ');

      for (i = 0; i < length; i++)
	insert (line[i]);

      free (line);
    }

  insert ('\n');
  close_paragraph ();
  filling_enabled = 1;
  return DONTCARE;
}

/* Show what an expression returns. */
int
cm_result (arg)
     int arg;
{
  if (arg == END)
    add_word ("=>");
  return DONTCARE;
}

/* What an expression expands to. */
int
cm_expansion (arg)
     int arg;
{
  if (arg == END)
    add_word ("==>");
  return DONTCARE;
}

/* Indicates two expressions are equivalent. */
int
cm_equiv (arg)
     int arg;
{
  if (arg == END)
    add_word ("==");
  return DONTCARE;
}

/* What an expression may print. */
int
cm_print (arg)
     int arg;
{
  if (arg == END)
    add_word ("-|");
  return DONTCARE;
}

/* An error signaled. */
int
cm_error (arg)
     int arg;
{
  if (arg == END)
    add_word ("error-->");
  return DONTCARE;
}

/* The location of point in an example of a buffer. */
int
cm_point (arg)
     int arg;
{
  if (arg == END)
    add_word ("-!-");
  return DONTCARE;
}

/* Start a new line with just this text on it.
   The text is outdented one level if possible. */
int
cm_exdent ()
{
  char *line;
  int i = current_indent;

  if (current_indent)
    current_indent -= default_indentation_increment;

  get_rest_of_line (&line);
  close_single_paragraph ();
  add_word_args ("%s", line, "", 0, 0);
  current_indent = i;
  free (line);
  close_single_paragraph ();
  return DONTCARE;
}

int
cm_include ()
{
  cm_infoinclude ();
  return DONTCARE;
}

/* Remember this file, and move onto the next. */
int
cm_infoinclude ()
{
  char *filename;

  close_paragraph ();
  get_rest_of_line (&filename);
  pushfile ();

  /* In verbose mode we print info about including another file. */
  if (verbose_mode)
    {
      register int i = 0;
      register FSTACK *stack = filestack;

      for (i = 0, stack = filestack; stack; stack = stack->next, i++);

      i *= 2;

      (void)printf ("%*s", i, "");
      (void)printf ("%c%s %s\n", COMMAND_PREFIX, command, filename);
      (void)fflush (stdout);
    }

  if (!find_and_load (filename)) {
    popfile ();

    /* Cannot "@include foo", in line 5 of "/wh/bar". */
    line_error();
    (void)fprintf(stderr, "%c%s ", COMMAND_PREFIX, command); perror(filename);
    }
  free (filename);
  return DONTCARE;
}

/* The other side of a malformed expression. */
int
misplaced_brace ()
{
  line_error();
  (void)fprintf(stderr, "Misplaced `}'.\n");
  return DONTCARE;
}

/* Don't let the filling algorithm insert extra whitespace here. */
int
cm_force_abbreviated_whitespace ()
{
  return DONTCARE;
}

/* Do not let this character signify the end of a sentence, though
   if it was seen without the command prefix it normally would.  We
   do this by turning on the 8th bit of the character. */
int
cm_ignore_sentence_ender ()
{
  add_char (META ((*command)));
  return DONTCARE;
}

/* Signals end of processing.  Easy to make this happen. */
int
cm_bye ()
{
  input_text_offset = size_of_input_text;
  return DONTCARE;
}

int
cm_asis ()
{
  return DONTCARE;
}

int
cm_math ()
{
  return DONTCARE;
}

int
cm_setchapternewpage ()
{
  discard_until ("\n");
  return DONTCARE;
}

int
cm_smallbook ()
{
  discard_until ("\n");
  return DONTCARE;
}

/* **************************************************************** */
/*								    */
/*			Indexing Stuff				    */
/*								    */
/* **************************************************************** */


/* An index element... */
typedef struct index_elt
{
  struct index_elt *next;
  char *entry;			/* The index entry itself. */
  char *node;			/* The node from whence it came. */
  int code;			/* Non-zero means add `@code{...}' when
				   printing this element. */
  int defining_line;		/* Line number where this entry was written. */
} INDEX_ELT;

/* A list of short-names for each index, and the index to that index in our
   index array, the_indices.  In addition, for each index, it is remembered
   whether that index is a code index or not.  Code indices have @code{}
   inserted around the first word when they are printed with printindex. */
typedef struct
{
  char *name;
  int index;
  int code;
} INDEX_ALIST;

INDEX_ALIST **name_index_alist = (INDEX_ALIST **) 0;

/* An array of pointers.  Each one is for a different index.  The
   "synindex" command changes which array slot is pointed to by a
   given "index". */
INDEX_ELT **the_indices = (INDEX_ELT **) 0;

/* The number of defined indices. */
int defined_indices = 0;

/* We predefine these. */
#define program_index 0
#define function_index 1
#define concept_index 2
#define variable_index 3
#define datatype_index 4
#define key_index 5

/* Find which element in the known list of indices has this name.
   Returns -1 if NAME isn't found. */
int
find_index_offset (name)
     char *name;
{
  register int i;
  for (i = 0; i < defined_indices; i++)
    if (name_index_alist[i] &&
	stricmp (name, name_index_alist[i]->name) == 0)
      return (name_index_alist[i]->index);
  return (-1);
}

/* Return a pointer to the entry of (name . index) for this name.
   Return NULL if the index doesn't exist. */
INDEX_ALIST *
find_index (name)
     char *name;
{
  int offset = find_index_offset (name);
  if (offset > -1)
    return (name_index_alist[offset]);
  else
    return ((INDEX_ALIST *) 0);
}

/* Given an index name, return the offset in the_indices of this index,
   or -1 if there is no such index. */
int
translate_index (name)
     char *name;
{
  INDEX_ALIST *which = find_index (name);

  if (which)
    return (which->index);
  else
    return (-1);
}

/* Return the index list which belongs to NAME. */
INDEX_ELT *
index_list (name)
     char *name;
{
  int which = translate_index (name);
  if (which < 0)
    return ((INDEX_ELT *) 0);
  else
    return (the_indices[which]);
}

/* Please release me, let me go... */
void
free_index (index)
     INDEX_ELT *index;
{
  INDEX_ELT *temp;

  while ((temp = index) != (INDEX_ELT *) 0)
    {
      free (temp->entry);
      free (temp->node);
      index = index->next;
      free((char *)temp);
    }
}

/* Flush an index by name. */
void
undefindex (name)
     char *name;
{
  int i;
  int which = find_index_offset (name);

  if (which < 0) return ;

  i = name_index_alist[which]->index;


  free_index (the_indices[i]);
  the_indices[i] = (INDEX_ELT *) 0;

  free (name_index_alist[which]->name);
  free((char *)name_index_alist[which]);
  name_index_alist[which] = (INDEX_ALIST *) 0;
}

/* Define an index known as NAME.  We assign the slot number.
   CODE if non-zero says to make this a code index. */
void
defindex (name, code)
     char *name;
     int code;
{
  register int i, slot;

  /* If it already exists, flush it. */
  undefindex (name);

  /* Try to find an empty slot. */
  slot = -1;
  for (i = 0; i < defined_indices; i++)
    if (!name_index_alist[i])
      {
	slot = i;
	break;
      }

  if (slot < 0)
    {
      /* No such luck.  Make space for another index. */
      slot = defined_indices;
      defined_indices++;

      name_index_alist = (INDEX_ALIST **)
	xrealloc ((char *)name_index_alist,
		  (1 + defined_indices) * sizeof (INDEX_ALIST *));
      the_indices = (INDEX_ELT **)
	xrealloc ((char *)the_indices,
		  (1 + defined_indices) * sizeof (INDEX_ELT *));
    }

  /* We have a slot.  Start assigning. */
  name_index_alist[slot] = (INDEX_ALIST *) xmalloc (sizeof (INDEX_ALIST));
  name_index_alist[slot]->name = savestring (name);
  name_index_alist[slot]->index = slot;
  name_index_alist[slot]->code = code;

  the_indices[slot] = (INDEX_ELT *) 0;
}

void
init_indices ()
{
  int i;

  /* Create the default data structures. */

  /* Initialize data space. */
  if (!the_indices)
    {
      the_indices = (INDEX_ELT **) xmalloc ((1 + defined_indices) *
					    sizeof (INDEX_ELT *));
      the_indices[defined_indices] = (INDEX_ELT *) 0;

      name_index_alist = (INDEX_ALIST **) xmalloc ((1 + defined_indices) *
						   sizeof (INDEX_ALIST *));
      name_index_alist[defined_indices] = (INDEX_ALIST *) 0;
    }

  /* If there were existing indices, get rid of them now. */
  for (i = 0; i < defined_indices; i++)
    undefindex (name_index_alist[i]->name);

  /* Add the default indices. */
  defindex ("pg", 0);
  defindex ("fn", 1);		/* "fn" is a code index.  */
  defindex ("cp", 0);
  defindex ("vr", 0);
  defindex ("tp", 0);
  defindex ("ky", 0);

}

/* Add the arguments to the current index command to the index NAME. */
void
index_add_arg (name)
     char *name;
{
  int which;
  char *index_entry;
  INDEX_ALIST *tem;

  tem = find_index (name);

  which = tem ? tem->index : -1;

  get_rest_of_line (&index_entry);
  ignore_blank_line ();

  if (which < 0) {
    line_error();
    (void)fprintf(stderr, "Unknown index reference `%s'.\n", name);
    free (index_entry);
  } else {
    INDEX_ELT *new = (INDEX_ELT *) xmalloc (sizeof (INDEX_ELT));
    new->next = the_indices[which];
    new->entry = index_entry;
    new->node = current_node;
    new->code = tem->code;
    new->defining_line = line_number - 1;
    the_indices[which] = new;
  }
}

#define INDEX_COMMAND_SUFFIX "index"

/* The function which user defined index commands call. */
int
gen_index ()
{
  char *name = savestring (command);
#if defined(__cplusplus) || defined(__STDC__)
  if ((size_t)strlen (name) >= (size_t)strlen ("index"))
#else
  if (strlen (name) >= strlen ("index"))
#endif
    name[strlen (name) - strlen ("index")] = '\0';
  index_add_arg (name);
  free (name);
  return DONTCARE;
}

/* Define a new index command.  Arg is name of index. */
int
cm_defindex ()
{
  gen_defindex (0);
  return DONTCARE;
}

int
cm_defcodeindex ()
{
  gen_defindex (1);
  return DONTCARE;
}

void
gen_defindex (code)
     int code;
{
  char *name;
  get_rest_of_line (&name);

  if (find_index (name)) {
    line_error();
    (void)fprintf(stderr, "Index `%s' already exists.\n", name);
  } else {
    char temp[BUFSIZ];
    (void)sprintf (temp, "%sindex", name);
    define_user_command (temp, gen_index, 0);
    defindex (name, code);
  }
  free (name);
}

/* Append LIST2 to LIST1.  Return the head of the list. */
INDEX_ELT *
index_append (head, tail)
     INDEX_ELT *head, *tail;
{
  register INDEX_ELT *t_head = head;

  if (!t_head)
    return (tail);

  while (t_head->next)
    t_head = t_head->next;
  t_head->next = tail;
  return (head);
}

/* Expects 2 args, on the same line.  Both are index abbreviations.
   Make the first one be a synonym for the second one, i.e. make the
   first one have the same index as the second one. */
int
cm_synindex ()
{
  int redirector, redirectee;
  char *temp;

  skip_whitespace ();
  get_until_in_line (" ", &temp);
  redirectee = find_index_offset (temp);
  skip_whitespace ();
  free_and_clear (&temp);
  get_until_in_line (" ", &temp);
  redirector = find_index_offset (temp);
  free (temp);
  if (redirector < 0 || redirectee < 0) {
    line_error();
    (void)fprintf(stderr, "Unknown index reference.\n");
  } else {
      /* I think that we should let the user make indices synonymous to
         each other without any lossage of info.  This means that one can
         say @synindex cp dt anywhere in the file, and things that used to
         be in cp will go into dt. */
      INDEX_ELT *i1 = the_indices[redirectee], *i2 = the_indices[redirector];

      if (i1 || i2)
	{
	  if (i1)
	    the_indices[redirectee] = index_append (i1, i2);
	  else
	    the_indices[redirectee] = index_append (i2, i1);
	}

      name_index_alist[redirectee]->index =
	name_index_alist[redirector]->index;
    }
  return DONTCARE;
}

int
cm_pindex ()			/* Pinhead index. */
{
  index_add_arg ("pg");
  return DONTCARE;
}

int
cm_vindex ()			/* Variable index. */
{
  index_add_arg ("vr");
  return DONTCARE;
}

int
cm_kindex ()			/* Key index. */
{
  index_add_arg ("ky");
  return DONTCARE;
}

int
cm_cindex ()			/* Concept index. */
{
  index_add_arg ("cp");
  return DONTCARE;
}

int
cm_findex ()			/* Function index. */
{
  index_add_arg ("fn");
  return DONTCARE;
}

int
cm_tindex ()			/* Data Type index. */
{
  index_add_arg ("tp");
  return DONTCARE;
}

/* Sorting the index. */
int
index_element_compare (element1, element2)
     INDEX_ELT **element1, **element2;
{
  /* This needs to ignore leading non-text characters. */
  return (strcmp ((*element1)->entry, (*element2)->entry));
}

#if defined(__cplusplus) || defined(__STDC__)
typedef int (*comparefct)(const void *, const void *);
#endif

/* Sort the index passed in INDEX, returning an array of
   pointers to elements.  The array is terminated with a NULL
   pointer.  We call qsort because it's supposed to be fast.
   I think this looks bad. */
INDEX_ELT **
sort_index (index)
     INDEX_ELT *index;
{
  INDEX_ELT *temp = index;
  INDEX_ELT **array;
  int count = 0;

  while (temp != (INDEX_ELT *) 0)
    {
      count++;
      temp = temp->next;
    }

  /* We have the length.  Make an array. */

  array = (INDEX_ELT **) xmalloc ((count + 1) * sizeof (INDEX_ELT *));
  count = 0;
  temp = index;

  while (temp != (INDEX_ELT *) 0)
    {
      array[count++] = temp;
      temp = temp->next;
    }
  array[count] = (INDEX_ELT *) 0;	/* terminate the array. */

  /* Sort the array. */
#if defined(__cplusplus) || defined(__STDC__)
  qsort ((char *)array, count, sizeof (INDEX_ELT *), (comparefct)index_element_compare);
#else
  qsort ((char *)array, count, sizeof (INDEX_ELT *), index_element_compare);
#endif
  return (array);
}

/* Non-zero means that we are in the middle of printing an index. */
int printing_index = 0;

/* Takes one arg, a short name of an index to print.
   Outputs a menu of the sorted elements of the index. */
int
cm_printindex ()
{
  int item;
  INDEX_ELT *index;
  INDEX_ELT **array;
  char *index_name;
  int old_inhibitions = inhibit_paragraph_indentation;
  int previous_filling_enabled_value = filling_enabled;

  close_paragraph ();
  get_rest_of_line (&index_name);

  index = index_list (index_name);
  if (! index ) {
    line_error();
    (void)fprintf(stderr, "Unknown index name `%s'.\n", index_name);
    free (index_name);
    return DONTCARE;
  } else free (index_name);

  array = sort_index (index);

  filling_enabled = 0;
  inhibit_paragraph_indentation = 1;
  close_paragraph ();
  add_word ("* Menu:\n\n");

  printing_index = 1;
  for (item = 0; (index = array[item]); item++)
    {
      int real_line_number = line_number;

      /* Let errors generated while making the index entry point back
	 at the line which contains the entry. */
      line_number = index->defining_line;

      /* If this particular entry should be printed as a "code" index,
	 then wrap the entry with "@code{...}". */
      if (index->code) {
	(void)sprintf(exec_string, "* @code{%s}: @bye\n", index->entry);
        execute_string();
      } else {
	(void)sprintf(exec_string, "* %s: @bye\n", index->entry);
        execute_string();
      }

      /* Pad the front of the destination nodename so that
	 the output looks nice. */
      if (fill_column > 40 && output_column < 40)
	indent (40 - output_column);

      (void)sprintf(exec_string, "%s.\n@bye\n", index->node);
      execute_string();

      line_number = real_line_number;
      flush_output ();
    }

  printing_index = 0;
  free((char *)array);
  close_single_paragraph ();
  filling_enabled = previous_filling_enabled_value;
  inhibit_paragraph_indentation = old_inhibitions;
  return DONTCARE;
}


/* **************************************************************** */
/*								    */
/*		    Making User Defined Commands		    */
/*								    */
/* **************************************************************** */

void
define_user_command (name, proc, needs_braces_p)
     char *name;
     FUNCTION *proc;
     int needs_braces_p;
{
  int slot = user_command_array_len;
  user_command_array_len++;

  if (!user_command_array)
    user_command_array = (COMMAND **) xmalloc (1 * sizeof (COMMAND *));

  user_command_array = (COMMAND **) xrealloc((char *)user_command_array,
					      (1 + user_command_array_len) *
					      sizeof (COMMAND *));

  user_command_array[slot] = (COMMAND *) xmalloc (sizeof (COMMAND));
  user_command_array[slot]->name = savestring (name);
  user_command_array[slot]->proc = proc;
  user_command_array[slot]->argument_in_braces = needs_braces_p;
}

/* Make ALIAS run the named FUNCTION.  Copies properties from FUNCTION. */
void
define_alias (alias, function)
     char *alias, *function;
{
}

/* Set the paragraph indentation variable to the value specified in STRING.
   Values can be:
   `asis': Don't change existing indentation.
   `none': Remove existing indentation.
      NUM: Indent NUM spaces at the starts of paragraphs.
           Note that if NUM is zero, we assume `none'.

   Returns 0 if successful, or non-zero if STRING isn't one of the above. */
int
set_paragraph_indent (string)
     char *string;
{
  if (strcmp (string, "asis") == 0)
    paragraph_start_indent = 0;
  else if (strcmp (string, "none") == 0)
    paragraph_start_indent = -1;
  else
    {
      if (sscanf (string, "%d", &paragraph_start_indent) != 1)
	return (-1);
      else
	{
	  if (paragraph_start_indent == 0)
	    paragraph_start_indent = -1;
	}
    }
  return (0);
}

int
cm_paragraphindent ()
{
  char *arg;

  get_rest_of_line (&arg);
  if (set_paragraph_indent (arg) != 0) {
    line_error();
    (void)fprintf(stderr, "Bad argument to @paragraphindent.\n");
  }

  free (arg);
  return DONTCARE;
}

/* Some support for footnotes. */

/* Footnotes are a new construct in Info.  We don't know the best method
   of implementing them for sure, so we present two possiblities.

   SeparateNode:
	Make them look like followed references, with the reference
	destinations in a makeinfo manufactured node or,

   EndNode:
	Make them appear at the bottom of the node that they originally
	appeared in. */
#define SeparateNode 0
#define EndNode 1

int footnote_style = EndNode;
int first_footnote_this_node = 1;
int footnote_count = 0;

/* Set the footnote style based on he style identifier in STRING. */
int
set_footnote_style (string)
     char *string;
{
  if ((stricmp (string, "separate") == 0) ||
      (stricmp (string, "MN") == 0))
    footnote_style = SeparateNode;
  else if ((stricmp (string, "end") == 0) ||
	   (stricmp (string, "EN") == 0))
    footnote_style = EndNode;
  else
    return (-1);

 return (0);
}

int
cm_footnotestyle ()
{
  char *arg;

  get_rest_of_line (&arg);

  if (set_footnote_style (arg) != 0) {
    line_error();
    (void)fprintf(stderr, "Bad argument to @footnotestyle.\n");
  }

  free (arg);
  return DONTCARE;
}

typedef struct fn
{
  struct fn *next;
  char *marker;
  char *note;
}  FN;

FN *pending_notes = (FN *) 0;

/* A method for remembering footnotes.  Note that this list gets output
   at the end of the current node. */
void
remember_note (marker, note)
     char *marker, *note;
{
  FN *temp = (FN *) xmalloc (sizeof (FN));

  temp->marker = savestring (marker);
  temp->note = savestring (note);
  temp->next = pending_notes;
  pending_notes = temp;
  footnote_count++;
}

/* How to get rid of existing footnotes. */
void
free_pending_notes ()
{
  FN *temp;

  while ((temp = pending_notes) != (FN *) 0)
    {
      free (temp->marker);
      free (temp->note);
      pending_notes = pending_notes->next;
      free((char *)temp);
    }
  first_footnote_this_node = 1;
  footnote_count = 0;
}

/* What to do when you see a @footnote construct. */

 /* Handle a "footnote".
    footnote *{this is a footnote}
    where "*" is the marker character for this note. */
int
cm_footnote ()
{
  char *marker;
  char *note;

  (void)get_until ("{", &marker);
  canon_white (marker);

  /* Read the argument in braces. */
  if (curchar () != '{') {
    line_error();
    (void)fprintf(stderr,
"`@%s' expected more than just `%s'.  It needs something in `{...}'.\n",
      command, marker);
    free (marker);
    return DONTCARE;
  } else {
    int braces = 1;
    int temp;
    int len;

    temp = ++input_text_offset;
    while (braces) {
      if (temp == size_of_input_text) {
	line_error();
        (void)fprintf(stderr, "No closing brace for footnote `%s'.\n", marker);
	return DONTCARE;
      }

      if (input_text[temp] == '{') braces++;
      else if (input_text[temp] == '}') braces--;
      else if (input_text[temp] == '\n') line_number ++;

      temp++;
    }

    len = (temp - input_text_offset) - 1;
    note = (char *)xmalloc (len + 1);
    (void)strncpy (note, &input_text[input_text_offset], len);
    note[len] = '\0';
    input_text_offset = temp;
  }

  if (!current_node || !*current_node) {
    line_error();
    (void)fprintf(stderr, "Footnote defined without parent node.\n");
    free (marker);
    free (note);
    return DONTCARE;
  }

  if (!*marker)
    {
      free (marker);

      if (number_footnotes)
	{
	  marker = (char *)xmalloc (10);
	  (void)sprintf (marker, "%d", current_footnote_number);
	  current_footnote_number++;
	}
      else
	marker = savestring ("*");
    }

  remember_note (marker, note);

  /* Your method should at least insert MARKER. */
  switch (footnote_style)
    {
    case SeparateNode:
      add_word_args ("(%s)", marker, "", 0, 0);
      if (first_footnote_this_node)
	{
	  char *temp_string;

	  temp_string = (char *)
	    xmalloc ((strlen (current_node)) + (strlen ("-Footnotes")) + 1);

	  add_word_args (" (*note %s-Footnotes::)", current_node, "", 0, 0);
	  (void)strcpy (temp_string, current_node);
	  (void)strcat (temp_string, "-Footnotes");
	  remember_node_reference (temp_string, line_number, followed_reference);
	  free (temp_string);
	  first_footnote_this_node = 0;
	}
      break;

    case EndNode:
      add_word_args ("(%s)", marker, "", 0, 0);
      break;

    default:
      break;
    }
  free (marker);
  free (note);
  return DONTCARE;
}

/* Non-zero means that we are currently in the process of outputting
   footnotes. */
int already_outputting_pending_notes = 0;

/* Output the footnotes.  We are at the end of the current node. */
void
output_pending_notes ()
{
  FN *footnote = pending_notes;

  if (!pending_notes)
    return;

  switch (footnote_style)
    {

    case SeparateNode:
      {
	char *old_current_node = current_node;
	char *old_command = savestring (command);

	already_outputting_pending_notes++;
	(void)sprintf(exec_string, "@node %s-Footnotes,,,%s\n@bye\n", current_node, current_node);
        execute_string();
	already_outputting_pending_notes--;
	current_node = old_current_node;
	free (command);
	command = old_command;
      }
      break;

    case EndNode:
      close_paragraph ();
      in_fixed_width_font++;
      (void)sprintf(exec_string, "---------- Footnotes ----------\n\n@bye\n");
      execute_string();
      in_fixed_width_font--;
      break;
    }

  /* Handle the footnotes in reverse order. */
  {
    FN **array = (FN **) xmalloc ((footnote_count + 1) * sizeof (FN *));

    array[footnote_count] = (FN *) 0;

    while (--footnote_count > -1)
      {
	array[footnote_count] = footnote;
	footnote = footnote->next;
      }

    filling_enabled = 1;
    indented_fill = 1;

    while ((footnote = array[++footnote_count]))
      {

	switch (footnote_style)
	  {
	  case SeparateNode:
	  case EndNode:
	    (void)sprintf(exec_string, "(%s)  %s@bye\n", footnote->marker, footnote->note);
            execute_string();
	    close_paragraph ();
	    break;
	  }
      }
    close_paragraph ();
    free((char *)array);
  }
}


/* **************************************************************** */
/*                                                                  */
/*              User definable Macros (text substitution)	    */
/*                                                                  */
/* **************************************************************** */

#if defined (HAVE_MACROS)

/* Array of macros and definitions. */
MACRO_DEF **macro_list = (MACRO_DEF **)0;

int macro_list_len = 0;		/* Number of elements. */
int macro_list_size = 0;	/* Number of slots in total. */

/* Return the macro definition of NAME or NULL if NAME is not defined. */
MACRO_DEF *
find_macro (name)
     char *name;
{
  register int i;
  register MACRO_DEF *def;

  def = (MACRO_DEF *)0;
  for (i = 0; macro_list && (def = macro_list[i]); i++)
    if (strcmp (def->name, name) == 0)
      break;

  return (def);
}

/* Add the macro NAME with DEFINITION to macro_list.  FILENAME is
   the name of the file where this definition can be found, and
   LINENO is the line number within that file.  If a macro already
   exists with NAME, then a warning is produced, and that previous
   definition is overwritten. */
void
add_macro (name, definition, filename, lineno)
     char *name, *definition;
     char *filename;
     int lineno;
{
  register MACRO_DEF *def;

  def = find_macro (name);

  if (!def)
    {
      if (macro_list_len + 2 >= macro_list_size)
	macro_list = (MACRO_DEF **)xrealloc((char *)macro_list,
                       ((macro_list_size += 10) * sizeof (MACRO_DEF *)));

      macro_list[macro_list_len] = (MACRO_DEF *)xmalloc (sizeof (MACRO_DEF));
      macro_list[macro_list_len + 1] = (MACRO_DEF *)0;

      def = macro_list[macro_list_len];
      macro_list_len += 1;
      def->name = savestring (name);
    }
  else
    {
      char *temp_filename = input_filename;
      int temp_line = line_number;

      if (print_warnings) {
        warning();
        (void)fprintf(stderr, "The macro `%s' is previously defined.\n", name);
      }

      input_filename = def->filename;
      line_number = def->lineno;

      if (print_warnings) {
        warning();
        (void)fprintf(stderr, "Here is the previous definition of `%s'.\n",
          name);
      }

      input_filename = temp_filename;
      line_number = temp_line;

      free (def->filename);
      free (def->definition);
    }

  def->filename = savestring (filename);
  def->lineno = lineno;
  def->definition = savestring (definition);
}


/* Delete the macro with name NAME.  The macro is deleted from the list,
   but it is also returned.  If there was no macro defined, NULL is
   returned. */
MACRO_DEF *
delete_macro (name)
     char *name;
{
  register int i;
  register MACRO_DEF *def;

  def = (MACRO_DEF *)0;
  for (i = 0; macro_list && (def = macro_list[i]); i++)
    if (strcmp (def->name, name) == 0)
      {
	memcpy ((char *)(macro_list + i), (char *)(macro_list + i + 1),
	       ((macro_list_len + 1) - i) * sizeof (MACRO_DEF *));
	break;
      }
  return (def);
}

/* Execute the macro passed in DEF, a pointer to a MACRO_DEF. */
void
execute_macro (def)
     MACRO_DEF *def;
{

  if (def != (MACRO_DEF *)0)
    {
      char *line, *string;

      (void)get_until ("\n", &line);

      if (curchar () == '\n')	/* as opposed to the end of the file... */
	{
	  line_number++;
	  input_text_offset++;
	}
      string = (char *)xmalloc (1 + strlen (def->definition) + strlen (line));
      (void)strcpy (string, def->definition);
      (void)strcat (string, line);
      free (line);

      (void)sprintf(exec_string, "%s\n@bye\n", string);
      execute_string();
      free (string);
    }
}

int
cm_macro ()
{
  register int i;
  char *line, *name;

  get_rest_of_line (&line);
  canon_white (line);

  for (i = 0; line[i] && !whitespace (line[i]); i++);
  name = (char *)xmalloc (i);
  (void)strncpy (name, line, i);
  name[i] = '\0';

  while (whitespace (line[i]))
    i++;

  add_macro (name, line + i, input_filename, line_number);
  free (line);
  free (name);
  return DONTCARE;
}

int
cm_unmacro ()
{
  register int i;
  char *line, *name;
  MACRO_DEF *def;

  get_rest_of_line (&line);
  canon_white (line);

  for (i = 0; line[i] && !whitespace (line[i]); i++);
  name = (char *)xmalloc (i);
  (void)strncpy (name, line, i);
  name[i] = '\0';

  def = delete_macro (name);

  if (def)
    {
      free (def->filename);
      free (def->name);
      free (def->definition);
      free((char *)def);
    }

  free (line);
  free (name);
  return DONTCARE;
}
#endif /* HAVE_MACROS */

/* **************************************************************** */
/*								    */
/*		    Example-oriented commands			    */
/*								    */
/* **************************************************************** */

#define EOEG	"--eg--"
#define EOEGLEN	6

int
cm_eg()
{
  static long int egpos;
  static char *egfilename, *oldegfilename = (char *)0;
  FILE *egfile = (FILE *)0;
  char buf[BUFSIZ];
  char *cp;

  close_paragraph ();
  get_rest_of_line (&egfilename);

  /* set up file parameters */
  if (*egfilename != '\0') {
    /* use new one from beginning */
    if (oldegfilename != (char *)0)
      free(oldegfilename);
    oldegfilename = savestring(egfilename);
    egpos = 0L;
  }

  /* open the file */
  if ((egfile = fopen( oldegfilename, "r" )) == (FILE *)0) {
    line_error();
    (void)fprintf(stderr, "@eg: can't open %s.\n", oldegfilename);
    return DONTCARE;
  }

  /* get to the correct place */
  (void)fseek( egfile, egpos, 0 );

  /* read the next eg section */
  while (fgets( buf, BUFSIZ, egfile ) != (char *)0) {
    /* look for the end of eg marker */
    for (cp = buf; (*cp != '\0') && (strncmp( cp, EOEG, EOEGLEN ) != 0);
	 cp++)
      ;
    if (*cp != '\0') break;
    /* otherwise copy the line out */
    add_word(buf);
  }

  /* save the finish position for a possible next time */
  egpos = ftell(egfile);

  /* close it off */
  (void)fclose(egfile);
  return DONTCARE;
}

int
cm_run()
{
  if (have_had_run) {
    line_error();
    (void)fprintf(stderr, "Can't have more than one @run in a node.\n");
  } else have_had_run = 1;
  begin_insertion(run);
  return DONTCARE;
}

int
cm_egfiles()
{
  extern int have_had_egfiles;

  if (have_had_run) {
    line_error();
    (void)fprintf(stderr, "Can't have @egfiles after @run, output garbled.\n");
  }
  if (have_had_egfiles) {
    line_error();
    (void)fprintf(stderr, "Can't have more than one @egfiles in a node.\n");
  } else have_had_egfiles = 1;
  begin_insertion(egfiles);
  return DONTCARE;
}

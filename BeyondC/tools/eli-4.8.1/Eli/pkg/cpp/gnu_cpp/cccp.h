/* $Id: cccp.h,v 1.1.1.1 2001/04/26 20:01:49 waite Exp $ */

/* Structure allocated for every #define.  For a simple replacement
   such as
   	#define foo bar ,
   nargs = -1, the `pattern' list is null, and the expansion is just
   the replacement text.  Nargs = 0 means a functionlike macro with no args,
   e.g.,
       #define getchar() getc (stdin) .
   When there are args, the expansion is the replacement text with the
   args squashed out, and the reflist is a list describing how to
   build the output from the input: e.g., "3 chars, then the 1st arg,
   then 9 chars, then the 3rd arg, then 0 chars, then the 2nd arg".
   The chars here come from the expansion.  Whatever is left of the
   expansion after the last arg-occurrence is copied after that arg.
   Note that the reflist can be arbitrarily long---
   its length depends on the number of times the arguments appear in
   the replacement text, not how many args there are.  Example:
   #define f(x) x+x+x+x+x+x+x would have replacement text "++++++" and
   pattern list
     { (0, 1), (1, 1), (1, 1), ..., (1, 1), NULL }
   where (x, y) means (nchars, argno). */

typedef char U_CHAR;

struct reflist {
  struct reflist *next;
  char stringify;		/* nonzero if this arg was preceded by a
				 # operator. */
  char raw_before;		/* Nonzero if a ## operator before arg. */
  char raw_after;		/* Nonzero if a ## operator after arg. */
  int nchars;			/* Number of literal chars to copy before
				 this arg occurrence.  */
  int argno;			/* Number of arg to substitute (origin-0) */
};

typedef struct definition {
  int nargs;
  int length;			/* length of expansion string */
  U_CHAR *expansion;
  struct reflist *pattern;
  /* Names of macro args, concatenated in reverse order
     with comma-space between them.
     The only use of this is that we warn on redefinition
     if this differs between the old and new definitions.  */
  U_CHAR *argnames;
} DEFINITION;

/* different kinds of things that can appear in the value field
   of a hash node.  Actually, this may be useless now. */
union hashval {
  int ival;
  char *cpval;
  DEFINITION *defn;
};


/* The structure of a node in the hash table.  The hash table
   has entries for all tokens defined by #define commands (type T_MACRO),
   plus some special tokens like __LINE__ (these each have their own
   type, and the appropriate code is run when that type of node is seen.
   It does not contain control words like "#define", which are recognized
   by a separate piece of code. */

/* different flavors of hash nodes --- also used in keyword table */
enum node_type {
 T_DEFINE = 1,	/* the `#define' keyword */
 T_INCLUDE,	/* the `#include' keyword */
 T_IFDEF,	/* the `#ifdef' keyword */
 T_IFNDEF,	/* the `#ifndef' keyword */
 T_IF,		/* the `#if' keyword */
 T_ELSE,	/* `#else' */
 T_PRAGMA,	/* `#pragma' */
 T_ELIF,	/* `#else' */
 T_UNDEF,	/* `#undef' */
 T_LINE,	/* `#line' */
 T_ERROR,	/* `#error' */
 T_ENDIF,	/* `#endif' */
 T_SCCS,	/* `#sccs', used on system V.  */
 T_IDENT,	/* `#ident', used on system V.  */
 T_SPECLINE,	/* special symbol `__LINE__' */
 T_DATE,	/* `__DATE__' */
 T_FILE,	/* `__FILE__' */
 T_BASE_FILE,	/* `__BASE_FILE__' */
 T_INCLUDE_LEVEL, /* `__INCLUDE_LEVEL__' */
 T_VERSION,	/* `__VERSION__' */
 T_TIME,	/* `__TIME__' */
 T_CONST,	/* Constant value, used by `__STDC__' */
 T_MACRO,	/* macro defined by `#define' */
 T_DISABLED,	/* macro temporarily turned off for rescan */
 T_SPEC_DEFINED, /* special `defined' macro for use in #if statements */
 T_UNUSED	/* Used for something not defined.  */
 };

typedef struct hashnode {
  struct hashnode *next;	/* double links for easy deletion */
  struct hashnode *prev;
  struct hashnode **bucket_hdr;	/* also, a back pointer to this node's hash
				   chain is kept, in case the node is the head
				   of the chain and gets deleted. */
  enum node_type type;		/* type of special token */
  int length;			/* length of token, for quick comparison */
  U_CHAR *name;			/* the actual name */
  union hashval value;		/* pointer to expansion, or whatever */
} HASHNODE;

#if PROTO_OK
extern HASHNODE *lookup(U_CHAR *, int, int);
#else
extern HASHNODE *lookup();
#endif

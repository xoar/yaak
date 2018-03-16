static char rcsid[] = "$Id: info.c,v 1.37 1998/02/11 16:43:10 waite Exp $";

/* info.c -- a stand-alone Info program which does what Info in GNU Emacs does.

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

#include "info.h"
#include "node.h"
#include "system.h"

/* If non-NULL, this is a colon separated list of directories to search
   for a specific info file.  The user places this variable into his or
   her environment. */
char *info_directory_paths = (char *) NULL;

char libname[FILENAME_LEN];	/* Library to get files for run and edit. */
char dumpfile[FILENAME_LEN];	/* If filled, the name of a file to write to.*/

/* **************************************************************** */
/*								    */
/*			Getting Started.			    */
/*								    */
/* **************************************************************** */

/* Begin the Info session. */

/* Global is on until we are out of trouble. */
boolean totally_inhibit_errors = true;

#define cons_string(x) strcpy((char *)xmalloc((size_t)(1+strlen(x))),(x))

void
#if defined(__cplusplus) || defined(__STDC__)
eat_argument(int ndx, int limit, char **array, char *string)
#else
eat_argument(ndx, limit, array, string)
int ndx, limit; char **array, *string;
#endif
{
  /* Eat argument from ARRAY[INDEX] into STRING.  If INDEX
     equals LIMIT barf. */

  if (ndx == limit)
    {
      (void)fprintf (stdout, "info: Missing argument.\n");
      exit (1);
    }

  (void)strncpy (string, array[ndx], FILENAME_LEN);
}

void
explain()
{
  /* tell them how to use it... */

  (void)fprintf (stderr, "usage: info [options...] [menu-item-name ...]\n" );
  (void)fprintf (stderr, "   options: -d info-dir-path, -f info-file, -l library-directory-name, \n" );
  (void)fprintf (stderr, "            -n nodename,      -o output-file\n" );
  exit (1);
}

void
#if defined(__cplusplus) || defined(__STDC__)
info(int argc, char **argv)
#else
info(argc, argv)
int argc; char **argv;
#endif
{
  int arg_index = 1;
  char filename[FILENAME_LEN];
  char nodename[NODENAME_LEN];

  char *env_info_dirs = getenv ("INFO_DIRECTORY_PATHS");

  nodename[0] = filename[0] = '\0';

  if (env_info_dirs)
    {
      if (*env_info_dirs)
	info_directory_paths = cons_string (env_info_dirs);
    }

  if (!info_directory_paths)
    info_directory_paths = cons_string (
       "/usr/gnu/info:/usr/gnu/lib/emacs/info:/usr/local/lib/emacs/info:.");

  /* Parse argument flags from the input line. */
  while (arg_index != argc && *(argv[arg_index]) == '-')
    {

      /* There are flag arguments, so parse them */
      char arg_character;
      int i = 1;
      int next_arg = 0;

      while ((!next_arg) && (arg_character = (argv[arg_index])[i]))
	{
	  i++;

	  switch (to_lower (arg_character))
	    {

	    case 'd':
	      /* Eat the next argument into INFO_DIRECTORY_PATH. */
	      free (info_directory_paths);
	      if (++arg_index == argc)
		{
		  (void)fprintf (stdout, "info: Missing argument.\n");
		  exit (1);
		}
	      info_directory_paths = cons_string(argv[arg_index]);
	      next_arg++;
	      break;

	    case 'n':
	      /* Eat the next argument into NODENAME. */
	      eat_argument (++arg_index, argc, argv, nodename);
	      next_arg++;
	      break;

	    case 'f':
	      /* Eat the next argument into FILENAME. */
	      eat_argument (++arg_index, argc, argv, filename);
	      next_arg++;
	      break;

	    case 'o':
	      /* Eat the next argument into DUMPNAME. */
	      eat_argument (++arg_index, argc, argv, dumpfile);
	      next_arg++;
	      break;

	    case 'l':
	      /* Eat the next argument into LIBNAME */
	      eat_argument (++arg_index, argc, argv, libname );
	      next_arg++;
	      break;

	    default:
	      explain ();	/* you lose if you type a bad flag */
	    }
	}
      arg_index++;
    }

  /* Okay, flags are parsed.  Get possible Info menuname. */

  /* Start with DIR or whatever was specified. */
  if (!get_node (filename, nodename, false))
    if (!get_node ((char *)NULL, (char *)NULL, true))
      {
	(void)fprintf (stderr, "%s: Cannot find \"%s\", or \"%s\".\n", argv[0],
		 filename, info_directory_paths);
	exit (1);
      }
  totally_inhibit_errors = false;
}

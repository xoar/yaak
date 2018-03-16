static char rcsid[] = "$Id: file.c,v 1.12 2005/07/29 21:47:27 profw Exp $";

/* filenames.c

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

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "../../../config.h"
#include "eliproto.h"
#if !(ERR_PROTO)
#  if USE_ERRLIST
     extern int sys_nerr;
     extern char *sys_errlist[];
#  else
     extern char *strerror ELI_ARG((int));
#  endif
#endif

#include "info.h"
#include "file.h"
#include "option.h"
#include "system.h"

/* Filename manipulators, and the like. */
static char local_temp_filename[FILENAME_LEN];

/* Given a string containing units of information separated by colons,
   return the next one pointed to by INDEX, or NULL if there are no more.
   Advance INDEX to the character after the colon. */
static char *
#if defined(__cplusplus) || defined(__STDC__)
extract_colon_unit(char *string, int *ndx)
#else
extract_colon_unit(string, ndx)
char *string; int *ndx;
#endif
{
  register int i, start;

  i = start = *ndx;
#if defined(__cplusplus) || defined(__STDC__)
  if (((size_t)i >= strlen (string)) || !string)
#else
  if ((i >= strlen (string)) || !string)
#endif
    return ((char *) NULL);

  while (string[i] && string[i] != ':')
    i++;
  if (i == start)
    {
      return ((char *) NULL);
    }
  else
    {
      char *value = (char *)xmalloc((size_t)(1 + (i - start)));
      (void)strncpy (value, &string[start], (i - start));
      value[i - start] = '\0';
      if (string[i])
	++i;
      *ndx = i;
      return (value);
    }
}

/***/
char *
#if defined(__cplusplus) || defined(__STDC__)
pathname(char *partial)
#else
pathname(partial)
char *partial;
#endif
/* Obtain a full path name for a file
 *    On entry-
 *       partial=tail of the desired path name
 *    If the file is in a directory named by INFO_PATHS then on exit-
 *       pathname=full path name
 *    Else on exit-
 *       pathname=partial
 ***/
{
  int initial_character;

  extern char *info_directory_paths;

  if (partial && (initial_character = *partial))
    {

      if (initial_character == '/')
	return (partial);
      if (initial_character == '~')
	{
	  if (partial[1] == '/')
	    {
	      /* Return the concatenation of HOME and the rest of the string. */
	      (void)strcpy (local_temp_filename, getenv ("HOME"));
	      (void)strcat (local_temp_filename, &partial[2]);
	      return (local_temp_filename);
	    }
	  else
	    {
	      struct passwd *user_entry;
	      int i, c;
	      char username[257];

	      for (i = 1; (c = partial[i]); i++)
		{
		  if (c == '/')
		    break;
		  else
		    username[i - 1] = c;
		}
	      username[i - 1] = '\0';

	      if (!(user_entry = getpwnam (username))) {
		  display_error("Not a registered user!");
		  return (partial);
		}
	      (void)strcpy (local_temp_filename, user_entry->pw_dir);
	      (void)strcat (local_temp_filename, &partial[i]);
	      return (local_temp_filename);
	    }
	}

      if (initial_character == '.') {
	  if (!getcwd (local_temp_filename, FILENAME_LEN)) return (partial);
	  (void)strcat (local_temp_filename, &partial[1]);
	  return (local_temp_filename);
	}

      /* Scan the list of directories in INFO_DIRECTORY_PATHS. */
      {
	struct stat finfo;
	char *temp_dirname;
	int dirname_index = 0;

	while ((temp_dirname = extract_colon_unit(info_directory_paths,
						  &dirname_index)))
	  {
	    (void)strcpy (local_temp_filename, temp_dirname);
	    if (temp_dirname[(strlen (temp_dirname)) - 1] != '/')
	      (void)strcat (local_temp_filename, "/");
	    (void)strcat (local_temp_filename, partial);
	    free (temp_dirname);
	    if (stat (local_temp_filename, &finfo) == 0)
	      return (local_temp_filename);
	  }
      }
    }
  return (partial);
}

/***/
char *
#if defined(__cplusplus) || defined(__STDC__)
make_temp_filename(char *starter)
#else
make_temp_filename(starter)
char *starter;
#endif
/* Make a temporary file name
 *    On entry-
 *       starter=initial characters for the file name
 ***/
{
  char *temp = (char *)xmalloc(FILENAME_LEN);
  (void)sprintf (temp, "%s-%d", starter, getpid ());
  return (temp);
}

/***/
void
#if defined(__cplusplus) || defined(__STDC__)
file_error(char *file)
#else
file_error(file)
char *file;
#endif
/* Display system error message
 *    On entry-
 *       filename is the file being processed when the error occurred
 ***/
{ char errbuf[BUFSIZ];

#if USE_ERRLIST
  if (errno < sys_nerr) {
    (void)sprintf(errbuf, "%s: %s\n", file, sys_errlist[errno]);
  }
  else {
    (void)sprintf(errbuf, "%s: Unknown error %d", file, errno);
  }
#else
  (void)sprintf(errbuf, "%s: %s\n", file, strerror(errno));
#endif
  display_error(errbuf);
}

/***/
boolean
#if defined(__cplusplus) || defined(__STDC__)
deletefile(char *filename)
#else
deletefile(filename)
char *filename;
#endif
/* Delete a file
 *    On entry-
 *       filename is to be deleted
 *    If the deletion is carried out correctly then on exit-
 *       deletefile=true
 *    Else on exit-
 *       deletefile=false
 *       The error has been reported
 ***/
{
  if (unlink(filename) == 0) return(true);
  file_error(filename);
  return(false);
}

#ifndef LPR
#define LPR		"lpr -P"
#endif

/***/
boolean
#if defined(__cplusplus) || defined(__STDC__)
printfile(char *filename)
#else
printfile(filename)
char *filename;
#endif
/* Print documentation
 *    On entry-
 *       filename contains the documentation to be printed
 *    If the printing was carried out without errors then on exit-
 *       printfile=true
 *    Else on exit-
 *       printfile=false
 *       The error has been reported
 ***/
{
  char cmdbuf[STRING_SIZE];
  int error;
  char *printer;

  printer = options[PRINTER].value;
  (void)sprintf (cmdbuf, "%s %s %s", LPR, printer, filename);
  error = system (cmdbuf);
  if (error) {
    char errbuf[BUFSIZ];
    (void)sprintf(errbuf, "Error %d invoking `%s'", error, cmdbuf);
    display_error(errbuf);
    return(false);
  }
  return(true);
}

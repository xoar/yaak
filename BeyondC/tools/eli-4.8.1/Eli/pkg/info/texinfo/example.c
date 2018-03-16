static char rcsid[] = "$Id: example.c,v 1.18 1998/02/11 16:43:03 waite Exp $";

/* example.c

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

/* **************************************************************** */
/*								    */
/*		   Running commands and editing files.		    */
/*								    */
/* **************************************************************** */
#include <unistd.h>
#include "info.h"
#include "file.h"
#include "node.h"
#include "option.h"
#include "list.h"

extern char libname[];

#ifndef CP
#define CP		"cp"
#endif
#ifndef MV
#define MV		"mv"
#endif
#ifndef SCRIPT
#define SCRIPT		"script"
#endif
#ifndef SED
#define SED		"sed"
#endif
#ifndef SHELL
#define SHELL		"/bin/sh"
#endif
#ifndef TOUCH
#define TOUCH		"touch"
#endif

static char lib[STRING_SIZE];

boolean
get_eg_file_list()
{
  /* On exit, "completion_list" specifies a list of extant files
   *   completion_list->identifier is the local name
   *   completion_list->data is the full path name
   */

  char ch, *cp;
  char localname[FILENAME_LEN], realname[FILENAME_LEN];
  size_t cmdp;

  /* Collect the library name */
  for (cmdp = nodebot + 2, cp = lib; (ch = info_file[cmdp]) != '\n'; cmdp++)
    *cp++ = ch;
  if (cp != lib) *cp = '\0';

  free_completion_list();

  /* collect the information about extant files */
  for (cmdp++; info_file[cmdp] != info_separator_char; cmdp++) {
    for (cp = localname;
	 ((ch = info_file[cmdp]) != '\n') && (ch != TAB) && (ch != SPACE);
	 cmdp++)
      *cp++ = ch;
    *cp = '\0';
    for ( ; info_file[cmdp] != '\n'; cmdp++ )
      ;

    /* If filename starts with a '/', filename must exist. */
    /* If lib starts with a '/', lib/filename must exist. */
    /* Otherwise, libname/lib/filename must exist. */
    if (FILE_EXISTS(localname)) strcpy(realname, localname);
    else if ((lib[0] == '/') || (libname == NULL) || (libname[0] == '\0'))
      (void)sprintf( realname, "%s/%s", lib, localname );
    else (void)sprintf( realname, "%s/%s/%s", libname, lib, localname );
    /* make sure that the library version exists */
    if (FILE_EXISTS( realname )) add_completion(localname, realname);
  }
  return(completion_list != NULL);
}

boolean
#if defined(__cplusplus) || defined(__STDC__)
set_up_run(boolean *bg, char *cmdbuf, char **cmdfilename)
#else
set_up_run(bg, cmdbuf, cmdfilename)
boolean *bg; char *cmdbuf, **cmdfilename;
#endif
{
  size_t cmdp;
  char ch, *cp, *runner;
  FILE *cmdfile;

  /* Collect the library name */
  for (cmdp = nodebot + 2, cp = lib; (ch = info_file[cmdp]) != '\n'; cmdp++)
    *cp++ = ch;
  if (cp != lib) *cp = '\0';

  for (cmdp = nodebot+2; info_file[cmdp] != info_separator_char; cmdp++)
    ;
  for (cmdp++; info_file[cmdp] != info_separator_char; cmdp++)
    ;

  /* Check whether there are any commands to run */
  if (info_file[cmdp+2] != '#') {
    display_error("Command specification for the run is missing");
    return(false);
  }
  for (cp = &info_file[cmdp+4]; *cp != '\n'; cp++) ;
  if (cp[1] == info_separator_char) return(false);

  /* Create the command file */
  *cmdfilename = make_temp_filename( ".Cmd" );
  if ((cmdfile = fopen(*cmdfilename,"w")) == NULL) {
    char errbuf[BUFSIZ];
    (void)sprintf(errbuf, "Couldn't open %s", *cmdfilename);
    display_error(errbuf);
    return (false);
  }
  if (chmod(*cmdfilename, 0755 )) {
    char errbuf[BUFSIZ];
    (void)sprintf(errbuf, "Couldn't chmod %s", *cmdfilename);
    display_error(errbuf);
    return (false);
  }

  /* Obtain the commands supplied with the node */
  for (cmdp += 2; info_file[cmdp] != info_separator_char; cmdp++)
    putc(info_file[cmdp],cmdfile);
  (void)fclose(cmdfile);

  /* Set up the command */
  if (((runner = options[WINRUNNER].value) == NULL) || (*runner == '\0')) {
    *bg = false;
    (void)sprintf(cmdbuf,
      "clear;INFOLIB=%s INFODIR=%s SCRIPTOUTPUT=%s `pwd`/%s",
      libname, lib, SCRIPTOUTPUT, *cmdfilename);
  } else {
    *bg = true;
    (void)sprintf(cmdbuf,
      "INFOLIB=%s INFODIR=%s SCRIPTOUTPUT=%s %s `pwd`/%s",
      libname, lib, SCRIPTOUTPUT, runner, *cmdfilename);
  }

  return (true);
}

void
#if defined(__cplusplus) || defined(__STDC__)
set_up_edit(boolean *bg, char *cmdbuf, char *file)
#else
set_up_edit(bg, cmdbuf, file)
boolean *bg; char *cmdbuf, *file;
#endif
{
  char *editor;

  if (((editor = options[WINEDITOR].value) == NULL) || (*editor == '\0')) {
    *bg = false;
    editor = options[EDITOR].value;
  } else
    /* use WINEDITOR */
    *bg = true;

  (void)sprintf(cmdbuf, "%s %s", editor, file );
}

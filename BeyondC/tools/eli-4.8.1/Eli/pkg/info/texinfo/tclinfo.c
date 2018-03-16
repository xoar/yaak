static char rcsid[] = "$Id: tclinfo.c,v 1.12 2013/12/05 21:34:42 profw Exp $";

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#include "tcl.h"
#include "tk.h"
#include "info.h"
#include "driver.h"
#include "file.h"
#include "node.h"
#include "list.h"
#include "option.h"
#include "util.h"
#include "example.h"
#include "system.h"

static char manualname[FILENAME_LEN];

#define DEFAULT_WINRUNNER	"xterm -e"

static INIT_OPTION infotool_options[] = {
  { WINEDITOR, NULL },
  { WINRUNNER, DEFAULT_WINRUNNER },
  { -1, NULL }
};

Tcl_Interp *n_interp;
int maxcol = 80;

/***/
void
#if defined(__cplusplus) || defined(__STDC__)
display_error(char *buf)
#else
display_error(buf)
char *buf;
#endif
/* Inform the user of an error via the message area
 *    On entry-
 *       buf=message to be displayed
 ***/
{ Tcl_SetVar(n_interp, "errmsg", buf, TCL_GLOBAL_ONLY); }

void
display_node()
{ char save, buf[BUFSIZ];
  struct stat manualinfo;

  if (extract_field ("Next:", buf, datatop)) {
    Tcl_SetVar(n_interp, "NextNodeName", buf, TCL_GLOBAL_ONLY);
    Tcl_VarEval(n_interp, ".t.next configure -state normal", NULL);
  } else
    Tcl_VarEval(n_interp, ".t.next configure -state disabled", NULL);

  if (extract_field ("Prev:", buf, datatop)) {
    Tcl_SetVar(n_interp, "PrevNodeName", buf, TCL_GLOBAL_ONLY);
    Tcl_VarEval(n_interp, ".t.prev configure -state normal", NULL);
  } else
    Tcl_VarEval(n_interp, ".t.prev configure -state disabled", NULL);

  if (extract_field ("Up:", buf, datatop)) {
    Tcl_SetVar(n_interp, "UpNodeName", buf, TCL_GLOBAL_ONLY);
    Tcl_VarEval(n_interp, ".t.goup configure -state normal", NULL);
  } else
    Tcl_VarEval(n_interp, ".t.goup configure -state disabled", NULL);

  if (extract_field ("Edit", buf, datatop) && get_eg_file_list()) {
    COMP_ENTRY *temp;

    Tcl_VarEval(n_interp, "NewEgFiles", NULL);
    for (temp = completion_list;
         temp != (COMP_ENTRY *)NULL;
         temp = temp->next)
      Tcl_VarEval(n_interp,
        "EgFile {", temp->identifier, "} {", temp->data, "}",
        NULL);
    Tcl_VarEval(n_interp, ".t.edit configure -state normal", NULL);
  } else
    Tcl_VarEval(n_interp, ".t.edit configure -state disabled", NULL);

  if (extract_field ("Run", buf, datatop))
    Tcl_VarEval(n_interp, ".t.exec configure -state normal", NULL);
  else
    Tcl_VarEval(n_interp, ".t.exec configure -state disabled", NULL);

  (void) sprintf (manualname, "%s%s%s", current_info_dir,
      current_info_file, PRINTEXTENSION);
  if (stat (manualname, &manualinfo) == 0) {
    (void)sprintf(buf,
      "Do you really want to print a %ldk PostScript file?",
      (long)(manualinfo.st_size / 1024));
    Tcl_SetVar(n_interp, "ManualMessage", buf, TCL_GLOBAL_ONLY);
    Tcl_VarEval(n_interp, ".b.pman configure -state normal", NULL);
  } else
    Tcl_VarEval(n_interp, ".b.pman configure -state disabled", NULL);

  /* IMPORTANT: Because the body of the node may contain arbitrary
   * characters, it MUST be stored in a Tcl variable and then accessed
   * by referencing that variable in a Tcl procedure.  It CANNOT be
   * passed as an argument to a command evaluation because then its
   * characters will be interpreted by Tcl.
   */
  save = info_file[nodebot]; info_file[nodebot] = '\0';
  Tcl_SetVar(n_interp, "NodeBody", &info_file[nodetop], TCL_GLOBAL_ONLY);
  info_file[nodebot] = save;

  Tcl_VarEval(n_interp,
    "NodeDisplay {", current_info_file, "} {", current_info_node, "}", NULL);
}

#if defined(__cplusplus) || defined(__STDC__)
#define CMD(name) int \
  name(ClientData clientData, Tcl_Interp *interp, int argc, char *argv[])
#else
#define CMD(name) int \
  name(clientData, interp, argc, argv) \
  ClientData clientData; Tcl_Interp *interp; int argc; char *argv[];
#endif

CMD(GotoNode)
{ if (get_node((char *)NULL, argv[1], 0)) display_node();
  Tcl_SetResult(interp, "", TCL_STATIC); return TCL_OK;
}

CMD(BackButton)
{ if (last_node()) display_node();
  Tcl_SetResult(interp, "", TCL_STATIC); return TCL_OK;
}

CMD(EditButton)
{ boolean bg;
  char buf[BUFSIZ];

  set_up_edit(&bg, buf, argv[1]); background(buf, (char *)NULL);
  Tcl_SetResult(interp, "", TCL_STATIC); return TCL_OK;
}

CMD(ExecButton)
{ boolean bg;
  char buf[BUFSIZ], *file;

  if (set_up_run(&bg, buf, &file)) background(buf, file);
  Tcl_SetResult(interp, "", TCL_STATIC); return TCL_OK;
}

CMD(PrintNodeButton)
{ if (print_current_node()) Tcl_SetResult(interp, "1", TCL_STATIC);
  else Tcl_SetResult(interp, "0", TCL_STATIC);
  return TCL_OK;
}

CMD(PrintManualButton)
{ if (printfile(manualname)) Tcl_SetResult(interp, "1", TCL_STATIC);
  else Tcl_SetResult(interp, "0", TCL_STATIC);
  return TCL_OK;
}

CMD(NodeMenu)
/* Follow a possible menu item selected from the current node
 *    On entry-
 *       argv[1]=Line of text with no leading white space
 *    If a menu item is present, and the node is accessible, then on exit-
 *       NodeMenu=true
 *       The referenced node has been displayed
 *    Else if a menu item is present then on exit-
 *       NodeMenu=false
 *       An error has been reported to the user
 *    Else on exit-
 *       NodeMenu=false
 ***/
{ char buf[BUFSIZ], *p, *q;

  p = argv[1];
  p += strspn(p, " \t");
  if (*p++ != '*') { Tcl_SetResult(interp, "0", TCL_STATIC); return TCL_OK; }

  p += strspn(p, " \t");
  if ((q = strpbrk(p, ":")) == NULL) {
    Tcl_SetResult(interp, "0", TCL_STATIC); return TCL_OK;
  }

  (void)strncpy(buf, p, q-p);
  buf[q-p] = '\0';
  if (q[1] == ':') p = buf;
  else p = q + strspn(q, ": ");

  if (!get_node((char *)NULL, p, 0)) { 
    Tcl_SetResult(interp, "0", TCL_STATIC); return TCL_OK;
  }

  display_node();
  Tcl_SetResult(interp, "1", TCL_STATIC); return TCL_OK;
}

CMD(NodeNote)
/* Follow a possible cross-reference selected from the current node
 *    On entry-
 *       str=a text segment guaranteed to contain the entire reference
 *          (if one is present)
 *       str[picked]=character actually marked by the selection
 *    If a reference is present, and the node is accessible, then on exit-
 *       NodeNote=true
 *       The referenced node has been displayed
 *    Else if a reference is present then on exit-
 *       NodeNote=false
 *       An error has been reported to the user
 *    Else on exit-
 *       NodeNote=false
 ***/
{ char buf[BUFSIZ], *p, *q;

  p = argv[1] + strlen(argv[2]);
  while (*p != '*' && *p != '.' && p > argv[1]) p--;
  if (strnicmp(p, "*note", 5) != 0) { 
    Tcl_SetResult(interp, "0", TCL_STATIC); return TCL_OK;
  }

  p += 5;
  p += strspn(p, " \t\n");
  if ((q = strpbrk(p, ":")) == NULL) { 
    Tcl_SetResult(interp, "0", TCL_STATIC); return TCL_OK;
  }

  (void)strncpy(buf, p, q-p);
  buf[q-p] = '\0';
  if (q[1] == ':') p = buf;
  else p = q + strspn(q, ": \t\n");

  if (!get_node((char *)NULL, p, 0)) { 
    Tcl_SetResult(interp, "0", TCL_STATIC); return TCL_OK;
  }

  display_node();
  Tcl_SetResult(interp, "1", TCL_STATIC); return TCL_OK;
}

CMD(SearchNode)
/* Search for a string in the current node
 *    On entry-
 *       str=a string to be searched for
 *    If the string is present in the node starting at the position of the
 * 	 carat, then on exit-
 *          The line with the string is at the top of the page.
 *	    The carat points to the end of the string.
 ***/
{ size_t pos;
  int counter;
  int start = nodetop;
  long line = atol(argv[2]);
  long col  = atol(argv[3]);
  char buf[BUFSIZ];

  for (counter = line-1; counter; counter--) {
    while (info_file[start++] != '\n') ;
  }
  start += col;

  set_search_constraints (info_file + start, nodebot - start + 1);
  pos = 0;
  if (!search_forward(argv[1], &pos)) {
    char buf [BUFSIZ];

    sprintf (buf, "String '%s' not found.", argv[1]);
    display_error(buf);
    Tcl_SetResult(interp, "0", TCL_STATIC); return TCL_OK;
  }
  while (pos--) {
    if (info_file[start++] == '\n') { line++; col = 0; } else col++;
  }
  (void)sprintf(buf,
    ".tx.t tag add sel %ld.%ld %ld.%ld",
    line, col, line, col + strlen(argv[1]));
  Tcl_VarEval(interp, ".tx.t tag remove sel 1.0 end;", buf, NULL);
  Tcl_SetResult(interp, "1", TCL_STATIC); return TCL_OK;
}

CMD(ResetOptions)
{ int i;

  for (i = 0; options[i].name; i++) {
    strcpy(
      options[i].value,
      Tcl_GetVar2(n_interp, "OptionValue", options[i].name, TCL_GLOBAL_ONLY));
  }
  Tcl_SetResult(interp, "1", TCL_STATIC); return TCL_OK;
}

CMD(SendComplaint)
{ char cmdbuf[STRING_SIZE], errbuf[BUFSIZ];
  char *filename;
  FILE *msg;

  filename = make_temp_filename ("complaint");
  if (!(msg = fopen(filename, "w"))) {
    display_error("Can't store complaint, sorry.");
    Tcl_SetResult(interp, "", TCL_STATIC); return TCL_OK;
  }
  (void)fprintf(msg, "To: %s\n", MAINTAINER);
  (void)fprintf(msg, "Subject: %s\n", argv[1]);
  (void)fputs(argv[2], msg); (void)fclose(msg);

  (void) sprintf (cmdbuf, "%s %s <%s", MAIL, MAINTAINER, filename);
  if (system (cmdbuf) != 0) {
    (void)sprintf(errbuf, "Error running \"%s\".", cmdbuf);
    display_error(errbuf);
  } else
    (void)deletefile(filename);
  Tcl_SetResult(interp, "1", TCL_STATIC); return TCL_OK;
}

typedef struct {
    char *name;
    Tcl_CmdProc *proc;
} CmdInfo;

static CmdInfo infoCmds[] = {
{ "c_GotoNode",			(Tcl_CmdProc *) GotoNode },
{ "c_BackButton",		(Tcl_CmdProc *) BackButton },
{ "c_EditButton",		(Tcl_CmdProc *) EditButton },
{ "c_ExecButton",		(Tcl_CmdProc *) ExecButton },
{ "c_PrintNodeButton",		(Tcl_CmdProc *) PrintNodeButton },
{ "c_PrintManualButton",	(Tcl_CmdProc *) PrintManualButton },
{ "c_NodeMenu",			(Tcl_CmdProc *) NodeMenu },
{ "c_NodeNote",			(Tcl_CmdProc *) NodeNote },
{ "c_SearchNode",		(Tcl_CmdProc *) SearchNode },
{ "c_ResetOptions",		(Tcl_CmdProc *) ResetOptions },
{ "c_SendComplaint",		(Tcl_CmdProc *) SendComplaint },
{ NULL,				(Tcl_CmdProc *) NULL }
};

static int main_argc;
static char **main_argv;

int
#if defined(__cplusplus) || defined(__STDC__)
Tcl_AppInit (Tcl_Interp *interp)
#else
Tcl_AppInit (interp)
Tcl_Interp *interp;
#endif
{ char *cp;
  char buf[STRING_SIZE];
  int i;
  Tk_Window w;
  CmdInfo *cmdinfo;

  /* Save the interpreter into a global variable */
  n_interp = interp;

  if (Tcl_Init(n_interp) != TCL_OK)
    return TCL_ERROR;

  if (Tk_Init(n_interp) != TCL_OK)
    return TCL_ERROR;

  /* Get the main window */
  w = Tk_MainWindow(interp);
  Tk_SetClass(w, "TclInfo");

  /* Load the new commands */
  for (cmdinfo = infoCmds; cmdinfo->name != NULL; cmdinfo++)
	Tcl_CreateCommand (n_interp, cmdinfo->name, cmdinfo->proc,
			   (ClientData) 0, (Tcl_CmdDeleteProc *) NULL);

  /* Create top-level */
  if (Tcl_EvalFile (n_interp, main_argv[1]) != TCL_OK) {
	fprintf (stderr, "info.tcl:%d: %s\n", 
		 n_interp->errorLine, Tcl_GetStringResult(n_interp));
	exit (1);
  }

  if ((cp = getenv("EDITOR")) == (char *)NULL)
    sprintf (buf, "%s %s", DEFAULT_WINRUNNER, DEFAULT_EDITOR);
  else
    sprintf (buf, "%s %s", DEFAULT_WINRUNNER, cp);
  infotool_options[0].value = buf;
  init_options(infotool_options);

  for (i = 0; options[i].name; i++) {
    Tcl_SetVar2(n_interp, "OptionValue", options[i].name, options[i].value, TCL_GLOBAL_ONLY);
    Tcl_SetVar2(n_interp, "OptionDesc", options[i].name, options[i].desc, TCL_GLOBAL_ONLY);
  }

  main_argv[1] = main_argv[0]; main_argv++; main_argc--;
  info(main_argc, main_argv);
  display_node();

  return TCL_OK;
}

int
#if defined(__cplusplus) || defined(__STDC__)
main (int argc, char **argv)
#else
main (argc, argv)
int argc;
char **argv;
#endif
{
  /* Check args */
  if (argc < 2) {
        fprintf (stderr, "usage: tclinfo info.tcl\n");
        exit (1);
  }

  main_argc = argc;
  main_argv = argv;

  Tk_Main (1, argv, Tcl_AppInit);
}

void
#if defined(__cplusplus) || defined(__STDC__)
opsys_abort(char *s, int i)
#else
opsys_abort(s, i)
char *s; int i;
#endif
{ Tcl_VarEval(n_interp, "destroy .", NULL);
  (void)fputs(s, stderr);
  exit(i);
}

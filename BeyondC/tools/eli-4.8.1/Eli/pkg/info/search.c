#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PATH_SEPARATOR ':'
#define STDPATH "/usr/local/etc/mailcap:/usr/etc/mailcap:/etc/mailcap:/etc/mail/mailcap:/usr/public/lib/mailcap"

#define CMDSIZE 1200 /* Maximum size of command to execute */
#define LINE_BUF_SIZE       2000

char Command[CMDSIZE];

static char *nomem = "Out of memory!";

struct MailcapEntry {
    char *contenttype;
    char *command;
    char *testcommand;
    int needsterminal;
    int copiousoutput;
    char *label;
    char *printcommand;
} mc;

int DoDebug = 0;

char *ContentType;
char *FileName;

int ExitWithError(char*);

char *
Cleanse(char *s)
/* no leading or trailing space, all lower case */
{
    char *tmp, *news;
    
    /* strip leading white space */
    while (*s && isspace((unsigned char) *s)) ++s;
    news = s;
    /* put in lower case */
    for (tmp=s; *tmp; ++tmp) {
        if (isupper((unsigned char) *tmp)) *tmp = tolower((unsigned char) *tmp);
    }
    /* strip trailing white space */
    while (tmp > news && *--tmp && isspace((unsigned char) *tmp)) *tmp = 0;
    return(news);
}

void
usage(char *name)
{
    fprintf(stderr, "Usage: %s content-type file\n", name);
    ExitWithError(NULL);
}


void
StripTrailingSpace(char *s)
{
    char *t = s+strlen(s) -1;
    while (isspace((unsigned char) *t) && (t >= s)) *t-- = 0;
}

int
lc2strncmp(char *s1, char *s2, int len)
{
    if (!s1 || !s2) return (-1);
    while (*s1 && *s2 && len > 0) {
	if (*s1 != *s2 && (tolower(*s1) != *s2)) return(-1);
	++s1; ++s2; --len;
    }
    if (len <= 0) return(0);
    return((*s1 == *s2) ? 0 : -1);
}

int
lc2strcmp(char *s1, char *s2)
{
    if (!s1 || !s2) return (-1);
    while (*s1 && *s2) {
	if (*s1 != *s2 && (tolower(*s1) != *s2)) return(-1);
	++s1; ++s2;
    }
    return((*s1 == *s2) ? 0 : -1);
}

int
CtypeMatch(void)
/* Verify the content type
 *   On entry-
 *     ContentType is the desired content type
 *     mc contains a decoded mailcap entry
 *   If the mailcap entry denotes the desired content type then on exit-
 *     CtypeMatch=1
 *   Else on exit-
 *     CtypeMatch=0
 ***/
{ int len, retcode = 0;
  char *pat = mc.contenttype, *pat2 = NULL;

  if (!lc2strcmp(ContentType, pat)) { /* exact match, case-insensitive */
    return(1);
  }
  if (index(pat, '/') == NULL) { /* implicit wildcard */
    pat2 = malloc(3 + strlen(pat));
    if (!pat2) ExitWithError(nomem);
    strcpy(pat2, pat);
    strcat(pat2, "/*");
    pat = pat2;
  }
  len = strlen(pat);
  if ((pat[--len] == '*') &&
      (pat[--len] == '/') &&
      (!lc2strncmp(ContentType, pat, len)) &&
      ((ContentType[len] == '/') || (ContentType[len] == '\0'))) {
    retcode = 1;
  } else {
    retcode = 0;
  }
  if (pat2) free(pat2);
  return retcode;
}

void
strcpynoquotes(char *t, char *f)
{
    static char *badchars="|<>%*?\"`'";

    while (*f) {
        if (index(badchars, *f)) *t++ = ' '; else *t++ = *f;
        ++f;
    }
}

int
BuildCommand(char *controlstring, char *FileName)
{ char *from, *to, *s;
  int prefixed = 0;

/* FIXME: No check for buffer overflow on command */
  for (from=controlstring, to=Command; *from; ++from) {
    if (prefixed) {
      prefixed = 0;
      switch(*from) {
      case '%':
        *to++ = '%';
        break;
      case 's':
        if (FileName) {
          strcpy(to, FileName);
          to += strlen(FileName);
        }
        break;
      case 't':
        strcpynoquotes(to, ContentType);
        to += strlen(ContentType);
        break;
      default:
        if (DoDebug) fprintf(stderr, "Unrecognized format code: %%%c\n", *from);
        return 0;
      }
    } else if (*from == '%') {
      prefixed = 1;
    } else {
      *to++ = *from;
    }
  }
  *to = 0;
  return 1;
}

int
PassesTest(void)
/* Check whether a specified test passes
 *   On entry-
 *     mc has been set up
 *   If there is no test, or the test command returned 0, then on exit-
 *     PassesTest=1
 *   Else on exit-
 *     PassesTest=0
 ***/
{ int result;

  if (!mc.testcommand) return(1);
  BuildCommand(mc.testcommand, FileName);
  if (DoDebug) printf("Executing test command: %s\n", Command);
  result = system(Command);
  return(!result);
}

char *
GetCommand(char *s, char **t)
/* Extract a command
 *   On entry-
 *     s points to the input string
 *   On exit-
 *     GetCommand points to the string following the command
 *       (which may be null)
 *     *t points to the command string
 ***/
{ char *s2;
  int quoted = 0;

  while (s && *s && isspace((unsigned char) *s)) ++s;
  s2 = malloc(strlen(s)*2+1); /* absolute max, if all % signs */
  if (!s2) ExitWithError(nomem);
  *t = s2;
  while (s && *s) {
    if (quoted) {
      *s2++ = *s++;
      quoted = 0;
    } else {
      if (*s == ';') {
        *s2 = 0;
	return(++s);
      }
      if (*s == '\\') {
        quoted = 1;
	++s;
      } else {
	*s2++ = *s++;
      }
    }
  }
  *s2 = 0;
  return(NULL);
}	

int
GetMailcapEntry(FILE *fp)
/* Parse a mailcap entry
 *   On entry-
 *     fp=mailcap file being read
 *   If a valid mailcap entry is found then on exit-
 *     GetMailcapEntry=1
 *     mc holds the decoded entry
 *   Else on exit-
 *     GetMailcapEntry=0
 *     The content of mc is undefined
 ***/
{ int rawentryalloc = 2000, len;
  char *rawentry, *s, *t, *LineBuf;

  LineBuf = malloc(LINE_BUF_SIZE);
  if (!LineBuf) ExitWithError(nomem);
  rawentry = malloc(1 + rawentryalloc);
  if (!rawentry) ExitWithError(nomem);
  *rawentry = 0;
  while (fgets(LineBuf, LINE_BUF_SIZE, fp)) {
    if (LineBuf[0] == '#') continue;
    len = strlen(LineBuf);
    if (len == 0) continue;
    if (LineBuf[len-1] == '\n') LineBuf[--len] = 0;
    if ((len + strlen(rawentry)) > rawentryalloc) {
      rawentryalloc += 2000;
      rawentry = realloc(rawentry, rawentryalloc+1);
      if (!rawentry) ExitWithError(nomem);
    }
    if (LineBuf[len-1] == '\\') {
      LineBuf[len-1] = 0;
      strcat(rawentry, LineBuf);
    } else {
      strcat(rawentry, LineBuf);
      break;
    }
  }
  free(LineBuf);
  for (s=rawentry; *s && isspace((unsigned char) *s); ++s) ;
  if (!*s) { /* totally blank entry -- quietly ignore */
    free(rawentry);
    return(0);
  }
  s = index(rawentry, ';');
  if (!s) { /* ignore invalid entries unless debugging */
    if (DoDebug)
      fprintf(stderr, "Invalid mailcap entry: %s\n", rawentry);
    free(rawentry);
    return(0);
  }
  *s++ = 0;	/* Terminate the content type and point to the remainder */

  mc.needsterminal = 0;
  mc.copiousoutput = 0;
  mc.testcommand = NULL;
  mc.label = NULL;
  mc.printcommand = NULL;

  StripTrailingSpace(rawentry);
  mc.contenttype = malloc(1+strlen(rawentry));
  if (!mc.contenttype) ExitWithError(nomem);
  strcpy(mc.contenttype, rawentry);

  t = GetCommand(s, &mc.command);
  if (!t) { /* There are no parameters */
    free(rawentry);
    return(1);
  }
  s = t;
  while (s) {
    char *arg, *eq;

    t = GetCommand(s, &arg);
    eq = index(arg, '=');
    if (eq) *eq++ = 0;
    if (*arg) {
      arg = Cleanse(arg);
      if (!strcmp(arg, "needsterminal")) {
	mc.needsterminal = 1;
      } else if (!strcmp(arg, "copiousoutput")) {
	mc.copiousoutput = 1;
      } else if (eq && !strcmp(arg, "test")) {
	mc.testcommand = eq;
      } else if (eq && !strcmp(arg, "description")) {
	mc.label = eq;
      } else if (eq && !strcmp(arg, "label")) { 
	mc.label = eq; /* bogus old name for description */
      } else if (eq && !strcmp(arg, "print")) {
	mc.printcommand = eq;
      } else if (eq && !strcmp(arg, "textualnewlines")) {
	/* ExceptionalNewline(mc.contenttype, atoi(eq)); */
      } else if (strcmp(arg, "notes")) { /* IGNORE notes field */
      } else if (*arg && DoDebug) {
        fprintf(stderr, "ignoring mailcap flag: %s\n", arg);
      }
    }
    s = t;
  }
  free(rawentry);
  return(1);
}

int
ExitWithError(char *txt)
{
    if (txt) fprintf(stderr, "metamail: %s\n", txt);
    exit(-1);
}

int
IsBadFile(char *fname)
/* Check whether a file is suitable
 *   On entry-
 *     fname names the file to be checked
 *   If the file does not exist then on exit-
 *     IsBadFile=-1
 *   If the file is a directory then on exit-
 *     IsBadFile=1
 *   Else on exit-
 *     IsBadFile=0
 ***/
{ struct stat stbuf;
  if (stat(fname, &stbuf)) {
    return(-1);
  }
  return (((stbuf.st_mode & S_IFMT) == S_IFDIR) ? 1 : 0);
}

int
ProcessMailcapFile(char *file)
/* Search one mailcap file
 *   On entry-
 *     file is the name of the file to be searched
 *   If file has a valid entry for ContentType then on exit-
 *     ProcessMailcapFile=1
 *   Else on exit-
 *     ProcessMailcapFile=0
 ***/
{ FILE *fp;
  int res;

  res = IsBadFile(file);
  if (res) {
    if (DoDebug) { /* Quietly ignore bad files unless debugging */
      if (res == 1) {
        fprintf(stderr, "Mailcap path entry '%s' is a directory.\n", file);
      } else {
        fprintf(stderr, "Mailcap path entry '%s' does not exist.\n", file);
      }
    }
    return 0;
  }
  fp = fopen(file, "r");
  if (DoDebug)
    fprintf(stderr, "Looking for '%s' in mailcap file '%s'.\n", ContentType, file);
  while (fp && !feof(fp)) {
    if (GetMailcapEntry(fp)) {
      if (CtypeMatch() && PassesTest()) {
        fclose(fp);
        return 1;
      }
    }
  }
  if (fp) fclose(fp);
  return 0;
}

int
ProcessMailcapFiles(char *path)
{ char *s;

  while(path) {
    s = index(path, PATH_SEPARATOR);
    if (s) *s++ = 0;
    if (ProcessMailcapFile(path)) return 1;
    path = s;
  }
  return 0;
}

int
main(int argc, char **argv)
{ char *home, *path;
  int pathsize;

  if (argc != 3) usage(argv[0]);
  ContentType = argv[1];
  FileName=argv[2];

  pathsize = strlen(STDPATH);
  home = getenv("HOME");
  if (home) {
    pathsize += strlen(home) + strlen("/.mailcap:");
  }
  path = malloc(1+pathsize);
  if (!path) ExitWithError(nomem);

  if (home) {
    strcat(path, home); strcat(path, "/.mailcap:");
  }
  strcat(path, STDPATH);

  if (ProcessMailcapFiles(path) &&
      BuildCommand(mc.command, FileName)) {
    puts(Command);
    return 0;
  } else {
    return 1;
  }
}
